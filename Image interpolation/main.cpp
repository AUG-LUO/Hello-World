#include <string.h>
#include <iostream>
#include "resize.h"

int main()
{
	const char* input_file = "E:\\pic1.yuv";		//原图片
	const char* output_file = "E:\\pic2.yuv";	//修改后图片	
	int src_width = 720;
	int src_height = 480;//原图片大小
	int dst_width = 1920;
	int dst_height = 1080;//修改后图片大小
	int resize_type = 1;		//0:nearest, 1:bilinear//决定调用最邻近还是双线性

	resize(input_file, src_width, src_height, output_file, dst_width, dst_height, resize_type);
	return 0;
}
