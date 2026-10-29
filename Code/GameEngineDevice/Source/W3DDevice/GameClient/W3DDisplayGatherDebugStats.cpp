// cl: /O1 /arch:SSE /G7 /MD /EHsc
// W3DDisplay::gatherDebugStats, retail 0x0004826C..0x00049271 (4101 bytes).
// Zero Hour W3DDisplay::gatherDebugStats is the semantic guide (WB 0x967A20 is the
// _INTERNAL build, which picks the drawable under the mouse instead). The release
// moused-over lookup is spelled once per RMB arm: retail's stack packing needs the
// two definitions of draw (weight 3 at StackPacking) that c2 tail-merges afterwards
// into the single block at +0x8EE; the single-lookup Zero Hour form packs draw one
// slot off. Behaviour is identical on both paths (concat, then the lookup).

typedef unsigned short WChar;

#include "../../../../../reference/shims/bfme2_ascii/string_base.h"
#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../../../../reference/shims/bfme2_ascii/unicode_string.h"
#define W(s) ((const WChar *)L##s)

#include "../../../../Libraries/Include/Lib/Coord3D.h"
enum PathfindLayerEnum { LAYER_INVALID = 0 };
class GameFont;
class FontLibrary
{
public:
	GameFont *getFont(const AsciiString *name, float pointSize, bool bold);
};
struct MouseIO { int x, y; char m_pad8[0x18 - 8]; int leftState; char m_pad1c[0x24 - 0x1C]; int rightState; char m_pad28[0x30 - 0x28]; int middleState; };
class Drawable;
struct BodyView { virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C(); virtual float getHealth(); };

struct DisplayString
{
	virtual void v000();
	virtual void setText(UnicodeString text);
	virtual void v008();
	virtual void v00C();
	virtual void v010();
	virtual void v014();
	virtual void setFont(GameFont *font);
};

class DisplayStringManager
{
public:
	virtual void v000();
	virtual void v004();
	virtual void v008();
	virtual void v00C();
	virtual void v010();
	virtual void v014();
	virtual void v018();
	virtual void v01C();
	virtual void v020();
	virtual void v024();
	virtual void v028();
	virtual void v02C();
	virtual void v030();
	virtual void v034();
	virtual DisplayString *newDisplayString();
};

class InGameUI
{
public:
	void rva002A4A68();
	virtual void v000();
	virtual void v004();
	virtual void v008();
	virtual void v00C();
	virtual void v010();
	virtual void v014();
	virtual void v018();
	virtual void v01C();
	virtual void v020();
	virtual void v024();
	virtual void v028();
	virtual void v02C();
	virtual void v030();
	virtual void v034();
	virtual void v038();
	virtual void v03C();
	virtual void v040();
	virtual void v044();
	virtual void v048();
	virtual void v04C();
	virtual void v050();
	virtual void v054();
	virtual void v058();
	virtual void v05C();
	virtual void v060();
	virtual void v064();
	virtual void v068();
	virtual void v06C();
	virtual void v070();
	virtual void v074();
	virtual void v078();
	virtual void v07C();
	virtual void v080();
	virtual void v084();
	virtual void v088();
	virtual void v08C();
	virtual void v090();
	virtual void v094();
	virtual void v098();
	virtual void v09C();
	virtual void v0A0();
	virtual void v0A4();
	virtual void v0A8();
	virtual void v0AC();
	virtual void v0B0();
	virtual void v0B4();
	virtual void v0B8();
	virtual void v0BC();
	virtual void v0C0();
	virtual void v0C4();
	virtual void v0C8();
	virtual void v0CC();
	virtual void v0D0();
	virtual void v0D4();
	virtual void v0D8();
	virtual void v0DC();
	virtual void v0E0();
	virtual void v0E4();
	virtual void v0E8();
	virtual void v0EC();
	virtual void v0F0();
	virtual void v0F4();
	virtual void v0F8();
	virtual void v0FC();
	virtual void v100();
	virtual void v104();
	virtual void v108();
	virtual void v10C();
	virtual void v110();
	virtual void v114();
	virtual int getSelectCount();
	virtual void v11C();
	virtual void v120();
	virtual void v124();
	virtual void v128();
	virtual Drawable *getFirstSelectedDrawable();
	virtual void v130();
	virtual void v134();
	virtual void v138();
	virtual void v13C();
	virtual void v140();
	virtual void v144();
	virtual void v148();
	virtual void v14C();
	virtual void v150();
	virtual void v154();
	virtual void v158();
	virtual void v15C();
	virtual void v160();
	virtual void v164();
	virtual void v168();
	virtual void v16C();
	virtual void v170();
	virtual int getMousedOverDrawableID();
};

class GameClient
{
public:
	virtual void v000();
	virtual void v004();
	virtual void v008();
	virtual void v00C();
	virtual void v010();
	virtual void v014();
	virtual void v018();
	virtual void v01C();
	virtual void v020();
	virtual void v024();
	virtual void v028();
	virtual void v02C();
	virtual void v030();
	virtual void v034();
	virtual void v038();
	virtual void v03C();
	virtual Drawable *findDrawableByID(int id);
	char m_pad[0xC4 - 4]; int m_onScreenObjectCount;
};

class View
{
public:
	virtual void v000();
	virtual void v004();
	virtual void v008();
	virtual void v00C();
	virtual void v010();
	virtual void v014();
	virtual void v018();
	virtual void v01C();
	virtual void v020();
	virtual void v024();
	virtual void v028();
	virtual void v02C();
	virtual void v030();
	virtual void v034();
	virtual void v038();
	virtual void v03C();
	virtual void v040();
	virtual void v044();
	virtual void v048();
	virtual void v04C();
	virtual void v050();
	virtual void v054();
	virtual void v058();
	virtual void v05C();
	virtual void v060();
	virtual void v064();
	virtual void v068();
	virtual void v06C();
	virtual void v070();
	virtual void v074();
	virtual void v078();
	virtual void v07C();
	virtual void v080();
	virtual void v084();
	virtual void v088();
	virtual void v08C();
	virtual void v090();
	virtual void v094();
	virtual void v098();
	virtual void v09C();
	virtual void v0A0();
	virtual void v0A4();
	virtual void v0A8();
	virtual void v0AC();
	virtual void v0B0();
	virtual void v0B4();
	virtual void v0B8();
	virtual void v0BC();
	virtual void v0C0();
	virtual void v0C4();
	virtual void v0C8();
	virtual void v0CC();
	virtual void v0D0();
	virtual void v0D4();
	virtual void v0D8();
	virtual void v0DC();
	virtual void v0E0();
	virtual void v0E4();
	virtual void v0E8();
	virtual void v0EC();
	virtual void v0F0();
	virtual void v0F4();
	virtual void v0F8();
	virtual void v0FC();
	virtual float getAngle();
	virtual void v104();
	virtual void v108();
	virtual void v10C();
	virtual void v110();
	virtual void v114();
	virtual void getPosition(Coord3D *pos);
	virtual void v11C();
	virtual void v120();
	virtual float getZoom();
	virtual void v128();
	virtual void v12C();
	virtual void v130();
	virtual void v134();
	virtual void v138();
	virtual void v13C();
	virtual void v140();
	virtual void v144();
	virtual float getTerrainHeightUnderCamera();
	virtual void v14C();
	virtual float getHeightAboveGround();
	virtual void v154();
	virtual void v158();
	virtual float getFieldOfView();
	virtual void v160();
	virtual void v164();
	virtual void screenToTerrain(const MouseIO *screen, Coord3D *world, int flag);
	virtual void v16C();
	virtual void v170();
	virtual void v174();
	virtual void v178();
	virtual void v17C();
	virtual void v180();
	virtual void v184();
	virtual void v188();
	virtual void v18C();
	virtual void v190();
	virtual void v194();
	virtual void v198();
	virtual void v19C();
	virtual void v1A0();
	virtual void v1A4();
	virtual void v1A8();
	virtual void v1AC();
	virtual float getPitch2();
	virtual void v1B4();
	virtual void v1B8();
	virtual void v1BC();
	virtual void v1C0();
	virtual void v1C4();
	virtual void v1C8();
	virtual void v1CC();
	virtual void v1D0();
	virtual void v1D4();
	virtual void v1D8();
	virtual void v1DC();
	virtual void v1E0();
	virtual void v1E4();
	virtual void v1E8();
	virtual void v1EC();
	virtual void v1F0();
	virtual void v1F4();
	virtual void v1F8();
	virtual void v1FC();
	virtual void v200();
	virtual void v204();
	virtual void v208();
	virtual void v20C();
	virtual void v210();
	virtual void v214();
	virtual void v218();
	virtual void v21C();
	virtual void v220();
	virtual void v224();
	virtual void v228();
	virtual float getPitch();
};

class TerrainRenderObject
{
public:
	virtual void v000();
	virtual void v004();
	virtual void v008();
	virtual void v00C();
	virtual void v010();
	virtual void v014();
	virtual void v018();
	virtual void v01C();
	virtual void v020();
	virtual void v024();
	virtual void v028();
	virtual void v02C();
	virtual void v030();
	virtual void v034();
	virtual void v038();
	virtual void v03C();
	virtual void v040();
	virtual void v044();
	virtual void v048();
	virtual void v04C();
	virtual void v050();
	virtual void v054();
	virtual void v058();
	virtual void v05C();
	virtual void v060();
	virtual void v064();
	virtual void v068();
	virtual void v06C();
	virtual void v070();
	virtual void v074();
	virtual void v078();
	virtual void v07C();
	virtual void v080();
	virtual void v084();
	virtual void v088();
	virtual void v08C();
	virtual void v090();
	virtual void v094();
	virtual void v098();
	virtual void v09C();
	virtual void v0A0();
	virtual void v0A4();
	virtual void v0A8();
	virtual void v0AC();
	virtual void v0B0();
	virtual void v0B4();
	virtual void v0B8();
	virtual void v0BC();
	virtual void v0C0();
	virtual void v0C4();
	virtual void v0C8();
	virtual void v0CC();
	virtual void v0D0();
	virtual void v0D4();
	virtual void v0D8();
	virtual void v0DC();
	virtual void v0E0();
	virtual void v0E4();
	virtual void v0E8();
	virtual void v0EC();
	virtual void v0F0();
	virtual void v0F4();
	virtual void v0F8();
	virtual void v0FC();
	virtual void v100();
	virtual void v104();
	virtual void v108();
	virtual void v10C();
	virtual void v110();
	virtual void v114();
	virtual void v118();
	virtual void v11C();
	virtual void v120();
	virtual void v124();
	virtual void v128();
	virtual void v12C();
	virtual void v130();
	virtual void v134();
	virtual void v138();
	virtual void v13C();
	virtual void v140();
	virtual void v144();
	virtual void v148();
	virtual void v14C();
	virtual void v150();
	virtual void v154();
	virtual void v158();
	virtual void v15C();
	virtual void v160();
	virtual void v164();
	virtual void v168();
	virtual void v16C();
	virtual void v170();
	virtual void v174();
	virtual void v178();
	virtual void v17C();
	virtual void v180();
	virtual void v184();
	virtual void v188();
	virtual void v18C();
	virtual void v190();
	virtual void v194();
	virtual void v198();
	virtual void v19C();
	virtual void v1A0();
	virtual void v1A4();
	virtual void v1A8();
	virtual void v1AC();
	virtual void v1B0();
	virtual void v1B4();
	virtual void v1B8();
	virtual void v1BC();
	virtual void v1C0();
	virtual void v1C4();
	virtual void v1C8();
	virtual void v1CC();
	virtual void v1D0();
	virtual void v1D4();
	virtual void v1D8();
	virtual void v1DC();
	virtual void v1E0();
	virtual void v1E4();
	virtual void v1E8();
	virtual void v1EC();
	virtual void v1F0();
	virtual void v1F4();
	virtual void v1F8();
	virtual void v1FC();
	virtual void v200();
	virtual void v204();
	virtual void v208();
	virtual void v20C();
	virtual void v210();
	virtual void v214();
	virtual void v218();
	virtual void v21C();
	virtual void v220();
	virtual void v224();
	virtual void v228();
	virtual void v22C();
	virtual void v230();
	virtual void v234();
	virtual void v238();
	virtual void v23C();
	virtual int getNumExtraBlendTiles();
};

class NetworkInterface
{
public:
	virtual void v000();
	virtual void v004();
	virtual void v008();
	virtual void v00C();
	virtual void v010();
	virtual void v014();
	virtual void v018();
	virtual void v01C();
	virtual void v020();
	virtual void v024();
	virtual void v028();
	virtual void v02C();
	virtual void v030();
	virtual void v034();
	virtual void v038();
	virtual void v03C();
	virtual void v040();
	virtual void v044();
	virtual void v048();
	virtual void v04C();
	virtual void v050();
	virtual void v054();
	virtual void v058();
	virtual void v05C();
	virtual void v060();
	virtual void v064();
	virtual void v068();
	virtual void v06C();
	virtual void v070();
	virtual void v074();
	virtual void v078();
	virtual void v07C();
	virtual void v080();
	virtual void v084();
	virtual void v088();
	virtual void v08C();
	virtual void v090();
	virtual void v094();
	virtual void v098();
	virtual void v09C();
	virtual void v0A0();
	virtual void v0A4();
	virtual void v0A8();
	virtual void v0AC();
	virtual void v0B0();
	virtual void v0B4();
	virtual void v0B8();
	virtual void v0BC();
	virtual void v0C0();
	virtual void v0C4();
	virtual void v0C8();
	virtual void v0CC();
	virtual void v0D0();
	virtual void v0D4();
	virtual void v0D8();
	virtual void v0DC();
	virtual void v0E0();
	virtual void v0E4();
	virtual void v0E8();
	virtual void v0EC();
	virtual void v0F0();
	virtual int getSequentialBufferCount(int i);
};

class ParticleSystemManager
{
public:
	virtual void v000();
	virtual void v004();
	virtual void v008();
	virtual void v00C();
	virtual void v010();
	virtual void v014();
	virtual void v018();
	virtual void v01C();
	virtual void v020();
	virtual void v024();
	virtual void v028();
	virtual void v02C();
	virtual void v030();
	virtual void v034();
	virtual int getParticleCount();
	char m_pad[0x50 - 4]; int m_onScreenParticleCount;
};

struct TerrainLogicVtbl
{
	virtual void v000();
	virtual void v004();
	virtual void v008();
	virtual void v00C();
	virtual void v010();
	virtual void v014();
	virtual void v018();
	virtual float getLayerHeight(float x, float y, PathfindLayerEnum layer, void *normal, bool clip);
};


struct NativeDebugDisplayFont { AsciiString name; int size; bool bold; };
class GlobalLanguage { public: char m_pad[0xC8]; NativeDebugDisplayFont m_nativeDebugDisplay; };
class GlobalData { public: char m_pad0[0x26]; bool m_useFpsLimit; char m_pad27; int m_framesPerSecondLimit; char m_pad2c[0x9C7 - 0x2C]; bool m_constantDebugUpdate; };
// class-gate: allow GameLogic canonical view lacks getObjectCount (rowed 0x0023CFCE) that this body calls and keeps the +0x38/+0x40 words private
#include "../../../../GameEngine/Source/Common/GameLogicObjectLookupView.h"
class Keyboard { public: bool isShift(); bool isCtrl(); bool isAlt(); char m_pad[0xC]; unsigned char m_modifiers; };
class Mouse { public: char m_pad[0x4F0C]; MouseIO m_currMouse; };
class ExperienceTracker { public: char m_pad[0x10]; float m_experience; char m_pad14[0x24 - 0x14]; int m_level; };
class ExperienceLevelStore { public: int rva00289BE0(const ExperienceTracker *tracker, int *out); };
class ExperienceLevelSystem;
class ThingTemplate { public: char m_pad[0x64]; char *m_nameData; const char *getNameText() const { return m_nameData ? m_nameData + 8 : ""; } char m_pad68[0x5E7 - 0x68]; bool m_showLevel; };
class AIUpdateInterface { public: int getCurrentStateID() const; };
namespace _STL { template <int N> struct _Base_bitset { unsigned int _M_w[N]; bool _M_is_any() const; }; }
typedef _STL::_Base_bitset<4> _STL_Base_bitset4;
struct BfmeFixedStorage128 { BfmeFixedStorage128(const BfmeFixedStorage128 &that); unsigned int m_bits[32]; };
class Object
{
public:
	Object *rva002931F5(bool flag);
	void *m_vtbl; ThingTemplate *m_template; char m_pad8[0x74 - 8]; int m_id;
	char m_pad78[0x88 - 0x78]; AsciiString m_name;
	char m_pad8c[0x94 - 0x8C]; _STL_Base_bitset4 m_status;
	char m_padA4[0x254 - 0xA4]; void *m_body; AIUpdateInterface *m_ai;
	char m_pad25c[0x264 - 0x25C]; ExperienceTracker *m_experienceTracker;
	char m_pad268[0x284 - 0x268]; BfmeFixedStorage128 m_upgrades;
	char m_pad304[0x45C - 0x304]; int m_army;
};
class Drawable
{
public:
	const Coord3D *getPosition() const;
	char m_pad0[0xFC]; Object *m_object;
	char m_pad100[0x258 - 0x100]; unsigned int m_conditionBits[20];
};
class Rva0055A88BDwordField { public: int get() const; };
class Rva00046827 { public: int rva00046827(); };
class UpgradeTemplateView { public: char m_pad[8]; AsciiString m_name; char m_padC[0x38 - 0xC]; unsigned int m_bit; };
class Rva0026F0F0 { public: void *rva0026F0F0(const void *mask); };
class TerrainLogic : public TerrainLogicVtbl { public: PathfindLayerEnum getHighestLayerForDestination(const Coord3D *pos, bool onlyHealthy); };
class Rva002A7461 { public: int rva002A7461(); int rva002A7548(int i); };
class Rva002A7389 { public: int get(int i); };
class Player { public: char m_pad[0x60]; Rva002A7461 m_commandPoints; };
class PlayerList
{
public:
	Player *getNthPlayer(int index);
	char m_pad00[0x10];
	Player *m_local; // +0x10
	int m_playerCount; // +0x14 +0x14
};
class ScriptEngine { public: char m_pad[0x1A4C4]; int m_campaignAI; };
class Rva002858E5 { public: bool rva002858E5(float *pos, int *a, int *b, int *c, int *d, int *e); };
struct Slot64 { char m_pad[0x18]; unsigned int m_used; char m_pad1c[0x28 - 0x1C]; unsigned int m_peak; };
class Rva006C1F60 { public: Slot64 *rva006C1AA0(unsigned int i); };
class RegistryClass { public: RegistryClass(const char *key, bool create); ~RegistryClass(); int Get_Int(const char *name, int def); bool Is_Valid() const { return m_valid; } int m_key; bool m_valid; };
namespace Debug_Statistics
{
	enum RecordTextureMode { RECORD_TEXTURE_NONE, RECORD_TEXTURE_SIMPLE };
	void Record_Texture_Mode(RecordTextureMode mode);
	int Get_Draw_Calls();
	int Get_Sorting_Polygons();
	int Get_DX8_Skin_Renders();
	int Get_DX8_Polygons();
	int Get_DX8_Vertices();
	int Get_Record_Texture_Size();
}
int __cdecl Rva00129640Get(int category);
int __cdecl Rva00129590Get();
int __cdecl Rva00129660Get();
int __cdecl Rva00129680Get();
int __cdecl Rva00078BEEGet();
int __cdecl Rva00078BF4Get();
__int64 __cdecl Rva00043024Get();
__int64 __cdecl Rva0004300DGet();
namespace EA { namespace Allocator { class GeneralAllocator; } }
// Release MemoryPool::GetHeapAllocatorByIndex: retail calls the folded 3-byte zero-return body
// at 0x65CE90 (WB wrapper 0x6FDCC0 via 0xDE03E0 supports the identity; the fold is below the
// fold-proof minimum, so the call keeps an address-named placeholder).
namespace MemoryPool { EA::Allocator::GeneralAllocator *Rva0065CE90(unsigned int index); }

extern GlobalLanguage *TheGlobalLanguageData;
extern FontLibrary *TheFontLibrary;
extern DisplayStringManager *TheDisplayStringManager;
extern GlobalData *TheWritableGlobalData;
extern GameLogic *TheGameLogic;
extern Keyboard *TheKeyboard;
extern Mouse *TheMouse;
extern GameClient *TheGameClient;
extern InGameUI *TheInGameUI;
extern View *TheTacticalView;
extern PlayerList *ThePlayerList;
extern ScriptEngine *TheScriptEngine;
class Rva002872BA; extern Rva002872BA *TheTriggerManager;
extern ParticleSystemManager *TheParticleSystemManager;
extern NetworkInterface *TheNetwork;
extern TerrainLogic *TheTerrainLogic;
extern ExperienceLevelSystem *TheExperienceLevelSystem;
class UpgradeCenter; extern UpgradeCenter *TheUpgradeCenter;
class BaseHeightMapRenderObjClass; extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;
extern const char *const ModelConditionNames[];
extern const char *BodyStateNames[];

class W3DDisplay
{
public:
	virtual void gatherDebugStats(void);
	char m_pad4[0x18C - 4];
	DisplayString *m_displayStrings[16];
	char m_pad1cc[0x278 - 0x1CC];
	DisplayString *m_benchmarkDisplayString;
};


void W3DDisplay::gatherDebugStats(void)
{
	static unsigned int s_framesRenderedSinceLastUpdate = 0;
	static __int64 s_lastUpdateTime64 = 0;
	static double s_timeSinceLastUpdateInSecs = 0.0;
	static int s_drawCallsSinceLastUpdate = 0;
	static int s_sortedPolysSinceLastUpdate = 0;

	if (m_displayStrings[0] == 0)
	{
		GameFont *font;
		GlobalLanguage *language = TheGlobalLanguageData;
		const AsciiString *fontName;
		if (language && (fontName = &language->m_nativeDebugDisplay.name, !fontName->isEmpty()))
		{
			font = TheFontLibrary->getFont(fontName, (float)language->m_nativeDebugDisplay.size, language->m_nativeDebugDisplay.bold);
		}
		else
		{
			AsciiString fixedSys("FixedSys");
			font = TheFontLibrary->getFont(&fixedSys, 8.0f, false);
		}

		for (int i = 0; i < 16; i++)
		{
			if (m_displayStrings[i] == 0)
			{
				m_displayStrings[i] = TheDisplayStringManager->newDisplayString();
				m_displayStrings[i]->setFont(font);
			}
		}
	}

	if (m_benchmarkDisplayString == 0)
	{
		GameFont *thisFont = TheFontLibrary->getFont(&AsciiString("FixedSys"), 8.0f, false);
		m_benchmarkDisplayString = TheDisplayStringManager->newDisplayString();
		m_benchmarkDisplayString->setFont(thisFont);
	}

	++s_framesRenderedSinceLastUpdate;
	s_drawCallsSinceLastUpdate += Debug_Statistics::Get_Draw_Calls();
	s_sortedPolysSinceLastUpdate += Debug_Statistics::Get_Sorting_Polygons();

	__int64 freq64 = Rva00043024Get();
	__int64 time64 = Rva0004300DGet();

	s_timeSinceLastUpdateInSecs = ((double)(time64 - s_lastUpdateTime64) / (double)(freq64));

	if (s_timeSinceLastUpdateInSecs >= 2.0 || TheWritableGlobalData->m_constantDebugUpdate)
	{
		UnicodeString unibuffer, unibuffer2;
		UnicodeString fpsString;

		Debug_Statistics::Record_Texture_Mode(Debug_Statistics::RECORD_TEXTURE_SIMPLE);

		double fps = (float)s_framesRenderedSinceLastUpdate / s_timeSinceLastUpdateInSecs;
		double drawsPerFrame = Debug_Statistics::Get_Draw_Calls();
		int draws0 = Rva00129640Get(0);
		int draws1 = Rva00129640Get(1);
		int draws2 = Rva00129640Get(2);
		double sortPolysPerFrame = Debug_Statistics::Get_Sorting_Polygons();
		double skinSubDraws = Rva00129590Get();
		double skinDrawsPerFrame = Debug_Statistics::Get_DX8_Skin_Renders();
		int shaderChanges = Rva00129680Get();

		if (fps < 0.1) fps = 0.1;

		double ms = 1000.0 / fps;

		if (Rva00129660Get() == 1)
			unibuffer.format(W("FPS: %.2f, %.2fms draws: %.2f skins: %.2f(%.2f) sort %.2f, shadChng %d"), fps, ms, drawsPerFrame, skinDrawsPerFrame, skinSubDraws, sortPolysPerFrame, shaderChanges);
		else if (Rva00129660Get() == 2)
			unibuffer.format(W("FPS: %.2f, %.2fms draws: %.2f(%d,%d) skins: %.2f(%.2f) sort %.2f, shadChng %d"), fps, ms, drawsPerFrame, draws0, draws1, skinDrawsPerFrame, skinSubDraws, sortPolysPerFrame, shaderChanges);
		else
			unibuffer.format(W("FPS: %.2f, %.2fms draws: %.2f(%d,%d,%d) skins: %.2f(%.2f) sort %.2f, shadChng %d"), fps, ms, drawsPerFrame, draws0, draws1, draws2, skinDrawsPerFrame, skinSubDraws, sortPolysPerFrame, shaderChanges);

		if (TheWritableGlobalData->m_useFpsLimit)
		{
			unibuffer2.format(W(", FPSLock %d"), TheWritableGlobalData->m_framesPerSecondLimit);
			unibuffer.concat(unibuffer2);
		}

		fpsString.format(W("FPS: %.2f"), fps);
		m_benchmarkDisplayString->setText(fpsString);

		int polyPerFrame = Debug_Statistics::Get_DX8_Polygons();

		RegistryClass registry("Software\\Microsoft\\Direct3d", true);
		if (registry.Is_Valid())
		{
			if (registry.Get_Int("LoadDebugRuntime", 0) == 1)
				unibuffer.concat(W(", DEBUG D3D"));
		}

		m_displayStrings[0]->setText(unibuffer);

		unibuffer.format(W("Session/Frame: %d/%d"), TheGameLogic->getTimestamp(), TheGameLogic->getFrame());
		m_displayStrings[1]->setText(unibuffer);

		unibuffer.format(W("Polygons: per frame %d, per second %d"), polyPerFrame, (int)(polyPerFrame * fps));
		m_displayStrings[2]->setText(unibuffer);

		unibuffer.format(W("Vertices: %d"), Debug_Statistics::Get_DX8_Vertices());
		m_displayStrings[3]->setText(unibuffer);

		int groups = Rva00078BF4Get() ? Rva00078BF4Get() : 1;
		unibuffer.format(W("Models w/ shareable skins: %d, groups: %d, avg models/group: %.2f"), Rva00078BEEGet(), Rva00078BF4Get(), (double)Rva00078BEEGet() / groups);
		m_displayStrings[12]->setText(unibuffer);

		if (ThePlayerList && ThePlayerList->m_local)
		{
			Rva002A7461 *points = &ThePlayerList->m_local->m_commandPoints;
			unibuffer.format(W("CmdPoints Total:%d, Used:%d (allies:%d), Available:%d (allies:%d)"), points->rva002A7461(), ((Rva002A7389 *)points)->get(0), ((Rva002A7389 *)points)->get(1), points->rva002A7548(0), points->rva002A7548(1));
		}
		else
			unibuffer.set(W(""));
		m_displayStrings[13]->setText(unibuffer);

		if (TheScriptEngine)
			unibuffer.format(W("Campaign AI: %d"), TheScriptEngine->m_campaignAI);
		else
			unibuffer.set(W(""));
		m_displayStrings[14]->setText(unibuffer);

		unibuffer.format(W("Video RAM: %d"), Debug_Statistics::Get_Record_Texture_Size());
		if (MemoryPool::Rva0065CE90(0))
		{
			unsigned int used = 0;
			unsigned int peak = 0;
			Rva006C1F60 *heap;
			for (int i = 0; (heap = (Rva006C1F60 *)MemoryPool::Rva0065CE90(i)) != 0; i++)
			{
				Slot64 *slot = heap->rva006C1AA0(3);
				used += slot->m_used;
				peak += slot->m_peak;
			}
			unibuffer2.format(W(", Sys RAM: %dk, Peak: %dk"), (used + 1023) / 1024, (peak + 1023) / 1024);
			unibuffer.concat(unibuffer2);
		}
		m_displayStrings[4]->setText(unibuffer);

		s_timeSinceLastUpdateInSecs = 0.0;
		s_lastUpdateTime64 = time64;
		s_framesRenderedSinceLastUpdate = 0;
		s_drawCallsSinceLastUpdate = 0;
		s_sortedPolysSinceLastUpdate = 0;

		unibuffer.format(W("3-Way Blends: %d"), ((TerrainRenderObject *)TheTerrainRenderObject)->getNumExtraBlendTiles());
		m_displayStrings[11]->setText(unibuffer);

		Coord3D pos;
		TheTacticalView->getPosition(&pos);
		float zoom = TheTacticalView->getZoom();
		float pitch = TheTacticalView->getPitch();
		float pitch2 = TheTacticalView->getPitch2();
		float yaw = TheTacticalView->getAngle();
		float fov = TheTacticalView->getFieldOfView();
		float terrainHeight = TheTacticalView->getTerrainHeightUnderCamera();
		float heightAbove = TheTacticalView->getHeightAboveGround();
		unibuffer.format(W("Camera zoom: %g, pitch: %g/%g, yaw: %g, pos: %g, %g, %g, FOV: %g\n       Height above ground: %g Terrain height: %g"),
			zoom, pitch, pitch2, yaw, pos.x, pos.y, pos.z, fov, heightAbove, terrainHeight);
		m_displayStrings[5]->setText(unibuffer);

		unibuffer.format(W("States: "));
		if (TheKeyboard->isShift())
		{
			unibuffer.concat(W("Shift("));
			if (TheKeyboard->m_modifiers & 0x10) unibuffer.concat(W("L"));
			if (TheKeyboard->m_modifiers & 0x20) unibuffer.concat(W("R"));
			unibuffer.concat(W(") "));
		}
		if (TheKeyboard->isCtrl())
		{
			unibuffer.concat(W("Ctrl("));
			if (TheKeyboard->m_modifiers & 0x04) unibuffer.concat(W("L"));
			if (TheKeyboard->m_modifiers & 0x08) unibuffer.concat(W("R"));
			unibuffer.concat(W(") "));
		}
		if (TheKeyboard->isAlt())
		{
			unibuffer.concat(W("Alt("));
			if (TheKeyboard->m_modifiers & 0x40) unibuffer.concat(W("L"));
			if (TheKeyboard->m_modifiers & 0x80) unibuffer.concat(W("R"));
			unibuffer.concat(W(") "));
		}

		const MouseIO *io = &TheMouse->m_currMouse;
		if (io->leftState) unibuffer.concat(W("LMB "));
		if (io->middleState) unibuffer.concat(W("MMB "));
		Drawable *draw;
		if (io->rightState)
		{
			unibuffer.concat(W("RMB "));
			draw = TheGameClient->findDrawableByID(TheInGameUI->getMousedOverDrawableID());
		}
		else
			draw = TheGameClient->findDrawableByID(TheInGameUI->getMousedOverDrawableID());

		Object *obj;
		if (draw && (obj = draw->m_object) != 0)
		{
			int objID = obj->m_id; unibuffer2.format(W("Moused over object: %S (%d) "), obj->m_template->getNameText(), objID);
			unibuffer.concat(unibuffer2);
			Object *container = obj->rva002931F5(false);
			int army = container ? container->m_army : obj->m_army;
			if (army)
				unibuffer2.format(W(" (army %d) "), army);
			else
				unibuffer2.format(W(" (army INVALID)"));
			unibuffer.concat(unibuffer2);
			if (obj->m_template->m_showLevel)
			{
				ExperienceTracker *tracker = obj->m_experienceTracker;
				float experience = tracker->m_experience;
				int level = tracker->m_level;
				unibuffer2.format(W("Level %d ( has %.1f and needs %d to level). "), level, experience, ((ExperienceLevelStore *)TheExperienceLevelSystem)->rva00289BE0(tracker, 0));
				unibuffer.concat(unibuffer2);
			}
		}
		else
			unibuffer.concat(W("Moused over object: TERRAIN "));
		m_displayStrings[6]->setText(unibuffer);

		Coord3D world;
		const MouseIO *mouse = &TheMouse->m_currMouse;
		TheTacticalView->screenToTerrain(mouse, &world, 0);
		unibuffer.format(W("Mouse position: screen: (%d, %d), world: (%g, %g, %g)"), mouse->x, mouse->y, world.x, world.y, world.z);
		m_displayStrings[7]->setText(unibuffer);

		if (TheTriggerManager)
		{
			int fuel, resistance, burnRate, maxBurn, decay;
			if (((Rva002858E5 *)TheTriggerManager)->rva002858E5(&world.x, &fuel, &burnRate, &decay, &resistance, &maxBurn))
				unibuffer.format(W("Fire logic: fuel=%d, resistance=%d, burn rate=%d, max=%d, decay=%d"), fuel, resistance, burnRate, maxBurn, decay);
			else
				unibuffer.set(W("Fire logic: ---"));
		}
		else
			unibuffer.set(W(""));
		m_displayStrings[15]->setText(unibuffer);

		int totalParticles = TheParticleSystemManager->m_onScreenParticleCount;
		int onScreenParticleCount = TheParticleSystemManager->getParticleCount();
		unibuffer.format(W("Particles: %d in world, %d being displayed"), totalParticles, onScreenParticleCount);
		m_displayStrings[8]->setText(unibuffer);

		unsigned int objectCount = TheGameLogic->getObjectCount();
		int onScreen = TheGameClient->m_onScreenObjectCount;
		int localObjects = 0;
		Player *localPlayer = ThePlayerList->m_local;
		if (localPlayer)
			localObjects = *(int *)((char *)localPlayer + 0x42C) - *(int *)((char *)localPlayer + 0x430);
		unibuffer.format(W("Objects: %d in world, %d being displayed, %d owned by local player"), objectCount, onScreen, localObjects);
		m_displayStrings[9]->setText(unibuffer);

		if (TheNetwork)
		{
			unibuffer.set(W("SequentialBuffers: "));
			for (int i = 0; i < 9; i++)
			{
				unibuffer2.format(W("%d "), TheNetwork->getSequentialBufferCount(i));
				unibuffer.concat(unibuffer2);
			}
			m_displayStrings[5]->setText(unibuffer);
		}

		unibuffer.format(W("Select Info: '%d' drawables selected"), TheInGameUI->getSelectCount());
		if (TheInGameUI->getSelectCount() == 1)
			draw = TheInGameUI->getFirstSelectedDrawable();
		Object *selObj;
		if (draw && (selObj = draw->m_object) != 0)
		{
			AsciiString name;
			name = "No-Name";
			if (!selObj->m_name.isEmpty())
				name = selObj->m_name;
			Coord3D selPos; const Coord3D *sp = draw->getPosition(); selPos.x = sp->x; selPos.y = sp->y; selPos.z = sp->z;
			void *body = selObj->m_body;
			PathfindLayerEnum layer = TheTerrainLogic->getHighestLayerForDestination(&selPos, false);
			float groundZ = TheTerrainLogic->getLayerHeight(selPos.x, selPos.y, layer, 0, true);
			unibuffer.format(W("Select Info: '%S'(%S)[%d][%d] at (%.3f,%.3f,%.3f) groundZ@pos: %.3f Health: %.3f"),
				((Object *)draw)->m_template->getNameText(), name.str(), ((Rva0055A88BDwordField *)draw)->get(), draw->m_object ? draw->m_object->m_id : 0,
				draw->getPosition()->x, draw->getPosition()->y, draw->getPosition()->z, groundZ,
				((BodyView *)body)->getHealth());

			unibuffer.concat(W("\nModelFlags: "));
			int perLine = 0;
			for (int i = 0; i < 591; i++)
			{
				if (draw->m_conditionBits[(unsigned)i >> 5] & (1 << (i & 31)))
				{
					unibuffer2.format(W("%S "), ModelConditionNames[i]);
					unibuffer.concat(unibuffer2);
					if (++perLine == 6)
					{
						perLine = 0;
						unibuffer.concat(W("\n"));
					}
				}
			}

			unibuffer.concat(W("\nStatus: "));
			const _STL_Base_bitset4 &status = selObj->m_status; if (status._M_is_any())
			{
				perLine = 0;
				for (int i = 0; i < 101; i++)
				{
					if (status._M_w[(unsigned)i >> 5] & (1 << (i & 31)))
					{
						unibuffer2.format(W("%S "), BodyStateNames[i]);
						unibuffer.concat(unibuffer2);
						if (++perLine == 6)
						{
							perLine = 0;
							unibuffer.concat(W("\n"));
						}
					}
				}
			}

			unibuffer.concat(W("\nUpgrades: "));
			BfmeFixedStorage128 mask(selObj->m_upgrades);
			bool anySet = false;
			for (unsigned int w = 0; w < 32; w++)
			{
				if (mask.m_bits[w])
				{
					anySet = true;
					break;
				}
			}
			if (anySet)
			{
				perLine = 0;
				while (((Rva00046827 *)&mask)->rva00046827() > 0)
				{
					UpgradeTemplateView *upgrade = (UpgradeTemplateView *)((Rva0026F0F0 *)TheUpgradeCenter)->rva0026F0F0(&mask);
					if (upgrade)
					{
						unibuffer2.format(W("%S "), upgrade->m_name.str());
						unibuffer.concat(unibuffer2);
						if (++perLine == 6)
						{
							perLine = 0;
							unibuffer.concat(W("\n"));
						}
					}
					mask.m_bits[upgrade->m_bit >> 5] &= ~(1 << (upgrade->m_bit & 31));
				}
			}

			if (selObj)
			{
				unibuffer.concat(W("\nAIStateType: "));
				AIUpdateInterface *ai = selObj->m_ai;
				if (ai)
				{
					unibuffer2.format(W("%d \n"), ai->getCurrentStateID());
					unibuffer.concat(unibuffer2);
				}
			}
		}
		m_displayStrings[10]->setText(unibuffer);
	}
}
