// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /arch:SSE /G7 /ICode/GameEngine/Source/Common /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// ?rva000982F9@Gen006E2310@@QAEXXZ retail 0x000982F9, 382 bytes: slot 10 of
// Gen006E2310's vtable 0x00BC8208 (slot 0 is its scalar deleting dtor
// 0x000982DD), the object the game client factory 0x0004C62D builds over
// the CloudEffect record class Rva009519B. Once per client frame it follows
// the global weather system's +0x10 state into its own +0xBC/+0xC0 pair
// (re-reading the cloud settings through virtual slot 14, 0x00214F14, when
// the state turns to 1), drops a pending light change at +0xC8 when the
// weather system's 0x003182CD check fails (restoring the scene light from
// +0xE0 and the shadow colour from +0xF8 when the record's +0x5C flag is
// set, then resetting the scene through 0x0006E605), steps the +0xC4 fade
// level down to 0 or up to 0xFF while the 0x00DB47EC mode is 2, and ends in
// the cloud/thunder update 0x000953B3.
//
// Its own unit, not Gen006E2310Ctor.cpp: that unit links today, and the two
// unrowed callees 0x0006E605 and 0x000953B3 (pinned) would stop it linking.
//
// Target facts: boundary, vtable slot, callees, globals, member offsets and
// store order are from retail. The member names and the method name are
// address-derived; the receivers of 0x0006E5C8 and 0x0006E605 are the scene
// pointer W3DDisplay::m_3DScene (VA 0x00DE1B34) that each call loads into ecx.

#include "ascii_string.h"

#include "../../Include/GameClient/GameClientClass.h"
extern GameClient *TheGameClient;

// The weather system's check 0x003182CD, rowed under an address-derived owner.
class Rva003182CD
{
public:
	unsigned char rva003182CD();
};

// The weather system's state word at +0x10.
class GlobalWeatherSystem
{
public:
	char m_pad[0x10];
	int m_state;
};
extern GlobalWeatherSystem *TheGlobalWeatherSystem;

#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/W3DShadowManager.h"
extern W3DShadowManager *TheW3DShadowManager;

#include "../../../Libraries/Source/WWVegas/WWMath/Vector3Data.h"

#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/RTS3DScene.h"

#include "../../../Libraries/Include/Lib/Coord3D.h"

#include "../../../Libraries/Include/Lib/Region3D.h"

// TheTerrainLogic's slot 8 is the map extent.
#include "../../Include/GameLogic/TerrainLogic.h"
extern TerrainLogic *TheTerrainLogic;

// TheTerrainRenderObject's slot 137, handed 0 every tenth frame of a fade.
class BaseHeightMapRenderObjClass
{
public:
	virtual void slot000(); virtual void slot001(); virtual void slot002(); virtual void slot003();
	virtual void slot004(); virtual void slot005(); virtual void slot006(); virtual void slot007();
	virtual void slot008(); virtual void slot009(); virtual void slot010(); virtual void slot011();
	virtual void slot012(); virtual void slot013(); virtual void slot014(); virtual void slot015();
	virtual void slot016(); virtual void slot017(); virtual void slot018(); virtual void slot019();
	virtual void slot020(); virtual void slot021(); virtual void slot022(); virtual void slot023();
	virtual void slot024(); virtual void slot025(); virtual void slot026(); virtual void slot027();
	virtual void slot028(); virtual void slot029(); virtual void slot030(); virtual void slot031();
	virtual void slot032(); virtual void slot033(); virtual void slot034(); virtual void slot035();
	virtual void slot036(); virtual void slot037(); virtual void slot038(); virtual void slot039();
	virtual void slot040(); virtual void slot041(); virtual void slot042(); virtual void slot043();
	virtual void slot044(); virtual void slot045(); virtual void slot046(); virtual void slot047();
	virtual void slot048(); virtual void slot049(); virtual void slot050(); virtual void slot051();
	virtual void slot052(); virtual void slot053(); virtual void slot054(); virtual void slot055();
	virtual void slot056(); virtual void slot057(); virtual void slot058(); virtual void slot059();
	virtual void slot060(); virtual void slot061(); virtual void slot062(); virtual void slot063();
	virtual void slot064(); virtual void slot065(); virtual void slot066(); virtual void slot067();
	virtual void slot068(); virtual void slot069(); virtual void slot070(); virtual void slot071();
	virtual void slot072(); virtual void slot073(); virtual void slot074(); virtual void slot075();
	virtual void slot076(); virtual void slot077(); virtual void slot078(); virtual void slot079();
	virtual void slot080(); virtual void slot081(); virtual void slot082(); virtual void slot083();
	virtual void slot084(); virtual void slot085(); virtual void slot086(); virtual void slot087();
	virtual void slot088(); virtual void slot089(); virtual void slot090(); virtual void slot091();
	virtual void slot092(); virtual void slot093(); virtual void slot094(); virtual void slot095();
	virtual void slot096(); virtual void slot097(); virtual void slot098(); virtual void slot099();
	virtual void slot100(); virtual void slot101(); virtual void slot102(); virtual void slot103();
	virtual void slot104(); virtual void slot105(); virtual void slot106(); virtual void slot107();
	virtual void slot108(); virtual void slot109(); virtual void slot110(); virtual void slot111();
	virtual void slot112(); virtual void slot113(); virtual void slot114(); virtual void slot115();
	virtual void slot116(); virtual void slot117(); virtual void slot118(); virtual void slot119();
	virtual void slot120(); virtual void slot121(); virtual void slot122(); virtual void slot123();
	virtual void slot124(); virtual void slot125(); virtual void slot126(); virtual void slot127();
	virtual void slot128(); virtual void slot129(); virtual void slot130(); virtual void slot131();
	virtual void slot132(); virtual void slot133(); virtual void slot134(); virtual void slot135();
	virtual void slot136();
	virtual void slot137(int arg);
};
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

class Matrix3D;
class FXList
{
public:
	static void doFXPos(const FXList *fx, const Coord3D *primary, const Matrix3D *primaryMtx,
		float primarySpeed, const Coord3D *secondary);
};

#include "../../Include/GameClient/FXListStore.h"
extern FXListStore *TheFXListStore;

#include "../../../Libraries/Source/WWVegas/WWMath/WWMathClass.h"

#include "../../Include/GameClient/GameClientRandomVariable.h"

// The record's colour triples, as the CloudEffect constructor zeroes them.
#include "../../../Libraries/Include/Lib/RGBColor.h"

// Address-derived helpers of the record, rowed under their own owners.
class Rva002153C7
{
public:
	Coord3D *rva002153C7(Coord3D *out);
};
class Rva00214D59
{
public:
	int rva00214D59();
};
class Rva00095224AsciiField
{
public:
	AsciiString get() const;
};

class W3DDisplay
{
public:
	static RTS3DScene *m_3DScene;
};

extern int g_Va00DB47EC;

// The CloudEffect record class (Rva009519BCtor.cpp), only as a base here;
// the +0x5C byte is the one this body tests.
class Rva009519B
{
public:
	virtual ~Rva009519B();
	// Slot 14, 0x00214F14 (Rva00214F14Init.cpp), as the call reaches it.
	virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
	virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08();
	virtual void v09(); virtual void v10(); virtual void v11(); virtual void v12();
	virtual void v13();
	virtual void rva00214F14();
protected:
	unsigned char m_04[0x30 - 4];
	RGBColor m_30;
	RGBColor m_3C;
	unsigned char m_48[0x5C - 0x48];
	unsigned char m_5C;
	float m_60;
	unsigned char m_64[0x74 - 0x64];
	GameClientRandomVariable m_74;
	float m_80;
	GameClientRandomVariable m_84;
	unsigned char m_90;
	unsigned char m_91;
	unsigned char m_92[0xBC - 0x92];
};

struct Gen006E2310Triple
{
	void Set(float x, float y, float z)
	{
		X = x;
		Y = y;
		Z = z;
	}

	float X;
	float Y;
	float Z;
};

class Gen006E2310 : public Rva009519B
{
public:
	void rva000982F9();
	void rva000953B3();

private:
	int m_BC;
	int m_C0;
	int m_C4;
	bool m_C8;
	int m_CC;
	float m_D0;
	Gen006E2310Triple m_D4;
	Gen006E2310Triple m_E0;
	Gen006E2310Triple m_EC;
	unsigned int m_F8;
	const FXList *m_FC;
	int m_100;
	int m_104;
};

void Gen006E2310::rva000982F9()
{
	int frame = TheGameClient->getFrame();
	bool sameFrame = false;
	if (m_100 == frame)
		sameFrame = true;
	m_100 = frame;
	if (sameFrame)
		return;

	int state = TheGlobalWeatherSystem->m_state;
	if (state == 1) {
		if (m_BC != 1) {
			rva00214F14();
			m_C0 = 1;
			m_BC = 1;
		}
	} else if (m_BC == 1) {
		m_C0 = 3;
		m_BC = state;
	}

	unsigned char keep = TheGlobalWeatherSystem ? ((Rva003182CD *)TheGlobalWeatherSystem)->rva003182CD() : 0;
	if (!keep && m_C8) {
		m_C8 = false;
		m_CC = 0;
		m_D0 = 0.0f;
		m_104 = 0;
		m_D4.Set(0.0f, 0.0f, 0.0f);
		if (m_5C) {
			W3DDisplay::m_3DScene->rva0006E5C8((Vector3 *)&m_E0);
			if (TheW3DShadowManager)
				TheW3DShadowManager->m_shadowColor = m_F8;
		}
		W3DDisplay::m_3DScene->rva0006E605((Vector3 *)&m_EC, true);
		m_E0.Set(0.0f, 0.0f, 0.0f);
		m_EC.Set(0.0f, 0.0f, 0.0f);
	}

	if (g_Va00DB47EC == 2) {
		if (m_C0 == 1) {
			if (--m_C4 <= 0) {
				m_C4 = 0;
				m_C0 = 2;
			}
		} else if (m_C0 == 3) {
			if (++m_C4 >= 0xff) {
				m_C4 = 0xff;
				m_C0 = 0;
			}
		}
	}
	rva000953B3();
}

// ?rva000953B3@Gen006E2310@@QAEXXZ retail 0x000953B3, 1134 bytes: the
// cloud and thunder update the per-frame follow 0x000982F9 ends in. In state
// 2 a passing 0x003182CD check either runs a flash (the +0xCC countdown holds
// the scene colour at the record's +0x30 or +0x3C triple, re-rolls the flash
// strength from +0x84 capped at 0.9 when +0x91 is set, and on the +0x80
// chance relights through 0x002153C7 when +0x5C is set; at zero the scene
// light, shadow colour and strength are restored) or, on the +0x60 chance
// more than three times over, starts one: a length from +0x74, a strength
// from +0x84, the current light saved into +0xE0 and the shadow colour into
// +0xF8 before both are replaced, and the record's FX list (looked up once by
// name) played at the middle of the map. Other states fade the colour by the
// +0xC4 level and poke the terrain every tenth frame.
void Gen006E2310::rva000953B3()
{
	int state = m_C0;
	if (state == 0)
		return;
	float value;
	RGBColor color;
	if (state == 2) {
		color = m_30;
		if (m_BC == state)
			color = m_3C;
		unsigned char active = TheGlobalWeatherSystem ? ((Rva003182CD *)TheGlobalWeatherSystem)->rva003182CD() : 0;
		if (active) {
			if (m_C8) {
				m_D4.Set(color.red, color.green, color.blue);
				if (--m_CC <= 0) {
					m_C8 = false;
					m_CC = 0;
					m_D0 = 0.0f;
					m_104 = 0;
					m_D4.Set(0.0f, 0.0f, 0.0f);
					if (m_5C) {
						W3DDisplay::m_3DScene->rva0006E5C8((Vector3 *)&m_E0);
						if (TheW3DShadowManager)
							TheW3DShadowManager->m_shadowColor = m_F8;
					}
					W3DDisplay::m_3DScene->rva0006E605((Vector3 *)&m_EC, true);
					m_E0.Set(0.0f, 0.0f, 0.0f);
					m_EC.Set(0.0f, 0.0f, 0.0f);
					return;
				}
				if (m_91) {
					m_D0 = m_84.getValue();
					if (m_D0 > 0.9)
						m_D0 = 0.9f;
					W3DDisplay::m_3DScene->rva0006E605((Vector3 *)&m_EC, true);
					m_EC.Set(m_D0, m_D0, m_D0);
					W3DDisplay::m_3DScene->rva0006E605((Vector3 *)&m_EC, false);
				}
				if (m_90) {
					value = m_80;
					if (value > WWMath::Random_Float() && m_5C) {
						((Rva002153C7 *)this)->rva002153C7((Coord3D *)&color);
						W3DDisplay::m_3DScene->rva0006E5C8((Vector3 *)&color);
					}
				}
				return;
			}
			float roll = WWMath::Random_Float();
			float threshold = m_60;
			if (threshold > roll && ++m_104 > 3) {
				m_C8 = true;
				m_CC = (int)m_74.getValue();
				m_D0 = m_84.getValue();
				if (m_D0 > 0.9)
					m_D0 = 0.9f;
				m_EC.Set(m_D0, m_D0, m_D0);
				if (m_5C) {
					W3DDisplay::m_3DScene->rva0006E5A0((Vector3 *)&m_E0);
					Coord3D flash;
					((Rva002153C7 *)this)->rva002153C7(&flash);
					W3DDisplay::m_3DScene->rva0006E5C8((Vector3 *)&flash);
					if (TheW3DShadowManager) {
						m_F8 = TheW3DShadowManager->m_shadowColor;
						TheW3DShadowManager->m_shadowColor = ((Rva00214D59 *)this)->rva00214D59();
					}
				}
				W3DDisplay::m_3DScene->rva0006E605((Vector3 *)&m_EC, false);
				if (!m_FC) {
					AsciiString name = ((Rva00095224AsciiField *)this)->get();
					if (!name.isEmpty())
						m_FC = TheFXListStore->findFXList(name.str());
				}
				if (m_FC) {
					Region3D extent;
					TheTerrainLogic->getExtent(&extent);
					Coord3D pos;
					pos.x = (extent.lo.x + extent.hi.x) * 0.5f;
					pos.y = (extent.lo.y + extent.hi.y) * 0.5f;
					pos.z = 0.0f;
					FXList::doFXPos(m_FC, &pos, 0, 0.0f, 0);
				}
			}
		}
		m_D4.X = color.red;
		m_D4.Y = color.green;
		m_D4.Z = color.blue;
	} else {
		color = m_30;
		float fade = (float)(1.0 - m_C4 * (1.0 / 255.0));
		if (m_BC == 2)
			color = m_3C;
		m_D4.X = ((volatile RGBColor &)color).red * fade;
		m_D4.Y = ((volatile RGBColor &)color).green * fade;
		m_D4.Z = ((volatile RGBColor &)color).blue * fade;
		if (TheGameClient->getFrame() % 10 == 0)
			TheTerrainRenderObject->slot137(0);
	}
}
