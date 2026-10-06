// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva0029A778@Rva0029A778@@QAEPAV1@ABV1@@Z @0x0029A778 39B. Copy UnicodeString at +0 via rowed StringBase wide set then 3 dwords at +4 +8 +0xC return this. Evidence: callee set StringBase wide 0x00037150 caller 0x0029BAD5.
#include "unicode_string.h"

class Rva0029A778
{
public:
	Rva0029A778 *rva0029A778(const Rva0029A778 &src);
private:
	UnicodeString m_str;
	int m_4;
	int m_8;
	int m_c;
};

Rva0029A778 *Rva0029A778::rva0029A778(const Rva0029A778 &src)
{
	m_str.set(src.m_str);
	m_4 = src.m_4;
	m_8 = src.m_8;
	m_c = src.m_c;
	return this;
}
