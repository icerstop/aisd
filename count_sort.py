import random
lista1 = []

for x in range(15):
    lista1.append(random.randint(1, 10))
print(lista1)
maxi = lista1[0]
for i in range(1, len(lista1)):
    if maxi < lista1[i]:
        maxi = lista1[i]
count_list = [0]*(maxi+1)
for i in range(len(lista1)):
    count_list[lista1[i]] += 1
print(count_list)
for i in range(1, len(count_list)):
    count_list[i] += count_list[i-1]
print(count_list)
final_list = [0] * (len(lista1)+1)
for i in range(len(lista1)-1, -1, -1):
    final_list[count_list[lista1[i]]] = lista1[i]
    count_list[lista1[i]] -= 1
final_list.remove(0)
print(final_list)