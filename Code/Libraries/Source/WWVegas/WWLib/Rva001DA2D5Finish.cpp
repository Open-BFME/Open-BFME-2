// cl: /Ireference/shims/bfme2_ascii /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??1Rva001DA2D5@@UAE@XZ @0x001DA2D5 164B: dtor with TheAudio slot 0x130, a
// destructible owned buffer at +0xB8, 4 vectors, 2 StringBase, vtable switch
// 0x007DA270 to 0x007C5128; evidence callees rowed, callers 0x001DA757
// 0x004333EC, neighbours StlportVectorGrowthFootprints.
#include <vector>
#include "ascii_string.h"

class BfmeStringTailRecord156 { public: ~BfmeStringTailRecord156(); char m_pad[8]; };
struct RvaPair001D9F62 { AsciiString m_key; int m_value; };

class AudioManager
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
	virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
	virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
	virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
	virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47();
	virtual void s48(); virtual void s49(); virtual void s50(); virtual void s51();
	virtual void s52(); virtual void s53(); virtual void s54(); virtual void s55();
	virtual void s56(); virtual void s57(); virtual void s58(); virtual void s59();
	virtual void s60(); virtual void s61(); virtual void s62(); virtual void s63();
	virtual void s64(); virtual void s65(); virtual void s66(); virtual void s67();
	virtual void s68(); virtual void s69(); virtual void s70(); virtual void s71();
	virtual void s72(); virtual void s73(); virtual void s74(); virtual void s75();
	virtual void s76(void *p);
};

extern AudioManager *TheAudio;
extern "C" void __cdecl free(void *) throw(...);

// The +0xB8 slot is a destructible member, not a raw pointer freed from the
// class body. Retail's first cleanup state (byte [ebp-4]=6) sits on the free,
// below the body state 7 -- that is a subobject dtor, and it is the highest
// member so it runs first. Written as a body-level free the compiler has no
// state to lower to and the dtor comes out 160B vs 164B.
class Rva001DA2D5OwnedFree
{
public:
	~Rva001DA2D5OwnedFree() { if (m_ptr != 0) free(m_ptr); }
private:
	void *m_ptr;
};

class Rva001DA2D5Base
{
public:
	virtual ~Rva001DA2D5Base() {}
};

class Rva001DA2D5 : public Rva001DA2D5Base
{
public:
	virtual ~Rva001DA2D5();
private:
	char m_pad04[4];
	AsciiString m_str08;
	AsciiString m_str0C;
	char m_pad10[0x50 - 0x10];
	_STL::vector<RvaPair001D9F62> m_vec50;
	int m_unk5C;
	_STL::vector<RvaPair001D9F62> m_vec60;
	int m_unk6C;
	_STL::vector<RvaPair001D9F62> m_vec70;
	int m_unk7C;
	_STL::vector<BfmeStringTailRecord156> m_vec80;
	char m_pad8C[0xB8 - 0x8C];
	Rva001DA2D5OwnedFree m_ownedB8;
};

Rva001DA2D5::~Rva001DA2D5()
{
	if (TheAudio != 0)
		TheAudio->s76(this);
}
