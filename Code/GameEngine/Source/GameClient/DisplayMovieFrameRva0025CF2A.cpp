// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?rva0025CF2A@Display@@UAEIH@Z
// retail 0x0025CF2A..0x0025D10F (485 bytes) thiscall RET 4.
//
// Display's movie frame step (virtual slot 33: absolute references
// 0x007C3DA4 and 0x007F5EC4 beside slot 26's rva0025C97E). Unless forced it
// does nothing while +0x40 or +0x44 is set; with a stream (+0x38) it sleeps
// 10ms while the engine is inactive (TheGameEngine slot 24), times the frame
// against g_bfmeVM0Quotient (formatting the stream's frame index), and when
// the stream has a frame ready (slot 5 with the flags +0x3C) and the movie
// transition step 0x0025CC7A is not done it refreshes through 0x0025C3AA and
// takes the device lock 0x0011F5B0: then it advances the stream (slot 6)
// marking +0x5D on bit 2 pumps TheWindowManager slot 10 renders (own slot
// 99) unlocks (0x00120F50) restores the FP mode (0x00040EA9) and keeps the
// optional average frame time trace; without the lock it sleeps 1ms and
// counts +0x13C. Returns the advance flags (2 when nothing was advanced).
//
// Donor: Open-BFME-1 game/GameEngine/Source/GameClient/MovieFrame0040E9E0.cpp
// frame0040E9E0 (same statements; fields 4 bytes lower). BFME 2 differences
// read from retail: the second engine-activity check after taking the lock
// (unlock then the shared Sleep(10) return) and the render slot. Both literals
// ("%d" 0x007BE164 and "Avg frame time %4.4f\n" 0x007F5D34) and the imports
// were read from retail. The clock globals 0x009FE9E8 (previous) 0x009FE9F0
// (current) 0x009FEA00 (elapsed) 0x009FEA08 (sum) 0x009FEA18 (count) and
// the trace switch 0x009FE9D4 have no ledger name and stay address-named.
// The frame-index buffer is sized below the trace buffer (17 bytes): equal
// sizes put it at the lower frame slot where retail has the trace text. The
// +0x13C counter is volatile to keep retail's add-to-memory. The method name
// stays address-derived.
typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

extern "C" __declspec(dllimport) int __cdecl sprintf(char *, const char *, ...);
extern "C" __declspec(dllimport) void __stdcall Sleep(unsigned long);
extern "C" __declspec(dllimport) void __stdcall OutputDebugStringA(const char *);

Bool bfmeRva0011F5B0(unsigned long);		// 0x0011F5B0, the device lock
Bool BFME_DX8_Thread_Assert();			// 0x00120F50, its unlock
void setFPMode();				// 0x00040EA9

class GameEngine
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual Bool isActive();			// slot 24 (+0x60)
};
extern GameEngine *TheGameEngine;

class GameWindowManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09();
	virtual void slot10();				// slot 10 (+0x28)
};
extern GameWindowManager *TheWindowManager;

extern __int64 g_bfmeVM0Quotient;
extern double g_bfmeVM0Scale;
extern __int64 g_00DFE9E8;
extern __int64 g_00DFE9F0;
extern __int64 g_00DFEA00;
extern double g_00DFEA08;
extern Int g_00DFEA18;
extern Bool g_00DFE9D4;

class VideoStreamInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual Bool isFrameReady(Int flags);		// slot 5 (+0x14)
	virtual UnsignedInt advance(Int flags);		// slot 6 (+0x18)
	virtual void slot07();
	virtual Int frameIndex();			// slot 8 (+0x20)
};

class Rva0025C3AA
{
public:
	void rva0025C3AA();				// 0x0025C3AA
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

class Display : public DisplaySlots<33>
{
public:
	virtual UnsignedInt rva0025CF2A(Int force);	// slot 33 (+0x84)
	virtual void slot34(); virtual void slot35(); virtual void slot36(); virtual void slot37();
	virtual void slot38(); virtual void slot39(); virtual void slot40(); virtual void slot41();
	virtual void slot42(); virtual void slot43(); virtual void slot44(); virtual void slot45();
	virtual void slot46(); virtual void slot47(); virtual void slot48(); virtual void slot49();
	virtual void slot50(); virtual void slot51(); virtual void slot52(); virtual void slot53();
	virtual void slot54(); virtual void slot55(); virtual void slot56(); virtual void slot57();
	virtual void slot58(); virtual void slot59(); virtual void slot60(); virtual void slot61();
	virtual void slot62(); virtual void slot63(); virtual void slot64(); virtual void slot65();
	virtual void slot66(); virtual void slot67(); virtual void slot68(); virtual void slot69();
	virtual void slot70(); virtual void slot71(); virtual void slot72(); virtual void slot73();
	virtual void slot74(); virtual void slot75(); virtual void slot76(); virtual void slot77();
	virtual void slot78(); virtual void slot79(); virtual void slot80(); virtual void slot81();
	virtual void slot82(); virtual void slot83(); virtual void slot84(); virtual void slot85();
	virtual void slot86(); virtual void slot87(); virtual void slot88(); virtual void slot89();
	virtual void slot90(); virtual void slot91(); virtual void slot92(); virtual void slot93();
	virtual void slot94(); virtual void slot95(); virtual void slot96(); virtual void slot97();
	virtual void slot98();
	virtual void render(Bool flag);			// slot 99 (+0x18C)

	Bool rva0025CC7A(Bool skip);			// 0x0025CC7A

private:
	unsigned char m_pad04[0x38 - 0x04];
	VideoStreamInterface *m_videoStream;		// +0x38
	Int m_movieFlags;				// +0x3C
	Int m_40;					// +0x40
	Int m_44;					// +0x44
	unsigned char m_pad48[0x5D - 0x48];
	Bool m_5D;					// +0x5D
	unsigned char m_pad5E[0x13C - 0x5E];
	volatile Int m_lockFailures;			// +0x13C
};

UnsignedInt Display::rva0025CF2A(Int force)
{
	UnsignedInt result = 2;
	char trace[20];
	char text[17];
	if (!force && (m_40 || m_44))
		return 0;
	if (m_videoStream)
	{
		if (!TheGameEngine->isActive())
		{
			Sleep(10);
			return 0;
		}
		g_00DFEA00 = g_00DFE9F0 - g_00DFE9E8;
		if (g_00DFEA00 > g_bfmeVM0Quotient)
			sprintf(text, "%d", m_videoStream->frameIndex());
		g_00DFE9E8 = g_00DFE9F0;
		if (m_videoStream->isFrameReady(m_movieFlags))
		{
			if (!rva0025CC7A(false))
			{
				((Rva0025C3AA *)this)->rva0025C3AA();
				if (bfmeRva0011F5B0(1))
				{
					m_lockFailures = 0;
					if (!TheGameEngine->isActive())
					{
						BFME_DX8_Thread_Assert();
						Sleep(10);
						return 0;
					}
					result = m_videoStream->advance(m_movieFlags);
					if (result & 2)
						m_5D = true;
					TheWindowManager->slot10();
					render(false);
					BFME_DX8_Thread_Assert();
					setFPMode();
					if (g_00DFE9D4)
					{
						g_00DFEA08 += (double)(g_00DFE9F0 - g_00DFE9E8);
						if (g_00DFEA18++ > 30)
						{
							sprintf(trace, "Avg frame time %4.4f\n", g_bfmeVM0Scale * g_00DFEA08);
							OutputDebugStringA(trace);
							g_00DFEA08 = 0.0;
							g_00DFEA18 = 0;
						}
					}
				}
				else
				{
					Sleep(1);
					++m_lockFailures;
				}
			}
			else
				m_5D = true;
		}
	}
	return result;
}
