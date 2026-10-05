// ?SetStringInRegistry@@YA_NV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@00@Z
// partial score=0.85 date=2026-10-04
// cl: /O2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?SetStringInRegistry@@YA_NV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@00@Z
// retail inlines the string copy ctor for the HKLM call's three by-value arguments (zeroed members + _M_range_initialize<char*> at 0x00008D00) and calls the out-of-line copy ctor 0x00009170 for the HKCU call; cl 7.1 here calls 0x00009170 for both (439B vs 485B)
// stlport
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// Registry.cpp
// Simple interface for storing/retreiving registry values
// Author: Matthew D. Campbell, December 2001
//
// Ported from Zero Hour's Libraries/Source/WWVegas/WWDownload/registry.cpp
// (GeneralsMD tree vendored under reference/open-bfme-1/inputs/reference).
// BFME 2 keeps the std::string interface but, like the AsciiString registry
// in Common/System, roots every public path under the GameRegPath value
// instead of Zero Hour's hard-coded "SOFTWARE\Electronic Arts\..." key.

// sprintf stays the msvcr71 import retail calls through. The strings free
// through the game's C++-linkage free at 0x00030830 (pinned as
// ?free@_STL@@YAXPAX@Z): a callee that may throw is what makes cl keep the
// unwind-state stores retail carries between the parameter destructors.
extern "C" __declspec(dllimport) int __cdecl sprintf(char *buffer, const char *format, ...);

#include <stdlib.h>
namespace _STL { void __cdecl free(void *block); }
#define free _STL::free
#include <string>
#undef free
#include <string.h>

struct HKEY__;
typedef HKEY__ *HKEY;
typedef unsigned long DWORD;
typedef long LONG;
#define ERROR_SUCCESS 0L
#define KEY_READ 0x20019L
#define KEY_WRITE 0x20006L
#define REG_OPTION_NON_VOLATILE 0L
#define REG_SZ 1
#define REG_DWORD 4
#define HKEY_CURRENT_USER ((HKEY)0x80000001)
#define HKEY_LOCAL_MACHINE ((HKEY)0x80000002)

extern "C" __declspec(dllimport) LONG __stdcall RegOpenKeyExA(
		HKEY hKey, const char *lpSubKey, DWORD ulOptions, DWORD samDesired, HKEY *phkResult);
extern "C" __declspec(dllimport) LONG __stdcall RegQueryValueExA(
		HKEY hKey, const char *lpValueName, DWORD *lpReserved, DWORD *lpType,
		unsigned char *lpData, DWORD *lpcbData);
extern "C" __declspec(dllimport) LONG __stdcall RegCreateKeyExA(
		HKEY hKey, const char *lpSubKey, DWORD Reserved, char *lpClass, DWORD dwOptions,
		DWORD samDesired, void *lpSecurityAttributes, HKEY *phkResult, DWORD *lpdwDisposition);
extern "C" __declspec(dllimport) LONG __stdcall RegSetValueExA(
		HKEY hKey, const char *lpValueName, DWORD Reserved, DWORD dwType,
		const unsigned char *lpData, DWORD cbData);
extern "C" __declspec(dllimport) LONG __stdcall RegCloseKey(HKEY hKey);

const char *GetRegistryGameRegPath();

bool setStringInRegistry( HKEY root, std::string path, std::string key, std::string val);
bool setUnsignedIntInRegistry( HKEY root, std::string path, std::string key, unsigned int val);
std::string buildGameRegistryPath(const char *subPath);

// ?SetStringInRegistry@@YA_NV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@00@Z present-unmatched
bool SetStringInRegistry( std::string path, std::string key, std::string val)
{
	std::string fullPath = buildGameRegistryPath(path.c_str());

	if (setStringInRegistry( HKEY_LOCAL_MACHINE, fullPath, key, val))
		return true;

	return setStringInRegistry( HKEY_CURRENT_USER, fullPath, key, val );
}

