// cl: /O1 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
//
// Opaque scalar deleting destructors, batch B12: 28-byte wrappers that
// call the destructor, test bit 0 of the flags, conditionally free through
// operator delete (0x0002FD60) and return this (ret 4), found in vtable slots
// with no ledger owner (vtable bounds taken from the constructor vptr stores
// in .text; slots shared by three or more vtables are not counted as owners).
// Each destructor is declared, not defined, so the call resolves to its pin
// in reverse/symbols.csv; the dummy tag constructors (no retail counterpart)
// only make this TU emit each vtable and with it the deleting destructor.
// Owner identities are not recovered, and these declarations model no layout
// beyond the thunk-proven secondary bases noted where they are declared
// (docs/reconstruction/deleting-destructor-identity-audit.md).
//
//   wrapper     dtor        vtable#slot
//   0x0051588B  0x00514EAB  0x00C65F10#0
//   0x00517582  0x005173F8  0x00C66428#0
//   0x00521CE3  0x00521977  0x00C67910#0
//   0x0052B40F  0x0052B3B2  0x00C685E0#0
//   0x0052B56C  0x0052B497  0x00C68620#0
//   0x005394D4  0x0053947D  0x00C69228#0
//   0x0053DAE6  0x00567A69  0x00C67E60#0, 0x00C67E70#0, 0x00C69310#0, 0x00C6CEA4#0, 0x00C794D4#0, 0x00C794DC#0
//   0x00551323  0x0055133F  0x00C6AC0C#0
//   0x00568629  0x005685EE  0x00C6CF74#0
//   0x0056B0A3  0x0056AD19  0x00C6D1EC#0
//   Rva0056B188's wrapper is emitted by its real MI lifetime unit.
//   0x0056BAA3  0x0056B9A2  0x00C6D810#0
//   0x0056D61F  0x0056D3FD  0x00C6DAA4#0
//   0x0056D74F  0x0056D690  0x00C6DAC4#0
//   0x0056DC2A  0x0056D915  0x00C6DB40#0
//   0x00574693  0x00574338  0x00C6E39C#0

struct EmitVtableTag;

// AptCreateAHero deleting destructor is emitted by its real owning destructor.

// Target514EAB/120B is a destructor, as existing deletingwrapper51588B
// and the EH teardown prove. It installs primaryC65F10/secondaryC65F0C,
// closes the20B resource290 when globalE048DC equals this, clears the
// global, releases string2A4, destroys resource290, and calls APT base5126F5.
// Resource teardown32B reads only optional pointers0/4; close34B releases
// COM pointer10 and tests status0C. Both complete providers are verified.
// Reuse the new base5126F5 consumed-prefix view identically; padding274
// does not assert which portion belongs to the original base. Full owner
// size, original name and unused fields remain unknown.
#include "../../Include/GameClient/Bfme2GameWindow.h"
#include "../../Include/GameClient/Rva005248D0.h"
#include "ascii_string.h"
class _bfme_AptGameWindow : public GameWindow, public Rva005248D0 {
public: virtual ~_bfme_AptGameWindow();
private: AsciiString filename270;
};

// The two established providers consume the same +290 resource: its array
// destructor reads pointers0/4, while close reads status0C and COM pointer10.
// Use their existing names directly; the original resource type remains unknown.
class Rva005B7010 { public: void rva005B7010(); };
class BfmeThingTTD {
public: ~BfmeThingTTD();
private: void* first;void* second;unsigned int unknown08;int status0C;void* com10;
};
class AptMainMenu : public _bfme_AptGameWindow {
public: AptMainMenu(EmitVtableTag*);virtual ~AptMainMenu();
private: unsigned char unknown274[0x1c];BfmeThingTTD resource290;AsciiString str2A4;
};
// ?<AptMainMenu::AptMainMenu> absent-from-retail
AptMainMenu::AptMainMenu(EmitVtableTag *)
{
}

// Rva005173F8's two tables (data ledger): GameWindow at +0 and Rva005248D0 at +0x218, whose
// slot 0 is a this-adjusting (sub ecx, 0x218) deleting-destructor thunk.
class Rva005173F8 : public GameWindow, public Rva005248D0
{
public:
	Rva005173F8(EmitVtableTag *);
public:
	virtual ~Rva005173F8();
};

// ?<Rva005173F8::Rva005173F8> absent-from-retail
Rva005173F8::Rva005173F8(EmitVtableTag *)
{
}

// 0x005206E2 and its thunk 0x005204E4 are AptTimeLine's (??_GRva005202C8,
// ??_ERva005202C8), emitted with its vtable in AptTimeLineCtor.cpp.

// ??_GAptSkirmish (0x00521CE3) is emitted with the AptSkirmish vtable in
// AptSkirmishDestructor.cpp.

class Rva0052B497
{
public:
	Rva0052B497(EmitVtableTag *);
public:
	virtual ~Rva0052B497();
};

// ?<Rva0052B497::Rva0052B497> absent-from-retail
Rva0052B497::Rva0052B497(EmitVtableTag *)
{
}

class Rva0053947D
{
public:
	Rva0053947D(EmitVtableTag *);
public:
	virtual ~Rva0053947D();
	virtual void v01();
	virtual void rva005391D3();
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
	virtual int v13();
	virtual void v14();
	virtual void *v15(int i);
	unsigned char m_list_storage[0x14];
};

// ?<Rva0053947D::Rva0053947D> absent-from-retail
Rva0053947D::Rva0053947D(EmitVtableTag *)
{
}

// The 0x0052B3B2 dtor calls this address on the complete object before it
// releases the ref at +0x40 and the pointer array at +0x2c. Its exact body is
// blocked separately; the call site and its 59-byte boundary establish the
// callee address, not the helper's identity.
#include "../../Include/Common/Rva0052B23D.h"

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);

namespace _STL
{
	void __cdecl free(void *p);
}

class Rva0052B3B2Buffer
{
public:
	~Rva0052B3B2Buffer()
	{
		if (m_begin)
			_STL::free(m_begin);
	}

	void **m_begin;
	void **m_end;
	void **m_capacity;
};

class Rva0052B3B2Ref
{
public:
	~Rva0052B3B2Ref()
	{
		if (m_ref)
			ReleaseTreeHintRef00217D4C(m_ref);
	}

	TargetRef00217D4C *m_ref;
};

class Rva0052B3B2 : public Rva0053947D
{
public:
	Rva0052B3B2(EmitVtableTag *);
	virtual ~Rva0052B3B2();

	unsigned char m_gap_18_2B[0x14];
	Rva0052B3B2Buffer m_buffer;
	unsigned char m_gap_38_3F[8];
	Rva0052B3B2Ref m_ref;
};

// ?<Rva0052B3B2::Rva0052B3B2> absent-from-retail
Rva0052B3B2::Rva0052B3B2(EmitVtableTag *tag) : Rva0053947D(tag)
{
}

Rva0052B3B2::~Rva0052B3B2()
{
	((Rva0052B23D *)this)->rva0052B23D();
}

class Rva00567A69
{
public:
	Rva00567A69(EmitVtableTag *);
public:
	virtual ~Rva00567A69();
};

// ?<Rva00567A69::Rva00567A69> absent-from-retail
Rva00567A69::Rva00567A69(EmitVtableTag *)
{
}

class Rva0055133F
{
public:
	Rva0055133F(EmitVtableTag *);
public:
	virtual ~Rva0055133F();
};

// ?<Rva0055133F::Rva0055133F> absent-from-retail
Rva0055133F::Rva0055133F(EmitVtableTag *)
{
}

class Rva005685EE
{
public:
	Rva005685EE(EmitVtableTag *);
public:
	virtual ~Rva005685EE();
};

// ?<Rva005685EE::Rva005685EE> absent-from-retail
Rva005685EE::Rva005685EE(EmitVtableTag *)
{
}

// Rva0056AD19's two tables (data ledger): Rva0056AC26A at +0 (vptr plus one word) and
// Rva0056AC26B at +0x8, whose slot 0 is a this-adjusting (sub ecx, 8)
// deleting-destructor thunk -- target evidence for that base and offset.
#include "../../Include/Common/Rva0056AC26A.h"
#include "../../Include/Common/Rva0056AC26B.h"
class Rva0056AD19 : public Rva0056AC26A, public Rva0056AC26B
{
public:
	Rva0056AD19(EmitVtableTag *);
public:
	virtual ~Rva0056AD19();
};

// ?<Rva0056AD19::Rva0056AD19> absent-from-retail
Rva0056AD19::Rva0056AD19(EmitVtableTag *)
{
}

class Rva0056B9A2
{
public:
	Rva0056B9A2(EmitVtableTag *);
public:
	virtual ~Rva0056B9A2();
};

// ?<Rva0056B9A2::Rva0056B9A2> absent-from-retail
Rva0056B9A2::Rva0056B9A2(EmitVtableTag *)
{
}

class Rva0056D3FD
{
public:
	Rva0056D3FD(EmitVtableTag *);
public:
	virtual ~Rva0056D3FD();
};

// ?<Rva0056D3FD::Rva0056D3FD> absent-from-retail
Rva0056D3FD::Rva0056D3FD(EmitVtableTag *)
{
}

class Rva0056D690
{
public:
	Rva0056D690(EmitVtableTag *);
public:
	virtual ~Rva0056D690();
};

// ?<Rva0056D690::Rva0056D690> absent-from-retail
Rva0056D690::Rva0056D690(EmitVtableTag *)
{
}

class Rva0056D915
{
public:
	Rva0056D915(EmitVtableTag *);
public:
	virtual ~Rva0056D915();
};

// ?<Rva0056D915::Rva0056D915> absent-from-retail
Rva0056D915::Rva0056D915(EmitVtableTag *)
{
}

class Rva00574338
{
public:
	Rva00574338(EmitVtableTag *);
public:
	virtual ~Rva00574338();
};

// ?<Rva00574338::Rva00574338> absent-from-retail
Rva00574338::Rva00574338(EmitVtableTag *)
{
}

// AptMainMenu's destructor 0x00514EAB: it installs vftable 0x00C65F10, which
// the AptMainMenu constructor 0x00516211 installs (WorldBuilder lead 28.4),
// and clears the instance global g_Va00E048DC that the AptMainMenu
// callbacks test; WorldBuilder's twin asserts the same s_instance.
extern int g_Va00E048DC;
AptMainMenu::~AptMainMenu() {
 if(g_Va00E048DC==reinterpret_cast<int>(this)) {reinterpret_cast<Rva005B7010 *>(&resource290)->rva005B7010();g_Va00E048DC=0;}
}
