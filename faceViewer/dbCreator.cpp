#include "dbCreator.h"
#include "StrTransfer.h"


// �½�һ�����ݿ�
bool CreateDataBase(const char* strPath, CppSQLite3DB *m_pDatabase)
{
	CppSQLite3DB s;
	if (NULL == m_pDatabase) m_pDatabase = &s;
	const char *szUtf8 = NULL;

	try
	{
		//�򿪻��½�һ�����ݿ�
		m_pDatabase->open( strPath );

		//�жϱ����Ƿ����
		if( !m_pDatabase->tableExists("faceInfo") )
		{
			//������, �½�Ŀ¼��
			char query[1024+32*512] = "create table faceInfo("
				"id integer not null PRIMARY KEY AUTOINCREMENT, "
				"path varchar(64) not null, " 
				"class integer not null default 0, "
				"embedding integer not null default 0, ", 
				*p = query + strlen(query);
			for (int i = 0; i < 511; ++i)
			{
				sprintf(p, "p%d float not null default 0, ", i+1);
				p += strlen(p);
			}
			sprintf(p, "p512 float not null default 0)");
			szUtf8 = MByteToUtf8(query);
			int ret = m_pDatabase->execDML(szUtf8);
			if (szUtf8) delete [] szUtf8;
			return ret >= 0;
		}
	}
	catch(CppSQLite3Exception ex)
	{
		OutputDebugStringA(ex.errorMessage());
		if (szUtf8) delete [] szUtf8;
		return false;
	}

	return true;
}
