# Protein Visualization Project 
Developed by Matthew Barrett and Dr. Nico Pietroni

The protein visualizer project is a software application that enables users to natively import Protein Data Bank (PDB) files directly into Unreal Engine 4 (UE4). Using data from PDBs, the application is able to offer the following functionality:

* Protein alignment through point-matching algorithms
* Comparative visualization of AlphaFold results
* Protein interpolation

## Installation Instructions

- Clone the repository or download the ZIP file
- Extract contents of the ZIP file to a folder on your computer
- Download the plugin below and copy it to `ProteinVis_2.0/Plugins/`
https://github.com/getnamo/SocketIOClient-Unreal
- Select the UProject file and select generate Visual Studio Project files
- Open the Visual Studio Solution (.sln) file and select build solution
- Ensure version `4.25.4` of UE4 is installed
- Launch again the UProject file


## Usage Instructions
For running the project in the UTS Data Arena, ensure that the target level is set to `Gallery`

To test the protein blending function, set to the target level to `DesktopViewer`

The latest functionality is found in the `SimpleUI` level.

For importing AlphaFold results, simply select the output folder containing the PDBs and `ranking_debug.json` 






## License

GPL3  licensed ([FAQ](https://www.gnu.org/licenses/gpl-faq.html))

For commerical licencing, please contact me at:
matthew.barrett@uts.edu.au
