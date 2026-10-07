// cl: /DNDEBUG /MD /EHs-c- /O2 /Ob2
// FTP.CPP: Cftp members retail links from this TU (tu_map approved, Zero Hour
// places them in WWDownload/FTP.CPP), folded from the split units with these
// exact flags. One Cftp view carries every offset they were verified against:
// vptr +0x00, command socket +0x04, data socket +0x08, data sockaddr +0x1C,
// remote path +0x38, remote name +0xB8, local file +0x3B8, status +0x3BC,
// SendNewPort state +0x3C0, find start +0x3C4.
//
// SendCommand is Zero Hour's plain member and the compiler decides where it
// inlines, exactly as retail shows: both LoginToServer sends, the FindFile
// CWD/LIST sends, the GetNextFileBlock TYPE send and the LogoffFromServer QUIT
// send are inlined; the FindFile SIZE send, the later GetNextFileBlock sends
// and SendNewPort's PORT send call the out-of-line copy at 0x006CA040.
// GetNextFileBlock precedes SendNewPort, which it calls, so the call stays a
// call.

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>

typedef long HRESULT;
typedef const char *LPCSTR;

struct sockaddr_in
{
	unsigned short sin_family;
	unsigned short sin_port;
	unsigned long sin_addr;
	unsigned char sin_zero[8];
};

extern "C" int __stdcall closesocket(int s);
extern "C" int __stdcall send(int, const char *, int, int);
extern "C" int __stdcall socket(int domain, int type, int protocol);
extern "C" int __stdcall ioctlsocket(int socketHandle, long command, unsigned long *argument);
extern "C" int __stdcall bind(int socketHandle, const void *address, int addressLength);
extern "C" int __stdcall getsockname(int socketHandle, void *address, int *addressLength);
extern "C" int __stdcall listen(int socketHandle, int backlog);
extern "C" unsigned long __stdcall htonl(unsigned long hostlong);
extern "C" __declspec(dllimport) int __cdecl sprintf(char *buffer, const char *format, ...);
extern "C" __declspec(dllimport) void __stdcall OutputDebugStringA(const char *string);
extern "C" __declspec(dllimport) int __cdecl _chmod(const char *, int);
extern "C" __declspec(dllimport) char *__cdecl _getcwd(char *, int);
extern "C" int __stdcall WSAGetLastError(void);
extern "C" int __stdcall recv(int, char *, int, int);
bool Prepare_Directories(const char *, const char *);
bool Use_Non_Blocking_Mode(void);
unsigned long MyIPAddress(int socketHandle);

enum
{
	FTP_SUCCEEDED = 0,
	FTP_FAILED = 0x80040001,
	FTP_TRYING = 0x80040002,
	FTPREPLY_PORTOK = 200,
	FTPREPLY_TYPEOK = 200,
	FTPREPLY_RESTARTOK = 350,
	FTPREPLY_OPENBINARY = 150,
	FTPREPLY_CONTROLCLOSED = 421,
	FTPSTAT_FILEFOUND = 100,
	FTPSTAT_FILEOPEN = 180,
	FTPSTAT_SENTFILEPORT = 190,
	FTPSTAT_SENDINGTYPE = 200,
	FTPSTAT_SENTTYPE = 210,
	FTPSTAT_SENDINGREST = 220,
	FTPSTAT_SENTREST = 230,
	FTPSTAT_SENDINGRETR = 240,
	FTPSTAT_SENTRETR = 250,
	FTPSTAT_FILEDATAOPEN = 260,
	FTPSTAT_FILEDATACLOSED = 270,
	FTPSTAT_TRANSFERREPLY = 280,
	FTPSTAT_INIT = 0,
	FTPSTAT_CONNECTED = 20,
	FTPSTAT_SENDINGUSER = 30,
	FTPSTAT_SENTUSER = 40,
	FTPSTAT_SENDINGPASS = 50,
	FTPSTAT_LOGGEDIN = 60,
	FTPSTAT_SENDINGCWD = 110,
	FTPSTAT_SENTCWD = 120,
	FTPSTAT_SENTPORT = 130,
	FTPSTAT_SENDINGLIST = 140,
	FTPSTAT_SENTLIST = 150,
	FTPSTAT_LISTDATAOPEN = 160,
	FTPSTAT_LISTDATARECVD = 170,
	FTPSTAT_SENDINGSIZE = 171,
	FTPSTAT_SENTSIZE = 172,
	FTPREPLY_LOGGEDIN = 230,
	FTPREPLY_CWDOK = 250,
	FTPREPLY_PASSWORD = 331,
	FTPREPLY_OPENASCII = 150,
	FTPREPLY_COMPLETE = 226,
	FTPREPLY_FILESTATUS = 213
};

class Rva00885390Class
{
public:
	void d_00885390(void);
};

class Rva00885920Class
{
public:
	int d_00885920(void);
};

class Rva00885980Class
{
public:
	void d_00885960(void);
};

class Rva008859D0Class
{
public:
	void d_008859d0(const char *, char *);
};

#pragma comment(linker, "/alternatename:?RecvReply@Cftp@@QAEJPBDHPAH@Z=?d_00885570@@YAXXZ")

class Cftp
{
public:
	virtual ~Cftp();
	HRESULT RecvReply(const char *reply, int size, int *replyCode);
	HRESULT DisconnectFromServer();
	int SendNewPort(void);
	HRESULT GetNextFileBlock(LPCSTR, int *);
	HRESULT LoginToServer(LPCSTR szUserName, LPCSTR szPassword);
	HRESULT LogoffFromServer(void);
	HRESULT FindFile(LPCSTR szRemoteFileName, int *piSize);
	void ZeroStuff(void);

private:
	HRESULT SendCommand(const char *command, int size);
	void CloseSockets(void);

	int m_iCommandSocket;			// +0x04
	int m_iDataSocket;			// +0x08
	unsigned char m_CommandSockAddr[16];	// +0x0C
	sockaddr_in m_DataSockAddr;		// +0x1C
	int m_iFilePos;
	int m_iBytesRead;
	int m_iFileSize;
	char m_szRemoteFilePath[128];		// +0x38
	char m_szRemoteFileName[128];		// +0xB8
	char m_szLocalFilePath[128];
	char m_szLocalFileName[128];
	char m_szServerName[128];
	char m_szUserName[128];
	char m_szPassword[128];
	FILE *m_pfLocalFile;			// +0x3B8
	int m_iStatus;				// +0x3BC
	int m_sendNewPortStatus;		// +0x3C0
	int m_findStart;			// +0x3C4
};

#pragma intrinsic(strlen)

// Cftp::LoginToServer, retail 0x006CA8A0 (464 bytes). Zero Hour's body
// verbatim; both SendCommand calls inline.
HRESULT Cftp::LoginToServer(LPCSTR szUserName, LPCSTR szPassword)
{
	char command[256];
	int iReply;

	strncpy(m_szUserName, szUserName, 128);
	strncpy(m_szPassword, szPassword, 128);

	memset(command, 0, 256);

	if (m_iStatus == FTPSTAT_CONNECTED)
	{
		sprintf(command, "USER %s\r\n", m_szUserName);

		if (SendCommand(command, 7 + strlen(m_szUserName)) < 0)
		{
			return FTP_TRYING;
		}

		m_iStatus = FTPSTAT_SENDINGUSER;
	}

	if (m_iStatus == FTPSTAT_SENDINGUSER)
	{
		if (RecvReply(command, 256, &iReply) != FTP_SUCCEEDED)
			return FTP_TRYING;

		if (iReply != FTPREPLY_PASSWORD)
			return FTP_FAILED;

		m_iStatus = FTPSTAT_SENTUSER;
	}

	if (m_iStatus == FTPSTAT_SENTUSER)
	{
		sprintf(command, "PASS %s\r\n", m_szPassword);

		if (SendCommand(command, 7 + strlen(m_szPassword)) < 0)
		{
			return FTP_TRYING;
		}

		m_iStatus = FTPSTAT_SENDINGPASS;
	}

	if (m_iStatus == FTPSTAT_SENDINGPASS)
	{
		if (RecvReply(command, 256, &iReply) != FTP_SUCCEEDED)
		{
			return FTP_TRYING;
		}

		if (iReply != FTPREPLY_LOGGEDIN)
		{
			if (iReply == FTPREPLY_CONTROLCLOSED)
			{
				return FTP_FAILED;
			}

			return FTP_TRYING;
		}

		m_iStatus = FTPSTAT_LOGGEDIN;
		return FTP_SUCCEEDED;
	}

	return FTP_FAILED;
}

// The size the server reported for the file FindFile last located, -1 when
// the SIZE request failed (.data 0x00DDC014, initialised -1).
static int s_iRemoteFileSize = -1;

// Cftp::FindFile, retail 0x006CAB30 (1273 bytes). Zero Hour's state machine
// (CWD, PORT, LIST, list data, transfer reply) with BFME2's additions read from
// the retail bytes: once the listing is complete the data connection is closed
// and a SIZE request (states 171/172, "SIZE %s\r\n" at 0x00CE8A64) asks for
// the exact size; a 213 reply parsed by "%d %ld " is preferred over the size
// column of the listing line. The listing line is the function-local static
// at 0x00E0C798. iCode holds the listing length and then the SIZE reply's
// leading code; sharing one address-taken slot is why retail stores the
// length to the stack.
HRESULT Cftp::FindFile(LPCSTR szRemoteFileName, int *piSize)
{
	char command[256];
	static char listline[256];
	int i, iReply, iCode;
	char ext[10];

	if (m_findStart == 0)
		m_findStart = time(NULL);

	if ((time(NULL) - m_findStart) > 30)  // try for 30 seconds
	{
		m_findStart = 0;
		return FTP_FAILED;
	}

	_splitpath(szRemoteFileName, NULL, m_szRemoteFilePath + strlen(m_szRemoteFilePath),
		m_szRemoteFileName, ext);

	strcat(m_szRemoteFileName, ext);

	for (i = 0; i < (int)strlen(m_szRemoteFilePath); i++)
	{
		if (m_szRemoteFilePath[i] == '\\')
		{
			m_szRemoteFilePath[i] = '/';
		}
	}

	memset(command, 0, 256);

	/* Change directory */

	if ((m_iStatus == FTPSTAT_LOGGEDIN) || (m_iStatus == FTPSTAT_FILEFOUND))
	{
		sprintf(command, "CWD %s\r\n", m_szRemoteFilePath);

		if (SendCommand(command, 6 + strlen(m_szRemoteFilePath)) < 0)
		{
			return FTP_TRYING;
		}

		m_iStatus = FTPSTAT_SENDINGCWD;
	}

	/* Get reply */

	if (m_iStatus == FTPSTAT_SENDINGCWD)
	{
		HRESULT reply = RecvReply(command, 256, &iReply);

		if ((reply == FTP_SUCCEEDED) && (iReply == 550))
		{
			m_findStart = 0;
			return FTP_FAILED;
		}

		if ((reply != FTP_SUCCEEDED) || (iReply != FTPREPLY_CWDOK))
		{
			return FTP_TRYING;
		}

		m_iStatus = FTPSTAT_SENTCWD;
	}

	/* Set up data connection port */

	if (m_iStatus == FTPSTAT_SENTCWD)
	{
		i = 0;
		while (SendNewPort() == FTP_TRYING)
		{
			i++;

			if (i == 1000)
			{
				return FTP_TRYING;
			}
		}

		m_iStatus = FTPSTAT_SENTPORT;
	}

	/* Get directory listing for file. */

	if (m_iStatus == FTPSTAT_SENTPORT)
	{
		sprintf(command, "LIST %s\r\n", m_szRemoteFileName);

		if (SendCommand(command, 7 + strlen(m_szRemoteFileName)) < 0)
		{
			return FTP_TRYING;
		}

		m_iStatus = FTPSTAT_SENDINGLIST;
	}

	/* Get reply */

	if (m_iStatus == FTPSTAT_SENDINGLIST)
	{
		if ((RecvReply(command, 256, &iReply) != FTP_SUCCEEDED) ||
			(iReply != FTPREPLY_OPENASCII))
		{
			return FTP_TRYING;
		}

		m_iStatus = FTPSTAT_SENTLIST;
	}

	/* Open data connection */

	if (m_iStatus == FTPSTAT_SENTLIST)
	{
		i = ((Rva00885920Class *)this)->d_00885920();
		if (i != FTP_SUCCEEDED)
		{
			m_findStart = 0;
			return i;
		}
		m_iStatus = FTPSTAT_LISTDATAOPEN;
		memset(listline, 0, 256);
	}

	/* Get data */

	if (m_iStatus == FTPSTAT_LISTDATAOPEN)
	{
		recv(m_iDataSocket, listline, 256, 0);

		iCode = strlen(listline);
		if (iCode == 0)
		{
			return FTP_TRYING;
		}
		m_iStatus = FTPSTAT_LISTDATARECVD;
	}

	/* Wait for confirmation of end of data stream */

	if (m_iStatus == FTPSTAT_LISTDATARECVD)
	{
		if ((RecvReply(command, 256, &iReply) != FTP_SUCCEEDED) ||
			(iReply != FTPREPLY_COMPLETE))
		{
			return FTP_TRYING;
		}

		m_iStatus = FTPSTAT_SENDINGSIZE;
		((Rva00885980Class *)this)->d_00885960();
	}

	/* Ask for the exact size */

	if (m_iStatus == FTPSTAT_SENDINGSIZE)
	{
		sprintf(command, "SIZE %s\r\n", m_szRemoteFileName);

		if (SendCommand(command, 7 + strlen(m_szRemoteFileName)) < 0)
		{
			return FTP_TRYING;
		}

		m_iStatus = FTPSTAT_SENTSIZE;
	}

	if (m_iStatus == FTPSTAT_SENTSIZE)
	{
		if (RecvReply(command, 256, &iReply) == FTP_SUCCEEDED)
		{
			s_iRemoteFileSize = -1;
			if (iReply == FTPREPLY_FILESTATUS)
			{
				if (sscanf(command, "%d %ld ", &iCode, &s_iRemoteFileSize) != 2)
					s_iRemoteFileSize = -1;
			}
		}
		m_iStatus = FTPSTAT_FILEFOUND;
	}

	m_findStart = 0;

	/* Is the file there? */

	if (strncmp(listline, m_szRemoteFileName, sizeof(m_szRemoteFileName)) == 0)
	{
		/* No */
		return FTP_FAILED;
	}

	/* Yes - find out the size, in bytes */

	if (s_iRemoteFileSize >= 0)
	{
		if (piSize != NULL)
		{
			*piSize = s_iRemoteFileSize;
			m_iFileSize = s_iRemoteFileSize;
		}
		return FTP_SUCCEEDED;
	}

	if (sscanf(&listline[32], " %d ", &i) == 1)
	{
		if (piSize != NULL)
		{
			*piSize = i;
			m_iFileSize = i;
		}
		return FTP_SUCCEEDED;
	}

	return FTP_FAILED;
}

// Cftp::SendCommand, retail 0x006CA040 (59 bytes). Zero Hour's body with the
// debug-output pair compiled in: OutputDebugStringA "-->" (0x00CE89FC) then
// the command.
HRESULT Cftp::SendCommand(const char *pCommand, int iSize)
{
	int i;

	i = send(m_iCommandSocket, pCommand, iSize, 0);
	if (i > 0)
	{
		OutputDebugStringA("-->");
		OutputDebugStringA(pCommand);
		return FTP_SUCCEEDED;
	}
	else
	{
		return FTP_FAILED;
	}
}

// Cftp::GetNextFileBlock, retail 0x006CB030 (1267 bytes).
// BFME1 donor Code/Libraries/Source/WWVegas/WWDownload/CftpGetNextFileBlock.cpp
// with BFME2 repairs: send/recv/WSAGetLastError ride the ILT (plain extern,
// retail calls them direct). The TYPE send goes through SendCommand as in
// Zero Hour; retail inlines that one and calls the rest. Every other member
// callee is rowed under the spelling declared here.
// ?GetNextFileBlock@Cftp@@QAEJPBDPAH@Z
HRESULT Cftp::GetNextFileBlock(LPCSTR szLocalFileName, int *piTotalRead)
{
	char command[256];
	int read, totread = 0;
	const int max_data_len = 10240;
	char data[max_data_len];
	int res, iReply;
	char downloadfilename[256];

	((Rva008859D0Class *)this)->d_008859d0(szLocalFileName, downloadfilename);
	strncpy(m_szLocalFileName, szLocalFileName, 256);

	if (m_iStatus == FTPSTAT_FILEFOUND)
	{
		if (m_iFilePos == 0)
		{
			if ((m_pfLocalFile = fopen(downloadfilename, "wb")) == 0)
				return FTP_FAILED;
		}
		else
		{
			if ((m_pfLocalFile = fopen(downloadfilename, "ab")) == 0)
				return FTP_FAILED;
		}
		m_iStatus = FTPSTAT_FILEOPEN;
	}

	if (m_iStatus == FTPSTAT_FILEOPEN)
	{
		if (((Cftp *)this)->SendNewPort() == FTP_SUCCEEDED)
			m_iStatus = FTPSTAT_SENTFILEPORT;
		else
			return FTP_TRYING;
	}

	if (m_iStatus == FTPSTAT_SENTFILEPORT)
	{
		sprintf(command, "TYPE I\r\n");
		if (SendCommand(command, strlen(command)) < 0)
			return FTP_TRYING;
		m_iStatus = FTPSTAT_SENDINGTYPE;
	}

	if (m_iStatus == FTPSTAT_SENDINGTYPE)
	{
		if ((((Cftp *)this)->RecvReply(command, 256, &iReply) != FTP_SUCCEEDED) ||
			(iReply != FTPREPLY_TYPEOK))
			return FTP_TRYING;
		m_iStatus = FTPSTAT_SENTTYPE;
	}

	if (m_iStatus == FTPSTAT_SENTTYPE)
	{
		if (m_iFilePos == 0)
			m_iStatus = FTPSTAT_SENTREST;
		else
		{
			sprintf(command, "REST %d\r\n", m_iFilePos);
			if (SendCommand(command, strlen(command)) < 0)
				return FTP_TRYING;
			m_iStatus = FTPSTAT_SENDINGREST;
		}
	}

	if (m_iStatus == FTPSTAT_SENDINGREST)
	{
		res = ((Cftp *)this)->RecvReply(command, 256, &iReply);
		if ((res == FTP_FAILED) || (iReply == 502))
		{
			m_iFilePos = 0;
			fclose(m_pfLocalFile);
			m_pfLocalFile = fopen(downloadfilename, "wb");
		}
		else if ((res != FTP_SUCCEEDED) || (iReply != FTPREPLY_RESTARTOK))
			return FTP_TRYING;
		m_iStatus = FTPSTAT_SENTREST;
	}

	if (m_iStatus == FTPSTAT_SENTREST)
	{
		sprintf(command, "RETR %s\r\n", m_szRemoteFileName);
		if (SendCommand(command, strlen(command)) < 0)
			return FTP_TRYING;
		m_iStatus = FTPSTAT_SENDINGRETR;
	}

	if (m_iStatus == FTPSTAT_SENDINGRETR)
	{
		if ((((Cftp *)this)->RecvReply(command, 256, &iReply) != FTP_SUCCEEDED) ||
			(iReply != FTPREPLY_OPENBINARY))
			return FTP_TRYING;
		m_iStatus = FTPSTAT_SENTRETR;
	}

	if (m_iStatus == FTPSTAT_SENTRETR)
	{
		res = ((Rva00885920Class *)this)->d_00885920();
		if (res != FTP_SUCCEEDED)
			return res;
		m_iStatus = FTPSTAT_FILEDATAOPEN;
	}

	if (m_iStatus == FTPSTAT_FILEDATAOPEN)
	{
		do
		{
			read = recv(m_iDataSocket, data, max_data_len, 0);
			if (read > 0)
			{
				fwrite(data, 1, read, m_pfLocalFile);
				totread += read;
			}
		}
		while ((read > 0) && (totread < (max_data_len * 20)));

		m_iFilePos += totread;
		if (piTotalRead != 0)
			*piTotalRead = m_iFilePos;

		if (read < 0)
		{
			int wsa_err = WSAGetLastError();
			if ((wsa_err == 10054) || (wsa_err == 10057))
				read = 0;
		}

		if (read == 0)
		{
			if (m_iFilePos != m_iFileSize)
				return FTP_FAILED;
			m_iStatus = FTPSTAT_FILEDATACLOSED;
		}
		else
			return FTP_TRYING;
	}

	if (m_iStatus == FTPSTAT_FILEDATACLOSED)
	{
		((Rva00885980Class *)this)->d_00885960();
		fclose(m_pfLocalFile);
		m_pfLocalFile = 0;

		char downloadfilename[256];
		((Rva008859D0Class *)this)->d_008859d0(m_szLocalFileName, downloadfilename);

		char curdir[256];
		_getcwd(curdir, 256);
		Prepare_Directories(curdir, m_szLocalFileName);

		if (rename(downloadfilename, m_szLocalFileName) != 0)
		{
			_chmod(m_szLocalFileName, 0x180);
			remove(m_szLocalFileName);
			if (rename(downloadfilename, m_szLocalFileName) != 0)
				return FTP_FAILED;
		}

		SendCommand("BOGUSCOMMAND\r\n", strlen("BOGUSCOMMAND\r\n"));
		OutputDebugStringA("File closed, waiting for response.\n");
		m_iStatus = FTPSTAT_TRANSFERREPLY;
	}

	if (m_iStatus == FTPSTAT_TRANSFERREPLY)
	{
		iReply = 0;
		if (((Cftp *)this)->RecvReply(command, 256, &iReply) != FTP_SUCCEEDED)
			return FTP_TRYING;
		if (iReply == FTPREPLY_CONTROLCLOSED)
		{
			m_iStatus = FTPSTAT_INIT;
			m_iFilePos = 0;
			((Rva00885390Class *)this)->d_00885390();
		}
		else
		{
			m_iStatus = FTPSTAT_LOGGEDIN;
			m_iFilePos = 0;
		}
		return FTP_SUCCEEDED;
	}
	return FTP_FAILED;
}

// WWDownload FTP.CPP Cftp::SendNewPort, retail 0x006CA250 (480 bytes).
// BFME1 donor (same file) with BFME2 repairs: self-contained TU in the
// CftpRecvReply.cpp style (no PreRTS.h, no vptr: retail's Cftp lays
// m_iCommandSocket at +4); the PORT format is retail's own .rdata string;
// SendCommand is the private Cftp member defined above (0x006CA040);
// socket-family imports ride the ILT
// (plain extern) while sprintf goes through the IAT.
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

// Cftp::DisconnectFromServer, retail 0x006CA490 (12 bytes).
// Ported from the Zero Hour reference (Libraries/Source/WWVegas/WWDownload/FTP.CPP):
// closes the command socket, returns FTP_SUCCEEDED. m_iCommandSocket sits
// at +4 (retail displacement, matching the Zero Hour layout where it is the
// first member after the vptr). closesocket rides the ILT through the
// _closesocket@4 thunk pin (plain extern, no dllimport).
HRESULT Cftp::DisconnectFromServer()
{
	closesocket(m_iCommandSocket);
	return FTP_SUCCEEDED;
}

// WWDownload FTP.CPP Cftp::LogoffFromServer, retail 0x006CAA70, 183 bytes.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/GameNetwork/CftpLogoffFromServer.cpp):
// verbatim except the debug-output pair. BFME1 reads a callback cell out of
// a data global (0x01358EA8) and invokes it with two string addresses;
// retail's QUIT goes through Zero Hour's SendCommand, inlined here, whose
// kernel32!OutputDebugStringA (IAT 0xBBA19C) pair prints "-->" then the
// command. send rides the ILT (plain extern, pin _send@16 at 0x0065568E);
// RecvReply/d_00885390/ZeroStuff resolve by row.
HRESULT Cftp::LogoffFromServer(void)
{
	char reply[50];
	int retCode;

	switch (m_iStatus)
	{
	case 70:
		if (SendCommand("QUIT\r\n", 6) == FTP_SUCCEEDED)
		{
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
