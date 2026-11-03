// cl: /O1 /G7 /Oi- /DNDEBUG /MD
//
// StringClass::StringClass(const char *, bool), retail 0x000F0ED1, 70 bytes.
// Dedicated TU so wwstring_assign_cstr.cpp cannot see this definition.
// Empty-inits the buffer from the static, measures with _mbslen, pre-sizes
// through Get_String when flagged or non-empty, then assigns. The
// signed-length jle and the flag-first push order fall out of the natural
// spelling under the assign TU's flags.

#include <mbstring.h>

#include "StringClassData.h"

// StringClass::m_EmptyString: defined in wwstring.cpp (= &m_NullChar).

// ??0StringClass@@QAE@PBD_N@Z
inline StringClass::StringClass(const char *name, bool flag)
{
	int len;

	m_Buffer = m_EmptyString;
	if (name != 0)
		len = (int)_mbslen((const unsigned char *)name);
	else
		len = 0;
	if (flag || len > 0)
		Get_String(len + 1, flag);
	*this = name;
}

// The constructor is a header inline in Zero Hour's wwstring.h; registry.cpp
// and the particle-texture unit emit it as select-any copies, which a plain
// definition here collided with. The anchor keeps this unit's copy for the
// row; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeStringClassCtorAnchor@@YAXPAVStringClass@@PBD@Z absent-from-retail
void _bfmeStringClassCtorAnchor(StringClass *string, const char *name)
{
	string->StringClass::StringClass(name, false);
}
#pragma inline_depth()
