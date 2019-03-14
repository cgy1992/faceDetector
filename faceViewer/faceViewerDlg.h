
// faceViewerDlg.h : ͷ�ļ�
//

#pragma once
#include "PicControl.h"
#include <map>
#include <queue>
#include "pyCaller.h"

// ÿ��/�����֧�ֲ��ŵĴ���
#define MAX_WNDSIZE 12

enum 
{
	Thread_Unknown = 0, 
	Thread_Start, 
	Thread_Stop, 
	App_Exit, 
};

//////////////////////////////////////////////////////////////////////////
// ���ָ��Ŀ¼������Ŀ¼�µ�ͼƬ(����������)�����ڶ������ˢ����ʾ

// CfaceViewerDlg �Ի���
class CfaceViewerDlg : public CDialogEx
{
// ����
public:
	CfaceViewerDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CfaceViewerDlg();

// �Ի�������
	enum { IDD = IDD_FACEVIEWER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	// ���ӵ�Ŀ¼
	char m_path[_MAX_PATH];
	// ��ǰ��ʾ�Ĵ�����/�������
	int m_nSize;
	// ˢ�¼����s��
	int m_nTime;
	// Ŀ¼����Ŀ¼ͼ����
	int m_nCount;
	// ������ʾ��ͼ����
	CPicControl *m_Pictures[MAX_WNDSIZE * MAX_WNDSIZE];
	// Ŀ¼��ͼ�����ӳ���ϵ
	std::map<CString, int> m_FolderMap;

	// ��������λ��
	void reSizeWindow();
	// ˢ��ͼ��
	int refreshFaces(const CString &folder, pyCaller *py);
	// ��ȡĿ¼��"jpg"ͼƬ����
	int getFolderPicNum(const CString &folder, std::queue<CString> &result) const;
	// ��ȡĿ¼��һ��"jpg"ͼƬ����
	int getLastPicNum(const CString &folder) const;
	bool m_bFullScreen;
	WINDOWPLACEMENT m_struOldWndpl;
	// ȫ��������
	void FullScreenProc();

	// ˢ��ͼ����߳�
	int m_nThreadState;
	static void RefreshThread(void *param);

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
