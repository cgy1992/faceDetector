
// faceViewer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CfaceViewerApp:
// �йش����ʵ�֣������ faceViewer.cpp
//

class CfaceViewerApp : public CWinApp
{
public:
	CfaceViewerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CfaceViewerApp theApp;