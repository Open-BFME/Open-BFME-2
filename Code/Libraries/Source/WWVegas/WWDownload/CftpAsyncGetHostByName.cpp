// cl: /DNDEBUG /MD /EHs-c- /Ob2 /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas
// Cftp::AsyncGetHostByName, retail 0x006C9F90 (165 bytes).
// Ported from the Zero Hour reference (Libraries/Source/WWVegas/WWDownload/FTP.CPP):
// a stat flag plus a worker thread resolving the name in the background,
// with the result copied out once the thread sets its done flag.
// Dedicated TU so CftpConnectToServer.cpp keeps its matched ConnectToServer:
// defining this beside that caller would let MSVC see the callee and change
// the caller's register save set (docs/matching.md pattern five).

typedef unsigned long DWORD;
typedef int BOOL;
#define NULL 0
#define AF_INET 2

#define FTP_SUCCEEDED 0
#define FTP_FAILED 0x80040001
#define FTP_TRYING 0x80040002

struct in_addr
{
	union
	{
		unsigned long S_addr;
	} S_un;
};

#define s_addr S_un.S_addr

struct sockaddr_in
{
	short sin_family;
	unsigned short sin_port;
	in_addr sin_addr;
	char sin_zero[8];
};

struct HOSTENT
{
	char *h_name;
	char **h_aliases;
	short h_addrtype;
	short h_length;
	char **h_addr_list;
};

#define h_addr h_addr_list[0]

extern "C" void *__cdecl memset(void *destination, int value, unsigned int count);
#pragma intrinsic(memset)
extern "C" __declspec(dllimport) void *__cdecl memcpy(void *destination, const void *source, unsigned int count);
extern "C" __declspec(dllimport) unsigned int __cdecl strlen(const char *string);
extern "C" __declspec(dllimport) HOSTENT *__stdcall gethostbyname(const char *name);
extern "C" __declspec(dllimport) void *__stdcall CreateThread(void *threadAttributes, unsigned long stackSize, DWORD (__stdcall *startAddress)(void *), void *parameter, unsigned long creationFlags, unsigned long *threadId);

struct sockaddr_in gThreadAddress;
static int gThreadFlag;

DWORD __stdcall gethostbynameA(void *szName)
{
	HOSTENT *hostEntry = gethostbyname((const char *)szName);

	if (hostEntry)
		memcpy((char *)&(gThreadAddress.sin_addr), hostEntry->h_addr, hostEntry->h_length);
	else
		memcpy((char *)&(gThreadAddress.sin_addr), "", strlen("") + 1);

	gThreadFlag = 1;
	return 0;
}

class Cftp
{
public:
	int AsyncGetHostByName(char *name, sockaddr_in &address);
};

int Cftp::AsyncGetHostByName(char *name, sockaddr_in &address)
{
	static int stat = 0;
	static unsigned long threadId;

	if (stat == 0)
	{
		gThreadFlag = 0;
		memset(&gThreadAddress, 0, sizeof(gThreadAddress));

		if (CreateThread(NULL, 0, gethostbynameA, name, 0, &threadId) == NULL)
		{
			return FTP_FAILED;
		}
		stat = 1;
	}
	if (stat == 1)
	{
		if (gThreadFlag)
		{
			address = gThreadAddress;
			address.sin_family = AF_INET;
			stat = 0;
			return FTP_SUCCEEDED;
		}
	}

	return FTP_TRYING;
}
