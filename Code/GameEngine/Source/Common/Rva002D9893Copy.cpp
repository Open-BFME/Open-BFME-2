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
