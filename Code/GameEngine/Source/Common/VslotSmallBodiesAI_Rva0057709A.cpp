// cl: /DNDEBUG /MD
// Split from VslotSmallBodiesAI.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
//
// Vtable-slot forwarders with no ledger owner and no Ghidra entry, batch AI:
// each loads a member (or takes a member's address) and tail-jumps to a
// rowed or pinned method, or to a virtual slot of the member. As in
// VslotSmallBodiesA-AH, classes and methods are address-derived unless the
// ledger names them, and model only what each body touches.

typedef int Int;
typedef unsigned int UnsignedInt;

// Native 0x0059B14E..0x0059B19A (RET 4): a nonzero input selects an
// experience-level handle with the receiver's +0x08 value; a valid handle
// adds its award to +0x04. The receiver's original identity is unknown.
// The two-word handle and award query agree with ExperienceLevelSystem.cpp.
class ExperienceLevelList;
struct ExperienceLevelNode;
class ExperienceLevelIterator
{
public:
	ExperienceLevelIterator() {}
	ExperienceLevelIterator(const ExperienceLevelIterator &that)
		: m_node(that.m_node) {}
	ExperienceLevelNode *m_node;
};
struct ExperienceLevelHandle
{
	ExperienceLevelHandle() {}
	ExperienceLevelHandle(const ExperienceLevelHandle &that)
		: m_list(that.m_list), m_iter(that.m_iter) {}
	ExperienceLevelList *m_list;
	ExperienceLevelIterator m_iter;
};
class ExperienceLevelStore
{
public:
	ExperienceLevelHandle rva00288D88(int value, int experience);
	int GetExperienceAwardForLevel(ExperienceLevelHandle level) const;
};
class Rva00288CFA;
class ExperienceLevelSystem;
extern ExperienceLevelSystem *TheExperienceLevelSystem;
class Rva0059B14E
{
public:
	int rva0059B14E(int value);
private:
	char m_unknown00[4];
	int m_award;
	int m_experience;
};


// Virtual slot N of a member object.
template <int N>
class Rva004888F8Slots : public Rva004888F8Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]);
};
template <>
class Rva004888F8Slots<0>
{
};
template <int N>
class Rva004888F8Target : public Rva004888F8Slots<N>
{
public:
	virtual void target();
};

// 0x004888F8: slot 4 of the +0x24 object.
class Rva004888F8
{
public:
	void rva004888F8();
private:
	char m_pad00[0x24];
	Rva004888F8Target<4> *m_24;
};


// 0x005778C9: slot 2 of the +0x3C object.
class Rva005778C9
{
public:
	void rva005778C9();
private:
	char m_pad00[0x3C];
	Rva004888F8Target<2> *m_3C;
};


// 0x005C3525: slot 5 of the +0x08 object.
class Rva005C3525
{
public:
	void rva005C3525();
private:
	char m_pad00[0x08];
	Rva004888F8Target<5> *m_08;
};


// 0x005CC9C3: slot 1 of the +0x24 object.
class Rva005CC9C3
{
public:
	void rva005CC9C3();
private:
	char m_pad00[0x24];
	Rva004888F8Target<1> *m_24;
};


// 0x0060037E and 0x00600386 (three tables each): slots 2 and 3 of the
// +0x08 object.
class Rva0060037ETarget
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
};
class Rva0060037E
{
public:
	void rva0060037E();
	void rva00600386();
private:
	Int m_00;
	Int m_04;
	Rva0060037ETarget *m_08;
};



// 0x002ABC76: the rowed AsciiStringRef::write of the +0x04 reference.
class AsciiStringRef
{
public:
	Int write(char *buf);
};
class Rva002ABC76
{
public:
	Int rva002ABC76(char *buf);
private:
	Int m_00;
	AsciiStringRef *m_04;
};


// 0x0057433D: the rowed getter 0x0042D6B4 of the +0x08 object.
class Rva0042D6B4PtrChaseField
{
public:
	Int get() const;
};
class Rva0057433D
{
public:
	Int rva0057433D();
private:
	Int m_00;
	Int m_04;
	Rva0042D6B4PtrChaseField *m_08;
};


// 0x005753AC (two tables): the rowed RAMFile::write of the +0x04 file,
// called directly.
class RAMFile
{
public:
	virtual Int write(const void *buffer, Int bytes);
};
class Rva005753AC
{
public:
	Int rva005753AC(const void *buffer, Int bytes);
private:
	Int m_00;
	RAMFile *m_04;
};


// 0x005785CD: target starts after the ret at 0x005785CC and ends at the ret
// before the rowed 0x005785F6 entry. It conditionally calls the rowed
// StrategicHUD::CommandUIImpl::Update 0x005D2A53 for this+0x44 then the shared
// empty body 0x000B3FD0 for this+0x4C and this+0x48. Field ownership and the
// address-derived class identity are structural views.
namespace StrategicHUD { class CommandUIImpl { public: void Update(); }; }
class Rva000B3FD0
{
public:
	void rva000B3FD0();
};
class Rva005785CD
{
public:
	void rva005785CD();

private:
	char m_pad00[0x44];
	StrategicHUD::CommandUIImpl *m_44;
	Rva000B3FD0 *m_48;
	Rva000B3FD0 *m_4C;
};
void Rva005785CD::rva005785CD()
{
	if (m_44 != 0)
		m_44->Update();
	if (m_4C != 0)
		m_4C->rva000B3FD0();
	if (m_48 != 0)
		m_48->rva000B3FD0();
}

// 0x0059B19A: the rowed length 0x00513E03 of the +0x04 object.
class Rva00513E03
{
public:
	Int length() const;
};
class Rva0059B19A
{
public:
	Int rva0059B19A() const;
private:
	Int m_00;
	Rva00513E03 *m_04;
};


// 0x005FC9F8 (two tables): the rowed 0x005FC8FD of the +0x18 object.
namespace StrategicHUD {
class ArmyMemberIconMovieClip
{
public:
	class Impl;
};
}

class StrategicHUD::ArmyMemberIconMovieClip::Impl
{
public:
	void Update();
};
class Rva005FC9F8
{
public:
	void rva005FC9F8();
private:
	char m_pad00[0x18];
	StrategicHUD::ArmyMemberIconMovieClip::Impl *m_18;
};


// 0x0044BD53: the rowed handle 0x0044BD5B on the +0x08 member.
class Rva004C5EF0
{
public:
	void handle(Int a);
};
class Rva0044BD53
{
public:
	void rva0044BD53(Int a);
private:
	char m_pad00[0x08];
	Rva004C5EF0 m_08;
};


// 0x0044BDF7 (8B): slot 4 of the same table (VA 0x00C3EDF0 holds
// 0x0044BD53, ..., 0x0044BDF7): the rowed functor fire 0x0044BDFF on the
// +0x08 member.
class Rva0044BDFF
{
public:
	void fire(Int which);
};
class Rva0044BDF7
{
public:
	void rva0044BDF7(Int which);
private:
	char m_pad00[0x08];
	Rva0044BDFF m_08;
};


// 0x00575CA6: the rowed clear 0x000AD6F4 on the +0x24 member.
class Rva000AD6F4
{
public:
	void clear();
};
class Rva00575CA6
{
public:
	virtual void rva00575CA6();
private:
	char m_pad04[0x24 - 4];
	Rva000AD6F4 m_24;
};


// 0x00575CAE: allocates the rowed 0x14-byte helper 0x0057551C from the
// adjusted owner pointer, then stores it through the rowed setter at +0x28.
// The helper identity follows the direct constructor call; owner type is
// address-derived and the -4/+0x28 offsets come from the target instructions.
class Rva0057551C
{
public:
	Rva0057551C(void *a, void *b, void *c);

private:
	void *m_vtable;
	void *m_04;
	void *m_08;
	void *m_0c;
	int m_10;
};
class Object
{
public:
	virtual void *deleteInstance(int flags);
};
class Rva00575674
{
public:
	void rva00575674(Object *p);
};
class Rva00575CAE
{
public:
	virtual void rva00575CAE(void *arg);

private:
	char m_pad04[0x28 - 4];
	Rva00575674 m_28;
};


// 0x0057956D and 0x0057B9D0: assignment of the argument to the +0x18 (resp.
// +0x30) tree hint through its rowed operator=.
struct TreeHintRef00217D4C
{
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);
	Int m_00;
};
class Rva0057956D
{
public:
	TreeHintRef00217D4C &rva0057956D(const TreeHintRef00217D4C &other);
private:
	char m_pad00[0x18];
	TreeHintRef00217D4C m_18;
};

class Rva0057B9D0
{
public:
	TreeHintRef00217D4C &rva0057B9D0(const TreeHintRef00217D4C &other);
private:
	char m_pad00[0x30];
	TreeHintRef00217D4C m_30;
};


// 0x0057A35A and 0x0057A37A: the rowed getter 0x0049CB82 resp. 0x005D4118
// on the +0x08 member.
class Rva0049CB82LeaField
{
public:
	void *get() const;
};
namespace StrategicHUD { class ChecklistUIItemMovieClip; }
class StrategicHUD::ChecklistUIItemMovieClip
{
public:
	void Flash();
};
class Rva0057A35A
{
public:
	void *rva0057A35A();
private:
	char m_pad00[0x08];
	Rva0049CB82LeaField m_08;
};

class Rva0057A37A
{
public:
	void rva0057A37A();
private:
	char m_pad00[0x08];
	StrategicHUD::ChecklistUIItemMovieClip m_08;
};


// 0x00456A3E: the rowed reset 0x0026549E on the +0x100 member.
class Rva0029FB3BMember
{
public:
	void reset();
};
class Rva00456A3E
{
public:
	void rva00456A3E();
private:
	char m_pad00[0x100];
	Rva0029FB3BMember m_100;
};


// 0x005785F6, 0x005785FE, 0x00578606, 0x0057860E and 0x00578646: the rowed
// methods 0x0057E556, 0x005D3776, 0x0036CBE7, 0x005D3846 resp. 0x004C54EC
// of the +0x4C object.
class Image;
class UnicodeString;
class Rva0057E556DwordField
{
public:
	Int get() const;
};
class Rva005D3776
{
public:
	void rva005D3776(const Image *image);
};
class Rva0036CBE7LeaField
{
public:
	void *get() const;
};
class Rva005D3846
{
public:
	void rva005D3846(const UnicodeString &text);
};
class NetProgressCommandMsg
{
public:
	unsigned char getPercentage();
};
class Rva005785F6
{
public:
	Int rva005785F6();
private:
	char m_pad00[0x4C];
	Rva0057E556DwordField *m_4C;
};

class Rva005785FE
{
public:
	void rva005785FE(const Image *image);
private:
	char m_pad00[0x4C];
	Rva005D3776 *m_4C;
};

class Rva00578606
{
public:
	void *rva00578606();
private:
	char m_pad00[0x4C];
	Rva0036CBE7LeaField *m_4C;
};

class Rva0057860E
{
public:
	void rva0057860E(const UnicodeString &text);
private:
	char m_pad00[0x4C];
	Rva005D3846 *m_4C;
};

class Rva00578646
{
public:
	unsigned char rva00578646();
private:
	char m_pad00[0x4C];
	NetProgressCommandMsg *m_4C;
};


// 0x005666BA: the rowed vector push_back 0x00566575 on the +0x90 member.
struct Rva00566575Element;
namespace _STL
{
template <class T> class allocator
{
};
template <class T, class A> class vector
{
public:
	void push_back(const T &x);
};
}
class Rva005666BA
{
public:
	void rva005666BA(const Rva00566575Element &e);
private:
	char m_pad00[0x90];
	_STL::vector<Rva00566575Element, _STL::allocator<Rva00566575Element> > m_90;
};


// Forwarders through a member pointer to a member of the pointee: the rowed
// Rva000AD6F4::clear (or the rowed 0x0057702E) on member +B of the object
// at +A.
class Rva0057702E
{
public:
	void rva0057702E();
};
struct Rva00574846Inner
{
	char m_pad00[0x54];
	Rva000AD6F4 m_54;
};
class Rva00574846
{
public:
	void rva00574846();
private:
	char m_pad00[0x08];
	Rva00574846Inner *m_08;
};

struct Rva005756E7Inner
{
	char m_pad00[0x28];
	Rva000AD6F4 m_28;
};
class Rva005756E7
{
public:
	void rva005756E7();
private:
	char m_pad00[0x08];
	Rva005756E7Inner *m_08;
};

struct Rva005767DCInner
{
	char m_pad00[0x1C];
	Rva000AD6F4 m_1C;
};
class Rva005767DC
{
public:
	void rva005767DC();
private:
	char m_pad00[0x08];
	Rva005767DCInner *m_08;
};

struct Rva00576808Inner
{
	char m_pad00[0x40];
	Rva000AD6F4 m_40;
};
class Rva00576808
{
public:
	void rva00576808();
private:
	char m_pad00[0x08];
	Rva00576808Inner *m_08;
};

struct Rva005CEA11Inner
{
	char m_pad00[0x1C];
	Rva000AD6F4 m_1C;
};
class Rva005CEA11
{
public:
	void rva005CEA11();
private:
	char m_pad00[0x0C];
	Rva005CEA11Inner *m_0C;
};

struct Rva005E57D0Inner
{
	char m_pad00[0x38];
	Rva000AD6F4 m_38;
};
class Rva005E57D0
{
public:
	void rva005E57D0();
private:
	char m_pad00[0x08];
	Rva005E57D0Inner *m_08;
};

struct Rva0057708FInner
{
	char m_pad00[0x14];
	Rva0057702E m_14;
};
// StrategicInGameUI::PlanRetreatsPhaseBehavior::Impl::Selection::DeselectThis,
// retail 0x0057708F: slot 5 of the selection's vftable 0x00C6E858 (installed
// at +0 by its destructor 0x00576F48 and constructor 0x005774E3; nothing
// calls it directly). WB's twin table 0x01F4871C holds WB 0x014CE670,
// DeselectThis, in slot 5 beside the same HeroArmySelectionHandler slots 0
// and 1. It clears the owning Impl's +0x14 selection holder.
namespace StrategicInGameUI
{
class PlanRetreatsPhaseBehavior
{
public:
	class Impl;
};
}
class StrategicInGameUI::PlanRetreatsPhaseBehavior::Impl
{
public:
	class Selection;
};
class StrategicInGameUI::PlanRetreatsPhaseBehavior::Impl::Selection
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04();
	virtual void DeselectThis();	// slot 5
private:
	char m_pad04[0x14 - 0x04];
	Rva0057708FInner *m_14;	// the owning Impl
};

struct Rva005770CBInner
{
	char m_pad00[0x14];
	Rva0057702E m_14;
};
class Rva005770CB
{
public:
	void rva005770CB();
private:
	char m_pad00[0x08];
	Rva005770CBInner *m_08;
};


// 0x0057709A: derived ctor of Rva005CBA04 storing vtable 0x00C6E8A8, base temp from global 0x00E0660C, outer arg at +8.
class BfmeFixedStorage002CF0F0
{
	char m_bytes[4];
public:
	__declspec(nothrow) BfmeFixedStorage002CF0F0(const BfmeFixedStorage002CF0F0 &);
};
extern unsigned g_Va00E0660C;
// The retail table at RVA 0x0086E8A8: 19 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva00576FCE@@UAEPAXI@Z")();
void __identifier("?b1Anchor@Rva0056B126B1@@UAE_NH@Z")();
void __identifier("?_bfme_ro_v50@RenderObjClass@@UAE_NH@Z")();
void __identifier("?rva0057548A@Rva0057548A@@UAEHPAUParent00575E4E@@@Z")();
void __identifier("?testBit@Rva005CBA3D@@QAEHI@Z")();
void __identifier("?rva005770CB@Rva005770CB@@QAEXXZ")();
void __identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")();
void __identifier("?selectArmy@Rva0057709A@@QAEXH@Z")();
void __identifier("??_ERva005770F7@@W3AEPAXI@Z")();
void __identifier("?rva00576FFE@Rva00576FFE@@QAEHXZ")();
}
extern const void *const g_00C6E8A8[19] = {
	(const void *)&__identifier("??_GRva00576FCE@@UAEPAXI@Z"), // slot 0 0x005E5A66
	(const void *)&__identifier("?b1Anchor@Rva0056B126B1@@UAE_NH@Z"), // slot 1 0x005CB9FF
	(const void *)&__identifier("?b1Anchor@Rva0056B126B1@@UAE_NH@Z"), // slot 2 0x005CB9FF
	(const void *)&__identifier("?b1Anchor@Rva0056B126B1@@UAE_NH@Z"), // slot 3 0x005CB9FF
	(const void *)&__identifier("?_bfme_ro_v50@RenderObjClass@@UAE_NH@Z"), // slot 4 0x005CB9FA
	(const void *)&__identifier("?_bfme_ro_v50@RenderObjClass@@UAE_NH@Z"), // slot 5 0x005CB9FA
	(const void *)&__identifier("?rva0057548A@Rva0057548A@@UAEHPAUParent00575E4E@@@Z"), // slot 6 0x0057548A
	(const void *)&__identifier("?_bfme_ro_v50@RenderObjClass@@UAE_NH@Z"), // slot 7 0x005CB9FA
	(const void *)&__identifier("?testBit@Rva005CBA3D@@QAEHI@Z"), // slot 8 0x005CBA3D
	(const void *)&__identifier("?rva005770CB@Rva005770CB@@QAEXXZ"), // slot 9 0x005770CB
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"), // slot 10 0x0047A69C
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"), // slot 11 0x0047A69C
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"), // slot 12 0x0047A69C
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"), // slot 13 0x0047A69C
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"), // slot 14 0x0047A69C
	(const void *)&__identifier("?selectArmy@Rva0057709A@@QAEXH@Z"), // slot 15 0x005775C1
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"), // slot 16 0x0047A69C
	(const void *)&__identifier("??_ERva005770F7@@W3AEPAXI@Z"), // slot 17 0x00577185
	(const void *)&__identifier("?rva00576FFE@Rva00576FFE@@QAEHXZ"), // slot 18 0x00576FFE
};

class Rva005CBA04
{
public:
	virtual ~Rva005CBA04();
	Rva005CBA04(BfmeFixedStorage002CF0F0 storage);
private:
	BfmeFixedStorage002CF0F0 m_storage;
};

class __declspec(novtable) Rva0057709A : public Rva005CBA04
{
public:
	Rva0057709A(int v);
private:
	int m_08;
};

Rva0057709A::Rva0057709A(int v)
	: Rva005CBA04(*(BfmeFixedStorage002CF0F0 *)&g_Va00E0660C), m_08(v)
{
	*(const void **)this = g_00C6E8A8;
}

// 0x0057B9D8 (?rva0057B9D8@Rva0057B9D8@@QAEXXZ), 25B: slot 4 of the table
// at 0x0086F26C (neighbours -8/-4 are the rowed 0x0057B97C/0x0057B9D0 of the
// same +0x30/+0x34 layout). Clears the +0x30 hint through the rowed
// ?clear@Rva002BED91@@QAEXXZ, then tail-jumps to the rowed
// ?rva005D4F7D@Rva005D4F7D@@QAEXXZ of the +0x34 object when it exists.
class Rva002BED91
{
public:
	void clear();
};
class Rva005D4F7D
{
public:
	void rva005D4F7D();
};
class Rva0057B9D8
{
public:
	void rva0057B9D8();
private:
	char m_pad00[0x30];
	Rva002BED91 m_30;
	Rva005D4F7D *m_34;
};


// 0x00578616, 0x0057861E, 0x00578626 (8B each), after the +0x4C forwarders
// above in the same Palantir vtable run: the +0x48 object receives the two
// ints through the leaf thunks 0x005D3272/79/80 (Rva005D3287Thunk.cpp).
class Rva005D3272 { public: void rva005D3272(Int a, Int b); };
class Rva005D3279 { public: void rva005D3279(Int a, Int b); };
class Rva005D3280 { public: void rva005D3280(Int a, Int b); };
class Rva00578616
{
public:
	void rva00578616(Int a, Int b);
	void rva0057861E(Int a, Int b);
	void rva00578626(Int a, Int b);
private:
	char m_pad00[0x48];
	void *m_48;
};




class Rva0056B9F2 : public Rva004888F8Slots<14>
{
public:
	virtual void vslot14(bool inv, Int arg);
	void rva0056B9F2(bool a, Int b);
};


struct Rva005778B6Ret
{
	void *m_ptr;
	Rva005778B6Ret(const Rva005778B6Ret &other);
};
class Rva005778B6Target
{
public:
	virtual void slot00();
	virtual Rva005778B6Ret slot04();
};
class Rva005778B6
{
public:
	Rva005778B6Ret rva005778B6();
private:
	char m_pad00[0x3C];
	Rva005778B6Target *m_3C;
};


class Rva005F6037ByteChaseField
{
public:
	unsigned char get() const;
};
class Rva005F62FE
{
public:
	void rva005F62FE(bool b);
};
class Rva005E6863
{
public:
	void rva005E6863(Int a, Int b);
private:
	Int m_00;
	void *m_04;
};


// 0x005CC4DA..0x005CC538 (six bodies in two tables, 11 bytes each): slot N
// of the object at +0x08 of the receiver's +0x10 object, as a tail jump.
template <int N>
struct Rva005CC4DAInner
{
	char m_pad00[0x08];
	Rva004888F8Target<N> *m_08;
};

// 0x005CC4DA: slot 2.
class Rva005CC4DA
{
public:
	void rva005CC4DA();
private:
	char m_pad00[0x10];
	Rva005CC4DAInner<2> *m_10;
};


// 0x005CC4E5: slot 5.
class Rva005CC4E5
{
public:
	void rva005CC4E5();
private:
	char m_pad00[0x10];
	Rva005CC4DAInner<5> *m_10;
};


// 0x005CC4F0: slot 6.
class Rva005CC4F0
{
public:
	void rva005CC4F0();
private:
	char m_pad00[0x10];
	Rva005CC4DAInner<6> *m_10;
};


// 0x005CC522: slot 1.
class Rva005CC522
{
public:
	void rva005CC522();
private:
	char m_pad00[0x10];
	Rva005CC4DAInner<1> *m_10;
};


// 0x005CC52D: slot 4.
class Rva005CC52D
{
public:
	void rva005CC52D();
private:
	char m_pad00[0x10];
	Rva005CC4DAInner<4> *m_10;
};


// 0x005CC538: slot 3.
class Rva005CC538
{
public:
	void rva005CC538();
private:
	char m_pad00[0x10];
	Rva005CC4DAInner<3> *m_10;
};


// 0x005CC984..0x005CC9B8 (one table, RET 4 with the argument unused): slot N
// of the +0x24 object; the two middle bodies first set (slot 3) or clear
// (slot 4) the +0x23 flag.
class Rva005CC984
{
public:
	void rva005CC984(Int unused);
private:
	char m_pad00[0x24];
	Rva004888F8Target<6> *m_24;
};

class Rva005CC98F
{
public:
	void rva005CC98F(Int unused);
private:
	char m_pad00[0x24];
	Rva004888F8Target<2> *m_24;
};

class Rva005CC99A
{
public:
	void rva005CC99A(Int unused);
private:
	char m_pad00[0x23];
	bool m_23;
	Rva004888F8Target<3> *m_24;
};

class Rva005CC9A9
{
public:
	void rva005CC9A9(Int unused);
private:
	char m_pad00[0x23];
	bool m_23;
	Rva004888F8Target<4> *m_24;
};

class Rva005CC9B8
{
public:
	void rva005CC9B8(Int unused);
private:
	char m_pad00[0x24];
	Rva004888F8Target<5> *m_24;
};


// Slot N taking two integer arguments.
template <int N>
class Rva005EA539Target : public Rva004888F8Slots<N>
{
public:
	virtual void target(Int a, Int b);
};


// 0x005EA539: slot 4 of the +0x14 object of the +0x08 object, passed the
// receiver's +0x0C and +0x10 words.
struct Rva005EA539Inner
{
	char m_pad00[0x14];
	Rva005EA539Target<4> *m_14;
};
class Rva005EA539
{
public:
	void rva005EA539();
private:
	char m_pad00[0x08];
	Rva005EA539Inner *m_08;
	Int m_0C;
	Int m_10;
};


// 0x005EA54D: slot 5 of the +0x14 object of the +0x08 object, passed the
// receiver's +0x0C and +0x10 words.
struct Rva005EA54DInner
{
	char m_pad00[0x14];
	Rva005EA539Target<5> *m_14;
};
class Rva005EA54D
{
public:
	void rva005EA54D();
private:
	char m_pad00[0x08];
	Rva005EA54DInner *m_08;
	Int m_0C;
	Int m_10;
};


// 0x005EA561: slot 6 of the +0x14 object of the +0x08 object, passed the
// receiver's +0x0C and +0x10 words.
struct Rva005EA561Inner
{
	char m_pad00[0x14];
	Rva005EA539Target<6> *m_14;
};
class Rva005EA561
{
public:
	void rva005EA561();
private:
	char m_pad00[0x08];
	Rva005EA561Inner *m_08;
	Int m_0C;
	Int m_10;
};


// 0x00494ABE (RET 4, argument unused): the receiver's own slot 2.
class Rva00494ABE : public Rva004888F8Target<2>
{
public:
	void rva00494ABE(Int unused);
};


// 0x005CFB93 (RET 4, argument unused): slot 1 of the +0x08 object.
class Rva005CFB93
{
public:
	void rva005CFB93(Int unused);
private:
	char m_pad00[0x08];
	Rva004888F8Target<1> *m_08;
};


// 0x005D1358: tail jump to slot 2 of the object the +0x08 object points to
// first.
struct Rva005D1358Inner
{
	Rva004888F8Target<2> *m_00;
};
class Rva005D1358
{
public:
	void rva005D1358();
private:
	char m_pad00[0x08];
	Rva005D1358Inner *m_08;
};


// 0x005EA052: tail jump to slot 1 of the +0x04 object of the +0x08 object.
struct Rva005EA052Inner
{
	char m_pad00[0x04];
	Rva004888F8Target<1> *m_04;
};
class Rva005EA052
{
public:
	void rva005EA052();
private:
	char m_pad00[0x08];
	Rva005EA052Inner *m_08;
};


// 0x00575DDA, 0x00575DE6 and 0x00575DF2: pass the receiver's +0x0C word to a
// rowed method of the +0x04 object.
struct Rva005757F9Value;
class Rva005757F9 { public: void rva005757F9(Rva005757F9Value *value); };
class Rva0057590E { public: void rva0057590E(Int value); };
class Rva005759A5 { public: void rva005759A5(Int value); };
class Rva00575DDA
{
public:
	void rva00575DDA();
private:
	Int m_00;
	Rva005757F9 *m_04;
	Int m_08;
	Rva005757F9Value *m_0C;
};

class Rva00575DE6
{
public:
	void rva00575DE6();
private:
	Int m_00;
	Rva0057590E *m_04;
	Int m_08;
	Int m_0C;
};

class Rva00575DF2
{
public:
	void rva00575DF2();
private:
	Int m_00;
	Rva005759A5 *m_04;
	Int m_08;
	Int m_0C;
};


// 0x005EA254: drops the +0x08 count and, once it reaches zero, runs the
// rowed 0x005EA0C0 on the +0x04 object.
class Rva005EA183 { public: void rva005EA0C0(); };
class Rva005EA254
{
public:
	void rva005EA254();
private:
	Int m_00;
	Rva005EA183 *m_04;
	Int m_08;
};


// 0x003698A5 and 0x003698BB (RET 8): the receiver's rowed 0x00368E95 toward
// an object's +0x38 position (flag set) or toward a given position (flag
// clear), with the waypoint passed through.
struct Coord3D;
class Waypoint;
class Rva00368344
{
public:
	void rva00368E95(const Coord3D *pos, const Waypoint *waypoint, bool flag);
};
struct Rva003698A5Object
{
	char m_pad00[0x38];
	char m_pos38[12];
};
class GiantBirdAIUpdate : public Rva00368344
{
public:
	void rva003698A5(Rva003698A5Object *obj, const Waypoint *waypoint);
	void rva003698BB(const Coord3D *pos, const Waypoint *waypoint);
};



// 0x005CCB0E (RET 4, argument unused): the receiver's rowed
// StrategicInGameUI::ChecklistItem::Impl 0x005CCA57.
namespace StrategicInGameUI
{
	class ChecklistItem
	{
	public:
		class Impl
		{
		public:
			void rva005CCA57();
		};
	};
}
class Rva005CCB0E : public StrategicInGameUI::ChecklistItem::Impl
{
public:
	void rva005CCB0E(Int unused);
};

