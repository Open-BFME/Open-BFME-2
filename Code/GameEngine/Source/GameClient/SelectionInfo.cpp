// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// stlport
// Ported verbatim from the Generals Zero Hour reference
// (GameEngine/Source/GameClient/SelectionInfo.cpp); this unit had no counterpart under Code/.
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
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

#include "PreRTS.h"
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

#include "GameLogic/Damage.h"
#include "GameLogic/Module/ContainModule.h"

#include "Common/ActionManager.h"
#include "Common/ThingTemplate.h"
#include "Common/PlayerList.h"
#include "Common/Player.h"

#include "GameClient/SelectionInfo.h"
#include "GameClient/CommandXlat.h"
#include "GameClient/ControlBar.h"
#include "GameClient/GameClient.h"
#include "GameClient/Drawable.h"
#include "GameClient/KeyDefs.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

//-------------------------------------------------------------------------------------------------
SelectionInfo::SelectionInfo() :
	currentCountEnemies(0),
	currentCountCivilians(0),
	currentCountMine(0),
	currentCountMineInfantry(0),
	currentCountMineBuildings(0),
	currentCountFriends(0),
	newCountEnemies(0),
	newCountCivilians(0),
	newCountCrates(0),
	newCountMine(0),
	newCountMineBuildings(0),
	newCountFriends(0),
	newCountGarrisonableBuildings(0),
	selectEnemies(FALSE),
	selectCivilians(FALSE),
	selectMine(FALSE),
	selectMineBuildings(FALSE),
	selectFriends(FALSE)
{ }

//-------------------------------------------------------------------------------------------------
// ?PickDrawableStruct::PickDrawableStruct present-unmatched
PickDrawableStruct::PickDrawableStruct() : drawableListToFill(NULL)
{
	//Added By Sadullah Nader
	//Initializations inserted
	drawableListToFill = FALSE;
	//
	forceAttackMode = TheInGameUI->isInForceAttackMode();
	UnsignedInt pickType = getPickTypesForContext(forceAttackMode);
	translatePickTypesToKindof(pickType, kindofsToMatch);
	if (!forceAttackMode)
	{
		kindofsToMatch.set(KINDOF_ALWAYS_SELECTABLE);
	}
}

//-------------------------------------------------------------------------------------------------
/**
 * contextCommandForNewSelection (retail 0x0030ECD6) is defined in
 * SelectionInfoContextCommand.cpp over BFME 2 views; the Zero Hour headers
 * this unit includes disagree with its field offsets.
 */

//-------------------------------------------------------------------------------------------------
UnsignedInt getPickTypesForContext( Bool forceAttackMode )
{
	UnsignedInt types = PICK_TYPE_SELECTABLE;

	if (forceAttackMode)
		types |= PICK_TYPE_FORCEATTACKABLE;

	//
	// if we have a gui context command that allows for a shrubbery target then we want to
	// pick that type too (generally shrubbery aren't pickable cause it would get in
	// the way with movement and general selection)
	//
	const CommandButton *command = TheInGameUI->getGUICommand();

	if (command != NULL) {
		if (BitTest( command->getOptions(), ALLOW_MINE_TARGET)) {
			types |= PICK_TYPE_MINES;
		}

		if (BitTest( command->getOptions(), ALLOW_SHRUBBERY_TARGET ) ) {
			types |= PICK_TYPE_SHRUBBERY;
		}
	} else {
		types |= getPickTypesForCurrentSelection(forceAttackMode);
	}

	return types;

}  // end getPickTypesForContext

//-------------------------------------------------------------------------------------------------
UnsignedInt getPickTypesForCurrentSelection( Bool forceAttackMode )
{
	UnsignedInt retVal = 0;
	if (!TheInGameUI->areSelectedObjectsControllable()) {
		return retVal;
	}

	const DrawableList *allSelectedDrawables = TheInGameUI->getAllSelectedDrawables();

	for (DrawableListCIt cit = allSelectedDrawables->begin(); cit != allSelectedDrawables->end(); ++cit) {
		Drawable *draw = *cit;
		if (!draw) {
			continue;
		}

		Object *obj = draw->getObject();
		if (!obj) {
			continue;
		}

// srj sez: thanks to new, area-effect disarming, we NO LONGER want to do this...
//		if (obj->hasWeaponToDealDamageType(DAMAGE_DISARM)) {
//			retVal |= PICK_TYPE_MINES;
//		}

		if (obj->hasWeaponToDealDamageType(DAMAGE_FLAME) && forceAttackMode ) {
			retVal |= PICK_TYPE_SHRUBBERY;
		}

		// For efficiency.
		if (BitTest(retVal, PICK_TYPE_MINES | PICK_TYPE_SHRUBBERY)) {
			break;
		}
	}

	return retVal;
		
}

//-------------------------------------------------------------------------------------------------
void translatePickTypesToKindof(UnsignedInt pickTypes, KindOfMaskType& outMask)
{
	if (BitTest(pickTypes, PICK_TYPE_SELECTABLE)) {
		outMask.set(KINDOF_SELECTABLE);
	}

	if (BitTest(pickTypes, PICK_TYPE_SHRUBBERY)) {
		outMask.set(KINDOF_SHRUBBERY);
	}

	if (BitTest(pickTypes, PICK_TYPE_MINES)) {
		outMask.set(KINDOF_MINE);
	}

	if (BitTest(pickTypes, PICK_TYPE_FORCEATTACKABLE)) {
		outMask.set(KINDOF_FORCEATTACKABLE);
	}	
}

//-------------------------------------------------------------------------------------------------
// Given a drawable, add it to an stl list specified by userData.
// Useful for iterateDrawablesInRegion.
Bool addDrawableToList( Drawable *draw, void *userData )
{
	PickDrawableStruct *pds = (PickDrawableStruct *) userData;
#if defined(_DEBUG) || defined(_INTERNAL)
	if (TheGlobalData->m_allowUnselectableSelection) {
		pds->drawableListToFill->push_back(draw);
		return TRUE;
	}
#endif

	if (!pds->drawableListToFill)
		return FALSE;

	if (!draw->getTemplate()->isAnyKindOf(pds->kindofsToMatch))
		return FALSE;

	if (!draw->isSelectable())
  {
    const Object *obj = draw->getObject();
    if ( obj && obj->getContainedBy() )//hmm, interesting... he is not selectable but he is contained
    {// What we are after here is to propagate the selection the selection ti the container
      // if the cobtainer is non-enclosing... see also selectionxlat, in the left_click case

      ContainModuleInterface *contain = obj->getContainedBy()->getContain();
      Drawable *containDraw = obj->getContainedBy()->getDrawable();
      if (contain && ! contain->isEnclosingContainerFor( obj ) && containDraw )
        return addDrawableToList( containDraw, userData );
    }
    else
      return FALSE;
  }

	//Kris: Aug 9, 2003!!! Wow, this bug has been around a LONG time!!
	//Basically, it was possible to drag select a single enemy/neutral unit even if you couldn't see it
	//including stealthed units.
	const Object *obj = draw->getObject();
	if( obj )
	{
		const Player *player = ThePlayerList->getLocalPlayer();
		Relationship rel = player->getRelationship( obj->getTeam() );
		if( rel == NEUTRAL || rel == ENEMIES )
		{
			if( obj->getShroudedStatus( player->getPlayerIndex() ) >= OBJECTSHROUD_FOGGED )
			{
				return FALSE;
			}

			//If stealthed, no way!
			if( obj->testStatus( OBJECT_STATUS_STEALTHED ) && !obj->testStatus( OBJECT_STATUS_DETECTED ) )
			{
				return FALSE;
			}
		}
	}

	pds->drawableListToFill->push_back(draw);
	return TRUE;
}
