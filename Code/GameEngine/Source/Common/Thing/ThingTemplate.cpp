// cl: /DBFME_ASCII_DTOR_DECL /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims/bfme_namekey /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/shims -ICode/Libraries/Source/Compression/LZHCompress/CompLibHeader /Ireference/shims/bfme2htree /Ireference/shims/bfme2renderobj /Ireference/shims/bfmecamera /Ireference/shims/bfmelight /Ireference/shims/bfmeparticlehandle /Ireference/shims/bfmeparticleload /Ireference/shims/bfmeparticlequat /Ireference/shims/bfmeparticlesave /Ireference/shims/bfmeparticleline /Ireference/shims/bfme2ray /Ireference/shims/bfme2scene -D_STLP_USE_STATIC_LIB -DNDEBUG -DWIN32 -D_WINDOWS /Ireference/shims/bfmefrustum
// stlport
// Ported verbatim from the Generals Zero Hour reference
// (GameEngine/Source/Common/Thing/ThingTemplate.cpp); this unit had no counterpart under Code/.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

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

// FILE: ThingTemplate.cpp ////////////////////////////////////////////////////////////////////////
// Created: Colin Day, April 2001
// Desc:    Thing templates
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

#define DEFINE_POWER_NAMES								// for PowerNames[]
#define DEFINE_SHADOW_NAMES								// for TheShadowNames[]
#define DEFINE_GEOMETRY_NAMES							// for GeometryNames[]
#define DEFINE_BUILD_COMPLETION_NAMES			// for BuildCompletionNames[]
#define DEFINE_EDITOR_SORTING_NAMES				// for EditorSortingNames[]
#define DEFINE_RADAR_PRIORITY_NAMES				// for RadarPriorityNames[]
#define DEFINE_BUILDABLE_STATUS_NAMES			// for BuildableStatusNames[]

#include "Common/DamageFX.h"
#include "Common/GameAudio.h"
#include "Common/GameCommon.h"
#include "Common/GlobalData.h"
#include "Common/INI.h"
#include "Common/MessageStream.h"
#include "Common/Module.h"
#include "Common/ModuleFactory.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/ProductionPrerequisite.h"
#include "Common/Radar.h"
#include "Common/RandomValue.h"
#include "Common/Science.h"
#include "Common/ThingTemplate.h"
#include "Common/ThingFactory.h"
#include "Common/ThingSort.h"
#include "Common/BitFlagsIO.h"

#include "GameClient/Drawable.h"
#include "GameClient/FXList.h"
#include "GameClient/GameText.h"
#include "GameClient/Image.h"
#include "GameClient/Shadow.h"

#include "GameLogic/Armor.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/SpecialPowerModule.h"
#include "GameLogic/Object.h"
#include "GameLogic/Powers.h"
#include "GameLogic/Weapon.h"

#include "Common/UnitTimings.h" //Contains the DO_UNIT_TIMINGS define jba.	

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
const Int USE_EXP_VALUE_FOR_SKILL_VALUE = -999;


///////////////////////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA ///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

AudioEventRTS ThingTemplate::s_audioEventNoSound;

/* 
	NOTE NOTE NOTE -- s_objectFieldParseTable and s_objectReskinFieldParseTable must be updated in tandem!

	"s_objectReskinFieldParseTable" is intended to be used for parsing the "ObjectReskin" keyword, and 
	should only allow you to specify things that affect the appearance of a template. 
	
	The idea is that some units are functionally the same, but different visually; rather than replicate
	all the settings, you can specify it as "this one is like that one, but looks different".

	Thus, currently, the only things in the reskin table are:
		
		-- DrawModules
		-- DrawModuleData
		-- Geometry
	
	So: if you add/remove/modify any settings that deal with visual appearance, you *may* want to 
	add 'em to the reskin table... but do so VERY CAUTIOUSLY and with careful deliberation (and
	after checking around for other opinions).

*/

// NOTE NOTE NOTE -- s_objectFieldParseTable and s_objectReskinFieldParseTable must be updated in tandem -- see comment above
const FieldParse ThingTemplate::s_objectFieldParseTable[] = 
{
	{ "DisplayName",					INI::parseAndTranslateLabel,					NULL,								offsetof( ThingTemplate, m_displayName ) },
	{ "RadarPriority",				INI::parseByteSizedIndexList,					RadarPriorityNames, offsetof( ThingTemplate, m_radarPriority ) },
	{ "TransportSlotCount",		INI::parseUnsignedByte,								NULL,		offsetof( ThingTemplate, m_transportSlotCount ) },
	{ "FenceWidth",						INI::parseReal,												NULL,		offsetof( ThingTemplate, m_fenceWidth ) },
	{ "FenceXOffset",					INI::parseReal,												NULL,		offsetof( ThingTemplate, m_fenceXOffset ) },
	{ "IsBridge",							INI::parseBool,												NULL,		offsetof( ThingTemplate, m_isBridge ) },
	{ "ArmorSet",							ThingTemplate::parseArmorTemplateSet, NULL, 0},
	{ "WeaponSet",						ThingTemplate::parseWeaponTemplateSet,NULL, 0},
	{ "VisionRange",					INI::parseReal,												NULL,		offsetof( ThingTemplate, m_visionRange ) },
	{ "ShroudClearingRange",	INI::parseReal,												NULL,		offsetof( ThingTemplate, m_shroudClearingRange ) },
	{ "ShroudRevealToAllRange",	INI::parseReal,											NULL,		offsetof( ThingTemplate, m_shroudRevealToAllRange ) },

	{ "PlacementViewAngle",		INI::parseAngleReal,									NULL,		offsetof( ThingTemplate, m_placementViewAngle ) },

	{ "FactoryExitWidth",			INI::parseReal,												NULL,		offsetof( ThingTemplate, m_factoryExitWidth ) },
	{ "FactoryExtraBibWidth",	INI::parseReal,												NULL,		offsetof( ThingTemplate, m_factoryExtraBibWidth ) },
																											
	{ "SkillPointValue",			ThingTemplate::parseIntList,					(void*)LEVEL_COUNT,		offsetof( ThingTemplate, m_skillPointValues ) },
	{ "ExperienceValue",			ThingTemplate::parseIntList,					(void*)LEVEL_COUNT,		offsetof( ThingTemplate, m_experienceValues ) },
	{ "ExperienceRequired",		ThingTemplate::parseIntList,					(void*)LEVEL_COUNT,		offsetof( ThingTemplate, m_experienceRequired ) },
	{ "IsTrainable",					INI::parseBool,												NULL,									offsetof( ThingTemplate, m_isTrainable ) },
	{ "EnterGuard",						INI::parseBool,												NULL,									offsetof( ThingTemplate, m_enterGuard ) },
	{ "HijackGuard",					INI::parseBool,												NULL,									offsetof( ThingTemplate, m_hijackGuard ) },

	{ "Side",									INI::parseAsciiString,								NULL,	offsetof( ThingTemplate, m_defaultOwningSide ) },

// NOTE NOTE NOTE -- s_objectFieldParseTable and s_objectReskinFieldParseTable must be updated in tandem -- see comment above
	{ "Prerequisites",				ThingTemplate::parsePrerequisites,	0, 0 },
	{ "Buildable",						INI::parseByteSizedIndexList,				BuildableStatusNames, offsetof( ThingTemplate, m_buildable) },
	{ "BuildCost",						INI::parseUnsignedShort,						NULL,		offsetof( ThingTemplate, m_buildCost ) },
	{ "BuildTime",						INI::parseReal,											NULL,		offsetof( ThingTemplate, m_buildTime ) },
	{ "RefundValue",					INI::parseUnsignedShort,						NULL,   offsetof( ThingTemplate, m_refundValue ) },
	{ "BuildCompletion",			INI::parseByteSizedIndexList,				BuildCompletionNames,		offsetof( ThingTemplate, m_buildCompletion ) },
	{ "EnergyProduction",			INI::parseInt,											NULL,   offsetof( ThingTemplate, m_energyProduction ) },
	{ "EnergyBonus",					INI::parseInt,											NULL,   offsetof( ThingTemplate, m_energyBonus ) },
	{ "IsForbidden",					INI::parseBool,											NULL,		offsetof( ThingTemplate, m_isForbidden ) },
	{ "IsPrerequisite",				INI::parseBool,											NULL,		offsetof( ThingTemplate, m_isPrerequisite ) },
	{ "DisplayColor",					INI::parseColorInt,									NULL,		offsetof( ThingTemplate, m_displayColor ) },
	{ "EditorSorting",				INI::parseByteSizedIndexList,				EditorSortingNames, offsetof( ThingTemplate, m_editorSorting ) },
	{ "KindOf",								KindOfMaskType::parseFromINI,				NULL,		offsetof( ThingTemplate, m_kindof ) },
	{ "CommandSet",						INI::parseAsciiString,							NULL,		offsetof( ThingTemplate, m_commandSetString ) },	
	{ "BuildVariations",			INI::parseAsciiStringVector,				NULL,		offsetof( ThingTemplate, m_buildVariations ) },

// NOTE NOTE NOTE -- s_objectFieldParseTable and s_objectReskinFieldParseTable must be updated in tandem -- see comment above
	{ "Behavior",							ThingTemplate::parseModuleName,		(const void*)MODULETYPE_BEHAVIOR, offsetof(ThingTemplate, m_behaviorModuleInfo) },
	{ "Body",									ThingTemplate::parseModuleName,		(const void*)999, offsetof(ThingTemplate, m_behaviorModuleInfo) },
	{ "Draw",									ThingTemplate::parseModuleName,		(const void*)MODULETYPE_DRAW, offsetof(ThingTemplate, m_drawModuleInfo) },
	{ "ClientUpdate",					ThingTemplate::parseModuleName,		(const void*)MODULETYPE_CLIENT_UPDATE, offsetof(ThingTemplate, m_clientUpdateModuleInfo) },
// NOTE NOTE NOTE -- s_objectFieldParseTable and s_objectReskinFieldParseTable must be updated in tandem -- see comment above

	{ "SelectPortrait",					INI::parseAsciiString,	NULL,		offsetof( ThingTemplate, m_selectedPortraitImageName ) },
	{ "ButtonImage",						INI::parseAsciiString,	NULL,		offsetof( ThingTemplate, m_buttonImageName ) },
	
	//Code renderer handles these states now.
	//{ "InventoryImageEnabled",	INI::parseAsciiString,	NULL,		offsetof( ThingTemplate, m_inventoryImage[ INV_IMAGE_ENABLED ] ) },
	//{ "InventoryImageDisabled",	INI::parseAsciiString,	NULL,		offsetof( ThingTemplate, m_inventoryImage[ INV_IMAGE_DISABLED ] ) },
	//{ "InventoryImageHilite",		INI::parseAsciiString,	NULL,		offsetof( ThingTemplate, m_inventoryImage[ INV_IMAGE_HILITE ] ) },
	//{ "InventoryImagePushed",		INI::parseAsciiString,	NULL,		offsetof( ThingTemplate, m_inventoryImage[ INV_IMAGE_PUSHED ] ) },
	
	{ "UpgradeCameo1",		INI::parseAsciiString,	NULL,		offsetof( ThingTemplate, m_upgradeCameoUpgradeNames[ 0 ] ) },
	{ "UpgradeCameo2",		INI::parseAsciiString,	NULL,		offsetof( ThingTemplate, m_upgradeCameoUpgradeNames[ 1 ] ) },
	{ "UpgradeCameo3",		INI::parseAsciiString,	NULL,		offsetof( ThingTemplate, m_upgradeCameoUpgradeNames[ 2 ] ) },
	{ "UpgradeCameo4",		INI::parseAsciiString,	NULL,		offsetof( ThingTemplate, m_upgradeCameoUpgradeNames[ 3 ] ) },
	{ "UpgradeCameo5",		INI::parseAsciiString,	NULL,		offsetof( ThingTemplate, m_upgradeCameoUpgradeNames[ 4 ] ) },
	
// NOTE NOTE NOTE -- s_objectFieldParseTable and s_objectReskinFieldParseTable must be updated in tandem -- see comment above

	{ "VoiceSelect",					INI::parseDynamicAudioEventRTS,	NULL,		offsetof( ThingTemplate, m_audioarray.m_audio[TTAUDIO_voiceSelect]) },
	{ "VoiceGroupSelect",			INI::parseDynamicAudioEventRTS,	NULL,		offsetof( ThingTemplate, m_audioarray.m_audio[TTAUDIO_voiceGroupSelect]) },
	{ "VoiceMove",						INI::parseDynamicAudioEventRTS,	NULL,		offsetof( ThingTemplate, m_audioarray.m_audio[TTAUDIO_voiceMove]) },
	{ "VoiceAttack",					INI::parseDynamicAudioEventRTS,	NULL,		offsetof( ThingTemplate, m_audioarray.m_audio[TTAUDIO_voiceAttack]) },
	{ "VoiceEnter",						INI::parseDynamicAudioEventRTS,	NULL,		offsetof( ThingTemplate, m_audioarray.m_audio[TTAUDIO_voiceEnter ]) },
	{ "VoiceFear",						INI::parseDynamicAudioEventRTS,	NULL,		offsetof( ThingTemplate, m_audioarray.m_audio[TTAUDIO_voiceFear ]) },
	{ "VoiceSelectElite",			INI::parseDynamicAudioEventRTS,	NULL,		offsetof( ThingTemplate, m_audioarray.m_audio[TTAUDIO_voiceSelectElite ]) },
	{ "VoiceCreated",					INI::parseDynamicAudioEventRTS,	NULL,		offsetof( ThingTemplate, m_audioarray.m_audio[TTAUDIO_voiceCreated]) },
	{ "VoiceTaskUnable",			INI::parseDynamicAudioEventRTS,	NULL,		offsetof( ThingTemplate, m_audioarray.m_audio[TTAUDIO_voiceTaskUnable ]) },
	{ "VoiceTaskComplete",		INI::parseDynamicAudioEventRTS,	NULL,		offsetof( ThingTemplate, m_audioarray.m_audio[TTAUDIO_voiceTaskComplete ]) },
	{ "VoiceMeetEnemy",				INI::parseDynamicAudioEventRTS,	NULL,		offsetof( ThingTemplate, m_audioarray.m_audio[TTAUDIO_voiceMeetEnemy]) },
	{ "VoiceGarrison",				INI::parseDynamicAudioEventRTS,	NULL,		offsetof( ThingTemplate, m_audioarray.m_audio[TTAUDIO_voiceGarrison]) },
#ifdef ALLOW_SURRENDER
	{ "VoiceSurrender",				INI::parseDynamicAudioEventRTS,	NULL,		offsetof( ThingTemplate, m_audioarray.m_audio[TTAUDIO_voiceSurrender]) },
#endif
	{ "VoiceDefect",					INI::parseDynamicAudioEventRTS,	NULL,		offsetof( ThingTemplate, m_audioarray.m_audio[TTAUDIO_voiceDefect]) },
	{ "VoiceAttackSpecial",		INI::parseDynamicAudioEventRTS,	NULL,		offsetof( ThingTemplate, m_audioarray.m_audio[TTAUDIO_voiceAttackSpecial ]) },	
	{ "VoiceAttackAir",				INI::parseDynamicAudioEventRTS,	NULL,		offsetof( ThingTemplate, m_audioarray.m_audio[TTAUDIO_voiceAttackAir ]) },	
	{ "VoiceGuard",						INI::parseDynamicAudioEventRTS,	NULL,		offsetof( ThingTemplate, m_audioarray.m_audio[TTAUDIO_voiceGuard ]) },	
	{ "SoundMoveStart",				INI::parseDynamicAudioEventRTS,	NULL,		offsetof( ThingTemplate, m_audioarray.m_audio[TTAUDIO_soundMoveStart]) },
	{ "SoundMoveStartDamaged",INI::parseDynamicAudioEventRTS,	NULL,		offsetof( ThingTemplate, m_audioarray.m_audio[TTAUDIO_soundMoveStartDamaged]) },
	{ "SoundMoveLoop",				INI::parseDynamicAudioEventRTS,	NULL,		offsetof( ThingTemplate, m_audioarray.m_audio[TTAUDIO_soundMoveLoop]) },
	{ "SoundMoveLoopDamaged",	INI::parseDynamicAudioEventRTS,	NULL,		offsetof( ThingTemplate, m_audioarray.m_audio[TTAUDIO_soundMoveLoopDamaged]) },
	{ "SoundAmbient",					INI::parseDynamicAudioEventRTS,	NULL,		offsetof( ThingTemplate, m_audioarray.m_audio[TTAUDIO_soundAmbient ]) },
	{ "SoundAmbientDamaged",	INI::parseDynamicAudioEventRTS,	NULL,		offsetof( ThingTemplate, m_audioarray.m_audio[TTAUDIO_soundAmbientDamaged ]) },
	{ "SoundAmbientReallyDamaged",INI::parseDynamicAudioEventRTS,	NULL,offsetof( ThingTemplate, m_audioarray.m_audio[TTAUDIO_soundAmbientReallyDamaged ]) },
	{ "SoundAmbientRubble",		INI::parseDynamicAudioEventRTS,	NULL,		offsetof( ThingTemplate, m_audioarray.m_audio[TTAUDIO_soundAmbientRubble]) },
	{ "SoundStealthOn",       INI::parseDynamicAudioEventRTS,  NULL,  offsetof( ThingTemplate, m_audioarray.m_audio[TTAUDIO_soundStealthOn ]) },
	{ "SoundStealthOff",      INI::parseDynamicAudioEventRTS,  NULL,  offsetof( ThingTemplate, m_audioarray.m_audio[TTAUDIO_soundStealthOff ]) },
	{ "SoundCreated",					INI::parseDynamicAudioEventRTS,	NULL,		offsetof( ThingTemplate, m_audioarray.m_audio[TTAUDIO_soundCreated ]) },
	{ "SoundOnDamaged",				INI::parseDynamicAudioEventRTS,	NULL,		offsetof( ThingTemplate, m_audioarray.m_audio[TTAUDIO_soundOnDamaged ]) },
	{ "SoundOnReallyDamaged",	INI::parseDynamicAudioEventRTS,	NULL,		offsetof( ThingTemplate, m_audioarray.m_audio[TTAUDIO_soundOnReallyDamaged ]) },
	{ "SoundEnter",						INI::parseDynamicAudioEventRTS,	NULL,		offsetof( ThingTemplate, m_audioarray.m_audio[TTAUDIO_soundEnter ]) },
	{ "SoundExit",						INI::parseDynamicAudioEventRTS,	NULL,		offsetof( ThingTemplate, m_audioarray.m_audio[TTAUDIO_soundExit ]) },
	{ "SoundPromotedVeteran",	INI::parseDynamicAudioEventRTS,	NULL,		offsetof( ThingTemplate, m_audioarray.m_audio[TTAUDIO_soundPromotedVeteran ]) },
	{ "SoundPromotedElite",		INI::parseDynamicAudioEventRTS,	NULL,		offsetof( ThingTemplate, m_audioarray.m_audio[TTAUDIO_soundPromotedElite ]) },
	{ "SoundPromotedHero",		INI::parseDynamicAudioEventRTS,	NULL,		offsetof( ThingTemplate, m_audioarray.m_audio[TTAUDIO_soundPromotedHero ]) },
	{ "SoundFallingFromPlane",INI::parseDynamicAudioEventRTS, NULL,		offsetof( ThingTemplate, m_audioarray.m_audio[TTAUDIO_soundFalling ]) },

	{ "UnitSpecificSounds",		ThingTemplate::parsePerUnitSounds, NULL, offsetof(ThingTemplate, m_perUnitSounds) },
	{ "UnitSpecificFX",				ThingTemplate::parsePerUnitFX, NULL, offsetof(ThingTemplate, m_perUnitFX) },
	{ "Scale",								INI::parseReal,						NULL,		offsetof( ThingTemplate, m_assetScale ) },
	{ "Geometry",							GeometryInfo::parseGeometryType,				NULL,  offsetof( ThingTemplate, m_geometryInfo ) },
	{ "GeometryMajorRadius",	GeometryInfo::parseGeometryMajorRadius,	NULL,		offsetof( ThingTemplate, m_geometryInfo ) },
	{ "GeometryMinorRadius",	GeometryInfo::parseGeometryMinorRadius,	NULL,		offsetof( ThingTemplate, m_geometryInfo ) },
	{ "GeometryHeight",				GeometryInfo::parseGeometryHeight,			NULL,		offsetof( ThingTemplate, m_geometryInfo ) },
	{ "GeometryIsSmall",			GeometryInfo::parseGeometryIsSmall,			NULL,		offsetof( ThingTemplate, m_geometryInfo ) },
	{ "Shadow",								INI::parseBitString8,		TheShadowNames,		offsetof( ThingTemplate, m_shadowType ) },
	{ "ShadowSizeX",					INI::parseReal,						NULL,	offsetof( ThingTemplate, m_shadowSizeX ) },
	{ "ShadowSizeY",					INI::parseReal,						NULL,	offsetof( ThingTemplate, m_shadowSizeY ) },
	{ "ShadowOffsetX",				INI::parseReal,						NULL,	offsetof( ThingTemplate, m_shadowOffsetX ) },
	{ "ShadowOffsetY",				INI::parseReal,						NULL,	offsetof( ThingTemplate, m_shadowOffsetY ) },
	{ "ShadowTexture",				INI::parseAsciiString,		NULL,	offsetof( ThingTemplate, m_shadowTextureName ) },
	{ "OcclusionDelay",					INI::parseDurationUnsignedInt,		NULL, offsetof( ThingTemplate, m_occlusionDelay ) },
	{ "AddModule",						ThingTemplate::parseAddModule,			NULL, 0 },
	{ "RemoveModule",					ThingTemplate::parseRemoveModule,		NULL, 0 },
	{ "ReplaceModule",				ThingTemplate::parseReplaceModule,	NULL, 0 },
	{ "InheritableModule",		ThingTemplate::parseInheritableModule,	NULL, 0 },

  { "OverrideableByLikeKind",		ThingTemplate::OverrideableByLikeKind,	NULL, 0 },

	{ "Locomotor",						AIUpdateModuleData::parseLocomotorSet, NULL, 0 },
	{ "InstanceScaleFuzziness",	INI::parseReal,					NULL, offsetof(ThingTemplate, m_instanceScaleFuzziness ) },
	{ "StructureRubbleHeight",	INI::parseUnsignedByte,					NULL, offsetof(ThingTemplate, m_structureRubbleHeight ) },
	{ "ThreatValue",						INI::parseUnsignedShort,		NULL, offsetof(ThingTemplate, m_threatValue ) }, 
  { "MaxSimultaneousOfType",	ThingTemplate::parseMaxSimultaneous,		NULL, offsetof(ThingTemplate, m_maxSimultaneousOfType ) }, 
  { "MaxSimultaneousLinkKey",	NameKeyGenerator::parseStringAsNameKeyType,		NULL, offsetof(ThingTemplate, m_maxSimultaneousLinkKey ) }, 
	{ "CrusherLevel",					INI::parseUnsignedByte,			NULL, offsetof( ThingTemplate, m_crusherLevel ) },
	{ "CrushableLevel",				INI::parseUnsignedByte,			NULL, offsetof( ThingTemplate, m_crushableLevel ) },

	{ 0, 0, 0, 0 }  // keep this last

};
// NOTE NOTE NOTE -- s_objectFieldParseTable and s_objectReskinFieldParseTable must be updated in tandem -- see comment above

// NOTE NOTE NOTE -- s_objectFieldParseTable and s_objectReskinFieldParseTable must be updated in tandem -- see comment above
const FieldParse ThingTemplate::s_objectReskinFieldParseTable[] = 
{
	{ "Draw",									ThingTemplate::parseModuleName,		(const void*)MODULETYPE_DRAW, offsetof(ThingTemplate, m_drawModuleInfo) },

	{ "Geometry",							GeometryInfo::parseGeometryType,				NULL,  offsetof( ThingTemplate, m_geometryInfo ) },
	{ "GeometryMajorRadius",	GeometryInfo::parseGeometryMajorRadius,	NULL,		offsetof( ThingTemplate, m_geometryInfo ) },
	{ "GeometryMinorRadius",	GeometryInfo::parseGeometryMinorRadius,	NULL,		offsetof( ThingTemplate, m_geometryInfo ) },
	{ "GeometryHeight",				GeometryInfo::parseGeometryHeight,			NULL,		offsetof( ThingTemplate, m_geometryInfo ) },
	{ "GeometryIsSmall",			GeometryInfo::parseGeometryIsSmall,			NULL,		offsetof( ThingTemplate, m_geometryInfo ) },
	{ "FenceWidth",						INI::parseReal,													NULL,		offsetof( ThingTemplate, m_fenceWidth ) },
	{ "FenceXOffset",					INI::parseReal,													NULL,		offsetof( ThingTemplate, m_fenceXOffset ) },

  // Needed to avoid some cheats with the scud storm rebuild hole
  { "MaxSimultaneousOfType",	ThingTemplate::parseMaxSimultaneous,		NULL, offsetof(ThingTemplate, m_maxSimultaneousOfType ) }, 
  { "MaxSimultaneousLinkKey",	NameKeyGenerator::parseStringAsNameKeyType,		NULL, offsetof(ThingTemplate, m_maxSimultaneousLinkKey ) }, 

	{ 0, 0, 0, 0 }  // keep this last

};
// NOTE NOTE NOTE -- s_objectFieldParseTable and s_objectReskinFieldParseTable must be updated in tandem -- see comment above

// ------------------------------------------------------------------------------------------------
/** See if the tag string is present in any of the module info entries here */
// ------------------------------------------------------------------------------------------------
// ?ModuleInfo::getNuggetWithTag present-unmatched
const ModuleInfo::Nugget *ModuleInfo::getNuggetWithTag( const AsciiString& tag ) const
{

	std::vector< Nugget >::const_iterator it;
	for( it = m_info.begin(); it != m_info.end(); ++it )
		if( (*it).m_moduleTag == tag )
			return &(*it);

	// no match
	return NULL;

}  // end isTagPresent

// ------------------------------------------------------------------------------------------------
/** Add this module info to the thing template */
// ------------------------------------------------------------------------------------------------
// ModuleInfo::addModuleInfo is defined with its retail-matched body in Code/GameEngine/Source/Common/Thing/ModuleInfoAddModuleInfo.cpp (0x0033D553).

//-------------------------------------------------------------------------------------------------
// ?ModuleInfo::clearModuleDataWithTag present-unmatched
Bool ModuleInfo::clearModuleDataWithTag(const AsciiString& tagToClear, AsciiString& clearedModuleNameOut) 
{ 
	Bool cleared = false;

	// do NOT clear... we only want to modify this if we return true.
	// if we return false, we should leave this unmodified.
	//clearedModuleNameOut.clear();

	for (std::vector<Nugget>::iterator it = m_info.begin(); it != m_info.end(); /* empty */ ) 
	{
		if (it->m_moduleTag == tagToClear)
		{
			DEBUG_ASSERTCRASH(!cleared, ("Hmm, multiple clears in ModuleInfo::clearModuleDataWithTag, should this be possible?"));
			clearedModuleNameOut = it->first;
			it = m_info.erase(it);
			cleared = true;
		}
		else
		{
			++it;
		}
	}
	return cleared;
}





//-------------------------------------------------------------------------------------------------
// ?ModuleInfo::clearCopiedFromDefaultEntries present-unmatched
Bool ModuleInfo::clearCopiedFromDefaultEntries(Int interfaceMask, const AsciiString &newName, const ThingTemplate *fullTemplate ) 
{ 
  static KindOfMaskType ImmuneToGPSScramblerMask;
  KindOfMaskType &m = ImmuneToGPSScramblerMask;
  m.set(KINDOF_AIRCRAFT);// NO PLANES or helicopters
  m.set(KINDOF_SHRUBBERY);// NO trees or bushes
  m.set(KINDOF_OPTIMIZED_TREE);
  m.set(KINDOF_STRUCTURE);// NO buildings
  m.set(KINDOF_DRAWABLE_ONLY);
  m.set(KINDOF_MOB_NEXUS);
  m.set(KINDOF_IGNORED_IN_GUI);
  m.set(KINDOF_CLEARED_BY_BUILD);
  m.set(KINDOF_DEFENSIVE_WALL);
  m.set(KINDOF_BALLISTIC_MISSILE);
  m.set(KINDOF_SUPPLY_SOURCE);
  m.set(KINDOF_BOAT);
  m.set(KINDOF_INERT);
  m.set(KINDOF_BRIDGE);
  m.set(KINDOF_LANDMARK_BRIDGE);
  m.set(KINDOF_BRIDGE_TOWER);
  Bool disallowed =  fullTemplate->isAnyKindOf( ImmuneToGPSScramblerMask );

  static KindOfMaskType CandidateForGPSScramblerMask;
  CandidateForGPSScramblerMask.set(KINDOF_SCORE);
  CandidateForGPSScramblerMask.set(KINDOF_VEHICLE);
  CandidateForGPSScramblerMask.set(KINDOF_INFANTRY);
  CandidateForGPSScramblerMask.set(KINDOF_PORTABLE_STRUCTURE);
  Bool candidate =  fullTemplate->isAnyKindOf( CandidateForGPSScramblerMask );

  Bool ret = false;

	std::vector<Nugget>::iterator it = m_info.begin();
	while( it != m_info.end() )
	{
		if( (it->interfaceMask & interfaceMask) != 0 && it->copiedFromDefault )
		{
      if ( it->inheritable )
			{
				if( it->m_moduleTag.compare("ModuleTag_DefaultAutoHealBehavior") == 0  && !fullTemplate->isTrainable() )
				{
					// Don't inherit this module if it is entirely useless to us.
          it = m_info.erase( it );
			    ret = true;
				}
				else
				{
					++it;//skip to the next nugget, 'cause we inherit this one
				}
			}
      else if ( it->overrideableByLikeKind)
      {
        
        AsciiString oldName = it->first;
        if ( oldName == newName  //we will dump this instance, since the INI author requested a specific one of the same class
             || disallowed  // or, we just do not Add these special overrideables to these kinds of templates, so just dump it
             || candidate == FALSE )
        {
          it = m_info.erase( it );
			    ret = true;
        }
        else
			    ++it;//no match, preserve the default instnace of this Module for now
      }
      else // just dump this instance of this Module, since one of the same interface mask has been added by caller
      {
        it = m_info.erase( it );
			  ret = true;
      }
    }
    else
			++it;
	}
	return ret;
}








//-------------------------------------------------------------------------------------------------
Bool ModuleInfo::clearAiModuleInfo() 
{ 
	Bool ret = false;

	std::vector<Nugget>::iterator it = m_info.begin();
	while( it != m_info.end() )
	{
		if (it->second->isAiModuleData() )
		{
			it = m_info.erase( it );
			ret = true;
		}
		else
		{
			++it;
		}
	}
	return ret;
}

//-------------------------------------------------------------------------------------------------
// ?ThingTemplate::parseModuleName present-unmatched
void ThingTemplate::parseModuleName(INI* ini, void *instance, void* store, const void* userData)
{
	ThingTemplate* self = (ThingTemplate*)instance;
	ModuleInfo* mi = (ModuleInfo*)store;
	ModuleType type = (ModuleType)(UnsignedInt)userData;
	const char* token = ini->getNextToken();
	AsciiString tokenStr = token;

	// get the tag string (it is now required)
	AsciiString moduleTagStr;
	try
	{
		moduleTagStr = ini->getNextToken();
	}
	catch( ... )
	{

		DEBUG_CRASH(( "[LINE: %d - FILE: '%s'] Module tag not found for module '%s' on thing template '%s'.  Module tags are required and must be unique for all modules within an object definition\n",
									ini->getLineNum(), ini->getFilename().str(), 
									tokenStr.str(), self->getName().str() ));
		throw;
				
	}

	Int interfaceMask;

	// ugh -- special case for "Body".
	if (type == 999)
	{
		type = MODULETYPE_BEHAVIOR;
	// what interface(s) does this module support?
		interfaceMask = TheModuleFactory->findModuleInterfaceMask(tokenStr, type);
		if ((interfaceMask & (MODULEINTERFACE_BODY)) == 0)
		{
			DEBUG_CRASH(("Only Body allowed here"));
			throw INI_INVALID_DATA;
		}
	}
	else
	{
		interfaceMask = TheModuleFactory->findModuleInterfaceMask(tokenStr, type);
		if ((interfaceMask & (MODULEINTERFACE_BODY)) != 0)
		{
			DEBUG_CRASH(("No Body allowed here"));
			throw INI_INVALID_DATA;
		}
	}
	
	// if we're overriding, we can totally skip over this block
	if (ini->getLoadType() == INI_LOAD_CREATE_OVERRIDES)
	{	
		if (self->m_moduleParsingMode == MODULEPARSE_ADD_REMOVE_REPLACE)
		{
			// do nothing, just fall thru
		}
		else
		{
			DEBUG_CRASH(("[LINE: %d - FILE: '%s'] You must use AddModule to add modules in override INI files.\n",
				ini->getLineNum(), ini->getFilename().str(), self->getName().str()));
			throw INI_INVALID_DATA;
		}
	}
	else
	{

//    if (self->getName().compare("GLAVehicleQuadCannon"))
//      DEBUG_ASSERTCRASH( FALSE, ("WE ARE CLEARING DEFAULT MODULES FROM A QUAD CANNON.") );

		self->m_behaviorModuleInfo.clearCopiedFromDefaultEntries(interfaceMask, tokenStr, self );
		self->m_drawModuleInfo.clearCopiedFromDefaultEntries(interfaceMask, tokenStr, self );
		self->m_clientUpdateModuleInfo.clearCopiedFromDefaultEntries(interfaceMask, tokenStr, self );
	}

	if (self->m_moduleParsingMode == MODULEPARSE_ADD_REMOVE_REPLACE 
			&& self->m_moduleBeingReplacedName.isNotEmpty()
			&& self->m_moduleBeingReplacedName != tokenStr)
	{
		DEBUG_CRASH(("[LINE: %d - FILE: '%s'] ReplaceModule must replace modules with another module of the same type, but you are attempting to replace a %s with a %s for Object %s.\n",
			ini->getLineNum(), ini->getFilename().str(), self->m_moduleBeingReplacedName.str(), tokenStr.str(), self->getName().str()));
		throw INI_INVALID_DATA;
	}

	if (self->m_moduleParsingMode == MODULEPARSE_ADD_REMOVE_REPLACE 
			&& self->m_moduleBeingReplacedTag.isNotEmpty()
			&& self->m_moduleBeingReplacedTag == moduleTagStr)
	{
		DEBUG_CRASH(("[LINE: %d - FILE: '%s'] ReplaceModule must specify a new, unique tag for the replaced module, but you are not doing so for %s (%s) for Object %s.\n",
			ini->getLineNum(), ini->getFilename().str(), moduleTagStr.str(), self->m_moduleBeingReplacedName.str(), self->getName().str()));
		throw INI_INVALID_DATA;
	}

	ModuleData* data = TheModuleFactory->newModuleDataFromINI(ini, tokenStr, type, moduleTagStr);

	if (data->isAiModuleData())
	{
		Bool replaced = mi->clearAiModuleInfo();
		if (replaced)
		{
			//Kris: Commented this out for SPAM reasons. Do we really need this?
			//DEBUG_LOG(("replaced an AI for %s!\n",self->getName().str()));
		}
	}

	Bool inheritable = (self->m_moduleParsingMode == MODULEPARSE_INHERITABLE);
  Bool overrideableByLikeKind = (self->m_moduleParsingMode == MODULEPARSE_OVERRIDEABLE_BY_LIKE_KIND);
	mi->addModuleInfo(self, tokenStr, moduleTagStr, data, interfaceMask, inheritable, overrideableByLikeKind);
}

//-------------------------------------------------------------------------------------------------
// ?ThingTemplate::parseIntList present-unmatched
void ThingTemplate::parseIntList(INI* ini, void *instance, void* store, const void* userData)
{
	Int numberEntries = (Int)userData;
	Int *intList = (Int*)store;

	for( Int intIndex = 0; intIndex < numberEntries; intIndex ++ )
	{
		const char *token = ini->getNextToken();
		intList[intIndex] = ini->scanInt(token);
	}
}

//-------------------------------------------------------------------------------------------------
static void parsePrerequisiteUnit( INI* ini, void *instance, void * /*store*/, const void* /*userData*/ )
{
	std::vector<ProductionPrerequisite>* v = (std::vector<ProductionPrerequisite>*)instance;

	ProductionPrerequisite prereq;
	Bool orUnitWithPrevious = FALSE;
	for (const char *token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		prereq.addUnitPrereq( AsciiString( token ), orUnitWithPrevious );
		orUnitWithPrevious = TRUE;
	}

	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
static void parsePrerequisiteScience( INI* ini, void *instance, void * /*store*/, const void* /*userData*/ )
{
	std::vector<ProductionPrerequisite>* v = (std::vector<ProductionPrerequisite>*)instance;

	ProductionPrerequisite prereq;
	prereq.addSciencePrereq(INI::scanScience(ini->getNextToken()));

	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ThingTemplate::parsePrerequisites( INI* ini, void *instance, void *store, const void* userData )
{
	ThingTemplate* self = (ThingTemplate*)instance;

	static const FieldParse myFieldParse[] = 
	{
		{ "Object", parsePrerequisiteUnit, 0, 0 },
		{ "Science", parsePrerequisiteScience,	0, 0 },
		{ 0, 0, 0, 0 }
	};

	if (ini->getLoadType() == INI_LOAD_CREATE_OVERRIDES)
	{
		self->m_prereqInfo.clear();
	}

	ini->initFromINI(&self->m_prereqInfo, myFieldParse);
}

//-------------------------------------------------------------------------------------------Static
static void parseArbitraryFXIntoMap( INI* ini, void *instance, void* /* store */, const void* userData )
{
	PerUnitFXMap* mapFX = (PerUnitFXMap*)instance;
	const char* name = (const char*)userData;
	const char* token = ini->getNextToken();
	const FXList* fxl = TheFXListStore->findFXList(token);	// could be null!
	DEBUG_ASSERTCRASH(fxl != NULL || stricmp(token, "None") == 0, ("FXList %s not found!\n",token));
	mapFX->insert(std::make_pair(AsciiString(name), fxl));	
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?ThingTemplate::parsePerUnitFX present-unmatched
void ThingTemplate::parsePerUnitFX( INI* ini, void *instance, void *store, const void *userData )
{
	PerUnitFXMap* fxmap = (PerUnitFXMap*)store;

	fxmap->clear();

	static const FieldParse myFieldParse[] = 
	{
		{ 0, parseArbitraryFXIntoMap, NULL, 0 },
		{ 0, 0, 0, 0 }
	};

	ini->initFromINI(fxmap, myFieldParse);
}

//-------------------------------------------------------------------------------------------Static
static void parseArbitrarySoundsIntoMap( INI* ini, void *instance, void* /* store */, const void* userData )
{
	PerUnitSoundMap *mapSounds = (PerUnitSoundMap*) instance;
	const char* name = (const char*)userData;
	const char* token = ini->getNextToken();
	
	AudioEventRTS a;
	if (token)
		a.setEventName(token);
	mapSounds->insert(std::make_pair(AsciiString(name), a));	
}

//-------------------------------------------------------------------------------------------------
/** Parse Additional per unit sounds such as TankTurretMove and TankTurretMoveLoop. */
//-------------------------------------------------------------------------------------------------
// ?ThingTemplate::parsePerUnitSounds present-unmatched
void ThingTemplate::parsePerUnitSounds( INI* ini, void *instance, void *store, const void *userData )
{
	PerUnitSoundMap *mapSounds = (PerUnitSoundMap*)store;
	mapSounds->clear();

	static const FieldParse myFieldParse[] = 
	{
		{ 0, parseArbitrarySoundsIntoMap, NULL, 0 },
		{ 0, 0, 0, 0 }
	};

	ini->initFromINI(mapSounds, myFieldParse);
}

//-------------------------------------------------------------------------------------------------
/** Parse modules to add to the existing set of modules. */
//-------------------------------------------------------------------------------------------------
// Native AddModule parser lives in ThingTemplateParseAddModule.cpp.


//-------------------------------------------------------------------------------------------------
/** Parse modules to remove from the existing set of modules. */
//-------------------------------------------------------------------------------------------------
// Native RemoveModule parser lives in ThingTemplateParseRemoveModule.cpp.


//-------------------------------------------------------------------------------------------------
/** Replace the existing tagged modules with the new modules. */
//-------------------------------------------------------------------------------------------------
// Native ReplaceModule parser lives in ThingTemplateParseReplaceModule.cpp.


//-------------------------------------------------------------------------------------------------
/** mark the module(s) as being "Inheritable". */
//-------------------------------------------------------------------------------------------------
// Native inheritable-module parser lives in ThingTemplateParseInheritable.cpp.



//-------------------------------------------------------------------------------------------------
/** mark the module(s) as being "VverrideableByLikeKind". default module will be replaced by any of the exact same class */
//-------------------------------------------------------------------------------------------------
// ?ThingTemplate::OverrideableByLikeKind present-unmatched
void ThingTemplate::OverrideableByLikeKind(INI *ini, void *instance, void *store, const void *userData)
{
	ThingTemplate* self = (ThingTemplate*)instance;	

	ModuleParseMode oldMode = (ModuleParseMode)self->m_moduleParsingMode;
	if (oldMode != MODULEPARSE_NORMAL)
		throw INI_INVALID_DATA;

	self->m_moduleParsingMode = MODULEPARSE_OVERRIDEABLE_BY_LIKE_KIND;

	ini->initFromINI(self, self->getFieldParse());

	self->m_moduleParsingMode = oldMode;
}






//-------------------------------------------------------------------------------------------------
/** Remove the module whose tag matches moduleToRemove. */
//-------------------------------------------------------------------------------------------------
// ?ThingTemplate::removeModuleInfo present-unmatched
Bool ThingTemplate::removeModuleInfo(const AsciiString& moduleToRemove, AsciiString& clearedModuleNameOut)
{
	Bool removed = false;

	// do NOT clear... we only want to modify this if we return true.
	// if we return false, we should leave this unmodified.
	//clearedModuleNameOut.clear();

	if (m_behaviorModuleInfo.clearModuleDataWithTag(moduleToRemove, clearedModuleNameOut))
	{
		DEBUG_ASSERTCRASH(!removed, ("Hmm, multiple removed in ThingTemplate::removeModuleInfo, should this be possible?"));
		removed = true;
	}
	if (m_drawModuleInfo.clearModuleDataWithTag(moduleToRemove, clearedModuleNameOut))
	{
		DEBUG_ASSERTCRASH(!removed, ("Hmm, multiple removed in ThingTemplate::removeModuleInfo, should this be possible?"));
		removed = true;
	}
	if (m_clientUpdateModuleInfo.clearModuleDataWithTag(moduleToRemove, clearedModuleNameOut))
	{
		DEBUG_ASSERTCRASH(!removed, ("Hmm, multiple removed in ThingTemplate::removeModuleInfo, should this be possible?"));
		removed = true;
	}

	return removed;
}

//-------------------------------------------------------------------------------------------------
/// @todo srj -- move this to another file
// ?ArmorTemplateSet::parseArmorTemplateSet present-unmatched
void ArmorTemplateSet::parseArmorTemplateSet( INI* ini )
{
	static const FieldParse myFieldParse[] = 
	{
		{ "Conditions", ArmorSetFlags::parseFromINI, NULL, offsetof( ArmorTemplateSet, m_types ) },
		{ "Armor", INI::parseArmorTemplate,	NULL, offsetof( ArmorTemplateSet, m_template ) },
		{ "DamageFX",	INI::parseDamageFX,	NULL, offsetof( ArmorTemplateSet, m_fx ) },
		{ 0, 0, 0, 0 }
	};

	ini->initFromINI(this, myFieldParse);
}

//-------------------------------------------------------------------------------------------------
// ?ThingTemplate::parseArmorTemplateSet present-unmatched
void ThingTemplate::parseArmorTemplateSet( INI* ini, void *instance, void * /*store*/, const void* /*userData*/ )
{
	ThingTemplate* self = (ThingTemplate*)instance;
	if (self->m_armorCopiedFromDefault == TRUE)
	{
		self->m_armorCopiedFromDefault = FALSE;
		self->m_armorTemplateSets.clear();
	}

	ArmorTemplateSet ws;
	ws.parseArmorTemplateSet(ini);
#if defined(_DEBUG) || defined(_INTERNAL)
	if (ini->getLoadType() != INI_LOAD_CREATE_OVERRIDES)
	{
		for (ArmorTemplateSetVector::const_iterator it = self->m_armorTemplateSets.begin(); it != self->m_armorTemplateSets.end(); ++it)
		{
			if (it->getNthConditionsYes(0) == ws.getNthConditionsYes(0))
			{
				DEBUG_CRASH(("dup armorset condition in %s\n",self->getName().str()));
			}
		}
	}
#endif
	self->m_armorTemplateSets.push_back(ws);
	self->m_armorTemplateSetFinder.clear();
}

//-------------------------------------------------------------------------------------------------
// ?ThingTemplate::parseWeaponTemplateSet present-unmatched
void ThingTemplate::parseWeaponTemplateSet( INI* ini, void *instance, void * /*store*/, const void* /*userData*/ )
{
	ThingTemplate* self = (ThingTemplate*)instance;
	if (self->m_weaponsCopiedFromDefault == TRUE)
	{
		self->m_weaponsCopiedFromDefault = FALSE;
		self->m_weaponTemplateSets.clear();
	}

	WeaponTemplateSet ws;
	ws.parseWeaponTemplateSet(ini, self);
#if defined(_DEBUG) || defined(_INTERNAL)
	if (ini->getLoadType() != INI_LOAD_CREATE_OVERRIDES)
	{
		for (WeaponTemplateSetVector::const_iterator it = self->m_weaponTemplateSets.begin(); it != self->m_weaponTemplateSets.end(); ++it)
		{
			if (it->getNthConditionsYes(0) == ws.getNthConditionsYes(0))
			{
				DEBUG_CRASH(("dup weaponset condition in %s\n",self->getName().str()));
			}
		}
	}
#endif
	self->m_weaponTemplateSets.push_back(ws);
	self->m_weaponTemplateSetFinder.clear();
}

//-------------------------------------------------------------------------------------------------
// Parse the "maxSimultaneousOfType" keyword
// ?ThingTemplate::parseMaxSimultaneous present-unmatched
void ThingTemplate::parseMaxSimultaneous(INI *ini, void *instance, void *store, const void *userData)
{
  // Most of the time, this is an UnsignedShort, but sometimes this is the keyword
  // "DeterminedBySuperweaponRestriction"
  const char DETERMINED_BY_SUPERWEAPON_KEYWORD[] = "DeterminedBySuperweaponRestriction";

  ThingTemplate *myTemplate = (ThingTemplate *)instance;
  DEBUG_ASSERTCRASH ( &myTemplate->m_maxSimultaneousOfType == store, ("Bad store passed to parseMaxSimultaneous" ) );

  const char * token = ini->getNextToken();
  if ( stricmp( token, DETERMINED_BY_SUPERWEAPON_KEYWORD ) == 0 )
  {
    myTemplate->m_maxSimultaneousDeterminedBySuperweaponRestriction = true;
    *(UnsignedShort *)store = 0;
  }
  else
  {
    // Copied from parseUnsignedShort
    Int value = INI::scanInt(token);
    if (value < 0 || value > 65535)
    {
      DEBUG_CRASH(("Bad value parseMaxSimultaneous"));
      throw ERROR_BUG;
    }
    *(UnsignedShort *)store = (UnsignedShort)value;
    myTemplate->m_maxSimultaneousDeterminedBySuperweaponRestriction = false;
  }
}


//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?ThingTemplate::ThingTemplate present-unmatched
ThingTemplate::ThingTemplate() :
	m_geometryInfo(GEOMETRY_SPHERE, FALSE, 1, 1, 1)
{
	m_moduleParsingMode = MODULEPARSE_NORMAL;
	m_reskinnedFrom = NULL;
	m_radarPriority = RADAR_PRIORITY_INVALID;

	m_nextThingTemplate = NULL;
	m_transportSlotCount = 0;
	m_fenceWidth = 0;
	m_fenceXOffset = 0;
	m_visionRange = 0.0f;
	m_shroudClearingRange = -1.0f;
	m_shroudRevealToAllRange = -1.0f;

	m_buildCost = 0;
	m_buildTime = 1;
	m_refundValue = 0;
	m_energyProduction = 0;
	m_energyBonus = 0;
	m_buildCompletion = BC_APPEARS_AT_RALLY_POINT;

	for( Int levelIndex = 0; levelIndex < LEVEL_COUNT; levelIndex++ )
	{
		m_experienceValues[levelIndex] = 0;
		m_experienceRequired[levelIndex] = 0;
		// -1 means "same value as experienceValues for that level"
		m_skillPointValues[levelIndex] = USE_EXP_VALUE_FOR_SKILL_VALUE;
	}
	m_isTrainable = FALSE;
	m_enterGuard = FALSE;
	m_hijackGuard = FALSE;

	m_templateID = 0;
	m_kindof = KINDOFMASK_NONE;
	//m_defaultOwningSide = "";	// unnecessary
	m_isBuildFacility = FALSE;
	m_isPrerequisite = FALSE;
	m_placementViewAngle = 0.0f;
	m_factoryExitWidth = 0.0f;
	m_factoryExtraBibWidth = 0.0f;

	m_selectedPortraitImage = NULL;
	m_buttonImage = NULL;

	m_shadowType = SHADOW_NONE;
	m_shadowSizeX = 0.0f;
	m_shadowSizeY = 0.0f;
	m_shadowOffsetX = 0.0f;
	m_shadowOffsetY = 0.0f;
	m_occlusionDelay = TheGlobalData->m_defaultOcclusionDelay;

	m_structureRubbleHeight = 0;
	m_instanceScaleFuzziness = 0;
	m_threatValue = 0;
	m_maxSimultaneousOfType = 0;	// unlimited
  m_maxSimultaneousLinkKey = NAMEKEY_INVALID; // Not linked
  m_maxSimultaneousDeterminedBySuperweaponRestriction = false;
	m_crusherLevel = 0;			//Unspecified, this object is unable to crush anything!
	m_crushableLevel = 255; //Unspecified, this object is unable to be crushed by anything!

}

//-------------------------------------------------------------------------------------------------
// ThingTemplate::friend_getAIModuleInfo is defined with its retail-matched body in Code/GameEngine/Source/Common/Thing/ModuleInfoGetNthData.cpp (0x0033B387).

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?ThingTemplate::validateAudio present-unmatched
void ThingTemplate::validateAudio()
{
#if defined(_DEBUG) || defined(_INTERNAL)

	#define AUDIO_TEST(y) \
		if (!get##y()->getEventName().isEmpty() && get##y()->getEventName().compareNoCase("NoSound") != 0) { \
			DEBUG_ASSERTLOG(TheAudio->isValidAudioEvent(get##y()), ("Invalid Sound '%s' in Object '%s'. (%s?)\n", #y, getName().str(), get##y()->getEventName().str())); \
		}

	AUDIO_TEST(VoiceSelect)
	AUDIO_TEST(VoiceGroupSelect)
	AUDIO_TEST(VoiceMove)
	AUDIO_TEST(VoiceAttack)
	AUDIO_TEST(VoiceEnter)
	AUDIO_TEST(VoiceFear)
	AUDIO_TEST(VoiceSelectElite)
	AUDIO_TEST(VoiceCreated)
	AUDIO_TEST(VoiceNearEnemy)
	AUDIO_TEST(VoiceTaskUnable)
	AUDIO_TEST(VoiceTaskComplete)
	AUDIO_TEST(VoiceMeetEnemy)
	AUDIO_TEST(VoiceGarrison)
#ifdef ALLOW_SURRENDER
	AUDIO_TEST(VoiceSurrender)
#endif
	AUDIO_TEST(VoiceDefect)
	AUDIO_TEST(VoiceAttackSpecial)
	AUDIO_TEST(VoiceAttackAir)
	AUDIO_TEST(VoiceGuard)

	AUDIO_TEST(SoundMoveStart)
	AUDIO_TEST(SoundMoveStartDamaged)
	AUDIO_TEST(SoundMoveLoop)
	AUDIO_TEST(SoundMoveLoopDamaged)
	AUDIO_TEST(SoundAmbient)
	AUDIO_TEST(SoundAmbientDamaged)
	AUDIO_TEST(SoundAmbientReallyDamaged)
	AUDIO_TEST(SoundAmbientRubble)
	AUDIO_TEST(SoundStealthOn)
	AUDIO_TEST(SoundStealthOff)
	AUDIO_TEST(SoundCreated)

	AUDIO_TEST(SoundOnDamaged)
	AUDIO_TEST(SoundOnReallyDamaged)
	AUDIO_TEST(SoundEnter)
	AUDIO_TEST(SoundExit)
	AUDIO_TEST(SoundPromotedVeteran)
	AUDIO_TEST(SoundPromotedElite)
	AUDIO_TEST(SoundPromotedHero)
	
	#undef AUDIO_TEST

	const PerUnitSoundMap *perUnitSounds = getAllPerUnitSounds();
	if (!perUnitSounds) 
	{
		return;
	}

	for (PerUnitSoundMap::const_iterator it = perUnitSounds->begin(); it != perUnitSounds->end(); ++it) 
	{
		if (!it->second.getEventName().isEmpty() && it->second.getEventName().compareNoCase("NoSound") != 0) 
		{
			DEBUG_ASSERTCRASH(TheAudio->isValidAudioEvent(&it->second), 
												("Invalid UnitSpecificSound '%s' in Object '%s'. (%s?)", 
												it->first.str(), 
												getName().str(), 
												it->second.getEventName().str())); 
		}
	}
#endif
}

//-------------------------------------------------------------------------------------------------
// ThingTemplate::validate is defined with its retail-matched body in Code/GameEngine/Source/Common/Thing/ThingTemplateValidate.cpp (0x0033B4CD).

//-------------------------------------------------------------------------------------------------
// copy the guts of that into this, but preserve this' name, id, and list-links.
// ?ThingTemplate::copyFrom present-unmatched
void ThingTemplate::copyFrom(const ThingTemplate* that)
{
	if (!that)
		return;

	ThingTemplate* next = this->m_nextThingTemplate;
	UnsignedShort id = this->m_templateID;
	AsciiString name = this->m_nameString;

	*this = *that;

	this->m_nextThingTemplate = next;
	this->m_templateID = id;
	this->m_nameString = name;
}

//-------------------------------------------------------------------------------------------------
void ThingTemplate::setCopiedFromDefault()
{
	m_armorCopiedFromDefault = true;
	m_weaponsCopiedFromDefault = true;
	m_behaviorModuleInfo.setCopiedFromDefault(true);
	m_drawModuleInfo.setCopiedFromDefault(true);
	m_clientUpdateModuleInfo.setCopiedFromDefault(true);
}

//-------------------------------------------------------------------------------------------------
// ?ThingTemplate::~ThingTemplate present-unmatched
ThingTemplate::~ThingTemplate()
{
	// note, we don't need to take any special action for Armor/WeaponSets...
	// though it is just a list of 'raw' pointers, we don't have ownership of 'em,
	// and so we MUST NOT delete them
} 

//=============================================================================
// ThingTemplate::resolveNames is defined with its retail-matched body in Code/GameEngine/Source/Common/Thing/Rva0033C2C2ResolveNames.cpp (0x0033C2C2).

//=============================================================================
#ifdef LOAD_TEST_ASSETS
// ?ThingTemplate::initForLTA present-unmatched
void ThingTemplate::initForLTA(const AsciiString& name)
{
	m_nameString = name;

	char buffer[1024];
	strncpy(buffer, name.str(), sizeof(buffer));
	for (int i=0; buffer[i]; i++) {
		if (buffer[i] == '/') {
			i++;
			break;
		}
	}
	m_LTAName = AsciiString(buffer+i);

	m_behaviorModuleInfo.clear();
	m_drawModuleInfo.clear();
	m_clientUpdateModuleInfo.clear();

	AsciiString moduleTag;

	moduleTag.format( "LTA_%sDestroyDie", m_LTAName.str() );
	m_behaviorModuleInfo.addModuleInfo(this, "DestroyDie", moduleTag, TheModuleFactory->newModuleDataFromINI(NULL, "DestroyDie", MODULETYPE_BEHAVIOR, moduleTag), (MODULEINTERFACE_DIE), false);

	moduleTag.format( "LTA_%sInactiveBody", m_LTAName.str() );
	m_behaviorModuleInfo.addModuleInfo(this, "InactiveBody", moduleTag, TheModuleFactory->newModuleDataFromINI(NULL, "InactiveBody", MODULETYPE_BEHAVIOR, moduleTag), (MODULEINTERFACE_BODY), false);

	moduleTag.format( "LTA_%sW3DDefaultDraw", m_LTAName.str() );
	m_drawModuleInfo.addModuleInfo(this, "W3DDefaultDraw", moduleTag, TheModuleFactory->newModuleDataFromINI(NULL, "W3DDefaultDraw", MODULETYPE_DRAW, moduleTag), (MODULEINTERFACE_DRAW), false);

	m_armorCopiedFromDefault = false;
	m_weaponsCopiedFromDefault = false;

	m_kindof = KINDOFMASK_NONE;
	m_assetScale = 1.0f;
	m_instanceScaleFuzziness = 0.0f;	///< tolerance to randomly vary scale per instance
	m_structureRubbleHeight = 0.0f;		// zero means "use global default"
	m_displayName.translate( name );
	m_shadowType = SHADOW_VOLUME;

	m_geometryInfo.set(GEOMETRY_SPHERE, false, 10.0, 10.0, 10.0);
	
}
#endif


//=============================================================================
// ?ThingTemplate::findArmorTemplateSet present-unmatched
const ArmorTemplateSet* ThingTemplate::findArmorTemplateSet(const ArmorSetFlags& t) const
{
  return m_armorTemplateSetFinder.findBestInfo(m_armorTemplateSets, t);
}

//=============================================================================
// ?ThingTemplate::findWeaponTemplateSet present-unmatched
const WeaponTemplateSet* ThingTemplate::findWeaponTemplateSet(const WeaponSetFlags& t) const
{
  return m_weaponTemplateSetFinder.findBestInfo(m_weaponTemplateSets, t);
}

//-----------------------------------------------------------------------------
// returns true iff we have at least one weaponset that contains a weapon.
// returns false if we have no weaponsets, or they are all empty.
// ?ThingTemplate::canPossiblyHaveAnyWeapon present-unmatched
Bool ThingTemplate::canPossiblyHaveAnyWeapon() const
{
	for (WeaponTemplateSetVector::const_iterator it = m_weaponTemplateSets.begin(); 
					it != m_weaponTemplateSets.end();
					++it)
	{
		if (it->hasAnyWeapons())
			return true;
	}
	return false;
}

//-----------------------------------------------------------------------------
// ?ThingTemplate::getSkillPointValue present-unmatched
Int ThingTemplate::getSkillPointValue(Int level) const 
{ 
	Int value = m_skillPointValues[level]; 
	
	if (value == USE_EXP_VALUE_FOR_SKILL_VALUE)
		value = getExperienceValue(level);
	
	return value;
}

//-----------------------------------------------------------------------------
// ThingTemplate::getBuildFacilityTemplate is defined with its retail-matched body in Code/GameEngine/Source/Common/ThingTemplateBuildFacility.cpp (0x0033A97F).

//-------------------------------------------------------------------------------------------------
// ?ThingTemplate::getBuildable present-unmatched
BuildableStatus ThingTemplate::getBuildable() const 
{ 
	BuildableStatus bs;
	if (TheGameLogic && TheGameLogic->findBuildableStatusOverride(this, bs))
		return bs;

	return (BuildableStatus)m_buildable; 
}

//-------------------------------------------------------------------------------------------------
// ?ThingTemplate::getPerUnitFX present-unmatched
const FXList *ThingTemplate::getPerUnitFX(const AsciiString& fxName) const
{
	if (fxName.isEmpty()) 
	{
		return NULL;
	}
	
	PerUnitFXMap::const_iterator it = m_perUnitFX.find(fxName);
	if (it == m_perUnitFX.end()) 
	{
		DEBUG_CRASH(("Unknown FX name (%s) asked for in ThingTemplate (%s). ", fxName.str(), m_nameString.str()));
		return NULL;
	}

	return (it->second);
}

//-------------------------------------------------------------------------------------------------
// ?ThingTemplate::getPerUnitSound present-unmatched
const AudioEventRTS *ThingTemplate::getPerUnitSound(const AsciiString& soundName) const
{
	if (soundName.isEmpty()) 
	{
		return &s_audioEventNoSound;
	}
	
	PerUnitSoundMap::const_iterator it = m_perUnitSounds.find(soundName);
	if (it == m_perUnitSounds.end()) 
	{
#ifndef DO_UNIT_TIMINGS
    DEBUG_LOG(("Unknown Audio name (%s) asked for in ThingTemplate (%s).\n", soundName.str(), m_nameString.str()));
#endif
    return &s_audioEventNoSound;
	}

	return &(it->second);
}

//-------------------------------------------------------------------------------------------------
// ?ThingTemplate::getMaxSimultaneousOfType present-unmatched
UnsignedInt ThingTemplate::getMaxSimultaneousOfType() const
{
  if ( m_maxSimultaneousDeterminedBySuperweaponRestriction && TheGameLogic )
  {
    return TheGameLogic->getSuperweaponRestriction();
  }

  return m_maxSimultaneousOfType;
}




//-------------------------------------------------------------------------------------------------
// BFME2 isEquivalentTo is defined in ThingTemplateIsEquivalentTo.cpp.
// The former Zero Hour donor body is not the retail BFME2 implementation.


//-------------------------------------------------------------------------------------------------
// ?ThingTemplate::isBuildableItem present-unmatched
Bool ThingTemplate::isBuildableItem(void) const
{
	return (getBuildCost() != 0);
}

//-------------------------------------------------------------------------------------------------
/** NOTE that we're not paying attention to m_override here, instead the portions
	* that retrieve template data values use the get() wrappers, which *DO* pay
	* attention to the override values */
//-------------------------------------------------------------------------------------------------
// ?ThingTemplate::calcCostToBuild present-unmatched
Int ThingTemplate::calcCostToBuild( const Player* player) const
{
	if (!player)
		return 0;

	// changePercent format is "-.2 equals 20% cheaper"
	Real factionModifier = 1 + player->getProductionCostChangePercent( getName() );
	factionModifier *= player->getProductionCostChangeBasedOnKindOf( m_kindof );
	return getBuildCost() * factionModifier * player->getHandicap()->getHandicap(Handicap::BUILDCOST, this);
}

//-------------------------------------------------------------------------------------------------
/** NOTE that we're not paying attention to m_override here, instead the portions
	* that retrieve template data values use the get() wrappers, which *DO* pay
	* attention to the override values */
//-------------------------------------------------------------------------------------------------
// ?ThingTemplate::calcTimeToBuild present-unmatched
Int ThingTemplate::calcTimeToBuild( const Player* player) const
{
	Int buildTime = getBuildTime() * LOGICFRAMES_PER_SECOND;
	buildTime *= player->getHandicap()->getHandicap(Handicap::BUILDTIME, this);

	Real factionModifier = 1 + player->getProductionTimeChangePercent( getName() );
	buildTime *= factionModifier;

#if defined (_DEBUG) || defined (_INTERNAL) || defined(_ALLOW_DEBUG_CHEATS_IN_RELEASE)
	if( player->buildsInstantly() )
	{
		buildTime = 1;
	}
#endif

	// Adjust build time based on energy supply.

	Real EnergyPercent = player->getEnergy()->getEnergySupplyRatio();	//I'm at 80% Energy
	if (EnergyPercent > 1.0f)
		EnergyPercent = 1.0f;	// getEnergySupplyRatio() returns a true ratio, but we don't care about excess.
	Real EnergyShort = 1.0f - EnergyPercent;					//so I am 20% short
	EnergyShort *= TheGlobalData->m_LowEnergyPenaltyModifier;	//which is a 40% penalty, or a 10% penalty
	Real penaltyRate = 1.0f - EnergyShort;
	penaltyRate = max(penaltyRate, TheGlobalData->m_MinLowEnergyProductionSpeed);	//bind so 0% does not dead stop you

	if( EnergyPercent < 1.0f )	//and make 99% look like 80% (eg) since most of the time you are down only a little
		penaltyRate = min(penaltyRate, TheGlobalData->m_MaxLowEnergyProductionSpeed);

	if (penaltyRate <= 0.0f)
		penaltyRate = 0.01f;	// Design won't make the minimum 0, they promise

	buildTime /= penaltyRate;//and voila.  Makes sense, designers have control, all is happy.

	//	Multiple build facilities can have an added production bonus.

	if (getBuildCompletion() == BC_APPEARS_AT_RALLY_POINT)
	{
		const ThingTemplate *tmpl = getBuildFacilityTemplate(player);	// could be null if none exist
		Int count = 0;
		if (tmpl)
		{
			player->countObjectsByThingTemplate(1, &tmpl, false, &count);
			Real factoryMult = TheGlobalData->m_MultipleFactory;
			if (factoryMult > 0.0f)
			{
				for(int i=0; i < count - 1; i++)
					buildTime *= factoryMult;
			}
		}
	}

	return(buildTime);
}

//---------------------------------------------------------------------------------------ModuleInfo
//-------------------------------------------------------------------------------------------------
// ?ModuleInfo::friend_getNthData present-unmatched
ModuleData* ModuleInfo::friend_getNthData(Int i)
{
	if (i >= 0 && i < m_info.size())
	{
		// This is kinda naughty, but its necessary.
		return const_cast<ModuleData*>(m_info[i].second);
	}
	return NULL;
}


// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeCallJA@BfmeHookJA@@QAEPAUBfmeSlotJA@@XZ=?getFinalOverride@Overridable@@QBEPBV1@XZ")

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?crc@GeometryInfo@@MAEXPAVXfer@@@Z=??_GRva0050B2A@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:?xfer@GeometryInfo@@MAEXPAVXfer@@@Z=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:?loadPostProcess@GeometryInfo@@MAEXXZ=?name@Rva00050C2BNamed@@QBEPBDXZ")

// Native boundary 0x00331578..0x0033162B (179B), RET 4. The target compares
// scalar words at +8/+18/+28, seven floats at +C/+10/+14/+24/+20/+2C/+30,
// and the two string subobjects at +0/+4 through rowed compare 0x69D6.
// Offset +1C is not read. Equality is the observed behavior; the original
// class, method, field names and association with ThingTemplate are unknown.
class Rva00331578
{
public:
	bool rva00331578(const Rva00331578 &other);

private:
	AsciiString word00, word04;
	unsigned int value08;
	float value0C, value10, value14;
	unsigned int value18;
	char unknown1C[4];
	float value20, value24;
	unsigned int value28;
	float value2C, value30;
};

bool Rva00331578::rva00331578(const Rva00331578 &other)
{
	if (value08 == other.value08 && value0C == other.value0C &&
		value10 == other.value10 && value14 == other.value14 &&
		value18 == other.value18 && word00.compare(other.word00) == 0 &&
		word04.compare(other.word04) == 0 && value24 == other.value24 &&
		value20 == other.value20 && value28 == other.value28 &&
		value2C == other.value2C && value30 == other.value30)
		return true;
	return false;
}
