//
// Created by ivan on 17-11-12.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HASH_TABLE_MAX_SIZE 1000000
typedef struct HashNode HashNode, *PHashNode;
struct HashNode{
    int key;
    int value;
    HashNode * next;
};
HashNode* hashTable[HASH_TABLE_MAX_SIZE];
int hashTableSize;
void hashTableInit();
unsigned int hashTableHashFn(int key);
void hashTableInsert(int key, int value);
HashNode* hashTableFind(int key);
void hashTableRelease();

int* twoSum(int* nums, int numsSize, int target) {
    int * indices = NULL;
    if (numsSize<2)
    {
        indices = (int*)malloc(2*sizeof(int));
        int * p = indices;
        *p = 0;
        p++;
        *p = 0;
        return indices;
    }
    int i = 0;
    for(i=0; i<numsSize; i++){
        int tmp = nums[i];
        int other_num = target - tmp;
        HashNode * node = hashTableFind(other_num);
        if (node != NULL && node->value != i){
            indices = (int*)malloc(2*sizeof(int));
            int * p = indices;
            *p = i;
            p++;
            *p = node->value;
            break;
        }
        hashTableInsert(nums[i], i);
    }
    if (indices == NULL){
        indices = (int*)malloc(2*sizeof(int));
        int * p = indices;
        *p = 0;
        p++;
        *p = 0;
    }
    return indices;
}

void release(int* indices){
    if (indices != NULL)
        free(indices);
}

int main(){
    hashTableInit();
    int nums[] = {3,2,4};
    int target = 6;
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int *indices = twoSum(nums, numsSize, target);
    if (indices != NULL){
        printf("%d, %d", indices[0], indices[1]);
    }
    else{
        printf("not exists!!!");
    }
    release(indices);
    hashTableRelease();
}

void hashTableInit(){
    hashTableSize = 0;
    memset(hashTable, 0, sizeof(HashNode*)*HASH_TABLE_MAX_SIZE);
}

unsigned int hashTableHashFn(int key){
    char buf[1024] = {0};
    sprintf(buf, "%d", key);
    const signed char *p = (const signed char*)buf;
    unsigned int h = *p;
    if (h){
        for(p+=1; *p!='\0'; ++p)
            h = (h << 5) - h + *p;
    }
    return h;
}

void hashTableInsert(int key, int value){
    if (hashTableSize >= HASH_TABLE_MAX_SIZE)
    {
        printf("out of hash table memory\n");
        return ;
    }
    unsigned int pos = hashTableHashFn(key) % HASH_TABLE_MAX_SIZE;
    HashNode* pHead = hashTable[pos];
    while(pHead){
        if (pHead->key == key){
            //printf("%d already exists!\n", key);
            return ;
        }
        pHead = pHead->next;
    }
    HashNode* pNewNode = (HashNode*)malloc(sizeof(HashNode));
    memset(pNewNode, 0, sizeof(HashNode));
    pNewNode->key = key;
    pNewNode->value = value;
    hashTable[pos] = pNewNode;
    hashTableSize++;
}

HashNode* hashTableFind(int key){
    unsigned int pos = hashTableHashFn(key) % HASH_TABLE_MAX_SIZE;
    if (hashTable[pos]){
        HashNode* pHead = hashTable[pos];
        while(pHead){
            if (pHead->key == key)
                return pHead;
            pHead = pHead->next;
        }
    }
    return NULL;
}

void hashTableRelease(){
    int i;
    for(i = 0; i < HASH_TABLE_MAX_SIZE; i++){
        if (hashTable[i]){
            HashNode* pHead = hashTable[i];
            while(pHead){
                HashNode* pTemp = pHead;
                pHead = pHead->next;
                if (pTemp){
                    free(pTemp);
                }
            }
        }
    }
}