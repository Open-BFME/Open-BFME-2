// cl: /DNDEBUG /MD /EHsc /Oy-
//
// ?rva002724FD@Drawable@@QAEXABVAsciiString@@HHMM@Z, retail 0x002724FD, 72 bytes.
// Drawable broadcaster over draw modules at this+0x14C via non-const
// getObjectDrawInterface at DrawModule slot 0xA8, forwarding 5 args to
// ObjectDrawInterface slot 0x88. Evidence: same +0x14C walk as landed
// Drawable_getPristineBonePositions 0x0027274D and siblings 0x002723ED,
// 0x0027248A, 0x0027257B; callers pass AsciiString plus ints plus floats
// (lua 0x00333424/0x003334EA/0x003335AF, vector 0x0045628C, 0x00496CA8).

extern class GameLogic *TheGameLogic;

class AsciiString;

class BfmeObjectDrawForRva2724FD
{
public:
	virtual void slot00() = 0; virtual void slot04() = 0;
	virtual void slot08() = 0; virtual void slot0C() = 0;
	virtual void slot10() = 0; virtual void slot14() = 0;
	virtual void slot18() = 0; virtual void slot1C() = 0;
	virtual void slot20() = 0; virtual void slot24() = 0;
	virtual void slot28() = 0; virtual void slot2C() = 0;
	virtual void slot30() = 0; virtual void slot34() = 0;
	virtual void slot38() = 0; virtual void slot3C() = 0;
	virtual void slot40() = 0; virtual void slot44() = 0;
	virtual void slot48() = 0; virtual void slot4C() = 0;
	virtual void slot50() = 0; virtual void slot54() = 0;
	virtual void slot58() = 0; virtual void slot5C() = 0;
	virtual void slot60() = 0; virtual void slot64() = 0;
	virtual void slot68() = 0; virtual void slot6C() = 0;
	virtual void slot70() = 0; virtual void slot74() = 0;
	virtual void slot78() = 0; virtual void slot7C() = 0;
	virtual void slot80() = 0; virtual void slot84() = 0;
	virtual void rva002724FDTarget(const AsciiString &a, int b, int c, float d, float e) = 0;
};

class BfmeDrawModuleForRva2724FD
{
public:
	virtual void slot00() = 0; virtual void slot04() = 0;
	virtual void slot08() = 0; virtual void slot0C() = 0;
	virtual void slot10() = 0; virtual void slot14() = 0;
	virtual void slot18() = 0; virtual void slot1C() = 0;
	virtual void slot20() = 0; virtual void slot24() = 0;
	virtual void slot28() = 0; virtual void slot2C() = 0;
	virtual void slot30() = 0; virtual void slot34() = 0;
	virtual void slot38() = 0; virtual void slot3C() = 0;
	virtual void slot40() = 0; virtual void slot44() = 0;
	virtual void slot48() = 0; virtual void slot4C() = 0;
	virtual void slot50() = 0; virtual void slot54() = 0;
	virtual void slot58() = 0; virtual void slot5C() = 0;
	virtual void slot60() = 0; virtual void slot64() = 0;
	virtual void slot68() = 0; virtual void slot6C() = 0;
	virtual void slot70() = 0; virtual void slot74() = 0;
	virtual void slot78() = 0; virtual void slot7C() = 0;
	virtual void slot80() = 0; virtual void slot84() = 0;
	virtual void slot88() = 0; virtual void slot8C() = 0;
	virtual void slot90() = 0; virtual void slot94() = 0;
	virtual void slot98() = 0; virtual void slot9C() = 0;
	virtual void slotA0() = 0; virtual void slotA4() = 0;
	virtual BfmeObjectDrawForRva2724FD *getObjectDrawInterface() = 0;
};

class Drawable
{
public:
	void rva002724FD(const AsciiString &a, int b, int c, float d, float e);
	void rva00272414(int arg);
	void rva002723ED();
};

void Drawable::rva002724FD(const AsciiString &a, int b, int c, float d, float e)
{
	BfmeDrawModuleForRva2724FD **modules =
		*reinterpret_cast<BfmeDrawModuleForRva2724FD ***>((unsigned char *)this + 0x14C);
	for (BfmeDrawModuleForRva2724FD **dm = modules; *dm; ++dm) {
		BfmeObjectDrawForRva2724FD *di = (*dm)->getObjectDrawInterface();
		if (di) {
			di->rva002724FDTarget(a, b, c, d, e);
		}
	}
}

// ?rva00272414@Drawable@@QAEXH@Z — RVA 0x00272414, 118B.
// Gated broadcaster: when byte +0x3AA is set and the TheGameLogic object's
// 0x00200084 predicate holds, require the +0xFC Thing to be any-kind-of the
// (0,0x78,0xB5) bitset; then walk the +0x14C draw modules via slot 0xA8 and
// forward the arg to slot 0x78 targets.
// Evidence: chain lane (calls landed 0x00200084); same +0x14C/slot-0xA8 walk
// as rva002724FD above; callers at 0x004B50F0 0x004B51F8.
template <int N> class BitFlags
{
public:
	unsigned m_words[7];
};

struct Rva0006EE7A : public BitFlags<69>
{
	Rva0006EE7A(int unused, int b1, int b2);
};

class Thing
{
public:
	bool isAnyKindOf(const BitFlags<69> &mask) const;
};

class Rva0023C6A4
{
public:
	bool rva00200084();
};

#define TheGameLogic (*(Rva0023C6A4 **)&TheGameLogic)

class BfmeObjectDrawForRva272414
{
public:
	virtual void slot00() = 0; virtual void slot04() = 0;
	virtual void slot08() = 0; virtual void slot0C() = 0;
	virtual void slot10() = 0; virtual void slot14() = 0;
	virtual void slot18() = 0; virtual void slot1C() = 0;
	virtual void slot20() = 0; virtual void slot24() = 0;
	virtual void slot28() = 0; virtual void slot2C() = 0;
	virtual void slot30() = 0; virtual void slot34() = 0;
	virtual void slot38() = 0; virtual void slot3C() = 0;
	virtual void slot40() = 0; virtual void slot44() = 0;
	virtual void slot48() = 0; virtual void slot4C() = 0;
	virtual void slot50() = 0; virtual void slot54() = 0;
	virtual void slot58() = 0; virtual void slot5C() = 0;
	virtual void slot60() = 0; virtual void slot64() = 0;
	virtual void slot68() = 0; virtual void slot6C() = 0;
	virtual void slot70() = 0; virtual void slot74() = 0;
	virtual void rva00272414Target(int arg) = 0;
};

class BfmeDrawModuleForRva272414
{
public:
	virtual void slot00() = 0; virtual void slot04() = 0;
	virtual void slot08() = 0; virtual void slot0C() = 0;
	virtual void slot10() = 0; virtual void slot14() = 0;
	virtual void slot18() = 0; virtual void slot1C() = 0;
	virtual void slot20() = 0; virtual void slot24() = 0;
	virtual void slot28() = 0; virtual void slot2C() = 0;
	virtual void slot30() = 0; virtual void slot34() = 0;
	virtual void slot38() = 0; virtual void slot3C() = 0;
	virtual void slot40() = 0; virtual void slot44() = 0;
	virtual void slot48() = 0; virtual void slot4C() = 0;
	virtual void slot50() = 0; virtual void slot54() = 0;
	virtual void slot58() = 0; virtual void slot5C() = 0;
	virtual void slot60() = 0; virtual void slot64() = 0;
	virtual void slot68() = 0; virtual void slot6C() = 0;
	virtual void slot70() = 0; virtual void slot74() = 0;
	virtual void slot78() = 0; virtual void slot7C() = 0;
	virtual void slot80() = 0; virtual void slot84() = 0;
	virtual void slot88() = 0; virtual void slot8C() = 0;
	virtual void slot90() = 0; virtual void slot94() = 0;
	virtual void slot98() = 0; virtual void slot9C() = 0;
	virtual void slotA0() = 0; virtual void slotA4() = 0;
	virtual BfmeObjectDrawForRva272414 *getObjectDrawInterface() = 0;
};

void Drawable::rva00272414(int arg)
{
	if (*(unsigned char *)((unsigned char *)this + 0x3AA) == 0)
		return;
	Thing *thing = *(Thing **)((unsigned char *)this + 0xFC);
	if (TheGameLogic->rva00200084()) {
		if (thing == 0)
			return;
		if (!thing->isAnyKindOf(Rva0006EE7A(0, 0x78, 0xB5)))
			return;
	}
	BfmeDrawModuleForRva272414 **modules =
		*reinterpret_cast<BfmeDrawModuleForRva272414 ***>((unsigned char *)this + 0x14C);
	for (BfmeDrawModuleForRva272414 **dm = modules; *dm; ++dm) {
		BfmeObjectDrawForRva272414 *di = (*dm)->getObjectDrawInterface();
		if (di)
			di->rva00272414Target(arg);
	}
}

// ?rva002723ED@Drawable@@QAEXXZ — RVA 0x002723ED, 39B.
// Draw-module walk at this+0x14C via slot 0xA8, forwarding to slot 0x74
// targets with no args. Evidence: same +0x14C/slot-0xA8 walk as landed
// rva002724FD/rva00272414 above; unblocks 0x0049015C 0x004562F8
// 0x004B5101 0x004B5020; callers at 0x004563B0 0x004901AA 0x004B50D3.
class BfmeObjectDrawForRva2723ED
{
public:
	virtual void slot00() = 0; virtual void slot04() = 0;
	virtual void slot08() = 0; virtual void slot0C() = 0;
	virtual void slot10() = 0; virtual void slot14() = 0;
	virtual void slot18() = 0; virtual void slot1C() = 0;
	virtual void slot20() = 0; virtual void slot24() = 0;
	virtual void slot28() = 0; virtual void slot2C() = 0;
	virtual void slot30() = 0; virtual void slot34() = 0;
	virtual void slot38() = 0; virtual void slot3C() = 0;
	virtual void slot40() = 0; virtual void slot44() = 0;
	virtual void slot48() = 0; virtual void slot4C() = 0;
	virtual void slot50() = 0; virtual void slot54() = 0;
	virtual void slot58() = 0; virtual void slot5C() = 0;
	virtual void slot60() = 0; virtual void slot64() = 0;
	virtual void slot68() = 0; virtual void slot6C() = 0;
	virtual void slot70() = 0;
	virtual void rva002723EDTarget() = 0;
};

class BfmeDrawModuleForRva2723ED
{
public:
	virtual void slot00() = 0; virtual void slot04() = 0;
	virtual void slot08() = 0; virtual void slot0C() = 0;
	virtual void slot10() = 0; virtual void slot14() = 0;
	virtual void slot18() = 0; virtual void slot1C() = 0;
	virtual void slot20() = 0; virtual void slot24() = 0;
	virtual void slot28() = 0; virtual void slot2C() = 0;
	virtual void slot30() = 0; virtual void slot34() = 0;
	virtual void slot38() = 0; virtual void slot3C() = 0;
	virtual void slot40() = 0; virtual void slot44() = 0;
	virtual void slot48() = 0; virtual void slot4C() = 0;
	virtual void slot50() = 0; virtual void slot54() = 0;
	virtual void slot58() = 0; virtual void slot5C() = 0;
	virtual void slot60() = 0; virtual void slot64() = 0;
	virtual void slot68() = 0; virtual void slot6C() = 0;
	virtual void slot70() = 0; virtual void slot74() = 0;
	virtual void slot78() = 0; virtual void slot7C() = 0;
	virtual void slot80() = 0; virtual void slot84() = 0;
	virtual void slot88() = 0; virtual void slot8C() = 0;
	virtual void slot90() = 0; virtual void slot94() = 0;
	virtual void slot98() = 0; virtual void slot9C() = 0;
	virtual void slotA0() = 0; virtual void slotA4() = 0;
	virtual BfmeObjectDrawForRva2723ED *getObjectDrawInterface() = 0;
};

void Drawable::rva002723ED()
{
	BfmeDrawModuleForRva2723ED **modules =
		*reinterpret_cast<BfmeDrawModuleForRva2723ED ***>((unsigned char *)this + 0x14C);
	for (BfmeDrawModuleForRva2723ED **dm = modules; *dm; ++dm) {
		BfmeObjectDrawForRva2723ED *di = (*dm)->getObjectDrawInterface();
		if (di)
			di->rva002723EDTarget();
	}
}

// Other units call this body (pinned at its address) under the spelling(s)
// below, with the same calling convention and stack arguments; bind them.
#pragma comment(linker, "/alternatename:?rva002724FD@Drawable@@QAEXABVAsciiString@@EHMM@Z=?rva002724FD@Drawable@@QAEXABVAsciiString@@HHMM@Z")
