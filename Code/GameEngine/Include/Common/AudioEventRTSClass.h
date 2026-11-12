// AudioEventRTS: canonical declarations for the members 6 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_AUDIOEVENTRTS_H
#define CANONICAL_AUDIOEVENTRTS_H

class AsciiString;

class AudioEventRTS
{
public:
	void generatePlayInfo();
	AsciiString getFilename();
	unsigned int getSoundClass() const;
	bool isPositionalAudio() const;
	void rva002D9ADC();
};

#endif // CANONICAL_AUDIOEVENTRTS_H
