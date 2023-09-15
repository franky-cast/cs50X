# Substitution - CS50
import string

def main ():
    key = validateKey()
    plain_text = input("Enter plain text: ")
    cipher_text = encode(plain_text, key)

    print(f'ciphertext: {cipher_text}')

    return 0

# verifies cipher key is 26 characters long and contains only alphabetic characters
def validateKey():
    repeat = True
    while (repeat):
        key = input("Enter cipher key: ")
        if (len(key) != 26):
            print("Key must be 26 alphabetic characters \n")
            continue

        if (not key.isalpha()):
            print("key.isalpha() returns False \n")
            continue

        repeat = False
        print("\n")
        break

    return key

# substitues each character of the plain_text string based on the cipher key provided
def encode(plain_text, key):
    alphabet = string.ascii_lowercase
    cipher_text = ""

    for char in plain_text:
        # Adds non-alphabetic characters to cipher_text as they are
        if (not char.isalpha()):
            cipher_text += char
            continue

        # If char is alphabetic, fork in the road --> upper or lower?
        # Fork #1: Uppercase char's
        if (char.isupper()):
            lcChar = char.lower()
            for letter in alphabet:
                if lcChar == letter:
                    current_index = alphabet.index(letter)
                    break
            cipher_text += key[current_index].upper()
            continue
        
        # Fork #2: Lowercase char's
        for letter in alphabet:
            if char == letter:
                current_index = alphabet.index(letter)
                break
        cipher_text += key[current_index].lower()

    return cipher_text

if __name__ == "__main__":
    main()