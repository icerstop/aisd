import random
lista = []

for x in range(15):
    lista.append(random.randint(1, 100))
print(lista)


def partition(array, low, high):
    pivot = array[high]
    i = low - 1
    for j in range(low, high):
        if array[j] <= pivot:
            i = i+1
            array[i], array[j] = array[j], array[i]
    array[i+1], array[high] = array[high], array[i + 1]
    return i+1


def iteration_quick_sort(array, low, high):
    size = high - low + 1
    stack = [0] * size

    top = 0
    stack[top] = low
    top = top+1
    stack[top] = high

    while top >= 0:
        pass