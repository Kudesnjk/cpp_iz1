//
// Created by daniil on 07.03.2020.
//
#include "libs/functions.h"
#include <assert.h>

int test_check_data_check_device();

int main(int argc, const char *argv[]){
    test_check_data_check_device();
    return 0;
}

int test_check_data_check_device(){
    device dev1 = {1 , 0, 0, 100, 0};
    device dev2 = {1, 0, 0 ,100, 0};
    int num = 2;

    device * dev_array = malloc(sizeof(device) * num);

    if(!dev_array){
        return ERR;
    }

    int i = 0;

    dev_array[i] = dev1;
    i++;
    dev_array[i] = dev2;
    i--;

    assert(check_data(dev_array, "CD", "no", i)==OK); //проверка валидных значений

    dev_array[i].cur_capacity = -10;
    assert(check_data(dev_array, "CD", "no", i)==CAP_ERR);//проверка валидности значений ёмкости

    dev_array[i].cur_capacity = 50;
    dev_array[i].capacity = 40;
    assert(check_data(dev_array, "CD", "no", i)==CAP_ERR);//проверка того, что заполненная ёмкость не превышает максимальную

    dev_array[i].cur_capacity = 0;
    dev_array[i].capacity = 100;
    assert(check_data(dev_array, "cdd", "no", i)==TYPE_ERR);//проверка валидности типа накопителя

    assert(check_data(dev_array, "CD", "noooo", i)==REW_ERR);//проверка валидности значения "возможность перезаписи"

    i++;
    assert(check_data(dev_array, "CD", "no", i)==ID_ERR); //проверка уникальности id

    int amount = 200;

    assert(check_device(dev_array, num, amount)!=OK); //проверка возможности записи памяти, большей доступной

    amount = 100;

    assert(check_device(dev_array, num, amount)==OK); //проверка валидного количества памяти

    free(dev_array);
    return OK;
}
