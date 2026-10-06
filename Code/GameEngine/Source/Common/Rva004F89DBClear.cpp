// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva004F89DB@Rva004F89DB@@QAEXXZ, retail 0x004F89DB, 30 bytes.
// Holder clear: destroy range [first,last) via rowed 0x004F8373 then free first via rowed free 0x00030830.
// Evidence: chain from 0x004F8373; callers 0x004F8B5C 0x004F8E93; prev vector dtor 0x004F8832 next vector clear 0x004F89F9 same shape.

struct Rva004F6986
{
	~Rva004F6986();
	char m_pad[8];
};

void __cdecl Rva004F8373Destroy(Rva004F6986 *first, Rva004F6986 *last);
extern "C" void __cdecl free(void *block);

class Rva004F89DB
{
public:
	void rva004F89DB();

private:
	Rva004F6986 *m_first;
	Rva004F6986 *m_last;
};

void Rva004F89DB::rva004F89DB()
{
	Rva004F8373Destroy(m_first, m_last);
	void *p = m_first;
	if (p)
		free(p);
}
