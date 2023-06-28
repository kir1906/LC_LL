#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;
struct Gate
{
    string name;
    string type;
    vector<string> inputs;
    string output;
    int level;
    Gate *next;
    Gate(string n, string t, vector<string> in, string out, int l)
    {
        name = n;
        type = t;
        inputs = in;
        output = out;
        level = l;
        next = nullptr;
    }
};
void createGate(Gate *&head, string name, string type, vector<string> inputs, string output, int level)
{
    Gate *newGate = new Gate(name, type, inputs, output, level);
    if (head == nullptr)
    {
        head = newGate;
    }
    else
    {
        Gate *temp = head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = newGate;
    }
}
void displayCircuit(Gate *head)
{
    Gate *temp = head;
    while (temp != nullptr)
    {
        cout << "Gate Name: " << temp->name << endl;
        cout << "Gate Type: " << temp->type << endl;
        cout << "Inputs: ";
        for (const auto &input : temp->inputs)
        {
            cout << input << " ";
        }
        cout << endl;
        cout << "Output: " << temp->output << endl;
        cout << "Level: " << temp->level << endl;
        cout << endl;
        temp = temp->next;
    }
}
bool computeXORGate(const vector<bool> &inputs)
{
    bool output = false;
    for (const auto &input : inputs)
    {
        output = output ^ input;
    }
    return output;
}
bool computeANDGate(const vector<bool> &inputs)
{
    bool output = true;
    for (const auto &input : inputs)
    {
        output = output && input;
    }
    return output;
}
bool computeORGate(const vector<bool> &inputs)
{
    bool output = false;
    for (const auto &input : inputs)
    {
        output = output || input;
    }
    return output;
}
bool computeNOTGate(bool input)
{
    return !input;
}
int main()
{
    Gate *circuit = nullptr;
    string gateName, gateType, outputGate;
    int numInputs, level;

    cout << "Enter the number of gates: ";
    int numGates;
    cin >> numGates;

    for (int i = 0; i < numGates; i++)
    {
        cout << "Enter the details for Gate " << i + 1 << endl;

        cout << "Gate Name: ";
        cin >> gateName;

        cout << "Gate Type: ";
        cin >> gateType;

        cout << "Number of Inputs: ";
        cin >> numInputs;
        vector<string> inputs(numInputs);
        for (int j = 0; j < numInputs; j++)
        {
            cout << "Input " << j + 1 << ": ";
            cin >> inputs[j];
        }

        cout << "Output: ";
        cin >> outputGate;

        cout << "Level: ";
        cin >> level;

        createGate(circuit, gateName, gateType, inputs, outputGate, level);
        cout << endl;
    }
    displayCircuit(circuit);
    unordered_map<string, bool> gateOutputs;

    while (true)
    {
        cout << "Do you want to provide input values for the gates? (y/n): ";
        char choice;
        cin >> choice;

        if (choice == 'n' || choice == 'N')
        {
            break;
        }
        cout<<"How many inputs do you want to provied"<<endl;
        int nui;
        cin>>nui;
        for(int j=0;j<nui;++j)
        {
            cout<<"Enter the name of input : "<<endl;
            string s;
            cin>>s;
            cout<<" Value :"<<endl;
            bool inpu;
            cin>>inpu;
            gateOutputs[s]=inpu;
        }
        Gate *temp = circuit;
        while (temp != nullptr)
        {
            vector<bool> inputValues;
            for (const auto &input : temp->inputs)
            {
                if (gateOutputs.find(input) != gateOutputs.end())
                {
                    inputValues.push_back(gateOutputs[input]);
                }
                else
                {
                    cout << "Error: Input " << input << " is not defined!" << endl;
                    return 1;
                }
            }
            bool output;
            if (temp->type == "AND")
            {
                output = computeANDGate(inputValues);
            }
            else if (temp->type == "NAND")
            {
                output = computeANDGate(inputValues);
                output = computeNOTGate(output);
            }
            else if (temp->type == "NOR")
            {
                output = computeORGate(inputValues);
                output = computeNOTGate(output);
            }
            else if (temp->type == "OR")
            {
                output = computeORGate(inputValues);
            }
            else if (temp->type == "XOR")
            {
                output = computeXORGate(inputValues);
            }
            else if (temp->type == "XNOR")
            {
                output = computeXORGate(inputValues);
                output = computeNOTGate(output);
            }
            else if (temp->type == "NOT")
            {
                if (inputValues.size() != 1)
                {
                    cout << "Error: NOT gate should have exactly one input!" << endl;
                    return 1;
                }
                output = computeNOTGate(inputValues[0]);
            }
            else
            {
                cout << "Error: Unknown gate type " << temp->type << "!" << endl;
                return 1;
            }
            gateOutputs[temp->output] = output;
            temp = temp->next;
        }
        cout << "Output Values:" << endl;
        for (const auto &output : gateOutputs)
        {
            cout << output.first << ": " << output.second << endl;
        }
        cout << endl;
    }
    return 0;
}