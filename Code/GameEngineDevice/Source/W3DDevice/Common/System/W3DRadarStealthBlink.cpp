// cl: /D__PLACEMENT_VEC_NEW_INLINE /FIzh_ascii.h /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/sweep_bfme1_outofline /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Include/Lib /ICode/Libraries/Include /Ireference/shims/moduledata /Ireference/shims/subsystem_bfme2
// stlport
// ?rva0004E704@@YA_NPAVObject@@PAH@Z  Native 0x0004E704..0x0004E7D2 (206 bytes)
// Radar stealth blink for one object: unless the object passes the rowed
// Object query 0x002943B2 (null player) or is disguised (0x0028F4BC record with
// a template at +0x3C) a foreign object that fails rva002933CD and status 0x11
// is hidden (returns false); otherwise the colour alpha pulses between 64 and
// 255 over 2 * BfmeClientFramesPerSecond client frames (TheGameClient slot 0x7C).
// Same shape as the BFME1 W3DRadar cold path rva006C42B0 (donor f98983a7d).
// Static helper with a private convention: its retail caller 0x00050125 (W3DRadar
// object-list render) passes the object in EDI and the colour pointer in EBX.
// The caller tests only AL of rva002933CD so the int row is read as a byte.
#include "always.h"
#undef W3DMPO_GLUE
#define W3DMPO_GLUE(ARGCLASS)
#define Matrix4x4 Matrix4  // BFME renamed it
#include "Common/PlayerList.h"
#include "GameLogic/Object.h"
#include "W3DDevice/Common/W3DRadar.h"

// BFME's offset of the local player, reached through the real ThePlayerList. The inline
// helper is what gives the static below retail's object in EDI and colour in EBX.
class W3DRadarPlayerListView
{
public:
	Player *bfme_local_player() { return m_local; }
	char m_pad00[0x10];
	Player *m_local; // +0x10
};
class Rva00373EC6 { public: char m_pad00[0x3c]; const ThingTemplate *m_template; };
static const ObjectStatusTypes OBJECT_STATUS_BFME_17 = static_cast<ObjectStatusTypes>(0x11);

class BeaconClientFrame
{
public:
#define SLOT(N) virtual void slot##N();
    SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6)
    SLOT(7) SLOT(8) SLOT(9) SLOT(10) SLOT(11) SLOT(12)
    SLOT(13) SLOT(14) SLOT(15) SLOT(16) SLOT(17) SLOT(18)
    SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23) SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30)
#undef SLOT
    virtual unsigned getFrame();
};

class GameClient;
extern GameClient *TheGameClient;
extern int BfmeClientFramesPerSecond;

static Bool rva0004E704(Object *object, Color *color)
{
	if (object->rva002943B2(0))
	{
		Rva00373EC6 *disguise = object->rva0028F4BC();
		if (disguise == 0 || disguise->m_template == 0)
		{
			if (object->getControllingPlayer() != ((W3DRadarPlayerListView *)ThePlayerList)->bfme_local_player() &&
				!(UnsignedByte)object->rva002933CD() && !object->testStatus(OBJECT_STATUS_BFME_17))
				return false;

			UnsignedByte red, green, blue, alpha;
			GameGetColorComponents(*color, &red, &green, &blue, &alpha);
			const UnsignedInt halfTransition = BfmeClientFramesPerSecond;
			UnsignedInt frame = reinterpret_cast<BeaconClientFrame *>(TheGameClient)->getFrame() % (halfTransition * 2);
			if (frame >= halfTransition)
				alpha = (UnsignedByte)(255 - ((frame - halfTransition) * 191) / halfTransition);
			else
				alpha = (UnsignedByte)(64 + (frame * 191) / halfTransition);
			*color = GameMakeColor(red, green, blue, alpha);
		}
	}
	return true;
}

// ?rva0004E704Caller absent-from-retail
Int rva0004E704Caller(RadarObject *const *objects, Int count, Color *colors)
{
	Int drawn = 0;
	for (Int i = 0; i < count; ++i)
	{
		Object *obj = objects[i]->friend_getObject();
		Color c = colors[i];
		if (rva0004E704(obj, &c))
			drawn += c;
	}
	return drawn;
}
