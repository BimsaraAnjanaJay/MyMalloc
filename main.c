#include <stdio.h>
#include <stdlib.h>
#define mem_size 25000

char memory[mem_size];

static int i = 0;
int j = 0, k = 0;

struct node
{
    void *block_ptr;
    void *data_ptr;
    int size;
    int free;
    struct node *next;
};
struct node *freeList = (void *)memory;
struct node *temp;

void *start = &memory[0];
void *end = &memory[mem_size];
void *void_ret_ptr, *temp_block, *temp_data, *temp_next, *to_free;

void begin()
{
    freeList->block_ptr = start;
    freeList->data_ptr = start + sizeof(struct node);
    freeList->size = mem_size - sizeof(struct node);
    freeList->free = 1;
    freeList->next = NULL;
}

void *MyMalloc(size_t req_size)
{
    if (i == 0)
    {
        begin();
        i++;
    }
    temp = (void *)memory;
    while (temp->next != NULL)
    {
        if (temp->free == 1)
        {
            if (temp->size >= (req_size + sizeof(struct node)))
            {
                break;
            }
            j++;
            printf("%d free block can't Allocate.\n", j);
        }
        temp = temp->next;
    }
    freeList = temp;

    if (freeList->size < req_size)
    {
        printf("Insufficient Memory.\n");
        return NULL;
    }
    else if (freeList->size == req_size)
    {
        freeList->free = 0;
        void_ret_ptr = (void *)(freeList->data_ptr);
        printf("Exact Sufficient memory allocated.\n");
        // merge();
        return void_ret_ptr;
    }
    else if (freeList->size > (req_size + sizeof(struct node)))
    {
        temp_block = freeList->block_ptr;
        temp_data = freeList->data_ptr;
        if (freeList->next == NULL)
        {
            freeList->free = 0;
            freeList->next = temp_data + req_size;
            freeList = freeList->next;
            freeList->block_ptr = temp_data + req_size;
            freeList->data_ptr = freeList->block_ptr + sizeof(struct node);
            freeList->size = (end - temp_data) - req_size - sizeof(struct node);
            freeList->free = 1;
            freeList->next = NULL;
        }
        else
        {
            freeList->free = 0;
            temp_next = freeList->next;
            freeList->next = temp_data + req_size;
            freeList = freeList->next;
            freeList->block_ptr = temp_data + req_size;
            freeList->data_ptr = freeList->block_ptr + sizeof(struct node);
            freeList->size = (end - temp_data) - req_size - sizeof(struct node);
            freeList->free = 1;
            freeList->next = temp_next;
        }
        // merge();
        void_ret_ptr = temp_data;
        return void_ret_ptr;
    }
    else if (freeList->size < (req_size + sizeof(struct node)))
    {
        freeList->free = 0;
        void_ret_ptr = (void *)(freeList->data_ptr);
        printf("Sufficient memory with Internal fragmentation allocated.\n");
        // merge();
        return void_ret_ptr;
    }
    merge();
}

void myFree(void *pointer)
{
    freeList = start;
    while (freeList != pointer)
    {
        freeList = freeList->next;
    }
    freeList->free = 1;
    for (to_free = pointer; to_free < (void *)freeList->next; to_free++)
    {
        to_free = NULL;
    }
}

void merge()
{
    void *prev_freeList;
    freeList = start;
    while (freeList != NULL)
    {
        if (freeList->free == 1 && freeList->next->free == 1)
        {
            int size_of_block = (sizeof(struct node) + freeList->size);
            if ((freeList->block_ptr + size_of_block) == freeList->next)
            {
                freeList->size = freeList->next->size + sizeof(struct node) + freeList->size;
                freeList->next = freeList->next->next;
            }
            freeList = prev_freeList;
        }
        prev_freeList = freeList;
        freeList = freeList->next;
    }
}

