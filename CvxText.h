//====================================================================  
//====================================================================  
// �ļ�: CvxText.h   
// ˵��: OpenCV 3.x �������    
// ʱ��:  2016-11-11 
// ��д����: zmdsjtu@163.com  
//���͵�ַ:http://blog.csdn.net/zmdsjtu/article/category/6371625

//ԭ���ߣ� chaishushan@gmail.com   2007-8-21
//====================================================================  
//====================================================================  

#ifndef OPENCV_Cv310Text_2016_11_11_ZMD 
#define OPENCV_Cv310Text_2016_11_11_ZMD 


#include "ft2build.h"
#include "freetype/freetype.h"
#include "config.h"


// Freetype ͼƬ����������
class CvxText
{
public:

	/**
	* װ���ֿ��ļ���Ĭ��Ϊ����"simfang.ttf"
	*/
	CvxText(const char *freeType = NULL);
	virtual ~CvxText();

	/**
	* ��ȡ���塣Ŀǰ��Щ�����в�֧�֡�
	*
	* \param font        ��������, Ŀǰ��֧��
	* \param size        �����С/�հױ���/�������/��ת�Ƕ�
	* \param underline   �»���
	* \param diaphaneity ͸����
	*
	* \sa setFont, restoreFont
	*/
	void getFont(int *type, CvScalar *size = NULL, bool *underline = NULL, float *diaphaneity = NULL);

	/**
	* �������塣Ŀǰ��Щ�����в�֧�֡�
	*
	* \param font        ��������, Ŀǰ��֧��
	* \param size        �����С/�հױ���/�������/��ת�Ƕ�
	* \param underline   �»���
	* \param diaphaneity ͸����
	*
	* \sa getFont, restoreFont
	*/
	void setFont(int *type, CvScalar *size = NULL, bool *underline = NULL, float *diaphaneity = NULL);

	/**
	* �ָ�ԭʼ���������á�
	*
	* \sa getFont, setFont
	*/
	void restoreFont();

	/**
	* ������֡���������������ַ���ֹͣ��
	*
	* \param img   �����Ӱ��
	* \param text  �ı�����
	* \param pos   �ı�λ��
	* \param color �ı���ɫ
	* 
	*/
	void putText(cv::Mat &frame, const char *text, const CvPoint &pos, const CvScalar &color);

	/**
	* ������֡���������������ַ���ֹͣ��
	*
	* \param img   �����Ӱ��
	* \param text  �ı�����
	* \param pos   �ı�λ��
	* \param color �ı���ɫ
	* 
	*/
	void putText(cv::Mat &frame, const wchar_t *text, const CvPoint &pos, const CvScalar &color);

private:

	// �����ǰ�ַ�, ����posλ��  
	void putWChar(cv::Mat &frame, wchar_t wc, CvPoint &pos, CvScalar color);

	// ��������
	bool LoadFont(const char *path);

private:

	FT_Library		m_library;   // �ֿ�
	FT_Face			m_face;      // ����

	bool			m_bOk;		// freetype�����Ƿ����
	int				m_fontType; // ��������
	CvScalar		m_fontSize; // �����С
	bool			m_fontUnderline; // �»���
	float			m_fontDiaphaneity;// �ں�
};

#endif // OPENCV_Cv310Text_2016_11_11_ZMD
