#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <locale.h>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;
using namespace std::chrono;

struct Node {
    int value;
    Node* next;
};

void addNode(Node** head, int value) {
    Node* newNode = new Node;
    newNode->value = value;
    newNode->next = *head;
    *head = newNode;
}

Node* createSortedLinkedList(int arr[], int n) {
    Node* head = NULL;
    for (int i = 0; i < n; i++) {
        Node* current = head;
        Node* previous = NULL;
        while (current != NULL && current->value < arr[i]) {
            previous = current;
            current = current->next;
        }
        if (previous == NULL) {
            addNode(&head, arr[i]);
        }
        else {
            Node* newNode = new Node;
            newNode->value = arr[i];
            newNode->next = current;
            previous->next = newNode;
        }
    }
    return head;
}

void searchList(Node* head, int arr[], int size) {
    Node* current = head; // Ustawienie wska�nika "current" na pocz�tek listy
    for (int i = 0; i < size; i++) { // Przechodzenie przez wszystkie elementy tablicy "arr"
        while (current != NULL) { // Przeszukiwanie listy od pocz�tku do ko�ca
            if (current->value == arr[i]) { // Sprawdzanie, czy warto�� w�z�a "current" zgadza si� z warto�ci� bie��cego elementu tablicy "arr"
                break; // Je�li tak, przerywamy p�tl� "while"
            }
            current = current->next; // Je�li nie, przechodzimy do nast�pnego w�z�a
        }
        current = head;  // Resetowanie wska�nika "current" na pocz�tek listy przed kolejnym przebiegiem p�tli "for"
    }
}

void deleteLinkedList(Node* head) {
    Node* current = head; // Ustawienie wska�nika "current" na pocz�tek listy
    Node* next;
    while (current != NULL) { // Wykonywanie p�tli od pocz�tku do ko�ca
        next = current->next; // Ustawienie wska�nika "next" na nast�pny element listy
        delete current; // Usuni�cie bie��cego w�z�a
        current = next; // Przesuni�cie wska�nika "current" na nast�pny w�ze�
    }
}

struct Tree {
    int key; // Warto�� w�z�a
    Tree* left; // Wska�nik na lewe poddrzewo
    Tree* right; // Wska�nik na prawe poddrzewo

    Tree(int value) { // Konstruktor
        key = value;
        left = right = NULL;
    }
};

Tree* insertBST(Tree* root, int value) {
    if (root == NULL) {
        return new Tree(value);
    }

    if (value < root->key) { // Je�li wstawiana warto�� jest mniejsza od korzenia, idziemy w lewe poddrzewo
        root->left = insertBST(root->left, value);
    }
    else { // Je�li wstawiana warto�� jest wi�ksza od korzenia, idziemy w prawe poddrzewo
        root->right = insertBST(root->right, value);
    }
    return root;
}

Tree* createBST(int arr[], int size) {
    if (size == 0) {
        return NULL;
    }

    Tree* root = NULL; // Pocz�tkowo puste drzewo

    for (int i = 0; i < size; i++) {
        root = insertBST(root, arr[i]);
    }
    return root;
}

void searchElement(Tree* root, int value) {
    if (root == NULL) { // Je�li korze� jest pusty
        return;
    }
    if (root->key == value) { // Je�li znaleziono szukan� warto��
        return;
    }
    if (value < root->key) {
        return searchElement(root->left, value); // Je�li szukana warto�� jest mniejsza od korzenia, id� w lewe poddrzewo
    }
    if (value > root->key) {
        return searchElement(root->right, value); // Je�li szukana warto�� jest wi�ksza od korzenia, id� w prawe poddrzewo
    }
}

void searchTree(Tree* root, int arr[], int n) {
    for (int i = 0; i < n; i++) {
        searchElement(root, arr[i]);
    }
}

void deleteTree(Tree* root) {
    if (root == NULL) { // Je�li korze� jest pusty
        return;
    }
    deleteTree(root->left); // Usu� lewe poddrzewo
    deleteTree(root->right); // Usu� prawe poddrzewo
    delete root; //Usu� obecny w�ze�
}

void inOrderTraversal(Tree* root, int* values, int& index) { // Wypisanie element�w drzewa w kolejno�ci inOrder
    if (root == NULL) { // Je�li korze� jest pusty
        return;
    }
    inOrderTraversal(root->left, values, index); // Najpierw lewe poddrzewo
    values[index++] = root->key; // Zapisujemy warto�� w�z�a w tablicy i zwi�kszamy indeks
    inOrderTraversal(root->right, values, index); // P�niej prawe poddrzewo
}

int getHeight(Tree* root) {
    if (root == NULL) {
        return 0;
    }
    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);
    return 1 + max(leftHeight, rightHeight);
}

Tree* constructAVL(int values[], int start, int end) {
    if (start > end) {
        return nullptr;
    }
    int mid = (start + end) / 2;
    Tree* root = new Tree(values[mid]);
    root->left = constructAVL(values, start, mid - 1);
    root->right = constructAVL(values, mid + 1, end);
    return root;
}

int main() {
    setlocale(LC_CTYPE, "Polish");
    srand(time(0));
    float time;
    int choice1;
    int choice2;
    int choice3;
    int samples;
    long double timeTotal1 = 0;
    long double timeTotal2 = 0;
    long double timeTotal3 = 0;
    long double timeTotal4 = 0;
    long double timeTotal5 = 0;
    long double timeTotal6 = 0;
    float bstHeightTotal = 0;
    float avlHeightTotal = 0;

    vector<int> numbers;
    int value;

    ifstream inputFile("numbers.txt");
    if (inputFile.is_open()) {
        while (inputFile >> value) {
            numbers.push_back(value);
        }
        inputFile.close();
    }
    else {
        cout << "Niemo�liwy odczyt pliku." << endl;
        return 1;
    }

    int fileSize = numbers.size();


    while (true) {
        system("cls");
        cout << "Algorytmy i Struktury Danych - sprawozdanie nr 2" << endl;
        cout << "------------------------------------------------" << endl;
        cout << "MENU G��WNE" << endl;
        cout << "1. Zadanie I" << endl;
        cout << "2. Zadanie II" << endl;
        cout << "3. Exit" << endl;
        cout << endl;
        cout << "Tw�j wyb�r: ";
        cin >> choice1;

        switch (choice1) {
        case 1:
            while (true) {
                system("cls");

                cout << "Algorytmy i Struktury Danych - sprawozdanie nr 2" << endl;
                cout << "------------------------------------------------" << endl;
                cout << "Zadanie I " << endl;
                cout << endl;
                cout << "Rodzaj danych wej�ciowych:" << endl;
                cout << "1. Losowe" << endl;
                cout << "2. Wczytywane z pliku" << endl;
                cout << "3. Powr�t" << endl;
                cout << endl;
                cout << "Tw�j wyb�r: ";
                cin >> choice2;

                switch (choice2) {
                case 1: //ZADANIE I - DANE LOSOWE
                    system("cls");
                    cout << "Algorytmy i Struktury Danych - sprawozdanie nr 2" << endl;
                    cout << "------------------------------------------------" << endl;
                    cout << "Zadanie I - dane losowe" << endl;
                    cout << endl;
                    cout << "Ile powt�rze� testu wykona�: ";
                    cin >> samples;
                    system("cls");
                    for (int size = 10000; size <= 150000; size += 10000) {
                        timeTotal1 = 0;
                        timeTotal2 = 0;
                        timeTotal3 = 0;
                        timeTotal4 = 0;
                        timeTotal5 = 0;
                        timeTotal6 = 0;
                        for (int i = 1; i <= samples; i++) {
                            int* arr = new int[size];
                            for (int i = 0; i < size; i++) {
                                arr[i] = i + 1;
                            }
                            random_shuffle(arr, arr + size);

                            auto start1 = high_resolution_clock::now();
                            Node* head = createSortedLinkedList(arr, size);
                            auto end1 = high_resolution_clock::now();
                            auto duration1 = duration_cast<nanoseconds>(end1 - start1);
                            timeTotal1 += duration1.count() / 1000000.0;
                            //cout << "Creating Sorted Linked List Time for " << size << " elements: " << time << " ms" << endl;

                            auto start2 = high_resolution_clock::now();
                            searchList(head, arr, size);
                            auto end2 = high_resolution_clock::now();
                            auto duration2 = duration_cast<nanoseconds>(end2 - start2);
                            timeTotal2 += duration2.count() / 1000000.0;

                            auto start3 = high_resolution_clock::now();
                            deleteLinkedList(head);
                            auto end3 = high_resolution_clock::now();
                            auto duration3 = duration_cast<nanoseconds>(end3 - start3);
                            timeTotal3 += duration3.count() / 1000000.0;

                            auto start4 = high_resolution_clock::now();
                            Tree* root = createBST(arr, size);
                            auto end4 = high_resolution_clock::now();
                            auto duration4 = duration_cast<nanoseconds>(end4 - start4);
                            timeTotal4 += duration4.count() / 1000000.0;

                            auto start5 = high_resolution_clock::now();
                            searchTree(root, arr, size);
                            auto end5 = high_resolution_clock::now();
                            auto duration5 = duration_cast<nanoseconds>(end5 - start5);
                            timeTotal5 += duration5.count() / 1000000.0;

                            auto start6 = high_resolution_clock::now();
                            deleteTree(root);
                            auto end6 = high_resolution_clock::now();
                            auto duration6 = duration_cast<nanoseconds>(end6 - start6);
                            timeTotal6 += duration6.count() / 1000000.0;

                            delete[] arr;

                        }
                        cout << "�redni czas tworzenia posortowanej listy jednokierunkowej z " << size << " element�w: " << fixed << setprecision(15) << (timeTotal1 / samples) << " ms" << endl;
                        cout << "�redni czas przeszukiwania posortowanej listy jednokierunkowej z " << size << " element�w: " << fixed << setprecision(15) << (timeTotal2 / samples) << " ms" << endl;
                        cout << "�redni czas usuwania posortowanej listy jednokierunkowej z " << size << " element�w: " << fixed << setprecision(15) << (timeTotal3 / samples) << " ms" << endl;
                        cout << "�redni czas tworzenia drzewa BST z " << size << " element�w: " << fixed << setprecision(15) << (timeTotal4 / samples) << " ms" << endl;
                        cout << "�redni czas przeszukiwania drzewa BST z " << size << " element�w: " << fixed << setprecision(15) << (timeTotal5 / samples) << " ms" << endl;
                        cout << "�redni czas usuwania drzewa BST z " << size << " element�w: " << fixed << setprecision(15) << (timeTotal6 / samples) << " ms" << endl;
                        cout << endl;
                    }
                    timeTotal1 = 0;
                    timeTotal2 = 0;
                    timeTotal3 = 0;
                    timeTotal4 = 0;
                    timeTotal5 = 0;
                    timeTotal6 = 0;
                    cout << "Naci�nij enter, aby kontynuowa�..." << endl;
                    cin.ignore(); // ignorujemy wcze�niej wprowadzone dane, aby m�c nacisn�� enter
                    cin.get(); // oczekujemy na naci�ni�cie enter
                    system("cls");
                    break;
                case 2: { //ZADANIE I - DANE WCZYTYWANE
                    timeTotal1 = 0;
                    timeTotal2 = 0;
                    timeTotal3 = 0;
                    timeTotal4 = 0;
                    timeTotal5 = 0;
                    timeTotal6 = 0;
                    system("cls");
                    cout << "Algorytmy i Struktury Danych - sprawozdanie nr 2" << endl;
                    cout << "------------------------------------------------" << endl;
                    cout << "Zadanie I - dane wczytywane z pliku" << endl;
                    cout << endl;
                    int* arr = new int[fileSize];
                    for (int i = 0; i < fileSize; i++) {
                        arr[i] = numbers[i];
                    }
                    auto start12 = high_resolution_clock::now();
                    Node* head = createSortedLinkedList(arr, fileSize);
                    auto end12 = high_resolution_clock::now();
                    auto duration12 = duration_cast<nanoseconds>(end12 - start12);
                    timeTotal1 += duration12.count() / 1000000.0;
                    //cout << "Creating Sorted Linked List Time for " << size << " elements: " << time << " ms" << endl;

                    auto start13 = high_resolution_clock::now();
                    searchList(head, arr, fileSize);
                    auto end13 = high_resolution_clock::now();
                    auto duration13 = duration_cast<nanoseconds>(end13 - start13);
                    timeTotal2 += duration13.count() / 1000000.0;

                    auto start14 = high_resolution_clock::now();
                    deleteLinkedList(head);
                    auto end14 = high_resolution_clock::now();
                    auto duration14 = duration_cast<nanoseconds>(end14 - start14);
                    timeTotal3 += duration14.count() / 1000000.0;

                    auto start15 = high_resolution_clock::now();
                    Tree* root = createBST(arr, fileSize);
                    auto end15 = high_resolution_clock::now();
                    auto duration15 = duration_cast<nanoseconds>(end15 - start15);
                    timeTotal4 += duration15.count() / 1000000.0;

                    auto start16 = high_resolution_clock::now();
                    searchTree(root, arr, fileSize);
                    auto end16 = high_resolution_clock::now();
                    auto duration16 = duration_cast<nanoseconds>(end16 - start16);
                    timeTotal5 += duration16.count() / 1000000.0;

                    auto start17 = high_resolution_clock::now();
                    deleteTree(root);
                    auto end17 = high_resolution_clock::now();
                    auto duration17 = duration_cast<nanoseconds>(end17 - start17);
                    timeTotal6 += duration17.count() / 1000000.0;

                    delete[] arr;

                    cout << "�redni czas tworzenia posortowanej listy jednokierunkowej z " << fileSize << " element�w: " << fixed << setprecision(15) << timeTotal1 << " ms" << endl;
                    cout << "�redni czas przeszukiwania posortowanej listy jednokierunkowej z " << fileSize << " element�w: " << fixed << setprecision(15) << timeTotal2 << " ms" << endl;
                    cout << "�redni czas usuwania posortowanej listy jednokierunkowej z " << fileSize << " element�w: " << fixed << setprecision(15) << timeTotal3 << " ms" << endl;
                    cout << "�redni czas tworzenia drzewa BST z " << fileSize << " element�w: " << fixed << setprecision(15) << timeTotal4 << " ms" << endl;
                    cout << "�redni czas przeszukiwania drzewa BST z " << fileSize << " element�w: " << fixed << setprecision(15) << timeTotal5 << " ms" << endl;
                    cout << "�redni czas usuwania drzewa BST z " << fileSize << " element�w: " << fixed << setprecision(15) << timeTotal6 << " ms" << endl;
                    cout << endl;
                    timeTotal1 = 0;
                    timeTotal2 = 0;
                    timeTotal3 = 0;
                    timeTotal4 = 0;
                    timeTotal5 = 0;
                    timeTotal6 = 0;
                    cout << "Naci�nij enter, aby kontynuowa�..." << endl;
                    cin.ignore(); // ignorujemy wcze�niej wprowadzone dane, aby m�c nacisn�� enter
                    cin.get(); // oczekujemy na naci�ni�cie enter
                    break;
                }
                case 3:
                    system("cls");
                    goto end_switch1;
                    break;
                default:
                    cout << endl;
                    cout << "Nieprawidlowy numer opcji. Sprobuj ponownie." << endl;
                    system("pause");
                    break;
                }
            }
        end_switch1:
            break;
        case 2:
            while (true) {
                system("cls");

                cout << "Algorytmy i Struktury Danych - sprawozdanie nr 2" << endl;
                cout << "------------------------------------------------" << endl;
                cout << "Zadanie II " << endl;
                cout << endl;
                cout << "Rodzaj danych wej�ciowych:" << endl;
                cout << "1. Losowe" << endl;
                cout << "2. Wczytywane z pliku" << endl;
                cout << "3. Powr�t" << endl;
                cout << endl;
                cout << "Tw�j wyb�r: ";
                cin >> choice2;

                switch (choice2) {
                case 1: //ZADANIE II - DANE LOSOWE
                {
                    system("cls");
                    cout << "Algorytmy i Struktury Danych - sprawozdanie nr 2" << endl;
                    cout << "------------------------------------------------" << endl;
                    cout << "Zadanie II - dane losowe" << endl;
                    cout << endl;
                    cout << "Ile powt�rze� testu wykona�: ";
                    cin >> samples;
                    system("cls");
                    for (int size = 10000; size <= 150000; size += 10000) {
                        bstHeightTotal = 0;
                        avlHeightTotal = 0;
                        timeTotal1 = 0;
                        timeTotal2 = 0;
                        timeTotal3 = 0;
                        timeTotal4 = 0;
                        timeTotal5 = 0;
                        timeTotal6 = 0;
                        for (int i = 1; i <= samples; i++) {
                            int* arr = new int[size];
                            for (int i = 0; i < size; i++) {
                                arr[i] = i + 1;
                            }
                            random_shuffle(arr, arr + size);

                            auto start7 = high_resolution_clock::now();
                            Tree* bstRoot = createBST(arr, size);
                            auto end7 = high_resolution_clock::now();
                            auto duration7 = duration_cast<nanoseconds>(end7 - start7);
                            timeTotal1 += duration7.count() / 1000000.0;

                            int* inOrder = new int[size];
                            int index = 0;
                            void(*inorder)(Tree*, int*, int&) = inOrderTraversal;
                            inorder(bstRoot, inOrder, index);

                            auto start8 = high_resolution_clock::now();
                            Tree* avlRoot = constructAVL(inOrder, 0, size - 1);
                            auto end8 = high_resolution_clock::now();
                            auto duration8 = duration_cast<nanoseconds>(end8 - start8);
                            time = duration8.count() / 1000000.0;

                            bstHeightTotal += getHeight(bstRoot);
                            avlHeightTotal += getHeight(avlRoot);

                            delete[] arr;
                            delete[] inOrder;

                            deleteTree(bstRoot);
                            deleteTree(avlRoot);
                        }
                        float bstAvgHeight = bstHeightTotal / samples;
                        float avlAvgHeight = avlHeightTotal / samples;
                        cout << endl;
                        cout << "BST average height for " << size << " elements: " << bstAvgHeight << endl;
                        cout << "AVL average height for " << size << " elements: " << avlAvgHeight << endl;
                    }
                    cout << "Naci�nij enter, aby spr�bowa� ponownie..." << endl;
                    cin.ignore(); // ignorujemy wcze�niej wprowadzone dane, aby m�c nacisn�� enter
                    cin.get(); // oczekujemy na naci�ni�cie enter
                    system("cls");
                    timeTotal1 = 0;
                    timeTotal2 = 0;
                    timeTotal3 = 0;
                    timeTotal4 = 0;
                    timeTotal5 = 0;
                    timeTotal6 = 0;
                    break;
                }
                case 2: {//ZADANIE II - DANE WCZYTYWANE
                    system("cls");
                    bstHeightTotal = 0;
                    avlHeightTotal = 0;
                    cout << "Algorytmy i Struktury Danych - sprawozdanie nr 2" << endl;
                    cout << "------------------------------------------------" << endl;
                    cout << "Zadanie II - dane wczytywane z pliku" << endl;
                    cout << endl;

                    int* fileArr = new int[fileSize];
                    for (int i = 0; i < fileSize; i++) {
                        fileArr[i] = numbers[i];
                    }

                    auto start10 = high_resolution_clock::now();
                    Tree* bstRoot = createBST(fileArr, fileSize);
                    auto end10 = high_resolution_clock::now();
                    auto duration10 = duration_cast<nanoseconds>(end10 - start10);
                    timeTotal1 += duration10.count() / 1000000.0;

                    int* inOrder = new int[fileSize];
                    int index = 0;
                    void(*inorder)(Tree*, int*, int&) = inOrderTraversal;
                    inorder(bstRoot, inOrder, index);

                    auto start11 = high_resolution_clock::now();
                    Tree* avlRoot = constructAVL(inOrder, 0, fileSize - 1);
                    auto end11 = high_resolution_clock::now();
                    auto duration11 = duration_cast<nanoseconds>(end11 - start11);
                    time = duration11.count() / 1000000.0;

                    bstHeightTotal += getHeight(bstRoot);
                    avlHeightTotal += getHeight(avlRoot);
                    system("cls");
                    cout << "BST average height for " << fileSize << " elements: " << bstHeightTotal << endl;
                    cout << "AVL average height for " << fileSize << " elements: " << avlHeightTotal << endl;
                    cout << endl;
                    cout << "Naci�nij enter, aby kontynuowa�..." << endl;
                    cin.ignore(); // ignorujemy wcze�niej wprowadzone dane, aby m�c nacisn�� enter
                    cin.get(); // oczekujemy na naci�ni�cie enter
                    break;
                }
                case 3: {
                    goto end_switch2;
                    break;
                }
                default: {
                    cout << "Nieprawidlowy numer opcji. Sprobuj ponownie." << endl;
                    cout << "Naci�nij enter, aby kontynuowa�..." << endl;
                    cin.ignore(); // ignorujemy wcze�niej wprowadzone dane, aby m�c nacisn�� enter
                    cin.get();
                    break;
                }
                }
            }
        end_switch2:
            break;
        case 3:
            return 0;
        default:
            cout << endl;
            cout << "Nieprawidlowy numer opcji. Sprobuj ponownie." << endl;
            system("pause");
            break;
        }
    }
}

