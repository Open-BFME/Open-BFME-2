// cl: /O1 /G7 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/stlp_nodealloc /Ireference/open-bfme-1/inputs/reference/shims/w3dmodeldraw /Ireference/open-bfme-1/inputs/reference/shims/asciistring8 /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/game/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
//
// ?doSingleBoneName@@YA_NPAVRenderObjClass@@ABVAsciiString@@AAV?$map@W4NameKeyType@@UPristineBoneInfo@@U?$less@W4NameKeyType@@@_STL@@V?$allocator@U?$pair@$$CBW4NameKeyType@@UPristineBoneInfo@@@_STL@@@4@@_STL@@@Z
// retail 0x000BD2BF, 488 bytes. Dedicated TU ported from the Open-BFME-1
// donor game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDraw.cpp (reference/open-bfme-1 @ 6d943426).
// The donor body does not place at BFME 1's flags; compiled /O1 it is
// byte-identical to retail once relocations are masked (unique hit on
// unclaimed .text). Only the placed body is defined here; the donor's
// other definitions are omitted.
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

#if defined(DEBUG_CRC) && (defined(_DEBUG) || defined(_INTERNAL))
#include <cstdarg>
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
static Bool findSingleBone(RenderObjClass* robj, const AsciiString& boneName, Matrix3D& mtx, Int& boneIndex)
{
	if (boneName.isNone() || boneName.isEmpty())
		return false;

	boneIndex = robj->Get_Bone_Index(boneName.str());
	if (boneIndex != 0)
	{
		mtx = robj->Get_Bone_Transform(boneIndex);
		return true;
	}
	else
	{
		return false;
	}
}

//-------------------------------------------------------------------------------------------------
static Bool findSingleSubObj(RenderObjClass* robj, const AsciiString& boneName, Matrix3D& mtx, Int& boneIndex)
{
	if (boneName.isNone() || boneName.isEmpty())
		return false;

	RenderObjClass* childObject = robj->Get_Sub_Object_By_Name(boneName.str());
	if (childObject)
	{
		mtx = childObject->Get_Transform();

		// you'd think this would work, but, it does not. do it the hard way.
		// boneIndex = childObject->Get_Sub_Object_Bone_Index(childObject);

		for (Int subObj = 0; subObj < robj->Get_Num_Sub_Objects(); subObj++)
		{	
			RenderObjClass* test = robj->Get_Sub_Object(subObj);
			if (test == childObject)
			{
				boneIndex = robj->Get_Sub_Object_Bone_Index(0, subObj);
#if defined(_DEBUG) || defined(_INTERNAL)
				test->Release_Ref();
				test = robj->Get_Sub_Object_On_Bone(0, boneIndex);
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

static Bool doesStateExist(const ModelConditionVector& v, const ModelConditionFlags& f)
{
	const RetailConditionVector00765B20& retailVector =
		*reinterpret_cast<const RetailConditionVector00765B20 *>(&v);
	const RetailConditionFlags00765B20& retailFlags =
		*reinterpret_cast<const RetailConditionFlags00765B20 *>(&f);
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
static Bool isAnimationComplete(RenderObjClass* r)
{
	if (r && r->Class_ID() == RenderObjClass::CLASSID_HLOD)
	{
		HLodClass *hlod = (HLodClass*)r;
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
static Bool turretNamesDiffer(const ModelConditionInfo* a, const ModelConditionInfo* b)
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

	if (!reinterpret_cast<const RetailModelConditionInfo *>(a)->m_validStuff ||
			!reinterpret_cast<const RetailModelConditionInfo *>(b)->m_validStuff)
	{
		return true;
	}
	for (int i = 0; i < MAX_TURRETS; ++i)
		if (reinterpret_cast<const RetailModelConditionInfo *>(a)->m_turrets[i].m_turretAngleNameKey !=
				reinterpret_cast<const RetailModelConditionInfo *>(b)->m_turrets[i].m_turretAngleNameKey ||
				reinterpret_cast<const RetailModelConditionInfo *>(a)->m_turrets[i].m_turretPitchNameKey !=
				reinterpret_cast<const RetailModelConditionInfo *>(b)->m_turrets[i].m_turretPitchNameKey)
			return true;

	return false;
}

 

 

//-------------------------------------------------------------------------------------------------
#ifdef ALLOW_ANIM_INQUIRIES

#endif

//-------------------------------------------------------------------------------------------------
struct Rva007705D0Element
{
	Int value[3];
};

class Rva007705D0Vector
{
public:
	void resizeValue(UnsignedInt newSize, Rva007705D0Element value);
	void fillInsert(Rva007705D0Element *position, UnsignedInt count,
		const Rva007705D0Element &value);

private:
	Rva007705D0Element *m_begin;
	Rva007705D0Element *m_end;
	Rva007705D0Element *m_capacity;
};

 

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
// ?doSingleBoneNameAnchor absent-from-retail
Bool doSingleBoneNameAnchor(RenderObjClass *robj, const AsciiString &a, const AsciiString &b, PristineBoneInfoMap &map)
{
	return doSingleBoneName(robj, a, map) && doSingleBoneName(robj, b, map);
}

// ------------------------------------------------------------------------------------------------
// retail 0x000BE245..0x000BE775 (1328 bytes) thiscall RET 0x10.
// The BFME 2 form of Zero Hour's ModelConditionInfo::validateCachedBones
// (WorldBuilder twin 0x00920780 has the same calls and the three report
// texts): the pristine bone cache lives in the per-state object (+0xA0, its
// clear is the rowed 0x000B92FB) with the valid bit at +0xF4 and the
// pristine frame at +0x60; the model name (rowed getter 0x000B4AB5) the
// animation base/model names (+0x58/+0x70) and the public bone names (+0x78)
// stay on the condition record. The first animation of the state is looked
// up through the rowed 0x000BE027 (unnumbered then numbered by
// Rva000B2BA3Get on the render object's drawable info); the frame is
// min(pristine frame and last frame) as in the twin. Global standard bones
// come from TheGlobalData +0xBA8 and the slerp flag 0x00E1D058 brackets the
// scaled identity transform. Only caller: the rowed 0x000C3886.
// Unit evidence: retail calls the static doSingleBoneName above with the
// render object in ECX and keeps the state's first animation in EDX across
// Rva000B2BA3Get, so all three share one unit (retail W3DScriptedModelDraw).
// ------------------------------------------------------------------------------------------------

struct Rva000B2BE5Src
{
	char pad[0x114];
	unsigned char flag;
};
// ?Rva000B2BA3Get@@YAHPBURva000B2BE5Src@@PA_N@Z, retail 0x000B2BA3..0x000B2BE5
// (66 bytes): its body as rowed in W3DScriptedModelDrawAnimationFrameCount.cpp.
// It must be compiled ahead of rva000BE245 in this unit (EDX live across it).
struct Rva000B2BA3LOD
{
	char m_pad0000[0x1774];
	int m_mode1774; // +0x1774
};
int __cdecl Rva000B2BA3Get(const Rva000B2BE5Src *p, bool *forced)
{
	int mode = reinterpret_cast<Rva000B2BA3LOD *>(TheGameLODManager)->m_mode1774;
	if (mode != 3 && p && (p->flag & 0x20))
	{
		if (forced)
			*forced = true;
		mode = 0;
	}
	switch (mode)
	{
	case 0:
		return 2;
	case 1:
		return 1;
	case 2:
	case 3:
		return 0;
	}
	return 0;
}
int Rva000B2CBDGet();
template <class T> class StringBase
{
public:
	bool isEmpty() const;
};

class Rva0013101E
{
public:
	Rva0013101E() : m_a(0), m_b(0), m_c(0), m_d1(0), m_d2(0), m_d3(0) {}
	unsigned m_a : 3;
	unsigned m_b : 27;
	unsigned m_c : 1;
	unsigned m_keep : 1;
	unsigned m_d1;
	unsigned m_d2;
	unsigned m_d3;
};
RenderObjClass *Rva00137364CreateRenderObj(const char *name, float scale, const Rva0013101E &options = Rva0013101E());

extern bool Rva00E1D058FastSlerpInline;

// HAnimClass as this body sees it: Delete_This slot 0 and Get_Num_Frames slot 5.
class Rva000BE245Anim
{
public:
	virtual void Delete_This();
	virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04();
	virtual int Get_Num_Frames();
	void Add_Ref() { NumRefs++; }
	void Release_Ref() { NumRefs--; if (NumRefs == 0) Delete_This(); }
	int NumRefs;
};

struct Rva000BE245DrawableInfo
{
	int m_shroudStatusObjectID;
	const Rva000B2BE5Src *m_drawable;
};

// RenderObjClass / HLodClass slots used here.
class Rva000BE245RObj
{
public:
	virtual void Delete_This();
	virtual void s01(); virtual void s02();
	virtual int Class_ID() const;
#define S(n) virtual void s##n();
	S(04) S(05) S(06) S(07) S(08) S(09) S(10) S(11) S(12) S(13) S(14) S(15) S(16) S(17) S(18) S(19)
	virtual void Validate_Transform() const;
	virtual void Set_Transform(const Matrix3D &m);
	S(22) S(23) S(24) S(25) S(26) S(27) S(28) S(29) S(30) S(31) S(32) S(33) S(34) S(35) S(36) S(37)
	S(38) S(39) S(40) S(41) S(42) S(43) S(44)
	virtual void Set_Animation(Rva000BE245Anim *motion, float frame, int mode);
	S(46) S(47) S(48) S(49) S(50) S(51) S(52) S(53) S(54) S(55) S(56) S(57) S(58) S(59) S(60) S(61)
	S(62) S(63) S(64) S(65) S(66) S(67) S(68) S(69) S(70) S(71) S(72) S(73) S(74) S(75) S(76) S(77)
	S(78) S(79) S(80) S(81) S(82) S(83) S(84) S(85) S(86)
	virtual Rva000BE245DrawableInfo *Get_User_Data();
	S(88) S(89) S(90) S(91) S(92) S(93) S(94) S(95) S(96) S(97) S(98) S(99) S(100) S(101) S(102) S(103)
	S(104) S(105) S(106) S(107) S(108) S(109) S(110) S(111) S(112) S(113) S(114) S(115) S(116) S(117)
	S(118) S(119) S(120) S(121) S(122) S(123) S(124) S(125) S(126) S(127) S(128)
#undef S
	virtual void Set_Animation_Frame_Rate_Multiplier(float multiplier);
	virtual Rva000BE245Anim *Peek_Animation_And_Info(float &frame, int &numFrames, int &mode, float &mult);

	const Matrix3D &Get_Transform() const { Validate_Transform(); return Transform; }
	void Release_Ref() { NumRefs--; if (NumRefs == 0) Delete_This(); }

	int NumRefs;
	char m_pad08[0x18 - 0x08];
	Matrix3D Transform;
};

class Rva000BE245Report;

class Debug
{
public:
#define S(n) virtual void s##n();
	S(00) S(04) S(08) S(0C) S(10) S(14) S(18) S(1C) S(20) S(24) S(28) S(2C) S(30) S(34) S(38) S(3C)
	S(40) S(44) S(48) S(4C) S(50) S(54) S(58) S(5C)
	virtual void beginReport();
	S(64) S(68)
#undef S
	virtual Rva000BE245Report *getReport(int, int, int);

	class Format
	{
	public:
		Format(const char *format, ...);
	private:
		char m_text[0x200];
	};
};
class Rva000BE245Report
{
public:
#define S(n) virtual void s##n();
	S(00) S(04) S(08) S(0C) S(10) S(14) S(18) S(1C) S(20) S(24) S(28) S(2C) S(30) S(34)
	virtual Rva000BE245Report *setText(const char *text);
	S(3C) S(40) S(44) S(48)
#undef S
	virtual void show(int mode);
	Rva000BE245Report &operator<<(const Debug::Format &value) { setText((const char *)&value); return *this; }
};

extern Debug *theDebug;
bool bfmeRva000387C0();
void _bfme_debugRecordCallsite(int kind);

class Rva000B4AB5
{
public:
	const AsciiString *rva000B4AB5(unsigned int index);
};

class Rva000B4926
{
public:
	const AsciiString &rva000B4926() const;
};

class HTreeClass;
class Rva000BE027Anim
{
public:
	HTreeClass *rva000BE027(const AsciiString &base, const AsciiString &model, bool numbered, int number);
};

class Rva000B646B
{
public:
	void rva000B92FB();
};

struct Rva000BE245AnimInfo
{
	char m_bytes[0x40];
};

struct Rva000C3886Obj
{
	char m_pad00[0x50];
	std::vector<Rva000BE245AnimInfo> m_animations;   // +0x50
	char m_pad5C[0x60 - 0x5C];
	int m_pristineFrame;                       // +0x60
	char m_pad64[0xA0 - 0x64];
	PristineBoneInfoMap m_pristineBones;       // +0xA0
	char m_padAC[0xF4 - 0xA0 - sizeof(PristineBoneInfoMap)];
	unsigned char m_validStuff;                // +0xF4
};

class Rva000C3886
{
public:
	void rva000BE245(void *first, float value, Rva000C3886Obj *obj, void *last);

	const AsciiString *getModelName(void *which)
	{
		return ((Rva000B4AB5 *)this)->rva000B4AB5((unsigned int)which);
	}

	char m_pad00[0x58];
	AsciiString m_animBaseName;                // +0x58
	char m_pad5C[0x70 - 0x5C];
	AsciiString m_animModelName;               // +0x70
	char m_pad74[0x78 - 0x74];
	std::vector<AsciiString> m_publicBones;    // +0x78
};

struct Rva000BE245GlobalData
{
	char m_pad000[0xBA8];
	std::vector<AsciiString> m_standardPublicBones;   // +0xBA8
};

enum { PRISTINE_BONES_VALID = 0x01, CLASSID_HLOD = 0x19 };

void Rva000C3886::rva000BE245(void *first, float scale, Rva000C3886Obj *obj, void *which)
{
	if (obj == NULL || (obj->m_validStuff & PRISTINE_BONES_VALID))
		return;

	if (!(unsigned char)Rva000B2CBDGet())
	{
		((Rva000B646B *)&obj->m_pristineBones)->rva000B92FB();
		obj->m_validStuff &= ~PRISTINE_BONES_VALID;
		return;
	}

	setFPMode();

	PristineBoneInfoMap *bones = &obj->m_pristineBones;
	((Rva000B646B *)bones)->rva000B92FB();

	obj->m_validStuff |= PRISTINE_BONES_VALID;

	Rva000BE245RObj *robj = (Rva000BE245RObj *)first;
	bool tossRobj = false;
	if (robj == NULL)
	{
		if (((const StringBase<char> *)getModelName(which))->isEmpty())
			return;

		robj = (Rva000BE245RObj *)Rva00137364CreateRenderObj(getModelName(which)->str(), scale);
		if (robj == NULL)
		{
			if (bfmeRva000387C0())
			{
				_bfme_debugRecordCallsite(1);
				theDebug->beginReport();
				const char *name = getModelName(which)->str();
				Rva000BE245Report *out = theDebug->getReport(0, 0, 0);
				(*out << Debug::Format("ASSET ERROR: Model %s not found!\n", name)).show(2);
			}
			return;
		}
		tossRobj = true;
	}

	Matrix3D originalTransform = robj->Get_Transform();
	Rva000BE245RObj *hlod = NULL;
	Rva000BE245Anim *curAnim = NULL;
	int numFrames = 0;
	float frame = 0.0f;
	int mode = 0;
	float mult = 1.0f;

	if (robj->Class_ID() == CLASSID_HLOD)
	{
		hlod = robj;
		curAnim = hlod->Peek_Animation_And_Info(frame, numFrames, mode, mult);
	}

	Rva000BE245Anim *animToUse;
	if (obj->m_animations.size() > 0)
	{
		animToUse = (Rva000BE245Anim *)((Rva000BE027Anim *)&obj->m_animations.front())->rva000BE027(m_animBaseName, m_animModelName, false, 0);
		if (animToUse == NULL)
		{
			Rva000BE245DrawableInfo *info = robj->Get_User_Data();
			const Rva000B2BE5Src *draw = info ? info->m_drawable : NULL;
			Rva000BE027Anim *front = (Rva000BE027Anim *)&obj->m_animations.front();
			animToUse = (Rva000BE245Anim *)front->rva000BE027(m_animBaseName, m_animModelName, true, Rva000B2BA3Get(draw, NULL));
			if (animToUse == NULL)
			{
				if (bfmeRva000387C0())
				{
					_bfme_debugRecordCallsite(1);
					theDebug->beginReport();
					theDebug->getReport(0, 0, 0)
						->setText("Animation ")
						->setText(((const Rva000B4926 *)&obj->m_animations.front())->rva000B4926().str())
						->setText(" in ")
						->setText(getModelName(which)->str())
						->setText(" not found.\n")
						->show(2);
				}
				goto anim_done;
			}
		}
	}
	else
	{
		animToUse = curAnim;
		if (animToUse == NULL)
			goto anim_done;
		animToUse->Add_Ref();
	}

	{
		int whichFrame = obj->m_pristineFrame;
		whichFrame = std::min(animToUse->Get_Num_Frames() - 1, whichFrame);
		robj->Set_Animation(animToUse, whichFrame, 0);
		animToUse->Release_Ref();
	}
anim_done:

	Rva00E1D058FastSlerpInline = true;
	Matrix3D tmp(true);
	tmp.Scale(scale);
	robj->Set_Transform(tmp);

	if (TheWritableGlobalData)
	{
		for (std::vector<AsciiString>::const_iterator it = ((const Rva000BE245GlobalData *)TheWritableGlobalData)->m_standardPublicBones.begin();
			it != ((const Rva000BE245GlobalData *)TheWritableGlobalData)->m_standardPublicBones.end(); ++it)
		{
			doSingleBoneName((RenderObjClass *)robj, *it, *bones);
		}
	}

	for (std::vector<AsciiString>::const_iterator it = m_publicBones.begin(); it != m_publicBones.end(); ++it)
	{
		if (!doSingleBoneName((RenderObjClass *)robj, *it, *bones))
		{
			if (bfmeRva000387C0())
			{
				_bfme_debugRecordCallsite(1);
				theDebug->beginReport();
				theDebug->getReport(0, 0, 0)
					->setText("A bone named '")
					->setText(it->str())
					->setText("' is needed in model ")
					->setText(getModelName(which)->str())
					->setText(" but it's not there.\nThis is either an art error (missing bone) or a design error (INI references the wrong bone).\n")
					->show(2);
			}
		}
	}

	Rva00E1D058FastSlerpInline = false;
	robj->Set_Transform(originalTransform);
	if (curAnim != NULL && hlod != NULL)
	{
		robj->Set_Animation(curAnim, frame, mode);
		hlod->Set_Animation_Frame_Rate_Multiplier(mult);
	}

	if (tossRobj)
		robj->Release_Ref();
}
