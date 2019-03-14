#pragma once
#include "afxwin.h"

enum 
{
	SERVER_FACE_IDENTIFY = 0,		// ����ʶ��
	SERVER_EMOTION_IDENTIFY = 1,	// ����ʶ��
	SERVER_AGE_IDENTIFY = 2,		// ����ʶ��
	SERVER_MAX, 
};

// CServerDlg �Ի���

class CServerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CServerDlg)

public:
	CServerDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CServerDlg();

// �Ի�������
	enum { IDD = IDD_SERVER_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_EditServerIP;
	CEdit m_EditServerPort;
	CString m_strServerIP;
	int m_nServerPort;
	CComboBox m_ComboType;
	int m_nType;
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboType();
};
