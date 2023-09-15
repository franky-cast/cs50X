import string
# scrabble


# making a dictionary that has the alphabet and an integer as key, value pairs respectively
lowercase_alphabet = list(string.ascii_lowercase)
letters_points_dict = {}
points = [1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10]
for letter in lowercase_alphabet:    
    letters_points_dict[letter] = points[lowercase_alphabet.index(letter)]



# prompts user to enter two words
def main ():
    words = []
    for x in range (0, 2):
        words.append(input("Enter a word: "))

    # initializes the scrabble game, prints result
    print(scrabble(words))



# gets score for both words entered by user
def scrabble (arr):
    score1 = compute_score(arr[0])
    score2 = compute_score(arr[1])

    
    if (score1 == score2):
        return "Tie!"
    

    result = "Player 1 wins!" if score2 < score1 else "Player 2 wins!"
    return result



def compute_score(word):
    score = 0

    # iterating thru each char of the word
    for char in word:
        lcChar = char.lower()

        # non alphabet characters do not affect scores
        if (not lcChar.isalpha()):
            continue
        else:
            # matching char with key (linear algorithm)
            for key, value in letters_points_dict.items():
                if key == lcChar:
                    score += value

    return score



if __name__ == "__main__":
    main()