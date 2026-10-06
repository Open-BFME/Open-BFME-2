// cl: /DNDEBUG /MD /EHs-c- /Ob2 /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas
// Cftp::RecvReply, retail 0x006CA080 (268 bytes).
// Ported from the Zero Hour reference (Libraries/Source/WWVegas/WWDownload/FTP.CPP).
// One BFME2 repair: the _DEBUG OutputDebugString pair ("<--" and the line)
// is unconditional in retail, so the #ifdef is dropped; with /O2 the two
// calls share one IAT load in edi, matching retail's call-edi pair.
// recv and WSAGetLastError ride the ILT (plain extern, no dllimport);
// strstr, _strnicmp, isdigit, atol and OutputDebugStringA go through the
// IAT (dllimport). m_iCommandSocket sits at +4 (retail displacement).
// Dedicated TU so CftpAsyncGetHostByName.cpp keeps its matched
// AsyncGetHostByName (pattern five).

typedef long HRESULT;
typedef const char *LPCSTR;
typedef unsigned int SOCKET;

#define FTP_SUCCEEDED 0
#define FTP_FAILED 0x80040001
#define FTP_TRYING 0x80040002
#define FTPREPLY_CONTROLCLOSED 421
#define MSG_PEEK 2
#define WSAECONNRESET 10054
#define WSAENOTCONN 10057

extern "C" __declspec(dllimport) char *__cdecl strstr(const char *string, const char *substring);
extern "C" __declspec(dllimport) int __cdecl _strnicmp(const char *a, const char *b, unsigned int count);
extern "C" __declspec(dllimport) int __cdecl isdigit(int c);
extern "C" __declspec(dllimport) long __cdecl atol(const char *string);
extern "C" __declspec(dllimport) void __stdcall OutputDebugStringA(const char *string);
extern "C" unsigned int __stdcall strlen(const char *string);
extern "C" int __stdcall recv(SOCKET socketHandle, char *buffer, int length, int flags);
extern "C" int __stdcall WSAGetLastError(void);

class Cftp
{
public:
	HRESULT RecvReply(LPCSTR replyBuffer, int size, int *replyCode);

private:
	int m_pad0;
	int m_iCommandSocket;
};

HRESULT Cftp::RecvReply(LPCSTR pReplyBuffer, int iSize, int *piRetCode)
{
	int readval;
	char *pc = (char *)pReplyBuffer;

	while (1) {
		readval = recv(m_iCommandSocket, pc, iSize - 1, MSG_PEEK);
		pc[iSize - 1] = 0;
		if (readval > 0)
			pc[readval] = 0;

		if (readval < 0) {
			if ((WSAGetLastError() == WSAECONNRESET) || ((WSAGetLastError() == WSAENOTCONN)))
				readval = 0;
			else {
				return FTP_TRYING;
			}
		}

		if (readval == 0) {
			*piRetCode = FTPREPLY_CONTROLCLOSED;
			return FTP_SUCCEEDED;
		}

		if (readval < 3)
			return FTP_TRYING;

		char *end = strstr(pc, "\r\n");
		if (end == 0)
			return FTP_TRYING;

		recv(m_iCommandSocket, pc, end - pc + strlen("\r\n"), 0);
		OutputDebugStringA("<--");
		OutputDebugStringA(pc);

		const char *BOGUS_RESPONSE = "500";
		if (_strnicmp(pc, BOGUS_RESPONSE, strlen(BOGUS_RESPONSE)) == 0)
			continue;

		if (isdigit(pc[0]) == 0)
			continue;

		if (piRetCode)
			*piRetCode = atol(pc);

		return FTP_SUCCEEDED;
	}
}
