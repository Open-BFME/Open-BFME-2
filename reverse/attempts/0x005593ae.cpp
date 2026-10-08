// ?rva005593AE@Rva00555BD5StatsQueue@@QAEXVPSPlayerAllStats@@@Z
// partial score=0.96 date=2026-10-08
// cl: /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /arch:SSE
// PersistentStorageThread.cpp -- GameSpy persistent-stats members recovered
// from WorldBuilder leads (reverse/wb_name_leads.csv): WB's debug build names
// each function; retail supplies the bytes.

// Canonical one-pointer AsciiString temporary used by the native wire adapter.
#include "ascii_string.h"
// stlport
#include <cctype>
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
// BFME 2's WWLib thread base, not ZH's 0x58-byte one that mutex.h would pull
// in: one-argument constructor 0x00610430, virtual destructor 0x00610480 and
// a virtual Execute (vftable slot 1), 0x50 bytes.
#define THREAD_H
class ThreadClass
{
public:
	ThreadClass(const char *name);
	virtual ~ThreadClass();
	virtual void Execute();
protected:
	virtual void Thread_Function() = 0;
private:
	char m_name[0x40];
	unsigned int m_threadId;
	void *m_handle;
	int m_priority;
};
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
    // STLport's inline teardown under the game allocator: free the block when
    // one was allocated (retail inlines it for by-value string temporaries).
    ~basic_string() { if (start) Rva00030830FreeAllocation(start); }
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
    PSPlayerAllStats(Int id = 0);
    Int getID() const { return m_id; }
    void incorporate(const PSPlayerAllStats *stats);
    void rva00552CB8();
    void rva00552E9E(Int v);
    Rva003844D7 rva00389DF1() const;
    Rva0038454E rva00389E0F() const;
    Rva00385333 rva00556508() const;
	PSPlayerAllStats &operator=(const PSPlayerAllStats &that);
	void setOpenPlayStats(Rva003844D7 stats);
	void setStrategicStats(Rva0038454E stats);
	void setTournamentStats(Rva00385333 stats);
	Int getLocale() const { return m_locale; }
	void setID(Int id);

private:
	Int m_id;						// +0x000
	Int m_locale;					// +0x004 set by rva00552E9E, copied by operator= @0x003874B0
	Rva00385333 m_tournamentStats;				// +0x008
	Rva003844D7 m_openPlayStats;				// +0x1B0
	Rva0038454E m_strategicStats;				// +0x340
};

typedef _STL::map<int, PSPlayerAllStats> PlayerAllStatsMap;
template <> PSPlayerAllStats &PlayerAllStatsMap::operator[](const int &);

// Native queue methods555BD5/555C76 lock mutex04 and query the int-key map90.
// BFME1 findPlayerStatsByID is the semantic guide; receiver name is unproved.
class Rva00555BD5StatsQueue {
public:
    void rva005593AE(PSPlayerAllStats stats);
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
void Rva00555BD5StatsQueue::rva005593AE(PSPlayerAllStats stats) {
    MutexClass::LockClass lock(m_mutex04);
    PSPlayerAllStats newStats;
    PlayerAllStatsMap::iterator it = m_playerStats.find(stats.getID());
    if (it._M_node != m_playerStats.end()._M_node) {
        newStats = it->second;
        newStats.incorporate(&stats);
        m_playerStats[stats.getID()] = newStats;
    } else {
        m_playerStats[stats.getID()] = stats;
    }
}
