// cl: /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /arch:SSE
// PersistentStorageThread.cpp -- GameSpy persistent-stats members recovered
// from WorldBuilder leads (reverse/wb_name_leads.csv): WB's debug build names
// each function; retail supplies the bytes.

// Canonical one-pointer AsciiString temporary used by the native wire adapter.
#include "ascii_string.h"
// stlport
#include <cstdlib>
void Rva00030830FreeAllocation(void *);
// Retail map teardown uses the independently rowed game allocator, whose
// C++ call route retains the native unwind-state transition.
#define free Rva00030830FreeAllocation
#include <map>
#undef free
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
    void rva00555DDC(XferStub *);
	void rva00555F68();
	~Rva00385333();						// 0x00385333
	Rva00385333 &operator=(const Rva00385333 &that);	// 0x00387A68

	unsigned short m_190;
	unsigned short m_192;
	Int m_194;
	Int m_198;
	unsigned char m_pad19C[0x1a8 - 0x19c];
};

class PSPlayerAllStats
{
public:
	PSPlayerAllStats &operator=(const PSPlayerAllStats &that);
	void setOpenPlayStats(Rva003844D7 stats);
	void setStrategicStats(Rva0038454E stats);
	void setTournamentStats(Rva00385333 stats);

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
	((Rva00385333String *)m_pad19C)->operator=(g_Rva0107301CEmptyString);
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
        ((StringBase<char> *)&wireText)->set(*(const char **)m_pad19C);
        xfer->_slot6c(wireText);
    } else {
        xfer->_slot6c(wireText);
        ((Rva00385333String *)m_pad19C)->operator=(wireText.str());
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
