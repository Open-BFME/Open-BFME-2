// cl: /Ireference/shims/sparse_public /Ireference/shims/bfme_geometryinfo_ctor_link /DBFME_ASCII_DTOR_DECL /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims/bfme_namekey /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/shims -ICode/Libraries/Source/Compression/LZHCompress/CompLibHeader /Ireference/shims/bfme2htree /Ireference/shims/bfme2renderobj /Ireference/shims/bfmecamera /Ireference/shims/bfmelight /Ireference/shims/bfmeparticlehandle /Ireference/shims/bfmeparticleload /Ireference/shims/bfmeparticlequat /Ireference/shims/bfmeparticlesave /Ireference/shims/bfmeparticleline /Ireference/shims/bfme2ray /Ireference/shims/bfme2scene -D_STLP_USE_STATIC_LIB -DNDEBUG -DWIN32 -D_WINDOWS /Ireference/shims/bfmefrustum
// stlport
// Ported verbatim from the Generals Zero Hour reference
// (GameEngine/Source/Common/Thing/ThingTemplate.cpp); this unit had no counterpart under Code/.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
// Retail imports only _strcmpi (stub 0x00629A2A calls msvcr71's); BFME2's
// stricmp spelling resolves there, not to the _stricmp alias.
#define stricmp _strcmpi
#define _STLP_BFME_RB_MINMAX_IMPORT  // inline _Rb_tree_node_base::_S_minimum/_S_maximum without a COMDAT copy (vendor/stlport/stl/_tree.h)
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

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
// The exact assignment specialization is provided by StlportAsciiStringVectorAssign.cpp.
// Keep this consumer on that verified body rather than instantiate the stock copy.
#include <vector>
#include "ascii_string.h"
namespace _STL {
template <> vector<AsciiString, allocator<AsciiString> > &
vector<AsciiString, allocator<AsciiString> >::operator=(const vector<AsciiString, allocator<AsciiString> > &);
}

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

// ZH's BitFlags intersection counters count through std::bitset inlines; retail
// keeps the four-word SWAR bodies out of line in BitFlagsCountIntersection.cpp
// (intersection 0x0033ADC0, inverse 0x0028F55C). The same computation here, so
// this TU emits retail's bytes while findBestInfoSlow keeps the alias knowledge
// the ZH inline gave it (SparseMatchFinder's matched body caches the vector end
// across these calls). BFME2's BitFlags<11> storage is one dword at +0.
template<> inline int BitFlags<11>::countIntersection(const BitFlags<11> &that) const
{
	unsigned v = *(const unsigned *)&m_bits & *(const unsigned *)&that.m_bits;
	v = v - ((v >> 1) & 0x55555555);
	v = (v & 0x33333333) + ((v >> 2) & 0x33333333);
	v = (v + (v >> 4)) & 0x0F0F0F0F;
	return (int)((v * 0x01010101u) >> 24);
}

template<> inline int BitFlags<11>::countInverseIntersection(const BitFlags<11> &that) const
{
	unsigned v = ~*(const unsigned *)&m_bits & *(const unsigned *)&that.m_bits;
	v = v - ((v >> 1) & 0x55555555);
	v = (v & 0x33333333) + ((v >> 2) & 0x33333333);
	v = (v + (v >> 4)) & 0x0F0F0F0F;
	return (int)((v * 0x01010101u) >> 24);
}

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
// bfme link decl-only begin
namespace _STL { template <> void _Construct<WeaponTemplateSet, WeaponTemplateSet>(WeaponTemplateSet *, WeaponTemplateSet const &); }
namespace _STL { template <> void _Destroy<ProductionPrerequisite *>(ProductionPrerequisite *, ProductionPrerequisite *); }
namespace _STL { template <> unsigned long _Base_bitset<4>::_S_maskbit(unsigned int); }
// Retail's ProductionPrerequisite range copy (0x0033E9DE) assigns through the
// out-of-line assign 0x002D0C44; this unit's ZH-layout copy is not that body.
namespace _STL { template <> ProductionPrerequisite *__copy<ProductionPrerequisite *, ProductionPrerequisite *, int>(ProductionPrerequisite *, ProductionPrerequisite *, ProductionPrerequisite *, const random_access_iterator_tag &, int *); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?parse@?$BitFlags@$0HE@@@QAEXPAVINI@@PAVAsciiString@@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class INI; class AsciiString;
template <> void BitFlags<116>::parse(INI *,AsciiString *);

// Retail keeps one vector<ProductionPrerequisite>::push_back (0x0033EA10); this
// unit calls it rather than leading link order with its own copy.
namespace _STL {
template <> void vector<ProductionPrerequisite, allocator<ProductionPrerequisite> >::push_back(const ProductionPrerequisite &);
template <> void _Construct<WeaponTemplateSet, WeaponTemplateSet>(WeaponTemplateSet *, const WeaponTemplateSet &);
}

// Preserve the native comparator's visible read-only contract. The established
// ledger spelling is BitFlags<17>; retail tests 21 bits in its first flag word.
// BitFlags contains only STLport bitset storage: one 32-bit unsigned long at
// offset zero. Read that measured word directly, without the legacy bit-count
// bound checked by BitFlags::test. This does not establish the original count.
typedef char BfmeWeaponFlagsWordSize[(sizeof(unsigned long) == 4) ? 1 : -1];
typedef char BfmeWeaponFlagsStorageSize[(sizeof(BitFlags<17>) == 4) ? 1 : -1];
template <> __declspec(noinline) bool SparseMatchFinder<WeaponTemplateSet, BitFlags<17> >::MapHelper::operator()(const BitFlags<17> &a, const BitFlags<17> &b) const
{
    const unsigned long *aWords = reinterpret_cast<const unsigned long *>(&a);
    const unsigned long *bWords = reinterpret_cast<const unsigned long *>(&b);
    for (int i = 0; i < 21; ++i)
    {
        bool aBit = (aWords[(unsigned)i >> 5] & (1u << (i & 31))) != 0;
        bool bBit = (bWords[(unsigned)i >> 5] & (1u << (i & 31))) != 0;
        if (aBit && !bBit)
            return false;
        if (!aBit && bBit)
            return true;
    }
    return false;
}

// The recovered Weapon map providers own these operations. This donor unit's
// incidental copies differ from retail; refer to the verified bodies instead.
// The existing sparse_public include profile exposes only MapHelper so
// VC7.1 accepts the explicit specialization declarations below.
namespace _STL {
template <> _Rb_tree<const BitFlags<17>, pair<const BitFlags<17>, const WeaponTemplateSet *>, _Select1st<pair<const BitFlags<17>, const WeaponTemplateSet *> >, SparseMatchFinder<WeaponTemplateSet, BitFlags<17> >::MapHelper, allocator<pair<const BitFlags<17>, const WeaponTemplateSet *> > >::_Link_type
_Rb_tree<const BitFlags<17>, pair<const BitFlags<17>, const WeaponTemplateSet *>, _Select1st<pair<const BitFlags<17>, const WeaponTemplateSet *> >, SparseMatchFinder<WeaponTemplateSet, BitFlags<17> >::MapHelper, allocator<pair<const BitFlags<17>, const WeaponTemplateSet *> > >::_M_create_node(const pair<const BitFlags<17>, const WeaponTemplateSet *> &);
template <> pair<_Rb_tree<const BitFlags<17>, pair<const BitFlags<17>, const WeaponTemplateSet *>, _Select1st<pair<const BitFlags<17>, const WeaponTemplateSet *> >, SparseMatchFinder<WeaponTemplateSet, BitFlags<17> >::MapHelper, allocator<pair<const BitFlags<17>, const WeaponTemplateSet *> > >::iterator, bool>
_Rb_tree<const BitFlags<17>, pair<const BitFlags<17>, const WeaponTemplateSet *>, _Select1st<pair<const BitFlags<17>, const WeaponTemplateSet *> >, SparseMatchFinder<WeaponTemplateSet, BitFlags<17> >::MapHelper, allocator<pair<const BitFlags<17>, const WeaponTemplateSet *> > >::insert_unique(const pair<const BitFlags<17>, const WeaponTemplateSet *> &);
template <> _Rb_tree<const BitFlags<17>, pair<const BitFlags<17>, const WeaponTemplateSet *>, _Select1st<pair<const BitFlags<17>, const WeaponTemplateSet *> >, SparseMatchFinder<WeaponTemplateSet, BitFlags<17> >::MapHelper, allocator<pair<const BitFlags<17>, const WeaponTemplateSet *> > >::iterator
_Rb_tree<const BitFlags<17>, pair<const BitFlags<17>, const WeaponTemplateSet *>, _Select1st<pair<const BitFlags<17>, const WeaponTemplateSet *> >, SparseMatchFinder<WeaponTemplateSet, BitFlags<17> >::MapHelper, allocator<pair<const BitFlags<17>, const WeaponTemplateSet *> > >::insert_unique(_Rb_tree<const BitFlags<17>, pair<const BitFlags<17>, const WeaponTemplateSet *>, _Select1st<pair<const BitFlags<17>, const WeaponTemplateSet *> >, SparseMatchFinder<WeaponTemplateSet, BitFlags<17> >::MapHelper, allocator<pair<const BitFlags<17>, const WeaponTemplateSet *> > >::iterator, const pair<const BitFlags<17>, const WeaponTemplateSet *> &);
template <> const WeaponTemplateSet *&
map<const BitFlags<17>, const WeaponTemplateSet *, SparseMatchFinder<WeaponTemplateSet, BitFlags<17> >::MapHelper, allocator<pair<const BitFlags<17>, const WeaponTemplateSet *> > >::operator[](const BitFlags<17> &);
}

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
// ModuleInfo's vector<Nugget> filters live in their own BFME 2 units: clearModuleDataWithTag
// (0x0033C807, Rva0033C807FindErase.cpp), the interface-mask filter (0x0033C84A,
// ModuleInfoRva0033C84A.cpp) and clearAiModuleInfo (0x0033C882, ModuleInfoRva0033C8B5.cpp).
// The Zero Hour copies formerly here (3-bool Nugget) emitted a non-retail
// vector<Nugget>::erase and Nugget::operator= ahead of retail's 0x0033C3BC/0x002CEFCD.

//-------------------------------------------------------------------------------------------------
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
// ThingTemplate::parsePrerequisites is rowed at 0x0033EBB5 with BFME2's body
// (ThingTemplateParsePrerequisites.cpp); the Zero Hour copy here was a second,
// non-retail definition.
// The anchor keeps the two prerequisite field parsers, whose science-vector
// callees this unit rows, emitted.
// ?bfmeAnchorThingTemplatePrereqParsers absent-from-retail
const void *bfmeAnchorThingTemplatePrereqParsers( int science )
{
	return science ? (const void *)parsePrerequisiteScience : (const void *)parsePrerequisiteUnit;
}
// The prerequisite-list clear the Zero Hour parser did keeps the science
// vector's rowed copy helper emitted.
// ?bfmeAnchorThingTemplatePrereqClear absent-from-retail
void bfmeAnchorThingTemplatePrereqClear( std::vector<ProductionPrerequisite> *prereqs )
{
	prereqs->clear();
}

//-------------------------------------------------------------------------------------------Static
// The rowed native callback also belongs to the external UnitSpecificFX table.
void parseArbitraryFXIntoMap( INI* ini, void *instance, void* /* store */, const void* userData )
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
// ??0ThingTemplate@@QAE@XZ is rowed in its own unit; this copy collided with it.

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
// BFME2 copyFrom is recovered in ThingTemplateSetCopiedFromDefault.cpp.

//-------------------------------------------------------------------------------------------------
// ThingTemplate::setCopiedFromDefault is defined with its retail-matched body (four ModuleInfos)
// in Code/GameEngine/Source/Common/Thing/ThingTemplateSetCopiedFromDefault.cpp (0x0033B539).

//-------------------------------------------------------------------------------------------------
// ThingTemplate::~ThingTemplate is defined with its retail-matched body in
// Code/GameEngine/Source/Common/Thing/Rva0033DDA1Dtor.cpp (0x0033DDA1). Zero Hour's
// empty protected destructor emitted a two-slot ZH vftable here that the link kept
// ahead of retail's one-slot ??_7ThingTemplate@@6B@ (LINK-146). This anchor keeps
// emitting the three member destructors rowed in this unit, which that
// destructor used to bring in; it is not a recovered retail function.
// ?bfmeAnchorThingTemplateMemberDtors absent-from-retail
typedef std::vector<ProductionPrerequisite> BfmePrereqVector;
void bfmeAnchorThingTemplateMemberDtors(ModuleInfo *info, BfmePrereqVector *prereqs,
	WeaponTemplateSetFinder *finder)
{
	info->~ModuleInfo();
	prereqs->~BfmePrereqVector();
	finder->~WeaponTemplateSetFinder();
}

//=============================================================================
// ThingTemplate::resolveNames is defined with its retail-matched body in Code/GameEngine/Source/Common/Thing/Rva0033C2C2ResolveNames.cpp (0x0033C2C2).

//=============================================================================
// Zero Hour's LOAD_TEST_ASSETS initForLTA has no BFME 2 body; compiled here, its
// ModuleInfo::clear() calls emitted a non-retail Nugget::operator= (3-bool
// Nugget) ahead of retail's 0x002CEFCD. Kept for reference only.
#if defined(LOAD_TEST_ASSETS) && 0
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
const ArmorTemplateSet* ThingTemplate::findArmorTemplateSet(const ArmorSetFlags& armorSetFlags) const
{
  return m_armorTemplateSetFinder.findBestInfo(m_armorTemplateSets, armorSetFlags);
}

//=============================================================================
// ?ThingTemplate::findWeaponTemplateSet present-unmatched
const WeaponTemplateSet* ThingTemplate::findWeaponTemplateSet(const WeaponSetFlags& weaponSetFlags) const
{
  return m_weaponTemplateSetFinder.findBestInfo(m_weaponTemplateSets, weaponSetFlags);
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
// Target getBuildable is defined by the verified owner in Rva0033A632.cpp.

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
// ThingTemplate::getMaxSimultaneousOfType: its only emitted copy is the inline one in
// GenericObjectCreationNuggetReallyCreate.cpp.




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
		const ThingTemplate *thingTemplate = getBuildFacilityTemplate(player);	// could be null if none exist
		Int count = 0;
		if (thingTemplate)
		{
			player->countObjectsByThingTemplate(1, &thingTemplate, false, &count);
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
#pragma comment(linker, "/alternatename:?bfmeCallJA@BfmeHookJA@@QAEPAUBfmeSlotJA@@XZ=?getFinalOverride@Rva001E35DFView@@QBEPBV1@XZ")

// Preserve this unit's existing vector allocation helper after moving the
// unfinished copyFrom caller. This member pointer only retains emission;
// it is a compile anchor and makes no retail data or assignment-body claim.
namespace _STL {
template _Vector_base<ScienceType, allocator<ScienceType> >::_Vector_base(size_t, const allocator<ScienceType> &);
// Its rowed ScienceType range copy was instantiated through this unit's
// ProductionPrerequisite copy, which the unit now calls (0x0033E9DE).
template ScienceType *__copy<const ScienceType *, ScienceType *, int>(const ScienceType *, const ScienceType *, ScienceType *, const random_access_iterator_tag &, int *);
}

// clearCopiedFromDefaultEntries (gone, see above) was this unit's user of the
// KindOf bitset AND row; a compile anchor, not a retail data claim, keeps it.
extern void (_STL::_Base_bitset<4>::*const _bfmeInlineAnchorBitsetAnd)(const _STL::_Base_bitset<4> &) =
    &_STL::_Base_bitset<4>::_M_do_and;
