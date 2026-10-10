// cl: /MD /EHsc
// ??1Rva00355D66@@UAE@XZ @0x00355D66 73B
// Intermediate dtor in the Gen_004902A0 family (base dtor rowed at 0x00355C77,
// base ctor unrowed at 0x00355C60, own ctor at 0x00355D4E with vtable 0x00814E5C).
// Evidence: stores vtable 0x00814E5C at [this], releases member +8 via
// TheWindowManager (0x00DFEF1C) slot 0x8C when non-null, clears +8, then calls
// base dtor; deleting dtor at 0x00355FDD calls here; EH prolog with scope
// 0x00B7D529 shared with sibling 0x00355CD8.

class Gen_004902A0
{
public:
	virtual ~Gen_004902A0() throw();
	Gen_004902A0 *m_next;
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

class Rva00355D66 : public Gen_004902A0
{
public:
	Rva00355D66();
	virtual ~Rva00355D66();
protected:
	GameWindow *m_win;
private:
	bool m_flag;
};

Rva00355D66::~Rva00355D66()
{
	if (m_win)
		TheWindowManager->managerSlot35(m_win);
	m_win = 0;
}

// ??1Rva00355DC5@@UAE@XZ @0x00355DC5 15B
// Derived dtor (vtable 0x00814E74) tail-jumping to base 0x00355D66.
// Evidence: clears +0x10 then stores vtable then jmp base; deleting dtor at
// 0x00356066 calls here; chain of 0x00355D66.
class Rva00355DC5 : public Rva00355D66
{
public:
	Rva00355DC5();
	virtual ~Rva00355DC5();
private:
	int m_extra;
};

// ??0Rva00355DC5@@QAE@XZ @0x00355DAF 22B: the matching constructor -- the
// rowed Rva00355D66 constructor 0x00355D4E, +0x10 cleared, vtable
// 0x00814E74. Nothing after the base can throw, so there is no EH frame.
Rva00355DC5::Rva00355DC5()
	: m_extra(0)
{
}

Rva00355DC5::~Rva00355DC5()
{
	m_extra = 0;
}

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
Rva00355F3E::Rva00355F3E()
{
	m_h = 0;
	for (int i = 0; i < 8; i++) {
		m_a[i] = 0;
		m_b[i] = 0;
		m_c[i] = 0;
		m_d[i] = -1;
		m_e[i] = -1;
	}
	m_f = 0;
	m_g = 0;
}

Rva00355F3E::~Rva00355F3E()
{
	for (int i = 0; i < 8; i++) {
		m_a[i] = 0;
		m_b[i] = 0;
		m_c[i] = 0;
		m_d[i] = -1;
		m_e[i] = -1;
	}
	m_f = 0;
	m_g = 0;
}

// ??1Rva003563A7@@UAE@XZ @0x003563A7 80B
// Derived dtor (vtable 0x00814ED4) with display global plus AsciiString member.
// Evidence: calls TheDisplay (0x00DFE9D8) slot 0x110, destroys StringBase narrow
// at +0x14 via rowed releaseBuffer, then calls base 0x00355D66; deleting dtor at
// 0x00356AFA calls here; chain of 0x00355D66; EH states 1/0/-1 with scope
// 0x00B7D5F0.
// Shared BFME2 one-pointer ownership: retail cleanup calls releaseBuffer,
// not the source-local public StringBase destructor spelling. The existing
// constructor parameter remains a StringBase reference; the shared wrapper
// itself uses this identical one-pointer representation for its copy.
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

class DisplayManager {
public:
	virtual void d00(); virtual void d01(); virtual void d02(); virtual void d03(); virtual void d04();
	virtual void d05(); virtual void d06(); virtual void d07(); virtual void d08(); virtual void d09();
	virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
	virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
	virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24();
	virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
	virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34();
	virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39();
	virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44();
	virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49();
	virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54();
	virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59();
	virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64();
	virtual void d65(); virtual void d66(); virtual void d67(); virtual void slot68();
	virtual void d69(); virtual void d70(); virtual void d71();
	virtual void slot72(AsciiString name, int flags);
	unsigned char m_pad04[0x10C - 0x04];
	bool m_10c; // +0x10C
};

class Display;
extern Display *TheDisplay;
#define TheDisplayManager ((DisplayManager *)TheDisplay)

class AudioManager
{
public:
	virtual void a00(); virtual void a01(); virtual void a02(); virtual void a03(); virtual void a04();
	virtual void a05(); virtual void a06(); virtual void a07(); virtual void a08(); virtual void a09();
	virtual void slot10();
	virtual void a11(); virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15();
	virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19();
	virtual void slot20(int which);
};

extern AudioManager *TheAudio;

class Rva003563A7 : public Rva00355D66
{
public:
	Rva003563A7(const StringBase<char> &name);
	virtual ~Rva003563A7();
	void rva00356B16(int unused); // vtable slot 2 (slot 1 is the shared empty RET 4 at 0x0047A69C)
	void rva00355EE1();
private:
	bool m_pad10;
	AsciiString m_str;
};

Rva003563A7::~Rva003563A7()
{
	TheDisplayManager->slot68();
}

// ??0Rva003563A7@@QAE@ABV?$StringBase@D@@@Z @0x00356367 64B: the matching
// constructor. Base 0x00355D4E (rowed Rva00355D66 ctor, EH state 0 once it
// is built), vtable 0x00814ED4, +0x10 cleared and the +0x14 name copied
// through the StringBase copy 0x000365F0. RET 4.
Rva003563A7::Rva003563A7(const StringBase<char> &name)
	: m_pad10(false),
	  m_str(reinterpret_cast<const AsciiString &>(name))
{
}

// Retail 0x00356B16, 98 bytes: slot 2 of vtable 0x00814ED4 (RET 4, argument
// unused). Nothing without a name; otherwise hands TheDisplay's slot 72 a copy
// of the +0x14 name with flags 0x800014 (slot 68 in the destructor and in
// rva00355EE1 undoes it), sets the display's +0x10C byte, then TheAudio
// (0x00DFE6E8) slot 20 with 2 and slot 10.
void Rva003563A7::rva00356B16(int)
{
	if (((const StringBase<char> *)&m_str)->isEmpty())
		return;
	if (TheDisplay)
		TheDisplayManager->slot72(m_str, 8388628); // 0x800014 int flags, not an image address
	TheDisplayManager->m_10c = true;
	TheAudio->slot20(2);
	TheAudio->slot10();
}

void Rva003563A7::rva00355EE1()
{
	TheDisplayManager->slot68();
	m_win = 0;
	m_pad10 = false;
}

// ?TheDisplay@@3PAVDisplayManager@@A: the global at this VA is ?TheDisplay@@3PAVDisplay@@A; this name is an alias for it.
// ?TheDisplay@@3PAVDisplayManager@@A: the global at VA 0xdfe9d8 is ?TheDisplay@@3PAVDisplay@@A.
