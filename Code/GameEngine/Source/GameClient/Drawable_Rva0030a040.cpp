// cl: -DNDEBUG -DWIN32 -MD -EHsc -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/reference/shims/locomotor -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Os -Ireference/open-bfme-1/game/GameEngine/Source/GameClient
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// Drawable.cpp ///////////////////////////////////////////////////////////////////////////////////
// "Drawables" - graphical GameClient entities bound to GameLogic objects
// Author: Michael S. Booth, March 2001
///////////////////////////////////////////////////////////////////////////////////////////////////
  
// BFME's Snapshot base is polymorphic where Zero Hour's is not: ~TintEnvelope
// calls the vptr-store-then-release-AsciiString body at 0x009A1A40, not the
// bare release at 0x00887940 that the ZH spelling resolves to.  Renaming the
// class for this TU gives that call its own pinnable symbol instead of a second
// address under a name another TU already resolves elsewhere.
#define Snapshot BfmeDrawableSnapshot
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

// BFME's placement operator delete is one shared 12-byte body that calls the
// CRT free import directly; ZH's macro routes it through ::operator delete,
// which is a different (and here, wrong) callee.  The two headers that declare
// this TU's four pooled classes are pulled in here so the override reaches them
// and nothing else.
// GameMemory.h must be resolved BEFORE the override: every header below
// reaches it transitively, and its own #define would otherwise land after
// ours and silently restore ZH's ::operator delete routing.
#include "Common/GameMemory.h"
#pragma push_macro("MEMORY_POOL_GLUE_WITHOUT_GCMP")
#undef MEMORY_POOL_GLUE_WITHOUT_GCMP
extern "C" void free(void *);
#define MEMORY_POOL_GLUE_WITHOUT_GCMP(ARGCLASS) \
protected: \
	virtual ~ARGCLASS(); \
public: \
	enum ARGCLASS##MagicEnum { ARGCLASS##_GLUE_NOT_IMPLEMENTED = 0 }; \
public: \
	inline void *operator new(size_t s, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ \
		DEBUG_ASSERTCRASH(s == sizeof(ARGCLASS), ("The wrong operator new is being called; ensure all objects in the hierarchy have MemoryPoolGlue set up correctly")); \
		return MP_GLUE_ALLOCATE(ARGCLASS); \
	} \
public: \
	inline void operator delete(void *p, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ \
		free(p); \
	} \
protected: \
	inline void *operator new(size_t s) \
	{ \
		DEBUG_ASSERTCRASH(s == sizeof(ARGCLASS), ("The wrong operator new is being called; ensure all objects in the hierarchy have MemoryPoolGlue set up correctly")); \
		return ::operator new(s); \
	} \
	inline void operator delete(void *p) \
	{ \
		::operator delete(p); \
	} \
private: \
	virtual MemoryPool *getObjectMemoryPool() \
	{ \
		return ARGCLASS::getClassMemoryPool(); \
	} \
public:
#include "Common/DynamicAudioEventInfo.h"
#include "GameClient/Drawable.h"
#pragma pop_macro("MEMORY_POOL_GLUE_WITHOUT_GCMP")

#include "Common/AudioEventInfo.h"
#include "Common/DynamicAudioEventInfo.h"
#include "Common/AudioSettings.h"
#include "Common/BitFlagsIO.h"
#include "Common/BuildAssistant.h"
#include "Common/ClientUpdateModule.h"
#include "Common/DrawModule.h"
#include "Common/GameAudio.h"
#include "Common/GameEngine.h"
#include "Common/GameLOD.h"
#include "Common/GameState.h"
#include "Common/GlobalData.h"
#include "Common/ModuleFactory.h"
#include "Common/PerfTimer.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/ThingFactory.h"
#include "Common/ThingTemplate.h"
#include "Common/Xfer.h"

#include "GameLogic/ExperienceTracker.h"
#include "GameLogic/GameLogic.h"		// for logic frame count
#include "GameLogic/Object.h"
#include "GameLogic/Locomotor.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Module/ContainModule.h"
#include "GameLogic/Module/PhysicsUpdate.h"
#include "GameLogic/Module/StealthUpdate.h"
#include "GameLogic/Module/StickyBombUpdate.h"
#include "GameLogic/Module/BattlePlanUpdate.h"
#include "GameLogic/ScriptEngine.h"
#include "GameLogic/Weapon.h"

#include "GameClient/Anim2D.h"
#include "GameClient/Display.h"
#include "GameClient/DisplayStringManager.h"
#include "GameClient/Drawable.h"
#include "GameClient/DrawGroupInfo.h"
#include "GameClient/GameClient.h"
#include "GameClient/GlobalLanguage.h"
#include "GameClient/InGameUI.h"
#include "GameClient/Image.h"
#include "GameClient/ParticleSys.h"
#include "GameClient/LanguageFilter.h"
#include "GameClient/Shadow.h"
#include "GameClient/GameText.h"

//#define KRIS_BRUTAL_HACK_FOR_AIRCRAFT_CARRIER_DEBUGGING 
#ifdef KRIS_BRUTAL_HACK_FOR_AIRCRAFT_CARRIER_DEBUGGING
	#include "GameLogic/Module/ParkingPlaceBehavior.h"
#endif

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

#define VERY_TRANSPARENT_MATERIAL_PASS_OPACITY (0.001f)
#define MATERIAL_PASS_OPACITY_FADE_SCALAR (0.8f)

// Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/GameClient/Drawable.cpp (reference/open-bfme-1),
// which is byte-identical to retail 0x0030A040 once relocations are masked.
// Only the placed body ?parseFireEffect@@YAXPAVINI@@@Z is defined here; the
// donor's other definitions are omitted.

struct FireEffect
{
	Real m_scale;					// 0x00  Scale
	Real m_blend;					// 0x04  Blend
	RGBColor m_effectColor;			// 0x08  EffectColor
	RGBColor m_baseColor;			// 0x14  BaseColor
	Real m_effectSaturation;		// 0x20  EffectSaturation
	Real m_baseSaturation;			// 0x24  BaseSaturation
	char m_unknown28[ 0x4c - 0x28 ];// 0x28  no INI field writes here
	Real m_velocity;				// 0x4c  Velocity
	Real m_textureCross;			// 0x50  TextureCross
	Real m_textureRepeatCount;		// 0x54  TextureRepeatCount

	static const FieldParse m_fieldParseTable[];
};

// BFME has a fourth INILoadType that Zero Hour does not, value 4. Both it and
// INI_LOAD_CREATE_OVERRIDES suppress the write-back. Left as the literal because
// nothing in the image names it.
static const INILoadType INI_LOAD_BFME_TYPE_4 = (INILoadType)4;

// BFME keeps m_loadType at INI+0x08. Zero Hour's header puts it at +0x2010,
// because Zero Hour parses through an 8KB m_readBuffer that BFME does not have
// (see docs/ini_loading.md). Reading it through a local view keeps these three
// functions matchable without moving this whole file onto the BFME INI shim.
inline INILoadType retailLoadType( const INI *ini )
{
	struct RetailINI { char m_pad[ 0x08 ]; INILoadType m_loadType; };
	return reinterpret_cast<const RetailINI *>( ini )->m_loadType;
}

static FireEffect s_fireEffectSaved;		// 0x12b5100
static FireEffect s_fireEffectActive;		// 0x12b5158

void parseFireEffect( INI *ini )
{
	s_fireEffectActive = s_fireEffectSaved;
	ini->initFromINI( &s_fireEffectActive, FireEffect::m_fieldParseTable );
	const INILoadType loadType = retailLoadType( ini );
	if( loadType != INI_LOAD_CREATE_OVERRIDES && loadType != INI_LOAD_BFME_TYPE_4 )
		s_fireEffectSaved = s_fireEffectActive;
}
