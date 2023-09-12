#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

struct Gate
{
    string type;
    string g_name;
    vector<string> inputs;
    vector<string> outputs;
};

struct Module
{
    vector<string> inputs;
    vector<string> outputs;
    vector<Gate> gates;
};


Module parseVerilog(const string &filename)
{
    ifstream file(filename);
    string line;
    regex inputRegex(R"(input\s+([a-zA-Z0-9_,\s]+);)");
    regex wireRegex(R"(wire\s+([a-zA-Z0-9_,\s]+);)");
    regex outputRegex(R"(output\s+([a-zA-Z0-9_,\s]+);)");
    regex nandRegex(R"(nand\s+([()a-zA-Z0-9_,\s]+);)");
    regex andRegex(R"(and\s+([()a-zA-Z0-9_,\s]+);)");
    regex orRegex(R"(or\s+([()a-zA-Z0-9_,\s]+);)");
    regex xorRegex(R"(xor\s+([()a-zA-Z0-9_,\s]+);)");
    regex xnorRegex(R"(xnor\s+([()a-zA-Z0-9_,\s]+);)");
    regex norRegex(R"(nor\s+([()a-zA-Z0-9_,\s]+);)");
    regex notRegex(R"(not\s+([()a-zA-Z0-9_,\s]+);)");
    Module module;

    while (getline(file, line))
    {
        smatch match;

        if (regex_search(line, match, inputRegex))
        {
            string inputsStr = match[1].str();

            stringstream inputsStream(inputsStr);
            string input;
            while (getline(inputsStream, input, ','))
            {
                module.inputs.push_back(input);
            }
        }
        else if (regex_search(line, match, wireRegex))
        {
            string inputsStr = match[1].str();
            stringstream inputsStream(inputsStr);
            string input;
            while (getline(inputsStream, input, ','))
            {
                module.outputs.push_back(input);
            }
        }
        else if (regex_search(line, match, outputRegex))
        {
            string outputsStr = match[1].str();
            stringstream outputsStream(outputsStr);
            string output;
            while (getline(outputsStream, output, ','))
            {
                module.outputs.push_back(output);
            }
        }
        else if (regex_search(line, match, nandRegex))
        {
            Gate gate;
            gate.type = "nand";
            string inputsStr = match[1].str();
            inputsStr.erase(remove(inputsStr.begin(), inputsStr.end(), ' '), inputsStr.end());
            stringstream inputsStream(inputsStr);
            string input;
            string ss;
            getline(inputsStream, ss, '(');
            gate.g_name = ss;
            while (getline(inputsStream, input, ','))
                gate.inputs.push_back(input);
            string sss = gate.inputs.back();
            sss = sss.substr(0, sss.size() - 1);
            gate.inputs[gate.inputs.size() - 1] = sss;
            if (gate.inputs.size() != 0)
            {
                gate.outputs.push_back(gate.inputs[0]);
                gate.inputs.erase(gate.inputs.begin());
            }
            module.gates.push_back(gate);
        }
        else if (regex_search(line, match, andRegex))
        {
            Gate gate;
            gate.type = "and";
            string inputsStr = match[1].str();
            inputsStr.erase(remove(inputsStr.begin(), inputsStr.end(), ' '), inputsStr.end());
            stringstream inputsStream(inputsStr);
            string input;
            string ss;
            getline(inputsStream, ss, '(');
            gate.g_name = ss;
            while (getline(inputsStream, input, ','))
                gate.inputs.push_back(input);
            string sss = gate.inputs.back();
            sss = sss.substr(0, sss.size() - 1);
            gate.inputs[gate.inputs.size() - 1] = sss;
            if (gate.inputs.size() != 0)
            {
                gate.outputs.push_back(gate.inputs[0]);
                gate.inputs.erase(gate.inputs.begin());
            }
            module.gates.push_back(gate);
        }
        else if (regex_search(line, match, xnorRegex))
        {
            Gate gate;
            gate.type = "xnor";
            string inputsStr = match[1].str();
            inputsStr.erase(remove(inputsStr.begin(), inputsStr.end(), ' '), inputsStr.end());
            stringstream inputsStream(inputsStr);
            string input;
            string ss;
            getline(inputsStream, ss, '(');
            gate.g_name = ss;
            while (getline(inputsStream, input, ','))
                gate.inputs.push_back(input);
            string sss = gate.inputs.back();
            sss = sss.substr(0, sss.size() - 1);
            gate.inputs[gate.inputs.size() - 1] = sss;
            if (gate.inputs.size() != 0)
            {
                gate.outputs.push_back(gate.inputs[0]);
                gate.inputs.erase(gate.inputs.begin());
            }
            module.gates.push_back(gate);
        }
        else if (regex_search(line, match, xorRegex))
        {
            Gate gate;
            gate.type = "xor";
            string inputsStr = match[1].str();
            inputsStr.erase(remove(inputsStr.begin(), inputsStr.end(), ' '), inputsStr.end());
            stringstream inputsStream(inputsStr);
            string input;
            string ss;
            getline(inputsStream, ss, '(');
            gate.g_name = ss;
            while (getline(inputsStream, input, ','))
                gate.inputs.push_back(input);
            string sss = gate.inputs.back();
            sss = sss.substr(0, sss.size() - 1);
            gate.inputs[gate.inputs.size() - 1] = sss;
            if (gate.inputs.size() != 0)
            {
                gate.outputs.push_back(gate.inputs[0]);
                gate.inputs.erase(gate.inputs.begin());
            }
            module.gates.push_back(gate);
        }
        else if (regex_search(line, match, norRegex))
        {
            Gate gate;
            gate.type = "nor";
            string inputsStr = match[1].str();
            inputsStr.erase(remove(inputsStr.begin(), inputsStr.end(), ' '), inputsStr.end());
            stringstream inputsStream(inputsStr);
            string input;
            string ss;
            getline(inputsStream, ss, '(');
            gate.g_name = ss;
            while (getline(inputsStream, input, ','))
                gate.inputs.push_back(input);
            string sss = gate.inputs.back();
            sss = sss.substr(0, sss.size() - 1);
            gate.inputs[gate.inputs.size() - 1] = sss;
            if (gate.inputs.size() != 0)
            {
                gate.outputs.push_back(gate.inputs[0]);
                gate.inputs.erase(gate.inputs.begin());
            }
            module.gates.push_back(gate);
        }
        else if (regex_search(line, match, orRegex))
        {
            Gate gate;
            gate.type = "or";
            string inputsStr = match[1].str();
            inputsStr.erase(remove(inputsStr.begin(), inputsStr.end(), ' '), inputsStr.end());
            stringstream inputsStream(inputsStr);
            string input;
            string ss;
            getline(inputsStream, ss, '(');
            gate.g_name = ss;
            while (getline(inputsStream, input, ','))
                gate.inputs.push_back(input);
            string sss = gate.inputs.back();
            sss = sss.substr(0, sss.size() - 1);
            gate.inputs[gate.inputs.size() - 1] = sss;
            if (gate.inputs.size() != 0)
            {
                gate.outputs.push_back(gate.inputs[0]);
                gate.inputs.erase(gate.inputs.begin());
            }
            module.gates.push_back(gate);
        }
        else if (regex_search(line, match, notRegex))
        {
            Gate gate;
            gate.type = "not";
            string inputsStr = match[1].str();
            inputsStr.erase(remove(inputsStr.begin(), inputsStr.end(), ' '), inputsStr.end());
            stringstream inputsStream(inputsStr);
            string input;
            string ss;
            getline(inputsStream, ss, '(');
            gate.g_name = ss;
            while (getline(inputsStream, input, ','))
                gate.inputs.push_back(input);
            string sss = gate.inputs.back();
            sss = sss.substr(0, sss.size() - 1);
            gate.inputs[gate.inputs.size() - 1] = sss;
            if (gate.inputs.size() != 0)
            {
                gate.outputs.push_back(gate.inputs[0]);
                gate.inputs.erase(gate.inputs.begin());
            }
            module.gates.push_back(gate);
        }
    }

    return module;
}
struct Node
{
    string name;
    string type;
    Node *next = NULL;
};

void connectNodes(vector<Node*> &nodes, const Module &module)
{
    unordered_map<string, int> mp;
    int ind = 0;
    for (auto it : module.inputs)
    {
        Node* ne=new Node;
        ne->name=it;
        ne->type="INPUT";
        ne->next=NULL;
        nodes.push_back(ne);
        mp[it] = ind++;
    }
    for (auto it : module.outputs){
         Node* ne=new Node;
        ne->name=it;
        ne->next=NULL;
        nodes.push_back(ne);
        mp[it] = ind++;
    }
    for(auto it:module.gates)
    {
        string type_g=it.type;
        vector<string>ip=it.inputs;
        string op=it.outputs[0];
        for(auto it1:ip)
        {
            Node* node = nodes[mp[it1]];
            Node* ne = new Node();
            ne->name=op;
            ne->type=type_g;
            nodes[mp[op]]->type=type_g;
            ne->next=NULL;
            while(node->next!=NULL)
            node=node->next;
            node->next=ne;
        }
    }
}

void displayfun(Module &module)
{
    vector<string> inputts = module.inputs;
    vector<string> outputts = module.outputs;
    vector<Gate> gatess = module.gates;

    for (auto it : inputts)
        cout << it << " ";
    cout << endl;
    for (auto it : outputts)
        cout << it << " ";
    cout << endl;

    for (auto it : gatess)
    {
        string type = it.type;
        vector<string> gateinput = it.inputs;
        vector<string> gateoutput = it.outputs;
        cout << type << " " << endl
             << "inputs"
             << " : ";
        for (auto ip : gateinput)
            cout << ip << " ";
        cout << endl;
        cout << "Output"
             << " : ";
        for (auto op : gateoutput)
            cout << op << " ";
        cout << endl;
    }
}

// void displayConnections(const vector<Node>& nodes) {
//     for (const auto& node : nodes) {
//         cout << "Node Name: " << node.name << ", Type: " << node.type << endl;
//         if (!node.connections.empty()) {
//             cout << "Connected to:";
//             for (const auto& connection : node.connections) {
//                 cout << " " << connection->name;
//             }
//             cout << endl;
//         } else {
//             cout << "No connection" << endl;
//         }
//         cout << endl;
//     }
// }

void displaycircuit(vector<Node*> &nodes){
    
    for(auto it : nodes){
        Node* node = it;
        while(node){
            cout<<node->type<<" ";
            cout<<node->name<<" -> ";
            node = node-> next;
        }
        cout<<"NULL"<<endl;
        
    }
}

int main()
{
    Module module = parseVerilog("example.v");
    vector<Node*> nodes;
    connectNodes(nodes, module);
    // for(auto it: nodes){

    //     cout<< it->type << " "<<it->name<<endl;
    // }
    displaycircuit(nodes);
    return 0;
}