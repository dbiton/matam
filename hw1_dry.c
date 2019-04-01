#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

char *duplicateString(char *str, int times);

typedef struct node_t {
    int x;
    struct node_t *next;
} *Node;
typedef enum {
    SUCCESS=0,
    MEMORY_ERROR,
    EMPTY_LIST,
    UNSORTED_LIST,
} ErrorCode;
int getListLength(Node list);
bool isListSorted(Node list);
ErrorCode mergeSortedLists(Node list1, Node list2, Node *mergedOut);

int main(){
}

ErrorCode mergeSortedLists(Node list1, Node list2, Node *mergedOut){
    if (!isListSorted(list1)||!isListSorted(list2)){
        return UNSORTED_LIST;
    }
    if (!getListLength(list1)||!getListLength(list2)){
        return EMPTY_LIST;
    }
    if (getListLength(list1)+getListLength(list2)>getListLength(mergedOut)){
            return MEMORY_ERROR;
    }
    while(*list1||*list2){
        if (*list1&&*list2){
            if (*list1>*list2){
                *mergedOut++ = *list2++;
            }else{
                *mergedOut++ = *list1++;
            }
        }else if (*list1){
            *mergedOut++ = *list1++;
        }else{
            *mergedOut++ = *list2++;
        }
    }
    return SUCCESS;
}



/*
Fixed function below.
Errors found:
Convention:
1. LEN changed to len
2. s changed to str
3. code wasn't "tabbed" correctly
4. changed function name to verb
Errors:
1. changed !str to str, since we want to assert the pointer
isn't 0, while !str does the opposite.
2. malloc changed to len*times+1 since we need space for the
'/0' as well as the strings actual chars //might not be an
actual fix, we should check if there is anything else.
3. changed place of out = out+len so the counter would work
correctly
4. returned pointer to the start of the out string instead
of it's end.
*/
char *duplicateString(char *str, int times)
{
    assert(str);
    assert(times > 0);
    int len = strlen(str);
    char *out = malloc(len*times+1);
    assert(out);
    for (int i = 0; i < times; i++) {
        strcpy(out, str);
        out += len;
    }
    return out-len*times;
}
