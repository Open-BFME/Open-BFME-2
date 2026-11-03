// cl: /O1 /EHsc /MD
// ??1Rva005D791C@@UAE@XZ @0x005D78E1 59B: dtor of Rva005D791C (vtable 0x00875DFC) calls tree member dtor 0x002F0B52 at +0x28 then base dtor 0x005EE30C. Evidence: retail vtable store plus lea ecx [esi+0x28] plus base chain per Rva005D791CCtor.cpp and Rva005EE30CChain.cpp; caller at 0x005D7956.
class Rva005EE30C
{
public:
	virtual ~Rva005EE30C();
private:
	char m_pad24[0x24];
};
#include "../../Include/GameLogic/Rva002EE9B7.h"
class Rva005D791C : public Rva005EE30C
{
public:
	virtual ~Rva005D791C();
private:
	Rva002EE9B7 m_tree28;
};
inline Rva005D791C::~Rva005D791C()
{
}

// This destructor is a header inline in the copier unit; the anchor is not retail code.
#pragma inline_depth(0)
// ?_bfmeRva005D791CDtorInlineAnchor@@YAXXZ absent-from-retail
void _bfmeRva005D791CDtorInlineAnchor()
{
    static_cast<Rva005D791C *>(0)->Rva005D791C::~Rva005D791C();
}
#pragma inline_depth()
