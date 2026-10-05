// cl: /O2 /MD
//
// ??1Rva0070A840@@QAE@XZ @0x0070A840 (111B).
// Hash dtor over count at +0 and 8-byte entries at +4: for each entry whose
// AsciiString key hasData, null a non-null value slot then run EAStringC
// rva006D3C20 on the key (AptNativeHash precedent casts key to EAStringC),
// then freeBlock the array via g_pChainBlockAllocator and null it.
// Callees all rowed: hasData 0x006CD4A0, rva006D3C20 0x006D3C20,
// freeBlock 0x006DB270. Callers include Rva006D63C0 dtor 0x006D63E8.
// Prev/next AptNativeHashBFME2.cpp flags /O2 /MD. LINK BONUS names this exact mangling.
// class-gate: allow AsciiString TU-local 4-byte view with hasData only; shared header lacks hasData and retail calls the rowed out-of-line hasData at 0x006CD4A0.
class AsciiString
{
	void *m_data;
public:
	bool hasData() const;
};

class EAStringC
{
public:
	void rva006D3C20();
};

class Rva006DB270
{
public:
	void freeBlock(void *p, int size);
};

extern Rva006DB270 *g_pChainBlockAllocator;

struct Rva0070A840Entry
{
	AsciiString key;
	void *value;
};

class Rva0070A840
{
	int m_count;
	Rva0070A840Entry *m_data;
public:
	~Rva0070A840();
};

Rva0070A840::~Rva0070A840()
{
	if (m_data)
	{
		for (int i = 0; i < m_count; i++)
		{
			if (!m_data[i].key.hasData())
				continue;
			if (m_data[i].value != 0)
				m_data[i].value = 0;
			((EAStringC *)&m_data[i].key)->rva006D3C20();
		}
		g_pChainBlockAllocator->freeBlock(m_data, m_count * 8);
		m_data = 0;
	}
}
