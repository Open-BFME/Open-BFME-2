// cl: /EHsc /Ireference/shims/bfme2_ascii
// ?rva000B4A9F@Rva000B4A9F@@QAEPBDXZ @0x000B4A9F 22B.
// Empty-aware four-byte string-handle address at +0x4C via finish at +0x50.
// Native empty address VA DE0878 is AsciiString::TheEmptyString, not a C-string literal.
// Native50C9AA passes the result directly to StringBase::set(copy).
#include "ascii_string.h"
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
class Rva000B4A9F
{
public:
	const char *rva000B4A9F();

private:
	char m_pad00[0x4C];
	const char *m_start4C;
	const char *m_finish50;
};

// ?rva000B4A9F@Rva000B4A9F@@QAEPBDXZ
const char *Rva000B4A9F::rva000B4A9F()
{
	int d = m_finish50 - m_start4C;
	_ReadWriteBarrier();
	if ((d & ~3) == 0)
		return (const char *)&AsciiString::TheEmptyString;
	return m_start4C;
}
