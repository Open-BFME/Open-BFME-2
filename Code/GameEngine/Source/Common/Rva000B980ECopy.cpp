// cl: /Ireference/shims/bfme2_ascii /MD
//
// ?rva000B980E@Rva000B980E@@QAEXPADHH@Z retail 0x000B980E 44B
// String-data memcpy: copy size bytes from the held AsciiString data
// plus offset (or the empty literal when null) to dst via msvcrt memcpy.
// Evidence: 2 callers plus empty-literal pin 0x00BBAC1C plus m_data
// plus 8 str idiom plus rowed memcpy import 0x006291A8.
#include <string.h>

#include "ascii_string.h"

#include "../../Include/Common/Rva000B980E.h"

void Rva000B980E::rva000B980E(char *dst, int off, int size)
{
	const char *base = m_str->str();
	memcpy(dst, base + off, size);
}
