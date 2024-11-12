import random
import time

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
def merge_sort(array):
    if len(array) > 1:
        mid = len(array) // 2
        left = array[:mid]
        right = array[mid:]

        merge_sort(left)
        merge_sort(right)
        i = j = k = 0
        while i < len(left) and j < len(right):
            if left[i] < right[j]:
                array[k] = left[i]
                i += 1
            else:
                array[k] = right[j]
                j += 1
            k += 1
        while i < len(left):
            array[k] = left[i]
            i += 1
            k += 1
        while j < len(right):
            array[k] = right[j]
            j += 1
            k += 1
def heapify(array, n, i):
    largest = i
    left = 2*i + 1
    right = 2*i + 2
    if left < n and array[largest] < array[left]:
        largest = left
    if right < n and array[largest] < array[right]:
        largest = right
    if largest != i:
        array[i], array[largest] = array[largest], array[i]
        heapify(array, n, largest)
def heapsort(array):
    n = len(array)
    for i in range(n//2-1, -1, -1):
        heapify(array, n, i)
    for i in range(n-1, 0, -1):
        array[i], array[0] = array[0], array[i]
        heapify(array, i, 0)
def insertion_sort(array):
    for j in range(1, len(array)):
        key = array[j]
        i = j-1
        while i >= 0 and array[i] > key:
            array[i + 1] = array[i]
            array[i] = key
            i = i - 1
def partition(array, low, high):
    pivot = array[high]
    i = low - 1
    for j in range(low, high):
        if array[j] <= pivot:
            i = i+1
            array[i], array[j] = array[j], array[i]
    array[i+1], array[high] = array[high], array[i + 1]
    return i+1
def quick_sort_recursive(array, low, high):
    if low < high:
        q = partition(array, low, high)
        quick_sort_recursive(array, low, q - 1)
        quick_sort_recursive(array, q + 1, high)
def quick_sort_iterative(array, low, high):
    size = high
    stack = [0]*size
    top = -1

    top += 1
    stack[top] = low
    top += 1
    stack[top] = high

    while top >= 0:

        high = stack[top]
        top = top-1
        low = stack[top]
        top -= 1

        p = partition(array, low, high)
        if p-1 > low:
            top = top + 1
            stack[top] = low
            top = top + 1
            stack[top] = p - 1
        if p + 1 < high:
            top = top + 1
            stack[top] = p + 1
            top = top + 1
            stack[top] = high



def random_array(length):
    lista = []
    for x in range(length):
        lista.append(random.randint(0, length))
    return lista
def increasing_array(length):
    lista = []
    for x in range(length):
        lista.append(x)
    return lista
def decreasing_array(length):
    lista = []
    for x in range(length, 0, -1):
        lista.append(x)
    return lista
def one_number_array(length):
    lista = []
    n = random.randint(0, length)
    for x in range(length):
        lista.append(n)
    return lista


lista = random_array(1000000)
# print(lista)
start = time.time()
quick_sort_iterative(lista, 0, len(lista)-1)
end = time.time()
# print(lista)
print(end-start)
lista2 = random_array(1000000)
# print(lista2)
start = time.time()
quick_sort_recursive(lista2, 0, len(lista2)-1)
end = time.time()
print(end-start)
#print(lista2)