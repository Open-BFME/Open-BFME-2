// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?rva0025CC7A@Display@@QAE_N_N@Z, retail 0x0025CC7A..0x0025CEEF (629B),
// thiscall ret 4.
//
// Display's movie-transition step (callers 0x0025CFF6 and 0x0025D7C9 in the
// Display area), returning true when the movie is done. State +0x54: 0 fades
// the movie in (playback rate ramp by 0.05 when flag 0x400000, else waiting
// for the window transitions to finish and resetting them), 1 plays until
// the end frame +0x58 or a skip and then starts the fade out (flag 0x200000:
// rate ramp; 0x20: the "FadeInGameMovie" group; 0x200: the
// "FadeScreenToWhite" group, each with a "_NoAudio" variant under flag
// 0x1000000, enabled and the window manager pumped), 2 waits for the fade
// out (the rate ramp after +0x110 frames or the transitions) and then for
// the last frame or a skip; any other state returns the skip flag.
//
// Donor: Open-BFME-1 game/GameEngine/Source/GameClient/MovieOpen0040E3B0.cpp
// update0040E680 (same states and flags, fields 4 bytes lower). BFME 2
// differences read from retail: the end-frame test is signed, the fade-out
// groups have the _NoAudio variants, the reset is transitions slot 9 and the
// window manager pump is its slot 10. As in the donor, the flags are read as a
// volatile dword and the end-of-movie test takes the stream by const
// reference (finished0040E680). Callees: rowed
// GameWindowTransitionsHandler::isFinished 0x001DBFEE / setGroup 0x001DC252,
// the rowed one-byte setter 0x001DBB82, StringBase::set 0x000055F5, the
// AsciiString copy 0x000365F0 and release 0x00036410. Literals at 0x007F5D88
// 0x007C8994 0x007F5D6C 0x007F5D58. The method name stays address-derived.
#include "ascii_string.h"

typedef int Int;
typedef float Real;
typedef bool Bool;

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
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void setRate(Real rate);	// slot 17 (+0x44)
	virtual Real getRate();			// slot 18 (+0x48)
};

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
	Bool isFinished();
	void setGroup(AsciiString groupName, Bool immediate);
};
extern GameWindowTransitionsHandler *TheTransitionHandler;

class Rva001DBB82OneSetter
{
public:
	void enable();
};

class GameWindowManager
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
	virtual void slot10();			// +0x28
};
extern GameWindowManager *TheWindowManager;

class Display
{
public:
	Bool rva0025CC7A(Bool skip);

private:
	static __forceinline Bool isMovieAtEnd(VideoStreamInterface *const &stream)
	{
		return stream->frameIndex() >= stream->frameCount() - 1;
	}

	unsigned char m_pad00[0x38];
	VideoStreamInterface *m_videoStream;	// +0x38
	volatile Int m_movieFlags;		// +0x3C (volatile as in the donor: every test rereads the dword)
	unsigned char m_pad40[0x54 - 0x40];
	Int m_movieState;			// +0x54
	Int m_movieEndFrame;			// +0x58
	unsigned char m_pad5C[0x110 - 0x5C];
	Int m_fadeOutDelay;			// +0x110
};

Bool Display::rva0025CC7A(Bool skip)
{
	if (!m_videoStream)
		return true;
	Bool done = false;
	switch (m_movieState)
	{
	case 0:
		if (m_movieFlags & 0x400000)
		{
			Real rate = m_videoStream->getRate() + 0.05f;
			if (rate > 1.0f)
			{
				rate = 1.0f;
				m_movieState = 1;
			}
			m_videoStream->setRate(rate);
		}
		else if (TheTransitionHandler->isFinished())
		{
			m_movieState = 1;
			TheTransitionHandler->reset();
		}
		break;
	case 1:
		if (m_videoStream->frameIndex() >= m_movieEndFrame || skip)
		{
			m_movieState = 3;
			if (m_movieFlags & 0x200000)
			{
				m_movieState = 2;
			}
			else if (m_movieFlags & 0x20)
			{
				AsciiString group;
				if (m_movieFlags & 0x1000000)
					group = "FadeInGameMovie_NoAudio";
				else
					group = "FadeInGameMovie";
				m_movieState = 2;
				TheTransitionHandler->setGroup(group, false);
				((Rva001DBB82OneSetter *)TheTransitionHandler)->enable();
				TheWindowManager->slot10();
			}
			else if (m_movieFlags & 0x200)
			{
				AsciiString group;
				if (m_movieFlags & 0x1000000)
					group = "FadeScreenToWhite_NoAudio";
				else
					group = "FadeScreenToWhite";
				m_movieState = 2;
				TheTransitionHandler->setGroup(group, false);
				((Rva001DBB82OneSetter *)TheTransitionHandler)->enable();
				TheWindowManager->slot10();
			}
			else if (skip)
			{
				done = true;
			}
		}
		break;
	case 2:
	{
		Bool finished = false;
		if (m_movieFlags & 0x200000)
		{
			if (m_fadeOutDelay <= 0)
			{
				Real rate = m_videoStream->getRate() - 0.05f;
				if (rate < 0.0f)
				{
					rate = 0.0f;
					finished = true;
				}
				m_videoStream->setRate(rate);
			}
			else
			{
				--m_fadeOutDelay;
			}
		}
		else if (TheTransitionHandler->isFinished())
		{
			finished = true;
		}
		if (finished)
		{
			if (skip || isMovieAtEnd(m_videoStream))
				done = true;
		}
		break;
	}
	default:
		done = skip;
		break;
	}
	return done;
}
