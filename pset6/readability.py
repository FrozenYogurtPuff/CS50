from cs50 import get_string

def main():
    s = get_string("Text: ")
    l = count_letters(s)
    w = count_words(s)
    s = count_sentences(s)
    L = l / w * 100.0
    S = s / w * 100.0
    index = round(0.0588 * L - 0.296 * S - 15.8)
    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")

def count_letters(s):
    length = len(s)
    letter = 0
    for i in range(length):
        if s[i].isalpha():
            letter += 1
    return letter

def count_words(s):
    length = len(s)
    word = 1
    for i in range(length):
        if s[i].isspace():
            word += 1
    return word

def count_sentences(s):
    length = len(s)
    sentence = 0
    for i in range(length):
        if s[i] in ['.', '?', '!']:
            sentence += 1
    return sentence

main()
