#include "resize.h"

int clip3(int data, int min, int max)//将某个数据限制在一个范围里
{
	return (data > max) ? max : ((data < min) ? min : data);//？？这里是不是重复了，上下是两种方法吧？？
	if (data > max)
		return max;
	else if (data > min)
		return data;
	else
		return min;
}

//bilinear takes 4 pixels (2×2) into account
/*
* 函数名：	bilinearHorScaler
* 说明：	水平方向双线性插值
* 参数：
*/
void bilinearHorScaler(int* src_image, int* dst_image, int src_width, int src_height, int dst_width, int dst_height)
{
	double resizeX = (double)dst_width / src_width;//现宽度比原宽度（缩放系数）
	for (int ver = 0; ver < dst_height; ++ver) {
		for (int hor = 0; hor < dst_width; ++hor) {//一行一行处理
			double srcCoorX = hor / resizeX;//当前像素在原宽度下的位置i+u
			double weight1 = srcCoorX - (double)((int)srcCoorX);//坐标小数部分u
			double weight2 = (double)((int)(srcCoorX + 1)) - srcCoorX;//1-u
			double dstValue = *(src_image + src_width * ver + clip3((int)srcCoorX, 0, src_width - 1)) * weight2 //用公式算
							+ *(src_image + src_width * ver + clip3((int)(srcCoorX + 1), 0, src_width - 1)) * weight1;
			*(dst_image + dst_width * ver + hor) = clip3((uint8)dstValue, 0, 255);
			// uint8=unsigned char;uint16=unsigned short;
		}
	}
}

/*
* 函数名：	bilinearVerScaler
* 说明：	垂直方向双线性插值
* 参数：
*/
void bilinearVerScaler(int* src_image, int* dst_image, int src_width, int src_height, int dst_width, int dst_height)
{
	double resizeY = (double)dst_height / src_height;
	for (int ver = 0; ver < dst_height; ++ver) {
		for (int hor = 0; hor < dst_width; ++hor) {
			double srcCoorY = ver / resizeY;
			double weight1 = srcCoorY - (double)((int)srcCoorY);
			double weight2 = (double)((int)(srcCoorY + 1)) - srcCoorY;
			double dstValue = *(src_image + src_width * clip3((int)srcCoorY, 0, src_height - 1) + hor) * weight2 
							+ *(src_image + src_width * clip3((int)(srcCoorY + 1), 0, src_height - 1) + hor) * weight1;
			*(dst_image + dst_width * ver + hor) = clip3((uint8)dstValue, 0, 255);
		}
	}
}

/*
* 函数名：	yuv420p_NearestScaler
* 说明：	最近邻插值
* 参数：
*/
void nearestScaler(int* src_image, int* dst_image, int src_width, int src_height, int dst_width, int dst_height)
{
	double resizeX = (double)dst_width / src_width;			//水平缩放系数
	double resizeY = (double)dst_height / src_height;			//垂直缩放系数
	int srcX = 0;
	int srcY = 0;
	for (int ver = 0; ver < dst_height; ++ver) {
		for (int hor = 0; hor < dst_width; ++hor) {
			srcX = clip3(int(hor / resizeX + 0.5), 0, src_width - 1);// 四舍五入判断用哪个
			srcY = clip3(int(ver / resizeY + 0.5), 0, src_height - 1);
			*(dst_image + dst_width * ver + hor) = *(src_image + src_width * srcY + srcX);
		}
	}
}

void resize(const char* input_file, int src_width, int src_height, const char* output_file, int dst_width, int dst_height, int resize_type)
{
	/*
	#include<string.h>void *memset(void *s, int ch, size_t n);
	memset是计算机中C/C++语言初始化函数。
	作用是将某一块内存中的内容全部设置为指定的值， 这个函数通常为新申请的内存做初始化工作。
	它是对较大的结构体或数组进行清零操作的一种最快方法(如果结构体中有数组的话还是需要对数组单独进行初始化处理的)。
	解释：将s中当前位置后面的n个字节用ch替换并返回s。
	*/
	//因为这里是针对YUV420数据，U和V的像素数量只有Y分量的1/4

	//定义+初始化src buffer
	int* src_y = new int[src_width * src_height];
	int* src_cb = new int[src_width * src_height / 4];
	int* src_cr = new int[src_width * src_height / 4];
	memset(src_y, 0, sizeof(int) * src_width * src_height);
	memset(src_cb, 0, sizeof(int) * src_width * src_height / 4);
	memset(src_cr, 0, sizeof(int) * src_width * src_height / 4);
	
	//定义+初始化 dst buffer
	int* dst_y = new int[dst_width * dst_height];
	int* dst_cb = new int[dst_width * dst_height / 4];
	int* dst_cr = new int[dst_width * dst_height / 4];
	memset(dst_y, 0, sizeof(int) * dst_width * dst_height);
	memset(dst_cb, 0, sizeof(int) * dst_width * dst_height / 4);
	memset(dst_cr, 0, sizeof(int) * dst_width * dst_height / 4);

	//定义+初始化mid buffer
	int* mid_y = new int[dst_width * src_height];
	int* mid_cb = new int[dst_width * src_height / 4];
	int* mid_cr = new int[dst_width * src_height / 4];
	memset(mid_y, 0, sizeof(int) * dst_width * src_height);
	memset(mid_cb, 0, sizeof(int) * dst_width * src_height / 4);
	memset(mid_cr, 0, sizeof(int) * dst_width * src_height / 4);

	uint8* data_in_8bit = new uint8[src_width * src_height * 3 / 2];
	memset(data_in_8bit, 0, sizeof(uint8) * src_width * src_height * 3 / 2);//3/2=1+1/4+1/4,即yuv420的数据储存方式

	uint8* data_out_8bit = new uint8[dst_width * dst_height * 3 / 2];
	memset(data_out_8bit, 0, sizeof(uint8) * dst_width * dst_height * 3 / 2);

	FILE* fp_in;
	if (fopen_s(&fp_in, input_file, "r") != 0)
		printf("The input_file was not opened\n");
	
	FILE* fp_out;
	if (fopen_s(&fp_out, output_file, "wb+") != 0)
		printf("The output_file was not opened\n");

	//data read
	fread(data_in_8bit, sizeof(uint8), src_width * src_height * 3 / 2, fp_in);
	//Y component
	for (int ver = 0; ver < src_height; ver++)
	{
		for (int hor = 0; hor < src_width; hor++)
		{
			src_y[ver * src_width + hor] = data_in_8bit[ver * src_width + hor];
		}
	}
	//c component YUV420P
	for (int ver = 0; ver < src_height / 2; ver++)
	{
		for (int hor = 0; hor < src_width / 2; hor++)
		{
			src_cb[ver * (src_width / 2) + hor] = data_in_8bit[src_height * src_width 
															  + ver * src_width / 2 + hor];
			src_cr[ver * (src_width / 2) + hor] = data_in_8bit[src_height * src_width 
				                                              + src_height * src_width / 4 
															  + ver * src_width / 2 + hor];
		}
	}

	//resize//对yuv三个component应用插值算法
	if (0 == resize_type)
	{
		nearestScaler(src_y, dst_y, src_width, src_height, dst_width, dst_height);
		nearestScaler(src_cb, dst_cb, src_width / 2, src_height / 2, dst_width / 2, dst_height / 2);
		nearestScaler(src_cr, dst_cr, src_width / 2, src_height / 2, dst_width / 2, dst_height / 2);
	}
	else if (1 == resize_type)
	{
		bilinearHorScaler(src_y, mid_y, src_width, src_height, dst_width, src_height);
		bilinearHorScaler(src_cb, mid_cb, src_width / 2, src_height / 2, dst_width / 2, src_height / 2);
		bilinearHorScaler(src_cr, mid_cr, src_width / 2, src_height / 2, dst_width / 2, src_height / 2);

		bilinearVerScaler(mid_y, dst_y, dst_width, src_height, dst_width, dst_height);
		bilinearVerScaler(mid_cb, dst_cb, dst_width / 2, src_height / 2, dst_width / 2, dst_height / 2);
		bilinearVerScaler(mid_cr, dst_cr, dst_width / 2, src_height / 2, dst_width / 2, dst_height / 2);
	}
	else//？？这里重复的意义是？？
	{
		nearestScaler(src_y, dst_y, src_width, src_height, dst_width, dst_height);
		nearestScaler(src_cb, dst_cb, src_width / 2, src_height / 2, dst_width / 2, dst_height / 2);
		nearestScaler(src_cr, dst_cr, src_width / 2, src_height / 2, dst_width / 2, dst_height / 2);
	}

	//data write
	for (int ver = 0; ver < dst_height; ver++)
	{
		for (int hor = 0; hor < dst_width; hor++)
		{
			data_out_8bit[ver * dst_width + hor] = clip3(dst_y[ver * dst_width + hor], 0, 255);
		}
	}

	for (int ver = 0; ver < dst_height / 2; ver++)
	{
		for (int hor = 0; hor < dst_width / 2; hor++)
		{
			data_out_8bit[dst_height * dst_width + ver * dst_width / 2 + hor] = clip3(dst_cb[ver * (dst_width / 2) + hor], 0, 255);
			data_out_8bit[dst_height * dst_width + dst_height * dst_width / 4 + ver * dst_width / 2 + hor] = clip3(dst_cr[ver * (dst_width / 2) + hor], 0, 255);
		}
	}
	fwrite(data_out_8bit, sizeof(uint8), dst_width * dst_height * 3 / 2, fp_out);

	delete[] src_y;
	delete[] src_cb;
	delete[] src_cr;
	delete[] dst_y;
	delete[] dst_cb;
	delete[] dst_cr;
	delete[] mid_y;
	delete[] mid_cb;
	delete[] mid_cr;
	delete[] data_in_8bit;
	delete[] data_out_8bit;
	fclose(fp_in);
	fclose(fp_out);

}
