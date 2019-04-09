#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include <assert.h>

struct Map_t{
    MapDataElement* data_elements;
    MapKeyElement* key_elements;
    int iterator;
    copyMapDataElements copyDataElement;
    copyMapKeyElements copyKeyElement;
    freeMapDataElements freeDataElement;
    freeMapKeyElements freeKeyElement;
    compareMapKeyElements compareKeyElements;
};

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
    map->key_elements = malloc(sizeof(MapKeyElement));
    map->data_elements = malloc(sizeof(MapDataElement));
    if (map->data_elements == NULL || map->key_elements == NULL){
        freeDataElement(map);
        freeKeyElement(map);
        return NULL;
    }
    map->iterator = 0;
    map->copyDataElement = copyDataElement;
    map->copyKeyElement = copyKeyElement;
    map->freeDataElement = freeDataElement;
    map->freeKeyElement = freeKeyElement;
    map->compareKeyElements = compareKeyElements;
    return map;
}

void mapDestroy(Map map){
    if (mapClear(map)!=MAP_SUCCESS){
        return;
    }
    free(map);
}

Map mapCopy(Map map) {
    Map map_copy = mapCreate(map->copyDataElement, map->copyKeyElement, map->freeDataElement,
                               map->freeKeyElement, map->compareKeyElements);
    //checking if mapCreate failed. mapCreate may fail if supplied functions are null, or in case of a memory error.
    if (map_copy == NULL){ //
        return NULL;
    }
    MAP_FOREACH(MapKeyElement,iterator,map){
        map_copy->copyDataElement(mapGet(map,iterator));
        map_copy->copyKeyElement(iterator);
    }
    return map_copy;
}

int mapGetSize(Map map){
    int size = 0;
    MAP_FOREACH(MapKeyElement,iterator,map){
        size++;
    }
    return size>0 ? size : -1;
}

bool mapContains(Map map, MapKeyElement element){
    MAP_FOREACH(MapKeyElement,iterator,map){
        if (map->compareKeyElements(element,iterator) == 0){
            return true;
        }
    }
    return false;
}

MapResult mapPut(Map map, MapKeyElement keyElement, MapDataElement dataElement){
    if (map == NULL){
        return MAP_NULL_ARGUMENT;
    }
    return MAP_SUCCESS;
}

MapDataElement mapGet(Map map, MapKeyElement keyElement){
    if (map == NULL){
        return NULL;
    }
    int old_iterator = map->iterator;
    MAP_FOREACH(MapKeyElement,iterator,map){
        if (map->compareKeyElements(keyElement,iterator) == 0){
            return
            map ->iterator = old_iterator;
    }
    map ->iterator = old_iterator;
}

MapResult mapRemove(Map map, MapKeyElement keyElement){
    if (map == NULL){
        return MAP_NULL_ARGUMENT;
    }
    MAP_FOREACH(MapKeyElement,iterator,map){
        if (map->compareKeyElements(keyElement,iterator) == 0){
            map->freeDataElement(mapGet(map,iterator));
            map->freeKeyElement(iterator);
            return MAP_SUCCESS;
        }
    }
    return MAP_ITEM_DOES_NOT_EXIST;
}

MapKeyElement mapGetFirst(Map map){

}

MapKeyElement mapGetNext(Map map){
    //if supplied with null map pointer, reached end of map or the iterator is in an invalid state for some reason.
    if (map == NULL || !mapGetSize(map)<++map->iterator || map->iterator<0){
        return NULL;
    }
    return
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
