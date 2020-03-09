//
// Created by daniil on 07.03.2020.
//

#ifndef HOMEWORK1_FUNCTIONS_H
#define HOMEWORK1_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 0
#define ERR -1
#define CAP_ERR -2
#define TYPE_ERR -3
#define ID_ERR -4
#define REW_ERR -5
#define MAX_STR_LEN 20

typedef struct device device;
typedef enum types types;

enum types{
    HDD,
    CD,
    SSD,
    CDROM,
    DVDROM,
    NUMBER_OF_TYPES
};

struct device {
    int id;
    types type;
    int cur_capacity;
    int capacity;
    _Bool rewrite;
};

int input_device();
int check_data(device * dev_array, char * type_str, char * rewrite_str,int i);
int check_device(device * dev_array, int num, int amount);
int print_device(device dev);

#endif //HOMEWORK1_FUNCTIONS_H