// cl: /MD /EHsc /Ireference/shims/bfme2_ascii
// ??1Rva00355D66@@UAE@XZ @0x00355D66 73B
// Intermediate dtor in the ProgressIndicator family (base dtor rowed at 0x00355C77,
// base ctor unrowed at 0x00355C60, own ctor at 0x00355D4E with vtable 0x00814E5C).
// Evidence: stores vtable 0x00814E5C at [this], releases member +8 via
// TheWindowManager (0x00DFEF1C) slot 0x8C when non-null, clears +8, then calls
// base dtor; deleting dtor at 0x00355FDD calls here; EH prolog with scope
// 0x00B7D529 shared with sibling 0x00355CD8.

class ProgressIndicator
{
public:
	virtual ~ProgressIndicator() throw();
	ProgressIndicator *m_next; // +0x04
};

class GameWindow;

class GameWindowManager
{
public:
	virtual void pad00();
	virtual void pad01();
	virtual void pad02();
	virtual void pad03();
	virtual void pad04();
	virtual void pad05();
	virtual void pad06();
	virtual void pad07();
	virtual void pad08();
	virtual void pad09();
	virtual void pad10();
	virtual void pad11();
	virtual void pad12();
	virtual void pad13();
	virtual void pad14();
	virtual void pad15();
	virtual void pad16();
	virtual void pad17();
	virtual void pad18();
	virtual void pad19();
	virtual void pad20();
	virtual void pad21();
	virtual void pad22();
	virtual void pad23();
	virtual void pad24();
	virtual void pad25();
	virtual void pad26();
	virtual void pad27();
	virtual void pad28();
	virtual void pad29();
	virtual void pad30();
	virtual void pad31();
	virtual void pad32();
	virtual void pad33();
	virtual void pad34();
	virtual void managerSlot35(GameWindow *w);
};

extern GameWindowManager *TheWindowManager;

class Rva00355D66 : public ProgressIndicator
{
public:
	Rva00355D66();
	virtual ~Rva00355D66();
protected:
	GameWindow *m_win;
private:
	bool m_flag;
};

// The Rva00355D66, Rva00355DC5, Rva00355F3E and Rva003563A7 dtors and the
// Rva00355F3E ctor are rows of Rva00355D66Dtor.cpp; this unit only declares them.

// ??1Rva00355DC5@@UAE@XZ @0x00355DC5 15B
// Derived dtor (vtable 0x00814E74) tail-jumping to base 0x00355D66.
// Evidence: clears +0x10 then stores vtable then jmp base; deleting dtor at
// 0x00356066 calls here; chain of 0x00355D66.
class GameInfo;
class Rva00355DC5 : public Rva00355D66
{
public:
	virtual void init(GameInfo *game);
private:
	GameWindow *m_progressBar; // +0x10
};

// ??1Rva00355F3E@@UAE@XZ @0x00355F3E 55B
// Large derived dtor (vtable 0x00814E8C) tail-jumping to base 0x00355D66.
// Evidence: clears five 8-int arrays at +0x10/+0x30/+0x50 to 0 and +0x70/+0x90
// to -1 plus +0xB0/+0xB4 to 0, then jmp base; deleting dtor at 0x003563F7 calls
// here; chain of 0x00355D66.
class Rva00355F3E : public Rva00355D66
{
public:
	Rva00355F3E();
	virtual ~Rva00355F3E();
	virtual void rva00356413(int x);
private:
	int m_a[8];
	int m_b[8];
	int m_c[8];
	int m_d[8];
	int m_e[8];
	int m_f;
	int m_g;
	int m_h;
};

// ??0Rva00355F3E@@QAE@XZ @0x00355EFC 66B
// Ctor counterpart of the 55B dtor above (vtable 0x00814E8C): base ctor 0x00355D4E
// (pinned twin Rva00355D66, ICF with Rva00490470), vtable store, init five 8-int
// arrays at +0x10/+0x30/+0x50 to 0 and +0x70/+0x90 to -1 plus +0xB0/+0xB4/+0xB8 to 0.
// Evidence: gap between 0x00355EE1 and 0x00355F3E, same // cl, callees pinned.
// ??1Rva003563A7@@UAE@XZ @0x003563A7 80B
// Derived dtor (vtable 0x00814ED4) with display global plus AsciiString member.
// Evidence: calls TheDisplay (0x00DFE9D8) slot 0x110, destroys StringBase narrow
// at +0x14 via rowed releaseBuffer, then calls base 0x00355D66; deleting dtor at
// 0x00356AFA calls here; chain of 0x00355D66; EH states 1/0/-1 with scope
// 0x00B7D5F0.
// The canonical frozen StringBase replaces the private copy; its switch makes
// the member dtor reachable and keeps the teardown an out-of-line call to the
// rowed releaseBuffer (0x00036410 narrow, 0x00036E70 wide).
#define BFME_STRINGBASE_PUBLIC_DTOR
#include "string_base.h"



class Display;
extern Display *TheDisplay;


// ?TheDisplay@@3PAVDisplayManager@@A: the global at this VA is ?TheDisplay@@3PAVDisplay@@A; this name is an alias for it.
// ?TheDisplay@@3PAVDisplayManager@@A: the global at VA 0xdfe9d8 is ?TheDisplay@@3PAVDisplay@@A.

// ?rva00356413@Rva00355F3E@@UAEXH@Z @0x00356413 35B slot 1 of vtable 0x00814E8C
// Evidence: vslot lane; TheNetwork slot 0x40 with 0 then LoadScreen::update pin 0x00355FF9 with arg
class NetworkInterface
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16(int x);
};

extern NetworkInterface *TheNetwork;

class LoadScreen
{
public:
	virtual void update(int x);
};

void Rva00355F3E::rva00356413(int x)
{
	NetworkInterface *net = TheNetwork;
	if (net != 0)
		net->s16(0);
	((LoadScreen *)this)->LoadScreen::update(x);
}
