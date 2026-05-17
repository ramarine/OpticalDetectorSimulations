import numpy as np
import pandas as pd
from scipy.interpolate import interp1d
from scipy.optimize import curve_fit
import matplotlib.pyplot as plt

# Load data files
# truth_df = pd.read_csv('PhotonData/proton_T100MeV_edep_bragg.csv')
meas_df = pd.read_csv('PhotonData/MPPC_proton_100.csv')
# meas_df = pd.read_csv('PhotonData/MPPC_proton_1000_24.csv')
# meas_df = pd.read_csv('PhotonData/MPPC_proton_100_32.csv')
truth_df = pd.read_csv('PhotonData/proton_T100MeV_BraggPeak_x_dose.csv')

# Handle duplicates by averaging energy values for each unique x_max
aggregated_data = truth_df.groupby('x_max[cm]').agg({
    'energy[MeV]': 'mean',
    'error_rel[percent]': 'mean'
}).reset_index()

# Store x_max and energy in numpy arrays
x_truth = aggregated_data['x_max[cm]'].values
y_truth = aggregated_data['energy[MeV]'].values


x_meas = meas_df['X [cm]'].values
y_meas = meas_df['energy[MeV]'].values
y_meas_err = meas_df['ey'].values

# Create interpolation function for truth table
interp_func = interp1d(x_truth, y_truth, kind='cubic', fill_value='extrapolate')

# Define fitting function with both X and Y scaling
def fit_func(x, x_scale, x_shift, y_scale, y_offset):
    """
    Transform truth table to match measured data
    x_scale: scales measured x to match truth x range
    x_shift: shifts measured x position
    y_scale: scales truth y to match measured y amplitude
    y_offset: adds offset to y values
    """
    xx = x_scale * x + x_shift
    xx = np.clip(xx, x_truth.min(), x_truth.max())
    yy = y_scale * interp_func(xx) + y_offset
    return yy

# Initial parameter guesses
x_scale_init = (x_truth.max() - x_truth.min()) / (x_meas.max() - x_meas.min())
x_shift_init = x_truth.min() - x_scale_init * x_meas.min()
y_scale_init = meas_df['energy[MeV]'].max() / truth_df['energy[MeV]'].max()
y_offset_init = 0

print("my initial guesses are x_scale_init= ", x_scale_init ," x_shift_init ", x_shift_init, " y_scale_init:", y_scale_init, " y_offset_init:", y_offset_init )
# Parameter bounds
bounds = ([1, -5, 1, -10], [15, 5, 100000, 10])

# Perform curve fitting
params, covariance = curve_fit(
    fit_func, x_meas, y_meas, 
    p0=[x_scale_init, x_shift_init, y_scale_init, y_offset_init],
    sigma=y_meas_err,
    absolute_sigma=True,
    bounds=bounds,
    maxfev=5000
)

x_scale_fit, x_shift_fit, y_scale_fit, y_offset_fit = params

print("="*60)
print("Fitted parameters:")
print(f"  x_scale: {x_scale_fit:.4f} (stretches measured x)")
print(f"  x_shift: {x_shift_fit:.4f} cm (shifts measured x)")
print(f"  y_scale: {y_scale_fit:.4f} (scales truth y)")
print(f"  y_offset: {y_offset_fit:.4f} MeV (y offset)")
print("="*60)

# Calculate goodness of fit
y_fit = fit_func(x_meas, *params)
residuals = y_meas - y_fit
ss_res = np.sum(residuals**2)
ss_tot = np.sum((y_meas - np.mean(y_meas))**2)
r_squared = 1 - (ss_res / ss_tot)
chi_squared = np.sum((residuals / y_meas_err)**2)
reduced_chi_squared = chi_squared / (len(y_meas) - len(params))

print(f"\nGoodness of fit:")
print(f"  R²: {r_squared:.4f}")
print(f"  Reduced χ²: {reduced_chi_squared:.4f}")
y_values = fit_func(x_truth, *params)

# Find the maximum y value and its corresponding x position
max_y = y_values.max()
max_x = x_truth[y_values.argmax()]
reco_R0 = max_x * x_scale_fit + x_shift_fit
print(f"Maximum y value: {max_y}")
print(f"At x position: {max_x}")
magnitude = 6.2
print(f"Reconstructed range: {reco_R0}")
print("Reco/Truth Range = ", 7.35/ reco_R0)

# Visualization
fig, axes = plt.subplots(2, 2, figsize=(10, 8))

# Plot 1: Measured data with fitted curve
ax1 = axes[0, 0]
ax1.errorbar(x_meas, y_meas, yerr=y_meas_err, fmt='ro', markersize=5, 
             capsize=3, label='MPPC Simulated Photon Distribution', alpha=0.7)
ax1.plot(x_truth, fit_func(x_truth, *params), 'b-', linewidth=2, 
         label='FLUKA Ideal Energy Deposition (Scintillator - optically magnified)')
ax1.set_xlabel('X [cm]')
ax1.set_ylabel('Energy Equivalent Units')
ax1.set_title('Fit: FLUKA Ideal vs C++ MPPC Simulated')
ax1.legend()
ax1.grid(True, alpha=0.3)

# Plot 2: Comparison with original truth
ax2 = axes[0, 1]
x_fit_range = np.linspace(x_meas.min(), x_meas.max(), 200)
ax2.plot(x_truth, y_truth, 'g-', linewidth=2, label='Original Truth', alpha=0.5)
# ax2.plot(x_fit_range, fit_func(x_fit_range, *params), 'b-', linewidth=2, 
        #  label='Scaled Truth')
# ax2.errorbar(x_meas, y_meas, yerr=y_meas_err, fmt='ro', markersize=4, 
            #  capsize=2, label='Measured', alpha=0.7)
ax2.set_xlabel('X [cm]')
ax2.set_ylabel('Energy [MeV]')
ax2.set_title('Truth Table Transformation')
ax2.legend()
ax2.grid(True, alpha=0.3)

# Plot 3: Residuals
ax3 = axes[1, 0]
ax3.errorbar(x_meas, residuals, yerr=y_meas_err, fmt='ro', markersize=5, capsize=3)
ax3.axhline(y=0, color='k', linestyle='--', linewidth=1)
ax3.set_xlabel('X [cm]')
ax3.set_ylabel('Residuals [MeV]')
ax3.set_title('Fit Residuals')
ax3.grid(True, alpha=0.3)

# Plot 4: Normalized residuals
ax4 = axes[1, 1]
normalized_residuals = residuals / y_meas_err
ax4.plot(x_meas, normalized_residuals, 'ro', markersize=5)
ax4.axhline(y=0, color='k', linestyle='--', linewidth=1)
ax4.axhline(y=2, color='orange', linestyle=':', linewidth=1, alpha=0.5)
ax4.axhline(y=-2, color='orange', linestyle=':', linewidth=1, alpha=0.5)
ax4.set_xlabel('X [cm]')
ax4.set_ylabel('Normalized Residuals (σ)')
ax4.set_title('Normalized Fit Residuals')
ax4.grid(True, alpha=0.3)

plt.tight_layout()
plt.savefig('fit_results.png', dpi=150, bbox_inches='tight')
plt.show()

print("\nFit complete! Results saved to 'fit_results.png'")
# Evaluate the function at all x_truth points

