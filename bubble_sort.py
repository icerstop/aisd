import random
lista = []

for x in range(15):
    lista.append(random.randint(1, 100))
print(lista)


def bubble_sort(array):
    for i in range(1, len(array) - 1):
        to_sort_check = False
        for j in range(len(array) - i):
            if array[j] > array[j + 1]:
                pom = array[j]
                array[j] = array[j + 1]
                array[j + 1] = pom
                to_sort_check = True
        if not to_sort_check:
            break


print(lista)
