// ?getLoadScreen@GameLogic@@AAEPAVLoadScreen@@_N@Z
// partial score=0.96 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// ?getLoadScreen@GameLogic@@AAEPAVLoadScreen@@_N@Z, retail 0x0023DD48, 764 bytes.
//
// Identity: the existing pin; startNewGame stores the result as the load
// screen. Donor: Open-BFME-1 game/GameEngine/Source/GameLogic/System/
// GameLogicGetLoadScreen.cpp (same mode dispatch and screen factories) and
// ZH GameLogic::getLoadScreen. BFME2 target facts: the mode is at +0x110 with
// an eight-entry jump table; the window manager's +0x31C flag selects the
// shell variant for modes 4 and 7; the default single-player screen
// (Rva0035615D, 0x28 bytes) takes the +0x84/+0x88/+0x8C strings unless loading
// a save, in mode 3, or the image name is empty, in which case it takes a
// fresh image (0x0023D614) and default or audio-settings (+0xA0 of
// TheAudio slot 0x138's result) string handles; modes 1/2/5 use the Apt load
// screen (0xD4 bytes, constructed with the mode) when +0x114 is set.

#include "ascii_string.h"
#include "string_base.h"

typedef bool Bool;

class LoadScreen;
class AsciiStringVX;

class OpaqueRefCounted
{
public:
	void Release_Ref();
};

class Rva0036CA00Str
{
public:
	__forceinline Rva0036CA00Str() : m_ref(0) {}
	Rva0036CA00Str(const Rva0036CA00Str &other);
	~Rva0036CA00Str() { if (m_ref) m_ref->Release_Ref(); }
	OpaqueRefCounted *m_ref;
};

class Rva0043A278
{
public:
	Rva0043A278();
private:
	char m_storage[0x10];
};

class Gen_00491580
{
public:
	Gen_00491580(const AsciiStringVX &a, const AsciiStringVX &b);
private:
	char m_storage[0x18];
};

class Rva0035615D
{
public:
	Rva0035615D(const AsciiString &a, const Rva0036CA00Str &b, const Rva0036CA00Str &c, bool d);
private:
	char m_storage[0x28];
};

class AptLoadScreen
{
public:
	AptLoadScreen(void *mode);
private:
	char m_storage[0xD4];
};

void Rva0023D614Set(StringBase<char> *image);

class BfmeAptWindowManager
{
public:
	char m_pad[0x31C];
	void *m_31c;
};
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

struct Rva0023DD48AudioSettings
{
	char m_pad[0xA0];
	Rva0036CA00Str m_loadScreenMusic;
};

class AudioManager
{
public:
#define X1_V(n) virtual void slot##n();
	X1_V(00) X1_V(01) X1_V(02) X1_V(03) X1_V(04) X1_V(05) X1_V(06) X1_V(07) X1_V(08) X1_V(09)
	X1_V(10) X1_V(11) X1_V(12) X1_V(13) X1_V(14) X1_V(15) X1_V(16) X1_V(17) X1_V(18) X1_V(19)
	X1_V(20) X1_V(21) X1_V(22) X1_V(23) X1_V(24) X1_V(25) X1_V(26) X1_V(27) X1_V(28) X1_V(29)
	X1_V(30) X1_V(31) X1_V(32) X1_V(33) X1_V(34) X1_V(35) X1_V(36) X1_V(37) X1_V(38) X1_V(39)
	X1_V(40) X1_V(41) X1_V(42) X1_V(43) X1_V(44) X1_V(45) X1_V(46) X1_V(47) X1_V(48) X1_V(49)
	X1_V(50) X1_V(51) X1_V(52) X1_V(53) X1_V(54) X1_V(55) X1_V(56) X1_V(57) X1_V(58) X1_V(59)
	X1_V(60) X1_V(61) X1_V(62) X1_V(63) X1_V(64) X1_V(65) X1_V(66) X1_V(67) X1_V(68) X1_V(69)
	X1_V(70) X1_V(71) X1_V(72) X1_V(73) X1_V(74) X1_V(75) X1_V(76) X1_V(77)
#undef X1_V
	virtual Rva0023DD48AudioSettings *getAudioSettings();
};
extern AudioManager *TheAudio;

class GameLogic
{
private:
	LoadScreen *getLoadScreen(Bool loadingSaveGame);
	char m_pad000[0x7C];
	AsciiString m_7c;
	AsciiString m_80;
	AsciiString m_loadScreenImage;
	AsciiString m_88;
	AsciiString m_8c;
	char m_pad090[0x110 - 0x90];
	unsigned int m_gameMode;
	int m_114;
};

LoadScreen *GameLogic::getLoadScreen(Bool loadingSaveGame)
{
	switch (m_gameMode)
	{
	case 4:
		if (g_bfmeAptWindowManager->m_31c)
			return (LoadScreen *)new Rva0043A278;
		return (LoadScreen *)new Gen_00491580((const AsciiStringVX &)m_7c, (const AsciiStringVX &)m_80);

	case 7:
		if (g_bfmeAptWindowManager->m_31c)
		{
			AsciiString image;
			Rva0023D614Set((StringBase<char> *)&image);
			return (LoadScreen *)new Rva0035615D(image, Rva0036CA00Str(), Rva0036CA00Str(), true);
		}
		return (LoadScreen *)new Gen_00491580((const AsciiStringVX &)m_7c, (const AsciiStringVX &)m_80);

	case 0:
	case 3:
	case 6:
		if (loadingSaveGame || m_gameMode == 3 ||
			((const StringBase<char> *)&m_loadScreenImage)->isEmpty())
		{
			AsciiString image;
			Rva0023D614Set((StringBase<char> *)&image);
			return (LoadScreen *)new Rva0035615D(image, Rva0036CA00Str(),
				TheAudio->getAudioSettings()->m_loadScreenMusic, false);
		}
		return (LoadScreen *)new Rva0035615D(m_loadScreenImage,
			*(const Rva0036CA00Str *)&m_88, *(const Rva0036CA00Str *)&m_8c, false);

	case 1:
	case 2:
	case 5:
		if (m_114 == 0)
		{
			if (loadingSaveGame || ((const StringBase<char> *)&m_loadScreenImage)->isEmpty())
			{
				AsciiString image;
				Rva0023D614Set((StringBase<char> *)&image);
				return (LoadScreen *)new Rva0035615D(image, Rva0036CA00Str(),
					TheAudio->getAudioSettings()->m_loadScreenMusic, false);
			}
			return (LoadScreen *)new Rva0035615D(m_loadScreenImage,
				*(const Rva0036CA00Str *)&m_88, *(const Rva0036CA00Str *)&m_8c, false);
		}
		return (LoadScreen *)new AptLoadScreen((void *)m_gameMode);
	}
	return 0;
}
