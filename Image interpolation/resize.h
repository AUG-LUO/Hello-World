#ifndef RESIZE_H
#define RESIZE_H//头文件必写

#include <stdio.h>
#include <string.h>

typedef unsigned char uint8;// typedef 是给一个已经存在的数据类型取一个别名，而非定义一个新的数据类型
typedef unsigned short uint16;

int clip3(int data, int min, int max);
void bilinearHorScaler(int* src_image, int* dst_image, int src_width, int src_height, int dst_width, int dst_height);
void bilinearVerScaler(int* src_image, int* dst_image, int src_width, int src_height, int dst_width, int dst_height);
void nearestScaler(int* src_image, int* dst_image, int src_width, int src_height, int dst_width, int dst_height);
void resize(const char* input_file, int src_width, int src_height, const char* output_file, int dst_width, int dst_height, int resize_type);

#endif
#pragma once//头文件必写
