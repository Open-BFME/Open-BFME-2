// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /O1 /I. /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/stlp_nodealloc /Ireference/shims/w3dmodeldraw /Ireference/open-bfme-1/inputs/reference/shims/asciistring8 /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/game/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
//
// ?doSingleBoneName@@YA_NPAVRenderObjClass@@ABVAsciiString@@AAV?$map@W4NameKeyType@@UPristineBoneInfo@@U?$less@W4NameKeyType@@@_STL@@V?$allocator@U?$pair@$$CBW4NameKeyType@@UPristineBoneInfo@@@_STL@@@4@@_STL@@@Z
// retail 0x000BD2BF, 488 bytes. Dedicated TU ported from the Open-BFME-1
// donor game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDraw.cpp (reference/open-bfme-1 @ 6d943426).
// The donor body does not place at BFME 1's flags; compiled /O1 it is
// byte-identical to retail once relocations are masked (unique hit on
// unclaimed .text). Only the placed body is defined here; the donor's
// other definitions are omitted.
// stlport
#include "reference/shims/bfme2_ascii/string_base.h"
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

// FILE: W3DModelDraw.cpp ///////////////////////////////////////////////////////////////////////
// Author: Colin Day, November 2001
// Desc:   Default w3d draw module
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////

#define DEFINE_W3DANIMMODE_NAMES
#define DEFINE_WEAPONSLOTTYPE_NAMES
#define _BFME_RETAIL_TREE_INSERT_LAYOUT

#define NO_DEBUG_CRC

#include "Common/CRC.h"
#include "Common/CRCDebug.h"
#include "Common/GameState.h"
#include "Common/GlobalData.h"
#include "Common/PerfTimer.h"
#include "Common/RandomValue.h"
#include "Common/ThingTemplate.h"
#include "Common/GameLOD.h"
#include "Common/Xfer.h"
#include "Common/GameState.h"
#include "Common/QuickTrig.h"
#include "GameClient/Drawable.h"
#include "GameClient/FXList.h"
#include "GameClient/Shadow.h"
#include "GameLogic/GameLogic.h"		// for real-time frame
#include "GameLogic/Object.h"
#include "GameLogic/WeaponSet.h"
#include "GameLogic/FPUControl.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/PhysicsUpdate.h"
#include "W3DDevice/GameClient/Module/W3DModelDraw.h"
#include "W3DDevice/GameClient/W3DAssetManager.h"
#include "W3DDevice/GameClient/W3DDisplay.h"
#include "W3DDevice/GameClient/W3DScene.h"
#include "W3DDevice/GameClient/W3DShadow.h"
#include "W3DDevice/GameClient/W3DTerrainTracks.h"
#include "W3DDevice/GameClient/WorldHeightMap.h"
#include "WW3D2/HAnim.h"
#include "WW3D2/HLod.h"
#include "WW3D2/RendObj.h"
#include "WW3D2/Mesh.h"
#include "WW3D2/MeshMdl.h"
#include "Common/BitFlagsIO.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

//-------------------------------------------------------------------------------------------------
static inline Bool isValidTimeToCalcLogicStuff()
{
	return (TheGameLogic && TheGameLogic->isInGameLogicUpdate()) ||
		(TheGameState && TheGameState->isInLoadGame());
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

// The native map subscript is provided out of line at 0x000BCF68.
namespace _STL { template <> PristineBoneInfo &map<NameKeyType, PristineBoneInfo, less<NameKeyType>, allocator<pair<const NameKeyType, PristineBoneInfo> > >::operator[](const NameKeyType &); }

#if defined(DEBUG_CRC) && (defined(_DEBUG) || defined(_INTERNAL))
#include <cstdarg>
// bfme link decl-only begin
namespace _STL { template <> void _Construct<pair<NameKeyType const, PristineBoneInfo>, pair<NameKeyType const, PristineBoneInfo> >(pair<NameKeyType const, PristineBoneInfo> *, pair<NameKeyType const, PristineBoneInfo> const &); }
namespace _STL { template <> PristineBoneInfo & map<NameKeyType, PristineBoneInfo, less<NameKeyType>, allocator<pair<NameKeyType const, PristineBoneInfo> > >::operator[](NameKeyType const &); }
namespace _STL { template <> _Rb_tree_node<pair<NameKeyType const, PristineBoneInfo> > * _Rb_tree<NameKeyType, pair<NameKeyType const, PristineBoneInfo>, _Select1st<pair<NameKeyType const, PristineBoneInfo> >, less<NameKeyType>, allocator<pair<NameKeyType const, PristineBoneInfo> > >::_M_create_node(pair<NameKeyType const, PristineBoneInfo> const &); }
namespace _STL { template <> _Rb_tree_iterator<pair<NameKeyType const, PristineBoneInfo>, _Nonconst_traits<pair<NameKeyType const, PristineBoneInfo> > > _Rb_tree<NameKeyType, pair<NameKeyType const, PristineBoneInfo>, _Select1st<pair<NameKeyType const, PristineBoneInfo> >, less<NameKeyType>, allocator<pair<NameKeyType const, PristineBoneInfo> > >::_M_insert(_Rb_tree_node_base *, _Rb_tree_node_base *, pair<NameKeyType const, PristineBoneInfo> const &, _Rb_tree_node_base *); }
namespace _STL { template <> _Rb_tree_iterator<pair<NameKeyType const, PristineBoneInfo>, _Nonconst_traits<pair<NameKeyType const, PristineBoneInfo> > > map<NameKeyType, PristineBoneInfo, less<NameKeyType>, allocator<pair<NameKeyType const, PristineBoneInfo> > >::insert(_Rb_tree_iterator<pair<NameKeyType const, PristineBoneInfo>, _Nonconst_traits<pair<NameKeyType const, PristineBoneInfo> > >, pair<NameKeyType const, PristineBoneInfo> const &); }
namespace _STL { template <> _Rb_tree_iterator<pair<NameKeyType const, PristineBoneInfo>, _Nonconst_traits<pair<NameKeyType const, PristineBoneInfo> > > _Rb_tree<NameKeyType, pair<NameKeyType const, PristineBoneInfo>, _Select1st<pair<NameKeyType const, PristineBoneInfo> >, less<NameKeyType>, allocator<pair<NameKeyType const, PristineBoneInfo> > >::insert_unique(_Rb_tree_iterator<pair<NameKeyType const, PristineBoneInfo>, _Nonconst_traits<pair<NameKeyType const, PristineBoneInfo> > >, pair<NameKeyType const, PristineBoneInfo> const &); }
namespace _STL { template <> pair<_Rb_tree_iterator<pair<NameKeyType const, PristineBoneInfo>, _Nonconst_traits<pair<NameKeyType const, PristineBoneInfo> > >, bool> _Rb_tree<NameKeyType, pair<NameKeyType const, PristineBoneInfo>, _Select1st<pair<NameKeyType const, PristineBoneInfo> >, less<NameKeyType>, allocator<pair<NameKeyType const, PristineBoneInfo> > >::insert_unique(pair<NameKeyType const, PristineBoneInfo> const &); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??A?$map@W4NameKeyType@@UPristineBoneInfo@@U?$less@W4NameKeyType@@@_STL@@V?$allocator@U?$p:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
enum NameKeyType; struct PristineBoneInfo;
namespace _STL { template <> PristineBoneInfo &map<NameKeyType, PristineBoneInfo, less<NameKeyType>, allocator<pair<const NameKeyType, PristineBoneInfo> > >::operator[](const NameKeyType &); }
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MiniLog.h
class LogClass
{
public:
	LogClass(const char *fname);
	~LogClass();
	void log(const char *fmt, ...);
	void dumpMatrix3D(const Matrix3D *m, AsciiString name, AsciiString fname, Int line);
	void dumpReal(Real r, AsciiString name, AsciiString fname, Int line);

protected:
	FILE *m_fp;
};

LogClass BonePosLog("bonePositions.txt");

#define BONEPOS_LOG(x) BonePosLog.log x
#define BONEPOS_DUMPMATRIX3D(x) BONEPOS_DUMPMATRIX3DNAMED(x, #x)
#define BONEPOS_DUMPMATRIX3DNAMED(x, y) BonePosLog.dumpMatrix3D(x, y, __FILE__, __LINE__)
#define BONEPOS_DUMPREAL(x) BONEPOS_DUMPREALNAMED(x, #x)
#define BONEPOS_DUMPREALNAMED(x, y) BonePosLog.dumpReal(x, y, __FILE__, __LINE__)

#else // DEBUG_CRC

#define BONEPOS_LOG(x) {}
#define BONEPOS_DUMPMATRIX3D(x) {}
#define BONEPOS_DUMPMATRIX3DNAMED(x, y) {}
#define BONEPOS_DUMPREAL(x) {}
#define BONEPOS_DUMPREALNAMED(x, y) {}

#endif // DEBUG_CRC

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

#if defined(_DEBUG) || defined(_INTERNAL)
extern AsciiString TheThingTemplateBeingParsedName;
extern Real TheSkateDistOverride;
#endif

// flags that aren't read directly from INI, but set in response to various other situations
enum INIReadFlagsType
{
	ANIMS_COPIED_FROM_DEFAULT_STATE = 0,
	GOT_NONIDLE_ANIMS,
	GOT_IDLE_ANIMS,
};

enum ACBits
{
	RANDOMIZE_START_FRAME = 0,
	START_FRAME_FIRST,
	START_FRAME_LAST,
	ADJUST_HEIGHT_BY_CONSTRUCTION_PERCENT,
	PRISTINE_BONE_POS_IN_FINAL_FRAME,
	MAINTAIN_FRAME_ACROSS_STATES,
	RESTART_ANIM_WHEN_COMPLETE,
	MAINTAIN_FRAME_ACROSS_STATES2,
	MAINTAIN_FRAME_ACROSS_STATES3,
	MAINTAIN_FRAME_ACROSS_STATES4,
};

static const char *ACBitsNames[] =
{
	"RANDOMSTART",
	"START_FRAME_FIRST",
	"START_FRAME_LAST",
	"ADJUST_HEIGHT_BY_CONSTRUCTION_PERCENT",
	"PRISTINE_BONE_POS_IN_FINAL_FRAME",
	"MAINTAIN_FRAME_ACROSS_STATES",
	"RESTART_ANIM_WHEN_COMPLETE",
	"MAINTAIN_FRAME_ACROSS_STATES2",
	"MAINTAIN_FRAME_ACROSS_STATES3",
	"MAINTAIN_FRAME_ACROSS_STATES4",
	
	NULL
};

static const Int ALL_MAINTAIN_FRAME_FLAGS =
	(1<<MAINTAIN_FRAME_ACROSS_STATES) |
	(1<<MAINTAIN_FRAME_ACROSS_STATES2) |
	(1<<MAINTAIN_FRAME_ACROSS_STATES3) |
	(1<<MAINTAIN_FRAME_ACROSS_STATES4);

inline Bool isAnyMaintainFrameFlagSet(Int flags)
{
	return (flags & ALL_MAINTAIN_FRAME_FLAGS) != 0;
}

inline Bool isCommonMaintainFrameFlagSet(Int a, Int b)
{
	a &= ALL_MAINTAIN_FRAME_FLAGS;
	b &= ALL_MAINTAIN_FRAME_FLAGS;
	return (a & b) != 0;
}

/** @todo: Move this to some kind of INI file*/
//
// Note: these values are saved in save files, so you MUST NOT REMOVE OR CHANGE
// existing values!
//
static char *TerrainDecalTextureName[TERRAIN_DECAL_MAX]=
{
#ifdef ALLOW_DEMORALIZE
	"DM_RING",//demoralized
#else
	"TERRAIN_DECAL_DEMORALIZED_OBSOLETE",
#endif
	"EXHorde",//enthusiastic
	"EXHorde_UP", //enthusiastic with nationalism 
	"EXHordeB",//enthusiastic vehicle
	"EXHordeB_UP", //enthusiastic vehicle with nationalism
	"EXJunkCrate",//Marks a crate as special
	"EXHordeC_UP", //enthusiastic with fanaticism 
	"EXChemSuit", //Marks a unit as having chemical suit on
	"",	//dummy entry for TERRAIN_DECAL_NONE
	"" //dummy entry for TERRAIN_DECAL_SHADOW_TEXTURE
};

const UnsignedInt NO_NEXT_DURATION = 0xffffffff;

//-------------------------------------------------------------------------------------------------
inline Bool testFlagBit(Int flags, Int bit)
{
	return (flags & (1<<bit)) != 0;
}

//-------------------------------------------------------------------------------------------------
// Target-only dispatch prefix: native B6B4F calls vslots C8 and CC.
// CC returns Matrix3D by value through a hidden 48-byte result buffer;
// these slots and ABI differ from the BFME 1 donor declaration. Unused
// slots stay opaque and no complete RenderObjClass layout is asserted.
// WB921920 supplies the helper identity; retail supplies every byte.
class RetailBoneRenderView {public:
virtual void slot00();
virtual void slot01();
virtual void slot02();
virtual void slot03();
virtual void slot04();
virtual void slot05();
virtual void slot06();
virtual void slot07();
virtual void slot08();
virtual void slot09();
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot20();
virtual void slot21();
virtual void slot22();
virtual void slot23();
virtual void slot24();
virtual void slot25();
virtual void slot26();
virtual void slot27();
virtual void slot28();
virtual void slot29();
virtual void slot30();
virtual void slot31();
virtual void slot32();
virtual void slot33();
virtual void slot34();
virtual void slot35();
virtual void slot36();
virtual void slot37();
virtual void slot38();
virtual void slot39();
virtual void slot40();
virtual void slot41();
virtual void slot42();
virtual void slot43();
virtual void slot44();
virtual void slot45();
virtual void slot46();
virtual void slot47();
virtual void slot48();
virtual void slot49();
virtual int Get_Bone_Index(const char*);
virtual Matrix3D Get_Bone_Transform(int);
};
static Bool findSingleBone(RenderObjClass* robj, const AsciiString& boneName, Matrix3D& mtx, Int& boneIndex)
{
	if (((const StringBase<char>*)&boneName)->isNone() || boneName.isEmpty())
		return false;

	boneIndex = ((RetailBoneRenderView*)robj)->Get_Bone_Index(boneName.str());
	if (boneIndex != 0)
	{
		mtx = ((RetailBoneRenderView*)robj)->Get_Bone_Transform(boneIndex);
		return true;
	}
	else
	{
		return false;
	}
}

//-------------------------------------------------------------------------------------------------
// Native B6BF0..B6CF1 and WB921AF0 identify the subobject helper.
// Only called root-object slots are typed; the verified donor child
// transform validity and reference-count handling remain unchanged.
class RetailSubObjRenderView {public:
virtual void slot00();
virtual void slot01();
virtual void slot02();
virtual void slot03();
virtual void slot04();
virtual void slot05();
virtual void slot06();
virtual void slot07();
virtual void slot08();
virtual void slot09();
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot20();
virtual void slot21();
virtual void slot22();
virtual void slot23();
virtual void slot24();
virtual void slot25();
virtual void slot26();
virtual void slot27();
virtual int Get_Num_Sub_Objects()const;
virtual void slot29();
virtual RenderObjClass*Get_Sub_Object(int)const;
virtual void slot31();
virtual RenderObjClass*Get_Sub_Object_By_Name(const char*,int * =0)const;
virtual void slot33();
virtual void slot34();
virtual int Get_Sub_Object_Bone_Index(int,int)const;
};
static Bool findSingleSubObj(RenderObjClass* robj, const AsciiString& boneName, Matrix3D& mtx, Int& boneIndex)
{
	if (((const StringBase<char>*)&boneName)->isNone() || boneName.isEmpty())
		return false;

	RenderObjClass* childObject = ((RetailSubObjRenderView*)robj)->Get_Sub_Object_By_Name(boneName.str());
	if (childObject)
	{
		mtx = childObject->Get_Transform();

		// you'd think this would work, but, it does not. do it the hard way.
		// boneIndex = childObject->Get_Sub_Object_Bone_Index(childObject);

		for (Int subObj = 0; subObj < ((RetailSubObjRenderView*)robj)->Get_Num_Sub_Objects(); subObj++)
		{	
			RenderObjClass* test = ((RetailSubObjRenderView*)robj)->Get_Sub_Object(subObj);
			if (test == childObject)
			{
				boneIndex = ((RetailSubObjRenderView*)robj)->Get_Sub_Object_Bone_Index(0, subObj);
#if defined(_DEBUG) || defined(_INTERNAL)
				test->Release_Ref();
				test = ((RetailSubObjRenderView*)robj)->Get_Sub_Object_On_Bone(0, boneIndex);
				DEBUG_ASSERTCRASH(test != NULL && test == childObject, ("*** ASSET ERROR: Hmm, bone problem"));
#endif
			}
			if (test) test->Release_Ref();
		}

		childObject->Release_Ref();

		return true;
	}
	else
	{
		return false;
	}
}

//-------------------------------------------------------------------------------------------------
static Bool doSingleBoneName(RenderObjClass* robj, const AsciiString& boneName, PristineBoneInfoMap& map)
{
	Bool foundAsBone = false;
	Bool foundAsSubObj = false;

	PristineBoneInfo info;
	AsciiString tmp;

	AsciiString boneNameTmp = boneName;
	boneNameTmp.toLower();	// convert to all-lowercase to avoid case sens issues later

	setFPMode();

	if (findSingleBone(robj, boneNameTmp, info.mtx, info.boneIndex))
	{
//DEBUG_LOG(("added bone %s\n",boneNameTmp.str()));
		BONEPOS_LOG(("Caching bone %s (index %d)\n", boneNameTmp.str(), info.boneIndex));
		BONEPOS_DUMPMATRIX3D(&(info.mtx));

		map[NAMEKEY(boneNameTmp)] = info;
		foundAsBone = true;
	}

	for (Int i = 1; i <= 99; ++i)
	{
		tmp.format("%s%02d", boneNameTmp.str(), i);
		if (findSingleBone(robj, tmp, info.mtx, info.boneIndex))
		{
//DEBUG_LOG(("added bone %s\n",tmp.str()));
			BONEPOS_LOG(("Caching bone %s (index %d)\n", tmp.str(), info.boneIndex));
			BONEPOS_DUMPMATRIX3D(&(info.mtx));
			map[NAMEKEY(tmp)] = info;
			foundAsBone = true;
		}
		else
		{
			break;
		}
	}

	if (!foundAsBone)
	{
		if (findSingleSubObj(robj, boneNameTmp, info.mtx, info.boneIndex))
		{
//DEBUG_LOG(("added subobj %s\n",boneNameTmp.str()));
			BONEPOS_LOG(("Caching bone from subobject %s (index %d)\n", boneNameTmp.str(), info.boneIndex));
			BONEPOS_DUMPMATRIX3D(&(info.mtx));
			map[NAMEKEY(boneNameTmp)] = info;
			foundAsSubObj = true;
		}

		for (Int i = 1; i <= 99; ++i)
		{
			tmp.format("%s%02d", boneNameTmp.str(), i);
			if (findSingleSubObj(robj, tmp, info.mtx, info.boneIndex))
			{
//DEBUG_LOG(("added subobj %s\n",tmp.str()));
				BONEPOS_LOG(("Caching bone from subobject %s (index %d)\n", tmp.str(), info.boneIndex));
				BONEPOS_DUMPMATRIX3D(&(info.mtx));
				map[NAMEKEY(tmp)] = info;
				foundAsSubObj = true;
			}
			else
			{
				break;
			}
		}
	}

	return foundAsBone || foundAsSubObj;
}

 

 

#ifdef CACHE_ATTACH_BONE

#endif

//-------------------------------------------------------------------------------------------------
enum ParseCondStateType
{
	PARSE_NORMAL,
	PARSE_DEFAULT,
	PARSE_TRANSITION,
	PARSE_ALIAS
};

//-------------------------------------------------------------------------------------------------
static void parseAsciiStringLC( INI* ini, void * /*instance*/, void *store, const void* /*userData*/ )
{
	AsciiString* asciiString = (AsciiString *)store;
	*asciiString = ini->getNextAsciiString();
	asciiString->toLower();
}

//-------------------------------------------------------------------------------------------------
enum AnimParseType
{
	ANIM_NORMAL,
	ANIM_IDLE
};

//-------------------------------------------------------------------------------------------------
static void parseAnimation(INI* ini, void *instance, void * /*store*/, const void* userData)
{
	AnimParseType animType = (AnimParseType)(UnsignedInt)userData;

	AsciiString animName = ini->getNextAsciiString();
	animName.toLower();

	const char* distanceCoveredToken = ini->getNextTokenOrNull();
	Real distanceCovered = distanceCoveredToken ? INI::scanReal(distanceCoveredToken) : 0;
	DEBUG_ASSERTCRASH(!(animType == ANIM_IDLE && distanceCovered != 0), ("You should not specify nonzero DistanceCovered values for Idle Anims"));

	const char* timesToRepeatToken = ini->getNextTokenOrNull();
	Int timesToRepeat = timesToRepeatToken ? INI::scanInt(timesToRepeatToken) : 1;
	if (timesToRepeat < 1) timesToRepeat = 1;

	W3DAnimationInfo animInfo(animName, (animType == ANIM_IDLE), distanceCovered);

	ModelConditionInfo* self = (ModelConditionInfo*)instance;
	if (self->m_iniReadFlags & (1<<ANIMS_COPIED_FROM_DEFAULT_STATE))
	{
		self->m_iniReadFlags &= ~((1<<ANIMS_COPIED_FROM_DEFAULT_STATE)|(1<<GOT_IDLE_ANIMS)|(1<<GOT_NONIDLE_ANIMS));
		self->m_animations.clear();
	}

	if (animInfo.isIdleAnim())
		self->m_iniReadFlags |= (1<<GOT_IDLE_ANIMS);
	else
		self->m_iniReadFlags |= (1<<GOT_NONIDLE_ANIMS);

	if (!animName.isEmpty() && !animName.isNone())
	{
		while (timesToRepeat--)
			self->m_animations.push_back(animInfo);
	}
}	

//-------------------------------------------------------------------------------------------------
static void parseShowHideSubObject(INI* ini, void *instance, void *store, const void* userData)
{
	std::vector<ModelConditionInfo::HideShowSubObjInfo>* vec = (std::vector<ModelConditionInfo::HideShowSubObjInfo>*)store;
	AsciiString subObjName = ini->getNextAsciiString();
	subObjName.toLower();

	// handle "None"
	if (subObjName.isNone())
	{
		vec->clear();
		return;
	}

	while (subObjName.isNotEmpty())
	{
		Bool found = false;
		for (std::vector<ModelConditionInfo::HideShowSubObjInfo>::iterator it = vec->begin(); it != vec->end(); ++it)
		{
			if (stricmp(it->subObjName.str(), subObjName.str()) == 0)
			{
				it->hide = (userData != NULL);
				found = true;
			}
		}
		
		if (!found)
		{
			ModelConditionInfo::HideShowSubObjInfo info;
			info.subObjName = subObjName;
			info.hide = (userData != NULL);
			vec->push_back(info);
		}
		subObjName = ini->getNextAsciiString();
		subObjName.toLower();
	}
}	

//-------------------------------------------------------------------------------------------------
static void parseWeaponBoneName(INI* ini, void *instance, void * store, const void* /*userData*/)
{
	ModelConditionInfo* self = (ModelConditionInfo*)instance;
	AsciiString* arr = (AsciiString*)store;
	
	WeaponSlotType wslot = (WeaponSlotType)INI::scanIndexList(ini->getNextToken(), TheWeaponSlotTypeNames);
	arr[wslot] = ini->getNextAsciiString();
	arr[wslot].toLower();
	if (arr[wslot].isNone())
		arr[wslot].clear();

	if (self)
		self->addPublicBone(arr[wslot]);
}

//-------------------------------------------------------------------------------------------------
static void parseParticleSysBone(INI* ini, void *instance, void * store, const void * /*userData*/)
{
	ParticleSysBoneInfo info;
	info.boneName = ini->getNextAsciiString();
	info.boneName.toLower();
	ini->parseParticleSystemTemplate(ini, instance, &(info.particleSystemTemplate), NULL);
	ModelConditionInfo *self = (ModelConditionInfo *)instance;
	self->m_particleSysBones.push_back(info);
}

//-------------------------------------------------------------------------------------------------
static void parseRealRange( INI *ini, void *instance, void *store, const void* /*userData*/ )
{
	ModelConditionInfo *self = (ModelConditionInfo *)instance;

	const char *token = ini->getNextToken();
	self->m_animMinSpeedFactor = ini->scanReal( token );
	token = ini->getNextToken();
	self->m_animMaxSpeedFactor = ini->scanReal( token );
}

//-------------------------------------------------------------------------------------------------
static void parseLowercaseNameKey(INI* ini, void *instance, void * store, const void * /*userData*/)
{
	NameKeyType* key = (NameKeyType*)store;

	AsciiString tmp = ini->getNextToken();
	tmp.toLower();

	*key = NAMEKEY(tmp.str());
}

//-------------------------------------------------------------------------------------------------
static void parseBoneNameKey(INI* ini, void *instance, void * store, const void * /*userData*/)
{
	ModelConditionInfo* self = (ModelConditionInfo*)instance;
	NameKeyType* key = (NameKeyType*)store;

	AsciiString tmp = ini->getNextToken();
	tmp.toLower();

	if (self)
		self->addPublicBone(tmp);

	if (tmp.isEmpty() || tmp.isNone())
		*key = NAMEKEY_INVALID;
	else
		*key = NAMEKEY(tmp.str());
}

//-------------------------------------------------------------------------------------------------
struct RetailConditionFlags00765B20
{
	UnsignedInt m_words[10];

	Bool operator==(const RetailConditionFlags00765B20& that) const
	{
		for (UnsignedInt i = 0; i < 10; ++i)
		{
			if (m_words[i] != that.m_words[i])
				return false;
		}
		return true;
	}
};

struct RetailModelConditionInfo00765B20
{
	RetailConditionFlags00765B20 m_conditions;
	Byte m_rest[0x100];
};

struct RetailConditionVector00765B20
{
	const RetailModelConditionInfo00765B20 *m_begin;
	const RetailModelConditionInfo00765B20 *m_end;
};

static Bool doesStateExist(const ModelConditionVector& modelConditionVector, const ModelConditionFlags& modelConditionFlags)
{
	const RetailConditionVector00765B20& retailVector =
		*reinterpret_cast<const RetailConditionVector00765B20 *>(&modelConditionVector);
	const RetailConditionFlags00765B20& retailFlags =
		*reinterpret_cast<const RetailConditionFlags00765B20 *>(&modelConditionFlags);
	for (const RetailModelConditionInfo00765B20 *it = retailVector.m_begin;
		 it != retailVector.m_end; ++it)
	{
		if (retailFlags == it->m_conditions)
			return true;
	}
	return false;
}

//-------------------------------------------------------------------------------------------------
static Int countOnBits(UnsignedInt val)
{
	Int count = 0;
	for (Int i = 0; i < 32; ++i)
	{
		if (val & 1) 
			++count;
		val >>= 1;
	}
	return count;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

/**collect some stats about the rendering cost of this draw module */
#if defined(_DEBUG) || defined(_INTERNAL)	

#endif //_DEBUG || _INTERNAL

/**recurse through sub-objs to collect stats about the rendering cost of this draw module */
#if defined(_DEBUG) || defined(_INTERNAL)	

#endif //_DEBUG || _INTERNAL

//-------------------------------------------------------------------------------------------------
// Retail does not go through enableShadowInvisible: it writes the flag straight
// into each sub-object's own byte at +0x05, and the two writes are NOT the same
// expression -- the first takes the argument and the second re-reads the member
// it just stored. That is one character in the source and three bytes in the
// object, so it is written as retail has it rather than tidied into one variable.
//
// The trailing call is also not doStartOrStopParticleSys: it is a plain call with
// `this' unchanged and nothing pushed, to a zero-argument member that is unnamed
// in the image. It is reached here through the same view spelling the donor
// pinned it under, which says what the call site does with it and asserts no more.
struct BfmeShroudSubObject
{
	unsigned char m_unreconstructed_000[ 5 ];
	Bool m_obscured;					///< retail this+0x05
};

class BfmeW3DModelDrawShroud
{
public:
	void updateSubObjectsFromShroud( void );		///< retail 0x00762500

	unsigned char m_unreconstructed_000[ 0x2d ];
	Bool m_fullyObscuredByShroud;				///< retail this+0x2D
	unsigned char m_unreconstructed_02e[ 0x3c - 0x2e ];
	BfmeShroudSubObject *m_shadow;				///< retail this+0x3C
	BfmeShroudSubObject *m_terrainDecal;			///< retail this+0x40
};

//-------------------------------------------------------------------------------------------------
static Bool isAnimationComplete(RenderObjClass* renderObj)
{
	if (renderObj && renderObj->Class_ID() == RenderObjClass::CLASSID_HLOD)
	{
		HLodClass *hlod = (HLodClass*)renderObj;
		return hlod->Is_Animation_Complete();
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/**
	Utility function to make it easier to recursively hide all objects connected to a certain bone.
	We will hide all objects connected to bones which are children of boneIdx
*/
static void doHideShowBoneSubObjs(Bool state, Int numSubObjects, Int boneIdx, RenderObjClass *fullObject, const HTreeClass *htree)
{
	for (Int i=0; i < numSubObjects; i++) 
	{
		RenderObjClass *childObject = fullObject->Get_Sub_Object(i);
		if (childObject)
		{
			Int parentBoneIndex = fullObject->Get_Sub_Object_Bone_Index(childObject);
			childObject->Release_Ref();
			while (parentBoneIndex > 0 && parentBoneIndex < fullObject->Get_Num_Bones())
			{
				parentBoneIndex = htree->Get_Parent_Index(parentBoneIndex);
				if (parentBoneIndex == boneIdx)
				{
					childObject = fullObject->Get_Sub_Object(i);
					if (childObject)
					{
						childObject->Set_Hidden(state);
						childObject->Release_Ref();
					}
					break;
				}
			}
		}
	}
}

//void W3DModelDraw::handleClientFlagPositioning()
//{
//	const ModelConditionInfo::TurretInfo& tur = m_curState->m_turrets[tslot];
//	Real turretAngle = TheGlobalData->m_downwindAngle;
//	if (tur.m_flagAngleBone )
//	{
//		Matrix3D turretXfrm(1);
//		turretXfrm.Rotate_Z(turretAngle);
//		if (m_renderObject)
//		{
//			m_renderObject->Capture_Bone( tur.m_turretAngleBone );
//			m_renderObject->Control_Bone( tur.m_turretAngleBone, turretXfrm );	
//		}
//	}
//}

//-------------------------------------------------------------------------------------------------
#if defined(_DEBUG) || defined(_INTERNAL)	//art wants to see buildings without flags as a test.

#endif

//-------------------------------------------------------------------------------------------------
static Bool turretNamesDiffer(const ModelConditionInfo* modelConditionInfo, const ModelConditionInfo* b)
{
	struct RetailModelConditionInfo
	{
		struct TurretInfo
		{
			UnsignedInt m_turretAngleNameKey;
			UnsignedInt m_turretPitchNameKey;
			char m_padding[0x10];
		};

		char m_padding[0xf0];
		TurretInfo m_turrets[2];
		char m_paddingAfterTurrets[4];
		unsigned char m_validStuff;
	};

	if (!reinterpret_cast<const RetailModelConditionInfo *>(modelConditionInfo)->m_validStuff ||
			!reinterpret_cast<const RetailModelConditionInfo *>(b)->m_validStuff)
	{
		return true;
	}
	for (int i = 0; i < MAX_TURRETS; ++i)
		if (reinterpret_cast<const RetailModelConditionInfo *>(modelConditionInfo)->m_turrets[i].m_turretAngleNameKey !=
				reinterpret_cast<const RetailModelConditionInfo *>(b)->m_turrets[i].m_turretAngleNameKey ||
				reinterpret_cast<const RetailModelConditionInfo *>(modelConditionInfo)->m_turrets[i].m_turretPitchNameKey !=
				reinterpret_cast<const RetailModelConditionInfo *>(b)->m_turrets[i].m_turretPitchNameKey)
			return true;

	return false;
}

 

 

//-------------------------------------------------------------------------------------------------
#ifdef ALLOW_ANIM_INQUIRIES

#endif

//-------------------------------------------------------------------------------------------------
 

  // end crc

  // end xfer

  // end loadPostProcess

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

// Emission anchor: doSingleBoneName is static and its callers are not carried
// here. Retail gives it a register calling convention (robj arrives in ECX),
// which MSVC only does for a static whose address is never taken, so it is
// kept alive by direct calls rather than by taking its address. Build
// scaffolding; it claims no retail bytes.
// ?doSingleBoneNameBfme2Anchor absent-from-retail
Bool doSingleBoneNameBfme2Anchor(RenderObjClass *robj, const AsciiString &asciiString, const AsciiString &b, PristineBoneInfoMap &map)
{
	return doSingleBoneName(robj, asciiString, map) && doSingleBoneName(robj, b, map);
}
