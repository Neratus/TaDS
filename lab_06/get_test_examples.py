import random
from nltk.corpus import words

def generate_random_words(n):
    word_list = words.words()

    random_words = random.sample(word_list, n)

    return random_words


def save_words_to_file(words, filename):
    with open(filename, 'w') as file:
        for word in words:
            file.write(word + '\n')

n = int(input("Введите количество случайных слов: "))

random_words = generate_random_words(n)

filename = "/Applications/programms/Types and structures of data/lab_06-work_in_progress/example_files/{0}words.txt".format(n)
save_words_to_file(random_words, filename)

print(f"Случайные слова сохранены в файле {filename}")


sorted_word_list = sorted(random_words)
filename = "/Applications/programms/Types and structures of data/lab_06-work_in_progress/example_files/{0}_sorted_words.txt".format(n)
save_words_to_file(sorted_word_list, filename)

print(f"Отсортированные слова сохранены в файле {filename}")
