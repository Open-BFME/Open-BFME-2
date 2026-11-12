// Registry constructor 0x003818F4 calls 0x00330757, which writes the final
// word at +0x0C. The globals in LivingWorldScoreKeeper occupy 16 bytes each.
#ifndef CANONICAL_RVA002B7250_H
#define CANONICAL_RVA002B7250_H

class CreateAHeroData;

class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *v);
private:
	char m_retailExtent[16];
};

#endif // CANONICAL_RVA002B7250_H
