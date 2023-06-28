#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;
#include <bits/stdc++.h>
struct Gate {
    std::string type;
    std::vector<std::string> inputs;
    std::vector<std::string> outputs;
};

struct Module {
    std::vector<std::string> inputs;
    std::vector<std::string> outputs;
    std::vector<Gate> gates;
};

struct Node {
    std::string name;
    std::string type;
    std::vector<Node*> connections;
};

Module parseVerilog(const std::string& dd) {
    std::ifstream file(dd);
    std::string line;
    std::regex inputRegex(R"(input\s+([a-zA-Z0-9_,\s]+);)");
    std::regex outputRegex(R"(output\s+([a-zA-Z0-9_,\s]+);)");
    std::regex gateRegex(R"(nand\s+([a-zA-Z0-9_]+)\s*\(([a-zA-Z0-9_,]+)\);)");

    Module module;

    while (std::getline(file, line)) {
        std::smatch match;

        if (std::regex_search(line, match, inputRegex)) {
            std::string inputsStr = match[1].str();
            std::stringstream inputsStream(inputsStr);
            std::string input;

            while (std::getline(inputsStream, input, ',')) {
                module.inputs.push_back(input);
            }
        }
        else if (std::regex_search(line, match, outputRegex)) {
            std::string outputsStr = match[1].str();
            std::stringstream outputsStream(outputsStr);
            std::string output;

            while (std::getline(outputsStream, output, ',')) {
                module.outputs.push_back(output);
            }
        }
        else if (std::regex_search(line, match, gateRegex)) {
            Gate gate;
            gate.type = match[1].str();
            std::string inputsStr = match[2].str();
            std::stringstream inputsStream(inputsStr);
            std::string input;

            while (std::getline(inputsStream, input, ',')) {
                gate.inputs.push_back(input);
            }

            gate.outputs.push_back(module.outputs.back());
            module.gates.push_back(gate);
        }
    }

    return module;
}

void connectNodes(std::vector<Node>& nodes, const Module& module) {
    std::unordered_map<std::string, Node*> nodeMap;
    for (auto& node : nodes) {
        nodeMap[node.name] = &node;
    }

    for (const auto& gate : module.gates) {
        for (const auto& output : gate.outputs) {
            Node* outputNode = nodeMap[output];
            for (const auto& input : gate.inputs) {
                Node* inputNode = nodeMap[input];
                outputNode->connections.push_back(inputNode);
                outputNode = inputNode;
            }
        }
    }
}

void displayConnections(const std::vector<Node>& nodes) {
    for (const auto& node : nodes) {
        std::cout << "Node Name: " << node.name << ", Type: " << node.type << std::endl;
        if (!node.connections.empty()) {
            std::cout << "Connected to:";
            for (const auto& connection : node.connections) {
                std::cout << " " << connection->name;
            }
            std::cout << std::endl;
        } else {
            std::cout << "No connection" << std::endl;
        }
        std::cout << std::endl;
    }
}

int main() {
    Module module = parseVerilog("example.v");

    std::vector<Node> nodes;
    for (const auto& input : module.inputs) {
        nodes.push_back({ input, "input", {} });
    }

    for (const auto& gate : module.gates) {
        for (const auto& input : gate.inputs) {
            nodes.push_back({ input, gate.type, {} });
        }
        for (const auto& output : gate.outputs) {
            nodes.push_back({ output, gate.type, {} });
        }
    }

    connectNodes(nodes, module);

    displayConnections(nodes);

    return 0;
}