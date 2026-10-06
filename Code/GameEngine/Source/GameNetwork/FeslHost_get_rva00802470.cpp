// flags: region default (reverse/retail_inventory/flag_regions.csv)
// Carried from the Open-BFME-1 donor at submodule revision 5cae4bdf
// (game/GameEngine/Source/GameNetwork/FeslHost_get_rva00801900.cpp). Target
// evidence: the two 59B host-key getters place uniquely in BFME2 .text at
// 0x0066DBC0 (donor b1 0x008018C0) and 0x0066E6B0 (donor b1 0x00802470); BFME1
// ICF-folded them. The class and method names are the carried donor names. The
// donor's third getter (b1 0x00801900, target 0x0066DC00) is already owned by
// FeslHost_get_rva00801900.cpp and is omitted here rather than duplicated.
// vtable 0x0112C4A8 slot 2 (Rva00802040Owner). Host-key lookup through
// matched ?rva007F76F0@Rva00802240Host@@QAEHPAURva007F76F0Vector@@PBD@Z.
// Slot 1 (0x008018C0) is the same lookup over the host's +0x2A8 key vector,
// and the vtable at 0x0112C55C carries a third copy over +0x2B8 (0x00802470).

struct Rva007F76F0Vector
{
	void *m_begin;
	int m_count;
};

class Rva00802240Host
{
public:
	int rva007F76F0(Rva007F76F0Vector *vector, const char *key);

	char m_pad[0x2A8];
	Rva007F76F0Vector m_firstVector;
	Rva007F76F0Vector m_vector;
	Rva007F76F0Vector m_thirdVector;
};

struct Rva00801900Entry
{
	int m_value;
	int m_pad;
};

class Rva00801900Get
{
public:
	int rva008018C0Get(const char *key);

private:
	char m_pad00[4];
	Rva00802240Host *m_host;
	char m_pad08[8];
	Rva00801900Entry *m_firstEntries;
	int m_firstCount;
	Rva00801900Entry *m_entries;
	int m_count;
};

class Rva00802470Get
{
public:
	int get(const char *key);

private:
	char m_pad00[4];
	Rva00802240Host *m_host;
	char m_pad08[0x18];
	Rva00801900Entry *m_entries;
	int m_count;
};

int Rva00801900Get::rva008018C0Get(const char *key)
{
	const char *k = key;
	Rva00802240Host *host = m_host;
	int index = host->rva007F76F0(&host->m_firstVector, k);
	if (index == -1)
		return 0;
	if (index >= m_firstCount)
	{
		volatile int *crash = 0;
		return *crash;
	}
	volatile Rva00801900Entry *entry = m_firstEntries + index;
	return entry->m_value;
}

int Rva00802470Get::get(const char *key)
{
	const char *k = key;
	Rva00802240Host *host = m_host;
	int index = host->rva007F76F0(&host->m_thirdVector, k);
	if (index == -1)
		return 0;
	if (index >= m_count)
	{
		volatile int *crash = 0;
		return *crash;
	}
	volatile Rva00801900Entry *entry = m_entries + index;
	return entry->m_value;
}
