// cl: /O2 /G6 /arch:SSE /MD
// ?rva006E2D60@AptCIH@@QAEXXZ, retail 0x006E2D60, 383 bytes.
// AptCIH per-frame tick. Sprite instance: assert isSpriteInstBase (AptCIH.h
// 0x7D) and take the +0x4C sprite; clear +0x28; when playing (bit 25 of +0x1C)
// step +0x18 (reset when +0x2C is 1) and either stop a one-frame movie or
// loop through jumpToFrame(0); otherwise run doFrameControls and
// queueFrameActions with +0x28 bracketed by -frame/frame. Then queue the
// clip events (0x006E2010) for state 2 when not latched (bit 24) or a
// defined button (type 0x12); when latched queue state 1 and clear the latch;
// finally tick the +0x24 display list (0x006F7A30). Edit text (type 0x0E,
// "this" assert AptCIH.h 0xB5): tick the +0x1C list of 0x006E1090.
// Evidence: WorldBuilder twin 0x01797540 (same calls and order); callees
// rowed or pinned (jumpToFrame doFrameControls queueFrameActions isUndefined
// getVtblIndex 0x006E1F90 0x006E2010 0x006F7A30); caller 0x006F7AA1 is the
// child walk 0x006F7A30 itself. 0x006E1F90 returns int: all five retail
// callers test eax (its body sets eax 0/1), so it is called through the
// placeholder spelling ?rva006E1F90@AptCIH@@QAEHH@Z.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
extern int g_00E17704;
void __debugbreak();
#pragma intrinsic(__debugbreak)

class AptCIH;
class AptNativeHash;
class AptDisplayList { public: void *state; };
class AptMovie
{
public:
	int nFrames;
	void doFrameControls(AptDisplayList *, AptCIH *, int);
	void queueFrameActions(AptCIH *, int);
};
struct AptCharacter { unsigned char prefix[8]; AptMovie movie; };
struct AptCharacterSpriteInstBase
{
	unsigned char prefix[12];
	AptCharacter *character;
	AptNativeHash *nativeHash;
	int unknown14;
	int mnFrame;
	unsigned int flagsLow : 24;
	unsigned int latched : 1;
	unsigned int playing : 1;
	unsigned int flagsHigh : 6;
	void *actions;
	AptDisplayList display;
	int mnGotoAnded;
	int mode;
};
class Rva006F7A30 { public: void rva006F7A30(); };
struct Rva006E1090Target { unsigned char prefix[0x1c]; Rva006F7A30 list; };
class Rva006E2010Dispatcher { public: void dispatch(int, int, int); };

class AptValue
{
public:
	int getVtblIndex() const;
	bool isUndefined() const;
};

class AptCIH : public AptValue
{
public:
	bool IsSpriteInstBase() const;
	AptCharacterSpriteInstBase *GetSpriteInstBase() const
	{
		if (!IsSpriteInstBase()) {
			g_bfmeAptAssertAtE17734("isSpriteInstBase()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0x7d);
			if (g_bfmeAptBreakOnAssertAtDDC01C)
				__debugbreak();
		}
		return character;
	}
	__forceinline bool isEditText() const
	{
		if (!this) {
			g_bfmeAptAssertAtE17734("this", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0xb5);
			if (g_bfmeAptBreakOnAssertAtDDC01C)
				__debugbreak();
		}
		return getVtblIndex() == 0xe && !isUndefined();
	}
	bool isButton() const { return getVtblIndex() == 0x12 && !isUndefined(); }
	void jumpToFrame(int);
	int rva006E1F90(int);
	void *rva006E1090() const;
	void rva006E2D60();

	unsigned char prefix[0x4c];
	AptCharacterSpriteInstBase *character;
};

void AptCIH::rva006E2D60()
{
	if (IsSpriteInstBase()) {
		AptCharacterSpriteInstBase *sprite = GetSpriteInstBase();
		sprite->mnGotoAnded = 0;
		if (sprite->playing) {
			if (sprite->mode == 1)
				sprite->mnFrame = 0;
			else
				sprite->mnFrame++;
			if (sprite->mnFrame == 1 && sprite->character->movie.nFrames == 1) {
				sprite->mnFrame = 0;
				goto events;
			}
			if (sprite->mnFrame == sprite->character->movie.nFrames) {
				jumpToFrame(0);
				goto events;
			}
		}
		if (sprite->playing)
			sprite->character->movie.doFrameControls(&sprite->display, this, sprite->mnFrame);
		if (sprite->playing) {
			sprite->mnGotoAnded = -sprite->mnFrame;
			sprite->character->movie.queueFrameActions(this, sprite->mnFrame);
			sprite->mnGotoAnded = sprite->mnFrame;
		}
	events:
		if (!sprite->latched || isButton()) {
			if (rva006E1F90(2))
				((Rva006E2010Dispatcher *)this)->dispatch(2, g_00E17704, 1);
		}
		if (sprite->latched) {
			((Rva006E2010Dispatcher *)this)->dispatch(1, g_00E17704, 1);
			sprite->latched = 0;
		}
		((Rva006F7A30 *)&sprite->display)->rva006F7A30();
	} else if (isEditText()) {
		Rva006E1090Target *target = (Rva006E1090Target *)rva006E1090();
		target->list.rva006F7A30();
	}
}
