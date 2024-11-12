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

void addNode(Node*& head, int data) { //dodawanie nowego elementu na pocz¹tek listy
	Node* newNode = new Node; //tworzenie nowego wêz³¹
	newNode->data = data; //przypisanie wartoœci
	newNode->next = head; //nowy wêze³ staje siê pierwszym elementem
	head = newNode; //przypisanie nowej g³owy
}

Node* createSortedLinkedList(int arr[], int n) { //tworzenie posortowanej listy 1-kierunkowej z tablicy nieposortowanej
	Node* head = NULL; //pocz¹tkowo lista pusta
	for (int i = 0; i < n; i++) { //szukanie odpowiedniego miejsca dla arr[i]
		Node* current = head;
		Node* previous = NULL;
		while (current != NULL && current->data < arr[i]) { //wykonujemy pêtle while dopóki wskaŸnik 'current' nie wskazuje na NULL i nie znajdzie elementu mniejszego od siebie
			previous = current;
			current = current->next;
		}
		if (previous == NULL) { // wstawianie na pocz¹tek
			addNode(head, arr[i]);
		}
		else { //wstawianie na koniec lub w œrodek listy
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

void deleteLinkedList(Node* head) { //usuwanie listy jednokierunkowej od pocz¹tku
	Node* current = head; //ustawienie wskaŸnika 'current' na g³owê listy
	while (current != NULL) { //pêtla wykonuje siê dopóki wskaŸnik 'current' nie wskazuje na NULL
		Node* next = current->next; //ustawiamy wskaŸnik 'next' na nastêpny element listy
		delete current; //usuwamy bie¿¹cy element listy
		current = next; //przesuwamy wskaŸnik 'current' na nastêpny element
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
	if (root == NULL) { //jeœli korzeñ jest pusty
		return;
	}
	if (root->data == value) {
		return; //jeœli znaleziono szukan¹ wartoœæ
	}
	if (value < root->data) {
		return searchElement(root->left, value); //jeœli szukana wartoœæ mniejsza od korzenia, idziemy w lewo
	}
	if (value > root->data) {
		return searchElement(root->right, value); //jeœli szukana wartoœæ wiêksza od korzenia, idziemy w prawo
	}
}

void searchTree(Tree* root, int arr[], int n) {
	for (int i = 0; i < n; i++) {
		searchElement(root, arr[i]);
	}
}

void deleteTree(Tree* root) {
	if (root == NULL) { //jeœli korzeñ jest pusty
		return;
	}
	deleteTree(root->left); //usuñ lewe poddrzewo
	deleteTree(root->right); //usuñ prawe poddrzewo
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