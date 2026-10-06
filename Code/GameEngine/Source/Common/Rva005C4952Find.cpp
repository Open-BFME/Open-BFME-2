// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
//
// ?rva005C4952@Rva005C4A91@@QBEEXPAVRva0040C804Target@@@Z @0x005C4952 (52B)
// ?rva005C49D4@Rva005C49D4Host@@UAEEXPAVRva0040C804Target@@@Z @0x005C49D4 (27B)

#include "ascii_string.h"
#include <vector>
#include <algorithm>

class Rva0040C804Target
{
public:
	int m_pad00;
	AsciiString m_name;
	bool check();
};

class Rva005C4A91
{
public:
	unsigned char rva005C4952(Rva0040C804Target *arg) const;

private:
	int m_pad00;
	int m_pad04;
	int m_pad08;
	_STL::vector<AsciiString> member0C;
};

unsigned char Rva005C4A91::rva005C4952(Rva0040C804Target *arg) const
{
	if (_STL::find(member0C.begin(), member0C.end(), arg->m_name) == member0C.end())
		return 0;
	return !arg->check();
}

class Rva005C49D4Host
{
public:
	virtual int getSlot0();
	virtual unsigned char rva005C49D4(Rva0040C804Target *arg);

private:
	int m_pad04;
	int m_pad08;
	int m_pad0C;
	int m_pad10;
	int m_val14;
};

unsigned char Rva005C49D4Host::rva005C49D4(Rva0040C804Target *arg)
{
	if (m_val14 >= getSlot0())
		return 0;

	Rva005C4A91 *owner = *(Rva005C4A91 **)((char *)this - 4);
	return owner->rva005C4952(arg);
}
