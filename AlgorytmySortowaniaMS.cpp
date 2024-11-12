#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <fstream>
#include <ctime>

using namespace std;

void NumGenerator(int nums[] /* tablica do liczb */, int size /* dlugosc tablicy */, char dtype /*rodzaj danych*/)
{
    int maxint = size * 10;
    for (int i = 0; i < size; i++)
        nums[i] = rand() % maxint + 1;
    switch (dtype)
    {
    case 'r': // losowe dane
        break;
    case 'u': // dane rosnace
        sort(nums, nums + size);
        break;
    case 'd': // dane malejace
        sort(nums, nums + size, greater<int>());
        break;
    case 'v': // dane v-ksztalne
        sort(nums, nums + size / 2, greater<int>());
        sort(nums + size / 2, nums + size);
        break;
    case 'a': // dane a-ksztaltne
        sort(nums, nums + size / 2);
        sort(nums + size / 2, nums + size, greater<int>());
        break;

    }
}

// algorytmy naiwne

void BubbleSort(int tab[], int size)
{
    for (int i = 0; i < size; i++)
        for (int j = 1; j < size - i; j++)
            if (tab[j - 1] > tab[j])
                swap(tab[j - 1], tab[j]);
}

void SelectionSort(int tab[], int size)
{
    int minnum;
    for (int i = 0; i < size - 1; i++)
    {
        minnum = i;
        for (int j = i + 1; j < size; j++)
            if (tab[j] < tab[minnum])
                minnum = j;
        swap(tab[i], tab[minnum]);
    }
}

// algorytmy d&c

void QuickSort(int tab[], int left, int right)
{
    int i = left - 1;
    int j = right + 1;
    int x = tab[(left + right) / 2];
    while (i <= j)
    {
        while (x > tab[++i]);
        while (x < tab[--j]);
        if (i <= j)
        {
            swap(tab[i], tab[j]);
        }
        else
            break;
    }
    if (j > left)
        QuickSort(tab, left, j);
    if (i < right)
        QuickSort(tab, i, right);
}

void Heapify(int tab[], int size, int i)
{
    int MAX = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < size && tab[left] > tab[MAX])
        MAX = left;
    if (right < size && tab[right] > tab[MAX])
        MAX = right;
    if (MAX != i)
    {
        swap(tab[i], tab[MAX]);
        Heapify(tab, size, MAX);
    }
}

void HeapSort(int tab[], int size)
{
    for (int i = size / 2 - 1; i >= 0; i--)
        Heapify(tab, size, i);
    for (int i = size - 1; i > 0; i--)
    {
        swap(tab[0], tab[i]);
        Heapify(tab, i, 0);
    }
}

// algorytmy inne

void ShellSort(int tab[], int size)
{
    for (int k = size / 2; k > 0; k /= 2)
        for (int i = k; i < size; i++)
        {
            int temp = tab[i];
            int j;
            for (j = i; (j >= k) && (tab[j - k] > temp); j -= k)
                tab[j] = tab[j - k];
            tab[j] = temp;
        }
}

main()
{
    fstream out;
    out.open("output.txt", ios::out);
    srand(time(0));
    int sizearr[10] = { 1000, 3000, 5000, 10000, 20000, 40000, 50000, 70000, 80000, 85000 };
    char datatypes[5] = { 'r', 'u', 'd', 'a', 'v' };
    clock_t begin, end;

    for (int j = 0; j < 5; j++)
    {
        out << "\nDla danych ";
        switch (datatypes[j])
        {
        case 'r':
            out << "losowych:\n";
            break;
        case 'u':
            out << "rosnacych:\n";
            break;
        case 'd':
            out << "malejacych:\n";
            break;
        case 'v':
            out << "v-ksztaltnych\n";
            break;
        case 'a':
            out << "a-ksztaltnych\n";
            break;
        }
        for (int i = 0; i < 10; i++)
        {
            int tab[sizearr[i]];

            int tab1[sizearr[i]];
            int tab2[sizearr[i]];
            int tab3[sizearr[i]];
            int tab4[sizearr[i]];
            int tab5[sizearr[i]];

            out << "\nDla danych o dlugosci " << sizearr[i] << " elementow, algorytmy wykonuja sie: \n";

            NumGenerator(tab, sizearr[i], datatypes[j]);
            for (int n = 0; n < sizearr[i]; n++)
            {
                tab1[n] = tab[n];
                tab2[n] = tab[n];
                tab3[n] = tab[n];
                tab4[n] = tab[n];
                tab5[n] = tab[n];
            }
            begin = clock();
            BubbleSort(tab1, sizearr[i]);
            end = clock();

            out << "Sortowanie babelkowe: " << fixed << double(end - begin) / double(CLOCKS_PER_SEC) << setprecision(5) << " sekund" << endl;

            begin = clock();
            SelectionSort(tab2, sizearr[i]);
            end = clock();

            out << "Sortowanie przez wybieranie: " << fixed << double(end - begin) / double(CLOCKS_PER_SEC) << setprecision(5) << " sekund" << endl;

            begin = clock();
            QuickSort(tab3, 0, sizearr[i] - 1);
            end = clock();

            out << "Sortowanie szybkie: " << fixed << double(end - begin) / double(CLOCKS_PER_SEC) << setprecision(5) << " sekund" << endl;

            begin = clock();
            HeapSort(tab4, sizearr[i]);
            end = clock();

            out << "Sortowanie stogowe: " << fixed << double(end - begin) / double(CLOCKS_PER_SEC) << setprecision(5) << " sekund" << endl;

            begin = clock();
            ShellSort(tab5, sizearr[i]);
            end = clock();

            out << "Sortowanie za pomoca malejacych przyrostow: " << fixed << double(end - begin) / double(CLOCKS_PER_SEC) << setprecision(5) << " sekund" << endl;
        }
    }
    out.close();
    cout << "Koniec.";
}