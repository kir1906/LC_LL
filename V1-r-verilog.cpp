#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Gate {
    std::string type;
    std::vector<std::string> inputs;
    std::string output;
};

int main() {
    std::ifstream file("example.v"); // Replace "example.v" with your Verilog file name

    std::vector<Gate> gates;

    std::string line;
    while (std::getline(file, line)) {
        if (line.find("assign") != std::string::npos) {
            Gate gate;
            size_t startPos = line.find_first_of('(') + 1;
            size_t endPos = line.find_first_of(')');

            gate.type = line.substr(startPos, endPos - startPos);

            size_t arrowPos = line.find("=>") + 2;
            size_t semicolonPos = line.find(';');

            gate.output = line.substr(arrowPos, semicolonPos - arrowPos);

            std::string inputsStr = line.substr(endPos + 2, arrowPos - endPos - 3);

            size_t commaPos;
            while ((commaPos = inputsStr.find(',')) != std::string::npos) {
                gate.inputs.push_back(inputsStr.substr(0, commaPos));
                inputsStr.erase(0, commaPos + 2);
            }
            gate.inputs.push_back(inputsStr);

            gates.push_back(gate);
        }
    }

    // Printing the gate information
    for (const auto& gate : gates) {
        std::cout << "Type: " << gate.type << std::endl;
        std::cout << "Inputs: ";
        for (const auto& input : gate.inputs) {
            std::cout << input << " ";
        }
        std::cout << std::endl;
        std::cout << "Output: " << gate.output << std::endl;
        std::cout << "-----------------------" << std::endl;
    }

    file.close();
    return 0;
}