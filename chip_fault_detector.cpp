include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <queue>
#include<algorithm>

using namespace std;

enum FaultType {
    SA0,
    SA1 
};

unordered_map<string, string> circuit;
unordered_map<string, bool> inputs;

bool evaluateGate(const string& gate) {
    size_t pos = gate.find_first_of("=~^&|");
    string op = gate.substr(pos, 1); 

    if (op == "=") {
        return inputs.at(gate.substr(pos + 2));
    } else if (op == "~") {
        return !evaluateGate(gate.substr(pos + 2));
    } else {
        size_t opPos = gate.find_first_of("=~^&|", pos + 2); 
        string operand1 = gate.substr(pos + 2, opPos - pos - 2); 
        string operand2 = gate.substr(opPos + 2); 

        bool value1 = evaluateGate(operand1);
        bool value2 = evaluateGate(operand2);

        if (op == "&") {
            return value1 && value2;
        } else if (op == "|") {
            return value1 || value2;
        } else if (op == "^") {
            return value1 ^ value2;
        }
    }   

    return false;
}

void simulateCircuit() {
    queue<string> gateQueue;
    for (auto it = circuit.begin(); it != circuit.end(); ++it) {
        gateQueue.push(it->first);
    }   

    while (!gateQueue.empty()) {
        string nodeName = gateQueue.front();
        gateQueue.pop();

        if (inputs.find(nodeName) == inputs.end()) {
            string gate = circuit[nodeName];

            if (gate.find_first_of("=~^&|") == string::npos) {
                inputs[nodeName] = evaluateGate(gate);
            } else {
                gateQueue.push(nodeName);
            }
        }
    }   
}

void findFaultInputVector(const string& circuitFile, const string& faultNode, FaultType faultType) {
    ifstream file(circuitFile);
    if (!file.is_open()) {
        cout << "Error: Unable to open circuit file." << endl;
        return;
    }   

    string line;
    while (getline(file, line)) {
        size_t equalPos = line.find('=');
        string nodeName = line.substr(0, equalPos);
        nodeName.erase(remove_if(nodeName.begin(), nodeName.end(), ::isspace), nodeName.end());
        string gate = line.substr(equalPos + 1); 

        circuit[nodeName] = gate;
        inputs[nodeName] = false;
    }   

    file.close();

    inputs[faultNode] = true; // Set the fault node to true
    simulateCircuit();
    bool expectedValue = (faultType == SA0) ? true : false;

    ofstream output("output.txt");
    if (output.is_open()) {
        output << "[A, B, C, D] = [";
        output << inputs["A"] << ", ";
        output << inputs["B"] << ", ";
        output << inputs["C"] << ", ";
        output << inputs["D"];
        output << "], Z = " << expectedValue << endl;

        output.close();
    } else {
        cout << "Error: Unable to write to output file." << endl;
    }   
}

int main() {
    string circuitFile = "circuit.txt";
    string faultNode = "net_f";
    FaultType faultType = SA0;

    findFaultInputVector(circuitFile, faultNode, faultType);

    return 0;
}
