// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?rva00319904@Rva003193EC@@QAEXPAV1@@Z @0x00319904 32B
// Method of Rva003193EC (this+arg are Rva003193EC* proven by rowed second
// callee 0x003198B8 ?rva003198B8@Rva003193EC@@QAEXPAV1@@Z). Drains other's
// +0x78 ArmySummary entry list into this +0x78 via rowed
// 0x0040ED4F ?MergeUnitsFromArmy@ArmySummary@@QAEXAAV1@@Z then forwards to rva003198B8.
// Evidence: packet disasm ret-4 single ptr arg plus callers 0x002B4A8D 0x002B672F.
#include "ascii_string.h"

class ArmySummary
{
public:
	void MergeUnitsFromArmy(ArmySummary &other);
};

class Rva003193EC
{
public:
	void rva003198B8(Rva003193EC *other);
	void rva00319904(Rva003193EC *other);
private:
	char m_pad00[0x78];
	ArmySummary *m_78;
};

void Rva003193EC::rva00319904(Rva003193EC *other)
{
	m_78->MergeUnitsFromArmy(*other->m_78);
	rva003198B8(other);
}
