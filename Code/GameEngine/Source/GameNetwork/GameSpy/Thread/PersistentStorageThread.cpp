// cl: /O1 /EHsc /MD /arch:SSE
// PersistentStorageThread.cpp -- GameSpy persistent-stats members recovered
// from WorldBuilder leads (reverse/wb_name_leads.csv): WB's debug build names
// each function; retail supplies the bytes.

namespace _STL
{
template <class CharT> class char_traits;
template <class CharT> class allocator;
template <class CharT, class Traits, class Alloc> class basic_string
{
public:
	basic_string &operator=(const CharT *text);
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
    virtual void _unused2();
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
    virtual void _unused27();
    virtual void _unused28();
    virtual void _unused29();
    virtual void _slot78(int &);
    virtual void _unused31();
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
    void reset();
    void rva005550A0(XferStub *);
    void rva00555109(XferStub *);
private:
    unsigned m_unmodelled00;
    Rva0038201D m_maps04[6];
    Rva0038201D m_maps4c[6];
    Rva0038201D m_maps94[6];
    Rva0038204A m_mapsdc[8];
    unsigned m_13c, m_140;
    unsigned short m_144, m_146, m_148, m_14a, m_14c;
    unsigned short m_unmodelled14e;
    unsigned m_id150;
};
typedef char StatsMapStrideCheck[sizeof(Rva0038201D) == 12 ? 1 : -1];
typedef char StatsCoreSizeCheck[sizeof(Rva00553E47StatsCore) == 0x154 ? 1 : -1];
void Rva00553E47StatsCore::reset() {
    m_id150 = 0;
    m_maps04[0].rva003828B6();
    m_maps04[1].rva003828B6();
    m_maps04[2].rva003828B6();
    m_maps04[3].rva003828B6();
    m_maps04[4].rva003828B6();
    m_maps04[5].rva003828B6();
    for (int i = 0; i < 6; ++i) {
        m_maps4c[i].rva003828B6();
        m_maps94[i].rva003828B6();
    }
    m_mapsdc[0].rva003828DF();
    m_mapsdc[1].rva003828DF();
    m_mapsdc[2].rva003828DF();
    m_mapsdc[3].rva003828DF();
    m_mapsdc[4].rva003828DF();
    m_mapsdc[5].rva003828DF();
    m_mapsdc[6].rva003828DF();
    m_mapsdc[7].rva003828DF();
    m_13c = 0;
    m_140 = 0;
    m_144 = 0;
    m_146 = 0;
    m_148 = 0;
    m_14a = 0;
    m_14c = 0;
}


class Rva003844D7	// open-play stats block
{
public:
	~Rva003844D7();						// 0x003844D7
	Rva003844D7 &operator=(const Rva003844D7 &that);	// 0x003874F9

	unsigned char m_pad00[0x150];
	Int m_id;						// +0x150
	unsigned char m_pad154[0x190 - 0x154];
};

class Rva0038454E	// strategic stats block
{
public:
    void rva00553F2F();
	~Rva0038454E();						// 0x0038454E
	Rva0038454E &operator=(const Rva0038454E &that);	// 0x00387945

	unsigned char m_pad00[0x150];
	Int m_id;						// +0x150
	unsigned char m_pad154[0x208 - 0x154];
};

class Rva00385333	// tournament stats block
{
public:
	void rva00553FDD();
	void rva00555F68();
	~Rva00385333();						// 0x00385333
	Rva00385333 &operator=(const Rva00385333 &that);	// 0x00387A68

	unsigned char m_pad00[0x150];
	Int m_id;						// +0x150
	unsigned char m_pad154[0x190 - 0x154];
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
	rva00553FDD();
	m_190 &= 0;
	m_192 &= 0;
	m_194 |= -1;
	m_198 |= -1;
	((Rva00385333String *)m_pad19C)->operator=(g_Rva0107301CEmptyString);
}

void Rva00385333::rva00553FDD() {
    ((Rva00553E47StatsCore *)this)->reset();
    ((Rva00382077 *)(m_pad154))->rva00382908();
    ((Rva0038201D *)(m_pad154 + 12))->rva003828B6();
    ((Rva0038201D *)(m_pad154 + 24))->rva003828B6();
    ((Rva0038204A *)(m_pad154 + 36))->rva003828DF();
    ((Rva0038204A *)(m_pad154 + 48))->rva003828DF();
}

// [553F2F,553FDD),174B clears the same fifteen 12-byte map slots that
// the verified strategic-block assignment387945 and destructor38454E use.
// Eight maps, two of the other map ABI, then five maps; core reset is553E47.
void Rva0038454E::rva00553F2F() {
    ((Rva00553E47StatsCore *)this)->reset();
    ((Rva0038204A *)(m_pad154 + 0x0))->rva003828DF();
    ((Rva0038204A *)(m_pad154 + 0xc))->rva003828DF();
    ((Rva0038204A *)(m_pad154 + 0x18))->rva003828DF();
    ((Rva0038204A *)(m_pad154 + 0x24))->rva003828DF();
    ((Rva0038204A *)(m_pad154 + 0x30))->rva003828DF();
    ((Rva0038204A *)(m_pad154 + 0x3c))->rva003828DF();
    ((Rva0038204A *)(m_pad154 + 0x48))->rva003828DF();
    ((Rva0038204A *)(m_pad154 + 0x54))->rva003828DF();
    ((Rva0038201D *)(m_pad154 + 0x60))->rva003828B6();
    ((Rva0038201D *)(m_pad154 + 0x6c))->rva003828B6();
    ((Rva0038204A *)(m_pad154 + 0x78))->rva003828DF();
    ((Rva0038204A *)(m_pad154 + 0x84))->rva003828DF();
    ((Rva0038204A *)(m_pad154 + 0x90))->rva003828DF();
    ((Rva0038204A *)(m_pad154 + 0x9c))->rva003828DF();
    ((Rva0038204A *)(m_pad154 + 0xa8))->rva003828DF();
}

// Native [5550A0,555109),105B transfers two maps and three scalars from
// the same core reset at553E47. Every call is an existing provider or a
// native Xfer vtable slot; the original method name remains unresolved.
void Rva00553E47StatsCore::rva005550A0(XferStub *xfer) {
    StatsXferVersion version;
    version.first = 1;
    version.second = 1;
    xfer->_slot28(version);
    ((PSPlayerStats *)this)->XferMap((MapHolder *)&m_maps04[0], xfer);
    ((PSPlayerStats *)this)->XferMap((MapHolder *)&m_maps04[1], xfer);
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
    ((PSPlayerStats *)this)->XferMap((MapHolder *)&m_maps04[2], xfer);
    ((PSPlayerStats *)this)->XferMap((MapHolder *)&m_maps04[3], xfer);
    ((PSPlayerStats *)this)->XferMap((MapHolder *)&m_maps04[4], xfer);
    ((PSPlayerStats *)this)->XferMap((MapHolder *)&m_maps04[5], xfer);
    for (int i=0;i<6;++i) {
        ((PSPlayerStats *)this)->XferMap((MapHolder *)&m_maps4c[i], xfer);
        ((PSPlayerStats *)this)->XferMap((MapHolder *)&m_maps94[i], xfer);
    }
    ((PSPlayerStats *)this)->rva0055499A((MapFloatHolder *)&m_mapsdc[0], xfer);
    ((PSPlayerStats *)this)->rva0055499A((MapFloatHolder *)&m_mapsdc[1], xfer);
    ((PSPlayerStats *)this)->rva0055499A((MapFloatHolder *)&m_mapsdc[2], xfer);
    ((PSPlayerStats *)this)->rva0055499A((MapFloatHolder *)&m_mapsdc[3], xfer);
    ((PSPlayerStats *)this)->rva0055499A((MapFloatHolder *)&m_mapsdc[4], xfer);
    ((PSPlayerStats *)this)->rva0055499A((MapFloatHolder *)&m_mapsdc[5], xfer);
    ((PSPlayerStats *)this)->rva0055499A((MapFloatHolder *)&m_mapsdc[6], xfer);
    if (version.second >= 2)
        ((PSPlayerStats *)this)->rva0055499A((MapFloatHolder *)&m_mapsdc[7], xfer);
    xfer->_slot80((short &)m_146);
    xfer->_slot80((short &)m_148);
    xfer->_slot80((short &)m_14a);
    xfer->_slot80((short &)m_14c);
}
