// cl: /Ireference/shims/bfme2_ascii /O1 /MD
// ?rva004FD6F9@Rva004FD6F9@@QAE_NABV?$StringBase@D@@@Z @0x004FD6F9 32B
// Evidence: this+0x38/+0x3C begin/end into rowed Rva000BD22FFind 0x000BD22F
// cmp against end; callers at 0x004FD89F 0x004FD8B0 0x004FD91B.
#include "ascii_string.h"

StringBase<char> *Rva000BD22FFind(StringBase<char> *first, StringBase<char> *last, const StringBase<char> &val);

class Rva004FD6F9
{
	unsigned char m_pad[0x38];
	StringBase<char> *m_begin;
	StringBase<char> *m_end;
public:
	bool rva004FD6F9(const StringBase<char> &val);
};

bool Rva004FD6F9::rva004FD6F9(const StringBase<char> &val)
{
	StringBase<char> *last = m_end;
	StringBase<char> *first = m_begin;
	return Rva000BD22FFind(first, last, val) == last;
}
