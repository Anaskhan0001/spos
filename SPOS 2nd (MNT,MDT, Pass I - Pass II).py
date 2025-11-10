# Data Structures
class MacroProcessor:
    def __init__(self):
        self.MNT = {}  # Macro Name Table: {macro_name: MDT_index}
        self.MDT = []  # Macro Definition Table: list of macro lines
        self.ICF = []  # Intermediate Code File: source code without macro definitions

    # Pass-I: Process macro definitions
    def pass_one(self, source_code):
        is_macro = False
        macro_name = ""
        for line in source_code:
            words = line.split()

            if words[0] == "MACRO":  # Start of macro definition
                is_macro = True
                continue

            if is_macro:
                if macro_name == "":
                    # First line of macro definition: capture macro name and arguments
                    macro_name = words[0]
                    self.MNT[macro_name] = len(self.MDT)  # Record MNT entry
                    arguments = words[1:]
                    arg_map = {arg: f"#{i+1}" for i, arg in enumerate(arguments)}
                elif words[0] == "MEND":  # End of macro definition
                    is_macro = False
                    macro_name = ""
                    self.MDT.append("MEND")
                else:
                    # Process macro body: replace arguments with positional notations
                    for i, word in enumerate(words):
                        if word in arg_map:
                            words[i] = arg_map[word]
                    self.MDT.append(" ".join(words))
            else:
                # Non-macro code goes to ICF
                self.ICF.append(line)

    # Pass-II: Expand macros using MNT and MDT
    def pass_two(self):
        expanded_code = []
        for line in self.ICF:
            words = line.split()
            if words[0] in self.MNT:  # Macro call
                macro_start = self.MNT[words[0]]
                arguments = words[1:]
                arg_map = {f"#{i+1}": arg for i, arg in enumerate(arguments)}
                # Expand macro
                i = macro_start
                while self.MDT[i] != "MEND":
                    macro_line = self.MDT[i].split()
                    expanded_line = [
                        arg_map[word] if word in arg_map else word for word in macro_line
                    ]
                    expanded_code.append(" ".join(expanded_line))
                    i += 1
            else:
                # Non-macro code remains as is
                expanded_code.append(line)
        return expanded_code

    # Display tables and results
    def display_results(self):
        print("Macro Name Table (MNT):")
        for macro_name, index in self.MNT.items():
            print(f"{macro_name} -> MDT Index: {index}")
        print("\nMacro Definition Table (MDT):")
        for i, line in enumerate(self.MDT):
            print(f"{i}: {line}")
        print("\nIntermediate Code File (ICF):")
        for line in self.ICF:
            print(line)

# Main Program
if __name__ == "__main__":
    source_code = [
        "MACRO",
        "INCR &ARG1 &ARG2",
        "LDA &ARG1",
        "ADD &ARG2",
        "STA &ARG1",
        "MEND",
        "START",
        "INCR A B",
        "INCR X Y",
        "END",
    ]

    processor = MacroProcessor()
    print("Pass-I:")
    processor.pass_one(source_code)
    processor.display_results()

    print("\nPass-II:")
    expanded_code = processor.pass_two()
    print("\nExpanded Code:")
    for line in expanded_code:
        print(line)
