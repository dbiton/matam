#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "map.h"

typedef struct Node_t {
    MapDataElement data;
    MapKeyElement key;
    struct Node_t *nextNode;
} *Node;

struct Map_t {
    Node first_node;
    int size;
    int iterator;

    copyMapDataElements copyDataElement;
    copyMapKeyElements copyKeyElement;
    freeMapDataElements freeDataElement;
    freeMapKeyElements freeKeyElement;
    compareMapKeyElements compareKeyElements;
};

//static functions, not for use by the user
static void nodeInsertBefore(Map map, Node thisNode, Node newNode, MapDataElement dataElement, MapKeyElement keyElement);
static Node nodeGet(Map map, Node node,MapKeyElement keyElement);
static void freeNodes(Node node, Map map);
static void freeNode(Node node, Map map);

static void freeNode(Node node, Map map) {
        map->freeDataElement(node->data);
        map->freeKeyElement(node->key);
        free(node);
}

static void freeNodes(Node node, Map map){
    if (node != NULL) {
        if (node->nextNode != NULL) {
            freeNodes(node->nextNode, map);
        }
        freeNode(node, map);
    }
}

Map mapCreate(copyMapDataElements copyDataElement,
              copyMapKeyElements copyKeyElement,
              freeMapDataElements freeDataElement,
              freeMapKeyElements freeKeyElement,
              compareMapKeyElements compareKeyElements) {

    assert(copyDataElement != NULL &&
           copyKeyElement != NULL && freeDataElement != NULL &&
           freeKeyElement != NULL && compareKeyElements != NULL);

    Map map = malloc(sizeof(struct Map_t));
    if (map == NULL) {
        return NULL;
    }
    map->first_node = NULL;
    map->size = 0;
    map->iterator = 0;
    map->copyDataElement = copyDataElement;
    map->copyKeyElement = copyKeyElement;
    map->freeDataElement = freeDataElement;
    map->freeKeyElement = freeKeyElement;
    map->compareKeyElements = compareKeyElements;
    return map;
}

void mapDestroy(Map map) {
    freeNodes(map->first_node,map);
    free(map);
}

Map mapCopy(Map map) {
    Map map_copy = mapCreate(map->copyDataElement, map->copyKeyElement, map->freeDataElement,
                             map->freeKeyElement, map->compareKeyElements);
    if (map_copy == NULL) {
        return NULL;
    }
    MAP_FOREACH(MapKeyElement, iterator, map) {
        if (mapPut(map_copy,iterator,mapGet(map,iterator))!=MAP_SUCCESS){
            return NULL;
        }
    }
    return map_copy;
}

int mapGetSize(Map map) {
    return map->size;
}

bool mapContains(Map map, MapKeyElement element) {
    if (map == NULL || element == NULL) {
        return false;
    }
    MAP_FOREACH(MapKeyElement, iterator, map) {
        if (map->compareKeyElements(element, iterator) == 0) {
            return true;
        }
    }
    return false;
}

static void nodeInsertBefore(Map map, Node thisNode,
        Node newNode, MapDataElement dataElement,
        MapKeyElement keyElement){
    newNode->nextNode = thisNode->nextNode;
    thisNode->nextNode = newNode;
    newNode->key = map->copyKeyElement(thisNode->key);
    newNode->data = map->copyDataElement(thisNode->data);
    thisNode->data = map->copyDataElement(dataElement);
    thisNode->key = map->copyKeyElement(keyElement);
}

MapResult mapPut(Map map, MapKeyElement keyElement, MapDataElement dataElement) {
    if (map == NULL) {
        return MAP_NULL_ARGUMENT;
    }

    Node newNode = malloc(sizeof(struct Node_t));
    if (newNode==NULL){
        return MAP_OUT_OF_MEMORY;
    }
    map->size++;
    //map size is 0
    if (map->first_node == NULL) {
        map->first_node = newNode;
        map->first_node->nextNode = NULL;
        map->first_node->data = map->copyDataElement(dataElement);
        map->first_node->key = map->copyKeyElement(keyElement);
        return MAP_SUCCESS;
    }

    Node thisNode = map->first_node;
    while (thisNode->nextNode != NULL){
        if (map->compareKeyElements(thisNode->key,keyElement)==0){
            return MAP_ITEM_ALREADY_EXISTS;
        }
        if (map->compareKeyElements(thisNode->key,keyElement)>0){
            nodeInsertBefore(map,thisNode,newNode,dataElement,keyElement);
            return MAP_SUCCESS;
        }
        thisNode = thisNode->nextNode;
    }
    //check if this should be the one before last node
    if (map->compareKeyElements(thisNode->key,keyElement)>0){
        nodeInsertBefore(map,thisNode,newNode,dataElement,keyElement);
        return MAP_SUCCESS;
    }
    //insert as last node
    thisNode->nextNode = newNode;
    newNode->nextNode = NULL;
    newNode->key = map->copyKeyElement(keyElement);
    newNode->data = map->copyDataElement(dataElement);
    return MAP_SUCCESS;
}

static Node nodeGet(Map map, Node node,MapKeyElement keyElement){
    if (node == NULL){
        return NULL;
    }
    if (map->compareKeyElements(node->key,keyElement)==0){
        return node;
    }
    return nodeGet(map,node->nextNode,keyElement);
}

MapDataElement mapGet(Map map, MapKeyElement keyElement) {
    Node returnNode = nodeGet(map,map->first_node,keyElement);
    if (map == NULL || returnNode == NULL) {
        return NULL;
    }
    return returnNode->data;
}

MapResult mapRemove(Map map, MapKeyElement keyElement) {
    if (map == NULL) {
        return MAP_NULL_ARGUMENT;
    }
    Node prev_node = map->first_node;
    if (map->compareKeyElements(prev_node->key, keyElement) == 0) {
        freeNode(prev_node, map);
        map->size --;
        return MAP_SUCCESS;
    }
    Node cur_node = prev_node->nextNode;
    while (cur_node != NULL && map->compareKeyElements(cur_node->key, keyElement) > 0) {
        if (map->compareKeyElements(cur_node->key, keyElement) == 0) {
            prev_node->nextNode = cur_node->nextNode;
            freeNode(cur_node, map);
            map->size --;
            return MAP_SUCCESS;
        }
        prev_node = cur_node;
        cur_node = prev_node->nextNode;
    }
    return MAP_ITEM_DOES_NOT_EXIST;
}

MapKeyElement mapGetFirst(Map map) {
    if (map->first_node == NULL) {
        return NULL;
    }
    return map->first_node->key;
}

MapKeyElement mapGetNext(Map map) {
    if (map == NULL){
        return NULL;
    }
    map->iterator++;
    if (map->iterator == mapGetSize(map)) {
        map->iterator--;
        return NULL;
    }

    Node returnNode = map->first_node;
    for (int i = 0; i < map->iterator; i++) {
        returnNode = returnNode->nextNode;
    }
    return returnNode->key;
}

MapResult mapClear(Map map) {
    if (map == NULL) {
        return MAP_NULL_ARGUMENT;
    }
    MapKeyElement iterator = mapGetFirst(map);
    do
    {
        map->freeDataElement(mapGet(map, iterator));
        map->freeKeyElement(iterator);
    } while (iterator == mapGetNext(map));
    return MAP_SUCCESS;
}
