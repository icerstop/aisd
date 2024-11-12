import random
lista = []

for x in range(15):
    lista.append(random.randint(1, 100))
print(lista)


def selection_sort(array):
    for i in range(len(array)):
        mini = array[i]
        mini_index = i
        for j in range(i, len(array)):
            if array[j] < mini:
                mini = array[j]
                mini_index = j
        pom = array[i]
        array[i] = mini
        array[mini_index] = pom

selection_sort(lista)
print(lista)
