// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD
// stlport
//
// ??1Rva0054C941@@QAE@XZ @0x0054C941 (89B).
// Dtor with EH scope 0x0079824F: releases TreeHint refs at +0x20/+0x1c,
// destroys Rva0052413E at +8, releases AsciiString at +4. LINK BONUS 46B,
// callers 0x0054CC02/0x0054CC27, unblocks 0x0054CC1B.
#include "ascii_string.h"
#include <vector>

class Rva0052413E
{
public:
	~Rva0052413E();
private:
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_vec;	// +0x00, size 12
};
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);
struct TreeHintRefHolder
{
	TargetRef00217D4C *m_ptr;
	~TreeHintRefHolder()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(m_ptr);
	}
};
class Rva0054C941
{
public:
	~Rva0054C941();
private:
	char m_pad00[4];			// +0x00
	AsciiString m_str;			// +0x04
	Rva0052413E m_rva08;			// +0x08
	char m_pad14[0x1c - 0x14];		// +0x14
	TreeHintRefHolder m_holder1C;	// +0x1c
	TreeHintRefHolder m_holder20;	// +0x20
};
Rva0054C941::~Rva0054C941()
{
}
