#pragma once
#include <WinSock2.h>
#include <string>

enum 
{
	THREADSTATE_UNKNOWN, // δ֪
	THREADSTATE_START,	// �߳�����
	THREADSTATE_STOP,	// �߳��˳�
	APP_TERMINATE,		// �����˳�
};

/** 
* @class	CBcecrSocket 
* @brief    ����socketͨ�ſͻ��˳���
* @details	ʵ�ֻ�������/�����ݵĹ���
*/
class CBcecrSocket
{
public:
	/// ���캯��
	CBcecrSocket();
	/// ����
	~CBcecrSocket();
	/// ���÷����IP���˿�
	void SetServerInfo(const char *pIp, int nPort);
	/// �Ͽ���Server������
	void DisConnect();
	/// ��������
	int recvData(char *pBuf, int nReadLen, int nTimeOut = 1000); //nTimeOut��λ����
	/// ��������
	int sendData(const char *pData, int nSendLen);
	/// �Ƿ������ӳɹ�
	bool IsConnected() const { return m_bConnected; }
	// ʶ��ͼ��
	double Identify(char **name);

private:
	bool Connect(); // ����

	static void  ConnectServer(void *param); // �����߳�

private:

	SOCKET m_Socket;		/**< ��Ϊ�ͻ������ӵ�socket */

	char m_chToIp[32];				/**< �Է���IP */
	int  m_nToport;					/**< �Է��Ķ˿� */
	int m_nThreadState;				/**< �߳�״̬ */
	bool m_bConnected;				/**< �Ƿ����ӳɹ� */
};
