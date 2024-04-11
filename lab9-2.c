#include <stdio.h>
#include <stdlib.h>
#define HASH_SIZE 32
// RecordType
struct RecordType
{
    int     id;
    char    name;
    int     order;
};

struct HashType{
    struct RecordType* data;
};

// Compute the hash function
int hash(int x){
    return x % HASH_SIZE; // Simple modulo hashing
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData){
    FILE* inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType*)malloc(sizeof(struct RecordType) * dataSz);
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

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
    int i;
    printf("\nRecords:\n");
    for (i = 0; i < dataSz; ++i)
    {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n\n");
}

// Initialize hash table
void initHash(struct HashType* hashArray, int hashSz)
{
    int i;
    for (i = 0; i < hashSz; ++i)
    {
        hashArray[i].data = NULL;
    }
}

// Insert record into hash table
void insertIntoHash(struct HashType* hashArray, int hashSz, struct RecordType record)
{
    int index = hash(record.id); // Compute hash index
    // Allocate memory for the record in the hash table
    hashArray[index].data = (struct RecordType*)malloc(sizeof(struct RecordType));
    // Copy values to the allocated memory
    *(hashArray[index].data) = record;
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
    int i;
    printf("\nRecords:\n");
    for (i = 0; i < hashSz; ++i)
    {
        if (pHashArray[i].data != NULL)
        {
            printf("Index %d -> %d %c %d\n", i, pHashArray[i].data->id, pHashArray[i].data->name, pHashArray[i].data->order);
        }
    }
    printf("\n\n");
}

int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);
    struct HashType hashTable[HASH_SIZE];
    initHash(hashTable, HASH_SIZE);

    int i;
    for (i = 0; i < recordSz; ++i){
        insertIntoHash(hashTable, HASH_SIZE, pRecords[i]);
    }
    displayRecordsInHash(hashTable, HASH_SIZE);
    free(pRecords);

    return 0;
}
