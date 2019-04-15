#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "map.h"

struct Map_t{
    Node first_node;
    int size;
    int iterator;
    copyMapDataElements copyDataElement;
    copyMapKeyElements copyKeyElement;
    freeMapDataElements freeDataElement;
    freeMapKeyElements freeKeyElement;
    compareMapKeyElements compareKeyElements;
};

void freeNode(Node node,Map map){
    map->freeDataElement(node->data);
    map->freeKeyElement(node->key);
    free(node);
}

Map mapCreate(copyMapDataElements copyDataElement,
              copyMapKeyElements copyKeyElement,
              freeMapDataElements freeDataElement,
              freeMapKeyElements freeKeyElement,
              compareMapKeyElements compareKeyElements){

    assert(copyDataElement != NULL &&
    copyKeyElement != NULL && freeDataElement != NULL &&
    freeKeyElement != NULL && compareKeyElements != NULL);

    Map map = malloc(sizeof(*map));
    if (map == NULL){
        return NULL;
    }
    map->first_node = malloc(sizeof(Node));
    if (map->first_node == NULL){
        mapDestroy(map);
        return NULL;
    }
    map->first_node->nextNode = NULL;
    map->first_node->prevNode = NULL;
    map->size = 0;
    map->iterator = 0;
    map->copyDataElement = copyDataElement;
    map->copyKeyElement = copyKeyElement;
    map->freeDataElement = freeDataElement;
    map->freeKeyElement = freeKeyElement;
    map->compareKeyElements = compareKeyElements;
    return map;
}

void mapDestroy(Map map){
    MAP_FOREACH(Node,curNode,map){
        freeNode(curNode,map);
    }
    free(map);
}

Map mapCopy(Map map) {
    Map map_copy = mapCreate(map->copyDataElement, map->copyKeyElement, map->freeDataElement,
                               map->freeKeyElement, map->compareKeyElements);
    //checking if mapCreate failed. mapCreate may fail if supplied functions are null, or in case of a memory error.
    if (map_copy == NULL){
        return NULL;
    }
    MAP_FOREACH(Node,iterator,map){
        map_copy->copyDataElement(mapGet(map,iterator));
        map_copy->copyKeyElement(iterator);
    }
    return map_copy;
}

int mapGetSize(Map map){
    return map->size>0 ? map->size : -1;
}

bool mapContains(Map map, MapKeyElement element){
    if (map == NULL || element == NULL){
        return false;
    }
    MAP_FOREACH(MapKeyElement,iterator,map){
        if (map->compareKeyElements(element,iterator) == 0){
            return true;
        }
    }
    return false;
}

bool insertNode(Node prevNode,MapKeyElement keyElement, MapDataElement dataElement){
    Node newNode = malloc(sizeof(Node));
    if (newNode == NULL){
        return false;
    }
    newNode->nextNode = prevNode->nextNode;
    prevNode->nextNode = newNode;
    newNode->key = keyElement;
    newNode->data = dataElement;
    return true;
}

MapResult mapPut(Map map, MapKeyElement keyElement, MapDataElement dataElement){
    if (map == NULL){
        return MAP_NULL_ARGUMENT;
    }
    //map size is 0
    if (map->first_node->data == NULL){
        map->first_node->data = dataElement;
        map->first_node->key = keyElement;
        return MAP_SUCCESS;
    }
    //map size is 1
    if (map->first_node->nextNode == NULL){
        if (map->compareKeyElements(map->first_node->key,keyElement)<0){
            Node newNode = malloc(sizeof(Node));
            if (newNode == false){
                return MAP_OUT_OF_MEMORY;
            }
            newNode->nextNode = map->first_node;
            map->first_node = newNode;
            newNode->key = keyElement;
            newNode->data = dataElement;
        }
        else if (map->compareKeyElements(map->first_node->key,keyElement)>0){
            if (insertNode(map->first_node,keyElement,dataElement)==false){
                return  MAP_OUT_OF_MEMORY;
            }
        }
        return MAP_ITEM_ALREADY_EXISTS;
    }
    //map size >= 2
    Node prev_node = map->first_node;
    Node cur_node = mapGetNext(map);

    for (int i = 0; i<map->size; i++){
        if (map->compareKeyElements(cur_node->key,keyElement)==0){
            return MAP_ITEM_ALREADY_EXISTS;
        }
        else if (map->compareKeyElements(cur_node->key,keyElement)<0){
            if (insertNode(prev_node,keyElement,dataElement)==false) {
                return MAP_OUT_OF_MEMORY;
            }
            return MAP_SUCCESS;
        }
        prev_node = cur_node;
        cur_node = mapGetNext(map);
    }
}

MapDataElement mapGet(Map map, MapKeyElement keyElement) {
    if (map == NULL) {
        return NULL;
    }
    Node curNode = mapGetFirst(map);
    while (curNode!=NULL){
        if (map->compareKeyElements(curNode->key,keyElement)==0){
            return curNode->data;
        }
        curNode = mapGetNext(map);
    }
    return NULL;
}

MapResult mapRemove(Map map, MapKeyElement keyElement){
    if (map == NULL){
        return MAP_NULL_ARGUMENT;
    }
    Node prevNode = mapGetFirst(map);
    Node nextNode = curNode;
    while (curNode!=NULL && map->compareKeyElements(curNode,keyElement)>0){
        if ()
        curNode = nextNode;
        nextNode = mapGetNext(map);
        return MAP_SUCCESS;
    }
    return MAP_ITEM_DOES_NOT_EXIST;
}

MapKeyElement mapGetFirst(Map map){
    return map->first_node->key;
}

MapKeyElement mapGetNext(Map map){
    map->iterator++;
    if (map == NULL || !mapGetSize(map)>map->iterator){
        map->iterator--;
        return NULL;
    }

    Node returnNode = mapGetFirst(map);
    for (int i = 0; i<map->iterator;i++){
        returnNode = returnNode->next;
    }
    return returnNode->key;
}

MapResult mapClear(Map map){
    if (map == NULL){
        return MAP_NULL_ARGUMENT;
    }
    MapKeyElement iterator = mapGetFirst(map);
    do
    {
        map->freeDataElement(mapGet(map,iterator));
        map->freeKeyElement(iterator);
    }while(iterator = mapGetNext(map));
    return MAP_SUCCESS;
}
