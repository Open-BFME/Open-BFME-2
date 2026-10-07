// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /arch:SSE /G7 /MD /EHsc
// ??1Rva003561BE@@UAE@XZ @0x003561BE 198B
// The destructor vtable and deleting-dtor anchor identify Rva003561BE.
// Target cleanup proves the +0x14/+0x18 references, +0x1c/+0x20 audio
// handles, and +0x24 flag; the constructor neighbor provides the +0x10
// AsciiString and 16-byte base extent. Unknown virtual slots are kept as
// slot-indexed views; no target method names are inferred from their offsets.
#include "ascii_string.h"

class AudioManager {
public:
#define AUDIO_SLOT(n) virtual void slot##n();
	AUDIO_SLOT(0) AUDIO_SLOT(1) AUDIO_SLOT(2) AUDIO_SLOT(3)
	AUDIO_SLOT(4) AUDIO_SLOT(5) AUDIO_SLOT(6) AUDIO_SLOT(7)
	AUDIO_SLOT(8) AUDIO_SLOT(9) AUDIO_SLOT(10) AUDIO_SLOT(11)
	AUDIO_SLOT(12) AUDIO_SLOT(13) AUDIO_SLOT(14) AUDIO_SLOT(15)
	AUDIO_SLOT(16) AUDIO_SLOT(17) AUDIO_SLOT(18) AUDIO_SLOT(19)
	AUDIO_SLOT(20) AUDIO_SLOT(21) AUDIO_SLOT(22) AUDIO_SLOT(23)
	AUDIO_SLOT(24) AUDIO_SLOT(25) AUDIO_SLOT(26)
	virtual void slot27(int);
#undef AUDIO_SLOT
};
extern AudioManager *TheAudio;

class W3DDisplay {
public:
	void rva0025D2F6();
#define DISPLAY_SLOT(n) virtual void slot##n();
	DISPLAY_SLOT(0) DISPLAY_SLOT(1) DISPLAY_SLOT(2) DISPLAY_SLOT(3)
	DISPLAY_SLOT(4) DISPLAY_SLOT(5) DISPLAY_SLOT(6) DISPLAY_SLOT(7)
	DISPLAY_SLOT(8) DISPLAY_SLOT(9) DISPLAY_SLOT(10) DISPLAY_SLOT(11)
	DISPLAY_SLOT(12) DISPLAY_SLOT(13) DISPLAY_SLOT(14) DISPLAY_SLOT(15)
	DISPLAY_SLOT(16) DISPLAY_SLOT(17) DISPLAY_SLOT(18) DISPLAY_SLOT(19)
	DISPLAY_SLOT(20) DISPLAY_SLOT(21) DISPLAY_SLOT(22) DISPLAY_SLOT(23)
	DISPLAY_SLOT(24) DISPLAY_SLOT(25) DISPLAY_SLOT(26) DISPLAY_SLOT(27)
	DISPLAY_SLOT(28) DISPLAY_SLOT(29) DISPLAY_SLOT(30) DISPLAY_SLOT(31)
	DISPLAY_SLOT(32) DISPLAY_SLOT(33) DISPLAY_SLOT(34) DISPLAY_SLOT(35)
	DISPLAY_SLOT(36) DISPLAY_SLOT(37) DISPLAY_SLOT(38) DISPLAY_SLOT(39)
	DISPLAY_SLOT(40) DISPLAY_SLOT(41) DISPLAY_SLOT(42) DISPLAY_SLOT(43)
	DISPLAY_SLOT(44) DISPLAY_SLOT(45) DISPLAY_SLOT(46) DISPLAY_SLOT(47)
	DISPLAY_SLOT(48) DISPLAY_SLOT(49) DISPLAY_SLOT(50) DISPLAY_SLOT(51)
	DISPLAY_SLOT(52) DISPLAY_SLOT(53) DISPLAY_SLOT(54) DISPLAY_SLOT(55)
	DISPLAY_SLOT(56) DISPLAY_SLOT(57) DISPLAY_SLOT(58) DISPLAY_SLOT(59)
	DISPLAY_SLOT(60) DISPLAY_SLOT(61) DISPLAY_SLOT(62) DISPLAY_SLOT(63)
	DISPLAY_SLOT(64) DISPLAY_SLOT(65) DISPLAY_SLOT(66) DISPLAY_SLOT(67)
	virtual void slot68();
#undef DISPLAY_SLOT
};
class Display : public W3DDisplay { };
extern Display *TheDisplay;

class GameLogic {
	public:
	unsigned char unknown[0x78];
	unsigned char field78;
};
extern GameLogic *TheGameLogic;

class Shell {
	public:
	void rva0035C7CF(bool);
};
extern Shell *TheShell;

struct OpaqueRefCounted { void Release_Ref(); };
struct Rva0036CA00Str {
	OpaqueRefCounted *m_ref;
	Rva0036CA00Str(const Rva0036CA00Str &);
	~Rva0036CA00Str() { if (m_ref) m_ref->Release_Ref(); }
};

class Rva00355D66 {
public:
	virtual ~Rva00355D66();
private:
	char m_pad[12];
};

class Rva003561BE : public Rva00355D66 {
public:
	virtual ~Rva003561BE();
private:
	AsciiString m_s10;
	Rva0036CA00Str m_s14;
	Rva0036CA00Str m_s18;
	int m_handle1c;
	int m_handle20;
	bool m_flag24;
};

Rva003561BE::~Rva003561BE()
{
	if (m_handle1c != 1) {
		TheAudio->slot27(m_handle1c);
		m_handle1c = 1;
	}
	if (m_handle20 != 1) {
		TheAudio->slot27(m_handle20);
		m_handle20 = 1;
	}
	TheGameLogic->field78 = 0;
	TheDisplay->slot68();
	TheDisplay->rva0025D2F6();
	if (m_flag24)
		TheShell->rva0035C7CF(true);
}
