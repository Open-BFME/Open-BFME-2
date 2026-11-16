// AudioEventRTS: canonical declarations for the members units call through private views of it;
// each call resolves to the unit's ledger row or pin. Retail reads +0x08 and +0x0C as Zero Hour's
// m_eventInfo and m_playingHandle; the leading eight bytes and the tail stay opaque.
#ifndef CANONICAL_AUDIOEVENTRTS_H
#define CANONICAL_AUDIOEVENTRTS_H

class AsciiString;
struct AudioEventInfo;

class AudioEventRTS
{
public:
	void generatePlayInfo();
	AsciiString getFilename();
	unsigned int getSoundClass() const;
	bool isPositionalAudio() const;
	void rva002D9ADC();

	char m_pad00[8];
	const AudioEventInfo *m_eventInfo;
	int m_playingHandle;
};

#endif // CANONICAL_AUDIOEVENTRTS_H
