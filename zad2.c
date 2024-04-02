#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    int size;
} List;

void initialiseList(List *list) {
    list->head = NULL;
    list->size = 0;
}

void insert(List *list, int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = value;

    if (list->head == NULL) {
        list->head = newNode;
        newNode->next = newNode; 
    } else {
        Node *current = list->head;
        while (current->next != list->head) {
            current = current->next;
        }
        current->next = newNode;
        newNode->next = list->head;
    }
    list->size++;
}

List merge(List list1, List list2) {
	if (list1.size==0)
        return list2;
 
    if (list2.size==0)
        return list1;
    List mergedList;
    initialiseList(&mergedList);

    Node *current1 = list1.head;
    Node *current2 = list2.head;

    // Wstawienie elementów z listy 1 do scalonej listy
    do {
        insert(&mergedList, current1->data);
        current1 = current1->next;
    } while (current1 != list1.head);

    // Wstawienie elementów z listy 2 do scalonej listy
    do {
        insert(&mergedList, current2->data);
        current2 = current2->next;
    } while (current2 != list2.head);

    return mergedList;
}

void displayList(List *list) {
    if (list->head == NULL) {
        printf("List is empty\n");
        return;
    }
    int i=2;
    Node *current = list->head;
    do {
        printf("%d ", current->data);
        current = current->next;
    } while (current != list->head);
    printf("\n");
}

int search(List *list, int key) {
    int comparisons = 0;
    if (list->head == NULL) {
        return comparisons;
    }

    Node *current = list->head;
    do {
        comparisons++;
        if (current->data == key) {
            return comparisons;
        }
        current = current->next;
    } while (current != list->head);

    return comparisons;
}

int main() {
	srand(time(NULL));
    List list1, list2;
    initialiseList(&list1);
    initialiseList(&list2);
    List L3;
    initialiseList(&L3);

    for (int i = 10; i <= 100; i += 10) {
        insert(&list1, i);
    }

    for (int i = 15; i <= 150; i += 15) {
        insert(&list2, i);
    }

    printf("Lista l1: ");
    displayList(&list1);

    printf("Lista l2: ");
    displayList(&list2);

    List merged = merge(list1, list2);

    printf("Po scaleniu: ");
    displayList(&merged);

    int T[10000];
    for (int i = 0; i < 10000; i++) {
        T[i] = rand() % 100001; 
        insert(&L3, T[i]);
    }

    int totalComparisons1 = 0;
    int totalComparisons2 = 0;
    for (int i = 0; i < 1000; i++) {
        int randomIndex1 = rand() % 10000;
        int randomIndex2 = rand() % 100001; 

        int key1 = T[randomIndex1];

        totalComparisons1 += search(&L3, key1);
        totalComparisons2 += search(&L3, randomIndex2);

    }
    double averageCost1 = (double)totalComparisons1 / 1000;
    double averageCost2 = (double)totalComparisons2 / 1000;

    printf("Średni koszt tysiąca wyszukiwań losowych liczb z tablicy T na liście L: %.2lf\n", averageCost1);
    printf("Średni koszt tysiąca wyszukiwań losowych liczb : %.2lf\n", averageCost2);

    return 0;
}
