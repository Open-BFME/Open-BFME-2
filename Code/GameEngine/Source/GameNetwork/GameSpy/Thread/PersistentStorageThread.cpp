// cl: /O1 /EHsc /MD /arch:SSE
// PersistentStorageThread.cpp -- GameSpy persistent-stats members recovered
// from WorldBuilder leads (reverse/wb_name_leads.csv): WB's debug build names
// each function; retail supplies the bytes.
//
// PSPlayerAllStats keeps the player id at +0x00 and three stats blocks: the
// open-play block at +0x1B0 (0x190 bytes), the strategic block at +0x340
// (0x208 bytes) and the tournament block at +0x08 (0x1A8 bytes). Each block
// carries its player id at +0x150, is passed by value and is assigned with an
// out-of-line operator=; the blocks' destructors are rowed under the
// placeholder class names used here.

typedef int Int;

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
	~Rva0038454E();						// 0x0038454E
	Rva0038454E &operator=(const Rva0038454E &that);	// 0x00387945

	unsigned char m_pad00[0x150];
	Int m_id;						// +0x150
	unsigned char m_pad154[0x208 - 0x154];
};

class Rva00385333	// tournament stats block
{
public:
	~Rva00385333();						// 0x00385333
	Rva00385333 &operator=(const Rva00385333 &that);	// 0x00387A68

	unsigned char m_pad00[0x150];
	Int m_id;						// +0x150
	unsigned char m_pad154[0x1a8 - 0x154];
};

class PSPlayerAllStats
{
public:
	void setOpenPlayStats(Rva003844D7 stats);
	void setStrategicStats(Rva0038454E stats);
	void setTournamentStats(Rva00385333 stats);

private:
	Int m_id;						// +0x000
	unsigned char m_pad004[4];
	Rva00385333 m_tournamentStats;				// +0x008
	Rva003844D7 m_openPlayStats;				// +0x1B0
	Rva0038454E m_strategicStats;				// +0x340
};

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
