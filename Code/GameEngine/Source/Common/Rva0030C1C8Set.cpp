// cl: /Ireference/shims/bfme2_ascii
// ?rva0030C1C8@Rva0030C1C8@@QAEXHABV?$StringBase@D@@@Z, retail 0x0030C1C8, 52 bytes.
// Array-of-StringBase setter at +0x40 stride 4 with virtual notify at slot 0x1c. Evidence: packet disassembly, callers 0x0030C6C8 0x00329339, compare/set rows.
#include "string_base.h"

class Rva0030C1C8
{
public:
	void rva0030C1C8(int idx, const StringBase<char> &val);
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07(int idx);
private:
	char m_pad04[0x3C];
	StringBase<char> m_arr40[];
};

void Rva0030C1C8::rva0030C1C8(int idx, const StringBase<char> &val)
{
	StringBase<char> *elem = &m_arr40[idx];
	if (val.compare(*elem) != 0)
	{
		elem->set(val);
		v07(idx);
	}
}
