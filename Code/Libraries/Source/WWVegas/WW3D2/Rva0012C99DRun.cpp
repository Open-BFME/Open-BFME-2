// cl: /DNDEBUG /MD /EHsc
// platformsdk
//
// ?RunShaderAssetBuilder@@YA_NXZ, retail 0x0012C99D, 148 bytes.
// Launch the wide command line at VA 0x00BD2354 with CREATE_NO_WINDOW,
// wait for it and succeed when its exit code is 0. Evidence: retail pushes
// 0x44/STARTUPINFOW size, wcscpy from 0x00BD2354, CreateProcessW with
// 0x8000000, WaitForSingleObject(-1), GetExitCodeProcess, CloseHandle x2;
// caller at 0x0012CFE9 in 0x0012CFA0.

#include <windows.h>

// memset is msvcr71's, called through its import thunk at 0x006291AE
// rather than expanded inline: <string.h>'s memset with
// #pragma function(memset).
#include <string.h>
#pragma function(memset)


// WorldBuilder RunShaderAssetBuilder, WB VA 0x009D6E10 (imports,strings lead, score 1.2).
bool __cdecl RunShaderAssetBuilder()
{
	STARTUPINFOW startup;
	WCHAR command[260];
	PROCESS_INFORMATION info;
	DWORD exitCode;
	bool ok = false;

	memset(&startup, 0, sizeof(startup));
	startup.cb = sizeof(startup);
	wcscpy(command, L"ShaderAssetBuilder.exe");
	if (CreateProcessW(0, command, 0, 0, 0, CREATE_NO_WINDOW, 0, 0, &startup, &info)) {
		WaitForSingleObject(info.hProcess, INFINITE);
		if (!GetExitCodeProcess(info.hProcess, &exitCode) || exitCode == 0)
			ok = true;
		CloseHandle(info.hProcess);
		CloseHandle(info.hThread);
		return ok;
	}
	return false;
}

// WorldBuilder ExecuteTextureAssetBuilder, WB VA 0x009D6BA0 (imports,strings lead, score 1.2).
bool __cdecl ExecuteTextureAssetBuilder(const WCHAR *currentDirectory)
{
	STARTUPINFOW startup;
	WCHAR command[260];
	PROCESS_INFORMATION info;
	DWORD exitCode;
	bool ok = false;

	memset(&startup, 0, sizeof(startup));
	startup.cb = sizeof(startup);
	wcscpy(command, L"TextureAssetBuilder.exe");
	if (CreateProcessW(0, command, 0, 0, 0, CREATE_NO_WINDOW, 0, currentDirectory, &startup, &info)) {
		WaitForSingleObject(info.hProcess, INFINITE);
		if (!GetExitCodeProcess(info.hProcess, &exitCode) || exitCode == 0)
			ok = true;
		CloseHandle(info.hProcess);
		CloseHandle(info.hThread);
		return ok;
	}
	return false;
}
