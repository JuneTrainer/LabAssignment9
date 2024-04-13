#include <stdio.h>

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
};

// Fill out this structure
struct HashType
{
	struct RecordType* record; 
    struct HashType* next;

};

// Compute the hash function
int hash(int x)
{
	return x % 23;
}

// parses input file to an integer array
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
		// Implement parse data block
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

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	for(int i = 0; i < hashSz; i++){

		if(pHashArray[i].record != NULL){

			printf("Index %d -> ", i);
			struct HashType*  Curr = &pHashArray[i];
			while(Curr != NULL){
				printf("%d, %c, %d ", Curr->record->id, Curr->record->name, Curr->record->order);

				Curr = Curr->next;
				}
			printf("\n");
		}
		else{
		printf("");
		}
	}
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);
	int hSize = 31;
	struct HashType hTable[31];
	for(int i = 0; i <hSize; i++){
		hTable[i].record = NULL;
		hTable[i].next = NULL;
	}
	for(int i = 0; i < recordSz; i++){
    int idx = hash(pRecords[i].id);
    if(hTable[idx].record == NULL){
        hTable[idx].record = &pRecords[i];
    }
    else{
        struct HashType *Curr = &hTable[idx];
        while(Curr->next != NULL){
            Curr = Curr->next;
        }
        Curr->next = (struct HashType*)malloc(sizeof(struct HashType));
        Curr->next->record = &pRecords[i];
        Curr->next->next = NULL;
    }
}

	displayRecordsInHash(hTable, hSize);
	return 0;
}