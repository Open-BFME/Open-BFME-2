// cl: /Ireference/shims/bfme2_ascii /O1 /MD
// ?rva004FD6F9@Rva004FD6F9@@QAE_NABV?$StringBase@D@@@Z @0x004FD6F9 32B
// ?rva004FD8A8@Rva004FD6F9@@QAE_NABV1@@Z @0x004FD8A8 16B thunk forwarding o.m_14
// Evidence: this+0x38/+0x3C begin/end into rowed Rva000BD22FFind 0x000BD22F
// cmp against end; callers at 0x004FD89F 0x004FD8B0 0x004FD91B.
#include "ascii_string.h"

StringBase<char> *Rva000BD22FFind(StringBase<char> *first, StringBase<char> *last, const StringBase<char> &val);

class Rva004FD6F9
{
	unsigned char m_pad00[0x14];
	StringBase<char> m_14;
	unsigned char m_pad18[0x38 - 0x14 - 4];
	StringBase<char> *m_begin;
	StringBase<char> *m_end;
public:
	bool rva004FD6F9(const StringBase<char> &val);
	bool rva004FD8A8(const Rva004FD6F9 &o);
};

bool Rva004FD6F9::rva004FD6F9(const StringBase<char> &val)
{
	StringBase<char> *last = m_end;
	StringBase<char> *first = m_begin;
	return Rva000BD22FFind(first, last, val) == last;
}

bool Rva004FD6F9::rva004FD8A8(const Rva004FD6F9 &o)
{
	return rva004FD6F9(o.m_14);
}
