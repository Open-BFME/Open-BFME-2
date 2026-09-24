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
// The narrow half of BFME 2's expression-template string concatenation, and
// the AsciiString registry-path builder built on it. The wide half lives in
// Code/GameEngine/Source/Main/WinMainPairUnicode.cpp; the (pointer, length)
// text reference is the same Rva000B3F84Pair shape.
//
// A concatenation "name + '\\' + text" builds by-value nodes: a reference to
// the AsciiString operand (optionally followed by one char) and a text
// reference. Each node knows its length and writes itself into a buffer;
// operator AsciiString() sizes an AsciiString and fills it. The generic
// nodes are template-shared across the image, so their bodies sit far from
// the registry code that first used them here.

extern "C" void *__cdecl memcpy(void *dst, const void *src, unsigned int n);

class AsciiString;

template <typename T>
class StringBase
{
	friend class AsciiString;
	StringBase(const T *text);
	StringBase(const StringBase &src);

public:
	StringBase() : m_data(0) {}
	~StringBase();
	T *getBufferForRead(int len);

	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

protected:
	Header *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &src) : StringBase<char>(src) {}
	AsciiString &operator=(const AsciiString &src);

	int getLength() const { return m_data ? m_data->length : 0; }
	const char *str() const { return m_data ? m_data->data : ""; }
};

// The (pointer, length) text reference shared with the wide builders.
class Rva000B3F84Pair
{
public:
	Rva000B3F84Pair() {}
	Rva000B3F84Pair *init(const char *src);
	int write(char *dst);

	const char *m_ptr;
	int m_len;
};

// A reference to an AsciiString operand.
struct AsciiStringRef
{
	int write(char *dst);

	const AsciiString *m_string;
};

// An AsciiString operand followed by one char.
struct AsciiStringRefWithChar : AsciiStringRef
{
	int write(char *dst);

	char m_char;
};

// "string + text"
struct AsciiStringPlusText : AsciiStringRef
{
	int length() const;
	int write(char *dst);
	operator AsciiString();

	Rva000B3F84Pair m_right;
};

// "string + char + text"
struct AsciiStringCharPlusText : AsciiStringRefWithChar
{
	int length() const;
	int write(char *dst);
	operator AsciiString();

	Rva000B3F84Pair m_right;
};

// ?write@Rva000B3F84Pair@@QAEHPAD@Z @0xB44F0
int Rva000B3F84Pair::write(char *dst)
{
	memcpy(dst, m_ptr, m_len);
	return m_len;
}

// ?write@AsciiStringRef@@QAEHPAD@Z @0x2C5B1
int AsciiStringRef::write(char *dst)
{
	int len = m_string->getLength();
	memcpy(dst, m_string->str(), len);
	return len;
}

// ?write@AsciiStringRefWithChar@@QAEHPAD@Z @0x2C7A7
int AsciiStringRefWithChar::write(char *dst)
{
	int n = AsciiStringRef::write(dst);
	dst[n] = m_char;
	return n + 1;
}

// ?length@AsciiStringPlusText@@QBEHXZ @0x2DBF50
int AsciiStringPlusText::length() const
{
	return m_string->getLength() + m_right.m_len;
}

// ?write@AsciiStringPlusText@@QAEHPAD@Z @0xBBD41
int AsciiStringPlusText::write(char *dst)
{
	int n = AsciiStringRef::write(dst);
	return n + m_right.write(dst + n);
}

// ??BAsciiStringPlusText@@QAE?AVAsciiString@@XZ @0xBC4F7
AsciiStringPlusText::operator AsciiString()
{
	AsciiString tmp;
	write(tmp.getBufferForRead(length()));
	return tmp;
}

// ?length@AsciiStringCharPlusText@@QBEHXZ @0x2347EB
int AsciiStringCharPlusText::length() const
{
	return m_string->getLength() + 1 + m_right.m_len;
}

// ?write@AsciiStringCharPlusText@@QAEHPAD@Z @0x2349D8
int AsciiStringCharPlusText::write(char *dst)
{
	int n = AsciiStringRefWithChar::write(dst);
	return n + m_right.write(dst + n);
}

// ??BAsciiStringCharPlusText@@QAE?AVAsciiString@@XZ @0x234CA6
AsciiStringCharPlusText::operator AsciiString()
{
	AsciiString tmp;
	write(tmp.getBufferForRead(length()));
	return tmp;
}

// ??H@YA?AUAsciiStringPlusText@@ABVAsciiString@@PBD@Z @0xB49C5
AsciiStringPlusText operator+(const AsciiString &left, const char *right)
{
	Rva000B3F84Pair text;
	text.init(right);
	AsciiStringPlusText result;
	result.m_string = &left;
	result.m_right = text;
	return result;
}

// ??H@YA?AUAsciiStringCharPlusText@@ABUAsciiStringRefWithChar@@PBD@Z @0x109CFD
AsciiStringCharPlusText operator+(const AsciiStringRefWithChar &left, const char *right)
{
	Rva000B3F84Pair text;
	text.init(right);
	AsciiStringCharPlusText result;
	static_cast<AsciiStringRefWithChar &>(result) = left;
	result.m_right = text;
	return result;
}

inline AsciiStringRefWithChar operator+(const AsciiString &left, char c)
{
	AsciiStringRefWithChar result;
	result.m_string = &left;
	result.m_char = c;
	return result;
}

// ?makeAsciiString@@YA?AVAsciiString@@PBD@Z @0x2343DF
AsciiString makeAsciiString(const char *text)
{
	return AsciiString(text);
}

const char *GetRegistryGameRegPath();

// ?buildGameRegistryPath@@YA?AVAsciiString@@PBD@Z @0x234D08
// The narrow twin of the wide builder: roots a registry sub-path under the
// game's GameRegPath value, inserting the backslash separator unless the
// sub-path is empty or already has one.
AsciiString buildGameRegistryPath(const char *subPath)
{
	AsciiString path;
	if (subPath && *subPath && *subPath != '\\')
		path = makeAsciiString(GetRegistryGameRegPath()) + '\\' + subPath;
	else
		path = makeAsciiString(GetRegistryGameRegPath()) + subPath;
	return path;
}
