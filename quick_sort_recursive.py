import random
lista = []

for x in range(100):
    lista.append(random.randint(1, 100))
print(lista)


def partition(array, low, high):
    pivot = array[random.randint(0, len(array)-1)]
    i = low - 1
    for j in range(low, high):
        if array[j] <= pivot:
            i = i+1
            array[i], array[j] = array[j], array[i]
    array[i+1], array[high] = array[high], array[i + 1]
    return i+1


def quick_sort(array, p, r):
    if p < r:
        q = partition(array, p, r)
        quick_sort(array, p, q-1)
        quick_sort(array, q+1, r)


quick_sort(lista, 0, len(lista)-1)
print(lista)


