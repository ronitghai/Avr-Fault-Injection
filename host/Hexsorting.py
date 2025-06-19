def filter_unique_hex_strings(input_file, output_file):
    # Read strings from input file (don't know if this is actually what we'll have)
    with open(input_file, 'r') as f:
        hex_strings = f.readlines()

    # Count string occurrences
    string_counts = {}
    for string in hex_strings:
        string = string.strip()
        string_counts[string] = string_counts.get(string, 0) + 1

    # Only keep the unique strings for our new file
    with open(output_file, 'w') as f:
        for string, count in string_counts.items():
            if len(string) == 32 and count == 1 and all(c in '0123456789abcdefABCDEF' for c in string):
                f.write(string + '\n')

if __name__ == '__main__':
    input_file = input("Enter the path to the input file: ")
    output_file = input("Enter the path to the output file: ")

    filter_unique_hex_strings(input_file, output_file)
