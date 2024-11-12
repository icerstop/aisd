# Selection i insertion obowiązkowo, merge sort quick sort(itteracyjnie i rekurencyjnie i heap sort
import random
lista = []

for x in range(15):
    lista.append(random.randint(1, 100))
print(lista)
# insertion sort


def insertion_sort(array):
    for j in range(1, len(array)):
        key = array[j]
        i = j-1
        while i >= 0 and array[i] > key:
            array[i + 1] = array[i]
            array[i] = key
            i = i - 1


insertion_sort(lista)
print(lista)