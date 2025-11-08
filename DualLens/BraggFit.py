import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

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

x_vals = np.linspace(0, 10, 500)

# Define your parameters (example values)
a1 = 10
a2 = 0.1
R0 = 7.4
p = 1.6

# Evaluate the function
y_vals = B_Func(x_vals, a1, a2, R0, p)
ax3.plot(x_vals, y_vals, label='B_Func')


plt.tight_layout()
plt.show()