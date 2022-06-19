# TODO

from cs50 import get_string


def main():
    text = get_string("Text: ")
    w = count_words(text)
    l = count_letters(text)
    s = count_sentences(text)

    # Cast values to float before performing division when calculating L and S!
    # Otherwise the result will be truncated.
    L = l * 100.00 / w
    S = s * 100.00 / w

    # Round the resulting index number to the nearest int
    index = round(0.0588 * L - 0.296 * S - 15.8)
    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


def count_words(text):
    # Assume that a sentence will not start or end with a space so first word counts
    count = 1
    for i in text:
        if i.isspace():
            count += 1
    return count


def count_letters(text):
    count = 0
    for i in text:
        if i.isalpha():
            count += 1
    return count


def count_sentences(text):
    count = 0
    for i in text:
        if i in [".", "!", "?"]:
            count += 1
    return count


if __name__ == "__main__":
    main()
