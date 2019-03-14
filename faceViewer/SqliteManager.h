#pragma once

#include "mString.h"

#if USING_ACL_SQLITE
#include "acl_cpp/db/db_sqlite.hpp"
#endif

enum State
{
	State_Error = -2, 
	Not_Exist = -1, 
	Embbed_False = 0, 
	Embbed_True = 1, 
};

struct buffer
{
	char sq[1024+32*512];
	char *p;
	buffer() { sq[0] = 0; p = sq; }
	buffer(const buffer &o)
	{
		memcpy(sq, o.sq, sizeof(sq));
		p = sq + (o.p - o.sq);
	}
	int length() const { return p - sq; }
	void append(const char* fmt, ...)
	{
		va_list ap;
		va_start(ap, fmt);
		vsprintf(p, fmt, ap);
		p += strlen(p);
		va_end(ap);
	}
};

/**
* @class CSqliteManager
* @brief ���ݿ������
* @date 2018-7-7 Ԭ����
*/
class CSqliteManager
{
private:
	NAMES::db_handle*	m_pDatabase; // ���ݿ����Ӿ��
	sqlite3_stmt		*m_pStmt[2];	// ִ��׼��

public:
	CSqliteManager(void);
	~CSqliteManager(void);

	// ��ʼ�����ݿ������
	bool initSqliteDB();
	// ִ��sql��䣬������insert��update��delete��ע���������ݵ�����
	// δ��������ֹǶ�׵��ó�������
	bool executeSql(const char* sql)
	{
		return m_pDatabase ? m_pDatabase->sql_update(sql) : false;
	}

	// ����Ƿ�����ȡ������������
	State embeddingCheck(const char *path, int &id);
	// �����������ݿ�
	bool InsertEmbedding(const char *path, const float *embed);
	bool UpdateEmbbedding(int id, const float *embed);

	void begin();

	void commit();
};

extern	CSqliteManager	g_dbManager;
