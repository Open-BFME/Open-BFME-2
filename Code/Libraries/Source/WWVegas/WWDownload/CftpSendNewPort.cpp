// cl: /DNDEBUG /MD /EHs-c- /Ob2
// WWDownload FTP.CPP Cftp::SendNewPort, retail 0x006CA250 (480 bytes).
// BFME1 donor (same file) with BFME2 repairs: self-contained TU in the
// CftpRecvReply.cpp style (no PreRTS.h, no vptr: retail's Cftp lays
// m_iCommandSocket at +4); the PORT format is retail's own .rdata string;
// SendCommand is the private Cftp member rowed at 0x6CA040
// (CftpLoginToServer.cpp); socket-family imports ride the ILT
// (plain extern) while sprintf goes through the IAT.

#include <cstdio>
#include <cstring>

typedef long HRESULT;

struct sockaddr_in
{
	unsigned short sin_family;
	unsigned short sin_port;
	unsigned long sin_addr;
	unsigned char sin_zero[8];
};

extern "C" int __stdcall socket(int domain, int type, int protocol);
extern "C" int __stdcall ioctlsocket(int socketHandle, long command, unsigned long *argument);
extern "C" int __stdcall bind(int socketHandle, const void *address, int addressLength);
extern "C" int __stdcall getsockname(int socketHandle, void *address, int *addressLength);
extern "C" int __stdcall listen(int socketHandle, int backlog);
extern "C" unsigned long __stdcall htonl(unsigned long hostlong);
extern "C" __declspec(dllimport) int __cdecl sprintf(char *buffer, const char *format, ...);
bool Use_Non_Blocking_Mode(void);
unsigned long MyIPAddress(int socketHandle);

enum
{
	FTP_FAILED = 0x80040001,
	FTP_TRYING = 0x80040002,
	FTP_SUCCEEDED = 0,
	FTPREPLY_PORTOK = 200
};

class Cftp
{
public:
	HRESULT RecvReply(const char *reply, int size, int *replyCode);
	int SendNewPort(void);

private:
	HRESULT SendCommand(const char *command, int size);
	int m_pad0;
	int m_iCommandSocket;
	int m_iDataSocket;
	unsigned char m_pad0C[0x1C - 0xC];
	sockaddr_in m_DataSockAddr;
	unsigned char m_pad2C[0x3C0 - 0x2C];
	int m_sendNewPortStatus;
};

int Cftp::SendNewPort(void)
{
	unsigned long uTemp;
	char command[256];
	int i, iReply;

	if (m_sendNewPortStatus == 0)
	{
		m_iDataSocket = socket(2, 1, 0);

		if (m_iDataSocket < 0)
		{
			return (FTP_FAILED);
		}

		uTemp = 1;

		if (Use_Non_Blocking_Mode())
		{
			if (ioctlsocket(m_iCommandSocket, 0x8004667eL, &uTemp) == -1)
			{
				return (FTP_FAILED);
			}
		}

		memset(&m_DataSockAddr, 0, sizeof(m_DataSockAddr));
		m_DataSockAddr.sin_family = 2;
		m_DataSockAddr.sin_addr = htonl(0);
		m_DataSockAddr.sin_port = 0;

		if (bind(m_iDataSocket, (struct sockaddr *)&m_DataSockAddr, sizeof(m_DataSockAddr)) < 0)
		{
			return (FTP_FAILED);
		}

		i = sizeof(m_DataSockAddr);
		getsockname(m_iDataSocket, (struct sockaddr *)&m_DataSockAddr, &i);
		listen(m_iDataSocket, 5);

		uTemp = 1;

		if (Use_Non_Blocking_Mode())
		{
			if (ioctlsocket(m_iDataSocket, 0x8004667eL, &uTemp) == -1)
			{
				return (FTP_FAILED);
			}
		}

		m_sendNewPortStatus = 1;
	}

	if (m_sendNewPortStatus == 1)
	{
		memset(command, 0, 256);

		i = MyIPAddress(m_iCommandSocket);

		if (i == FTP_FAILED)
		{
			return (FTP_FAILED);
		}

		sprintf(command, "PORT %d,%d,%d,%d,%d,%d\r\n",
				i & 0xFF,
				(i >> 8) & 0xFF,
				(i >> 16) & 0xFF,
				(i >> 24) & 0xFF,
				m_DataSockAddr.sin_port & 0xFF,
				m_DataSockAddr.sin_port >> 8);

		if (SendCommand(command, strlen(command)) < 0)
		{
			return (FTP_TRYING);
		}

		m_sendNewPortStatus = 2;
	}

	if (m_sendNewPortStatus == 2)
	{
		if ((RecvReply(command, 256, &iReply) != FTP_SUCCEEDED) ||
			(iReply != FTPREPLY_PORTOK))
		{
			return (FTP_TRYING);
		}

		m_sendNewPortStatus = 0;
	}

	return (FTP_SUCCEEDED);
}
