// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// stlport
// Ported verbatim from the Generals Zero Hour reference
// (GameEngine/Source/Common/DamageFX.cpp); this unit had no counterpart under Code/.
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7 /arch:SSE) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
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

// FILE: DamageFX.cpp ///////////////////////////////////////////////////////////////////////////////
// Author: Steven Johnson, November 2001
// Desc:   DamageFX descriptions
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////

#include "PreRTS.h"	// This must go first in EVERY cpp file in the GameEngine

#include "Common/INI.h"
#include "Common/ThingFactory.h"
#include "Common/ThingTemplate.h"
#include "Common/DamageFX.h"
#include "Common/GameAudio.h"

#include "GameLogic/Damage.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Object.h"
#include "GameClient/GameClient.h"
#include "GameClient/InGameUI.h"

// LINK-COMDAT: static FXList::doFXObj is kept as the /O1 copy from ToppleUpdate.cpp;
// this TU is default-flag, so the ZH header inline copy differs. Declare only (no
// body) so calls reach the kept copy and this object emits no differing copy.
class Object;
class FXList
{
public:
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);
};

// LINK-COMDAT: rts::equal_to<NameKeyType> is kept as the /O1 copy from FXList.cpp;
// this TU is default-flag for its hashtable clear row, so its own copy differs.
// Specialize only the member under "s" so our emitted copy matches the kept /O1 body,
// while inlined key compares and the clear row keep default flags (as in FXListMapNodeEmit.cpp).
#pragma optimize("s", on)
namespace rts {
template<> Bool equal_to<NameKeyType>::operator()(const NameKeyType &a, const NameKeyType &b) const { return a == b; }
}
#pragma optimize("", on)

///////////////////////////////////////////////////////////////////////////////////////////////////
// PUBLIC DATA ////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

DamageFXStore *TheDamageFXStore = NULL;					///< the DamageFX store definition

///////////////////////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA ///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
// PRIVATE CLASSES ///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
// ?DamageFX::DamageFX present-unmatched
DamageFX::DamageFX()
{
	// not necessary.
	//clear();
}

//-------------------------------------------------------------------------------------------------
// ?DamageFX::clear present-unmatched
void DamageFX::clear()
{
	for (Int dt = 0; dt < DAMAGE_NUM_TYPES; ++dt)
	{
		for (Int v = LEVEL_FIRST; v <= LEVEL_LAST; ++v)
		{
			m_dfx[dt][v].clear();
		}
	}
}

//-------------------------------------------------------------------------------------------------
// ?DamageFX::getDamageFXThrottleTime present-unmatched
UnsignedInt DamageFX::getDamageFXThrottleTime(DamageType t, const Object* source) const 
{ 
	return m_dfx[t][source ? source->getVeterancyLevel() : LEVEL_REGULAR].m_damageFXThrottleTime; 
}

//-------------------------------------------------------------------------------------------------
// ?DamageFX::doDamageFX present-unmatched
void DamageFX::doDamageFX(DamageType t, Real damageAmount, const Object* source, const Object* victim) const
{ 
	ConstFXListPtr fx = getDamageFXList(t, damageAmount, source);
	// since the victim is receiving the damage, it's the "primary" object.
	// the source is the "secondary" object -- unused by most fx, but could be
	// useful in some cases.
	FXList::doFXObj(fx, victim, source);
}

//-------------------------------------------------------------------------------------------------
// ?DamageFX::getDamageFXList present-unmatched
ConstFXListPtr DamageFX::getDamageFXList(DamageType t, Real damageAmount, const Object* source) const
{ 
	/*
		if damage is zero, never do damage fx. this is by design, since "zero" damage can happen
		with some special weapons, like the battleship, which is a "faux" weapon that never does damage.
		if you really need to change this for some reason, consider carefully... (srj)
	*/
	if (damageAmount == 0.0f)
		return NULL;

	const DFX& dfx = m_dfx[t][source ? source->getVeterancyLevel() : LEVEL_REGULAR];
	ConstFXListPtr fx = 
		damageAmount >= dfx.m_amountForMajorFX ? 
		dfx.m_majorDamageFXList : 
		dfx.m_minorDamageFXList;

	return fx;
}

//-------------------------------------------------------------------------------------------------
// ?DamageFX::getFieldParse present-unmatched
const FieldParse* DamageFX::getFieldParse() const
{
	static const FieldParse myFieldParse[] = 
	{
		{ "AmountForMajorFX",						parseAmount,			NULL, 0 },
		{ "MajorFX",										parseMajorFXList,	NULL, 0 },
		{ "MinorFX",										parseMinorFXList,	NULL, 0 },
		{ "ThrottleTime",								parseTime,				NULL, 0 },
		{ "VeterancyAmountForMajorFX",	parseAmount,			TheVeterancyNames, 0 },
		{ "VeterancyMajorFX",						parseMajorFXList,	TheVeterancyNames, 0 },
		{ "VeterancyMinorFX",						parseMinorFXList,	TheVeterancyNames, 0 },
		{ "VeterancyThrottleTime",			parseTime,				TheVeterancyNames, 0 },
		{ 0, 0, 0,0 }
	};
	return myFieldParse;
}

//-------------------------------------------------------------------------------------------Static
static void parseCommonStuff(
	INI* ini, 
	ConstCharPtrArray names, 
	VeterancyLevel& vetFirst, 
	VeterancyLevel& vetLast, 
	DamageType& damageFirst, 
	DamageType& damageLast
)
{
	if (names)
	{
		vetFirst = (VeterancyLevel)INI::scanIndexList(ini->getNextToken(), names);
		vetLast = vetFirst;
	}
	else
	{
		vetFirst = LEVEL_FIRST;
		vetLast = LEVEL_LAST;
	}

	const char* damageName = ini->getNextToken();
	if (stricmp(damageName, "Default") == 0)
	{
		damageFirst = (DamageType)0;
		damageLast = (DamageType)(DAMAGE_NUM_TYPES - 1);
	}
	else
	{
		damageFirst = (DamageType)DamageTypeFlags::getSingleBitFromName(damageName);
		damageLast = damageFirst;
	}
}

//-------------------------------------------------------------------------------------------Static
/*static*/ void DamageFX::parseAmount( INI* ini, void* instance, void* /*store*/, const void* userData )
{
	DamageFX* self = (DamageFX*)instance;
	ConstCharPtrArray names = (ConstCharPtrArray)userData;

	VeterancyLevel vetFirst, vetLast;
	DamageType damageFirst, damageLast;
	parseCommonStuff(ini, names, vetFirst, vetLast, damageFirst, damageLast);

	Real amt = INI::scanReal(ini->getNextToken());

	for (Int dt = damageFirst; dt <= damageLast; ++dt)
	{
		for (Int v = vetFirst; v <= vetLast; ++v)
		{
			self->m_dfx[dt][v].m_amountForMajorFX = amt;
		}
	}
}

//-------------------------------------------------------------------------------------------Static
/*static*/ void DamageFX::parseMajorFXList( INI* ini, void* instance, void* /*store*/, const void* userData )
{
	DamageFX* self = (DamageFX*)instance;
	ConstCharPtrArray names = (ConstCharPtrArray)userData;

	VeterancyLevel vetFirst, vetLast;
	DamageType damageFirst, damageLast;
	parseCommonStuff(ini, names, vetFirst, vetLast, damageFirst, damageLast);

	ConstFXListPtr fx;
	INI::parseFXList(ini, NULL, &fx, NULL);

	for (Int dt = damageFirst; dt <= damageLast; ++dt)
	{
		for (Int v = vetFirst; v <= vetLast; ++v)
		{
			self->m_dfx[dt][v].m_majorDamageFXList = fx;
		}
	}
}

//-------------------------------------------------------------------------------------------Static
/*static*/ void DamageFX::parseMinorFXList( INI* ini, void* instance, void* /*store*/, const void* userData )
{
	DamageFX* self = (DamageFX*)instance;
	ConstCharPtrArray names = (ConstCharPtrArray)userData;

	VeterancyLevel vetFirst, vetLast;
	DamageType damageFirst, damageLast;
	parseCommonStuff(ini, names, vetFirst, vetLast, damageFirst, damageLast);

	ConstFXListPtr fx;
	INI::parseFXList(ini, NULL, &fx, NULL);

	for (Int dt = damageFirst; dt <= damageLast; ++dt)
	{
		for (Int v = vetFirst; v <= vetLast; ++v)
		{
			self->m_dfx[dt][v].m_minorDamageFXList = fx;
		}
	}
}

//-------------------------------------------------------------------------------------------Static
/*static*/ void DamageFX::parseTime( INI* ini, void* instance, void* /*store*/, const void* userData )
{
	DamageFX* self = (DamageFX*)instance;
	ConstCharPtrArray names = (ConstCharPtrArray)userData;

	VeterancyLevel vetFirst, vetLast;
	DamageType damageFirst, damageLast;
	parseCommonStuff(ini, names, vetFirst, vetLast, damageFirst, damageLast);

	UnsignedInt t;
	INI::parseDurationUnsignedInt(ini, NULL, &t, NULL);

	for (Int dt = damageFirst; dt <= damageLast; ++dt)
	{
		for (Int v = vetFirst; v <= vetLast; ++v)
		{
			self->m_dfx[dt][v].m_damageFXThrottleTime = t;
		}
	}
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?DamageFXStore::DamageFXStore present-unmatched
DamageFXStore::DamageFXStore()
{
	m_dfxmap.clear();
}

//-------------------------------------------------------------------------------------------------
// ?DamageFXStore::~DamageFXStore present-unmatched
DamageFXStore::~DamageFXStore()
{
	m_dfxmap.clear();
}

//-------------------------------------------------------------------------------------------------
// ?DamageFXStore::findDamageFX present-unmatched
const DamageFX *DamageFXStore::findDamageFX(AsciiString name) const
{
	NameKeyType namekey = TheNameKeyGenerator->nameToKey(name);
  DamageFXMap::const_iterator it = m_dfxmap.find(namekey);
  if (it == m_dfxmap.end()) 
	{
		return NULL;
	}
	else
	{
		return &(*it).second;
	}
}

//-------------------------------------------------------------------------------------------------
// ?DamageFXStore::init present-unmatched
void DamageFXStore::init()
{
}

//-------------------------------------------------------------------------------------------------
// ?DamageFXStore::reset present-unmatched
void DamageFXStore::reset()
{
} 

//-------------------------------------------------------------------------------------------------
// ?DamageFXStore::update present-unmatched
void DamageFXStore::update()
{
}

//-------------------------------------------------------------------------------------------------
/*static */ void DamageFXStore::parseDamageFXDefinition(INI* ini)
{

	const char *c = ini->getNextToken();
	NameKeyType key = TheNameKeyGenerator->nameToKey(c);
	DamageFX& dfx = TheDamageFXStore->m_dfxmap[key];
	dfx.clear();
	ini->initFromINI(&dfx, dfx.getFieldParse());
}
