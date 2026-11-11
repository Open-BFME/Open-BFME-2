// cl: /DNDEBUG /MD /EHsc
// ??0Rva006003FCMember@@QAE@PAX00I@Z @0x00600352 39B evidence: thiscall
// ctor (owner, first, second, colour; ret 0x10) of the player page's +8
// member, called so by 0x00600432: it chains to the rowed
// StrategicHUD::BattlePromptPlayerPageMovieClip ctor 0x00600305 with
// (first, second, colour), stores the owner at +8 and installs vtable
// 0x00C7A620 by literal store. TU-local view only.
// The retail table at RVA 0x0087A620: 4 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva00600379@@UAEPAXI@Z")();
void __identifier("?rva0060037E@Rva0060037E@@QAEXXZ")();
void __identifier("?rva00600386@Rva0060037E@@QAEXXZ")();
void __identifier("?rva0060038E@Rva0060038E@@QAEXXZ")();
}
extern "C" const void *const vtbl_00C7A620[4] = {
	(const void *)&__identifier("??_GRva00600379@@UAEPAXI@Z"), // slot 0 0x006003D3
	(const void *)&__identifier("?rva0060037E@Rva0060037E@@QAEXXZ"), // slot 1 0x0060037E
	(const void *)&__identifier("?rva00600386@Rva0060037E@@QAEXXZ"), // slot 2 0x00600386
	(const void *)&__identifier("?rva0060038E@Rva0060038E@@QAEXXZ"), // slot 3 0x0060038E
};
// ??0Rva006003FC@@QAE@PAX00@Z, native 600432..6004A5 (115B, EH, RET 0xC;
// callers the three player-page constructors 0x005FB14E, 0x005FB30A and
// 0x005FB4DF): over the zeroing counted base (Rva0007DF07, destructor
// 0x004E84A4 as its unwind action) it builds its +8 member through the
// constructor above, called as the thiscall it is (owner, two inputs and
// the player's colour with full alpha; the colour comes from the third
// input's object through 0x003F468D and RGBColor::getAsInt at +0x184), then
// copies the third input's three words to +0x14. Address-derived names;
// the member constructor's thiscall spelling is pinned at 0x00600352.
#include "../../Include/Common/Rva0007DF07.h"
#include "../../../Libraries/Include/Lib/RGBColor.h"
// 0x003F468D returns the player as an int (its rowed spelling).
#include "../../Include/Common/Rva003F468D.h"
struct Rva006003FCPlayer
{
	unsigned char m_pad000[0x184];
	RGBColor m_color;				// +0x184
	const RGBColor *getColor() const { return &m_color; }
};
struct Rva006003FCInputs
{
	Rva003F468D *m_source;
	int m_a;
	int m_b;
};
class Rva006003FCMember
{
public:
	Rva006003FCMember(void *owner, void *first, void *second, unsigned int color);	// 0x00600352
private:
	unsigned char m_clip[0x08];		// the movie clip base
	void *m_owner;					// +0x08
};
class AsciiString;
namespace StrategicHUD {
class BattlePromptPlayerPageMovieClip
{
public:
	BattlePromptPlayerPageMovieClip(int level, const AsciiString &name, int playerColor);	// 0x00600305
};
}
Rva006003FCMember::Rva006003FCMember(void *owner, void *first, void *second, unsigned int color)
{
	((StrategicHUD::BattlePromptPlayerPageMovieClip *)this)->StrategicHUD::BattlePromptPlayerPageMovieClip::BattlePromptPlayerPageMovieClip(
		(int)first, *(const AsciiString *)second, color);
	m_owner = owner;
	*(const void *const **)this = vtbl_00C7A620;
}
static __forceinline unsigned int getPlayerColor(const Rva006003FCInputs *in)
{
	return ((Rva006003FCPlayer *)in->m_source->rva003F468D(in->m_a, in->m_b))->getColor()->getAsInt() | 0xff000000;
}
class Rva006003FC : public Rva0007DF07
{
public:
	Rva006003FC(void *first, void *second, void *third);
	virtual ~Rva006003FC();	// 0x006003FC, Rva006003FCDtor.cpp
private:
	Rva006003FCMember m_08;			// +0x08
	Rva006003FCInputs m_14;			// +0x14
};
Rva006003FC::Rva006003FC(void *first, void *second, void *third)
	: m_08(this, first, second, getPlayerColor((const Rva006003FCInputs *)third))
{
	const Rva006003FCInputs *in = (const Rva006003FCInputs *)third;
	m_14.m_source = in->m_source;
	m_14.m_a = in->m_a;
	m_14.m_b = in->m_b;
}
