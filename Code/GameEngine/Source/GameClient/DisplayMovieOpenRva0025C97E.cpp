// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?rva0025C97E@Display@@UAE_NVAsciiString@@HHH@Z
// retail 0x0025C97E..0x0025CC79 (764 bytes) thiscall RET 0x10.
//
// Display's movie start (virtual; absolute references 0x007C3D88 and
// 0x007F5EA8), the opener whose state DisplayMovieUpdateRva0025CC7A.cpp
// steps. Donor: Open-BFME-1 game/GameEngine/Source/GameClient/
// MovieOpen0040E3B0.cpp open (same flags and fields, 4 bytes lower). BFME 2
// differences read from retail: the video player's open is slot 17, the
// stream's subtitle record (stream +0x08, then +0x18) gets its font from
// TheFontLibrary->getFont (0x002189E1) at the record's point size scaled by
// the display height over 1024 and handed to the rowed 0x006883B0, the
// fade groups have "_NoAudio" variants under flag 0x1000000, and the
// transitions are guarded by the rowed Rva0023C565 lock (out-of-line
// constructor, inline unlock). Callees: Display slots 68 (stop), 16
// (height) and 41 (video buffer), VideoPlayer slot 17, stream slots 14
// (start), 17 (rate) and 9 (frame count), the transitions' slot 9 reset,
// reverse 0x001DC345 and bfmeGetGroupTotalFrames 0x001DC1FD, timeGetTime.
// The method name stays address-derived.
#include "ascii_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

class GameFont;

class FontLibrary
{
public:
	GameFont *getFont(const AsciiString *name, Real pointSize, Bool bold);
};
extern FontLibrary *TheFontLibrary;

// The stream's subtitle record: font name +0x0C, point size +0x10.
class Rva006883B0Owner
{
public:
	void broadcast(Int value);

	unsigned char m_pad00[0x0C];
	AsciiString m_fontName;		// +0x0C
	Int m_pointSize;			// +0x10
};

struct VideoStreamSubtitles
{
	unsigned char m_pad00[0x18];
	Rva006883B0Owner *m_subtitles;	// +0x18
};

class VideoStreamInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual Int frameIndex();		// slot 8 (+0x20)
	virtual Int frameCount();		// slot 9 (+0x24)
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual Bool start(void *buffer);	// slot 14 (+0x38)
	virtual void slot15();
	virtual void slot16();
	virtual void setRate(Real rate);	// slot 17 (+0x44)

	unsigned char m_pad04[0x08 - 0x04];
	VideoStreamSubtitles *m_08;		// +0x08
};

class VideoPlayerInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual VideoStreamInterface *open(AsciiString movieName, Int flags);	// slot 17 (+0x44)
};
extern VideoPlayerInterface *TheVideoPlayer;

class GameWindowTransitionsHandler
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void reset();			// slot 9 (+0x24)
	void reverse(AsciiString groupName);
	Int bfmeGetGroupTotalFrames(AsciiString groupName);
};
extern GameWindowTransitionsHandler *TheTransitionHandler;

class Rva001DBAA4
{
public:
	void unlock(void);
};

class Rva0023C565
{
public:
	Rva0023C565();
	~Rva0023C565()
	{
		if (TheTransitionHandler)
			((Rva001DBAA4 *)TheTransitionHandler)->unlock();
	}
};

template <int N> class DisplaySlots : public DisplaySlots<N - 1>
{
public:
	virtual void gap(char (*)[N]);
};
template <> class DisplaySlots<1>
{
public:
	virtual void gap(char (*)[1]);
};

class Display : public DisplaySlots<16>
{
public:
	virtual UnsignedInt getHeight();				// slot 16 (+0x40)
	virtual void slot17(); virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23(); virtual void slot24();
	virtual void slot25(); virtual void slot26(); virtual void slot27(); virtual void slot28();
	virtual void slot29(); virtual void slot30(); virtual void slot31(); virtual void slot32();
	virtual void slot33(); virtual void slot34(); virtual void slot35(); virtual void slot36();
	virtual void slot37(); virtual void slot38(); virtual void slot39(); virtual void slot40();
	virtual void *createVideoBuffer(Bool special);	// slot 41 (+0xA4)
	virtual void slot42(); virtual void slot43(); virtual void slot44(); virtual void slot45();
	virtual void slot46(); virtual void slot47(); virtual void slot48(); virtual void slot49();
	virtual void slot50(); virtual void slot51(); virtual void slot52(); virtual void slot53();
	virtual void slot54(); virtual void slot55(); virtual void slot56(); virtual void slot57();
	virtual void slot58(); virtual void slot59(); virtual void slot60(); virtual void slot61();
	virtual void slot62(); virtual void slot63(); virtual void slot64(); virtual void slot65();
	virtual void slot66(); virtual void slot67();
	virtual void stopMovie();						// slot 68 (+0x110)
	virtual Bool rva0025C97E(AsciiString movieName, Int flags, Int x, Int y);

private:
	unsigned char m_pad04[0x38 - 0x04];
	VideoStreamInterface *m_videoStream;	// +0x38
	volatile Int m_movieFlags;		// +0x3C
	unsigned char m_pad40[0x54 - 0x40];
	Int m_movieState;			// +0x54
	Int m_movieEndFrame;			// +0x58
	Bool m_5C;				// +0x5C
	volatile Bool m_5D;			// +0x5D (volatile as the donor's +0x59: the store keeps its place)
	unsigned char m_pad5E[0xD0 - 0x5E];
	AsciiString m_movieName;		// +0xD0
	unsigned char m_padD4[0xE0 - 0xD4];
	Int m_movieX;				// +0xE0
	Int m_movieY;				// +0xE4
	UnsignedInt m_movieStartTime;		// +0xE8
	unsigned char m_padEC[0x110 - 0xEC];
	Int m_fadeOutDelay;			// +0x110
};

Bool Display::rva0025C97E(AsciiString movieName, Int flags, Int x, Int y)
{
	stopMovie();
	Bool special = false;
	m_5D = true;
	m_5C = false;
	if (flags & 0x40)
		special = true;

	m_videoStream = TheVideoPlayer->open(movieName, flags);
	if (!m_videoStream)
		return false;

	Rva006883B0Owner *subtitles = m_videoStream->m_08->m_subtitles;
	if (subtitles)
	{
		Int pointSize = subtitles->m_pointSize;
		Real size = pointSize * ((Real)getHeight() / 1024.0f);
		GameFont *font = TheFontLibrary->getFont(&subtitles->m_fontName, size, false);
		subtitles->broadcast((Int)font);
	}

	if (!m_videoStream->start(createVideoBuffer(special)))
	{
		stopMovie();
		return false;
	}

	m_5D = false;
	m_movieName = movieName;
	m_movieX = x;
	m_movieY = y;
	m_movieStartTime = timeGetTime();
	m_movieFlags = flags;

	if (m_movieFlags & 0x400000)
		m_videoStream->setRate(0.05f);
	else if (m_movieFlags & 0x10)
	{
		AsciiString group;
		if (m_movieFlags & 0x1000000)
			group = "FadeInGameMovie_NoAudio";
		else
			group = "FadeInGameMovie";
		Rva0023C565 lock;
		TheTransitionHandler->reset();
		TheTransitionHandler->reverse(group);
		m_movieState = 0;
	}
	else if (m_movieFlags & 0x100)
	{
		AsciiString group;
		if (m_movieFlags & 0x1000000)
			group = "FadeScreenToWhite_NoAudio";
		else
			group = "FadeScreenToWhite";
		Rva0023C565 lock;
		TheTransitionHandler->reset();
		TheTransitionHandler->reverse(group);
		m_movieState = 0;
	}
	else
	{
		TheTransitionHandler->reset();
		m_movieState = 1;
	}

	Int count = m_videoStream->frameCount();
	if (m_movieFlags & 0x200000)
	{
		m_fadeOutDelay = 10;
		if (m_movieFlags & 0x80)
			m_movieEndFrame = count;
		else
			m_movieEndFrame = count - 20;
	}
	else if (m_movieFlags & 0x20)
	{
		AsciiString group;
		if (m_movieFlags & 0x1000000)
			group = "FadeInGameMovie_NoAudio";
		else
			group = "FadeInGameMovie";
		m_movieEndFrame = count - TheTransitionHandler->bfmeGetGroupTotalFrames(group);
	}
	else if (m_movieFlags & 0x200)
	{
		AsciiString group;
		if (m_movieFlags & 0x1000000)
			group = "FadeScreenToWhite_NoAudio";
		else
			group = "FadeScreenToWhite";
		m_movieEndFrame = count - TheTransitionHandler->bfmeGetGroupTotalFrames(group);
	}
	else
		m_movieEndFrame = m_videoStream->frameCount();
	return true;
}
