import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
from scipy.special import gamma
from scipy.special import pbdv

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

def B_Func(x, a1, a2, R0, p):
    val = np.zeros_like(x)
    mask = (x <= R0)
    val[~mask] = 0
    val[mask] = ((a1 * (R0 - x[mask])**(1.0/p - 1.0) + a2 * (R0 - x[mask])**(1.0/p)))
    return val

#  Read data from CSV
data = np.loadtxt('PhotonData/proton_T100MeV_edep_bragg.csv', delimiter=',', skiprows=1)
data2 = np.loadtxt("MPPCData/MPPC_proton_1000.csv", delimiter=',', skiprows=1)

Scint_pos, energy = data[:,0],data[:,1]
MPPC_pos, MPPC_phot, MPPC_pos_err, MPPC_phot_err = data2[:,0], data2[:,1], data2[:,2], data2[:,3]





# seed_params_Scint = [1.0, 0.5, Scint_pos[np.argmax(energy)], 2.0]
# params_opt, params_cov = curve_fit(B_Func, Scint_pos, energy, p0=seed_params_Scint, bounds=([0, 0, 0, 0], [np.inf, 10, 20, 5]))

# print("PULAA " , max(Scint_pos)*0.9 , " PULA 22 ", Scint_pos[np.argmax(energy)])

seed_params_Scint = [1.0, 0.5, max(Scint_pos)*0.9, 2.0]
params_opt, params_cov = curve_fit(B_Func, Scint_pos, energy, p0=seed_params_Scint)

# Initial parameter guesses
max_index = np.argmax(MPPC_phot)  # Find index of max value efficiently
init_R0 = MPPC_pos[max_index]
init_R0 = 1.
seed_params_MPPC = [10, 0.9, 1.27, 1.6]
params_opt2, covariance = curve_fit(B_Func, MPPC_pos, MPPC_phot, p0=seed_params_MPPC, bounds=([0, 0, 0, 0], [np.inf, np.inf, 2, 5]))
a1_fit, a2_fit, R0_fit, p_fit = params_opt2
y_fit = B_Func(MPPC_pos, *params_opt2)



# Parameter names for display
param_names = ['a1', 'a2', 'R0', 'p']
param_text = '\n'.join([f'{name} = {value:.4f}' for name, value in zip(param_names, params_opt)])

# Generate fitted curve data
x_vals = np.linspace(min(Scint_pos), max(Scint_pos), 200)
fitted_vals = B_Func(x_vals, *params_opt)



# Optional: print fitted parameters
print(f'Fitted parameters: a1={params_opt2[0]:.4f}, a2={params_opt2[1]:.4f}, R0={params_opt2[2]:.4f}, p={params_opt2[3]:.4f}')

param_names = ['a1', 'a2', 'R0', 'p']

# param_text1 = '\n'.join([f'{name} = {value:.4f}' for name, value in zip(param_names, params_opt)])
param_text2 = '\n'.join([f'{name} = {value:.4f}' for name, value in zip(param_names, params_opt2)])

# Plot both datasets side by side on one canvas
fig, (ax1, ax2, ax3) = plt.subplots(1, 3, figsize=(20,6), sharey=False)

# Left plot for first dataset (replace X1, energy1, fit_vals1 accordingly)
ax1.plot(Scint_pos, energy, 'bo', label='Data 1')
ax1.plot(x_vals, fitted_vals, 'r-', label='Fit 1')
ax1.set_xlabel('Scintilator Position X [cm]')
ax1.set_ylabel('Energy [MeV]')
ax1.set_title('Proton Energy Deposition In Scintillator')
ax1.legend()
ax1.grid(True)
ax1.text(0.05, 0.95, param_text, transform=ax1.transAxes, fontsize=10,
         verticalalignment='top', bbox=dict(boxstyle='round', facecolor='white', alpha=0.8))

# Right plot for second dataset with errors
ax2.errorbar(MPPC_pos, MPPC_phot, yerr=MPPC_phot_err, xerr=MPPC_pos_err, fmt='go', label='Data 2')
ax2.plot(MPPC_pos, y_fit, 'm-', label='Fit 2')
ax2.set_xlabel('MPPC Position X [cm]')
ax2.set_ylabel('Photon Count per Pixel')
ax2.set_title('Photon Distribution at MPPC')
ax2.legend()
ax2.grid(True)
ax2.text(0.05, 0.95, param_text2, transform=ax2.transAxes, fontsize=10,
         verticalalignment='top', bbox=dict(boxstyle='round', facecolor='white', alpha=0.8))


R0 = 15.0
z = np.linspace(0, R0 + 2.0, 800)
Dvals = D_piecewise(z, R0, Phi0=1.0)

# Optional normalization for plotting:
Dn = Dvals / np.max(Dvals) if np.max(Dvals) > 0 else Dvals

# D_vals = B_Func(x_vals, psi0,p,R0)

ax3.plot(z, Dn, label=f'dasd')
ax3.axvline(R0, color="k", linestyle="--", linewidth=1)
ax3.grid(True)
ax3.set_xlabel('Depth Z (cm)')
ax3.set_ylabel('Dose')

# ax3.tight_layout()
plt.show()

print (gamma(1/p))