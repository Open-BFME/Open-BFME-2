// ?rva0035C2B9@Shell@@QAEXXZ
// partial score=0.99 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /G7 /DNDEBUG /MD /EHsc
//
// ?rva0035C2B9@Shell@@QAEXXZ @0x0035C2B9 266B: BFME 2's shell music keeper,
// rowed by address (the method is declared, unnamed, in ShellTop.cpp's view).
// While the shell wants music (+0x6C) and TheAudio exists and the handle at
// +0x68 is no longer playing (TheAudio slot 0xD0), it either consumes a
// one-shot skip (+0x6D) or restarts the track: the misc-audio record from
// TheAudio slot 0x138 supplies the shell-map track (+0x90) or, when the
// shell map is off (TheGlobalData +0xAF0), the plain shell track (+0x8C);
// slot 0x8C (2, 1, 0) stops the old music first, then the event is built
// (constructor 0x002D97D6), typed 2 (0x002D94CE) and its handle kept.
#include "Common/BfmeAudioEventPrefix136.h"

typedef bool Bool;

struct ShellMusicMiscAudio
{
	unsigned char m_pad00[0x8C];
	OpaqueRefElement4 m_shellMusic;		// +0x8C
	OpaqueRefElement4 m_shellMapMusic;	// +0x90
};

class AudioManager
{
public:
#define V(n) virtual void pad##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	V(24)
	virtual unsigned int addAudioEvent(const BfmeAudioEventPrefix136 *evt) = 0;	// 0x64
	V(26) V(27) V(28) V(29) V(30) V(31) V(32) V(33) V(34)
	virtual void removeAudioEvents(int a, int b, int c) = 0;	// 0x8C
	V(36) V(37) V(38) V(39) V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47)
	V(48) V(49) V(50) V(51)
	virtual Bool isCurrentlyPlaying(unsigned int handle) = 0;	// 0xD0
	V(53) V(54) V(55) V(56) V(57) V(58) V(59) V(60) V(61) V(62) V(63) V(64)
	V(65) V(66) V(67) V(68) V(69) V(70) V(71) V(72) V(73) V(74) V(75) V(76) V(77)
#undef V
	virtual ShellMusicMiscAudio *getMiscAudio() = 0;	// 0x138
};
extern AudioManager *TheAudio;

struct ShellMusicGlobalData
{
	unsigned char m_pad[0xAF0];
	Bool m_shellMapOn;	// +0xAF0
};
extern ShellMusicGlobalData *TheGlobalData;

class Rva002D94CE { public: void rva002D94CE(int value); };

struct ShellMusicRef : OpaqueRefElement4
{
	ShellMusicRef() { referent = 0; }
	~ShellMusicRef() { if (referent) referent->Release_Ref(); }
};

class Shell
{
public:
	void rva0035C2B9();

private:
	unsigned char m_pad00[0x68];
	unsigned int m_musicHandle;	// +0x68
	Bool m_wantMusic;		// +0x6C
	Bool m_skipMusicRestart;	// +0x6D
};

void Shell::rva0035C2B9()
{
	if (!m_wantMusic || !TheAudio || TheAudio->isCurrentlyPlaying(m_musicHandle))
		return;

	if (m_skipMusicRestart)
	{
		m_skipMusicRestart = false;
		return;
	}

	ShellMusicMiscAudio *misc = TheAudio->getMiscAudio();
	if (!misc)
		return;

	ShellMusicRef track;
	track.OpaqueRefElement4::operator=((TheGlobalData && !TheGlobalData->m_shellMapOn) ? misc->m_shellMusic : misc->m_shellMapMusic);
	if (track.referent)
	{
		TheAudio->removeAudioEvents(2, 1, 0);
		BfmeAudioEventPrefix136 music(track, 0);
		((Rva002D94CE *)&music)->rva002D94CE(2);
		m_musicHandle = TheAudio->addAudioEvent(&music);
	}
}
