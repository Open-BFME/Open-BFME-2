// cl: /Os /Oy- /Oi- /DNDEBUG /MD /EHsc
// Native 12C889..12C907,126B cdecl bool(constwide*) launcher. The verified
// 12C907 texture builder launcher is the local semantic and import lead;
// native uses assetCacheBuilder.exe and returns success after wait/close,
// without checking the process exit code. Name remains address-derived.
typedef unsigned long DWORD;

struct STARTUPINFOW
{
	DWORD cb;
	unsigned char m_rest[0x40];
};

struct PROCESS_INFORMATION
{
	void *hProcess;
	void *hThread;
	DWORD dwProcessId;
	DWORD dwThreadId;
};

extern "C" void *__cdecl memset(void *, int, unsigned int);

extern "C" __declspec(dllimport) unsigned short *__cdecl wcscpy(unsigned short *dst, const unsigned short *src);
extern "C" __declspec(dllimport) int __stdcall CreateProcessW(
	const unsigned short *application, unsigned short *commandLine,
	void *processAttributes, void *threadAttributes, int inheritHandles, DWORD creationFlags,
	void *environment, const unsigned short *currentDirectory, STARTUPINFOW *startupInfo,
	PROCESS_INFORMATION *processInformation);
extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(void *handle, unsigned long timeout);
extern "C" __declspec(dllimport) int __stdcall CloseHandle(void *handle);


bool __cdecl Rva0012C889(const unsigned short *currentDirectory)
{
 STARTUPINFOW startup;
 unsigned short command[260];
 PROCESS_INFORMATION info;
 memset(&startup,0,sizeof(startup));
 startup.cb=sizeof(startup);
 wcscpy(command,L"assetCacheBuilder.exe");
 if(CreateProcessW(0,command,0,0,0,0x8000000,0,currentDirectory,&startup,&info)){
  WaitForSingleObject(info.hProcess,0xFFFFFFFF);
  CloseHandle(info.hProcess);CloseHandle(info.hThread);return true;
 }
 return false;
}
