// ?rva0051759E@Rva00517345@@UAEHIEI@Z
// partial score=0.75 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?rva0051759E@Rva00517345@@UAEHIEI@Z
// retail 0x0051759E..0x00517724 (390 bytes) thiscall RET 0xC.
//
// NEAR (helper draft, not under Code/): compiles to 393 bytes. What is left:
// (1) cl keeps both function-pointer temporaries of the two handle
// constructions in separate slots (frame 0x18), retail shares the dead
// msg slot [ebp+8] for both (frame 0x14); (2) as a knock-on, the register
// constant becomes ebx=1 instead of retail's ebx=0, so many compares and
// stores differ only in that operand. Everything else (control flow, the
// handler loop, both fetches, the in-place construction of the two
// handles, the pair, its copy and the converted callback argument, and
// the cleanup states) lines up.
// Needs three placeholder pins (the rowed spellings are member functions or
// take other parameter types, so cl cannot construct the by-value arguments
// in place through them):
//   ??0Rva004F6986Member@@QAE@ABQ6AXXZ@Z=0x0044BC76
//   ??0Rva0044BA4E@@QAE@ABU0@@Z=0x0044BD00
//   ??0Rva0044BF40@@QAE@URva0044BA4E@@@Z=0x0044BF40
// Identity: slot 4 of vtable 0x0086641C (the ledger's ??_7Rva00517345);
// message 0x15 with key 1 (Esc) or 0x1C/0x9C (Enter) plus the modifier
// bits 1/0xC; rowed Rva00511730/Rva005116C2, the +0x280 handler vector
// (slot +0x10), then the "APT:LogoffConfirmationTitle/Msg" message box
// through _Rva00437F61 with two callbacks (VA 0x00812731 = folded
// CloseWindow body 0x00412731, VA 0x004B3FD0 = empty function 0x000B3FD0).
#include "ascii_string.h"
#include "unicode_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef bool Bool;

class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
	virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0) = 0;
};
extern GameTextInterface *TheGameText;

#define GAMESPY_SLOT(n) virtual void slot##n();
class GameSpyInfoInterface
{
public:
	GAMESPY_SLOT(00) GAMESPY_SLOT(01) GAMESPY_SLOT(02) GAMESPY_SLOT(03) GAMESPY_SLOT(04)
	GAMESPY_SLOT(05) GAMESPY_SLOT(06) GAMESPY_SLOT(07) GAMESPY_SLOT(08) GAMESPY_SLOT(09)
	GAMESPY_SLOT(10) GAMESPY_SLOT(11) GAMESPY_SLOT(12) GAMESPY_SLOT(13) GAMESPY_SLOT(14)
	GAMESPY_SLOT(15) GAMESPY_SLOT(16) GAMESPY_SLOT(17) GAMESPY_SLOT(18) GAMESPY_SLOT(19)
	GAMESPY_SLOT(20) GAMESPY_SLOT(21) GAMESPY_SLOT(22) GAMESPY_SLOT(23) GAMESPY_SLOT(24)
	GAMESPY_SLOT(25) GAMESPY_SLOT(26) GAMESPY_SLOT(27) GAMESPY_SLOT(28) GAMESPY_SLOT(29)
	GAMESPY_SLOT(30) GAMESPY_SLOT(31) GAMESPY_SLOT(32) GAMESPY_SLOT(33) GAMESPY_SLOT(34)
	GAMESPY_SLOT(35) GAMESPY_SLOT(36) GAMESPY_SLOT(37) GAMESPY_SLOT(38) GAMESPY_SLOT(39)
	GAMESPY_SLOT(40) GAMESPY_SLOT(41) GAMESPY_SLOT(42) GAMESPY_SLOT(43) GAMESPY_SLOT(44)
	GAMESPY_SLOT(45) GAMESPY_SLOT(46) GAMESPY_SLOT(47) GAMESPY_SLOT(48) GAMESPY_SLOT(49)
	GAMESPY_SLOT(50) GAMESPY_SLOT(51) GAMESPY_SLOT(52) GAMESPY_SLOT(53) GAMESPY_SLOT(54)
	GAMESPY_SLOT(55) GAMESPY_SLOT(56) GAMESPY_SLOT(57) GAMESPY_SLOT(58) GAMESPY_SLOT(59)
	GAMESPY_SLOT(60) GAMESPY_SLOT(61) GAMESPY_SLOT(62) GAMESPY_SLOT(63) GAMESPY_SLOT(64)
	GAMESPY_SLOT(65) GAMESPY_SLOT(66) GAMESPY_SLOT(67) GAMESPY_SLOT(68) GAMESPY_SLOT(69)
	GAMESPY_SLOT(70) GAMESPY_SLOT(71) GAMESPY_SLOT(72) GAMESPY_SLOT(73) GAMESPY_SLOT(74)
	GAMESPY_SLOT(75) GAMESPY_SLOT(76) GAMESPY_SLOT(77) GAMESPY_SLOT(78) GAMESPY_SLOT(79)
	GAMESPY_SLOT(80) GAMESPY_SLOT(81) GAMESPY_SLOT(82) GAMESPY_SLOT(83) GAMESPY_SLOT(84)
	GAMESPY_SLOT(85) GAMESPY_SLOT(86) GAMESPY_SLOT(87) GAMESPY_SLOT(88) GAMESPY_SLOT(89)
	GAMESPY_SLOT(90) GAMESPY_SLOT(91) GAMESPY_SLOT(92) GAMESPY_SLOT(93) GAMESPY_SLOT(94)
	GAMESPY_SLOT(95) GAMESPY_SLOT(96)
	virtual bool slot97();				// +0x184
};
extern GameSpyInfoInterface *TheGameSpyInfo;

extern int g_Va00E046B8;
void Rva00511730(int a);
void Rva005116C2();

// Reference-counted callback handles (address-derived views; the callee
// releases its by-value handles).
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);

struct Rva004F6986Member
{
	Rva004F6986Member(void (* const &fn)());
	Rva004F6986Member(const Rva004F6986Member &that) : m_ptr(that.m_ptr)
	{
		if (m_ptr)
			++((int *)m_ptr)[1];
	}
	~Rva004F6986Member()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(m_ptr);
	}
	TargetRef00217D4C *m_ptr;
};

struct Rva0044BA4E
{
	Rva0044BA4E(Rva004F6986Member first, Rva004F6986Member second);
	Rva0044BA4E(const Rva0044BA4E &other);
	~Rva0044BA4E();
	Rva004F6986Member m_00;
	Rva004F6986Member m_04;
};

struct Rva0044BF40
{
	Rva0044BF40(Rva0044BA4E buttons);
	Rva0044BF40(const Rva0044BF40 &that) : m_ptr(that.m_ptr)
	{
		if (m_ptr)
			++((int *)m_ptr)[1];
	}
	~Rva0044BF40()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(m_ptr);
	}
	TargetRef00217D4C *m_ptr;
};

extern "C" void __cdecl Rva00437F61(int type, const UnicodeString &title,
	const UnicodeString &message, Rva0044BF40 callback);

void Rva00412731Close();
void Rva000B3FD0Noop();

class Rva00517345;

class Rva0051759EHandler
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual Int handle(Rva00517345 *screen, UnsignedInt msg, UnsignedByte key, UnsignedInt state);
};

class Rva00517345
{
public:
	virtual Int rva0051759E(UnsignedInt msg, UnsignedByte key, UnsignedInt state);

private:
	char m_pad004[0x280 - 0x004];
	Rva0051759EHandler **m_handlersBegin;	// +0x280
	Rva0051759EHandler **m_handlersEnd;		// +0x284
};

Int Rva00517345::rva0051759E(UnsignedInt msg, UnsignedByte key, UnsignedInt state)
{
	Bool showLogoff = false;
	if (msg == 0x15)
	{
		if (key == 1)
		{
			if (state & 1)
			{
				if (g_Va00E046B8)
				{
					Rva00511730(0);
					return 1;
				}
				showLogoff = true;
			}
		}
		else if ((key == 0x1c || key == 0x9c) && (state & 0xc) && TheGameSpyInfo && TheGameSpyInfo->slot97())
		{
			if (state & 1)
			{
				if (g_Va00E046B8)
					Rva00511730(0);
				else
					Rva005116C2();
			}
			return 1;
		}
	}
	for (Rva0051759EHandler **it = m_handlersBegin; it != m_handlersEnd; ++it)
	{
		if ((*it)->handle(this, msg, key, state) == 1)
			return 1;
	}
	if (showLogoff)
	{
		UnicodeString title = TheGameText->fetch("APT:LogoffConfirmationTitle");
		UnicodeString message = TheGameText->fetch("APT:LogoffConfirmationMsg");
		Rva0044BA4E buttons((Rva004F6986Member(Rva00412731Close)), (Rva004F6986Member(Rva000B3FD0Noop)));
		Rva00437F61(2, title, message, buttons);
	}
	return 0;
}
