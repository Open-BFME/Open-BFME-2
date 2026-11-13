// cl: /Os /Oy- /Oi- /DNDEBUG /MD /EHsc
// Native 12C889..12C907,126B cdecl bool(constwide*) launcher. The verified
// 12C907 texture builder launcher is the local semantic and import lead;
// native uses assetCacheBuilder.exe and returns success after wait/close,
// without checking the process exit code. Name remains address-derived.
#include <string.h>
typedef unsigned long DWORD;

struct STARTUPINFOW
{
	DWORD cb;
	unsigned char m_rest[0x40];
};

#include "../../../../GameEngine/Include/Common/PROCESS_INFORMATION.h"


extern "C" __declspec(dllimport) int __stdcall CreateProcessW(
	const unsigned short *application, unsigned short *commandLine,
	void *processAttributes, void *threadAttributes, int inheritHandles, DWORD creationFlags,
	void *environment, const unsigned short *currentDirectory, STARTUPINFOW *startupInfo,
	PROCESS_INFORMATION *processInformation);
extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(void *handle, unsigned long timeout);
extern "C" __declspec(dllimport) int __stdcall CloseHandle(void *handle);


// WorldBuilder ExecuteAssetCacheBuilder, WB VA 0x009D6AA0 (imports,strings lead, score 1.1).
bool __cdecl ExecuteAssetCacheBuilder(const unsigned short *currentDirectory)
{
 STARTUPINFOW startupInfo;
 unsigned short commandLine[260];
 PROCESS_INFORMATION processInfo;
 memset(&startupInfo,0,sizeof(startupInfo));
 startupInfo.cb=sizeof(startupInfo);
 wcscpy(commandLine,L"assetCacheBuilder.exe");
 if(CreateProcessW(0,commandLine,0,0,0,0x8000000,0,currentDirectory,&startupInfo,&processInfo)){
  WaitForSingleObject(processInfo.hProcess,0xFFFFFFFF);
  CloseHandle(processInfo.hProcess);CloseHandle(processInfo.hThread);return true;
 }
 return false;
}
