// cl: /DNDEBUG /MD /EHs-c- /Ob2
// WWDownload FTP.CPP Cftp::LogoffFromServer, retail 0x006CAA70, 183 bytes.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/GameNetwork/CftpLogoffFromServer.cpp):
// verbatim except the debug-output pair. BFME1 reads a callback cell out of
// a data global (0x01358EA8) and invokes it with two string addresses;
// retail calls kernel32!OutputDebugStringA (IAT 0xBBA19C) with "-->" then
// "QUIT\r\n" instead (CftpRecvReply.cpp precedent: with /O2 the two calls
// share one IAT load in edi). send rides the ILT (plain extern, pin
// _send@16 at 0x0065568E); RecvReply/d_00885390/ZeroStuff resolve by row.

typedef long HRESULT;

extern "C" int __stdcall send(int, const char *, int, int);
extern "C" __declspec(dllimport) void __stdcall OutputDebugStringA(const char *string);

class Rva00885390Class
{
public:
	void d_00885390(void);
};

#pragma comment(linker, "/alternatename:?RecvReply@Cftp@@QAEJPBDHPAH@Z=?d_00885570@@YAXXZ")

class Cftp
{
public:
	virtual ~Cftp();
	HRESULT RecvReply(const char *, int, int *);
	HRESULT LogoffFromServer(void);
	void ZeroStuff(void);

private:
	int m_iCommandSocket;
	int m_iDataSocket;
	char m_pad0C[0x3AC];
	void *m_pfLocalFile;
	int m_iStatus;
	int m_sendNewPortStatus;
	int m_findStart;

	void CloseSockets(void);
};

HRESULT Cftp::LogoffFromServer(void)
{
	char reply[50];
	int retCode;

	switch (m_iStatus)
	{
	case 70:
		if (send(m_iCommandSocket, "QUIT\r\n", 6, 0) > 0)
		{
			OutputDebugStringA("-->");
			OutputDebugStringA("QUIT\r\n");
			m_iStatus = 80;
		}
		else
		{
			return 0x80040001;
		}
	case 80:
		{
			int replyResult = RecvReply(reply, 50, &retCode);
			if (replyResult == 0)
			{
				if (retCode == 221)
				{
					((Rva00885390Class *)this)->d_00885390();
					ZeroStuff();
					return 0;
				}
				m_iStatus = 70;
				return 0x80040002;
			}

			return replyResult == 0x80040001 ? 0x80040001 : 0x80040002;
		}
	default:
		m_iStatus = 70;
		return 0x80040002;
	}
}
