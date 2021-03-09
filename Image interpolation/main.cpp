#include <string.h>
#include <iostream>
#include "resize.h"

int main()
{
	const char* input_file = "E:\\pic1.yuv";		//ԭͼƬ
	const char* output_file = "E:\\pic2.yuv";	//�޸ĺ�ͼƬ	
	int src_width = 720;
	int src_height = 480;//ԭͼƬ��С
	int dst_width = 1920;
	int dst_height = 1080;//�޸ĺ�ͼƬ��С
	int resize_type = 1;		//0:nearest, 1:bilinear//�����������ڽ�����˫����

	resize(input_file, src_width, src_height, output_file, dst_width, dst_height, resize_type);
	return 0;
}
