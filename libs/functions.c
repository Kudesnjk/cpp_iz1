//
// Created by daniil on 07.03.2020.
//
#include "functions.h"


int input_device(){
    int count = 0;
    printf("Input number of devices:");
    if(scanf("%d", &count) != 1 || count < 1){
        printf("Incorrect data!\n");
        return ERR;
    }

    device * dev_array = malloc(sizeof(device) * count);

    if(dev_array == NULL){
        printf("Unable to allocate memory!");
        return ERR;
    }

    printf("Input device in format: id(unique) type(HDD, SSD, CD, CDROM, DVDROM) capacity(current, max) rewritability (yes/no):\n");
    char type_str[MAX_STR_LEN];
    char rewrite_str[MAX_STR_LEN];
    for(int i =0; i < count; i++){
        if(scanf("%d %19s %d %d %19s", &dev_array[i].id, type_str, &dev_array[i].cur_capacity, &dev_array[i].capacity, rewrite_str) != 5){
            printf("Incorrect data!");
            return ERR;
        }
        switch(check_data(dev_array, type_str, rewrite_str, i)){
            case ID_ERR:
                printf("Wrong format of id, input again!\n");
                i--;
                break;
            case TYPE_ERR:
                printf("Wrong format of type, input again!\n");
                i--;
                break;
            case CAP_ERR:
                printf("Wrong format of capacity, input again!\n");
                i--;
                break;
            case REW_ERR:
                printf("Wrong format of rewritability, input again!\n");
                i--;
                break;
        }
    }
    int amount = 0;
    printf("Input amount of data you need to record: ");
    if(scanf("%d", &amount) != 1 || amount < 0){
        printf("Incorrect data!");
        return ERR;
    }
    if(check_device(dev_array, count, amount)==ERR){
        printf("No such device!\n");
        free(dev_array);
        return ERR;
    }
    free(dev_array);
    return OK;
}

int check_data(device * dev_array, char * type_str, char * rewrite_str, int i){

    const char * const types_str[NUMBER_OF_TYPES] = {
            [HDD] = "HDD",
            [CD] = "CD",
            [SSD] = "SSD",
            [CDROM] = "CDROM",
            [DVDROM] = "DVDROM"
    };

    if(dev_array[i].cur_capacity > dev_array[i].capacity || dev_array[i].capacity<0 || dev_array[i].cur_capacity<0){
        return CAP_ERR;
    }

    int flag = 0;
    for(int j = 0; j < NUMBER_OF_TYPES; j++){
        if(!strcmp(types_str[j], type_str)){
            dev_array[i].type = j;
            flag = 1;
        }
    }
    if(!flag){
        return TYPE_ERR;
    }

    if(!strcmp(rewrite_str, "yes")){
        dev_array[i].rewrite = 1;
    }
    else if(!strcmp(rewrite_str, "no")){
        dev_array[i].rewrite = 0;
    }
    else {
        return REW_ERR;
    }

    if(dev_array[i].id < 0){
        return ID_ERR;
    }
    for(int j = 0; j < i; j++){
        if(dev_array[j].id == dev_array[i].id){
            return ID_ERR;
        }
    }
    return OK;
}

int check_device(device * dev_array, int num, int amount){
    int i = 0;
    int count = 0;
    while(i < num){
        if(!dev_array[i].rewrite && dev_array[i].cur_capacity == 0 && (dev_array[i].capacity - amount) >= 0){
            print_device(dev_array[i]);
            i++;
            count++;
        }
        else if(dev_array[i].rewrite && (dev_array[i].capacity - dev_array[i].cur_capacity - amount) >= 0){
            print_device(dev_array[i]);
            i++;
            count++;
        }
        else
            i++;
    }
    if(count==0){
        return ERR;
    }
    return OK;
}

int print_device(device dev){
    const char * const types_str[NUMBER_OF_TYPES] = {
            [HDD] = "HDD",
            [CD] = "CD",
            [SSD] = "SSD",
            [CDROM] = "CDROM",
            [DVDROM] = "DVDROM"
    };

    if(dev.rewrite == 1){
        printf("id: %d\ntype: %s\ncapacity: %d/%d\nrewritability: %s\n", dev.id, types_str[dev.type], dev.cur_capacity, dev.capacity, "yes");
    }
    else{
        printf("id: %d\ntype: %s\ncapacity: %d/%d\nrewritability: %s\n", dev.id, types_str[dev.type], dev.cur_capacity, dev.capacity, "no");
    }
    return OK;
}