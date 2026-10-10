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
	virtual unsigned advance(Int flags);
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
	virtual unsigned advance(Int flags);
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
	virtual unsigned advance(Int flags);
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();			// +0x28
};
extern GameWindowManager *TheWindowManager;

class Display
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29();
	virtual void v30();
	virtual void v31();
	virtual void v32();
	virtual void v33();
	virtual void v34();
	virtual void v35();
	virtual void v36();
	virtual void v37();
	virtual void v38();
	virtual void v39();
	virtual void v40();
	virtual void v41();
	virtual void v42();
	virtual void v43();
	virtual void v44();
	virtual void v45();
	virtual void v46();
	virtual void v47();
	virtual void v48();
	virtual void v49();
	virtual void v50();
	virtual void v51();
	virtual void v52();
	virtual void v53();
	virtual void v54();
	virtual void v55();
	virtual void v56();
	virtual void v57();
	virtual void v58();
	virtual void v59();
	virtual void v60();
	virtual void v61();
	virtual void v62();
	virtual void v63();
	virtual void v64();
	virtual void v65();
	virtual void v66();
	virtual void v67();
	virtual void stopMovie();
	void rva0025C4F3();
	Bool rva0025CC7A(Bool skip);

private:
	static __forceinline Bool isMovieAtEnd(VideoStreamInterface *const &stream)
	{
		return stream->frameIndex() >= stream->frameCount() - 1;
	}

	unsigned char m_pad04[0x34];
	VideoStreamInterface *m_videoStream;	// +0x38
	volatile Int m_movieFlags;		// +0x3C (volatile as in the donor: every test rereads the dword)
	Int m_field40;
	Int m_field44;
	unsigned char m_pad48[0x54-0x48];
	Int m_movieState;			// +0x54
	Int m_movieEndFrame;			// +0x58
	Bool m_endReached;
	unsigned char m_pad5D[0xE0-0x5D];
	Int m_deadline0;
	Int m_deadline1;
	unsigned m_start0;
	unsigned m_start1;
	unsigned char m_padF0[0x110-0xF0];
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

// BFME 1 MovieFrame0040E9E0 guides stream advance and the trace loop; this
// target dispatcher additionally finishes fade-out or expires two timers.
extern "C" __declspec(dllimport) int __cdecl sprintf(char*,const char*,...);
extern "C" __declspec(dllimport) void __stdcall OutputDebugStringA(const char*);
extern "C" __declspec(dllimport) unsigned __stdcall timeGetTime();
extern __int64 g_bfmeVM0Total;
extern double g_bfmeVM0Scale;
VideoStreamInterface *MovieFrameStream;
bool MovieFrameTrace;
__int64 MovieFramePrevious, MovieFrameCurrent, MovieFrameElapsed;
double MovieFrameSum;
int MovieFrameCount, MovieFrameDropped;
class Rva0025C3AA { public: void rva0025C3AA(); };

void Display::rva0025C4F3()
{
    char text[40];
    if (m_videoStream && !m_field44) {
        MovieFrameStream = m_videoStream;
        MovieFrameElapsed = MovieFrameCurrent - MovieFramePrevious;
        unsigned result = m_videoStream->advance(m_movieFlags);
        if (result & 4) ++MovieFrameDropped;
        ((Rva0025C3AA*)this)->rva0025C3AA();
        if (MovieFrameTrace) {
            MovieFramePrevious = MovieFrameCurrent;
            MovieFrameSum += (double)(MovieFrameCurrent - MovieFramePrevious);
            if (MovieFrameCount++ > 30) {
                g_bfmeVM0Scale = 0.03333333333333333 / (double)g_bfmeVM0Total * 1000.0;
                sprintf(text, "Avg frame time %4.4f\n", g_bfmeVM0Scale * MovieFrameSum);
                OutputDebugStringA(text);
                MovieFrameSum = 0.0;
                MovieFrameCount = 0;
            }
        }
        if (result & 2) {
            if (m_deadline1 < 0 && m_deadline0 < 0) {
                m_endReached = true;
                if (m_movieFlags & 0x80) {
                    if (m_movieFlags & 0x200000) {
                        if (m_fadeOutDelay <= 0) {
                            Real rate = m_videoStream->getRate() - 0.05f;
                            if (rate <= 0.0f) stopMovie();
                            else m_videoStream->setRate(rate);
                        } else --m_fadeOutDelay;
                    }
                } else stopMovie();
            } else {
                if (!m_start1) m_start1 = timeGetTime();
                if (m_start0 + m_deadline0 < timeGetTime() && m_start1 + m_deadline1 < timeGetTime()) {
                    m_deadline0 = -1; m_deadline1 = -1;
                    m_start0 = 0; m_start1 = 0;
                }
            }
        }
    }
}
