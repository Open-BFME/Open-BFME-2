// cl: /O1 /EHsc /MD
//
// ?Rva0040D11CSwap@@YAXPAVRva0040D0A4Entry@@0@Z @0x0040D11C (84B):
// Swap two 8-byte entries via tmp copy plus two rowed assigns with EH frame.
// Tmp is Rva0040CB11Entry copy of *a via rowed copy ctor 0x004F6335, then
// *a = *b and *b = tmp via rowed assign 0x0040D0A4, then tmp holder release
// via rowed fastcall 0x0007DEEF on +0xAC target. Caller 0x0040D963.
// Evidence: unlock lane, all callees rowed, prev/next assign and copybackward
// prove 8-byte entry layout, EH prolog plus and/or state stores.
#include "../../../Libraries/Source/Apt/AptRefTarget.h"
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);
class Rva002B2F97
{
public:
	Rva002B2F97 &operator=(const Rva002B2F97 &other);
	void *m_ptr;
};
#include "../../Include/Common/Rva0040D0A4Entry.h"
class Rva0040CB11Entry
{
public:
	Rva0040CB11Entry(const Rva0040CB11Entry &other);
	~Rva0040CB11Entry();
private:
	int m_first;
	Rva002B2F97 m_second;
};
// ??1Rva0040CB11Entry@@QAE@XZ present-unmatched
inline Rva0040CB11Entry::~Rva0040CB11Entry()
{
	void *p = m_second.m_ptr;
	if (p)
		ReleaseTreeHintRef00217D4C(reinterpret_cast<TargetRef00217D4C *>(static_cast<char *>(p) + 0xAC));
}
void __cdecl Rva0040D11CSwap(Rva0040D0A4Entry *lhs, Rva0040D0A4Entry *rhs)
{
	Rva0040CB11Entry tmp(*reinterpret_cast<const Rva0040CB11Entry *>(lhs));
	*lhs = *rhs;
	*rhs = *reinterpret_cast<const Rva0040D0A4Entry *>(&tmp);
}
