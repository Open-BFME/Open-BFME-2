// cl: /Oy- /DNDEBUG /MD /GX /Ireference/shims/bfme2_ascii
// Native1F12DF..1F131F64B indexes complete20B module entries and copies a
// four-byte string into its hidden result. Native callers release that result
// using the shared StringBase<char> worker, just as AsciiString does.
// Use the shared string contract rather than a second private StringBase.
#include "ascii_string.h"

struct ModuleNugget { char m_bytes[20]; };
class ModuleInfo
{
public:
    AsciiString getNthName(int index) const;
    ModuleNugget *m_begin;
    ModuleNugget *m_end;
    ModuleNugget *m_cap;
};

AsciiString ModuleInfo::getNthName(int index) const
{
    if (index < 0 || (unsigned)index >= (unsigned)(((char *)m_end - (char *)m_begin) / 20))
        return AsciiString::TheEmptyString;
    return *(const AsciiString *)(m_begin + index);
}
