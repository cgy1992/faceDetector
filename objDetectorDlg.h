
// objDetectorDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "pyCaller.h"
#include "FileReader.h"
#include "CvvImage.h"
#include "ResultDlg.h"
#include <vector>
#include "socket\BcecrSocket.h"
#include "CvxText.h"
using namespace std;

// ���ο���ɫ
#define RECT_COLOR CV_RGB(0, 0, 255)
// ������ɫ
#define TEXT_COLOR CV_RGB(0, 255, 0)
// �߿���
#define THICK_NESS 2

extern labelMap g_map; // �����Ϣ

extern CvxText g_font; // freetype

// ͼ���ע
struct Tips
{
	char name[64];		// ���
	int class_id;		// ���ID
	double score;		// �÷�
	cv::Rect rect;		// ���ο�
	Tips() { memset(this, 0, sizeof(Tips)); }
	Tips(const cv::Rect &rt, double s, int id = 1) : class_id(id), score(s), rect(rt) { memset(name, 0, 64); }
	int Xmin() const { return rect.x; }
	int Ymin() const { return rect.y; }
	int Xmax() const { return rect.x + rect.width; }
	int Ymax() const { return rect.y + rect.height; }
	// ���õ�ǰĿ������
	inline void setName(const char *_name) { if (_name) strcpy_s(name, _name); }
	// ��ȡ��ǰĿ������
	inline const char* getName() const { return name[0] ? name : g_map.getItemName(class_id); }
	// �Ƿ���ʶ��Ŀ��
	inline bool identifyed() const { return name[0]; }
	// Ϊͼ������ע��
	void AddTips(cv::Mat &m) const
	{
		cv::rectangle(m, rect, RECT_COLOR, THICK_NESS);
		char text[256];
		sprintf_s(text, "%s:%.3f", getName(), score);
		g_font.putText(m, text, cv::Point(rect.x, rect.y), TEXT_COLOR);
	}
	void AddTips(cv::Mat &m, const char *_name)
	{
		cv::rectangle(m, rect, RECT_COLOR, THICK_NESS);
		char text[256];
		if (_name) strcpy_s(name, _name);
		sprintf_s(text, "%s:%.3f", getName(), score);
		g_font.putText(m, text, cv::Point(rect.x, rect.y), TEXT_COLOR);
	}
	void Output() const
	{
		OUTPUT("======> x=%d, y=%d, w=%d, h=%d), score = %f\n", rect.x, rect.y, rect.width, rect.height, score);
	}
};

// ý��״̬
enum MediaState
{
	STATE_DONOTHING = 0,			// ����
	STATE_DETECTING,				// ���
	STATE_PLAYING,					// ����
	STATE_PAUSE,					// ��ͣ
};

#define Thread_Start    1			// �߳�����
#define Thread_Stop		0			// �߳�ֹͣ

// �߳�����ö��
enum Thread
{
	_InitPyCaller = 0, 
	_DetectVideo, 
	_PlayVideo,
	_Max
};

// CobjDetectorDlg �Ի���
class CobjDetectorDlg : public CDialogEx
{
// ����
public:
	CobjDetectorDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_OBJDETECTOR_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	MediaState m_nMediaState;		// ý��״̬

	char m_strFile[_MAX_PATH];		// �ļ�·��

	char m_strPath[_MAX_PATH];		// ��ǰ·��

	char m_strImage[_MAX_PATH];		// ͼ��·��: object_detection

	CFileReader m_reader;			// �ļ���ȡ��

	tfOutput m_tf;					// TensorFlow����ֵ

	pyCaller *m_py;					// python������

	bool m_bExit;					// �Ƿ��˳�����

	bool m_bOK;						// pyCaller�Ƿ��λ

	CRect m_rtPaint;				// ��ͼ����

	HDC m_hPaintDC;					// ��ͼHDC

	int m_nThreadState[_Max];		// �߳�״̬

	double m_fThreshSave;			// ͼ�񱣴���ֵ

	double m_fThreshShow;			// ͼ����ʾ��ֵ

	double m_fThreshIdentify;		// ͼ��ʶ����ֵ

	int m_nMinFaceSize;				// ����ʶ�����С�����ߴ�

	double m_fThreshBlur;			// ģ����ֵ��С�ڸ�ֵ�����������棩

	int m_nBufSize;					// ����֡��

	int m_nDetectStep;				// ���֡������

	char m_pyHome[_MAX_PATH];		// Python Home

	CvvImage m_Image;				// ��ͼͼ��

	CString m_strSettings;			// setting.ini

	char m_strServerIP[128];
	int m_nServerPort;
	int m_nServerType;
	CBcecrSocket *m_pSocket;		// Socket Client

	IPCamInfo m_info;					// IPC info

	bool m_bFullScreen;
	WINDOWPLACEMENT m_struOldWndpl;

	// �Ƿ����ڼ��
	bool IsDetecting() const { return STATE_DETECTING == m_nMediaState; }

	// �Ƿ���æ
	bool IsBusy() const { return STATE_DETECTING == m_nMediaState || STATE_PLAYING == m_nMediaState; }

	// ��ȡ��ⲽ��
	const int& GetStep() const { return m_nDetectStep; }

	// ����ͼ��
	void Paint(const cv::Mat &m);

	// ����ͼ��
	void Save(const cv::Mat &sub_m, const char *folder, int id);

	// ��ʼ��python���û���
	static void InitPyCaller(LPVOID param);
	// �����Ƶ
	static void DetectVideo(LPVOID param);
	// ��ʾ�����
	static void PlayVideo(LPVOID param);
	// ����Ŀ����
	std::vector<Tips> DoDetect(cv::Mat &m);

// ʵ��
protected:
	HICON m_hIcon;

	CResultDlg *m_pResult; // ���չʾ�Ի���

	void ReSize();		// ��������λ��

	void ObjDetectProc();// ����Ŀ����

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CStatic m_picCtrl;
	afx_msg void OpenFileProc();
	afx_msg void OnDestroy();
	afx_msg void OnObjDetect();
	afx_msg void OnFileClose();
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnUpdateFileOpen(CCmdUI *pCmdUI);
	afx_msg void OnUpdateObjDetect(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFileClose(CCmdUI *pCmdUI);
	afx_msg void OnFileQuit();
	afx_msg void OnEditPlay();
	afx_msg void OnUpdateEditPlay(CCmdUI *pCmdUI);
	afx_msg void OnEditPause();
	afx_msg void OnUpdateEditPause(CCmdUI *pCmdUI);
	afx_msg void OnEditStop();
	afx_msg void OnUpdateEditStop(CCmdUI *pCmdUI);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OpenIPCProc();
	afx_msg void OnUpdateFileIpc(CCmdUI *pCmdUI);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSetThreshold();
	afx_msg void OnSetPython();
	afx_msg void ShowResultProc();
	virtual BOOL DestroyWindow();
	afx_msg void FullScreenProc();
	afx_msg void OnUpdateFullScreen(CCmdUI *pCmdUI);
	afx_msg void OnFaceServer();
};