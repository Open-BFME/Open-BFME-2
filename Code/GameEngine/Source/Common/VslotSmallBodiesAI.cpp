// cl: /DNDEBUG /MD
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
int Rva0059B14E::rva0059B14E(int value)
{
	if (value != 0)
	{
		ExperienceLevelHandle level =
			((ExperienceLevelStore *)TheExperienceLevelSystem)->rva00288D88(value, m_experience);
		if (level.m_list != 0)
			m_award += ((ExperienceLevelStore *)TheExperienceLevelSystem)->GetExperienceAwardForLevel(level);
	}
	return 1;
}

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
void Rva004888F8::rva004888F8()
{
	m_24->target();
}

// 0x005778C9: slot 2 of the +0x3C object.
class Rva005778C9
{
public:
	void rva005778C9();
private:
	char m_pad00[0x3C];
	Rva004888F8Target<2> *m_3C;
};
void Rva005778C9::rva005778C9()
{
	m_3C->target();
}

// 0x005C3525: slot 5 of the +0x08 object.
class Rva005C3525
{
public:
	void rva005C3525();
private:
	char m_pad00[0x08];
	Rva004888F8Target<5> *m_08;
};
void Rva005C3525::rva005C3525()
{
	m_08->target();
}

// 0x005CC9C3: slot 1 of the +0x24 object.
class Rva005CC9C3
{
public:
	void rva005CC9C3();
private:
	char m_pad00[0x24];
	Rva004888F8Target<1> *m_24;
};
void Rva005CC9C3::rva005CC9C3()
{
	m_24->target();
}

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
void Rva0060037E::rva0060037E()
{
	m_08->v02();
}
void Rva0060037E::rva00600386()
{
	m_08->v03();
}

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
Int Rva002ABC76::rva002ABC76(char *buf)
{
	return m_04->write(buf);
}

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
Int Rva0057433D::rva0057433D()
{
	return m_08->get();
}

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
Int Rva005753AC::rva005753AC(const void *buffer, Int bytes)
{
	return m_04->RAMFile::write(buffer, bytes);
}

// 0x005785CD: target starts after the ret at 0x005785CC and ends at the ret
// before the rowed 0x005785F6 entry. It conditionally calls 0x005D2A53 for
// this+0x44 then the shared empty body 0x000B3FD0 for this+0x4C and this+0x48.
// Field ownership and the address-derived class identity are structural
// views; the routine's original name and purpose are unknown.
class Rva005D2A53Call
{
public:
	void rva005D2A53();
};
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
	Rva005D2A53Call *m_44;
	Rva000B3FD0 *m_48;
	Rva000B3FD0 *m_4C;
};
void Rva005785CD::rva005785CD()
{
	if (m_44 != 0)
		m_44->rva005D2A53();
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
Int Rva0059B19A::rva0059B19A() const
{
	return m_04->length();
}

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
void Rva005FC9F8::rva005FC9F8()
{
	m_18->Update();
}

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
void Rva0044BD53::rva0044BD53(Int a)
{
	m_08.handle(a);
}

// 0x00575C5D: validates two signed endpoint deltas, builds a point from lower coords,
// calls 0x005757A5, reports whether +0x28 changed.
struct Rva00575C5DPoint
{
	int x;
	int y;
};

class Rva005757A5
{
public:
	void rva005757A5(int point);
};

class Rva00575C5D
{
public:
	int rva00575C5D(const int *bounds, int unused);
private:
	char m_pad00[0x28];
	void *m_28;
};

int Rva00575C5D::rva00575C5D(const int *bounds, int unused)
{
	int width = bounds[2] - bounds[0];
	if (width <= 0) {
		int height = bounds[3] - bounds[1];
		if (height <= 0) {
			void *old = m_28;
			Rva00575C5DPoint point;
			point.x = bounds[0];
			point.y = bounds[1];
			((Rva005757A5 *)this)->rva005757A5((int)&point);
			return (m_28 != old) ? 1 : 0;
		}
	}
	return 0;
}

// 0x00575CA6: the rowed clear 0x000AD6F4 on the +0x24 member.
class Rva000AD6F4
{
public:
	void clear();
};
class Rva00575CA6
{
public:
	void rva00575CA6();
private:
	char m_pad00[0x24];
	Rva000AD6F4 m_24;
};
void Rva00575CA6::rva00575CA6()
{
	m_24.clear();
}

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
void *__cdecl operator new(unsigned int size);
inline void *__cdecl operator new(unsigned int size, void *place)
{
	return place;
}
class Rva00575CAE
{
public:
	void rva00575CAE(void *arg);

private:
	char m_pad00[0x28];
	Rva00575674 m_28;
};
void Rva00575CAE::rva00575CAE(void *arg)
{
	void *memory = operator new(0x14);
	Rva0057551C *helper;
	if (memory)
		helper = new (memory) Rva0057551C((char *)this - 4, arg, 0);
	else
		helper = 0;
	m_28.rva00575674((Object *)helper);
}

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
TreeHintRef00217D4C &Rva0057956D::rva0057956D(const TreeHintRef00217D4C &other)
{
	return m_18 = other;
}
class Rva0057B9D0
{
public:
	TreeHintRef00217D4C &rva0057B9D0(const TreeHintRef00217D4C &other);
private:
	char m_pad00[0x30];
	TreeHintRef00217D4C m_30;
};
TreeHintRef00217D4C &Rva0057B9D0::rva0057B9D0(const TreeHintRef00217D4C &other)
{
	return m_30 = other;
}

// 0x0057A35A and 0x0057A37A: the rowed getter 0x0049CB82 resp. 0x005D4118
// on the +0x08 member.
class Rva0049CB82LeaField
{
public:
	void *get() const;
};
class Rva005D4118
{
public:
	void rva005D4118();
};
class Rva0057A35A
{
public:
	void *rva0057A35A();
private:
	char m_pad00[0x08];
	Rva0049CB82LeaField m_08;
};
void *Rva0057A35A::rva0057A35A()
{
	return m_08.get();
}
class Rva0057A37A
{
public:
	void rva0057A37A();
private:
	char m_pad00[0x08];
	Rva005D4118 m_08;
};
void Rva0057A37A::rva0057A37A()
{
	m_08.rva005D4118();
}

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
void Rva00456A3E::rva00456A3E()
{
	m_100.reset();
}

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
Int Rva005785F6::rva005785F6()
{
	return m_4C->get();
}
class Rva005785FE
{
public:
	void rva005785FE(const Image *image);
private:
	char m_pad00[0x4C];
	Rva005D3776 *m_4C;
};
void Rva005785FE::rva005785FE(const Image *image)
{
	m_4C->rva005D3776(image);
}
class Rva00578606
{
public:
	void *rva00578606();
private:
	char m_pad00[0x4C];
	Rva0036CBE7LeaField *m_4C;
};
void *Rva00578606::rva00578606()
{
	return m_4C->get();
}
class Rva0057860E
{
public:
	void rva0057860E(const UnicodeString &text);
private:
	char m_pad00[0x4C];
	Rva005D3846 *m_4C;
};
void Rva0057860E::rva0057860E(const UnicodeString &text)
{
	m_4C->rva005D3846(text);
}
class Rva00578646
{
public:
	unsigned char rva00578646();
private:
	char m_pad00[0x4C];
	NetProgressCommandMsg *m_4C;
};
unsigned char Rva00578646::rva00578646()
{
	return m_4C->getPercentage();
}

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
void Rva005666BA::rva005666BA(const Rva00566575Element &e)
{
	m_90.push_back(e);
}

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
void Rva00574846::rva00574846()
{
	m_08->m_54.clear();
}
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
void Rva005756E7::rva005756E7()
{
	m_08->m_28.clear();
}
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
void Rva005767DC::rva005767DC()
{
	m_08->m_1C.clear();
}
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
void Rva00576808::rva00576808()
{
	m_08->m_40.clear();
}
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
void Rva005CEA11::rva005CEA11()
{
	m_0C->m_1C.clear();
}
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
void Rva005E57D0::rva005E57D0()
{
	m_08->m_38.clear();
}
struct Rva005E586BInner
{
	char m_pad00[0x40];
	Rva000AD6F4 m_40;
};
class Rva005E586B
{
public:
	void rva005E586B();
private:
	char m_pad00[0x0C];
	Rva005E586BInner *m_0C;
};
void Rva005E586B::rva005E586B()
{
	m_0C->m_40.clear();
}
struct Rva0057708FInner
{
	char m_pad00[0x14];
	Rva0057702E m_14;
};
class Rva0057708F
{
public:
	void rva0057708F();
private:
	char m_pad00[0x14];
	Rva0057708FInner *m_14;
};
void Rva0057708F::rva0057708F()
{
	m_14->m_14.rva0057702E();
}
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
void Rva005770CB::rva005770CB()
{
	m_08->m_14.rva0057702E();
}

// 0x0057709A: derived ctor of Rva005CBA04 storing vtable 0x00C6E8A8, base temp from global 0x00E0660C, outer arg at +8.
class BfmeFixedStorage002CF0F0
{
	char m_bytes[4];
public:
	__declspec(nothrow) BfmeFixedStorage002CF0F0(const BfmeFixedStorage002CF0F0 &);
};
extern BfmeFixedStorage002CF0F0 g_00E0660C;
extern const void *const g_00C6E8A8[];

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

Rva0057709A::Rva0057709A(int v) : Rva005CBA04(g_00E0660C), m_08(v)
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
void Rva0057B9D8::rva0057B9D8()
{
	m_30.clear();
	if (m_34)
		m_34->rva005D4F7D();
}
