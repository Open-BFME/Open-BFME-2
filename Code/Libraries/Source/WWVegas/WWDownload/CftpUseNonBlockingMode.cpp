// cl: /DNDEBUG /MD /EHs-c- /Ob2 /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas
// Use_Non_Blocking_Mode, retail 0x006C9E00 (154 bytes).
// Ported from the Zero Hour reference (Libraries/Source/WWVegas/WWDownload/FTP.CPP):
// a registry hack for firewalls that break non-blocking sockets; defaults to
// TRUE when the key or DWORD is missing. Three advapi32 imports verify.
// Dedicated TU so CftpConnectToServer.cpp keeps its matched ConnectToServer
// (pattern five); the existing symbols.csv pin already names this address.

typedef void *HKEY;
typedef long LONG;
typedef unsigned long DWORD;
typedef unsigned char BYTE;

#define HKEY_LOCAL_MACHINE ((HKEY)0x80000002)
#define KEY_READ 0x20019
#define ERROR_SUCCESS 0
#define REG_DWORD 4
#define TRUE 1

extern "C" __declspec(dllimport) LONG __stdcall RegOpenKeyExA(HKEY key, const char *subKey, DWORD reserved, DWORD access, HKEY *result);
extern "C" __declspec(dllimport) LONG __stdcall RegQueryValueExA(HKEY key, const char *valueName, DWORD *reserved, DWORD *type, BYTE *data, DWORD *dataSize);
extern "C" __declspec(dllimport) LONG __stdcall RegCloseKey(HKEY key);

bool Use_Non_Blocking_Mode(void)
{
	HKEY regKey;
	LONG regRetval;
	DWORD bufSize = 0;
	DWORD valueType = 0;
	DWORD valueData = 0;

	regRetval = RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\Westwood\\Earth And Beyond Beta 2", 0, KEY_READ, &regKey);
	if (regRetval != ERROR_SUCCESS)
		return TRUE;

	bufSize = sizeof(valueData);
	valueType = REG_DWORD;
	regRetval = RegQueryValueExA(regKey, "UseNonBlockingFTP", 0, &valueType, (BYTE *)&valueData, &bufSize);

	RegCloseKey(regKey);

	if ((regRetval != ERROR_SUCCESS) || (valueType != REG_DWORD))
		return TRUE;

	return valueData != 0;
}
