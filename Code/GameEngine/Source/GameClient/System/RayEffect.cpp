// cl: -DNDEBUG -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Include/Precompiled -Ireference/open-bfme-1/game/GameEngine/Source/Common/System -Ireference/open-bfme-1/game/GameEngine/Source/GameClient -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/System
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

// FILE: RayEffect.cpp ////////////////////////////////////////////////////////////////////////////
// Created:   Colin Day, May 2001
// Desc:      Ray effect system manager
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "prerts.h"
#include "coord.h"	// This must go first in EVERY cpp file int the GameEngine

#include "ray_effect.h"
#include "drawable.h"

// PUBLIC DATA ////////////////////////////////////////////////////////////////////////////////////
class RayEffectSystem *TheRayEffects = NULL;

// PRIVATE METHODS ////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
/** Find an effect entry given a drawable */
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void RayEffectSystem::deleteRayEffect( const Drawable *draw )
{
	RayEffectData *effectData = NULL;

	// sanity
	if( draw == NULL )
		return;

	// find the effect entry
	effectData = findEntry( draw );
	if( effectData )
	{

		// remove the data for this entry
		effectData->draw = NULL;

	}  // end if

}  // end deleteRayEffect

//-------------------------------------------------------------------------------------------------
/** given a drawable, if it is in the ray effect system list retrieve
	*	the ray effect data for its entry */
//-------------------------------------------------------------------------------------------------
void RayEffectSystem::getRayEffectData( const Drawable *draw, 
																			  RayEffectData *effectData )
{
	RayEffectData *entry = NULL;

	// sanity
	if( draw == NULL || effectData == NULL )
		return;

	// find the effect data entry
	entry = findEntry( draw );
	if( entry )
	{

		// data has been found, copy to parameter
		*effectData = *entry;

	}  // end effectData

}  // end getRayEffectData
