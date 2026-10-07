// cl: /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /arch:SSE
// PersistentStorageThread.cpp -- GameSpy persistent-stats members recovered
// from WorldBuilder leads (reverse/wb_name_leads.csv): WB's debug build names
// each function; retail supplies the bytes.

// Canonical one-pointer AsciiString temporary used by the native wire adapter.
#include "ascii_string.h"
// stlport
#include <cstdlib>
#include <cstring>
#include <ctime>
void Rva00030830FreeAllocation(void *);
// Retail map teardown uses the independently rowed game allocator, whose
// C++ call route retains the native unwind-state transition.
#define free Rva00030830FreeAllocation
#include <map>
#undef free
// STLport has already supplied the placement-new operators.
#define _OPERATOR_NEW_DEFINED_
#include <mutex.h>
// Inline the stock integer comparison without emitting an /O1 COMDAT
// that competes with the independently rowed /Od less<int> provider.
template <> __declspec(dllimport) __forceinline bool _STL::less<int>::operator()(const int &left, const int &right) const { return left < right; }
typedef _STL::map<unsigned char, short> StatsShortMap;
typedef _STL::map<unsigned char, int> StatsIntMap;
template <> int &StatsIntMap::operator[](const unsigned char &);
typedef _STL::map<unsigned char, float> StatsFloatMap;
template <> short &StatsShortMap::operator[](const unsigned char &);
template <> float &StatsFloatMap::operator[](const unsigned char &);

namespace _STL
{
template <class CharT> class char_traits;
template <class CharT> class allocator;
template <class CharT, class Traits, class Alloc> class basic_string
{
public:
    basic_string();
    ~basic_string();
	basic_string &operator=(const CharT *text);
    basic_string &assign(const basic_string &);
    unsigned size() const { return finish - start; }
private:
    CharT *start;
    CharT *finish;
    CharT *storageEnd;
};
}

typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> >
	Rva00385333String;

extern const char g_Rva0107301CEmptyString[];
//
// PSPlayerAllStats keeps the player id at +0x00 and three stats blocks: the
// open-play block at +0x1B0 (0x190 bytes), the strategic block at +0x340
// (0x208 bytes) and the tournament block at +0x08 (0x1A8 bytes). Each block
// carries its player id at +0x150, is passed by value and is assigned with an
// out-of-line operator=; the blocks' destructors are rowed under the
// placeholder class names used here.

typedef int Int;
// Native stats reset [553E47,553F2F),232B and tournament clear
// [553FDD,55401D),64B. GameSpy persistent-storage reference family, with
// BFME2's proven 12-byte map stride and target-specific field groups.
// The ZH/BFME1 PSPlayerStats reset is a semantic lead; this target's precise
// base record name and map key/value identities remain unproved.
class Rva0038201D {
    unsigned m_words[3];
public:
    void rva003828B6();
};
class Rva0038204A {
    unsigned m_words[3];
public:
    void rva003828DF();
};
class Rva00382077 {
    unsigned m_words[3];
public:
    void rva00382908();
};
// Physical ABI used by the already recovered177-byte XferMap provider.
// Native slot28 receives two adjacent version bytes, both initialized to1.
struct StatsXferVersion { unsigned char first, second; };
class XferStub {
public:
    virtual ~XferStub();
    virtual void _unused1();
    virtual bool _isWriting();
    virtual void _unused3();
    virtual void _unused4();
    virtual void _unused5();
    virtual void _unused6();
    virtual void _unused7();
    virtual void _unused8();
    virtual void _unused9();
    virtual void _slot28(StatsXferVersion &);
    virtual void _unused11();
    virtual void _unused12();
    virtual void _unused13();
    virtual void _unused14();
    virtual void _unused15();
    virtual void _unused16();
    virtual void _unused17();
    virtual void _unused18();
    virtual void _unused19();
    virtual void _unused20();
    virtual void _unused21();
    virtual void _unused22();
    virtual void _unused23();
    virtual void _unused24();
    virtual void _unused25();
    virtual void _unused26();
    virtual void _slot6c(AsciiString &);
    virtual void _unused28();
    virtual void _unused29();
    virtual void _slot78(int &);
    virtual void _slot7c(int &);
    virtual void _slot80(short &);
};
class MapHolder;
class MapFloatHolder;
class MapIntHolder;
class PSPlayerStats {
public:
    void XferMap(MapHolder *, XferStub *);
    void rva0055499A(MapFloatHolder *, XferStub *);
    void rva00554A4A(MapIntHolder *, XferStub *);
};
class Rva00553E47StatsCore {
public:
    Rva00553E47StatsCore(const Rva00553E47StatsCore &);
    Rva00553E47StatsCore(int id);
    virtual void reset();
    virtual void rva005550A0(XferStub *);
    virtual void rva00555109(XferStub *);
    virtual void rva00554AF2(const Rva00553E47StatsCore *);
private:
    StatsShortMap m_maps04_0;
    StatsShortMap m_maps04_1;
    StatsShortMap m_maps04_2;
    StatsShortMap m_maps04_3;
    StatsShortMap m_maps04_4;
    StatsShortMap m_maps04_5;

    StatsShortMap m_maps4c[6];
    StatsShortMap m_maps94[6];
    StatsFloatMap m_mapsdc_0;
    StatsFloatMap m_mapsdc_1;
    StatsFloatMap m_mapsdc_2;
    StatsFloatMap m_mapsdc_3;
    StatsFloatMap m_mapsdc_4;
    StatsFloatMap m_mapsdc_5;
    StatsFloatMap m_mapsdc_6;
    StatsFloatMap m_mapsdc_7;

    unsigned m_13c, m_140;
    unsigned short m_144, m_146, m_148, m_14a, m_14c;
    unsigned short m_unmodelled14e;
public:
    int m_id;
    unsigned short getField144() const { return m_144; }
};
typedef char StatsMapStrideCheck[sizeof(Rva0038201D) == 12 ? 1 : -1];
typedef char StatsCoreSizeCheck[sizeof(Rva00553E47StatsCore) == 0x154 ? 1 : -1];
void Rva00553E47StatsCore::reset() {
    m_id = 0;
    ((Rva0038201D *)&m_maps04_0)->rva003828B6();
    ((Rva0038201D *)&m_maps04_1)->rva003828B6();
    ((Rva0038201D *)&m_maps04_2)->rva003828B6();
    ((Rva0038201D *)&m_maps04_3)->rva003828B6();
    ((Rva0038201D *)&m_maps04_4)->rva003828B6();
    ((Rva0038201D *)&m_maps04_5)->rva003828B6();
    for (int i = 0; i < 6; ++i) {
        ((Rva0038201D *)&m_maps4c[i])->rva003828B6();
        ((Rva0038201D *)&m_maps94[i])->rva003828B6();
    }
    ((Rva0038204A *)&m_mapsdc_0)->rva003828DF();
    ((Rva0038204A *)&m_mapsdc_1)->rva003828DF();
    ((Rva0038204A *)&m_mapsdc_2)->rva003828DF();
    ((Rva0038204A *)&m_mapsdc_3)->rva003828DF();
    ((Rva0038204A *)&m_mapsdc_4)->rva003828DF();
    ((Rva0038204A *)&m_mapsdc_5)->rva003828DF();
    ((Rva0038204A *)&m_mapsdc_6)->rva003828DF();
    ((Rva0038204A *)&m_mapsdc_7)->rva003828DF();
    m_13c = 0;
    m_140 = 0;
    m_144 = 0;
    m_146 = 0;
    m_148 = 0;
    m_14a = 0;
    m_14c = 0;
}


// Native open-play vtable86B100 extends the core with prefix merge555845.
class Rva003844D7 : public Rva00553E47StatsCore {
public:
    Rva003844D7(int);
    Rva003844D7(const Rva003844D7 &);
    virtual void reset();
    virtual void rva00555109(XferStub *);
    virtual void rva00555845(const Rva003844D7 *);
    ~Rva003844D7();
    Rva003844D7 &operator=(const Rva003844D7 &);
    StatsIntMap m_map154;
    StatsShortMap m_map160, m_map16c;
    StatsFloatMap m_map178, m_map184;
};
typedef char OpenPlaySizeCheck[sizeof(Rva003844D7)==0x190?1:-1];

class Rva0038454E : public Rva00553E47StatsCore	// strategic stats block
{
public:
    Rva0038454E(int);
    Rva0038454E(const Rva0038454E &);
    virtual void reset();
    virtual void rva00555109(XferStub *);
    virtual void rva0055524B(const Rva0038454E *);
	~Rva0038454E();						// 0x0038454E
	Rva0038454E &operator=(const Rva0038454E &that);	// 0x00387945

    StatsFloatMap m_map154;
    StatsFloatMap m_map160;
    StatsFloatMap m_map16c;
    StatsFloatMap m_map178;
    StatsFloatMap m_map184;
    StatsFloatMap m_map190;
    StatsFloatMap m_map19c;
    StatsFloatMap m_map1a8;
    StatsShortMap m_map1b4;
    StatsShortMap m_map1c0;
    StatsFloatMap m_map1cc;
    StatsFloatMap m_map1d8;
    StatsFloatMap m_map1e4;
    StatsFloatMap m_map1f0;
    StatsFloatMap m_map1fc;

};

class Rva00385333 : public Rva003844D7	// tournament stats block
{
public:
	Rva00385333(int);
	Rva00385333(const Rva00385333 &);
    void rva00555DDC(XferStub *);
	void rva00555F68();
	~Rva00385333();						// 0x00385333
	Rva00385333 &operator=(const Rva00385333 &that);	// 0x00387A68

	unsigned short m_190;
	unsigned short m_192;
	Int m_194;
	Int m_198;
	Rva00385333String m_text19C;
};

class PSPlayerAllStats
{
public:
    PSPlayerAllStats(Int id);
    void rva00552CB8();
    void rva00552E9E(Int v);
    Rva003844D7 rva00389DF1() const;
    Rva0038454E rva00389E0F() const;
    Rva00385333 rva00556508() const;
	PSPlayerAllStats &operator=(const PSPlayerAllStats &that);
	void setOpenPlayStats(Rva003844D7 stats);
	void setStrategicStats(Rva0038454E stats);
	void setTournamentStats(Rva00385333 stats);
	// Stores the id into each block's +0x150 slot from last to first, then +0.
	void setID(Int id)
	{
		m_strategicStats.m_id = id;
		m_openPlayStats.m_id = id;
		m_tournamentStats.m_id = id;
		m_id = id;
	}

private:
	Int m_id;						// +0x000
	Int m_unk004;					// +0x004 copied by operator= @0x003874B0
	Rva00385333 m_tournamentStats;				// +0x008
	Rva003844D7 m_openPlayStats;				// +0x1B0
	Rva0038454E m_strategicStats;				// +0x340
};

// ??4PSPlayerAllStats@@QAEAAV0@ABV0@@Z 0x003874B0 73B: thiscall operator= copies
// m_id plus three stats blocks via their out-of-line operator=; evidence pins
// for the three callees naming PSPlayerAllStats set* at +0x008 +0x1B0 +0x340.
PSPlayerAllStats &PSPlayerAllStats::operator=(const PSPlayerAllStats &that)
{
	m_id = that.m_id;
	m_unk004 = that.m_unk004;
	m_tournamentStats = that.m_tournamentStats;
	m_openPlayStats = that.m_openPlayStats;
	m_strategicStats = that.m_strategicStats;
	return *this;
}

// PSPlayerAllStats::setOpenPlayStats, retail 0x00555AE7.
void PSPlayerAllStats::setOpenPlayStats(Rva003844D7 stats)
{
	if (m_id == 0 || m_id == stats.m_id)
	{
		m_id = stats.m_id;
		m_openPlayStats = stats;
	}
}

// PSPlayerAllStats::setStrategicStats, retail 0x00555B30.
void PSPlayerAllStats::setStrategicStats(Rva0038454E stats)
{
	if (m_id == 0 || m_id == stats.m_id)
	{
		m_id = stats.m_id;
		m_strategicStats = stats;
	}
}

// PSPlayerAllStats::setTournamentStats, retail 0x00555FA0.
void PSPlayerAllStats::setTournamentStats(Rva00385333 stats)
{
	if (m_id == 0 || m_id == stats.m_id)
	{
		m_id = stats.m_id;
		m_tournamentStats = stats;
	}
}

// ?rva00555F68@Rva00385333@@QAEXXZ, retail 0x00555F68. Target evidence:
// this 56-byte body calls 0x00553FDD; writes the final scalar fields at +0x190
// through +0x198; and assigns the narrow string at +0x19C from 0x00BBAC1C.
// The original method name remains unresolved.
void Rva00385333::rva00555F68()
{
	Rva003844D7::reset();
	m_190 &= 0;
	m_192 &= 0;
	m_194 |= -1;
	m_198 |= -1;
	((Rva00385333String *)(char *)&m_text19C)->operator=(g_Rva0107301CEmptyString);
}

void Rva003844D7::reset() {
    ((Rva00553E47StatsCore *)this)->Rva00553E47StatsCore::reset();
    ((Rva00382077 *)((char *)&m_map154))->rva00382908();
    ((Rva0038201D *)((char *)&m_map160))->rva003828B6();
    ((Rva0038201D *)((char *)&m_map16c))->rva003828B6();
    ((Rva0038204A *)((char *)&m_map178))->rva003828DF();
    ((Rva0038204A *)((char *)&m_map184))->rva003828DF();
}

// [553F2F,553FDD),174B clears the same fifteen 12-byte map slots that
// the verified strategic-block assignment387945 and destructor38454E use.
// Eight maps, two of the other map ABI, then five maps; core reset is553E47.
void Rva0038454E::reset() {
    ((Rva00553E47StatsCore *)this)->Rva00553E47StatsCore::reset();
    ((Rva0038204A *)((char *)&m_map154))->rva003828DF();
    ((Rva0038204A *)((char *)&m_map160))->rva003828DF();
    ((Rva0038204A *)((char *)&m_map16c))->rva003828DF();
    ((Rva0038204A *)((char *)&m_map178))->rva003828DF();
    ((Rva0038204A *)((char *)&m_map184))->rva003828DF();
    ((Rva0038204A *)((char *)&m_map190))->rva003828DF();
    ((Rva0038204A *)((char *)&m_map19c))->rva003828DF();
    ((Rva0038204A *)((char *)&m_map1a8))->rva003828DF();
    ((Rva0038201D *)((char *)&m_map1b4))->rva003828B6();
    ((Rva0038201D *)((char *)&m_map1c0))->rva003828B6();
    ((Rva0038204A *)((char *)&m_map1cc))->rva003828DF();
    ((Rva0038204A *)((char *)&m_map1d8))->rva003828DF();
    ((Rva0038204A *)((char *)&m_map1e4))->rva003828DF();
    ((Rva0038204A *)((char *)&m_map1f0))->rva003828DF();
    ((Rva0038204A *)((char *)&m_map1fc))->rva003828DF();
}

// Native [5550A0,555109),105B transfers two maps and three scalars from
// the same core reset at553E47. Every call is an existing provider or a
// native Xfer vtable slot; the original method name remains unresolved.
void Rva00553E47StatsCore::rva005550A0(XferStub *xfer) {
    StatsXferVersion version;
    version.first = 1;
    version.second = 1;
    xfer->_slot28(version);
    ((PSPlayerStats *)this)->XferMap((MapHolder *)&m_maps04_0, xfer);
    ((PSPlayerStats *)this)->XferMap((MapHolder *)&m_maps04_1, xfer);
    xfer->_slot78((int &)m_13c);
    xfer->_slot78((int &)m_140);
    xfer->_slot80((short &)m_144);
}

// Native [555109,55524B),322B continues the core transfer: four short maps,
// six paired short-map groups, eight float maps (last since version2), four shorts.
void Rva00553E47StatsCore::rva00555109(XferStub *xfer) {
    StatsXferVersion version;
    version.first=1;
    version.second=2;
    xfer->_slot28(version);
    ((PSPlayerStats *)this)->XferMap((MapHolder *)&m_maps04_2, xfer);
    ((PSPlayerStats *)this)->XferMap((MapHolder *)&m_maps04_3, xfer);
    ((PSPlayerStats *)this)->XferMap((MapHolder *)&m_maps04_4, xfer);
    ((PSPlayerStats *)this)->XferMap((MapHolder *)&m_maps04_5, xfer);
    for (int i=0;i<6;++i) {
        ((PSPlayerStats *)this)->XferMap((MapHolder *)&m_maps4c[i], xfer);
        ((PSPlayerStats *)this)->XferMap((MapHolder *)&m_maps94[i], xfer);
    }
    ((PSPlayerStats *)this)->rva0055499A((MapFloatHolder *)&m_mapsdc_0, xfer);
    ((PSPlayerStats *)this)->rva0055499A((MapFloatHolder *)&m_mapsdc_1, xfer);
    ((PSPlayerStats *)this)->rva0055499A((MapFloatHolder *)&m_mapsdc_2, xfer);
    ((PSPlayerStats *)this)->rva0055499A((MapFloatHolder *)&m_mapsdc_3, xfer);
    ((PSPlayerStats *)this)->rva0055499A((MapFloatHolder *)&m_mapsdc_4, xfer);
    ((PSPlayerStats *)this)->rva0055499A((MapFloatHolder *)&m_mapsdc_5, xfer);
    ((PSPlayerStats *)this)->rva0055499A((MapFloatHolder *)&m_mapsdc_6, xfer);
    if (version.second >= 2)
        ((PSPlayerStats *)this)->rva0055499A((MapFloatHolder *)&m_mapsdc_7, xfer);
    xfer->_slot80((short &)m_146);
    xfer->_slot80((short &)m_148);
    xfer->_slot80((short &)m_14a);
    xfer->_slot80((short &)m_14c);
}

// Native rva0055573B: core transfer then version1 and the same map groups as its reset.
void Rva0038454E::rva00555109(XferStub *xfer) {
    ((Rva00553E47StatsCore *)this)->Rva00553E47StatsCore::rva00555109(xfer);
    // Retail keeps the two version bytes in a reusable four-byte stack slot.
    union { StatsXferVersion version; unsigned versionStorage; };
    version.first=1;
    version.second=1;
    xfer->_slot28(version);
    ((PSPlayerStats *)this)->rva0055499A((MapFloatHolder *)((char *)&m_map154), xfer);
    ((PSPlayerStats *)this)->rva0055499A((MapFloatHolder *)((char *)&m_map160), xfer);
    ((PSPlayerStats *)this)->rva0055499A((MapFloatHolder *)((char *)&m_map16c), xfer);
    ((PSPlayerStats *)this)->rva0055499A((MapFloatHolder *)((char *)&m_map178), xfer);
    ((PSPlayerStats *)this)->rva0055499A((MapFloatHolder *)((char *)&m_map184), xfer);
    ((PSPlayerStats *)this)->rva0055499A((MapFloatHolder *)((char *)&m_map190), xfer);
    ((PSPlayerStats *)this)->rva0055499A((MapFloatHolder *)((char *)&m_map19c), xfer);
    ((PSPlayerStats *)this)->rva0055499A((MapFloatHolder *)((char *)&m_map1a8), xfer);
    ((PSPlayerStats *)this)->XferMap((MapHolder *)((char *)&m_map1b4), xfer);
    ((PSPlayerStats *)this)->XferMap((MapHolder *)((char *)&m_map1c0), xfer);
    ((PSPlayerStats *)this)->rva0055499A((MapFloatHolder *)((char *)&m_map1cc), xfer);
    ((PSPlayerStats *)this)->rva0055499A((MapFloatHolder *)((char *)&m_map1d8), xfer);
    ((PSPlayerStats *)this)->rva0055499A((MapFloatHolder *)((char *)&m_map1e4), xfer);
    ((PSPlayerStats *)this)->rva0055499A((MapFloatHolder *)((char *)&m_map1f0), xfer);
    ((PSPlayerStats *)this)->rva0055499A((MapFloatHolder *)((char *)&m_map1fc), xfer);
}

// Native rva00555988: core transfer then version1 and the same map groups as its reset.
void Rva003844D7::rva00555109(XferStub *xfer) {
    ((Rva00553E47StatsCore *)this)->Rva00553E47StatsCore::rva00555109(xfer);
    // Retail keeps the two version bytes in a reusable four-byte stack slot.
    union { StatsXferVersion version; unsigned versionStorage; };
    version.first=1;
    version.second=1;
    xfer->_slot28(version);
    ((PSPlayerStats *)this)->rva00554A4A((MapIntHolder *)((char *)&m_map154), xfer);
    ((PSPlayerStats *)this)->XferMap((MapHolder *)((char *)&m_map160), xfer);
    ((PSPlayerStats *)this)->XferMap((MapHolder *)((char *)&m_map16c), xfer);
    ((PSPlayerStats *)this)->rva0055499A((MapFloatHolder *)((char *)&m_map178), xfer);
    ((PSPlayerStats *)this)->rva0055499A((MapFloatHolder *)((char *)&m_map184), xfer);
}

// Native [555DDC,555EB4),216B bridges the stored STL narrow string at19C
// through an AsciiString wire temporary; scalars agree with reset555F68.
void Rva00385333::rva00555DDC(XferStub *xfer) {
    ((Rva00553E47StatsCore *)this)->Rva00553E47StatsCore::rva005550A0(xfer);
    // Version bytes occupy a distinct aligned stack slot beside the wire string.
    union { StatsXferVersion version; unsigned versionStorage; };
    version.first=1;
    version.second=1;
    xfer->_slot28(version);
    xfer->_slot80((short &)m_190);
    xfer->_slot80((short &)m_192);
    xfer->_slot7c(m_194);
    xfer->_slot7c(m_198);
    AsciiString wireText;
    if (xfer->_isWriting()) {
        ((StringBase<char> *)&wireText)->set(*(const char **)(char *)&m_text19C);
        xfer->_slot6c(wireText);
    } else {
        xfer->_slot6c(wireText);
        ((Rva00385333String *)(char *)&m_text19C)->operator=(wireText.str());
    }
}

// BFME1 PSPlayerStats::incorporate (1399ad37) supplies the map-merge purpose;
// native [554AF2,554F70),1150B supplies BFME2 groups, scalar rules and ABI.
// Original field identities remain unresolved, so offsets retain neutral names.
void Rva00553E47StatsCore::rva00554AF2(const Rva00553E47StatsCore *other) {
    int i;
    if ((int)other->m_id > 0) m_id=other->m_id;
    for (StatsShortMap::const_iterator it=((const StatsShortMap *)&other->m_maps04_0)->begin(); it._M_node!=((const StatsShortMap *)&other->m_maps04_0)->end()._M_node; ++it) {
        if ((unsigned short)it->second > 0)
            (*(StatsShortMap *)&m_maps04_0)[it->first]=it->second;
    }
    for (StatsShortMap::const_iterator it=((const StatsShortMap *)&other->m_maps04_1)->begin(); it._M_node!=((const StatsShortMap *)&other->m_maps04_1)->end()._M_node; ++it) {
        if ((unsigned short)it->second > 0)
            (*(StatsShortMap *)&m_maps04_1)[it->first]=it->second;
    }
    for (StatsShortMap::const_iterator it=((const StatsShortMap *)&other->m_maps04_2)->begin(); it._M_node!=((const StatsShortMap *)&other->m_maps04_2)->end()._M_node; ++it) {
        (*(StatsShortMap *)&m_maps04_2)[it->first]=it->second;
    }
    for (StatsShortMap::const_iterator it=((const StatsShortMap *)&other->m_maps04_3)->begin(); it._M_node!=((const StatsShortMap *)&other->m_maps04_3)->end()._M_node; ++it) {
        (*(StatsShortMap *)&m_maps04_3)[it->first]=it->second;
    }
    for (StatsShortMap::const_iterator it=((const StatsShortMap *)&other->m_maps04_4)->begin(); it._M_node!=((const StatsShortMap *)&other->m_maps04_4)->end()._M_node; ++it) {
        if ((unsigned short)it->second > 0)
            (*(StatsShortMap *)&m_maps04_4)[it->first]=it->second;
    }
    for (StatsShortMap::const_iterator it=((const StatsShortMap *)&other->m_maps04_5)->begin(); it._M_node!=((const StatsShortMap *)&other->m_maps04_5)->end()._M_node; ++it) {
        if ((unsigned short)it->second > 0)
            (*(StatsShortMap *)&m_maps04_5)[it->first]=it->second;
    }
    for (i=0;i<6;++i) {
        for (StatsShortMap::const_iterator it=((const StatsShortMap *)&other->m_maps4c[i])->begin(); it._M_node!=((const StatsShortMap *)&other->m_maps4c[i])->end()._M_node; ++it) {
            if ((unsigned short)it->second > 0)
                (*(StatsShortMap *)&m_maps4c[i])[it->first]=it->second;
        }
    }
    for (i=0;i<6;++i) {
        for (StatsShortMap::const_iterator it=((const StatsShortMap *)&other->m_maps94[i])->begin(); it._M_node!=((const StatsShortMap *)&other->m_maps94[i])->end()._M_node; ++it) {
            if ((unsigned short)it->second > 0)
                (*(StatsShortMap *)&m_maps94[i])[it->first]=it->second;
        }
    }
    for (StatsFloatMap::const_iterator it=((const StatsFloatMap *)&other->m_mapsdc_0)->begin(); it._M_node!=((const StatsFloatMap *)&other->m_mapsdc_0)->end()._M_node; ++it) {
        if (it->second > 0.0f)
            (*(StatsFloatMap *)&m_mapsdc_0)[it->first]=it->second;
    }
    for (StatsFloatMap::const_iterator it=((const StatsFloatMap *)&other->m_mapsdc_1)->begin(); it._M_node!=((const StatsFloatMap *)&other->m_mapsdc_1)->end()._M_node; ++it) {
        if (it->second > 0.0f)
            (*(StatsFloatMap *)&m_mapsdc_1)[it->first]=it->second;
    }
    for (StatsFloatMap::const_iterator it=((const StatsFloatMap *)&other->m_mapsdc_2)->begin(); it._M_node!=((const StatsFloatMap *)&other->m_mapsdc_2)->end()._M_node; ++it) {
        if (it->second > 0.0f)
            (*(StatsFloatMap *)&m_mapsdc_2)[it->first]=it->second;
    }
    for (StatsFloatMap::const_iterator it=((const StatsFloatMap *)&other->m_mapsdc_3)->begin(); it._M_node!=((const StatsFloatMap *)&other->m_mapsdc_3)->end()._M_node; ++it) {
        if (it->second > 0.0f)
            (*(StatsFloatMap *)&m_mapsdc_3)[it->first]=it->second;
    }
    for (StatsFloatMap::const_iterator it=((const StatsFloatMap *)&other->m_mapsdc_4)->begin(); it._M_node!=((const StatsFloatMap *)&other->m_mapsdc_4)->end()._M_node; ++it) {
        if (it->second > 0.0f)
            (*(StatsFloatMap *)&m_mapsdc_4)[it->first]=it->second;
    }
    for (StatsFloatMap::const_iterator it=((const StatsFloatMap *)&other->m_mapsdc_5)->begin(); it._M_node!=((const StatsFloatMap *)&other->m_mapsdc_5)->end()._M_node; ++it) {
        if (it->second > 0.0f)
            (*(StatsFloatMap *)&m_mapsdc_5)[it->first]=it->second;
    }
    for (StatsFloatMap::const_iterator it=((const StatsFloatMap *)&other->m_mapsdc_6)->begin(); it._M_node!=((const StatsFloatMap *)&other->m_mapsdc_6)->end()._M_node; ++it) {
        if (it->second > 0.0f)
            (*(StatsFloatMap *)&m_mapsdc_6)[it->first]=it->second;
    }
    for (StatsFloatMap::const_iterator it=((const StatsFloatMap *)&other->m_mapsdc_7)->begin(); it._M_node!=((const StatsFloatMap *)&other->m_mapsdc_7)->end()._M_node; ++it) {
        if (it->second > 0.0f)
            (*(StatsFloatMap *)&m_mapsdc_7)[it->first]=it->second;
    }
    if (other->m_13c>0) m_13c=other->m_13c;
    if (other->m_140>0) m_140=other->m_140;
    if (other->m_144>0) m_144=other->m_144;
    m_146=other->m_146;
    m_148=other->m_148;
    m_14a=other->m_14a;
    m_14c=other->m_14c;
}

typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > Rva00555D74String;

class Rva00555D74
{
public:
    void rva00555D74(const Rva00555D74 *source);
private:
    unsigned char pad00[0x190];
    unsigned short word190;
    unsigned short word192;
    int value194;
    int value198;
    Rva00555D74String text19C;
};

void Rva00555D74::rva00555D74(const Rva00555D74 *source)
{
    ((Rva003844D7 *)this)->Rva003844D7::rva00555845((const Rva003844D7 *)source);
    word190 = source->word190;
    word192 = source->word192;
    if (source->value194 > 0)
        value194 = source->value194;
    if (source->value198 > 0)
        value198 = source->value198;
    if (source->text19C.size() != 0)
        text19C.assign(source->text19C);
}

// Native [555845,555988),323B merges five12-byte maps in the common prefix.
// Layout and signedness follow its own node tests; core merge is554AF2.
void Rva003844D7::rva00555845(const Rva003844D7 *source) {
    ((Rva00553E47StatsCore *)this)->Rva00553E47StatsCore::rva00554AF2((const Rva00553E47StatsCore *)source);
    for (StatsIntMap::const_iterator it=((const StatsIntMap *)((const char *)source+0x154))->begin(); it._M_node!=((const StatsIntMap *)((const char *)source+0x154))->end()._M_node; ++it) {
        if ((unsigned int)it->second > 0)
            (*(StatsIntMap *)((char *)this+0x154))[it->first]=it->second;
    }
    for (StatsShortMap::const_iterator it=((const StatsShortMap *)((const char *)source+0x160))->begin(); it._M_node!=((const StatsShortMap *)((const char *)source+0x160))->end()._M_node; ++it) {
        if ((unsigned short)it->second > 0)
            (*(StatsShortMap *)((char *)this+0x160))[it->first]=it->second;
    }
    for (StatsShortMap::const_iterator it=((const StatsShortMap *)((const char *)source+0x16c))->begin(); it._M_node!=((const StatsShortMap *)((const char *)source+0x16c))->end()._M_node; ++it) {
        if ((unsigned short)it->second > 0)
            (*(StatsShortMap *)((char *)this+0x16c))[it->first]=it->second;
    }
    for (StatsFloatMap::const_iterator it=((const StatsFloatMap *)((const char *)source+0x178))->begin(); it._M_node!=((const StatsFloatMap *)((const char *)source+0x178))->end()._M_node; ++it) {
        if (it->second > 0.0f)
            (*(StatsFloatMap *)((char *)this+0x178))[it->first]=it->second;
    }
    for (StatsFloatMap::const_iterator it=((const StatsFloatMap *)((const char *)source+0x184))->begin(); it._M_node!=((const StatsFloatMap *)((const char *)source+0x184))->end()._M_node; ++it) {
        if (it->second > 0.0f)
            (*(StatsFloatMap *)((char *)this+0x184))[it->first]=it->second;
    }
}

// Native [554F70,5550A0),304B copy constructor initializes map members,
// resets the record, then incorporates its source through554AF2.
Rva00553E47StatsCore::Rva00553E47StatsCore(const Rva00553E47StatsCore &source) {
    reset();
    rva00554AF2(&source);
}

struct StatsSystemTime {
    unsigned short year, month, dayOfWeek, day, hour, minute, second, milliseconds;
};
extern "C" __declspec(dllimport) void __stdcall GetLocalTime(StatsSystemTime *);
// Native [554463,55459E),315B initializes the same map/vtable groups as
// the copy constructor, resets, sets the id at150, and queries local time.
Rva00553E47StatsCore::Rva00553E47StatsCore(int id) {
    reset();
    m_id=id;
    StatsSystemTime localTime;
    GetLocalTime(&localTime);
}

// Native strategic vtable86B0EC has core slots0..3 and this fifth slot55524B.
// Its15 maps agree with reset553F2F and xfer55573B, each with its own tests.
void Rva0038454E::rva0055524B(const Rva0038454E *source) {
    Rva00553E47StatsCore::rva00554AF2(source);
    for (StatsFloatMap::const_iterator it=((const StatsFloatMap *)((const char *)&source->m_map154))->begin(); it._M_node!=((const StatsFloatMap *)((const char *)&source->m_map154))->end()._M_node; ++it) {
        if (it->second > 0.0f)
            (*(StatsFloatMap *)((char *)&m_map154))[it->first]=it->second;
    }
    for (StatsFloatMap::const_iterator it=((const StatsFloatMap *)((const char *)&source->m_map160))->begin(); it._M_node!=((const StatsFloatMap *)((const char *)&source->m_map160))->end()._M_node; ++it) {
        if (it->second > 0.0f)
            (*(StatsFloatMap *)((char *)&m_map160))[it->first]=it->second;
    }
    for (StatsFloatMap::const_iterator it=((const StatsFloatMap *)((const char *)&source->m_map16c))->begin(); it._M_node!=((const StatsFloatMap *)((const char *)&source->m_map16c))->end()._M_node; ++it) {
        if (it->second > 0.0f)
            (*(StatsFloatMap *)((char *)&m_map16c))[it->first]=it->second;
    }
    for (StatsFloatMap::const_iterator it=((const StatsFloatMap *)((const char *)&source->m_map178))->begin(); it._M_node!=((const StatsFloatMap *)((const char *)&source->m_map178))->end()._M_node; ++it) {
        if (it->second > 0.0f)
            (*(StatsFloatMap *)((char *)&m_map178))[it->first]=it->second;
    }
    for (StatsFloatMap::const_iterator it=((const StatsFloatMap *)((const char *)&source->m_map184))->begin(); it._M_node!=((const StatsFloatMap *)((const char *)&source->m_map184))->end()._M_node; ++it) {
        if (it->second > 0.0f)
            (*(StatsFloatMap *)((char *)&m_map184))[it->first]=it->second;
    }
    for (StatsFloatMap::const_iterator it=((const StatsFloatMap *)((const char *)&source->m_map190))->begin(); it._M_node!=((const StatsFloatMap *)((const char *)&source->m_map190))->end()._M_node; ++it) {
        if (it->second > 0.0f)
            (*(StatsFloatMap *)((char *)&m_map190))[it->first]=it->second;
    }
    for (StatsFloatMap::const_iterator it=((const StatsFloatMap *)((const char *)&source->m_map19c))->begin(); it._M_node!=((const StatsFloatMap *)((const char *)&source->m_map19c))->end()._M_node; ++it) {
        if (it->second > 0.0f)
            (*(StatsFloatMap *)((char *)&m_map19c))[it->first]=it->second;
    }
    for (StatsFloatMap::const_iterator it=((const StatsFloatMap *)((const char *)&source->m_map1a8))->begin(); it._M_node!=((const StatsFloatMap *)((const char *)&source->m_map1a8))->end()._M_node; ++it) {
        if (it->second > 0.0f)
            (*(StatsFloatMap *)((char *)&m_map1a8))[it->first]=it->second;
    }
    for (StatsShortMap::const_iterator it=((const StatsShortMap *)((const char *)&source->m_map1b4))->begin(); it._M_node!=((const StatsShortMap *)((const char *)&source->m_map1b4))->end()._M_node; ++it) {
        if ((unsigned short)it->second > 0)
            (*(StatsShortMap *)((char *)&m_map1b4))[it->first]=it->second;
    }
    for (StatsShortMap::const_iterator it=((const StatsShortMap *)((const char *)&source->m_map1c0))->begin(); it._M_node!=((const StatsShortMap *)((const char *)&source->m_map1c0))->end()._M_node; ++it) {
        if ((unsigned short)it->second > 0)
            (*(StatsShortMap *)((char *)&m_map1c0))[it->first]=it->second;
    }
    for (StatsFloatMap::const_iterator it=((const StatsFloatMap *)((const char *)&source->m_map1cc))->begin(); it._M_node!=((const StatsFloatMap *)((const char *)&source->m_map1cc))->end()._M_node; ++it) {
        if (it->second > 0.0f)
            (*(StatsFloatMap *)((char *)&m_map1cc))[it->first]=it->second;
    }
    for (StatsFloatMap::const_iterator it=((const StatsFloatMap *)((const char *)&source->m_map1d8))->begin(); it._M_node!=((const StatsFloatMap *)((const char *)&source->m_map1d8))->end()._M_node; ++it) {
        if (it->second > 0.0f)
            (*(StatsFloatMap *)((char *)&m_map1d8))[it->first]=it->second;
    }
    for (StatsFloatMap::const_iterator it=((const StatsFloatMap *)((const char *)&source->m_map1e4))->begin(); it._M_node!=((const StatsFloatMap *)((const char *)&source->m_map1e4))->end()._M_node; ++it) {
        if (it->second > 0.0f)
            (*(StatsFloatMap *)((char *)&m_map1e4))[it->first]=it->second;
    }
    for (StatsFloatMap::const_iterator it=((const StatsFloatMap *)((const char *)&source->m_map1f0))->begin(); it._M_node!=((const StatsFloatMap *)((const char *)&source->m_map1f0))->end()._M_node; ++it) {
        if (it->second > 0.0f)
            (*(StatsFloatMap *)((char *)&m_map1f0))[it->first]=it->second;
    }
    for (StatsFloatMap::const_iterator it=((const StatsFloatMap *)((const char *)&source->m_map1fc))->begin(); it._M_node!=((const StatsFloatMap *)((const char *)&source->m_map1fc))->end()._M_node; ++it) {
        if (it->second > 0.0f)
            (*(StatsFloatMap *)((char *)&m_map1fc))[it->first]=it->second;
    }
}
typedef char StrategicStatsSizeCheck[sizeof(Rva0038454E)==0x208?1:-1];

// Strategic constructors use the same15 map members as reset/xfer/merge,
// both starting from the base id0 constructor.
Rva0038454E::Rva0038454E(int id) : Rva00553E47StatsCore(0) {
    reset();
    m_id=id;
}
Rva0038454E::Rva0038454E(const Rva0038454E &source) : Rva00553E47StatsCore(0) {
    reset();
    rva0055524B(&source);
}

Rva003844D7::Rva003844D7(int id) : Rva00553E47StatsCore(0) {
    reset();
    m_id=id;
}
Rva003844D7::Rva003844D7(const Rva003844D7 &source) : Rva00553E47StatsCore(0) {
    reset();
    rva00555845(&source);
}

// Tournament vtable86B114 inherits the five prefix slots and adds final merge.
Rva00385333::Rva00385333(int id) : Rva003844D7(0) {
    rva00555F68();
    m_id = id;
}
Rva00385333::Rva00385333(const Rva00385333 &source) : Rva003844D7(0) {
    rva00555F68();
    ((Rva00555D74 *)this)->rva00555D74((const Rva00555D74 *)&source);
}

// These return the same concrete members as the native RVO getters389DF1/389E0F.
Rva003844D7 PSPlayerAllStats::rva00389DF1() const { return m_openPlayStats; }
Rva0038454E PSPlayerAllStats::rva00389E0F() const { return m_strategicStats; }
Rva00385333 PSPlayerAllStats::rva00556508() const { return m_tournamentStats; }

// Native [55621F,55628F),112B builds each stats block from id0 in member
// order, resets the record through552CB8, then stores the id in the blocks'
// +0x150 slots from last to first before the record's own +0.
PSPlayerAllStats::PSPlayerAllStats(Int id)
	: m_tournamentStats(0), m_openPlayStats(0), m_strategicStats(0)
{
	rva00552CB8();
	m_strategicStats.m_id = id;
	m_openPlayStats.m_id = id;
	m_tournamentStats.m_id = id;
	m_id = id;
}

// The 0x598-byte request record that connectCallback38B9F8 fills for the
// stats thread queue (E05FC8 slot4) and destroys through pinned38A1F2. Its
// copy constructor556375 and deque rows establish the members; BFME1's
// PSRequest is the donor lead for the request type at +0, the strings
// (+0x550 cdkey, +0x55C nick, +0x568 password, +0x574 email, +0x58C results)
// and the flags/house fields at +0x580..+0x584. The dword at +4 is a BFME2
// addition the constructor defaults to 3.
struct BfmeOpaqueOwnedRecord1432
{
	BfmeOpaqueOwnedRecord1432();
	~BfmeOpaqueOwnedRecord1432();
	BfmeOpaqueOwnedRecord1432 &operator=(const BfmeOpaqueOwnedRecord1432 &that);
	Int requestType;
	Int m_04;
	PSPlayerAllStats player;
	Rva00385333String cdkey;
	Rva00385333String nick;
	Rva00385333String password;
	Rva00385333String email;
	bool addDiscon;
	bool addDesync;
	Int lastHouse;
	Int m_588;
	Rva00385333String results;
};
typedef char RequestRecordSizeCheck[sizeof(BfmeOpaqueOwnedRecord1432) == 0x598 ? 1 : -1];

// Native [556523,5565C5),162B.
BfmeOpaqueOwnedRecord1432::BfmeOpaqueOwnedRecord1432() : player(0)
{
	player.rva00552CB8();
	requestType = 0;
	addDiscon = addDesync = false;
	lastHouse = -1;
	m_04 = 3;
}

// ??4BfmeOpaqueOwnedRecord1432@@QAEAAU0@ABU0@@Z @0x005565C5 175B: memberwise
// copy in declaration order; the queue's request pop (0x00557D98) is its only
// caller, as ZH's getRequest assigns the front PSRequest.
BfmeOpaqueOwnedRecord1432 &BfmeOpaqueOwnedRecord1432::operator=(const BfmeOpaqueOwnedRecord1432 &that)
{
	requestType = that.requestType;
	m_04 = that.m_04;
	player = that.player;
	cdkey.assign(that.cdkey);
	nick.assign(that.nick);
	password.assign(that.password);
	email.assign(that.email);
	addDiscon = that.addDiscon;
	addDesync = that.addDesync;
	lastHouse = that.lastHouse;
	m_588 = that.m_588;
	results.assign(that.results);
	return *this;
}

// Native queue methods555BD5/555C76 lock mutex04 and query the int-key map90.
// BFME1 findPlayerStatsByID is the semantic guide; receiver name is unproved.
class Rva00555BD5StatsQueue {
public:
    Rva003844D7 rva00555BD5(int id);
    Rva0038454E rva00555C76(int id);
    Rva00385333 rva00556730(int id);
    PSPlayerAllStats rva00556674(int id);
private:
    unsigned m_00;
    MutexClass m_mutex04;
    unsigned char m_pad0c[0x90-0x0c];
    _STL::map<int, PSPlayerAllStats> m_playerStats;
};
Rva003844D7 Rva00555BD5StatsQueue::rva00555BD5(int id) {
    MutexClass::LockClass lock(m_mutex04);
    _STL::map<int, PSPlayerAllStats>::iterator it=m_playerStats.find(id);
    if (it._M_node != m_playerStats.end()._M_node)
        return it->second.rva00389DF1();
    Rva003844D7 empty(0);
    return empty;
}
Rva0038454E Rva00555BD5StatsQueue::rva00555C76(int id) {
    MutexClass::LockClass lock(m_mutex04);
    _STL::map<int, PSPlayerAllStats>::iterator it=m_playerStats.find(id);
    if (it._M_node != m_playerStats.end()._M_node)
        return it->second.rva00389E0F();
    Rva0038454E empty(0);
    return empty;
}
Rva00385333 Rva00555BD5StatsQueue::rva00556730(int id) {
    MutexClass::LockClass lock(m_mutex04);
    _STL::map<int, PSPlayerAllStats>::iterator it=m_playerStats.find(id);
    if (it._M_node != m_playerStats.end()._M_node)
        return it->second.rva00556508();
    Rva00385333 empty(0);
    return empty;
}

// Native [556674,556730),188B is vtable slot 12 beside the three block
// getters: ZH's findPlayerStatsByID shape, returning the whole record and an
// id-0 record on a miss.
PSPlayerAllStats Rva00555BD5StatsQueue::rva00556674(int id) {
    MutexClass::LockClass lock(m_mutex04);
    _STL::map<int, PSPlayerAllStats>::iterator it=m_playerStats.find(id);
    if (it._M_node != m_playerStats.end()._M_node)
        return it->second;
    PSPlayerAllStats empty(0);
    empty.setID(0);
    return empty;
}

// The 0x580-byte response record the stats thread posts through the queue's
// addResponse (E05FC8 slot6). Its implicit destructor 0x00555ADF destroys only
// the +8 PSPlayerAllStats; BFME1's PSResponse is the donor lead for the type at
// +0 and the preorder flag at +0x57C.
struct BfmeOpaqueOwnedRecord1408
{
	BfmeOpaqueOwnedRecord1408() : player(0) {}
	Int responseType;
	Int m_04;
	PSPlayerAllStats player;
	unsigned int m_550[11];
	bool preorder;
	bool m_57D;
};
typedef char ResponseRecordSizeCheck[sizeof(BfmeOpaqueOwnedRecord1408) == 0x580 ? 1 : -1];

class GameSpyPSMessageQueueInterface
{
public:
	virtual ~GameSpyPSMessageQueueInterface();
	virtual void startThread() = 0;
	virtual void endThread() = 0;
	virtual bool isThreadRunning() = 0;
	virtual void addRequest(const BfmeOpaqueOwnedRecord1432 &req) = 0;
	virtual bool getRequest(BfmeOpaqueOwnedRecord1432 &req) = 0;
	virtual void addResponse(const BfmeOpaqueOwnedRecord1408 &resp) = 0;
};
extern GameSpyPSMessageQueueInterface *TheGameSpyPSMessageQueue;	// 0x00E05FC8

// The stats thread keeps its outstanding GameSpy operation count at +0x54.
class PSThreadClass
{
public:
	void decrOpCount() { --m_opCount; }
private:
	unsigned char m_pad00[0x54];
	Int m_opCount;
};

typedef enum { pd_private_ro, pd_private_rw, pd_public_ro, pd_public_rw } persisttype_t;

// Native [5567E2,55686A),136B: ZH getPreorderCallback with the newer SDK's
// modified-time argument; response type 2 is PSRESPONSE_PREORDER.
void getPreorderCallback(int localid, int profileid, persisttype_t type, int index, int success, time_t modified, char *data, int len, void *instance)
{
	PSThreadClass *t = (PSThreadClass *)instance;
	if (!t)
		return;

	t->decrOpCount();

	BfmeOpaqueOwnedRecord1408 resp;

	if (!success)
		return;

	resp.responseType = 2;
	resp.preorder = (data && strcmp(data, "\\preorder\\1") == 0);
	TheGameSpyPSMessageQueue->addResponse(resp);
}

// The save-side Xfer: constructor 0x0060D1F7, open 0x0060D10A, close
// 0x0060C8CD and virtual destructor 0x0060D0B3; 0x40 bytes on the frame.
class Xfer;
class XferSave : public XferStub
{
public:
	XferSave();
	virtual ~XferSave();
	unsigned char Open(Xfer *stream, int arg2, bool arg3);
	void close();
private:
	unsigned char m_pad04[0x3C];
};

// The named memory stream XferSave writes into: made by 0x006023C1 and
// drained by 0x006021A4, which hands back its buffer and length.
class BfmeMade_009CB5F0;
BfmeMade_009CB5F0 *bfmeMake_009CB5F0(void *owner);
class BfmeThingEC
{
public:
	int bfmeTakeEC(int *out);
};

// Native [55686A,556982),280B with its catch funclet at 0x556957. Serializes
// the tournament, open-play and strategic blocks into a "playerStats" stream
// and returns its buffer and length; the stats thread hands both to
// SetPersistData (index 1) and frees the buffer. A failed open yields none.
char *rva0055686A(const PSPlayerAllStats *stats, int *len)
{
	BfmeMade_009CB5F0 *stream = bfmeMake_009CB5F0((void *)"playerStats");
	if (!stream)
	{
		*len = 0;
		return 0;
	}

	XferSave xfer;
	try
	{
		xfer.Open((Xfer *)stream, 1, false);
	}
	catch (...)
	{
		*len = 0;
		return 0;
	}

	stats->rva00556508().rva005550A0(&xfer);
	stats->rva00389DF1().rva005550A0(&xfer);
	stats->rva00389E0F().rva005550A0(&xfer);
	xfer.close();
	return (char *)((BfmeThingEC *)stream)->bfmeTakeEC(len);
}

// Native [556B3C,556C54),280B with its catch funclet at 0x556C29: the same
// "playerStats" serializer through each block's second xfer slot, whose
// buffer the stats thread (0x005589AE) stores at SetPersistData index 2.
char *rva00556B3C(const PSPlayerAllStats *stats, int *len)
{
	BfmeMade_009CB5F0 *stream = bfmeMake_009CB5F0((void *)"playerStats");
	if (!stream)
	{
		*len = 0;
		return 0;
	}

	XferSave xfer;
	try
	{
		xfer.Open((Xfer *)stream, 1, false);
	}
	catch (...)
	{
		*len = 0;
		return 0;
	}

	stats->rva00556508().rva00555109(&xfer);
	stats->rva00389DF1().rva00555109(&xfer);
	stats->rva00389E0F().rva00555109(&xfer);
	xfer.close();
	return (char *)((BfmeThingEC *)stream)->bfmeTakeEC(len);
}

// The load-side Xfer: built from three null pointers by 0x0060C5FA, opened
// on a stream by 0x0060C3C3, cleared by 0x0060C45E and torn down through the
// base destructor 0x004053E7; 0x20 bytes on the frame.
class Xfer : public XferStub
{
public:
	virtual ~Xfer();
};
class Rva0060C5FA : public Xfer
{
public:
	Rva0060C5FA(void *a1, void *a2, void *a3);
private:
	unsigned char m_pad04[0x20 - 4];
};
struct Rva0060C3C3Stream;
class XferLoad
{
public:
	bool Open(Rva0060C3C3Stream *stream, Int *version);
};
class Rva0060C45E
{
public:
	void clear();
};
class File
{
public:
	virtual ~File();
	virtual bool open(const char *filename, Int access);
	virtual void close();
};
File *createMemoryReadFile(char *data, Int size);

// Native [556982,556B3C),442B with its catch funclet at 0x556B1E. Reads the
// tournament, open-play and strategic blocks back from a persist-data buffer
// into the player's stats, then copies the open-play +0x144 short into every
// block; an empty buffer, a failed open or a throw resets the stats instead.
void rva00556982(char *data, int len, PSPlayerAllStats *stats)
{
	File *file = createMemoryReadFile(data, len);
	if (!file)
	{
		stats->rva00552CB8();
		return;
	}

	Rva0060C5FA xfer(0, 0, 0);
	Int version = 1;
	try
	{
		if (((XferLoad *)&xfer)->Open((Rva0060C3C3Stream *)file, &version))
		{
			Rva00385333 tournament = stats->rva00556508();
			Rva003844D7 openPlay = stats->rva00389DF1();
			Rva0038454E strategic = stats->rva00389E0F();
			tournament.rva00555DDC(&xfer);
			openPlay.rva005550A0(&xfer);
			strategic.rva005550A0(&xfer);
			stats->setTournamentStats(tournament);
			stats->setOpenPlayStats(openPlay);
			stats->setStrategicStats(strategic);
			stats->rva00552E9E(openPlay.getField144());
		}
		else
			stats->rva00552CB8();
	}
	catch (...)
	{
		((Rva0060C45E *)&xfer)->clear();
		file->close();
		stats->rva00552CB8();
		return;
	}
	((Rva0060C45E *)&xfer)->clear();
	file->close();
}
