#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Trie node structure
struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE]; // Array to hold pointers to child nodes
    int count; // To store the count of occurrences of the word
};

// Trie structure
struct Trie {
    struct TrieNode *root;
};

// Function prototypes
struct TrieNode *createNode(void);
struct Trie *createTrie(void);
void insert(struct Trie *trie, char *word);
int numberOfOccurrences(struct Trie *trie, char *word);
void deallocateTrie(struct Trie *trie);
void deallocateNode(struct TrieNode *node); // Correct place for the prototype

// Function to initialize a Trie node
struct TrieNode *createNode() {
    struct TrieNode *node = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    if (node) {
        node->count = 0; // Initialize count to 0
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            node->children[i] = NULL; // Initialize all children to NULL
        }
    }
    return node;
}

// Function to initialize a trie structure
struct Trie *createTrie() {
    struct Trie *trie = (struct Trie *)malloc(sizeof(struct Trie));
    if (trie) {
        trie->root = createNode(); // Create the root node
    }
    return trie;
}

// Function to insert a word into the trie
void insert(struct Trie *trie, char *word) {
    struct TrieNode *current = trie->root;
    int index;

    for (int i = 0; i < strlen(word); i++) {
        index = word[i] - 'a'; // Calculate the index of the child node
        if (!current->children[index]) {
            current->children[index] = createNode(); // Create a new node if it doesn't exist
        }
        current = current->children[index]; // Move to the child node
    }
    current->count++; // Increment count of occurrences
}

// Function to compute the number of occurrences of a word in the trie
int numberOfOccurrences(struct Trie *trie, char *word) {
    struct TrieNode *current = trie->root;
    int index;

    for (int i = 0; i < strlen(word); i++) {
        index = word[i] - 'a'; // Calculate the index of the child node
        if (!current->children[index]) {
            return 0; // Word not found
        }
        current = current->children[index]; // Move to the child node
    }
    return current->count; // Return the count of occurrences
}

// Function to deallocate a trie structure
void deallocateTrie(struct Trie *trie) {
    deallocateNode(trie->root); // Recursively deallocate nodes starting from the root
    free(trie); // Free the trie structure
}

// Recursive function to deallocate nodes
void deallocateNode(struct TrieNode *node) {
    if (node) {
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (node->children[i]) {
                deallocateNode(node->children[i]); // Recursively deallocate child nodes
            }
        }
        free(node); // Free memory allocated for the current node
    }
}

// Function to read words from a file and store them in an array
int readDictionary(char *filename, char **pInWords) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file %s\n", filename);
        exit(1);
    }

    int count = 0;
    char word[100];

    while (fscanf(file, "%s", word) != EOF) { // Read words from file
        pInWords[count] = strdup(word); // Store each word in the array
        count++;
    }

    fclose(file);
    return count; // Return the number of words read
}

int main(void) {
    char *inWords[256];

    int numWords = readDictionary("dictionary.txt", inWords); // Read words into inWords array
    struct Trie *trie = createTrie(); // Create a trie

    for (int i = 0; i < numWords; i++) {
        insert(trie, inWords[i]); // Insert each word into the trie
    }

    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++) {
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(trie, pWords[i])); // Print the count of occurrences for each word
    }

    deallocateTrie(trie); // Deallocate the trie

    return 0;
}
