// cl: /DNDEBUG /MD /EHsc
//
// ?Rva0012C99DRun@@YA_NXZ, retail 0x0012C99D, 148 bytes.
// Launch the wide command line at VA 0x00BD2354 with CREATE_NO_WINDOW,
// wait for it and succeed when its exit code is 0. Evidence: retail pushes
// 0x44/STARTUPINFOW size, wcscpy from 0x00BD2354, CreateProcessW with
// 0x8000000, WaitForSingleObject(-1), GetExitCodeProcess, CloseHandle x2;
// caller at 0x0012CFE9 in 0x0012CFA0.

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

void *__cdecl ji_006291ae(void *dest, int val, unsigned int count);
#pragma comment(linker, "/alternatename:?ji_006291ae@@YAPAXPAXHI@Z=?ji_006291ae@@YAXXZ")

extern "C" __declspec(dllimport) unsigned short *__cdecl wcscpy(unsigned short *dst, const unsigned short *src);
extern "C" __declspec(dllimport) int __stdcall CreateProcessW(
	const unsigned short *application, unsigned short *commandLine,
	void *processAttributes, void *threadAttributes, int inheritHandles, DWORD creationFlags,
	void *environment, const unsigned short *currentDirectory, STARTUPINFOW *startupInfo,
	PROCESS_INFORMATION *processInformation);
extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(void *handle, unsigned long timeout);
extern "C" __declspec(dllimport) int __stdcall GetExitCodeProcess(void *process, DWORD *exitCode);
extern "C" __declspec(dllimport) int __stdcall CloseHandle(void *handle);


bool __cdecl Rva0012C99DRun()
{
	STARTUPINFOW startup;
	unsigned short command[260];
	PROCESS_INFORMATION info;
	DWORD exitCode;
	bool ok = false;

	ji_006291ae(&startup, 0, sizeof(startup));
	startup.cb = sizeof(startup);
	wcscpy(command, L"ShaderAssetBuilder.exe");
	if (CreateProcessW(0, command, 0, 0, 0, 0x8000000, 0, 0, &startup, &info)) {
		WaitForSingleObject(info.hProcess, 0xFFFFFFFF);
		if (!GetExitCodeProcess(info.hProcess, &exitCode) || exitCode == 0)
			ok = true;
		CloseHandle(info.hProcess);
		CloseHandle(info.hThread);
		return ok;
	}
	return false;
}

bool __cdecl Rva0012C907Run(const unsigned short *currentDirectory)
{
	STARTUPINFOW startup;
	unsigned short command[260];
	PROCESS_INFORMATION info;
	DWORD exitCode;
	bool ok = false;

	ji_006291ae(&startup, 0, sizeof(startup));
	startup.cb = sizeof(startup);
	wcscpy(command, L"TextureAssetBuilder.exe");
	if (CreateProcessW(0, command, 0, 0, 0, 0x8000000, 0, currentDirectory, &startup, &info)) {
		WaitForSingleObject(info.hProcess, 0xFFFFFFFF);
		if (!GetExitCodeProcess(info.hProcess, &exitCode) || exitCode == 0)
			ok = true;
		CloseHandle(info.hProcess);
		CloseHandle(info.hThread);
		return ok;
	}
	return false;
}
