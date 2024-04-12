#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
    int    id;
    char   name;
    int    order; 
};

// Node for chaining
struct Node
{
    struct RecordType data;
    struct Node* next;
};

// HashType with separate chaining
struct HashType
{
    struct Node** heads; // Array of pointers to Nodes (chains)
    int size;            // Size of the array
};

// Hash function that distributes data evenly
int hash(int key, int size)
{
    return key % size; // Using modulo operation for simplicity and uniform distribution
}

// Initialize the hash table
struct HashType* createHashTable(int size)
{
    struct HashType* hashTable = (struct HashType*)malloc(sizeof(struct HashType));
    hashTable->size = size;
    hashTable->heads = (struct Node**)malloc(sizeof(struct Node*) * size);
    
    for (int i = 0; i < size; i++) {
        hashTable->heads[i] = NULL;
    }
    
    return hashTable;
}

// Insert a record into the hash table
void insertRecord(struct HashType* hashTable, struct RecordType record)
{
    int index = hash(record.id, hashTable->size);
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = record;
    newNode->next = hashTable->heads[index];
    hashTable->heads[index] = newNode;
}

// Display the records in the hash table
void displayRecordsInHash(struct HashType *hashTable)
{
    printf("\nRecords in Hash Table:\n");
    for (int i = 0; i < hashTable->size; ++i)
    {
        struct Node* temp = hashTable->heads[i];
        if (temp != NULL) {
            printf("Index %d -> ", i);
            while (temp != NULL) {
                printf("id: %d, name: %c, order: %d -> ", temp->data.id, temp->data.name, temp->data.order);
                temp = temp->next;
            }
            printf("NULL\n");
        }
    }
    printf("\n");
}

// Parsing input file
int parseData(char* inputFileName, struct RecordType** ppData)
{
    FILE* inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
        }

        fclose(inFile);
    }

    return dataSz;
}

// Main function
int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;

    recordSz = parseData("input_lab_9.txt", &pRecords);
    printf("Parsed %d records.\n", recordSz);

    struct HashType* hashTable = createHashTable(10); // Creating a hash table with size 10

    for (int i = 0; i < recordSz; i++) {
        insertRecord(hashTable, pRecords[i]);
    }

    displayRecordsInHash(hashTable);
    return 0;
}
