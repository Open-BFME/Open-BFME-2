// cl: /O2 /Oi /DNDEBUG /MD
//
// Cftp::ZeroStuff, retail 0x006C9ED0, 109 bytes.
// Dedicated TU so ftp_constructor.cpp cannot see this body.
// Layout matches the ZH ftp.h members after the virtual dtor's vptr.
// /O2 /Oi unrolls the 16-byte memset pair as lea edx / mov / add ecx.

struct SockAddr4
{
	int a;
	int b;
	int c;
	int d;
};

class Cftp
{
	int m_iCommandSocket;
	int m_iDataSocket;
	SockAddr4 m_CommandSockAddr;
	SockAddr4 m_DataSockAddr;
	int m_iFilePos;
	int m_iBytesRead;
	int m_iFileSize;
	char m_szRemoteFilePath[128];
	char m_szRemoteFileName[128];
	char m_szLocalFilePath[128];
	char m_szLocalFileName[128];
	char m_szServerName[128];
	char m_szUserName[128];
	char m_szPassword[128];
	void *m_pfLocalFile;
	int m_iStatus;
	int m_sendNewPortStatus;
	int m_findStart;

public:
	virtual ~Cftp();
	void ZeroStuff();
};

extern "C" void *memset(void *dst, int val, unsigned n);

void Cftp::ZeroStuff()
{
	m_iBytesRead = 0;
	m_iFileSize = 0;
	m_szRemoteFilePath[0] = 0;
	m_szRemoteFileName[0] = 0;
	m_szLocalFilePath[0] = 0;
	m_szLocalFileName[0] = 0;
	m_szServerName[0] = 0;
	m_szUserName[0] = 0;
	m_szPassword[0] = 0;
	m_iDataSocket = 0;
	m_iCommandSocket = 0;
	m_iFilePos = 0;
	m_iStatus = 0;
	m_sendNewPortStatus = 0;
	m_pfLocalFile = 0;
	m_findStart = 0;
	memset(&m_CommandSockAddr, 0, sizeof(m_CommandSockAddr));
	memset(&m_DataSockAddr, 0, sizeof(m_DataSockAddr));
}
