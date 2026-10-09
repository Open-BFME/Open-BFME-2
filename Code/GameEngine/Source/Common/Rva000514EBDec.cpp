// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?notifyOf2DSampleCompletion@MilesAudioManager@@QAEXXZ @0x000514EB 16B
// Guarded decrement at +0x684. Evidence: __thiscall via ecx plus no
// stack args plus ret; lea plus test plus jbe plus dec plus store;
// WorldBuilder 0x00797440 names the method and m_numPlaying2DSamples;
// its guarded unsigned decrement at +0x684 agrees with the whole retail body.
class MilesAudioManager
{
public:
    void notifyOf2DSampleCompletion();
private:
    char m_pad[0x684];
    unsigned m_numPlaying2DSamples;
};

class Rva000514EB
{
public:
	void rva000514FB();

private:
	char m_pad[0x684];
	unsigned m_count684;
	unsigned m_count688; // +0x688
};

void MilesAudioManager::notifyOf2DSampleCompletion()
{
	unsigned *p = (unsigned *)((char *)this + 0x684);
	if (*p <= 0u)
		return;
	--(*p);
}

void Rva000514EB::rva000514FB()
{
	unsigned *p = (unsigned *)((char *)this + 0x688);
	if (*p <= 0u)
		return;
	--(*p);
}
