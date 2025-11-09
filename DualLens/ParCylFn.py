import numpy as np
import matplotlib.pyplot as plt
from scipy.special import pbdv

# Parameters
y = -0.565
R0 = 7.4
sigma = 0.1

# Domain
x = np.linspace(0.0, 10.0, 1000)

# Mask: keep only x <= R0
mask = x <= R0

# Argument and function on the masked domain
z = (R0 - x[mask]) / sigma
D_vals = pbdv(y, z)[0]

# Optional: filter out inf/NaN just in case
finite = np.isfinite(D_vals)
x_plot = x[mask][finite]
D_plot = D_vals[finite]

# Plot
plt.plot(x_plot, D_plot, label=r'D_{%.3f}((R_0-x)/\sigma), x \le R_0' % y)
plt.axvline(R0, color='k', ls='--', lw=1, label='R0')
plt.xlabel('x')
plt.ylabel('D_y((R0-x)/sigma)')
plt.title('Parabolic cylinder function with mask x ≤ R0')
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()
