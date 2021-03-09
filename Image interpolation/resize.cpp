#include "resize.h"

int clip3(int data, int min, int max)//��ĳ������������һ����Χ��
{
	return (data > max) ? max : ((data < min) ? min : data);//���������ǲ����ظ��ˣ����������ַ����ɣ���
	if (data > max)
		return max;
	else if (data > min)
		return data;
	else
		return min;
}

//bilinear takes 4 pixels (2��2) into account
/*
* ��������	bilinearHorScaler
* ˵����	ˮƽ����˫���Բ�ֵ
* ������
*/
void bilinearHorScaler(int* src_image, int* dst_image, int src_width, int src_height, int dst_width, int dst_height)
{
	double resizeX = (double)dst_width / src_width;//�ֿ�ȱ�ԭ��ȣ�����ϵ����
	for (int ver = 0; ver < dst_height; ++ver) {
		for (int hor = 0; hor < dst_width; ++hor) {//һ��һ�д���
			double srcCoorX = hor / resizeX;//��ǰ������ԭ����µ�λ��i+u
			double weight1 = srcCoorX - (double)((int)srcCoorX);//����С������u
			double weight2 = (double)((int)(srcCoorX + 1)) - srcCoorX;//1-u
			double dstValue = *(src_image + src_width * ver + clip3((int)srcCoorX, 0, src_width - 1)) * weight2 //�ù�ʽ��
							+ *(src_image + src_width * ver + clip3((int)(srcCoorX + 1), 0, src_width - 1)) * weight1;
			*(dst_image + dst_width * ver + hor) = clip3((uint8)dstValue, 0, 255);
			// uint8=unsigned char;uint16=unsigned short;
		}
	}
}

/*
* ��������	bilinearVerScaler
* ˵����	��ֱ����˫���Բ�ֵ
* ������
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
* ��������	yuv420p_NearestScaler
* ˵����	����ڲ�ֵ
* ������
*/
void nearestScaler(int* src_image, int* dst_image, int src_width, int src_height, int dst_width, int dst_height)
{
	double resizeX = (double)dst_width / src_width;			//ˮƽ����ϵ��
	double resizeY = (double)dst_height / src_height;			//��ֱ����ϵ��
	int srcX = 0;
	int srcY = 0;
	for (int ver = 0; ver < dst_height; ++ver) {
		for (int hor = 0; hor < dst_width; ++hor) {
			srcX = clip3(int(hor / resizeX + 0.5), 0, src_width - 1);// ���������ж����ĸ�
			srcY = clip3(int(ver / resizeY + 0.5), 0, src_height - 1);
			*(dst_image + dst_width * ver + hor) = *(src_image + src_width * srcY + srcX);
		}
	}
}

void resize(const char* input_file, int src_width, int src_height, const char* output_file, int dst_width, int dst_height, int resize_type)
{
	/*
	#include<string.h>void *memset(void *s, int ch, size_t n);
	memset�Ǽ������C/C++���Գ�ʼ��������
	�����ǽ�ĳһ���ڴ��е�����ȫ������Ϊָ����ֵ�� �������ͨ��Ϊ��������ڴ�����ʼ��������
	���ǶԽϴ�Ľṹ�������������������һ����췽��(����ṹ����������Ļ�������Ҫ�����鵥�����г�ʼ�������)��
	���ͣ���s�е�ǰλ�ú����n���ֽ���ch�滻������s��
	*/
	//��Ϊ���������YUV420���ݣ�U��V����������ֻ��Y������1/4

	//����+��ʼ��src buffer
	int* src_y = new int[src_width * src_height];
	int* src_cb = new int[src_width * src_height / 4];
	int* src_cr = new int[src_width * src_height / 4];
	memset(src_y, 0, sizeof(int) * src_width * src_height);
	memset(src_cb, 0, sizeof(int) * src_width * src_height / 4);
	memset(src_cr, 0, sizeof(int) * src_width * src_height / 4);
	
	//����+��ʼ�� dst buffer
	int* dst_y = new int[dst_width * dst_height];
	int* dst_cb = new int[dst_width * dst_height / 4];
	int* dst_cr = new int[dst_width * dst_height / 4];
	memset(dst_y, 0, sizeof(int) * dst_width * dst_height);
	memset(dst_cb, 0, sizeof(int) * dst_width * dst_height / 4);
	memset(dst_cr, 0, sizeof(int) * dst_width * dst_height / 4);

	//����+��ʼ��mid buffer
	int* mid_y = new int[dst_width * src_height];
	int* mid_cb = new int[dst_width * src_height / 4];
	int* mid_cr = new int[dst_width * src_height / 4];
	memset(mid_y, 0, sizeof(int) * dst_width * src_height);
	memset(mid_cb, 0, sizeof(int) * dst_width * src_height / 4);
	memset(mid_cr, 0, sizeof(int) * dst_width * src_height / 4);

	uint8* data_in_8bit = new uint8[src_width * src_height * 3 / 2];
	memset(data_in_8bit, 0, sizeof(uint8) * src_width * src_height * 3 / 2);//3/2=1+1/4+1/4,��yuv420�����ݴ��淽ʽ

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

	//resize//��yuv����componentӦ�ò�ֵ�㷨
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
	else//���������ظ��������ǣ���
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
