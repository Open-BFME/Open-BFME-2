// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva0020F442@Rva0020F442@@QAEPAVAsciiString@@ABV2@@Z @0x0020F442 65B via vector find with StringBase compare
// Evidence: retail loops (end-begin)>>2 at +0x34/+0x38 with index edi, calls rowed
// ?compare@?$StringBase@D@@QBEHABV1@@Z @0x000069D6, returns matching element or NULL;
// callers 0x004FD8B8 (Science/prereq walk) and 0x0056DB60; owner unproven so honest-address name.
#include "ascii_string.h"

class Rva0020F442
{
public:
	AsciiString *rva0020F442(const AsciiString &key);
private:
	char m_pad[0x34];
	union { AsciiString **m_begin; AsciiString ** volatile m_beginVolatile; };
	AsciiString **m_end;
};

AsciiString *Rva0020F442::rva0020F442(const AsciiString &key)
{
	for (unsigned i = 0; i < (unsigned)(((char *)m_end - (char *)m_begin) >> 2); ++i) {
		if (((const StringBase<char> *)m_beginVolatile[i])->compare((const StringBase<char> &)key) == 0)
			return m_beginVolatile[i];
	}
	return 0;
}
