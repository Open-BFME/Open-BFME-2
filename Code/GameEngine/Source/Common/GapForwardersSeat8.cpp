// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Member forwarders from unrowed .text gaps: each adjusts or loads the
// receiver and tail-jumps a rowed callee, called through that row's own
// spelling. Owners are not recovered, so each keeps an address-derived name
// and a view of only the member it reaches. Skeletons match the matched
// wide-adjust forwarders (RvaWideAdjustFwds.cpp) and the guarded
// member-pointer forwarders.

#include "../../Include/Common/Rva0040A59B.h"

class Dict;
class TeamsInfoRec
{
public:
	int addTeam(const Dict *d);
};

#include "../../Include/Common/BfmeDfe6e4.h"

// --- 0x00219435 (11B): +0x174 then the rowed 0x0040A59B.
class Rva00219435
{
public:
	void rva00219435();
private:
	char m_pad000[0x174];
	Rva0040A59B m_174;
};
void Rva00219435::rva00219435()
{
	m_174.rva0040A59B();
}

// --- 0x0023C60E (11B): +0xF44 then the rowed TeamsInfoRec::addTeam
// 0x0032DA4E with the stack argument passed through (the shape of Zero
// Hour's inline SidesList::addTeam forwarding to its team record; the owner
// is not proven here).
class Rva0023C60E
{
public:
	int rva0023C60E(const Dict *d);
private:
	char m_pad000[0xF44];
	TeamsInfoRec m_teams;
};
int Rva0023C60E::rva0023C60E(const Dict *dict)
{
	return m_teams.addTeam(dict);
}

// --- 0x0023C4A1 (12B): calls the rowed 0x00225476 on the pointer at +0
// when it is set.
class Rva0023C4A1
{
public:
	void rva0023C4A1();
private:
	BfmeDfe6e4 *m_target;
};
void Rva0023C4A1::rva0023C4A1()
{
	if (m_target)
		m_target->_M_rva00625476();
}

// --- 8-byte receiver-adjust forwarders (add ecx, imm8; jmp rowed callee),
// the skeleton of ??1PlayerPosition 0x0022D920. Stack arguments pass
// through; each callee keeps its ledger spelling.
#include "../../Include/Common/RvaSmartPtr12.h"
#include "../../Include/GameLogic/Rva00283002.h"
enum ScienceType { };
#include "../../Include/Common/Player.h"
class DataChunkInput;
#include "../../Include/Common/ElevatedAreaPolygon.h"
struct Rva0030B7C2Point;
class Rva002E37B1 { public: bool rva002E37B1(const Rva0030B7C2Point *point); };	// 0x002E37B1
#include "../../Include/Common/Rva003184B8.h"
#include "../../Include/GameLogic/Rva0030B719Shape.h"

// --- 0x001F4A1A: +0x78 then RvaSmartPtr12::operator=.
class Rva001F4A1A
{
public:
	RvaSmartPtr12 &rva001F4A1A(const RvaSmartPtr12 &other);
private:
	char m_pad00[0x78];
	RvaSmartPtr12 m_78;
};
RvaSmartPtr12 &Rva001F4A1A::rva001F4A1A(const RvaSmartPtr12 &other)
{
	return m_78 = other;
}

// --- 0x0028339B: +0x64 then the rowed list clear 0x00283002.
class Rva0028339B
{
public:
	void rva0028339B();
private:
	char m_pad00[0x64];
	Rva00283002 m_64;
};
void Rva0028339B::rva0028339B()
{
	m_64.rva00283002();
}

// --- 0x002B118A: from a sub-object at +4 of a Player back to
// Player::hasScience.
class Rva002B118A
{
public:
	bool rva002B118A(ScienceType science) const;
};
bool Rva002B118A::rva002B118A(ScienceType science) const
{
	return ((const Player *)((const char *)this - 4))->hasScience(science);
}

// --- 0x002E36AF: +8 then ElevatedAreaPolygon::parse.
class Rva002E36AF
{
public:
	void rva002E36AF(DataChunkInput &file, int val);
private:
	char m_pad00[8];
	ElevatedAreaPolygon m_08;
};
void Rva002E36AF::rva002E36AF(DataChunkInput &file, int val)
{
	m_08.parse(file, val);
}

// --- 0x002E37C3: from a sub-object at +0x38 back to the rowed 0x002E37B1.
class Rva002E37C3
{
public:
	bool rva002E37C3(const Rva0030B7C2Point *point);
};
bool Rva002E37C3::rva002E37C3(const Rva0030B7C2Point *point)
{
	return ((Rva002E37B1 *)((char *)this - 0x38))->rva002E37B1(point);
}

// --- 0x003187A0: from a sub-object at +0xC back to the rowed 0x003184B8.
class Rva003187A0
{
public:
	void rva003187A0();
};
void Rva003187A0::rva003187A0()
{
	((Rva003184B8 *)((char *)this - 0xC))->rva003184B8();
}

// --- 0x00330A9E: +8 then the rowed shape getter 0x0030B706 (float).
class Rva00330A9E
{
public:
	float rva00330A9E() const;
private:
	char m_pad00[8];
	Rva0030B719Shape m_08;
};
float Rva00330A9E::rva00330A9E() const
{
	return m_08.rva0030B706();
}

// --- 0x002714B4 (22B): TheAudio (VA 0x00DFE6E8) slot 52 (+0xD0) with the
// sound handle at +0x144.
class Rva002714B4Audio
{
public:
#define V(n) virtual void slot##n();
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09) V(10) V(11)
	V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31) V(32) V(33) V(34) V(35)
	V(36) V(37) V(38) V(39) V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47)
	V(48) V(49) V(50) V(51)
#undef V
	virtual void slot52(unsigned int handle);
};
class AudioManager;
extern AudioManager *TheAudio;
class Rva002714B4
{
public:
	void rva002714B4();
private:
	char m_pad000[0x144];
	unsigned int m_handle;
};
void Rva002714B4::rva002714B4()
{
	((Rva002714B4Audio *)TheAudio)->slot52(m_handle);
}

// --- 0x00313923 (23B, RET4): TheWindowManager (VA 0x00DFEF1C) slot 60
// (+0xF0) with the receiver and the stack argument.
class Rva00313923;
class Rva00313923Manager
{
public:
#define V(n) virtual void slot##n();
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09) V(10) V(11)
	V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31) V(32) V(33) V(34) V(35)
	V(36) V(37) V(38) V(39) V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47)
	V(48) V(49) V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58) V(59)
#undef V
	virtual void slot60(Rva00313923 *window, int value);
};
class GameWindowManager;
extern GameWindowManager *TheWindowManager;
class Rva00313923
{
public:
	void rva00313923(int value);
};
void Rva00313923::rva00313923(int value)
{
	((Rva00313923Manager *)TheWindowManager)->slot60(this, value);
}

// --- Additional receiver-adjust forwarders (8B and 11B) ---------------------
class AsciiString;
class Xfer;
class Rva004E194E;

#include "../../Include/Common/ArmySummarySystem.h"

namespace _STL
{
template <class T> class allocator;
template <class T, class A> class vector
{
public:
	void push_back(const T &);
};
}

class Rva0023D012 { public: int rva0023D012(int a); private: char m_pad[0x184]; ArmySummarySystem m_184; };
int Rva0023D012::rva0023D012(int a) { return m_184.rva0040D025(a); }

class Rva0023D01D { public: const AsciiString *rva0023D01D(int a); private: char m_pad[0x184]; ArmySummarySystem m_184; };
const AsciiString *Rva0023D01D::rva0023D01D(int a) { return m_184.rva0040D041(a); }

class Rva00566557
{
public:
	void rva00566557(const Rva004E194E &v);
private:
	char m_pad[0x6C];
	_STL::vector<Rva004E194E, _STL::allocator<Rva004E194E> > m_6c;
};
void Rva00566557::rva00566557(const Rva004E194E &v) { m_6c.push_back(v); }

struct EmitVtableTag;

#define DEFINE_THUNK_UAE_TAG(Cls, Meth, Off, ArgDecl, Tag) \
	struct Cls##_BaseA { virtual void Meth ArgDecl = 0; char m_pad[(Off) - 4]; }; \
	struct Cls##_BaseB { virtual void Meth ArgDecl = 0; }; \
	class Cls : public Cls##_BaseA, public Cls##_BaseB \
	{ \
	public: \
		Cls(Tag *); \
		virtual void Meth ArgDecl; \
	}; \
	Cls::Cls(Tag *) {}

#define DEFINE_THUNK_UAE(Cls, Meth, Off, ArgDecl) \
	DEFINE_THUNK_UAE_TAG(Cls, Meth, Off, ArgDecl, EmitVtableTag)

#define DEFINE_THUNK_MAE(Cls, Meth, Off, ArgDecl) \
	struct Cls##_BaseA { protected: virtual void Meth ArgDecl = 0; char m_pad[(Off) - 4]; }; \
	struct Cls##_BaseB { protected: virtual void Meth ArgDecl = 0; }; \
	class Cls : public Cls##_BaseA, public Cls##_BaseB \
	{ \
	public: \
		Cls(EmitVtableTag *); \
	protected: \
		virtual void Meth ArgDecl; \
	}; \
	Cls::Cls(EmitVtableTag *) {}

// ?<Rva003A57A9::Rva003A57A9> absent-from-retail
DEFINE_THUNK_UAE(Rva003A57A9, DoXfer, 0x0C, (Xfer &))
// ?<Rva003AE94E::Rva003AE94E> absent-from-retail
DEFINE_THUNK_UAE(Rva003AE94E, xfer, 0x18, (Xfer *))
// ?<Rva0055B30F::Rva0055B30F> absent-from-retail
DEFINE_THUNK_UAE(Rva0055B30F, rva0055B30F, 0x1C, (Xfer *))
// ?<Rva0055B951::Rva0055B951> absent-from-retail
DEFINE_THUNK_UAE(Rva0055B951, rva0055B951, 0x1C, (Xfer *))
// ?<Rva0055EF39::Rva0055EF39> absent-from-retail
DEFINE_THUNK_UAE(Rva0055EF39, xfer, 0x1C, (Xfer *))
// ?<Rva0055F710::Rva0055F710> absent-from-retail
DEFINE_THUNK_UAE(Rva0055F710, rva0055F710, 0x1C, (Xfer *))
// ?<Rva0055DB41::Rva0055DB41> absent-from-retail
DEFINE_THUNK_UAE(Rva0055DB41, DoXfer, 0x1C, (Xfer &))
// ?<Rva0055CA8A::Rva0055CA8A> absent-from-retail
DEFINE_THUNK_MAE(Rva0055CA8A, xfer, 0x1C, (Xfer *))
// ?<Rva0055CD38::Rva0055CD38> absent-from-retail
DEFINE_THUNK_UAE(Rva0055CD38, rva0055CD38, 0x1C, (Xfer *))
// ?<Rva0055D3F5::Rva0055D3F5> absent-from-retail
DEFINE_THUNK_UAE(Rva0055D3F5, rva0055D3F5, 0x1C, (Xfer *))
// ?<Rva003AF22E::Rva003AF22E> absent-from-retail
DEFINE_THUNK_MAE(Rva003AF22E, xfer, 0x18, (Xfer *))
// ?<Rva0055B3D9::Rva0055B3D9> absent-from-retail
DEFINE_THUNK_UAE(Rva0055B3D9, xfer, 0x0C, (Xfer *))
// ?<Rva0055BB5C::Rva0055BB5C> absent-from-retail
DEFINE_THUNK_UAE(Rva0055BB5C, rva0055BB5C, 0x0C, (Xfer *))
// ?<Rva0055F805::Rva0055F805> absent-from-retail
DEFINE_THUNK_UAE(Rva0055F805, rva0055F805, 0x0C, (Xfer *))
// ?<Rva003AE0AF::Rva003AE0AF> absent-from-retail
DEFINE_THUNK_MAE(Rva003AE0AF, xfer, 0x10, (Xfer *))
// ?<Rva003AE2A9::Rva003AE2A9> absent-from-retail
DEFINE_THUNK_MAE(Rva003AE2A9, xfer, 0x10, (Xfer *))
// ?<Rva005E62F1::Rva005E62F1> absent-from-retail
DEFINE_THUNK_UAE(Rva005E62F1, rva0050B238, 0x20, (void *, unsigned int))
// ?<Rva00562945::Rva00562945> absent-from-retail
DEFINE_THUNK_UAE(Rva00562945, rva00562945, 0x18, (Xfer *))
// ?<Rva00561527::Rva00561527> absent-from-retail
DEFINE_THUNK_UAE(Rva00561527, rva00561527, 0x18, (Xfer *))
// ?<Rva00563ED1::Rva00563ED1> absent-from-retail
DEFINE_THUNK_UAE(Rva00563ED1, rva00563ED1, 0x20, (Xfer *))
// ?<Rva00562233::Rva00562233> absent-from-retail
DEFINE_THUNK_UAE(Rva00562233, rva00562233, 0x1C, (Xfer *))
// ?<Rva005644A9::Rva005644A9> absent-from-retail
DEFINE_THUNK_UAE(Rva005644A9, rva005644A9, 0x20, (Xfer *))
// ?<Rva0056234A::Rva0056234A> absent-from-retail
DEFINE_THUNK_UAE(Rva0056234A, rva0056234A, 0x0C, (Xfer *))
// ?<Rva0055EFC5::Rva0055EFC5> absent-from-retail
DEFINE_THUNK_UAE(Rva0055EFC5, rva0055EFC5, 0x0C, (Xfer *))
// ?<Rva003A5757::Rva003A5757> absent-from-retail
DEFINE_THUNK_UAE(Rva003A5757, rva003A5757, 0x1C, (Xfer *))
struct Parent0057605D;
// ?<Rva005756B6::Rva005756B6> absent-from-retail
struct Parent00575EEA;
struct Parent00575E4E;
struct Rva005756B6_BaseA
{
	virtual void rva00576388(Parent00575EEA *) = 0;
	virtual void rva00576105(Parent0057605D *) = 0;
	virtual void rva00576323(Parent00575E4E *) = 0;
};
struct Rva005756B6_BaseB
{
	virtual void rva00576388(Parent00575EEA *) = 0;
	virtual void rva00576105(Parent0057605D *) = 0;
	virtual void rva00576323(Parent00575E4E *) = 0;
};
class Rva005756B6 : public Rva005756B6_BaseA, public Rva005756B6_BaseB
{
public:
	Rva005756B6(EmitVtableTag *);
	virtual void rva00576388(Parent00575EEA *);
	virtual void rva00576105(Parent0057605D *);
	virtual void rva00576323(Parent00575E4E *);
};
Rva005756B6::Rva005756B6(EmitVtableTag *) {}
// ?<Rva005E6B8F::Rva005E6B8F> absent-from-retail
DEFINE_THUNK_UAE(Rva005E6B8F, rva005E6B8F, 0x08, ())
// ?<Rva0047E33F::Rva0047E33F> absent-from-retail
DEFINE_THUNK_UAE(Rva0047E33F, rva0047E33F, 0x20, (int, int))
// ?<Rva005E5554::Rva005E5554> absent-from-retail
DEFINE_THUNK_UAE(Rva005E5554, step, 0x08, ())
namespace FXParticleSystem {
// Keep this emission-only constructor distinct from the deleting-dtor view.
struct WindTransferEmitTag;
// ?<Rva005FEA50Base::Rva005FEA50Base> absent-from-retail
// This emission-only constructor emits the adjusting wrapper.
DEFINE_THUNK_UAE_TAG(Rva005FEA50Base, DoXfer, 0x1C, (Xfer &), WindTransferEmitTag)
}
// ?<Rva00085947::Rva00085947> absent-from-retail
DEFINE_THUNK_UAE(Rva00085947, rva00085947, 0xB4, ())
// W3DView's secondary base at +0xB4 (vtable 0x007C7530) also declares init.
// ?<W3DView::W3DView> absent-from-retail
DEFINE_THUNK_UAE(W3DView, init, 0xB4, ())
// ?<Rva0030817A::Rva0030817A> absent-from-retail
DEFINE_THUNK_UAE(Rva0030817A, rva0030817A, 0x30, (int))
struct Rva004543A9LeaNegSbbField_BaseA { virtual int get() const = 0; char m_pad[0x14 - 4]; };
struct Rva004543A9LeaNegSbbField_BaseB { virtual int get() const = 0; };
class Rva004543A9LeaNegSbbField : public Rva004543A9LeaNegSbbField_BaseA, public Rva004543A9LeaNegSbbField_BaseB
{
public:
	Rva004543A9LeaNegSbbField(EmitVtableTag *);
	virtual int get() const;
};
// ?<Rva004543A9LeaNegSbbField::Rva004543A9LeaNegSbbField> absent-from-retail
Rva004543A9LeaNegSbbField::Rva004543A9LeaNegSbbField(EmitVtableTag *) {}
struct Rva00472444Mask;
// ?<Rva005E549E::Rva005E549E> absent-from-retail
DEFINE_THUNK_UAE(Rva005E549E, rva005E549E, 0x08, ())
// ?<Rva00472444::Rva00472444> absent-from-retail
DEFINE_THUNK_UAE(Rva00472444, rva00472444, 0xFC, (const Rva00472444Mask &, const AsciiString *))
struct Rva00575CA6_BaseA { virtual void rva00575CA6() = 0; };
struct Rva00575CA6_BaseB { virtual void rva00575CA6() = 0; };
class Rva00575CA6 : public Rva00575CA6_BaseA, public Rva00575CA6_BaseB
{
public:
	Rva00575CA6(EmitVtableTag *);
	virtual void rva00575CA6();
};
// ?<Rva00575CA6::Rva00575CA6> absent-from-retail
Rva00575CA6::Rva00575CA6(EmitVtableTag *) {}
struct Rva00575CAE_BaseA { virtual void rva00575CAE(void *) = 0; };
struct Rva00575CAE_BaseB { virtual void rva00575CAE(void *) = 0; };
class Rva00575CAE : public Rva00575CAE_BaseA, public Rva00575CAE_BaseB
{
public:
	Rva00575CAE(EmitVtableTag *);
	virtual void rva00575CAE(void *);
};
// ?<Rva00575CAE::Rva00575CAE> absent-from-retail
Rva00575CAE::Rva00575CAE(EmitVtableTag *) {}

namespace FXParticleSystem
{
// ?<BoxEmissionVolumeModule::BoxEmissionVolumeModule> absent-from-retail
DEFINE_THUNK_MAE(BoxEmissionVolumeModule, xfer, 0x1C, (Xfer *))
// ?<OrthoEmissionVelocityModule::OrthoEmissionVelocityModule> absent-from-retail
DEFINE_THUNK_MAE(OrthoEmissionVelocityModule, xfer, 0x18, (Xfer *))
// ?<CylindricalEmissionVelocityModule::CylindricalEmissionVelocityModule> absent-from-retail
DEFINE_THUNK_MAE(CylindricalEmissionVelocityModule, xfer, 0x18, (Xfer *))
}

class Object { public: virtual void *slot() const; };
class Rva00299CA8DwordSlot { public: void set(int); int get() const; };
class Rva00299CCE { public: void *get() const; };
class Rva00299CDD { public: float get() const; };
class Rva005E3AA2Mid { public: void fwd(); };
class Rva005E3E41 { public: void rva005E3E41(); };
class Rva005E4389 { public: void rva005E4389(); };
class Rva005E51D3 { public: void rva005E51D3(); };

class Rva00299C91 { public: void *rva00299C91() const; };
void *Rva00299C91::rva00299C91() const { return ((const Object *)((const char *)this - *(const int *)((const char *)this - 4)))->Object::slot(); }

class Rva00299CA0 { public: void rva00299CA0(int a); };
void Rva00299CA0::rva00299CA0(int a) { ((Rva00299CA8DwordSlot *)((char *)this - *(int *)((char *)this - 4)))->set(a); }

class Rva00299CB2 { public: int rva00299CB2() const; };
int Rva00299CB2::rva00299CB2() const { return ((const Rva00299CA8DwordSlot *)((const char *)this - *(const int *)((const char *)this - 4)))->get(); }

class Rva00299CC6 { public: void *rva00299CC6() const; };
void *Rva00299CC6::rva00299CC6() const { return ((const Rva00299CCE *)((const char *)this - *(const int *)((const char *)this - 4)))->get(); }

class Rva00299CD5 { public: float rva00299CD5() const; };
float Rva00299CD5::rva00299CD5() const { return ((const Rva00299CDD *)((const char *)this - *(const int *)((const char *)this - 4)))->get(); }

class Rva005E3D84 { public: void rva005E3D84(); };
void Rva005E3D84::rva005E3D84() { ((Rva005E3AA2Mid *)((char *)this - *(int *)((char *)this - 4)))->fwd(); }

class Rva005E3ECB { public: void rva005E3ECB(); };
void Rva005E3ECB::rva005E3ECB() { ((Rva005E3E41 *)((char *)this - *(int *)((char *)this - 4)))->rva005E3E41(); }

class Rva005E4663 { public: void rva005E4663(); };
void Rva005E4663::rva005E4663() { ((Rva005E4389 *)((char *)this - *(int *)((char *)this - 4)))->rva005E4389(); }

class Rva005E5237 { public: void rva005E5237(); };
void Rva005E5237::rva005E5237() { ((Rva005E51D3 *)((char *)this - *(int *)((char *)this - 4)))->rva005E51D3(); }

// --- 0x003ABF24 (8B): this-8 adjustor thunk of Rva003AA6BD's deleting
// destructor, jumping to the rowed vector deleting destructor 0x003AA704.
struct __declspec(novtable) Rva003AA6BD_BaseA { virtual ~Rva003AA6BD_BaseA(); char m_pad[4]; };
struct __declspec(novtable) Rva003AA6BD_BaseB { virtual ~Rva003AA6BD_BaseB(); };
class Rva003AA6BD : public Rva003AA6BD_BaseA, public Rva003AA6BD_BaseB
{
public:
	Rva003AA6BD(EmitVtableTag *);
	virtual ~Rva003AA6BD();
};
// The ledger's row at 0x003AA6BD is the FXParticleSystem template dtor's own
// spelling (a 5-byte jump to 0x003A9C39); the address-derived name the vector
// deleting destructor below calls is that same body, so bind the two.
#pragma comment(linker, "/alternatename:??1Rva003AA6BD@@UAE@XZ=??1?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?RENDEROBJECT_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?RENDEROBJECT_DRAW_MODULE_NAME@2@3QBDBVRenderObjectDrawModule@2@VRenderObjectDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@@FXParticleSystem@@@FXParticleSystem@@UAE@XZ")

// ?<Rva003AA6BD::Rva003AA6BD> absent-from-retail
Rva003AA6BD::Rva003AA6BD(EmitVtableTag *) {}

// Deleting-destructor adjustor thunks (sub ecx, Off; jmp ??_E<Cls>): the jmp
// goes through the class's weak vector deleting destructor, whose COFF
// default is its rowed ??_G. The secondary base sits at Off; both bases are
// novtable, so the view emits only the class's own tables.
#define DEFINE_DTOR_THUNK(Cls, Off, Access) \
	struct __declspec(novtable) Cls##_DtorBaseA { virtual ~Cls##_DtorBaseA(); char m_pad[(Off) - 4]; }; \
	struct __declspec(novtable) Cls##_DtorBaseB { virtual ~Cls##_DtorBaseB(); }; \
	class Cls : public Cls##_DtorBaseA, public Cls##_DtorBaseB \
	{ \
	public: \
		Cls(EmitVtableTag *); \
	Access: \
		virtual ~Cls(); \
	}; \
	Cls::Cls(EmitVtableTag *) {}

// --- 0x0051CC82 (11B): AptScoreScreen, table 0x00C66FA8 (the +0x218 screen
// callback base) -> ??_G 0x0051CE56.
// ?<AptScoreScreen::AptScoreScreen> absent-from-retail
DEFINE_DTOR_THUNK(AptScoreScreen, 0x218, public)
// --- 0x004E845F (11B): AptInGameChat, one-slot table 0x00C6262C (the
// +0x218 screen callback base) -> ??_G 0x004E84E3.
// ?<AptInGameChat::AptInGameChat> absent-from-retail
DEFINE_DTOR_THUNK(AptInGameChat, 0x218, public)
// --- 0x004AB88F (8B): slot 11 of table 0x00C548B8 (the +0x24 base) ->
// ??_G 0x004ABB1B.
// ?<LargeGroupAudioUpdate::LargeGroupAudioUpdate> absent-from-retail
DEFINE_DTOR_THUNK(LargeGroupAudioUpdate, 0x24, public)

class AptSkirmish { public: void InitCreateAHeroOnStartGame(); };
class Rva00521B48 { public: void rva00521B48(int, int); };
void Rva00521B48::rva00521B48(int, int)
{
	((AptSkirmish *)((char *)this - 0x27C))->InitCreateAHeroOnStartGame();
}

#include "../../Include/GameClient/AptOnlineCustomMatch.h"
class Rva0059EF57 { public: void rva0059EF57(int, int, int); };
void Rva0059EF57::rva0059EF57(int, int, int)
{
	((AptOnlineCustomMatch *)((char *)this - 0x6C))->UpdatePings();
}

#include "../../Include/Common/Rva0042D697PtrChaseField.h"
#include "../../Include/Common/Rva005CB265.h"
struct Rva005CF9B2Mid { char m_pad[0xC]; Rva0042D697PtrChaseField *m_field; };
class Rva005CF9B2 { public: void rva005CF9B2(); };
void Rva005CF9B2::rva005CF9B2()
{
	Rva005CF9B2Mid *mid = *(Rva005CF9B2Mid **)((char *)this - 4);
	int v = mid->m_field->get();
	if (v)
		((Rva005CB265 *)v)->Rva005CB265::rva005CB265();
}
// ?rva0049B517@Rva0049B517@@QAEXXZ @0x0049B517 7B: no caller left in retail
// (dead member forwarder after its update 0x0049B483); adjusts the receiver
// to its member at +0x20 and tail-calls that member's first virtual. The
// slot's return and argument contract is not established (an argument-taking
// spelling compiles to the same jmp), so the view is void/no-argument.
class Rva0049B517Member
{
public:
	virtual void slot0();
};
class Rva0049B517
{
public:
	void rva0049B517();
private:
	char m_pad[0x20];
	Rva0049B517Member m_20;
};
void Rva0049B517::rva0049B517()
{
	m_20.slot0();
}

// Names this unit references that no unit defines under that spelling. Each is
// bound to the row that owns the pinned retail address (same address, same
// body); the pin keeps the name, the row supplies the definition.
#pragma comment(linker, "/alternatename:??1Rva003AA6BD@@UAE@XZ=??1?$ConcreteModuleTemplate@V?$ModuleTag@$05$E?RENDEROBJECT_DRAW_MODULE_KEY@FXParticleSystem@@3QBDB$E?RENDEROBJECT_DRAW_MODULE_NAME@2@3QBDBVRenderObjectDrawModule@2@VRenderObjectDrawModuleTemplate@2@V?$DefaultParticleModule@$05@2@@FXParticleSystem@@@FXParticleSystem@@UAE@XZ")
