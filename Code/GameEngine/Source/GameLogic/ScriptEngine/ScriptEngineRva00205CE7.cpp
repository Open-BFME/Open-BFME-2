// cl: /Ireference/shims/bfme2_ascii /EHsc
// ?rva00205CE7@ScriptEngine@@QAE?AVAsciiString@@V2@@Z @0x00205CE7 118B
// ScriptEngine path join: resolveName(param) plus '/' plus param via rowed
// AsciiString plus-char and StringBase concat; by-value param and return.
// Evidence: sits between ScriptEngine 0x00205C93 and 0x00205D5D, same this
// used for pinned resolveName 0x002046C0, '/' 0x2f, callers 0x003C03C6 0x003C04C8.
#include "ascii_string.h"

class Rva002046C0Owner
{
public:
	AsciiString resolveName(const AsciiString &s);
};

class ScriptEngine
{
public:
	AsciiString rva00205CE7(AsciiString s);
};

AsciiString ScriptEngine::rva00205CE7(AsciiString s)
{
	AsciiString tmp = ((Rva002046C0Owner *)this)->resolveName(s);
	tmp += '/';
	tmp += s;
	return tmp;
}
