
#include "../pyCaller.h"
#include "../CvxText.h"

// ���ԣ���"image.jpg"�����������
int main()
{
	cv::Mat m = imread("image.jpg");
	if (false == m.empty())
	{
		pyCaller py;
		py.SetPythonHome("D:/Anaconda3/envs/tfgpu");
		py.Init("detect");
		py.ActivateFunc("test_src");
		npy_intp dims[] = { m.rows, m.cols, 3 }; // ����ά����Ϣ
		// ���ɰ��������ά�����PyObject����ʹ��PyArray_SimpleNewFromData����
		// ��һ������2��ʾά�ȣ��ڶ���Ϊά������Dims,����������ָ����������ͣ����ĸ�����Ϊ����
		PyObject *PyArray  = PyArray_SimpleNewFromData(3, dims, NPY_UBYTE, m.data);
		// ͬ�������С��Python������������һ�µ�PyTuple����
		PyObject *ArgArray = PyTuple_New(1);
		PyTuple_SetItem(ArgArray, 0, PyArray); 
		tfOutput tf(100);
		py.CallFunction("test_src", ArgArray, &tf);
		if (tf.output())
		{
			const float *p = tf.boxes;
			float x1 = *p++, y1 = *p++, x2 = *p++, y2 = *p++;
			cv::Rect rect(CvPoint(x1, y1), CvPoint(x2, y2));
			cv::rectangle(m, rect, CV_RGB(0, 0, 255), 2);
			CvxText font("simsun.ttc");
			char text[256];
			sprintf_s(text, "%s:%.3f", "����", *p);
			font.putText(m, text, cv::Point(rect.x, rect.y), 
				CV_RGB(0, 255, 0));
			imshow("face", m);
			waitKey(0);
		}
	}
	system("PAUSE");
	return 0;
}
