#include <stdio.h>
#include <stdlib.h>
#include "map.h"

Map mapCreate(copyMapDataElements copyDataElement,
              copyMapKeyElements copyKeyElement,
              freeMapDataElements freeDataElement,
              freeMapKeyElements freeKeyElement,
              compareMapKeyElements compareKeyElements){
}

int mapGetSize(Map map){
    int i = 0;
    while(*map.ptr_key_arr++){
        i++;
    }
    return i;
}

void mapDestroy(Map map){
    int map_size = mapGetSize(map);
    for (int i=0;i<map_size;i++){
        free(*map.ptr_str_arr++);
    }
    free(map.ptr_key_arr);
    free(map.ptr_str_arr);
}
