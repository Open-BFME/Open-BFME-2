// cl: /DNDEBUG /MD /EHsc
// ??1Display@@UAE@XZ, retail 0x0025D686, 111 bytes.
// Destructor of Display: stores vtable 0x7F5DA0 then runs the field-reset
// helper rva0025D19E and the list-clear rva0025C0FF on the same this, then
// destroys AsciiString at +0xF0/+0xD0 and Unicode string at +0xB0 in reverse
// order, then the SubsystemInterface base dtor.
// Evidence: same-this calls at 0x0025D6A4/0x0025D6AB; vtable shared with ctor
// 0x0025D489 which inits the same D0/E0/E4/C8/CC/F0 fields; base call
// 0x001B4E74; deleting-dtor caller 0x0025DA57.
#define BFME_STRINGBASE_PUBLIC_DTOR
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
// bfme link decl-only begin
template <> StringBase<char>::~StringBase();
// bfme link decl-only end

// Inline destruction uses the owned releaseBuffer worker directly.


class Rva0025C0FF
{
public:
	void rva0025C0FF();
};


class W3DDisplay
{
public:
	void rva0025D2F6();
};

class ListNode0025D9E3
{
public:
	virtual void s000();
	virtual void s001();
	virtual void s002();
	virtual void s003();
	virtual void s004();
	virtual void v005();
	virtual void s006();
	virtual void s007();
	virtual void s008();
	virtual void s009();
	virtual void s010();
	virtual void s011();
	virtual void s012();
	virtual void s013();
	virtual void s014(int x);
	virtual int s015();
	virtual void s016(int y);
	virtual int s017();
	virtual void s018(int x, int y);
	virtual void s019(int *a, int *b);
	virtual void s020();
	virtual void s021();
	virtual void s022();
	virtual void s023();
	virtual void s024();
	virtual void s025();
	virtual void s026();
	virtual void s027();
	virtual void s028();
	virtual void s029();
	virtual void s030();
	virtual void s031();
	virtual void s032();
	virtual void s033();
	virtual void s034();
	virtual void s035();
	virtual void s036();
	virtual void s037();
	virtual void s038();
	virtual void s039();
	virtual void s040();
	virtual void s041();
	virtual void s042();
	virtual void s043();
	virtual void s044();
	virtual void s045();
	virtual void s046();
	virtual void s047();
	virtual void s048();
	virtual void s049();
	virtual void s050();
	virtual void s051();
	virtual void s052();
	virtual void s053();
	virtual void s054();
	virtual void s055();
	virtual void s056();
	virtual void s057();
	virtual void s058();
	virtual void s059();
	virtual void s060();
	virtual void s061();
	virtual void s062();
	virtual void s063();
	virtual void s064();
	virtual void s065();
	virtual void s066();
	virtual void s067();
	virtual void s068();
	virtual void s069();
	virtual void s070();
	virtual void s071();
	virtual void s072();
	virtual void s073();
	virtual void s074();
	virtual void s075();
	virtual void s076();
	virtual void s077();
	virtual void s078();
	virtual void s079();
	virtual void s080();
	virtual void s081();
	virtual void s082();
	virtual void s083();
	virtual void s084();
	virtual void s085();
	virtual void s086();
	virtual void s087();
	virtual void s088();
	virtual void s089();
	virtual void s090();
	virtual void s091();
	virtual void s092();
	virtual void s093();
	virtual void s094();
	virtual void s095();
	virtual void s096();
	virtual void s097();
	virtual void s098();
	virtual void s099();
	virtual void s100();
	virtual void s101();
	virtual void s102();
	virtual void s103();
	virtual void s104();
	virtual void s105();
	virtual void s106();
	virtual void s107();
	virtual void s108();
	virtual void s109();
	virtual void s110();
	virtual void s111();
	virtual void s112();
	virtual void s113();
	virtual void s114();
	virtual void s115();
	virtual void s116();
	virtual void s117();
	virtual void s118();
	virtual void s119();
	virtual void s120();
	virtual void s121();
	virtual void s122();
	virtual void s123();
	virtual void s124();
	virtual void s125();
	virtual void s126();
	virtual void s127();
	virtual void s128();
	virtual void s129();
	virtual void s130();
	virtual void s131();
	virtual void s132();
	virtual void s133();
	virtual void s134();
	virtual void s135();
	virtual void s136();
	virtual void s137();
	virtual void s138();
	virtual void s139();
	virtual void s140();
	virtual void s141();
	virtual void s142();
	virtual void s143();
	virtual void s144();
	virtual void s145();
	virtual void s146();
	virtual void s147();
	virtual void s148();
	virtual void s149();
	virtual void s150();
	virtual void s151();
	virtual ListNode0025D9E3 *getNext();
};

// Base ctor 0x001B4E63 / dtor 0x001B4E74 by their row names ??0/??1SubsystemInterface (SubsystemInterface.cpp).
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

#include "GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

struct GlobalA01E48
{
	char pad[0x5d];
	unsigned char flag;
};
// ?g_Va00A01E48@@3PAUGlobalA01E48@@A: the global at this VA is ?TheShell@@3PAVShell@@A; this name is an alias for it.
class Shell;
extern Shell *TheShell;

struct Rva0025C18BCoord
{
	float x;
	float y;
};

class Display : public SubsystemInterface
{
public:
	virtual ~Display();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27() = 0;
	virtual void v28() = 0;
	virtual void v29() = 0;
	virtual void v30();
	virtual void v31() = 0;
	virtual void v32() = 0;
	virtual void v33() = 0;
	virtual void v34() = 0;
	virtual void v35();
	virtual void v36();
	virtual void v37();
	virtual void rva0025C14D();
	virtual void rva0025C18B(Rva0025C18BCoord *a, Rva0025C18BCoord *b);
	virtual void rva0025C238();
	virtual void v41() = 0;
	virtual void v42() = 0;
	virtual void v43() = 0;
	virtual void v44() = 0;
	virtual void v45() = 0;
	virtual void v46() = 0;
	virtual void v47() = 0;
	virtual void v48() = 0;
	virtual void v49() = 0;
	virtual void v50() = 0;
	virtual void v51() = 0;
	virtual void v52() = 0;
	virtual void v53() = 0;
	virtual void v54() = 0;
	virtual void v55() = 0;
	virtual void v56() = 0;
	virtual void v57() = 0;
	virtual void v58() = 0;
	virtual void v59() = 0;
	virtual void v60() = 0;
	virtual void v61() = 0;
	virtual void v62() = 0;
	virtual void v63() = 0;
	virtual void v64() = 0;
	virtual void v65() = 0;
	virtual void v66();
	virtual void v67();
	virtual void v68();
	void rva0025D19E();
	void reset();
	void rva00049F94(AsciiString s);
private:
	char m_pad0C[0x10];
	ListNode0025D9E3 *m_head1C;
	char m_pad20[0x90];
	StringBase<unsigned short> m_sB0;
	int m_iB4;
	int m_iB8;
	int m_iBC;
	float m_fC0;
	float m_fC4;
	float m_fC8;
	float m_fCC;
	StringBase<char> m_sD0;
	float m_fD4;
	bool m_bD8;
	char m_padD9[0x17];
	StringBase<char> m_sF0;
	char m_padF4[0x1C];
	char m_pad110[0x04];
	bool m_b114;
	char m_pad115[0x0B];
	float m_f120;
	char m_tail[0x22];
};

Display::~Display()
{
	rva0025D19E();
	((Rva0025C0FF *)this)->rva0025C0FF();
}

// ?rva0025D358 (0x0025D358, the UnicodeString setter of the +0xB0 block) lives in
// BfmeStrVM0SetText.cpp, which includes the canonical unicode_string.h.

// ?reset@Display@@QAEXXZ, retail 0x0025D9E3, 116 bytes.
// Slot-9 virtual of Display: when +0x114 is clear, zeroes +0xD4/+0xD8, runs
// the slot-68 virtual plus the W3DDisplay clear helper; then always clears
// +0x114/+0x120, walks the +0x1C list via slot-5 plus getNext, and zeroes
// +0xC8/+0xCC.
// Evidence: vtable slot 9 of 0x7F5DA0; same +0xB0/+0xC8/+0xD0/+0x114/+0x120
// layout as this TU and ctor 0x0025D489; callees slot-68 plus rowed
// rva0025D2F6 plus node slots 5/152; caller 0x00043427.
void Display::reset()
{
	if (m_b114 == 0)
	{
		m_fD4 = 0.0f;
		m_bD8 = 0;
		v68();
		((W3DDisplay *)this)->rva0025D2F6();
	}
	ListNode0025D9E3 *cur = m_head1C;
	m_b114 = 0;
	m_f120 = 0.0f;
	if (cur != 0)
	{
		ListNode0025D9E3 *next;
		do
		{
			cur->v005();
			next = cur->getNext();
			cur = next;
		} while (next != 0);
	}
	m_fC8 = 0.0f;
	m_fCC = 0.0f;
}

// ?rva0025C14D@Display@@UAEXXZ, retail 0x0025C14D, 62 bytes.
// Slot-38 virtual of Display: unless the GameLogic mode predicate says
// otherwise with the global 0xA01E48 byte at +0x5D set, walks the +0x1C
// node list calling slot-94 on each node and advancing via getNext.
// Evidence: vtable slot 38 of 0x7F5DA0; same +0x1C list as reset and
// rva0025C18B in this TU; callees rowed rva00085124 0x00085124 plus node
// slots 94/152 predeclared in this TU; no callers.
void Display::rva0025C14D()
{
	if (TheGameLogic->rva00085124())
	{
		if (((GlobalA01E48 *)TheShell)->flag != 0)
			return;
	}
	ListNode0025D9E3 *node = m_head1C;
	while (node != 0)
	{
		node->s094();
		node = node->getNext();
	}
}

// ?rva0025C18B@Display@@UAEXPAURva0025C18BCoord@@0@Z, retail 0x0025C18B, 173 bytes.
// Slot-39 virtual of Display: walks the +0x1C node list; per node it takes
// two no-arg ints plus an out-pair, converts both float args to int for the
// first round of node slots, then replays the saved values through the same
// slots and advances via getNext.
// Evidence: vtable slot 39 of 0x7F5DA0; same +0x1C list as reset in this
// TU; node slots 14-19/94/152 predeclared in this TU; no callers.
void Display::rva0025C18B(Rva0025C18BCoord *a, Rva0025C18BCoord *b)
{
	ListNode0025D9E3 *node = m_head1C;
	while (node != 0)
	{
		int t15 = node->s015();
		int t17 = node->s017();
		int t8;
		int t4;
		node->s019(&t8, &t4);
		node->s014((int)b->x);
		node->s016((int)b->y);
		node->s018((int)a->x, (int)a->y);
		node->s094();
		node->s014(t15);
		node->s016(t17);
		node->s018(t8, t4);
		node = node->getNext();
	}
}

// ?rva00049F94@Display@@QAEXVAsciiString@@@Z, retail 0x00049F94, 55 bytes.
// Slot-89 virtual of Display: sets the +0xF0 AsciiString from a by-value
// string arg; the by-value temp is released at the end under EH.
// Evidence: vtable slot 89 of 0x7F5DA0; same +0xF0 layout as the dtor in this
// TU; callees AsciiString::operator= 0x000366F0 plus releaseBuffer 0x00036410.
void Display::rva00049F94(AsciiString s)
{
	AsciiString &dst = *(AsciiString *)&m_sF0;
	dst = s;
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.

// ?rva0025C238@Display@@UAEXXZ, retail 0x0025C238 (34 bytes), slot 40 next to the slot-38
// walker above: every node of the +0x1C list gets its slot-95 step, unconditionally.
void Display::rva0025C238()
{
	for (ListNode0025D9E3 *node = m_head1C; node != 0; node = node->getNext())
		node->s095();
}

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?v02@Display@@UAEXXZ=?loadIniFilesFromLegend@SubsystemInterface@@UAE_NXZ")
#pragma comment(linker, "/alternatename:?v10@Display@@UAEXXZ=?update@Display@@QAEXXZ")
#pragma comment(linker, "/alternatename:?v12@Display@@UAEXXZ=?rva0025C25A@Rva0025C25AForwarder@@QAEXXZ")
#pragma comment(linker, "/alternatename:?v18@Display@@UAEXXZ=?set@Rva002B22A5DwordSlot@@QAEXH@Z")
#pragma comment(linker, "/alternatename:?v20@Display@@UAEXXZ=?set@Rva00049F2BByteSlot@@QAEXE@Z")
#pragma comment(linker, "/alternatename:?v22@Display@@UAEXXZ=?setDisplayMode@Display@@UAE_NIII_N@Z")
#pragma comment(linker, "/alternatename:?v24@Display@@UAEXXZ=?rva001F01E8@Rva001F01E8@@QAEXHHHH@Z")
#pragma comment(linker, "/alternatename:?v25@Display@@UAEXXZ=?rva001F01E8@Rva001F01E8@@QAEXHHHH@Z")
#pragma comment(linker, "/alternatename:?v26@Display@@UAEXXZ=?testMinSpecRequirements@Display@@UAE_NPA_N00PAW4StaticGameLODLevel@@PAM@Z")
#pragma comment(linker, "/alternatename:?v37@Display@@UAEXXZ=?rva00049F4F@W3DDisplay@@QAEHPAVRva00049F4FObject@@@Z")
#pragma comment(linker, "/alternatename:?v66@Display@@UAEXXZ=?rva0025C97E@Display@@UAE_NVAsciiString@@HHH@Z")
#pragma comment(linker, "/alternatename:?v67@Display@@UAEXXZ=?rva0025D6F5@W3DDisplay@@QAE_NVAsciiString@@_NH@Z")
