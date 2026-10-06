// cl: /Ireference/shims/bfme2_ascii /MD
//
// ?rva000B980E@Rva000B980E@@QAEXPADHH@Z retail 0x000B980E 44B
// String-data memcpy: copy size bytes from the held AsciiString data
// plus offset (or the empty literal when null) to dst via msvcrt memcpy.
// Evidence: 2 callers plus empty-literal pin 0x00BBAC1C plus m_data
// plus 8 str idiom plus rowed memcpy import 0x006291A8.
extern "C" void *memcpy(void *dst, const void *src, unsigned int n);

#include "ascii_string.h"

class Rva000B980E
{
public:
	void rva000B980E(char *dst, int off, int size);
private:
	AsciiString *m_str;
};

void Rva000B980E::rva000B980E(char *dst, int off, int size)
{
	const char *base = m_str->str();
	memcpy(dst, base + off, size);
}
