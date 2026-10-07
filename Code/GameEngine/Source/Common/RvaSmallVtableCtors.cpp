// cl: /O1 /DNDEBUG /MD
//
// Small constructors that install a vtable, in two shapes of rowed bodies:
//   18 bytes as ??0Rva005CB22A (V3PolyCopyCtors.cpp): store the vtable, then the
//     pointer argument at +4;
//   13 bytes as ??0NetCommandWrapperList: zero +4, then store the vtable, the
//     order an inlined base constructor followed by the derived vtable store gives.
// Each copy differs from its template only in the vtable it installs. One class
// per copy names that vtable; its destructor is inline and empty so the vtable
// the compiler emits resolves in this unit. The owning classes are not
// recovered, so each keeps its address.

struct RvaSmallVtableZeroBase
{
	void *m_04;
	RvaSmallVtableZeroBase() : m_04(0) {}
};

// ??0Rva000ABD56@@QAE@PAX@Z @0x000ABD56 18B, vtable VA 0xbc957c
class Rva000ABD56
{
public:
	Rva000ABD56(void *p);
	virtual ~Rva000ABD56() {}
private:
	void *m_04;
};

Rva000ABD56::Rva000ABD56(void *p) : m_04(p)
{
}

// ??0Rva00222A19@@QAE@PAX@Z @0x00222A19 18B, vtable VA 0xbe6d5c
class Rva00222A19
{
public:
	Rva00222A19(void *p);
	virtual ~Rva00222A19() {}
private:
	void *m_04;
};

Rva00222A19::Rva00222A19(void *p) : m_04(p)
{
}

// ??0Rva002293F9@@QAE@PAX@Z @0x002293F9 18B, vtable VA 0xbe73e4
class Rva002293F9
{
public:
	Rva002293F9(void *p);
	virtual ~Rva002293F9() {}
private:
	void *m_04;
};

Rva002293F9::Rva002293F9(void *p) : m_04(p)
{
}

// ??0Rva002AAD77@@QAE@PAX@Z @0x002AAD77 18B, vtable VA 0xbfdc60
class Rva002AAD77
{
public:
	Rva002AAD77(void *p);
	virtual ~Rva002AAD77() {}
private:
	void *m_04;
};

Rva002AAD77::Rva002AAD77(void *p) : m_04(p)
{
}

// ??0Rva002AAD9C@@QAE@PAX@Z @0x002AAD9C 18B, vtable VA 0xbfdc6c
class Rva002AAD9C
{
public:
	Rva002AAD9C(void *p);
	virtual ~Rva002AAD9C() {}
private:
	void *m_04;
};

Rva002AAD9C::Rva002AAD9C(void *p) : m_04(p)
{
}

// ??0Rva002B29D8@@QAE@PAX@Z @0x002B29D8 18B, vtable VA 0xbfe000
class Rva002B29D8
{
public:
	Rva002B29D8(void *p);
	virtual ~Rva002B29D8() {}
private:
	void *m_04;
};

Rva002B29D8::Rva002B29D8(void *p) : m_04(p)
{
}

// ??0Rva0032A3C6@@QAE@PAX@Z @0x0032A3C6 18B, vtable VA 0xc0d938
class Rva0032A3C6
{
public:
	Rva0032A3C6(void *p);
	virtual ~Rva0032A3C6() {}
private:
	void *m_04;
};

Rva0032A3C6::Rva0032A3C6(void *p) : m_04(p)
{
}

// ??0Rva003A538E@@QAE@PAX@Z @0x003A538E 18B, vtable VA 0xc1b320
class Rva003A538E
{
public:
	Rva003A538E(void *p);
	virtual ~Rva003A538E() {}
private:
	void *m_04;
};

Rva003A538E::Rva003A538E(void *p) : m_04(p)
{
}

// ??0Rva003EE734@@QAE@PAX@Z @0x003EE734 18B, vtable VA 0xc363c0
class Rva003EE734
{
public:
	Rva003EE734(void *p);
	virtual ~Rva003EE734() {}
private:
	void *m_04;
};

Rva003EE734::Rva003EE734(void *p) : m_04(p)
{
}

// ??0Rva003F3FEC@@QAE@PAX@Z @0x003F3FEC 18B, vtable VA 0xc37064
class Rva003F3FEC
{
public:
	Rva003F3FEC(void *p);
	virtual ~Rva003F3FEC() {}
private:
	void *m_04;
};

Rva003F3FEC::Rva003F3FEC(void *p) : m_04(p)
{
}

// ??0Rva003F424F@@QAE@PAX@Z @0x003F424F 18B, vtable VA 0xc37080
class Rva003F424F
{
public:
	Rva003F424F(void *p);
	virtual ~Rva003F424F() {}
private:
	void *m_04;
};

Rva003F424F::Rva003F424F(void *p) : m_04(p)
{
}

// ??0Rva003F82E2@@QAE@PAX@Z @0x003F82E2 18B, vtable VA 0xc37310
class Rva003F82E2
{
public:
	Rva003F82E2(void *p);
	virtual ~Rva003F82E2() {}
private:
	void *m_04;
};

Rva003F82E2::Rva003F82E2(void *p) : m_04(p)
{
}

// ??0Rva003FC428@@QAE@PAX@Z @0x003FC428 18B, vtable VA 0xc37c20
class Rva003FC428
{
public:
	Rva003FC428(void *p);
	virtual ~Rva003FC428() {}
private:
	void *m_04;
};

Rva003FC428::Rva003FC428(void *p) : m_04(p)
{
}

// ??0Rva004318C6@@QAE@PAX@Z @0x004318C6 18B, vtable VA 0xc3c970
class Rva004318C6
{
public:
	Rva004318C6(void *p);
	virtual ~Rva004318C6() {}
private:
	void *m_04;
};

Rva004318C6::Rva004318C6(void *p) : m_04(p)
{
}

// ??0Rva0059B060@@QAE@PAX@Z @0x0059B060 18B, vtable VA 0xc70e60
class Rva0059B060
{
public:
	Rva0059B060(void *p);
	virtual ~Rva0059B060() {}
private:
	void *m_04;
};

Rva0059B060::Rva0059B060(void *p) : m_04(p)
{
}

// ??0Rva005B253F@@QAE@PAX@Z @0x005B253F 18B, vtable VA 0xc72b74
class Rva005B253F
{
public:
	Rva005B253F(void *p);
	virtual ~Rva005B253F() {}
private:
	void *m_04;
};

Rva005B253F::Rva005B253F(void *p) : m_04(p)
{
}

// ??0Rva005C1860@@QAE@PAX@Z @0x005C1860 18B, vtable VA 0xc743b8
class Rva005C1860
{
public:
	Rva005C1860(void *p);
	virtual ~Rva005C1860() {}
private:
	void *m_04;
};

Rva005C1860::Rva005C1860(void *p) : m_04(p)
{
}

// ??0Rva005CD9AE@@QAE@PAX@Z @0x005CD9AE 18B, vtable VA 0xc75014
class Rva005CD9AE
{
public:
	Rva005CD9AE(void *p);
	virtual ~Rva005CD9AE() {}
private:
	void *m_04;
};

Rva005CD9AE::Rva005CD9AE(void *p) : m_04(p)
{
}

// ??0Rva005CF872@@QAE@PAX@Z @0x005CF872 18B, vtable VA 0xc75290
class Rva005CF872
{
public:
	Rva005CF872(void *p);
	virtual ~Rva005CF872() {}
private:
	void *m_04;
};

Rva005CF872::Rva005CF872(void *p) : m_04(p)
{
}

// ??0Rva005EA1D5@@QAE@PAX@Z @0x005EA1D5 18B, vtable VA 0xc781b4
class Rva005EA1D5
{
public:
	Rva005EA1D5(void *p);
	virtual ~Rva005EA1D5() {}
private:
	void *m_04;
};

Rva005EA1D5::Rva005EA1D5(void *p) : m_04(p)
{
}

// ??0Rva00656090@@QAE@PAX@Z @0x00656090 18B, vtable VA 0xce0fb4
class Rva00656090
{
public:
	Rva00656090(void *p);
	virtual ~Rva00656090() {}
private:
	void *m_04;
};

Rva00656090::Rva00656090(void *p) : m_04(p)
{
}

// ??0Rva00040ECE@@QAE@XZ @0x00040ECE 13B, vtable VA 0xbc16b8
class Rva00040ECE : public RvaSmallVtableZeroBase
{
public:
	Rva00040ECE();
	virtual ~Rva00040ECE() {}
};

Rva00040ECE::Rva00040ECE()
{
}

// ??0Rva000421C8@@QAE@XZ @0x000421C8 13B, vtable VA 0xbc26e0
// The partition filter base. Retail's vftable has three slots: the deleting
// dtor 0x000421D5, __purecall 0x0003B810 (allow) and the shared `or eax,-1`
// body 0x0036CC7A (getPlayerMask), the view the other filter units declare.
class Object;
class Rva000421C8 : public RvaSmallVtableZeroBase
{
public:
	Rva000421C8();
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
};

#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

inline Rva000421C8::Rva000421C8()
{
}

// ??0Rva000657D9@@QAE@XZ @0x000657D9 13B, vtable VA 0xbc5c6c
class Rva000657D9 : public RvaSmallVtableZeroBase
{
public:
	Rva000657D9();
	virtual ~Rva000657D9() {}
};

Rva000657D9::Rva000657D9()
{
}

// ??0Rva0007DF07@@QAE@XZ @0x0007DF07 13B, vtable VA 0xbc6f20
class Rva0007DF07 : public RvaSmallVtableZeroBase
{
public:
	Rva0007DF07();
	virtual ~Rva0007DF07() {}
};

inline Rva0007DF07::Rva0007DF07()
{
}

// ??0Rva000A882D@@QAE@XZ @0x000A882D 13B, vtable VA 0xbc93a0
class Rva000A882D : public RvaSmallVtableZeroBase
{
public:
	Rva000A882D();
	virtual ~Rva000A882D() {}
};

Rva000A882D::Rva000A882D()
{
}

// ??0Rva000FBA4A@@QAE@XZ @0x000FBA4A 13B, vtable VA 0xbcf364
class Rva000FBA4A : public RvaSmallVtableZeroBase
{
public:
	Rva000FBA4A();
	virtual ~Rva000FBA4A() {}
};

Rva000FBA4A::Rva000FBA4A()
{
}

// ??0Rva00217497@@QAE@XZ @0x00217497 13B, vtable VA 0xbe5aa8
class Rva00217497 : public RvaSmallVtableZeroBase
{
public:
	Rva00217497();
	virtual ~Rva00217497() {}
};

Rva00217497::Rva00217497()
{
}

// ??0Rva002390F8@@QAE@XZ @0x002390F8 13B, vtable VA 0xbed684
class Rva002390F8 : public RvaSmallVtableZeroBase
{
public:
	Rva002390F8();
	virtual ~Rva002390F8() {}
};

Rva002390F8::Rva002390F8()
{
}

// ??0Rva0026FFB1@@QAE@XZ @0x0026FFB1 13B, vtable VA 0xbfad1c
class Rva0026FFB1 : public RvaSmallVtableZeroBase
{
public:
	Rva0026FFB1();
	virtual ~Rva0026FFB1() {}
};

Rva0026FFB1::Rva0026FFB1()
{
}

// ??0Rva0030D346@@QAE@XZ @0x0030D346 13B, vtable VA 0xc089ec
class Rva0030D346 : public RvaSmallVtableZeroBase
{
public:
	Rva0030D346();
	virtual ~Rva0030D346() {}
};

inline Rva0030D346::Rva0030D346()
{
}

// ??0Rva003E3C0C@@QAE@XZ @0x003E3C0C 13B, vtable VA 0xc35b28
class Rva003E3C0C : public RvaSmallVtableZeroBase
{
public:
	Rva003E3C0C();
	virtual ~Rva003E3C0C() {}
};

Rva003E3C0C::Rva003E3C0C()
{
}

// ??0Rva0048B664@@QAE@XZ @0x0048B664 13B, vtable VA 0xc4bf78
class Rva0048B664 : public RvaSmallVtableZeroBase
{
public:
	Rva0048B664();
	virtual ~Rva0048B664() {}
};

Rva0048B664::Rva0048B664()
{
}

// ??0Rva004B236E@@QAE@XZ @0x004B236E 13B, vtable VA 0xc56930
class Rva004B236E : public RvaSmallVtableZeroBase
{
public:
	Rva004B236E();
	virtual ~Rva004B236E() {}
};

Rva004B236E::Rva004B236E()
{
}

// ??0Rva0051489D@@QAE@XZ @0x0051489D 13B, vtable VA 0xc65ee0
class Rva0051489D : public RvaSmallVtableZeroBase
{
public:
	Rva0051489D();
	virtual ~Rva0051489D() {}
};

Rva0051489D::Rva0051489D()
{
}

// ??0Rva0052510C@@QAE@XZ @0x0052510C 13B, vtable VA 0xc67e50
class Rva0052510C : public RvaSmallVtableZeroBase
{
public:
	Rva0052510C();
	virtual ~Rva0052510C() {}
};

Rva0052510C::Rva0052510C()
{
}

// Three more shapes, also differing from their rowed template only in the vtable:
//   20 bytes as ??0NetCommandList: store the vtable, then zero +4, +8 and +0xC;
//   17 bytes as BfmeThingTC::bfmeBaseTC: zero +4 and +8, then store the vtable;
//   23 bytes as ??0Rva0036247C: store the vtable, then zero +4 .. +0x10.

struct RvaSmallVtableZeroBase2
{
	virtual ~RvaSmallVtableZeroBase2() {}
	void *m_04;
	void *m_08;
	RvaSmallVtableZeroBase2() : m_04(0), m_08(0) {}
};

// ??0Rva00148AB0@@QAE@XZ @0x00148AB0 20B, vtable VA 0xbd3564
class Rva00148AB0
{
public:
	Rva00148AB0();
	virtual ~Rva00148AB0() {}
private:
	void *m_04;
	void *m_08;
	void *m_0C;
};

Rva00148AB0::Rva00148AB0()
	: m_04(0), m_08(0), m_0C(0)
{
}

// ??0Rva004E1780@@QAE@XZ @0x004E1780 20B, vtable VA 0xc61b78
class Rva004E1780
{
public:
	Rva004E1780();
	virtual ~Rva004E1780() {}
private:
	void *m_04;
	void *m_08;
	void *m_0C;
};

Rva004E1780::Rva004E1780()
	: m_04(0), m_08(0), m_0C(0)
{
}

// ??0Rva0054D54A@@QAE@XZ @0x0054D54A 20B, vtable VA 0xc6a774. Its destructor is
// rowed too (0x0054D55E, below): it frees the node list at +4 exactly as
// ~NetCommandWrapperList does, storing this class's vtable on entry.
struct Rva0054D54ANode
{
	virtual void *destroy(unsigned int flags);
	Rva0054D54ANode *m_next;
};

// The node list's view of a message: the argument count byte at +0x18 and
// the per-argument type query.
enum GameMessageArgumentDataType
{
	ARGUMENTDATATYPE_INTEGER,
	ARGUMENTDATATYPE_REAL,
	ARGUMENTDATATYPE_BOOLEAN,
	ARGUMENTDATATYPE_OBJECTID,
	ARGUMENTDATATYPE_DRAWABLEID,
	ARGUMENTDATATYPE_TEAMID,
	ARGUMENTDATATYPE_LOCATION,
	ARGUMENTDATATYPE_PIXEL,
	ARGUMENTDATATYPE_PIXELREGION,
	ARGUMENTDATATYPE_TIMESTAMP,
	ARGUMENTDATATYPE_WIDECHAR,
	ARGUMENTDATATYPE_UNKNOWN
};

class GameMessage
{
public:
	unsigned char getArgumentCount() const { return m_argCount; }
	GameMessageArgumentDataType getArgumentDataType(int argIndex);
private:
	char m_pad[0x18];
	unsigned char m_argCount;
};

class Rva0054D54A
{
public:
	Rva0054D54A();
	Rva0054D54A(GameMessage *msg);
	virtual ~Rva0054D54A();
private:
	Rva0054D54ANode *m_04;
	void *m_08;
	int m_0C;
};

Rva0054D54A::Rva0054D54A()
	: m_04(0), m_08(0), m_0C(0)
{
}

// ??1Rva0054D54A@@UAE@XZ @0x0054D55E 53B: the bytes of ~NetCommandWrapperList
// except the vtable stored on entry.
Rva0054D54A::~Rva0054D54A()
{
	while (m_04 != 0) {
		Rva0054D54ANode *next = m_04->m_next;
		void *p = m_04 ? m_04->destroy(0) : 0;
		::operator delete(p);
		m_04 = next;
	}
}

// ??0Rva001FD2B4@@QAE@XZ @0x001FD2B4 17B, vtable VA 0xbe1aa0
class Rva001FD2B4 : public RvaSmallVtableZeroBase2
{
public:
	Rva001FD2B4();
	virtual ~Rva001FD2B4() {}
};

Rva001FD2B4::Rva001FD2B4()
{
}

// ??0Rva002D24F6@@QAE@XZ @0x002D24F6 17B, vtable VA 0xc02a5c
class Rva002D24F6 : public RvaSmallVtableZeroBase2
{
public:
	Rva002D24F6();
	virtual ~Rva002D24F6() {}
};

Rva002D24F6::Rva002D24F6()
{
}

// ??0Rva0043A340@@QAE@XZ @0x0043A340 17B, vtable VA 0xc3d490
class Rva0043A340 : public RvaSmallVtableZeroBase2
{
public:
	Rva0043A340();
	virtual ~Rva0043A340() {}
};

Rva0043A340::Rva0043A340()
{
}

// ??0Rva004817F4@@QAE@XZ @0x004817F4 17B, vtable VA 0xc49174
class Rva004817F4 : public RvaSmallVtableZeroBase2
{
public:
	Rva004817F4();
	virtual ~Rva004817F4() {}
};

Rva004817F4::Rva004817F4()
{
}

// ??0Rva003E3C22@@QAE@XZ @0x003E3C22 23B, vtable VA 0xc35b34
class Rva003E3C22
{
public:
	Rva003E3C22();
	virtual ~Rva003E3C22() {}
private:
	void *m_04;
	void *m_08;
	void *m_0C;
	void *m_10;
};

Rva003E3C22::Rva003E3C22()
	: m_04(0), m_08(0), m_0C(0), m_10(0)
{
}

// ??0Rva0054D593@@QAE@PAX0@Z @0x0054D593 29B, vtable VA 0xc6a778: zero +4,
// store first arg at +8, vtable, then second arg at +0xC. Two new-placement
// calls in 0x0054D5D3 pass the outer args through after a 0x10 operator new.
class Rva0054D593
{
	friend class Rva0054D5D3;
public:
	Rva0054D593(void *a, void *b);
	virtual ~Rva0054D593() {}
private:
	Rva0054D593 *m_04;
	void *m_08;
	void *m_0C;
};

Rva0054D593::Rva0054D593(void *a, void *b)
	: m_04(0), m_08(a), m_0C(b)
{
}

// ?rva0054D5D3@Rva0054D5D3@@QAEX PAX0@Z @0x0054D5D3 93B: list append with
// 0x10 operator new of Rva0054D593. Empty list sets head and tail to the new
// node; otherwise tails next is set and tail advances via a reload. Callers
// at 0x0054D699 0x0054D6B7 0x0037B908 0x00591FA8 pass the two data args.
class Rva0054D5D3
{
public:
	virtual ~Rva0054D5D3();
	void rva0054D5D3(void *a, void *b);
private:
	Rva0054D593 *m_04;
	Rva0054D593 *m_08;
};

void Rva0054D5D3::rva0054D5D3(void *a, void *b)
{
	if (m_04 == 0)
	{
		Rva0054D593 *p = new Rva0054D593(a, b);
		m_04 = p;
		m_08 = p;
	}
	else
	{
		Rva0054D593 *p = new Rva0054D593(a, b);
		m_08->m_04 = p;
		m_08 = m_08->m_04;
	}
}

// ??0Rva0054D54A@@QAE@PAVGameMessage@@@Z @0x0054D64D 123B: ZH's
// GameMessageParser(GameMessage *) constructor, statement for statement: runs
// of equal argument types become one rva0054D5D3(type, count) append each,
// counted at +0xC (ARGUMENTDATATYPE_UNKNOWN, 11, seeds the run type). The
// add-game-command room check 0x0058D92F builds one with operator new(0x10)
// and walks the +4 list it makes, so this class is GameMessageParser in all but
// name; the append is reached through its own address-named class.
Rva0054D54A::Rva0054D54A(GameMessage *msg)
	: m_04(0), m_08(0), m_0C(0)
{
	unsigned char argCount = msg->getArgumentCount();
	GameMessageArgumentDataType lasttype = ARGUMENTDATATYPE_UNKNOWN;
	int thisTypeCount = 0;
	for (unsigned char i = 0; i < argCount; ++i) {
		GameMessageArgumentDataType type = msg->getArgumentDataType(i);
		if (type != lasttype) {
			if (thisTypeCount > 0) {
				((Rva0054D5D3 *)this)->rva0054D5D3((void *)lasttype, (void *)thisTypeCount);
				++m_0C;
			}
			lasttype = type;
			thisTypeCount = 0;
		}
		++thisTypeCount;
	}
	if (thisTypeCount > 0) {
		((Rva0054D5D3 *)this)->rva0054D5D3((void *)lasttype, (void *)thisTypeCount);
		++m_0C;
	}
}

// ??0Rva000421C8 is a header inline elsewhere: other units emit select-any
// copies of it, so a strong definition here was a duplicate symbol in the
// linked build. This anchor only makes this unit emit its copy for the ledger
// row; it is not retail code. ??0Rva0007DF07 and ??0Rva0030D346 below are the
// same: their inline copies elsewhere (static instance, dtor TUs) forced the
// strong definitions here into duplicates as well.
#pragma inline_depth(0)
// ?bfmeEmitRva000421C8Ctor@@YAXPAVRva000421C8@@@Z present-unmatched
void bfmeEmitRva000421C8Ctor(Rva000421C8 *p)
{
	p->Rva000421C8::Rva000421C8();
}
// ?bfmeEmitRva0007DF07Ctor@@YAXPAVRva0007DF07@@@Z present-unmatched
void bfmeEmitRva0007DF07Ctor(Rva0007DF07 *p)
{
	p->Rva0007DF07::Rva0007DF07();
}
// ?bfmeEmitRva0030D346Ctor@@YAXPAVRva0030D346@@@Z present-unmatched
void bfmeEmitRva0030D346Ctor(Rva0030D346 *p)
{
	p->Rva0030D346::Rva0030D346();
}
#pragma inline_depth()
