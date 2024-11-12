#include <iostream>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace std::chrono;

struct Node {
	int data;
	Node* next;
};

struct Tree {
	int data;
	Tree* left;
	Tree* right;

	Tree(int value) {
		data = value;
		left = right = NULL;
	}
};

void addNode(Node*& head, int data) { //dodawanie nowego elementu na pocz�tek listy
	Node* newNode = new Node; //tworzenie nowego w�z��
	newNode->data = data; //przypisanie warto�ci
	newNode->next = head; //nowy w�ze� staje si� pierwszym elementem
	head = newNode; //przypisanie nowej g�owy
}

Node* createSortedLinkedList(int arr[], int n) { //tworzenie posortowanej listy 1-kierunkowej z tablicy nieposortowanej
	Node* head = NULL; //pocz�tkowo lista pusta
	for (int i = 0; i < n; i++) { //szukanie odpowiedniego miejsca dla arr[i]
		Node* current = head;
		Node* previous = NULL;
		while (current != NULL && current->data < arr[i]) { //wykonujemy p�tle while dop�ki wska�nik 'current' nie wskazuje na NULL i nie znajdzie elementu mniejszego od siebie
			previous = current;
			current = current->next;
		}
		if (previous == NULL) { // wstawianie na pocz�tek
			addNode(head, arr[i]);
		}
		else { //wstawianie na koniec lub w �rodek listy
			Node* newNode = new Node;
			newNode->data = arr[i];
			newNode->next = current;
			previous->next = newNode;
		}
	}
	return head;
}

void searchList(Node* head, int arr[], int size) {
	Node* curr = head;
	for (int i = 0; i < size; i++) {
		while (curr != NULL) {
			if (curr->data == arr[i]) {
				break;
			}
			curr = curr->next;
		}
		curr = head;
	}
}

void deleteLinkedList(Node* head) { //usuwanie listy jednokierunkowej od pocz�tku
	Node* current = head; //ustawienie wska�nika 'current' na g�ow� listy
	while (current != NULL) { //p�tla wykonuje si� dop�ki wska�nik 'current' nie wskazuje na NULL
		Node* next = current->next; //ustawiamy wska�nik 'next' na nast�pny element listy
		delete current; //usuwamy bie��cy element listy
		current = next; //przesuwamy wska�nik 'current' na nast�pny element
	}
}

Tree* insertBST(Tree* root, int val) {
	if (!root) {
		return new Tree(val);
	}

	if (val < root->data) {
		root->left = insertBST(root->left, val);
	}
	else {
		root->right = insertBST(root->right, val);
	}

	return root;
}

Tree* createBST(int arr[], int size) {
	if (size == 0) {
		return NULL;
	}

	Tree* root = NULL;

	for (int i = 0; i < size; i++) {
		root = insertBST(root, arr[i]);
	}

	return root;
}

void searchElement(Tree* root, int value) {
	if (root == NULL) { //je�li korze� jest pusty
		return;
	}
	if (root->data == value) {
		return; //je�li znaleziono szukan� warto��
	}
	if (value < root->data) {
		return searchElement(root->left, value); //je�li szukana warto�� mniejsza od korzenia, idziemy w lewo
	}
	if (value > root->data) {
		return searchElement(root->right, value); //je�li szukana warto�� wi�ksza od korzenia, idziemy w prawo
	}
}

void searchTree(Tree* root, int arr[], int n) {
	for (int i = 0; i < n; i++) {
		searchElement(root, arr[i]);
	}
}

void deleteTree(Tree* root) {
	if (root == NULL) { //je�li korze� jest pusty
		return;
	}
	deleteTree(root->left); //usu� lewe poddrzewo
	deleteTree(root->right); //usu� prawe poddrzewo
	delete root;
}

int main() {
	const int size = 140000;
	int arr[size];
	srand(time(0));
	for (int i = 0; i < size; i++) {
		arr[i] = i + 1;
	}
	random_shuffle(arr, arr + size);
	float time;

	auto start1 = high_resolution_clock::now();
	Node* head = createSortedLinkedList(arr, size);
	auto end1 = high_resolution_clock::now();
	auto duration1 = duration_cast<nanoseconds>(end1 - start1);
	time = duration1.count() / 1000000.0;
	cout << "Creating Sorted Linked List Time: " << time << " ms" << endl;

	auto start2 = high_resolution_clock::now();
	searchList(head, arr, size);
	auto end2 = high_resolution_clock::now();
	auto duration2 = duration_cast<nanoseconds>(end2 - start2);
	time = duration2.count() / 1000000.0;
	cout << "Searching Linked List Time: " << time << " ms" << endl;

	auto start3 = high_resolution_clock::now();
	deleteLinkedList(head);
	auto end3 = high_resolution_clock::now();
	auto duration3 = duration_cast<nanoseconds>(end3 - start3);
	time = duration3.count()/1000000.0;
	cout << "Deleting Linked List Time: " << time << " ms" << endl;

	cout << endl;

	auto start4 = high_resolution_clock::now();
	Tree* root = createBST(arr, size);
	auto end4 = high_resolution_clock::now();
	auto duration4 = duration_cast<nanoseconds>(end4 - start4);
	time = duration4.count() / 1000000.0;
	cout << "Creating BST Time: " << time << " ms" << endl;

	auto start5 = high_resolution_clock::now();
	searchTree(root, arr, size);
	auto end5 = high_resolution_clock::now();
	auto duration5 = duration_cast<nanoseconds>(end5 - start5);
	time = duration5.count() / 1000000.0;
	cout << "Searching BST Time: " << time << " ms" << endl;

	auto start6 = high_resolution_clock::now();
	deleteTree(root);
	auto end6 = high_resolution_clock::now();
	auto duration6 = duration_cast<nanoseconds>(end6 - start6);
	time = duration6.count() / 1000000.0;
	cout << "Deleting BST Time: " << time << " ms" << endl;

	return 0;
}