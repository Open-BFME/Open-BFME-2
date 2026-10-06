// cl: /D_STLP_USE_STATIC_LIB /D_BFME_RETAIL_TREE_INSERT_LAYOUT /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/reference/shims/nat /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// ??0Rva005E4AE2@@QAE@PAXPAU_Rva005E4AE2In@@H@Z @0x005E4AE2 141B.
// Constructor of a two-base object that registers its listener base with a
// holder's list through the rowed append 0x005A0B4C. Retail's unwind map:
// state 0 destroys the first polymorphic base through the vptr setter
// 0x005E394E, state 1 the +4 listener base through 0x005E3947, state 2 the
// map<int, void *> at +0x1C (ctor 0x0033C432). The +4 subobject first gets
// its own vtable 0x00C79544 and then this class's second vtable, the pattern
// of a second base. Its vtable differs from the listener base of
// Rva0057605DCtor.cpp, so it keeps its own address-derived name and is passed
// to the list as the list's pointer type. Replaces the banked 0.91 attempt,
// which wrote the vtable stores as volatile integers.
#include <map>
struct Rva002BA8F1Listener;
struct Rva005E4AE2Listener
{
	Rva005E4AE2Listener() {}
	virtual ~Rva005E4AE2Listener();
};
class Rva005A0B4CList
{
public:
	void append(Rva002BA8F1Listener *p);
private:
	char m_pad[12];
};
struct Rva005E4AE2Holder
{
	Rva005A0B4CList m_list;
	char m_pad0C[8];
	int m_14;
};
struct _Rva005E4AE2In
{
	int m_00;
	int m_04;
	Rva005E4AE2Holder *m_08;
};
class Rva005E4AE2Base
{
public:
	Rva005E4AE2Base() {}
	virtual ~Rva005E4AE2Base();
};
class Rva005E4AE2 : public Rva005E4AE2Base, public Rva005E4AE2Listener
{
public:
	Rva005E4AE2(void *a1, _Rva005E4AE2In *a2, int a3);
	virtual ~Rva005E4AE2();
private:
	void *m_08;
	int m_0C;
	int m_10;
	Rva005E4AE2Holder *m_14;
	int m_18;
	_STL::map<int, void *> m_1C;
	int m_28;
	unsigned char m_2C;
	unsigned char m_2D;
};
Rva005E4AE2::Rva005E4AE2(void *a1, _Rva005E4AE2In *a2, int a3)
	: m_08(a1)
	, m_0C(a2->m_00)
	, m_10(a2->m_04)
	, m_14(a2->m_08)
	, m_18(a3)
	, m_1C()
{
	m_28 = 0;
	m_2C = 0;
	m_2D = (a2->m_08->m_14 != 0);
	m_14->m_list.append((Rva002BA8F1Listener *)static_cast<Rva005E4AE2Listener *>(this));
}
