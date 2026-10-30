// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
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
#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > & basic_string<char, char_traits<char>, allocator<char> >::assign(char const *, char const *); }
namespace _STL { template <> char * basic_string<char, char_traits<char>, allocator<char> >::erase(char *, char *); }
namespace _STL { template <> char * __char_traits_base<char, int>::move(char *, char const *, unsigned int); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?_M_allocate_block@?$_String_base@DV?$allocator@D@_STL@@@_STL@@QAEXI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void _String_base<char,allocator<char> >::_M_allocate_block(unsigned int); }
// Suppress this TU's non-retail copy of ??$uninitialized_copy@PADPAD@_STL@@YAPADPAD00@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> char * uninitialized_copy<char *,char *>(char *,char *,char *); }
// Suppress this TU's non-retail copy of ??$__uninitialized_copy@PADPAD@_STL@@YAPADPAD00ABU__true_type@0@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> char *__uninitialized_copy<char *, char *>(char *, char *, char *, const __true_type &); }
// Suppress this TU's non-retail proxy<char> allocate copy (family2-LK3 row 30):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> __declspec(dllimport) __forceinline
char *_STLP_alloc_proxy<char*, char, allocator<char> >::allocate(size_t __n)
{ return __n != 0 ? allocator<char>::allocate(__n * sizeof(char), 0) : 0; }
}

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

bool  getStringFromRegistry(HKEY root, std::string path, std::string key, std::string& val)
{
	HKEY handle;
	unsigned char buffer[256];
	unsigned long size = 256;
	unsigned long type;
	int returnValue;

	if ((returnValue = RegOpenKeyExA( root, path.c_str(), 0, KEY_READ, &handle )) == ERROR_SUCCESS)
	{
		returnValue = RegQueryValueExA(handle, key.c_str(), NULL, &type, (unsigned char *) &buffer, &size);
		RegCloseKey( handle );
	}

	if (returnValue == ERROR_SUCCESS)
	{
		val = (char *)buffer;
		return true;
	}

	return false;
}

bool getUnsignedIntFromRegistry(HKEY root, std::string path, std::string key, unsigned int& val)
{
	HKEY handle;
	unsigned char buffer[4];
	unsigned long size = 4;
	unsigned long type;
	int returnValue;

	if ((returnValue = RegOpenKeyExA( root, path.c_str(), 0, KEY_READ, &handle )) == ERROR_SUCCESS)
	{
		returnValue = RegQueryValueExA(handle, key.c_str(), NULL, &type, (unsigned char *) &buffer, &size);
		RegCloseKey( handle );
	}

	if (returnValue == ERROR_SUCCESS)
	{
		val = *(unsigned int *)buffer;
		return true;
	}

	return false;
}

bool setStringInRegistry( HKEY root, std::string path, std::string key, std::string val)
{
	HKEY handle;
	unsigned long type;
	unsigned long returnValue;
	int size;

	if ((returnValue = RegCreateKeyExA( root, path.c_str(), 0, "REG_NONE", REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &handle, NULL )) == ERROR_SUCCESS)
	{
		type = REG_SZ;
		size = val.length()+1;
		returnValue = RegSetValueExA(handle, key.c_str(), 0, type, (unsigned char *)val.c_str(), size);
		RegCloseKey( handle );
	}

	return (returnValue == ERROR_SUCCESS);
}

bool setUnsignedIntInRegistry( HKEY root, std::string path, std::string key, unsigned int val)
{
	HKEY handle;
	unsigned long type;
	unsigned long returnValue;
	int size;

	if ((returnValue = RegCreateKeyExA( root, path.c_str(), 0, "REG_NONE", REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &handle, NULL )) == ERROR_SUCCESS)
	{
		type = REG_DWORD;
		size = 4;
		returnValue = RegSetValueExA(handle, key.c_str(), 0, type, (unsigned char *)&val, size);
		RegCloseKey( handle );
	}

	return (returnValue == ERROR_SUCCESS);
}

// BFME 2: the std::string twin of Common/System's buildGameRegistryPath.
std::string buildGameRegistryPath(const char *subPath)
{
	char fullPath[512];
	if (subPath)
	{
		if (*subPath && *subPath != '\\')
			sprintf(fullPath, "%s\\%s", GetRegistryGameRegPath(), subPath);
		else
			sprintf(fullPath, "%s%s", GetRegistryGameRegPath(), subPath);
	}
	else
	{
		strcpy(fullPath, GetRegistryGameRegPath());
	}
	return std::string(fullPath);
}

bool GetStringFromRegistry(std::string path, std::string key, std::string& val)
{
	std::string fullPath = GetRegistryGameRegPath();

	fullPath.append(path);
	if (getStringFromRegistry(HKEY_LOCAL_MACHINE, fullPath.c_str(), key.c_str(), val))
	{
		return true;
	}

	return getStringFromRegistry(HKEY_CURRENT_USER, fullPath.c_str(), key.c_str(), val);
}

bool GetUnsignedIntFromRegistry(std::string path, std::string key, unsigned int& val)
{
	std::string fullPath = buildGameRegistryPath(path.c_str());

	if (getUnsignedIntFromRegistry(HKEY_LOCAL_MACHINE, fullPath.c_str(), key.c_str(), val))
	{
		return true;
	}

	return getUnsignedIntFromRegistry(HKEY_CURRENT_USER, fullPath.c_str(), key.c_str(), val);
}
