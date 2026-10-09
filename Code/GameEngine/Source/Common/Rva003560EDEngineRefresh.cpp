// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva00355DF4@Rva003560ED@@QAEXH@Z @0x00355DF4 44B
// ?rva00355E20@Rva003560ED@@QAEXHH@Z @0x00355E20 44B
// ?rva00356889@Rva003561BE@@QAEXPAVGameInfo@@@Z @0x00356889 625B (SSE: /G7 /arch:SSE)
// ?rva00356724@Rva003560ED@@QAEXPAVGameInfo@@@Z @0x00356724 329B
// Slots 1 and 4 of vtable 0x00C14EA4 (class of the rowed dtor 0x003560ED and
// of rva00355DDD, slot 3), shared by the derived vtable 0x00C14EBC: both call
// TheGameEngine slot 23 and, when TheWritableGlobalData's +0x11C8 flag is set,
// TheDisplay slot 73 with 0. They differ only in their ignored stack
// arguments (ret 4 / ret 8), so ICF could not fold them.
#include "GameLogicObjectLookupView.h"
#include "ascii_string.h"
#include "unicode_string.h"

template <int N> class VirtualSlots : public VirtualSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]);
};
template <> class VirtualSlots<0>
{
};
class GameEngine : public VirtualSlots<23>
{
public:
	virtual void slot23();
};
class Display : public VirtualSlots<66>
{
public:
	virtual void slot66(AsciiString name, int flags, int a, int b);
	virtual void d67();
	virtual void slot68();
	virtual void d69(); virtual void d70(); virtual void d71();
	virtual void slot72(AsciiString name, int flags);
	virtual void slot73(int value);
	void rva002B2466(float x0, float y0, float x1, float y1);
};
class W3DDisplay
{
public:
	void rva0025D2F6();
};
class Image
{
public:
	unsigned char m_pad00[0x28];
	int m_28; // +0x28 (height in 768-line units)
};
class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};
extern ImageCollection *TheMappedImageCollection;
class GameFont;
class FontLibrary
{
public:
	GameFont *getFont(const AsciiString *name, float pointSize, bool bold);
};
extern FontLibrary *TheFontLibrary;
class GameTextInterface : public VirtualSlots<14>
{
public:
	virtual UnicodeString fetch(const AsciiString &label, bool *exists);
};
extern GameTextInterface *TheGameText;
// TheDisplay's W3DDisplay members (rowed under this opaque class name).
class BfmeStrVM0
{
public:
	void rva0025C6E2(int image, int layer, float x0, float y0, float x1, float y1);
	void rva0025D358(UnicodeString text, float x, float y, int font, int color, int flags);
};
class GlobalData
{
public:
	unsigned char m_pad0000[0x11C8];
	bool m_11c8; // +0x11C8
};
extern GameEngine *TheGameEngine;
extern Display *TheDisplay;
extern GlobalData *TheWritableGlobalData;
class GameInfo;
class Rva003560ED
{
public:
	void rva00355DF4(int);
	void rva00355E20(int, int);
	void rva00356724(GameInfo *game);
private:
	unsigned char m_pad00[0x10];
	AsciiString m_movieOverlay; // +0x10
	AsciiString m_image; // +0x14
};
void Rva003560ED::rva00355DF4(int)
{
	TheGameEngine->slot23();
	if (TheWritableGlobalData->m_11c8)
		TheDisplay->slot73(0);
}
void Rva003560ED::rva00355E20(int, int)
{
	TheGameEngine->slot23();
	if (TheWritableGlobalData->m_11c8)
		TheDisplay->slot73(0);
}

// ?rva00355E4C@Rva003561BE@@QAE_NXZ @0x00355E4C 57B
// Slot 5 of the derived vtable 0x00C14EBC (class of the rowed deleting dtor
// 0x0035686D): true without TheAudio; otherwise TheAudio slot 10, then, unless
// the +0x1C value is 1, true only when TheAudio slot 52 refuses that value.
class AudioManager : public VirtualSlots<10>
{
public:
	virtual void slot10();
	virtual void a11(); virtual void a12(); virtual void a13(); virtual void a14();
	virtual void a15(); virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19();
	virtual void slot20(int which); virtual void a21(); virtual void a22(); virtual void a23(); virtual void a24();
	virtual void a25(); virtual void a26(); virtual void slot27(int value); virtual void a28(); virtual void a29();
	virtual void a30(); virtual void a31(); virtual void a32(); virtual void a33(); virtual void a34();
	virtual void a35(); virtual void a36(); virtual void a37(); virtual void a38(); virtual void a39();
	virtual void a40(); virtual void a41(); virtual void a42(); virtual void a43(); virtual void a44();
	virtual void a45(); virtual void a46(); virtual void a47(); virtual void a48(); virtual void a49();
	virtual void a50(); virtual void a51();
	virtual bool slot52(int value);
};
extern AudioManager *TheAudio;
class Rva003561BE
{
public:
	bool rva00355E4C();
	void rva00355E85();
	void rva00356889(GameInfo *game);
private:
	unsigned char m_pad00[0x08];
	int m_08; // +0x08
	unsigned char m_pad0C[0x10 - 0x0C];
	AsciiString m_image; // +0x10
	int m_14; // +0x14
	int m_18; // +0x18
	int m_1c; // +0x1C
	int m_20; // +0x20
};
bool Rva003561BE::rva00355E4C()
{
	bool result = true;
	if (TheAudio)
	{
		TheAudio->slot10();
		if (m_1c != 1)
			result = !TheAudio->slot52(m_1c);
	}
	return result;
}

// TheGameLogic's +0x78 flag, private padding in the shared GameLogic view.
extern GameLogic *TheGameLogic;
static __forceinline void clearGameLogicFlag78()
{
	*((bool *)TheGameLogic + 0x78) = false;
}
static __forceinline void setGameLogicFlag78()
{
	*((bool *)TheGameLogic + 0x78) = true;
}
class Rva00356284
{
public:
	void rva00356284();
};

// ?rva00355E85@Rva003561BE@@QAEXXZ @0x00355E85 92B
// Slot 3 of the derived vtable 0x00C14EBC: hands each of the +0x1C/+0x20
// values that is not 1 to TheAudio slot 27 and resets it to 1, clears
// TheGameLogic's +0x78 flag, runs TheDisplay slot 68 and the rowed
// W3DDisplay 0x0025D2F6, and clears +0x08 (the base slot 3 rva00355DDD runs
// the same slot 68 then clears +0x08).
void Rva003561BE::rva00355E85()
{
	if (m_1c != 1)
	{
		TheAudio->slot27(m_1c);
		m_1c = 1;
	}
	if (m_20 != 1)
	{
		TheAudio->slot27(m_20);
		m_20 = 1;
	}
	clearGameLogicFlag78();
	TheDisplay->slot68();
	((W3DDisplay *)TheDisplay)->rva0025D2F6();
	m_08 &= 0;
}

// ?rva00356889@Rva003561BE@@QAEXPAVGameInfo@@@Z @0x00356889 625B
// Slot 2 of the derived vtable 0x00C14EBC (RET 4, argument unused): the
// load screen's start. TheAudio slot 20 (2) and slot 10; the
// "LoadScreenForeground" image on display layer 2 over the whole screen and
// the +0x10 image (when named) on layer 0 from y = 126/768 down by its +0x28
// height in 768ths; TheGameLogic +0x78 set; TheDisplay rva002B2466 with the
// ring rectangle; the "SmallRing" movie through TheDisplay slot 72 (flags
// 0x14, or 0x1000014 without the +0x14/+0x18 values) or, with
// TheWritableGlobalData +0x11C8, slot 66 (0x14, -1, -1); the audio start
// (rowed 0x00356284); and the "GUI:Loading" text in 18-point "SachaWynter"
// at (0.5, 1/32) through the rowed W3DDisplay text setter 0x0025D358.
void Rva003561BE::rva00356889(GameInfo *)
{
	TheAudio->slot20(2);
	TheAudio->slot10();
	AsciiString foregroundName("LoadScreenForeground");
	const Image *foreground = TheMappedImageCollection->findImageByName(foregroundName);
	if (foreground)
		((BfmeStrVM0 *)TheDisplay)->rva0025C6E2((int)foreground, 2, 0.0f, 0.0f, 1.0f, 1.0f);
	if (!((const StringBase<char> *)&m_image)->isEmpty())
	{
		const Image *image = TheMappedImageCollection->findImageByName(m_image);
		if (image)
			((BfmeStrVM0 *)TheDisplay)->rva0025C6E2((int)image, 0, 0.0f, 0.1640625f, 1.0f,
				image->m_28 / 768.0f + 0.1640625f);
	}
	setGameLogicFlag78();
	TheDisplay->rva002B2466(0.46826171875f, 0.87565106f, 0.53076171875f, 0.958984375f);
	AsciiString movieName("SmallRing");
	int flags = 0x14;
	if (!m_14 && !m_18)
		flags = 0x1000014;
	if (!TheWritableGlobalData->m_11c8)
	{
		if (TheDisplay)
			TheDisplay->slot72(movieName, flags);
	}
	else
		TheDisplay->slot66(movieName, 0x14, -1, -1);
	((Rva00356284 *)this)->rva00356284();
	bool exists = false;
	GameFont *font = TheFontLibrary->getFont(&AsciiString("SachaWynter"), 18.0f, false);
	UnicodeString text = TheGameText->fetch(AsciiString("GUI:Loading"), &exists);
	((BfmeStrVM0 *)TheDisplay)->rva0025D358(text, 0.5f, 0.03125f, (int)font, -10924, 0);
}

// ?rva00356724@Rva003560ED@@QAEXPAVGameInfo@@@Z @0x00356724 329B
// Slot 2 of vtable 0x00C14EA4 (RET 4, argument unused), the base load
// screen's start: with a +0x10 name, the ring rectangle (Display 0x002B2466)
// and TheAudio slots 20(2)/10; the +0x14 image on display layer 2 over the
// whole screen; TheGameLogic +0x78; and with a +0x10 name the "SmallRing"
// movie through TheDisplay slot 72 (flags 4) or, with TheWritableGlobalData
// +0x11C8, slot 66 (4, -1, -1). The derived 0x00356889 is the same sequence
// with its foreground and text.
void Rva003560ED::rva00356724(GameInfo *)
{
	if (!((const StringBase<char> *)&m_movieOverlay)->isEmpty())
	{
		TheDisplay->rva002B2466(0.4677734375f, 0.84114583f, 0.5302734375f, 0.92447917f);
		TheAudio->slot20(2);
		TheAudio->slot10();
	}
	if (!((const StringBase<char> *)&m_image)->isEmpty())
		((BfmeStrVM0 *)TheDisplay)->rva0025C6E2((int)TheMappedImageCollection->findImageByName(m_image), 2, 0.0f, 0.0f, 1.0f, 1.0f);
	setGameLogicFlag78();
	if (!((const StringBase<char> *)&m_movieOverlay)->isEmpty())
	{
		AsciiString movieName("SmallRing");
		if (!TheWritableGlobalData->m_11c8)
		{
			if (TheDisplay)
				TheDisplay->slot72(movieName, 4);
		}
		else
			TheDisplay->slot66(movieName, 4, -1, -1);
	}
}
