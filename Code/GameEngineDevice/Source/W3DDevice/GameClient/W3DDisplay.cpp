// ?rva000438CB@W3DDisplay@@QAEXXZ
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /I.
// ?rva000438CB@W3DDisplay@@QAEXXZ, retail 0x000438CB, 814 bytes including both switch tables.
// Complete native438CB..43BF9; code RET at43BAC followed by76B switch data.
// BFME1 reference cee35b7d8c supplies the rendering structure; native BFME2
// supplies the table extents, offsets and exact call relationships.
// W3DDisplay third debug page: 17 DisplayStrings at +0x234, each given a
// colour from the network and leave-status state, then color(c, black),
// place(3, y, 1, 1), size(&w, &h) and y += h. Rows 10..16 colour player
// leave-status lines (human / packet-router frame lag / defeat / victory),
// row 8 the frames behind the packet router, 9 and 7 the receive-age and
// router flags; the shared warning flag flips the blink phase on exit.
// Evidence (target): sibling rowed unit pair 0x0004387E (16 strings at
// +0x18C) and 0x00043BF9 (25 at +0x1D0) share the three DisplayString slots;
// rowed GameLogic::getPlayerLeaveStatus 0x0023D1E3; Network slots 0x8C/0xAC,
// 0xEC, 0xF8 read by this body. Donor (structure only, not target fact):
// BFME 1 W3DDisplayDrawThirdDebugDisplay006e8800.cpp; BFME 2 moves the frame
// counter to GameLogic +0x40, the string table to +0x234 and the five-frame
// receive window to LOGICFRAMES_PER_SECOND.
// Shared W3DDisplay unit view: one declaration of each class for every body
// retail built into this unit. Display slots follow the retail W3DDisplay
// vtable 0x007C3C80 (101 slots); unnamed slots are ABI padding.
typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;
typedef __int64 Int64;

struct Coord3D;
struct RGBColor;
class Image;
class VideoBuffer;
class Render2DClass;
class Rva006E8800DisplayString;

// Retail's lock calls are the BFME_DX8_Thread_Lock / BFME_DX8_Thread_Assert
// providers at 0x0011F520 / 0x00120F50.
void __cdecl BFME_DX8_Thread_Lock(void);
bool __cdecl BFME_DX8_Thread_Assert(void);

class BFMEDX8DeviceLock
{
public:
	// Keep the inline lock without emitting a competing constructor copy.
	__declspec(dllimport) __forceinline BFMEDX8DeviceLock(void)
	{
		BFME_DX8_Thread_Lock();
	}

	~BFMEDX8DeviceLock(void)
	{
		BFME_DX8_Thread_Assert();
	}
};

class Vector3
{
public:
	__declspec(dllimport) __forceinline Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
	float X;
	float Y;
	float Z;
};

class WW3D
{
public:
	static bool Set_Device_Resolution(int width, int height, int bits, int windowed, bool resize_window);
	static bool Begin_Render(bool clear, bool clearz, const Vector3 &color, float destAlpha);
	static bool End_Render(bool flipFrame);
};

class IDirect3DSurface9;
class DX8Caps;
class DX8Wrapper
{
public:
	static IDirect3DSurface9 *_Get_DX8_Front_Buffer();
	static const DX8Caps *Get_Current_Caps() { return CurrentCaps; }

protected:
	// The caps at 0x00DEDA7C (defined in dx8wrapper.cpp).
	static DX8Caps *CurrentCaps;
};

class GlobalData
{
public:
	unsigned char m_pad00[0x50];
	Int m_terrainLOD;			// +0x50
	bool m_54;				// +0x54
	unsigned char m_pad55[0x58 - 0x55];
	Int m_terrainLODTargetTimeMS;		// +0x58
	unsigned char m_pad5C[0xEA5 - 0x5C];
	bool m_delayBeforeCapture;		// +0xEA5
};

extern GlobalData *TheWritableGlobalData;

class RTS3DScene
{
public:
	void drawTerrainOnly(bool draw) { m_drawTerrainOnly = draw; }
private:
	unsigned char m_pad000[0x12C];
	bool m_drawTerrainOnly;			// +0x12C
};

class GameLODManager
{
public:
	char m_pad[0x1774];
	int m_detailVariant;		// +0x1774
};
extern GameLODManager *TheGameLODManager;

template <typename T> class StringBase
{
	void releaseBuffer();
	void *m_data;

public:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	void set(const StringBase<T> &src);
	void set(const T *str);
	void clear()
	{
		releaseBuffer();
	}
	void concat(const StringBase<T> &str);
private:
	friend class W3DDisplay;
	~StringBase() { releaseBuffer(); }
};

// Retail ordinary teardown calls releaseBuffer36410; return-value
// cleanup75D142 calls the five-byte private StringBase destructor48BA39.
// Keeping that destructor inline permits the worker call at ordinary
// exits while giving the EH return-value callback its actual wrapper.
// The friend grants access only for this address-named by-value ABI
// view; the original method return type remains unproven.

class Display
{
public:
	Display();
	virtual ~Display();	// slot 0
	virtual void init();	// slot 1
	virtual void slot02(); virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void reset();	// slot 9
	virtual void slot10(); virtual void slot11();
	virtual void draw();	// slot 12
	virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual UnsignedInt getWidth();	// slot 16
	virtual UnsignedInt getHeight();	// slot 17
	virtual void setBitDepth(UnsignedInt bitDepth);	// slot 18
	virtual UnsignedInt getBitDepth();	// slot 19
	virtual void setWindowed(Bool windowed);	// slot 20
	virtual Bool getWindowed();	// slot 21
	virtual Bool setDisplayMode(UnsignedInt xres, UnsignedInt yres, UnsignedInt bitdepth, Bool windowed);	// slot 22
	virtual void slot23(); virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual void slot27(); virtual void slot28(); virtual void slot29(); virtual void slot30();
	virtual void slot31(); virtual void slot32(); virtual void slot33();
	virtual StringBase<char> rva000481AA(const StringBase<char> &name);	// slot 34
	virtual void slot35(); virtual void slot36(); virtual void slot37();
	virtual void drawViews();	// slot 38
	virtual void slot39();
	virtual void updateViews();	// slot 40
	virtual VideoBuffer *createVideoBuffer(Bool allowAlpha);	// slot 41
	virtual void slot42(); virtual void slot43(); virtual void slot44(); virtual void slot45();
	virtual void slot46();
	virtual void createLightPulse(const Coord3D *position, const RGBColor *color, Real innerRadius, Real attenuationWidth, UnsignedInt increaseTime, UnsignedInt decayTime);	// slot 47
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51();
	virtual void slot52();
	virtual void beginImageDraw();	// slot 53
	virtual void slot54(); virtual void slot55(); virtual void slot56(); virtual void slot57();
	virtual void slot58(); virtual void slot59(); virtual void slot60(); virtual void slot61();
	virtual void slot62();
	virtual void drawImageCore(Image *image, Real x0, Real y0, Real x1, Real y1, Int color);	// slot 63
	virtual void endImageDraw();	// slot 64
	virtual void drawImage(Image *image, Real x0, Real y0, Real x1, Real y1, Int color);	// slot 65
	virtual void slot66(); virtual void slot67(); virtual void slot68(); virtual void slot69();
	virtual void slot70(); virtual void slot71(); virtual void slot72(); virtual void slot73();
	virtual void slot74(); virtual void slot75(); virtual void slot76(); virtual void slot77();
	virtual void slot78(); virtual void slot79(); virtual void slot80(); virtual void slot81();
	virtual void slot82(); virtual void slot83(); virtual void slot84(); virtual void slot85();
	virtual void slot86(); virtual void slot87(); virtual void slot88(); virtual void slot89();
	virtual void slot90(); virtual void slot91(); virtual void slot92(); virtual void slot93();
	virtual void slot94(); virtual void slot95(); virtual void slot96(); virtual void slot97();
	virtual void slot98(); virtual void slot99(); virtual void slot100();

protected:
	unsigned char m_pad004[0x144 - 0x04];
};

class W3DDisplay : public Display
{
public:
	virtual Bool setDisplayMode(UnsignedInt xres, UnsignedInt yres, UnsignedInt bitdepth, Bool windowed);
	virtual StringBase<char> rva000481AA(const StringBase<char> &name);
	virtual VideoBuffer *createVideoBuffer(Bool allowAlpha);
	virtual void createLightPulse(const Coord3D *position, const RGBColor *color, Real innerRadius, Real attenuationWidth, UnsignedInt increaseTime, UnsignedInt decayTime);
	virtual void drawImage(Image *image, Real x0, Real y0, Real x1, Real y1, Int color);

	void rva000438CB();
	void rva00043FB9();

	static RTS3DScene *m_3DScene;

protected:
	void calculateTerrainLOD(void);

private:
	void rva00045213(char *image, unsigned int rowBytes);

	unsigned char m_pad144[0x168 - 0x144];
	Render2DClass *m_render2D;		// +0x168
	unsigned char m_pad16C[0x180 - 0x16C];
	Real m_180;				// +0x180
	unsigned char m_pad184[0x234 - 0x184];
	Rva006E8800DisplayString *m_displayStrings[17];	// +0x234
};

class Rva006E8800DisplayString
{
public:
	virtual void slot00(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot0c(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot1c(void) = 0;
	virtual void slot20(void) = 0;
	virtual void slot24(void) = 0;
	virtual void color006e(int color, unsigned int dropColor) = 0;
	virtual void slot2c(void) = 0;
	virtual void slot30(void) = 0;
	virtual void slot34(void) = 0;
	virtual void place006e(int x, int y, int width, int height) = 0;
	virtual void size006e(int *width, int *height) = 0;
};

// The eight-record GameLogic status returned by the rowed getPlayerLeaveStatus
// 0x0023D1E3 (GameLogicSetPlayerLeaveStatus.cpp owns the layout). The overlay
// only reads the fields below.
struct PlayerLeaveStatus
{
	int status;
	int quitFrame;
	int defeatFrame;
	int victoryFrame;
	bool notPresent;
	char padding[3];
	int isHuman;
	char playerName[4];
};

#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"

// The slots used here are independently named by the BFME Network vtable at
// 0x0111A968: isPacketRouter (+0x8c), getFramesBehindPacketRouter (+0xcc),
// and getPlayerLatestFrame (+0xd8).  The intervening slots are deliberately
// unnamed ABI padding, not semantic wrappers.
class NetworkInterface
{
public:
	virtual void slot00(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot0c(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot1c(void) = 0;
	virtual void slot20(void) = 0;
	virtual void slot24(void) = 0;
	virtual void slot28(void) = 0;
	virtual void slot2c(void) = 0;
	virtual void slot30(void) = 0;
	virtual void slot34(void) = 0;
	virtual void slot38(void) = 0;
	virtual void slot3c(void) = 0;
	virtual void slot40(void) = 0;
	virtual void slot44(void) = 0;
	virtual void slot48(void) = 0;
	virtual void slot4c(void) = 0;
	virtual void slot50(void) = 0;
	virtual void slot54(void) = 0;
	virtual void slot58(void) = 0;
	virtual void slot5c(void) = 0;
	virtual void slot60(void) = 0;
	virtual void slot64(void) = 0;
	virtual void slot68(void) = 0;
	virtual void slot6c(void) = 0;
	virtual void slot70(void) = 0;
	virtual void slot74(void) = 0;
	virtual void slot78(void) = 0;
	virtual void slot7c(void) = 0;
	virtual void slot80(void) = 0;
	virtual void slot84(void) = 0;
	virtual void slot88(void) = 0;
	virtual void slot8c(void) = 0;
	virtual void slot90(void) = 0;
	virtual void slot94(void) = 0;
	virtual void slot98(void) = 0;
	virtual void slot9c(void) = 0;
	virtual void slota0(void) = 0;
	virtual void slota4(void) = 0;
	virtual void slota8(void) = 0;
	virtual bool isPacketRouter(void) = 0;
	virtual void slotb0(void) = 0;
	virtual void slotb4(void) = 0;
	virtual void slotb8(void) = 0;
	virtual void slotbc(void) = 0;
	virtual void slotc0(void) = 0;
	virtual void slotc4(void) = 0;
	virtual void slotc8(void) = 0;
	virtual void slotcc(void) = 0;
	virtual void slotd0(void) = 0;
	virtual void slotd4(void) = 0;
	virtual void slotd8(void) = 0;
	virtual void slotdc(void) = 0;
	virtual void slote0(void) = 0;
	virtual void slote4(void) = 0;
	virtual void slote8(void) = 0;
	virtual int getFramesBehindPacketRouter(void) = 0;
	virtual void slotf0(void) = 0;
	virtual void slotf4(void) = 0;
	virtual int getPlayerLatestFrame(int playerIndex) = 0;
};

extern NetworkInterface *TheNetwork;

extern GameLogic *TheGameLogic;

// Address-derived globals: the last-packet frame stamp and the blink phase
// byte flipped at the end of the page (same pair BFME 1 names 0x012F8054 /
// 0x012F81A9), and the runtime LOGICFRAMES_PER_SECOND at 0x00DBA4E4.
unsigned int BfmeNetworkRunAheadChangeFrame = 0;
unsigned char BfmeNetworkStatsBlink = 0;
extern int BfmeLogicFramesPerSecond;

void W3DDisplay::rva000438CB()
{
	int i;
	int y = 3;
	bool flip = false;
	int frame;
	PlayerLeaveStatus *player;
	int width;
	int height;

	for (i = 0; i < 17; ++i)
	{
		int color = -1;
		if (i >= 10 && i <= 16)
		{
			{
				NetworkInterface *network = TheNetwork;
				if (network == 0)
					continue;
			}

			int playerIndex = i - 9;
			player = TheGameLogic->getPlayerLeaveStatus(playerIndex);
			if (player->notPresent)
				continue;

			if (player->isHuman == 1)
			{
				color = 0xffc8a0e1;
			}
			else if (TheNetwork->isPacketRouter())
			{
				int currentFrame = TheGameLogic->getFrame();
				frame = TheNetwork->getPlayerLatestFrame(playerIndex);
				frame += 10 - currentFrame;
				switch (frame)
				{
				case 8: color = 0xffffffa0; break;
				case 7: color = 0xffa0ffa0; break;
				case 5:
				case 6: color = 0xffa0a0ff; break;
				case 4: color = 0xff9696ff; break;
				case 3: color = 0xff8c8cff; break;
				case 2: color = 0xff8282ff; break;
				case 1: color = 0xff7878ff; break;
				case 0: color = 0xff6e6eff; break;
				default:
					color = BfmeNetworkStatsBlink ? -1 : 0xffff0000;
					flip = true;
					break;
				}
			}
			else
			{
				color = 0xffc8c8a0;
			}

			if (player->status != 0)
				color = 0xc8a06464;
			else if (player->isHuman == 0)
			{
				if (player->victoryFrame != 0)
					color = 0xff64c8c8;
				else if (player->defeatFrame != 0)
					color = 0xffc89664;
			}
			else if (player->isHuman == 1)
			{
				if (player->victoryFrame != 0)
					color = 0xffdca0ff;
				else if (player->defeatFrame != 0)
					color = 0xff9664af;
			}
		}
		else
		{
			if (i == 8)
			{
				if (TheNetwork != 0 && !TheNetwork->isPacketRouter())
				{
					switch (TheNetwork->getFramesBehindPacketRouter())
					{
					case 1: color = 0xffffffa0; break;
					case 2: color = 0xffa0ffa0; break;
					case 3:
					case 4: color = 0xffa0a0ff; break;
					case 5: color = 0xff9696ff; break;
					case 6: color = 0xff8c8cff; break;
					case 7: color = 0xff8282ff; break;
					case 8: color = 0xff7878ff; break;
					case 9: color = 0xff6e6eff; break;
					case 0:
						if (BfmeNetworkRunAheadChangeFrame + BfmeLogicFramesPerSecond <
							(unsigned int)TheGameLogic->getFrame())
							color = 0xffff0000;
						else
						{
							color = BfmeNetworkStatsBlink ? -1 : 0xffff0000;
							flip = true;
						}
						break;
					default:
						color = BfmeNetworkStatsBlink ? -1 : 0xffff0000;
						flip = true;
						break;
					}
				}
				else
				{
					color = -1;
				}
			}
			else if (i == 9)
			{
				if (BfmeNetworkRunAheadChangeFrame + BfmeLogicFramesPerSecond <
					(unsigned int)TheGameLogic->getFrame())
					color = -1;
				else
					color = BfmeNetworkStatsBlink ? -1 : 0xffff0000;
			}
			else if (i == 7)
			{
				if (TheNetwork != 0 && TheNetwork->isPacketRouter())
					color = 0xffc8c8ff;
				else
					color = 0xffffc8c8;
			}
			else
			{
				color = -1;
			}
		}

		m_displayStrings[i]->color006e(color, 0xff000000u);
		m_displayStrings[i]->place006e(3, y, 1, 1);
		m_displayStrings[i]->size006e(&width, &height);
		y += height;
	}

	if (flip)
		BfmeNetworkStatsBlink = BfmeNetworkStatsBlink ? 0 : 1;
}

// Concurrent letterbox recovery retained from origin/master.
// ?rva00044018@Rva00044018@@QAEXI@Z
// Original letterbox settings: /O1 /G7 /arch:SSE /MD; shared settings above.
// Rva00044018::rva00044018, retail 0x00044018 (479 B): the fade/letterbox bar
// update on the rowed bar painter 0x0004263F (callers at 0x0004A913). While
// the +0xD8 flag is set the bars grow in: progress (+0xD4) rises over
// 1000 ms from the start time (+0xDC) to 1, and the top and bottom bars of a
// 16:9 frame inside the +0x0C x +0x10 viewport are drawn with that alpha; with
// the flag clear they fade back out to 0 (top bar only) and the flag-off state
// ends there. Constants are compiler literals (1.0f, 0.001f, 255, 0.5625f,
// 0.5f); unsigned dimensions convert through x87 as retail does. Names are
// structural. Semantic donor: BFME1 cee35b7d8ca077d7255f1c39cb69e9fd9627aa85,
// game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplay.cpp:1794,
// W3DDisplay::renderLetterBox. The caller, fields, branches, constants and
// complete native 44018..441F7 body support that role; original target
// member spelling is not independently named, so the bank's neutral name stays.

class Rva0004263F
{
	virtual void slot00();
public:
	void rva0004263F(float x0, float y0, float x1, float y1, int color);	// 0x0004263F
};

class Rva00044018 : public Rva0004263F
{
	char m_pad04[8];
	unsigned int m_width;		// +0x0C
	unsigned int m_height;		// +0x10
	char m_pad14[0xD4 - 0x14];
	float m_progress;			// +0xD4
	unsigned char m_fadingIn;	// +0xD8
	char m_padD9[3];
	unsigned int m_startTime;	// +0xDC
public:
	void rva00044018(unsigned int now);
};

// Retail uses the single-precision 255.0f literal at VA 0x00BC2900 in
// an x87 multiply before _ftol2. Volatile reference reads prevent VC7.1
// from replacing that sequence with SSE conversion or a double literal.
static const volatile float letterboxAlphaScale = 255.0f;
inline double scaleLetterboxAlpha(const volatile float &progress)
{
    return (double)progress * letterboxAlphaScale;
}

void Rva00044018::rva00044018(unsigned int now)
{
	if (m_fadingIn)
	{
		if (m_progress != 1.0f)
		{
			now -= m_startTime;
			float f = (float)now * 0.001f;
			m_progress = f;
			if (f > 1.0f)
				m_progress = 1.0f;
		}
		int alpha = (int)scaleLetterboxAlpha(m_progress) << 24;
		rva0004263F(0.0f, 0.0f, (float)m_width, ((float)m_height - (float)m_width * 0.5625f) * 0.5f, alpha);
		rva0004263F(0.0f, (float)m_height - ((float)m_height - (float)m_width * 0.5625f) * 0.5f, (float)m_width, (float)m_height, alpha);
	}
	else if (m_progress != 0.0f)
	{
		now -= m_startTime;
		float f = 1.0f - (float)now * 0.001f;
		m_progress = f;
		if (f < 0.0f)
			m_progress = 0.0f;
		rva0004263F(0.0f, 0.0f, (float)m_width, ((float)m_height - (float)m_width * 0.5625f) * 0.5f, (int)scaleLetterboxAlpha(m_progress) << 24);
	}
	else
	{
		m_fadingIn = 0;
	}
}
