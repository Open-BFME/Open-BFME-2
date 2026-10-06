// cl: /DNDEBUG /MD
// ??1Rva004962EA@@QAE@XZ 0x004962EA 30B vector teardown via destroy range and free no EH
// Evidence: calls 0x00496292 destroy and _free at 0x00030830; members at +0 and +4; caller at 0x00496442.

extern "C" void __cdecl free(void *block);

struct BfmeStringRecord00426A5B {
	~BfmeStringRecord00426A5B();
	char m_pad[12];
};

void Rva00496292Destroy(void *first, void *last);

class Rva004962EA {
public:
	~Rva004962EA();
	BfmeStringRecord00426A5B *m_first;
	BfmeStringRecord00426A5B *m_last;
};

Rva004962EA::~Rva004962EA()
{
	Rva00496292Destroy(m_first, m_last);
	void *block = m_first;
	if (block) {
		free(block);
	}
}
