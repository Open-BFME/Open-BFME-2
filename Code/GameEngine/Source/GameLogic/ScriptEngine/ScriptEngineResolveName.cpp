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
