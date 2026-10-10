// ?HandlePersistentStorageResponses@@YAXXZ
// partial score=0.99304531085353 date=2026-10-10
extern "C" unsigned __cdecl strlen(const char*);
#pragma intrinsic(strlen)
// ?HandlePersistentStorageResponses@@YAXXZ
// partial score=0.988 date=2026-10-09
// Full current-home C++ bank; pending body at the end. Existing home definitions are retained.
// cl: /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /arch:SSE
#include "ascii_string.h"
// stlport
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <ctime>
void Rva00030830FreeAllocation(void *);
#define free Rva00030830FreeAllocation
#include <map>
#undef free
#define _OPERATOR_NEW_DEFINED_
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
template<class CharT,class Alloc>class _String_base {
public:
 _String_base(const Alloc&):start(0),finish(0),storageEnd(0){}
 ~_String_base(){if(start)Rva00030830FreeAllocation(start);}
 CharT*start,*finish,*storageEnd;
};
template <class CharT,class Traits,class Alloc>class basic_string:public _String_base<CharT,Alloc> {
public:
 basic_string();
 inline __declspec(noinline) basic_string(const CharT*text,const Alloc&alloc=Alloc()):_String_base<CharT,Alloc>(alloc){_M_range_initialize(text,text+strlen(text));}
 ~basic_string(){}
 basic_string&operator=(const CharT*);
 basic_string&assign(const basic_string&);
 unsigned size()const{return finish-start;}
 template<class It>void _M_range_initialize(It,It);
};
}
typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> >
	Rva00385333String;
extern const char g_Rva0107301CEmptyString[];
typedef int Int;
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
    friend class Rva00559D0CRankWeights;
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
	Int getLocale() const { return m_locale; }
	void setID(Int id);
	friend void HandlePersistentStorageResponses();
	Int getID() const { return m_id; }
private:
	Int m_id;						// +0x000
	Int m_locale;					// +0x004 set by rva00552E9E, copied by operator= @0x003874B0
	Rva00385333 m_tournamentStats;				// +0x008
	Rva003844D7 m_openPlayStats;				// +0x1B0
	Rva0038454E m_strategicStats;				// +0x340
};
void PSPlayerAllStats::setID(Int id)
{
	m_strategicStats.m_id = id;
	m_openPlayStats.m_id = id;
	m_tournamentStats.m_id = id;
	m_id = id;
}
PSPlayerAllStats &PSPlayerAllStats::operator=(const PSPlayerAllStats &that)
{
	m_id = that.m_id;
	m_locale = that.m_locale;
	m_tournamentStats = that.m_tournamentStats;
	m_openPlayStats = that.m_openPlayStats;
	m_strategicStats = that.m_strategicStats;
	return *this;
}
void PSPlayerAllStats::setOpenPlayStats(Rva003844D7 stats)
{
	if (m_id == 0 || m_id == stats.m_id)
	{
		m_id = stats.m_id;
		m_openPlayStats = stats;
	}
}
void PSPlayerAllStats::setStrategicStats(Rva0038454E stats)
{
	if (m_id == 0 || m_id == stats.m_id)
	{
		m_id = stats.m_id;
		m_strategicStats = stats;
	}
}
void PSPlayerAllStats::setTournamentStats(Rva00385333 stats)
{
	if (m_id == 0 || m_id == stats.m_id)
	{
		m_id = stats.m_id;
		m_tournamentStats = stats;
	}
}
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
void Rva0038454E::rva00555109(XferStub *xfer) {
    ((Rva00553E47StatsCore *)this)->Rva00553E47StatsCore::rva00555109(xfer);
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
void Rva003844D7::rva00555109(XferStub *xfer) {
    ((Rva00553E47StatsCore *)this)->Rva00553E47StatsCore::rva00555109(xfer);
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
void Rva00385333::rva00555DDC(XferStub *xfer) {
    ((Rva00553E47StatsCore *)this)->Rva00553E47StatsCore::rva005550A0(xfer);
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
Rva00553E47StatsCore::Rva00553E47StatsCore(const Rva00553E47StatsCore &source) {
    reset();
    rva00554AF2(&source);
}
struct StatsSystemTime {
    unsigned short year, month, dayOfWeek, day, hour, minute, second, milliseconds;
};
extern "C" __declspec(dllimport) void __stdcall GetLocalTime(StatsSystemTime *);
Rva00553E47StatsCore::Rva00553E47StatsCore(int id) {
    reset();
    m_id=id;
    StatsSystemTime localTime;
    GetLocalTime(&localTime);
}
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
Rva00385333::Rva00385333(int id) : Rva003844D7(0) {
    rva00555F68();
    m_id = id;
}
Rva00385333::Rva00385333(const Rva00385333 &source) : Rva003844D7(0) {
    rva00555F68();
    ((Rva00555D74 *)this)->rva00555D74((const Rva00555D74 *)&source);
}
Rva003844D7 PSPlayerAllStats::rva00389DF1() const { return m_openPlayStats; }
Rva0038454E PSPlayerAllStats::rva00389E0F() const { return m_strategicStats; }
Rva00385333 PSPlayerAllStats::rva00556508() const { return m_tournamentStats; }
PSPlayerAllStats::PSPlayerAllStats(Int id)
	: m_tournamentStats(0), m_openPlayStats(0), m_strategicStats(0)
{
	rva00552CB8();
	m_strategicStats.m_id = id;
	m_openPlayStats.m_id = id;
	m_tournamentStats.m_id = id;
	m_id = id;
}
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
BfmeOpaqueOwnedRecord1432::BfmeOpaqueOwnedRecord1432() : player(0)
{
	player.rva00552CB8();
	requestType = 0;
	addDiscon = addDesync = false;
	lastHouse = -1;
	m_04 = 3;
}
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
PSPlayerAllStats Rva00555BD5StatsQueue::rva00556674(int id) {
    MutexClass::LockClass lock(m_mutex04);
    _STL::map<int, PSPlayerAllStats>::iterator it=m_playerStats.find(id);
    if (it._M_node != m_playerStats.end()._M_node)
        return it->second;
    PSPlayerAllStats empty(0);
    empty.setID(0);
    return empty;
}
struct Rva00552F2E;
struct BfmeOpaqueOwnedRecord1408
{
	BfmeOpaqueOwnedRecord1408() : player(0) {}
	Int responseType;
	Int m_04;
	PSPlayerAllStats player;
	Int m_550;
	Int m_554;
	Int m_558;
	Int m_55C;
	Int m_560;
	Rva00552F2E *m_564[6];
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
	virtual bool getResponse(BfmeOpaqueOwnedRecord1408 &resp);
	virtual void trackPlayerStats(PSPlayerAllStats stats);
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual PSPlayerAllStats findPlayerStatsByID(Int id);
	virtual Rva00385333 slot13(Int id);
};
extern GameSpyPSMessageQueueInterface *TheGameSpyPSMessageQueue;	// 0x00E05FC8
struct Rva00557996Request;
class PSThreadClass : public ThreadClass
{
public:
	virtual ~PSThreadClass();
	void persAuthCallback(bool val) { m_loginOK = val; m_doneTryingToLogin = true; }
	void decrOpCount() { --m_opCount; }
	Int getOpCount() const { return m_opCount; }
	bool sawLocalPlayerData() const { return m_sawLocalPlayerData; }
protected:
	virtual void Thread_Function();
private:
	bool tryConnect();
	bool tryLogin(Int id, Rva00385333String nick, Rva00385333String password, Rva00385333String email);
	bool m_loginOK;
	bool m_doneTryingToLogin;
	Int m_opCount;
	bool m_sawLocalPlayerData;
	_STL::map<int, Rva00557996Request *> m_requests;
	void *m_owner;
};
typedef enum { pd_private_ro, pd_private_rw, pd_public_ro, pd_public_rw } persisttype_t;
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
class BfmeMade_009CB5F0;
BfmeMade_009CB5F0 *bfmeMake_009CB5F0(void *owner);
class BfmeThingEC
{
public:
	int bfmeTakeEC(int *out);
};
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
void rva00556C54(char *data, int len, PSPlayerAllStats *stats)
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
			tournament.rva00555109(&xfer);
			openPlay.rva00555109(&xfer);
			strategic.rva00555109(&xfer);
			stats->setTournamentStats(tournament);
			stats->setOpenPlayStats(openPlay);
			stats->setStrategicStats(strategic);
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
class UserPreferences
{
public:
	virtual ~UserPreferences();
	virtual bool write(void);
private:
	unsigned char m_pad04[0x10];
};
class GameSpyMiscPreferences : public UserPreferences
{
public:
	GameSpyMiscPreferences();
	virtual ~GameSpyMiscPreferences();
	int rva00559782();
	void rva0055986F(AsciiString val);
	void rva00559924(AsciiString val);
	AsciiString rva00559813();
	AsciiString rva005598C8();
};
static bool rva0055325C(const AsciiString &text, char *out, unsigned int outLen)
{
	const char *s = text.str();
	int len = text.getLength();
	if (s)
	{
		unsigned int o = 0;
		for (int i = 0; i < len; ++i)
		{
			char hi;
			if (s[i] >= 'a' && s[i] <= 'f')
				hi = (s[i] - 'a' + 10) * 16;
			else if (s[i] >= '0' && s[i] <= '9')
				hi = (s[i] - '0') * 16;
			else
				return false;
			++i;
			char lo;
			if (s[i] >= 'a' && s[i] <= 'f')
				lo = s[i] - 'a' + 10;
			else if (s[i] >= '0' && s[i] <= '9')
				lo = s[i] - '0';
			else
				return false;
			if (outLen >= o)
				out[o++] = hi | lo;
		}
		return true;
	}
	return false;
}
PSPlayerAllStats rva00556DFF()
{
	PSPlayerAllStats stats(0);
	GameSpyMiscPreferences prefs;
	AsciiString first = prefs.rva00559813();
	AsciiString second = prefs.rva005598C8();
	if (first.getLength() % 2)
		return stats;
	int len = first.getLength() / 2;
	if (len)
	{
		char *buf = new char[len];
		if (buf && rva0055325C(first, buf, len))
		{
			rva00556982(buf, len, &stats);
			delete[] buf;
		}
	}
	if (second.getLength() % 2)
		return stats;
	len = second.getLength() / 2;
	if (len)
	{
		char *buf = new char[len];
		if (buf && rva0055325C(second, buf, len))
		{
			rva00556C54(buf, len, &stats);
			delete[] buf;
		}
	}
	return stats;
}
extern const char g_cachedStatsHexDigits[16] = {
	'0', '1', '2', '3', '4', '5', '6', '7',
	'8', '9', 'a', 'b', 'c', 'd', 'e', 'f',
};
static bool rva00552EC0(const unsigned char *data, AsciiString &out, unsigned int len)
{
	unsigned int size = len * 2 + 1;
	char *buf = new char[size];
	if (buf)
	{
		memset(buf, ' ', size);
		buf[size - 1] = 0;
		for (unsigned int i = 0; i < len; ++i)
		{
			unsigned char b = data[i];
			char lo = g_cachedStatsHexDigits[b & 0xf];
			char hi = g_cachedStatsHexDigits[b >> 4];
			buf[i * 2] = hi;
			buf[i * 2 + 1] = lo;
		}
		out.format(buf);
		delete[] buf;
		return true;
	}
	return false;
}
struct Gen_uw_00385371;
void Rva00556FB8(const Gen_uw_00385371 &statsRef)
{
	GameSpyMiscPreferences prefs;
	AsciiString first;
	AsciiString second;
	int len;
	char *data = rva0055686A((const PSPlayerAllStats *)&statsRef, &len);
	if (data)
	{
		if (rva00552EC0((const unsigned char *)data, first, len))
		{
			prefs.rva0055986F(first);
			prefs.write();
		}
		delete data;
	}
	data = rva00556B3C((const PSPlayerAllStats *)&statsRef, &len);
	if (data)
	{
		if (rva00552EC0((const unsigned char *)data, second, len))
		{
			prefs.rva00559924(second);
			prefs.write();
		}
		delete data;
	}
}
class Gen_00654130
{
public:
	void bfmeErase(void *key);
	unsigned char m_prefix[0x5c];
	_STL::map<int, int> m_values;
};
class Rva005571FC : public Gen_00654130
{
public:
	int rva005571FC(int a1, int a2, int a3, int a4, int a5);
};
int Rva005571FC::rva005571FC(int request, int result, int buffer, int, int)
{
	_STL::map<int, int>::iterator it = m_values.find(request);
	if (result != 0 || it._M_node == m_values.end()._M_node || it->second == 0)
	{
		bfmeErase((void *)request);
		return 1;
	}
	AsciiString text((const char *)buffer);
	text.trim();
	int value = atoi(text.str());
	if (value != -2)
	{
		int kind = ((int *)it->second)[1];
		if (kind == 1 || kind == 2)
		{
			BfmeOpaqueOwnedRecord1408 resp;
			resp.responseType = 4;
			resp.m_55C = value;
			resp.m_560 = kind;
			if (TheGameSpyPSMessageQueue)
				TheGameSpyPSMessageQueue->addResponse(resp);
		}
	}
	bfmeErase((void *)request);
	return 1;
}
class Rva00557304 : public Gen_00654130
{
public:
	int rva00557304(int a1, int a2, int a3, int a4, int a5);
};
int Rva00557304::rva00557304(int request, int result, int buffer, int, int)
{
	_STL::map<int, int>::iterator it = m_values.find(request);
	if (result != 0 || it._M_node == m_values.end()._M_node || it->second == 0)
	{
		bfmeErase((void *)request);
		return 1;
	}
	AsciiString text((const char *)buffer);
	text.trim();
	int value = atoi(text.str());
	if (value >= 0 && value <= 1)
	{
		BfmeOpaqueOwnedRecord1408 resp;
		resp.responseType = 6;
		resp.m_57D = value == 1;
		if (TheGameSpyPSMessageQueue)
			TheGameSpyPSMessageQueue->addResponse(resp);
	}
	bfmeErase((void *)request);
	return 1;
}
struct Rva00552F2E
{
	int a[4];
	int b[4];
	Rva00552F2E() throw();
};
class Rva005573FA : public Gen_00654130
{
public:
	int rva005573FA(int a1, int a2, int a3, int a4, int a5);
};
int Rva005573FA::rva005573FA(int request, int result, int buffer, int, int)
{
	_STL::map<int, int>::iterator it = m_values.find(request);
	if (result != 0 || it._M_node == m_values.end()._M_node || it->second == 0)
	{
		bfmeErase((void *)request);
		return 1;
	}
	Rva00552F2E *men = new Rva00552F2E;
	Rva00552F2E *elves = new Rva00552F2E;
	Rva00552F2E *dwarves = new Rva00552F2E;
	Rva00552F2E *isengard = new Rva00552F2E;
	Rva00552F2E *mordor = new Rva00552F2E;
	Rva00552F2E *goblins = new Rva00552F2E;
	AsciiString text((const char *)buffer);
	int period = 4;
	AsciiString line;
	Rva00552F2E *table = NULL;
	while (text.nextToken(&line, "\n"))
	{
		line.trim();
		line.toLower();
		if (strstr(line.str(), "today"))
			period = 0;
		else if (strstr(line.str(), "yesterday"))
			period = 1;
		else if (strstr(line.str(), "all time"))
			period = 2;
		else if (strstr(line.str(), "last week"))
			period = 3;
		else if (period != 4)
		{
			if (strstr(line.str(), "men"))
				table = men;
			else if (strstr(line.str(), "elves"))
				table = elves;
			else if (strstr(line.str(), "dwarves"))
				table = dwarves;
			else if (strstr(line.str(), "isengard"))
				table = isengard;
			else if (strstr(line.str(), "mordor"))
				table = mordor;
			else if (strstr(line.str(), "goblins"))
				table = goblins;
		}
		if (table)
		{
			AsciiString field1;
			AsciiString field2;
			AsciiString field3;
			text.nextToken(&field1, "\n");
			text.nextToken(&field2, "\n");
			text.nextToken(&field3, "\n");
			while (!field1.isEmpty() && !isdigit(field1.str()[0]))
				field1.set(field1.str() + 1);
			while (!field2.isEmpty() && !isdigit(field2.str()[0]))
				field2.set(field2.str() + 1);
			while (!field3.isEmpty() && !isdigit(field3.str()[0]))
				field3.set(field3.str() + 1);
			if (!field1.isEmpty() && !field2.isEmpty() && !field3.isEmpty())
			{
				table->a[period] = atoi(field2.str());
				table->b[period] = atoi(field3.str());
			}
			table = NULL;
		}
	}
	BfmeOpaqueOwnedRecord1408 resp;
	resp.responseType = 5;
	resp.m_564[0] = men;
	resp.m_564[1] = elves;
	resp.m_564[2] = dwarves;
	resp.m_564[3] = isengard;
	resp.m_564[4] = mordor;
	resp.m_564[5] = goblins;
	if (TheGameSpyPSMessageQueue)
	{
		TheGameSpyPSMessageQueue->addResponse(resp);
	}
	else
	{
		delete men;
		delete elves;
		delete dwarves;
		delete isengard;
		delete mordor;
		delete goblins;
	}
	bfmeErase((void *)request);
	return 1;
}
extern "C" int ghttpGetA(const char *url, int blocking, int (__cdecl *callback)(int, int, int, int, int, void *), void *param);
int __cdecl rva00557902(int a1, int a2, int a3, int a4, int a5, void *context);
int __cdecl rva00557927(int a1, int a2, int a3, int a4, int a5, void *context);
struct Rva00557996Request
{
	Gen_00654130 *owner;
	int ladder;
	int profileID;
};
class Rva00557996 : public Gen_00654130
{
public:
	void rva00557996(int ladder);
	void rva00557A33(int profileID);
};
void Rva00557996::rva00557996(int ladder)
{
	AsciiString url;
	if (ladder == 1)
		url.format("http://lotrebfme2.arenasdk.gamespy.com/ladderstats.sdk?ladderid=35030&action=COUNT", ladder);
	else
		url.format("http://lotrebfme2.arenasdk.gamespy.com/ladderstats.sdk?ladderid=35033&action=COUNT", 2);
	int request = ghttpGetA(url.str(), 0, rva00557902, this);
	if (request)
	{
		Rva00557996Request *data = new Rva00557996Request;
		data->owner = this;
		data->ladder = ladder;
		m_values[request] = (int)data;
	}
}
void Rva00557996::rva00557A33(int profileID)
{
	AsciiString url;
	url.format("http://lotrebfme2.arenasdk.gamespy.com/ladderrank.sdk?ladderid=35030,35033&profileid=%d", profileID);
	int request = ghttpGetA(url.str(), 0, rva00557927, this);
	if (request)
	{
		Rva00557996Request *data = new Rva00557996Request;
		data->owner = this;
		data->profileID = profileID;
		m_values[request] = (int)data;
	}
}
class GameSpyPSMessageQueue : public GameSpyPSMessageQueueInterface
{
public:
	Int getLocalPlayerID() const { return m_localPlayerID; }
private:
	unsigned char m_pad04[0x64];
	Int m_localPlayerID;
};
#define MESSAGE_QUEUE ((GameSpyPSMessageQueue *)TheGameSpyPSMessageQueue)
class Rva00555A8BNarrowField
{
public:
	Rva00385333String get() const;
};
class Rva00555AA6NarrowField
{
public:
	Rva00385333String get() const;
};
class Rva00555AC1NarrowField
{
public:
	Rva00385333String get() const;
};
void rva00556982(char *data, int len, PSPlayerAllStats *stats);
void rva00556C54(char *data, int len, PSPlayerAllStats *stats);
void getPersistentDataCallback(int localid, int profileid, persisttype_t type, int index, int success, time_t modified, char *data, int len, void *instance)
{
	PSThreadClass *t = (PSThreadClass *)instance;
	if (!t)
		return;
	t->decrOpCount();
	BfmeOpaqueOwnedRecord1408 resp;
	if (!success)
	{
		resp.responseType = 1;
		resp.player.setID(profileid);
		TheGameSpyPSMessageQueue->addResponse(resp);
		if (!t->getOpCount() && !t->sawLocalPlayerData())
		{
			BfmeOpaqueOwnedRecord1432 req;
			req.requestType = 0;
			req.m_04 = index;
			req.player.setID(MESSAGE_QUEUE->getLocalPlayerID());
			TheGameSpyPSMessageQueue->addRequest(req);
		}
		return;
	}
	resp.responseType = 0;
	if (index == 1)
	{
		if (len > 0)
			rva00556982(data, len, &resp.player);
		if (profileid == MESSAGE_QUEUE->getLocalPlayerID())
		{
			GameSpyMiscPreferences pref;
			if (pref.rva00559782() != resp.player.getLocale())
			{
				resp.player.rva00552E9E(pref.rva00559782());
				BfmeOpaqueOwnedRecord1432 req;
				req.requestType = 1;
				req.email.assign(((const Rva00555A8BNarrowField *)TheGameSpyPSMessageQueue)->get());
				req.nick.assign(((const Rva00555AA6NarrowField *)TheGameSpyPSMessageQueue)->get());
				req.password.assign(((const Rva00555AC1NarrowField *)TheGameSpyPSMessageQueue)->get());
				req.m_04 = 1;
				req.addDesync = false;
				req.addDiscon = false;
				req.player = resp.player;
				req.player.setID(profileid);
				TheGameSpyPSMessageQueue->addRequest(req);
			}
		}
	}
	else if (index == 2)
	{
		if (len > 0)
			rva00556C54(data, len, &resp.player);
	}
	else
	{
		return;
	}
	resp.player.setID(profileid);
	resp.m_04 = index;
	TheGameSpyPSMessageQueue->addResponse(resp);
}
extern "C" void ghttpCleanup();
PSThreadClass::~PSThreadClass()
{
	for (_STL::map<int, Rva00557996Request *>::iterator it = m_requests.begin(); it != m_requests.end(); ++it)
	{
		if (it->second)
			delete it->second;
	}
	m_requests.clear();
	ghttpCleanup();
}
extern "C" int IsStatsConnected();
extern "C" int InitStatsConnection(int gameport);
extern "C" void PersistThink();
extern "C" char *GetChallenge(void *game);
extern "C" char *GenerateAuthA(char *challenge, char *password, char *response);
typedef void (*PersAuthCallbackFn)(int localid, int profileid, int authenticated, char *errmsg, void *instance);
extern "C" void PreAuthenticatePlayerPartner(int localid, const char *authtoken, const char *challengeresponse, PersAuthCallbackFn callback, void *instance);
bool PSThreadClass::tryConnect()
{
	if (IsStatsConnected())
		return true;
	int result = InitStatsConnection(0);
	if (result != 0)
		return false;
	return true;
}
void persAuthCallback(int localid, int profileid, int authenticated, char *errmsg, void *instance)
{
	PSThreadClass *t = (PSThreadClass *)instance;
	if (t)
		t->persAuthCallback(authenticated != 0);
}
void setPersistentDataLocaleCallback(int localid, int profileid, persisttype_t type, int index, int success, time_t modified, void *instance)
{
	PSThreadClass *t = (PSThreadClass *)instance;
	if (!t)
		return;
	t->decrOpCount();
}
struct CDAuthInfo
{
	bool success;
	bool done;
	Int id;
};
void preAuthCDCallback(int localid, int profileid, int authenticated, char *errmsg, void *instance)
{
	CDAuthInfo *authInfo = (CDAuthInfo *)instance;
	authInfo->success = authenticated != 0;
	authInfo->done = true;
	authInfo->id = profileid;
}
class GameSpyBuddyMessageQueueInterface
{
public:
	virtual ~GameSpyBuddyMessageQueueInterface();
	virtual void unknown04(); virtual void unknown08(); virtual void unknown0C();
	virtual void unknown10(); virtual void unknown14(); virtual void unknown18();
	virtual void unknown1C(); virtual void unknown20(); virtual void unknown24();
	virtual void unknown28();
	virtual const char *getReplyIdentityText();
	virtual const char *getAuthSecretText();
};
extern GameSpyBuddyMessageQueueInterface *TheGameSpyBuddyMessageQueue;
extern "C" char *strdup(const char *text);
bool PSThreadClass::tryLogin(Int id, Rva00385333String nick, Rva00385333String password, Rva00385333String email)
{
	char validate[33];
	m_loginOK = false;
	m_doneTryingToLogin = false;
	char *authToken = strdup(TheGameSpyBuddyMessageQueue->getReplyIdentityText());
	char *secret = strdup(TheGameSpyBuddyMessageQueue->getAuthSecretText());
	GenerateAuthA(GetChallenge(NULL), secret, validate);
	PreAuthenticatePlayerPartner(id, authToken, validate, ::persAuthCallback, this);
	Rva00030830FreeAllocation(authToken);
	Rva00030830FreeAllocation(secret);
	while (!m_doneTryingToLogin && IsStatsConnected())
		PersistThink();
	return m_loginOK;
}
void Rva005BD5F3Add()
{
	BfmeOpaqueOwnedRecord1432 req;
	req.requestType = 12;
	if (TheGameSpyPSMessageQueue != 0)
		TheGameSpyPSMessageQueue->addRequest(req);
}
void Rva005BD64DAdd()
{
	BfmeOpaqueOwnedRecord1432 req;
	req.requestType = 10;
	if (TheGameSpyPSMessageQueue != 0)
		TheGameSpyPSMessageQueue->addRequest(req);
}
#include "unicode_string.h"
class PlayerInfo
{
public:
	AsciiString m_name;
	AsciiString m_locale;
	AsciiString m_clan;
	Int m_wins;
	Int m_losses;
	Int m_profileID;
	Int m_flags;
	Int m_rankPoints;
	Int m_side;
	Int m_unk24;
	Int m_dc;
	Int m_desync;
	Int m_preorder;
	~PlayerInfo();
};
struct AsciiComparator
{
	bool operator()(AsciiString s1, AsciiString s2) const;
};
typedef _STL::map<AsciiString, PlayerInfo, AsciiComparator> PlayerInfoMap;
class GameSpyInfoInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual PlayerInfoMap *getPlayerInfoMap(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual Int getLocalProfileID(void);
	virtual AsciiString getLocalEmail(void);
	virtual void slot33(); virtual void slot34(); virtual void slot35(); virtual void slot36();
	virtual AsciiString getLocalBaseName(void);
	virtual void setCachedLocalPlayerStats(PSPlayerAllStats stats);
	virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51();
	virtual void slot52(); virtual void slot53(); virtual void slot54(); virtual void slot55();
	virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63();
	virtual void slot64(); virtual void slot65(); virtual void slot66(); virtual void slot67();
	virtual void slot68(); virtual void slot69(); virtual void slot70(); virtual void slot71();
	virtual void slot72(); virtual void slot73(); virtual void slot74(); virtual void slot75();
	virtual void slot76(); virtual void slot77(); virtual void slot78(); virtual void slot79();
	virtual void slot80(); virtual void slot81(); virtual void slot82(); virtual void slot83();
	virtual void slot84(); virtual void slot85(); virtual void slot86(); virtual void slot87();
	virtual void slot88(); virtual void slot89();
	virtual bool didPlayerPreorder(Int profileID) const;
	virtual void markPlayerAsPreorder(Int profileID);
};
extern GameSpyInfoInterface *TheGameSpyInfo;
extern int g_009C0758;
extern int g_009C075C;
void Rva005BD910Submit(Rva00385333 *stats)
{
	if (!TheGameSpyInfo || !TheGameSpyPSMessageQueue)
		return;
	Int low = (g_009C0758 > 0 && (stats->m_194 <= 0 || g_009C0758 < stats->m_194)) ? g_009C0758 : stats->m_194;
	Int high = (g_009C075C > 0 && (stats->m_198 <= 0 || g_009C075C < stats->m_198)) ? g_009C075C : stats->m_198;
	if (low == stats->m_194 && high == stats->m_198)
		return;
	stats->m_194 = low;
	stats->m_198 = high;
	PSPlayerAllStats player(0);
	player.setID(stats->m_id);
	player.setTournamentStats(*stats);
	BfmeOpaqueOwnedRecord1432 req;
	req.requestType = 11;
	req.email = TheGameSpyInfo->getLocalEmail().str();
	req.nick = TheGameSpyInfo->getLocalBaseName().str();
	req.password = g_Rva0107301CEmptyString;
	req.player = player;
	TheGameSpyPSMessageQueue->addRequest(req);
}
class Rva00559D0CRankWeights
{
public:
	Int rva00559D0C(const Rva00553E47StatsCore *stats) const;
private:
	unsigned char m_00[0x2C];
	float m_winWeight;
	float m_lossWeight;
};
Int Rva00559D0CRankWeights::rva00559D0C(const Rva00553E47StatsCore *stats) const
{
	if (stats->m_id == 0)
		return 0;
	Int wins = 0;
	StatsShortMap::const_iterator it;
	for (it = stats->m_maps04_0.begin(); it != stats->m_maps04_0.end(); ++it)
		wins += (unsigned short)it->second;
	Int winPoints = (Int)((float)wins * m_winWeight);
	Int losses = 0;
	for (it = stats->m_maps04_1.begin(); it != stats->m_maps04_1.end(); ++it)
		losses += (unsigned short)it->second;
	Int rank = (Int)((float)losses * m_lossWeight + (float)winPoints);
	return _STL::max(rank, 0);
}
extern unsigned int g_Va00E05FCC;
extern unsigned int g_Va00E06000;
struct BfmeOpaqueOwnedRecord492
{
	BfmeOpaqueOwnedRecord492();
	~BfmeOpaqueOwnedRecord492();
	Int requestType;
	unsigned char m_04[0x114];
	Int m_118;
	Int m_11c;
	unsigned char m_120[0xCC];
};
typedef char PeerRequestViewSizeCheck[sizeof(BfmeOpaqueOwnedRecord492) == 0x1EC ? 1 : -1];
class PeerResponse
{
public:
	PeerResponse();
	~PeerResponse();
	Int peerResponseType;
	Rva00385333String groupRoomName;
	Rva00385333String nick;
	Rva00385333String oldNick;
	unsigned char text[12];				// wide string
	Rva00385333String locale;
	Rva00385333String stagingServerGameOptions;
	unsigned char stagingServerName[12];	// wide string
	Rva00385333String stagingServerPingString;
	Rva00385333String stagingServerLadderIP;
	Rva00385333String stagingRoomMapName;
	Rva00385333String extraRoomString;
	Rva00385333String stagingRoomPlayerNames[8];
	Rva00385333String command;
	Rva00385333String commandOptions;
	unsigned char stringList[12];			// vector<AsciiString>
	Int words[143];
};
typedef char PeerResponseViewSizeCheck[sizeof(PeerResponse) == 0x348 ? 1 : -1];
class GameSpyPeerMessageQueueInterface
{
public:
	virtual ~GameSpyPeerMessageQueueInterface();
	virtual void startThread();
	virtual void endThread();
	virtual bool isThreadRunning();
	virtual bool isConnected();
	virtual bool isConnecting();
	virtual void addRequest(const BfmeOpaqueOwnedRecord492 &req);
	virtual bool getRequest(BfmeOpaqueOwnedRecord492 &req);
	virtual void addResponse(const PeerResponse &resp);
};
extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;
class GameTextInterface
{
public:
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
	virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
	virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
	virtual UnicodeString fetch(const char *label, bool *exists = 0);
};
extern GameTextInterface *TheGameText;
void GSMessageBoxOk(UnicodeString title, UnicodeString message, void (*okFunc)());
void Rva00548B97Free(int overlay);
bool SetUnsignedIntInRegistry(Rva00385333String path, Rva00385333String key, unsigned int val);
void Rva0043DB3DSet(unsigned char flag);
struct Rva005B9717Block;
void rva005B9717(const Rva005B9717Block *, const Rva005B9717Block *, const Rva005B9717Block *,
	const Rva005B9717Block *, const Rva005B9717Block *, const Rva005B9717Block *);
class GameSpyStagingRoomModeView
{
public:
	unsigned char m_00[0x5C];
	Int m_gameMode;
};
extern GameSpyStagingRoomModeView *TheGameSpyGame;
struct Rva0059EB6FModeHolder
{
	unsigned char m_00[0x7C];
	Int m_mode;
};
extern Rva0059EB6FModeHolder *g_Va00E0333C;
class Rva005537BA { public: unsigned short rva005537BA(); };
class Rva005537EB { public: unsigned short rva005537EB(); };
class Rva00553D26 { public: unsigned char rva00553D26(); };
Int g_psResponseKind1Value;
Int g_psResponseKind2Value;
// ?HandlePersistentStorageResponses@@YAXXZ present-unmatched
void HandlePersistentStorageResponses()
{
	if (TheGameSpyPSMessageQueue)
	{
	BfmeOpaqueOwnedRecord1408 resp;
	if (TheGameSpyPSMessageQueue->getResponse(resp))
	{
		switch (resp.responseType)
		{
		case 1:
			{
				GSMessageBoxOk(TheGameText->fetch("GUI:Error"), TheGameText->fetch("GUI:PSCannotConnect"), 0);
				Rva00548B97Free(0);
			}
			break;
		case 2:
			{
				if (resp.preorder)
				{
					SetUnsignedIntInRegistry("", "Preorder", 1);
					TheGameSpyInfo->markPlayerAsPreorder(TheGameSpyInfo->getLocalProfileID());
					BfmeOpaqueOwnedRecord1408 newResp;
					newResp.responseType = 0;
					newResp.player = TheGameSpyPSMessageQueue->findPlayerStatsByID(TheGameSpyInfo->getLocalProfileID());
					TheGameSpyPSMessageQueue->addResponse(newResp);
				}
			}
			break;
		case 3:
			{
				Rva00385333 tournament = TheGameSpyPSMessageQueue->slot13(resp.player.m_id);
				if (resp.m_550 == TheGameSpyInfo->getLocalProfileID())
				{
					g_009C0758 = resp.m_554;
					g_009C075C = resp.m_558;
					if (tournament.m_id)
						Rva005BD910Submit(&tournament);
					BfmeOpaqueOwnedRecord492 req;
					req.requestType = 0x19;
					req.m_118 = g_009C0758;
					req.m_11c = g_009C075C;
					TheGameSpyPeerMessageQueue->addRequest(req);
				}
				PlayerInfoMap::iterator it = TheGameSpyInfo->getPlayerInfoMap()->begin();
				while (it != TheGameSpyInfo->getPlayerInfoMap()->end())
				{
					PlayerInfo *info = &(it->second);
					if (info && info->m_profileID == resp.player.m_id)
					{
						info->m_side = g_009C0758;
						info->m_unk24 = g_009C075C;
						break;
					}
					++it;
				}
			}
			break;
		case 0:
			{
				TheGameSpyPSMessageQueue->trackPlayerStats(resp.player);
				PSPlayerAllStats stats = TheGameSpyPSMessageQueue->findPlayerStatsByID(resp.player.m_id);
				Rva0038454E strategic(0);
				Rva003844D7 openPlay(0);
				Rva00385333 tournament(0);
				strategic = stats.rva00389E0F();
				openPlay = stats.rva00389DF1();
				tournament = stats.rva00556508();
				Rva00553E47StatsCore *current = 0;
				if (g_Va00E0333C)
				{
					if (g_Va00E0333C->m_mode == 1)
						current = &strategic;
					else if (g_Va00E0333C->m_mode == 0)
						current = &openPlay;
				}
				if (resp.player.getID() == TheGameSpyInfo->getLocalProfileID() && resp.m_04 == 1)
				{
					BfmeOpaqueOwnedRecord492 req;
					req.requestType = 0x13;
					TheGameSpyPeerMessageQueue->addRequest(req);
					Rva005BD910Submit(&tournament);
				}
				if (stats.getID() == TheGameSpyInfo->getLocalProfileID())
					TheGameSpyInfo->setCachedLocalPlayerStats(stats);
				if (current)
				{
					PlayerInfoMap::iterator it = TheGameSpyInfo->getPlayerInfoMap()->begin();
					while (it != TheGameSpyInfo->getPlayerInfoMap()->end())
					{
						PlayerInfo *info = &(it->second);
						if (info && info->m_profileID == stats.m_id)
						{
							info->m_wins = ((Rva005537BA *)current)->rva005537BA();
							info->m_losses = ((Rva005537EB *)current)->rva005537EB();
							if (TheGameSpyGame->m_gameMode == 1)
								info->m_rankPoints = ((Rva00559D0CRankWeights *)&g_Va00E05FCC)->rva00559D0C(current);
							else if (TheGameSpyGame->m_gameMode == 0)
								info->m_rankPoints = ((Rva00559D0CRankWeights *)&g_Va00E06000)->rva00559D0C(current);
							info->m_desync = ((Rva00553D26 *)current)->rva00553D26();
							info->m_preorder = TheGameSpyInfo->didPlayerPreorder(info->m_profileID);
							PeerResponse presp;
							presp.peerResponseType = 13;
							presp.nick = info->m_name.str();
							presp.words[0] = info->m_profileID;
							presp.words[4] = info->m_flags;
							presp.words[1] = info->m_wins;
							presp.words[2] = info->m_losses;
							presp.locale = info->m_clan.str();
							presp.words[6] = info->m_rankPoints;
							presp.words[7] = info->m_desync;
							presp.words[8] = info->m_preorder;
							presp.words[140] = info->m_side;
							presp.words[141] = info->m_unk24;
							presp.words[142] = info->m_dc;
							TheGameSpyPeerMessageQueue->addResponse(presp);
							break;
						}
						++it;
					}
				}
			}
			break;
		case 4:
			if (resp.m_560 == 1)
				g_psResponseKind1Value = resp.m_55C;
			else if (resp.m_560 == 2)
				g_psResponseKind2Value = resp.m_55C;
			break;
		case 5:
			rva005B9717((const Rva005B9717Block *)resp.m_564[0], (const Rva005B9717Block *)resp.m_564[1],
				(const Rva005B9717Block *)resp.m_564[2], (const Rva005B9717Block *)resp.m_564[3],
				(const Rva005B9717Block *)resp.m_564[4], (const Rva005B9717Block *)resp.m_564[5]);
			delete resp.m_564[0];
			resp.m_564[0] = 0;
			delete resp.m_564[1];
			resp.m_564[1] = 0;
			delete resp.m_564[2];
			resp.m_564[2] = 0;
			delete resp.m_564[3];
			resp.m_564[3] = 0;
			delete resp.m_564[4];
			resp.m_564[4] = 0;
			delete resp.m_564[5];
			resp.m_564[5] = 0;
			break;
		case 6:
			Rva0043DB3DSet(resp.m_57D);
			break;
		}
	}
	}
}
