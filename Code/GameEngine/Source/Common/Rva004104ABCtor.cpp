// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD

// ??0Rva004104AB@@QAE@_NPBD@Z, retail 0x004104AB 30B.
// thiscall ctor with ret 8: bool flag at +0 plus AsciiString at +4 built
// via AptUtils::DotPath2SlashPath 0x00412E76 hidden return. Callers 0x00411803
// (push 1) and 0x00411861 (push 0) prove bool plus path; returns this.

#include "ascii_string.h"

namespace AptUtils
{
	AsciiString DotPath2SlashPath(const char *path);
}

class Rva004104AB
{
public:
	Rva004104AB(bool flag, const char *path);
private:
	bool m_flag;
	char m_pad[3];
	AsciiString m_name;
};

Rva004104AB::Rva004104AB(bool flag, const char *path) : m_flag(flag), m_name(AptUtils::DotPath2SlashPath(path))
{
}
