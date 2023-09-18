import csv
import sys


def main():
    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    # TODO: Read database file into a variable
    csv_file = sys.argv[1]
    dna_database = []
    header = None
    with open (csv_file) as fp:
        reader = csv.DictReader(fp, delimiter=',')

        # storing the csv header sequences in a list
        header = list(reader.fieldnames)
        header = header[1:]

        # storing database file into an array of dictionaries
        for row in reader:
            person_name = row["name"]
            sequences = {}
            for x in header:
                sequences[x] = int(row[x])

            dna_database.append({
                "name": person_name,
                "sequence": sequences
            })
    
    # TODO: Read DNA sequence file into a variable
    txt_file = sys.argv[2]
    unkown_dna = None
    with open (txt_file, "r") as dna_sequence:
        unkown_dna = dna_sequence.read()  

    # TODO: Find longest match of each STR in DNA sequence
    strs = {}
    for x in header:
        strs[x] = longest_match(unkown_dna, x)

    # TODO: Check database for matching profiles
    for profile in dna_database:
        if profile["sequence"] == strs:
            print(profile["name"])
            sys.exit(0)

    print("No match")
    
    sys.exit(0)


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1
            
            # If there is no match in the substring
            else:
                break
        
        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
