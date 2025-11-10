#include iostream
#include vector
#include unordered_map
#include string
#include iomanip
#include sstream

using namespace std;

 Structure to store details of each line in the intermediate code
struct IntermediateLine {
    int loc;
    string instruction;
    string operand;
};

 Opcode table to map mnemonics to opcode and instruction length
unordered_mapstring, pairstring, int opcodeTable = {
    {LOAD, {01, 2}},
    {STORE, {02, 2}},
    {ADD, {03, 2}},
    {SUB, {04, 2}},
    {MULT, {05, 2}}
};

 Symbol table for storing labels and their memory addresses
unordered_mapstring, int symbolTable;

 Intermediate code storage
vectorIntermediateLine intermediateCode;

 Function to parse a line into label, instruction, and operand
void parseLine(const string &line, string &label, string &instruction, string &operand) {
    stringstream ss(line);
    label = instruction = operand = ;
    ss  label;

    if (opcodeTable.count(label)  label == START  label == END  label == DC  label == DS) {
        instruction = label;
        label = ;
        ss  operand;
    } else {
        ss  instruction  operand;
    }
}

 Pass-I Generate the symbol table and intermediate code
void passOne(const vectorstring &sourceCode) {
    int LC = 0;   Location counter

    for (const string &line  sourceCode) {
        string label, instruction, operand;
        parseLine(line, label, instruction, operand);

         Handle START directive
        if (instruction == START) {
            LC = stoi(operand);
            continue;
        }

         Process label
        if (!label.empty()) {
            symbolTable[label] = LC;
        }

         Process instructions
        if (opcodeTable.count(instruction)) {
            intermediateCode.push_back({LC, instruction, operand});
            LC += opcodeTable[instruction].second;  Update LC by instruction length
        }
         Handle data definition (DC) directive
        else if (instruction == DC) {
            symbolTable[label] = LC;
            intermediateCode.push_back({LC, DC, operand});
            LC += 1;   Assuming DC takes one memory word
        }
         Handle space reservation (DS) directive
        else if (instruction == DS) {
            symbolTable[label] = LC;
            LC += stoi(operand);   Reserve space
        }
         Handle END directive
        else if (instruction == END) {
            break;
        }
    }
}

 Pass-II Generate the final machine code
void passTwo() {
    cout  nFinal Machine Coden;
    for (const IntermediateLine &line  intermediateCode) {
        string opcode = opcodeTable[line.instruction].first;
        int operandAddress = 0;

        if (!line.operand.empty() && symbolTable.count(line.operand)) {
            operandAddress = symbolTable[line.operand];
        }

        if (line.instruction == DC) {
            cout  setw(4)  setfill('0')  line.loc   DC   line.operand  endl;
        } else {
            cout  setw(4)  setfill('0')  line.loc     opcode     setw(4)  setfill('0')  operandAddress  endl;
        }
    }
}

int main() {
    vectorstring sourceCode;
    string line;

     Get the source code from the user
    cout  Enter the source code line by line (enter 'END' to finish)n;
    while (true) {
        getline(cin, line);
        if (line == END) {
            break;
        }
        sourceCode.push_back(line);
    }

     Run Pass-I
    passOne(sourceCode);
    cout  nSymbol Tablen;
    for (const auto &entry  symbolTable) {
        cout  entry.first     entry.second  endl;
    }

     Run Pass-II
    passTwo();

    return 0;
}

 Enter the source code line by line (enter 'END' to finish)
 START 100
 LOAD A
 ADD B
 STORE C
 A DC 5
 B DC 10
 C DS 1
 END

 Symbol Table
 A 100
 B 102
 C 104

 Final Machine Code
 0100 01 0100
 0102 03 0102
 0104 02 0104
 0105 DC 5
 0106 DC 10
 0107 DS 1

