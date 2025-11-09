import numpy as np
from scipy.special import pbdv  # returns (D_v(x), D_v'(x))

# Constants for water from Table I (modifiable for other media)
p_default = 1.77                 # exponent of range–energy relation
beta_default = 0.012             # cm^-1 (fluence reduction slope)
epsilon_default = 0.1            # fraction locally absorbed in nuclear interactions
sigma_from_R0 = lambda R0: 0.012 * R0**0.935  # cm (Eq. 18)

def Dhat_H2O(z, R0, Phi0=1.0, beta=beta_default, eps=epsilon_default):
    """
    Eq. (28): D̂_H2O(z) — depth-dose without straggling, water.
    Returns array with zeros for z > R0 as implied by the model.
    """
    z = np.asarray(z, dtype=float)
    dz = R0 - z
    out = np.zeros_like(dz)

    mask = dz > 0.0
    # numbers from Eq. (28): 17.93, 0.435 and coefficients for the eps term
    out[mask] = (Phi0 / (1.0 + beta * R0)) * (
        17.93 * (dz[mask])**(-0.435) + (0.444 + 31.7 * eps / R0) * (dz[mask])**0.565
    )
    return out  # Eq. (28) [attached_file:2]

def D_H2O(z, R0, Phi0=1.0, beta=beta_default, eps=epsilon_default, sigma=None):
    """
    Eq. (29): D_H2O(z) — depth-dose with range straggling, water.
    Computes exp(- (R0 - z)^2 / (4 sigma^2)) * sigma^0.565 times a linear combination
    of parabolic cylinder functions with orders -0.565 and -1.565 evaluated at -(R0 - z)/sigma.
    """
    z = np.asarray(z, dtype=float)
    if sigma is None:
        sigma = sigma_from_R0(R0)

    dz = R0 - z
    out = np.zeros_like(dz)

    mask = dz > 0.0  # only defined for z < R0 before applying Eq. (27) window
    if not np.any(mask):
        return out

    x = -dz[mask] / sigma
    # exp( - (R0 - z)^2 / (4 sigma^2) ) * sigma^0.565 /(1 + 0.012 R0)
    pref = Phi0 * np.exp(-(dz[mask]**2) / (4.0 * sigma**2)) * (sigma**0.565) / (1.0 + beta * R0)

    # Parabolic cylinder functions D_v(x) with v = -0.565 and v = -1.565
    Dm0565 = pbdv(-0.565, x)[0]
    Dm1565 = pbdv(-1.565, x)[0]

    out[mask] = pref * (11.26 * (sigma**-1) * Dm0565 + (0.157 + 11.26 * eps / R0) * Dm1565)
    return out  # Eq. (29)

def D_piecewise(z, R0, Phi0=1.0, beta=beta_default, eps=epsilon_default, sigma=None,
                use_Dhat_below=True):
    """
    Eq. (27) piecewise definition:
      - For z < R0 - 10*sigma: D̂(z) (optionally) or D(z). The paper allows D̂ since D and D̂ agree within 0.5%.
      - For R0 - 10*sigma <= z <= R0 + 5*sigma: D(z)
      - Otherwise: 0
    """
    z = np.asarray(z, dtype=float)
    if sigma is None:
        sigma = sigma_from_R0(R0)

    Dhat = Dhat_H2O(z, R0, Phi0=Phi0, beta=beta, eps=eps)
    Dfull = D_H2O(z, R0, Phi0=Phi0, beta=beta, eps=eps, sigma=sigma)

    out = np.zeros_like(z, dtype=float)
    lower = z < (R0 - 10.0 * sigma)
    middle = (z >= (R0 - 10.0 * sigma)) & (z <= (R0 + 5.0 * sigma))
    # Upper region z > R0 + 5*sigma is already zero

    if use_Dhat_below:
        out[lower] = Dhat[lower]          # D̂(z) below the window
    else:
        out[lower] = Dfull[lower]         # Optionally use D(z) everywhere

    out[middle] = Dfull[middle]           # D(z) in the window
    # out[~(lower|middle)] remains 0 as per Eq. (27)

    return out  # Eq. (27) windowing [attached_file:2]

# Example usage:
if __name__ == "__main__":
    import matplotlib.pyplot as plt
    R0 = 15.0
    z = np.linspace(0, R0 + 2.0, 800)
    Dvals = D_piecewise(z, R0, Phi0=1.0)

    # Optional normalization for plotting:
    Dn = Dvals / np.max(Dvals) if np.max(Dvals) > 0 else Dvals

    plt.plot(z, Dn, label="Bortfeld Eq. 27/28/29 (water)")
    plt.axvline(R0, color="k", ls="--", lw=1)
    plt.xlabel("Depth z (cm)")
    plt.ylabel("Relative dose")
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    plt.show()
