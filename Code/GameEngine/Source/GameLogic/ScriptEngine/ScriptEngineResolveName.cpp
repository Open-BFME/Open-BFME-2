// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?Rva0032A9D3Split@@YA?AVAsciiString@@AAV1@ABV1@@Z, retail 0x0032A9D3 (141B),
// and ?resolveName@Rva002046C0Owner@@QAE?AVAsciiString@@ABV2@@Z, retail
// 0x002046C0 (36B).
// Script names may be qualified as "<prefix>/<name>". The splitter returns the
// prefix and leaves the bare name in its argument; an unqualified name keeps
// its text and gets the supplied default prefix. ScriptEngine's resolveName
// (the owner keeps its pinned address-derived spelling) splits with the
// default at +0x1A10C; getTeamNamed and the by-value unit lookup call it and
// then key their maps on the (prefix, name) pair.

#include "ascii_string.h"

AsciiString Rva0032A9D3Split(AsciiString &name, const AsciiString &defaultPrefix)
{
	int len = name.getLength();
	for (int i = 0; i < len; i++)
	{
		if (name.getCharAt(i) == '/')
		{
			AsciiString prefix(name, 0, i);
			++i;
			((StringBase<char> *)&name)->set(*(const StringBase<char> *)&name, i, len - i);
			return prefix;
		}
	}
	return defaultPrefix;
}

unsigned long Rva003ECA13Get(const AsciiString &name);
unsigned long Rva003EC991(const char *text, int length, unsigned long crc);

// Native 0032AA60..0032AAEE, 142B, cdecl RET0. Like the rowed string
// splitter above, the first slash separates prefix and name. This variant
// returns CRC keys, with the supplied default prefix for unqualified names.
// Callee identities and the string header are independently rowed. Retail
// retains the initial buffer for the prefix and reloads it for the suffix.
// The original function name remains unknown.
unsigned long Rva0032AA60Split(unsigned long &nameKey, const AsciiString &name,
	unsigned long defaultPrefix)
{
	const char *data = *reinterpret_cast<const char *const *>(&name);
	int length = data ? *reinterpret_cast<const unsigned short *>(data + 4) : 0;
	for (int i = 0; i < length; ++i) {
		if (name.getCharAt(i) == '/') {
			unsigned long prefix = Rva003EC991(data ? data + 8 : "", i, 0);
			++i;
			nameKey = Rva003EC991(name.str() + i, length - i, 0);
			return prefix;
		}
	}
	nameKey = Rva003ECA13Get(name);
	return defaultPrefix;
}

class Rva002046C0Owner
{
public:
	AsciiString resolveName(const AsciiString &name);

private:
	char m_pad00[0x1A10C];
	AsciiString m_defaultPrefix; // +0x1A10C
};

AsciiString Rva002046C0Owner::resolveName(const AsciiString &name)
{
	return Rva0032A9D3Split(const_cast<AsciiString &>(name), m_defaultPrefix);
}

// Native inventory boundary 0x0032AAEE..0x0032ABDA (236B), ending in RET 8.
// ECX+0x0C supplies an array of 16-byte records; MOVSX reads signed 16-bit
// links at +0 and +2. The twelve remaining bytes are never consumed here.
// Removing both records and reinserting each at the other's position is the
// structural interpretation of the target writes. The original container,
// method name and relationship to the preceding name splitter are unknown.
struct Rva0032AAEENode
{
	short next;
	short previous;
	char unknown04[12];
};

class Rva0032AAEE
{
public:
	void rva0032AAEE(int a, int b);

private:
	char unknown00[12];
	Rva0032AAEENode *nodes;
};

void Rva0032AAEE::rva0032AAEE(int a, int b)
{
	if (a == b)
		return;
	if (nodes[a].previous == b) {
		int tmp = a;
		a = b;
		b = tmp;
	}

	Rva0032AAEENode *first = &nodes[a];
	Rva0032AAEENode *second = &nodes[b];
	int beforeFirst = first->previous;
	nodes[beforeFirst].next = first->next;
	nodes[first->next].previous = (short)beforeFirst;
	int beforeSecond = second->previous;
	nodes[beforeSecond].next = second->next;
	nodes[second->next].previous = (short)beforeSecond;

	first->next = nodes[beforeSecond].next;
	first->previous = (short)beforeSecond;
	nodes[beforeSecond].next = (short)a;
	nodes[first->next].previous = (short)a;
	second->next = nodes[beforeFirst].next;
	second->previous = (short)beforeFirst;
	nodes[beforeFirst].next = (short)b;
	nodes[second->next].previous = (short)b;
}

// Native 0x0032AFD4..0x0032B067, RET 12. The receiver holds two string
// pointers at +0/+4: the first supplies its unsigned length at buffer+4,
// and both supply text at buffer+8 (or the retail empty string). The two
// memcpy calls establish copying a slice across their concatenated text.
// Shared AsciiString accessors reproduce those independent header facts;
// the original owner/method and relationship to script names are unknown.
class Rva0032AFD4
{
public:
	void rva0032AFD4(char *out, int start, int length);
private:
	AsciiString *m_first;
	AsciiString *m_second;
};

void Rva0032AFD4::rva0032AFD4(char *out, int start, int length)
{
	int firstLen = m_first->getLength();
	if (start < firstLen) {
		int count = length;
		if (start + length > firstLen)
			count = firstLen - start;
		memcpy(out, m_first->str() + start, count);
		length -= count;
		if (length <= 0)
			return;
		out += count;
		start += count;
	}
	start -= firstLen;
	memcpy(out, m_second->str() + start, length);
}
