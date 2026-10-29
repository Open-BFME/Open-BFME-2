// cl: /Ireference/shims/bfme2_ascii /O1 /MD
// ?rva002D9893@Rva002D9893@@QAEXABV1@@Z @ 0x002D9893 336B
// Evidence: honest address Copy method void(const ref) ret 4 skips vptr; AsciiString +0x04 +0x1C +0x20 +0x84 via set; Opaque +0x08 via rowed assign; Pool10 +0x10 via rowed assign; 12B at +0x3C via struct assign for movsd x3; cond +0x34 if +0x38 in 1..5; landing unlocks 0x002D9A31 0x002D99E3; neighbours Rva002D9622Audio and tailrecord dtor.
#include "ascii_string.h"

struct OpaqueRefElement4
{
	void *m_ptr;
	OpaqueRefElement4 &operator=(const OpaqueRefElement4 &other);
};

class BfmePoolRef10
{
	void *m_target;

public:
	BfmePoolRef10 &operator=(const BfmePoolRef10 &other);
};

struct Twelve
{
	int a;
	int b;
	int c;
};

class Rva002D9893
{
	virtual ~Rva002D9893();

public:
	void rva002D9893(const Rva002D9893 &other);
	Rva002D9893 &operator=(const Rva002D9893 &other);

private:
	StringBase<char> m_filenameToLoad;
	OpaqueRefElement4 m_eventInfo;
	int m_playingHandle;
	BfmePoolRef10 m_10;
	int m_14;
	int m_18;
	StringBase<char> m_1C;
	StringBase<char> m_20;
	int m_24;
	int m_28;
	int m_2C;
	int m_30;
	int m_ownerID;
	int m_ownerType;
	Twelve m_positionOfAudio;
	unsigned char m_48;
	unsigned char m_49;
	unsigned char m_4A;
	unsigned char m_4B;
	unsigned char m_4C;
	unsigned char m_4D;
	unsigned char m_4E;
	unsigned char m_4F;
	unsigned char m_50;
	unsigned char m_51;
	unsigned char m_52;
	unsigned char m_53;
	int m_pitchShift;
	int m_58;
	int m_volumeShift;
	int m_60;
	int m_delay;
	int m_playingAudioIndex;
	int m_6C;
	int m_70;
	int m_portionToPlayNext;
	int m_78;
	int m_7C;
	int m_80;
	StringBase<char> m_84;
};

void Rva002D9893::rva002D9893(const Rva002D9893 &other)
{
	m_filenameToLoad.set(other.m_filenameToLoad);
	m_eventInfo = other.m_eventInfo;
	m_playingHandle = other.m_playingHandle;
	m_10 = other.m_10;
	m_14 = other.m_14;
	m_18 = other.m_18;
	m_24 = other.m_24;
	m_28 = other.m_28;
	m_2C = other.m_2C;
	m_ownerType = other.m_ownerType;
	m_30 = other.m_30;
	m_49 = other.m_49;
	m_pitchShift = other.m_pitchShift;
	m_58 = other.m_58;
	m_volumeShift = other.m_volumeShift;
	m_60 = other.m_60;
	m_playingAudioIndex = other.m_playingAudioIndex;
	m_6C = other.m_6C;
	m_delay = other.m_delay;
	m_1C.set(other.m_1C);
	m_20.set(other.m_20);
	m_portionToPlayNext = other.m_portionToPlayNext;
	m_4A = other.m_4A;
	m_4B = other.m_4B;
	m_4C = other.m_4C;
	m_4D = other.m_4D;
	m_4E = other.m_4E;
	m_4F = other.m_4F;
	m_50 = other.m_50;
	m_51 = other.m_51;
	m_52 = other.m_52;
	m_78 = other.m_78;
	m_7C = other.m_7C;
	m_80 = other.m_80;
	m_84.set(other.m_84);
	m_70 = other.m_70;
	m_positionOfAudio = other.m_positionOfAudio;
	m_48 = other.m_48;
	m_53 = other.m_53;
	if (m_ownerType == 1 || m_ownerType == 2 || m_ownerType == 3 || m_ownerType == 4 || m_ownerType == 5)
		m_ownerID = other.m_ownerID;
}

Rva002D9893 &Rva002D9893::operator=(const Rva002D9893 &other)
{
	rva002D9893(other);
	return *this;
}

class Rva00051C3F : public Rva002D9893
{
	int m_88;
	unsigned char m_8C;

public:
	Rva00051C3F &operator=(const Rva00051C3F &other);
};

Rva00051C3F &Rva00051C3F::operator=(const Rva00051C3F &other)
{
	Rva002D9893::operator=(other);
	m_88 = other.m_88;
	m_8C = other.m_8C;
	return *this;
}
