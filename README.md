
**Circuit Fault Detection README**
This README provides instructions on how to set up and run the code for Circuit Fault Detection. It includes information on generating the necessary environment and executing the code.

**Environment Setup**
Make sure you have a C++ compiler installed on your system.

**Clone the repository to your local machine using the following command:**
git clone https://github.com/your-username/circuit-fault-detection.git

Alternatively, you can download the repository as a ZIP file and extract it.

**Running the Code**
Navigate to the project directory:
cd circuit-fault-detection

**Compile the code using the C++ compiler:**
g++ -o main chip_fault_detector.cpp

**Run the executable:**
./circuit_fault_detection

**Usage**
1. Place the circuit file (in the specified format) in the project directory.
2. Modify the CIRCUIT_FILE_PATH constant in the chip_fault_detector.cpp file to match the filename of your circuit file.
3. Specify the fault node location (FAULT_AT) and fault type (FAULT_TYPE) in the main.cpp file.
4. Save the changes to main.cpp.
5. Compile and run the code using the steps mentioned in the "Running the Code" section.
6. The output will be displayed on the console and saved in the output.txt file in the run directory.

**Additional Information**
1. The circuit file should be in the specified format, with 4 input nodes (A, B, C, D), a circuit built using AND, OR, NOT, and XOR gates, and a single output node (Z).
2. The code assumes boolean inputs (0 or 1) for the circuit simulation and fault detection.
3. Ensure that the circuit file, fault node location, and fault type are correctly specified to obtain accurate results.
4. Feel free to modify the code to add more features or enhance functionality as per your requirements.
