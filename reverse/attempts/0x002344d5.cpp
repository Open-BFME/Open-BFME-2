// ?getStringFromRegistry@@YA_NPAUHKEY__@@VAsciiString@@1AAV2@@Z
// partial score=0.95 date=2026-09-22
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
// cl: /O2 /EHsc
//
// Narrow getStringFromRegistry, retail 0x002344D5 (155 bytes). Converts the
// AsciiString path/key through wide temporaries, runs them through the wide
// core reader in RegistryGetUnicodeString.cpp, and translates a successful
// read back into the narrow result. The models below mirror the canonical
// wide/narrow declarations in WWLib/UnicodeFromAscii.cpp: UnicodeString
// derives from StringBase so a default temporary zeroes itself inline,
// AsciiString teardown resolves to the pinned 0x0036410 body, and the
// wide-building constructor plus translate resolve to their rowed bodies.

struct HKEY__ { int unused; };
typedef struct HKEY__ *HKEY;

template <typename T>
class StringBase
{
public:
	StringBase() : m_data(0) {}
	void releaseBuffer();
	~StringBase() { releaseBuffer(); }

	T *m_data;
};

class AsciiString;

class UnicodeString : public StringBase<unsigned short>
{
public:
	UnicodeString() {}
	UnicodeString(const AsciiString &src);
};

class AsciiString
{
public:
	~AsciiString();
	void translate(const UnicodeString &src);

private:
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		char data[1];
	};

	Header *m_data;
};

bool getStringFromRegistry(HKEY root, UnicodeString path, UnicodeString key, UnicodeString &val);

bool getStringFromRegistry(HKEY root, AsciiString path, AsciiString key, AsciiString &val)
{
	UnicodeString wval;

	bool ok = getStringFromRegistry(root, UnicodeString(path), UnicodeString(key), wval) ?
		(val.translate(wval), true) : false;
	return ok;
}
