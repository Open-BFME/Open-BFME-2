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
// cl: /O1 /EHsc
//
// getStringFromRegistry, retail 0x00234417 (190 bytes). Reads a wide
// registry string (typically DisplayName) under a caller-supplied root key
// into a UnicodeString. Reconciled from Open-BFME-1's
// Code/GameEngine/Source/Common/System/RegistryGetUnicodeString.cpp:
// the layout, EH shape, KEY_READ open, query-then-close order and
// open/query-fail sharing are the donor's own. BFME 2 repair: the value is
// stored with the one-argument set (retail calls 0x00565D, pinned here)
// where the donor spells set(buffer, wcslen(buffer)).

#define WIN32_LEAN_AND_MEAN

struct HKEY__ { int unused; };
typedef struct HKEY__ *HKEY;

typedef unsigned long DWORD;
typedef long LONG;
typedef int BOOL;
#define NULL 0
#define ERROR_SUCCESS 0L
#define KEY_READ 0x20019L
#define HKEY_LOCAL_MACHINE ((HKEY)0x80000002)

extern "C" __declspec(dllimport) LONG __stdcall RegOpenKeyExW(
		HKEY hKey, const unsigned short *lpSubKey, DWORD ulOptions, DWORD samDesired, HKEY *phkResult);
extern "C" __declspec(dllimport) LONG __stdcall RegQueryValueExW(
		HKEY hKey, const unsigned short *lpValueName, DWORD *lpReserved, DWORD *lpType,
		unsigned char *lpData, DWORD *lpcbData);
extern "C" __declspec(dllimport) LONG __stdcall RegCloseKey(HKEY hKey);

// Only what this body reaches of the engine's reference-counted string:
// the header layout behind str(), the out-of-line releaseBuffer the
// destructor forwards to, and the one-argument set (pinned at 0x00565D).
template <typename T>
class StringBase
{
public:
	void set(const T *src);

	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	void releaseBuffer();
	Header *m_data;
};

class UnicodeString
{
public:
	~UnicodeString()
	{
		m_data.releaseBuffer();
	}

private:
	StringBase<unsigned short> m_data;
};

static const unsigned short *registryString(const UnicodeString &value)
{
	char *data = *reinterpret_cast<char *const *>(&value);
	return data ? reinterpret_cast<unsigned short *>(data + 8) : L"";
}

bool getStringFromRegistry(HKEY root, UnicodeString path, UnicodeString key, UnicodeString &val)
{
	HKEY handle;
	unsigned short buffer[128];
	DWORD size = 256;
	DWORD type;
	LONG returnValue;

	if ((returnValue = RegOpenKeyExW(root, registryString(path), 0, KEY_READ, &handle)) == ERROR_SUCCESS)
	{
		returnValue = RegQueryValueExW(handle, registryString(key), NULL, &type,
		                              reinterpret_cast<unsigned char *>(buffer), &size);
		RegCloseKey(handle);
	}

	if (returnValue == ERROR_SUCCESS)
	{
		((StringBase<unsigned short> *)&val)->set(buffer);
		return true;
	}

	return false;
}
