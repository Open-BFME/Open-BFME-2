// cl: /Ireference/shims/aiupdatelayout /Ireference/shims/bfme2_locomotor_flags44 /Ireference/shims/weapon_outofline /Ireference/shims/zh_outofline /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims
// stlport
// Ported verbatim from the Generals Zero Hour reference (GameEngine/Source/GameLogic/Object/Update/AIUpdate/DeliverPayloadAIUpdate.cpp); this unit had no counterpart under Code/.
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
// stlport
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

// DeliverPayloadAIUpdate.cpp ////////////
// Author: Graham Smallwood, March 2002
// Desc:   State machine that controls the approach and deployment of airborne cargo
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

#define DEFINE_WEAPONSLOTTYPE_NAMES

#include "Common/Player.h"
#include "Common/RandomValue.h"
#include "Common/ThingFactory.h"
#include "Common/ThingTemplate.h"
#include "Common/Xfer.h"
#include "GameClient/Drawable.h"
#include "GameClient/FXList.h"
#include "GameClient/InGameUI.h"
#include "GameLogic/Locomotor.h"
#include "GameLogic/Module/SmartBombTargetHomingUpdate.h"
#include "GameLogic/Module/GenerateMinefieldBehavior.h"
#include "GameLogic/Module/DeliverPayloadAIUpdate.h"
#include "GameLogic/Module/ParachuteContain.h"
#include "GameLogic/Module/ContainModule.h"
#include "GameLogic/Module/PhysicsUpdate.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Object.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/Weapon.h"
#include "GameLogic/WeaponSet.h"

// BFME 2's Object keeps its behavior list at +0x244 (the matched
// Object::findModule 0x0028B6D6 walks it there), its contain module at +0x250
// and its body module at +0x254; this tree's Zero Hour Object.h has +0x18C,
// +0x190 and +0x194. This unit reads them through these functions instead of
// the header's inline getters, whose Zero Hour copies would otherwise come
// early in link order and displace every BFME 2 unit's copy (retail has no
// out-of-line Object getter: the 7-byte bodies at 0x00313E8C/93/9A are
// GameWindow text-colour getters).
static BehaviorModule **getRetailBehaviorModules( const Object *obj ) { return *(BehaviorModule ** const *)((const char *)obj + 0x244); }
static ContainModuleInterface *getRetailContain( const Object *obj ) { return *(ContainModuleInterface * const *)((const char *)obj + 0x250); }
static BodyModuleInterface *getRetailBodyModule( const Object *obj ) { return *(BodyModuleInterface * const *)((const char *)obj + 0x254); }

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version 
	* 5: Whoops version.  preOpenDistance just wasn't saved.
*/
// ------------------------------------------------------------------------------------------------
// ?xfer@DeliverPayloadAIUpdate@@ present-unmatched
void DeliverPayloadAIUpdate::xfer( Xfer *xfer )
{
  // version
  const XferVersion currentVersion = 5;
  XferVersion version = currentVersion;
  xfer->xferVersion( &version, currentVersion );
 
 // extend base class
	AIUpdateInterface::xfer(xfer);

	xfer->xferCoord3D(&m_targetPos);
	xfer->xferCoord3D(&m_moveToPos);
	xfer->xferInt(&m_visibleItemsDelivered);
	xfer->xferUser(&m_diveState, sizeof(m_diveState));

	DeliverPayloadData data = m_data;

	xfer->xferAsciiString(&data.m_visibleDropBoneName);	
	xfer->xferAsciiString(&data.m_visibleSubObjectName);	
	xfer->xferAsciiString(&data.m_visiblePayloadTemplateName);
  xfer->xferReal(&data.m_distToTarget);
	if( version >= 5 )
		xfer->xferReal(&data.m_preOpenDistance);
	xfer->xferInt(&data.m_maxAttempts);
	xfer->xferCoord3D(&data.m_dropOffset);
	xfer->xferCoord3D(&data.m_dropVariance);
	xfer->xferUnsignedInt(&data.m_dropDelay);
	xfer->xferBool(&data.m_fireWeapon);
	xfer->xferBool(&data.m_selfDestructObject);
	xfer->xferInt(&data.m_visibleNumBones);						
	xfer->xferReal(&data.m_diveStartDistance);
	xfer->xferReal(&data.m_diveEndDistance);
	xfer->xferUser(&data.m_strafingWeaponSlot, sizeof(data.m_strafingWeaponSlot));
	xfer->xferInt(&data.m_visibleItemsDroppedPerInterval);
	xfer->xferBool(&data.m_inheritTransportVelocity);
	xfer->xferBool(&data.m_isParachuteDirectly);		
	xfer->xferReal(&data.m_exitPitchRate);
	// const FXList					*m_strafeFX;
	xfer->xferReal(&data.m_strafeLength);
	AsciiString weaponTemplateName;
	if (data.m_visiblePayloadWeaponTemplate) 
	{
		weaponTemplateName = data.m_visiblePayloadWeaponTemplate->getName();
	}
	xfer->xferAsciiString(&weaponTemplateName);
	if( xfer->getXferMode() == XFER_LOAD && weaponTemplateName.isNotEmpty()) 
	{
		data.m_visiblePayloadWeaponTemplate = TheWeaponStore->findWeaponTemplate(weaponTemplateName);
	}
	data.m_deliveryDecalTemplate.xferRadiusDecalTemplate(xfer);
	xfer->xferReal(&data.m_deliveryDecalRadius);
	 *((DeliverPayloadData*)&m_data) = data;

	Bool hasStateMachine = m_deliverPayloadStateMachine!=NULL;
	xfer->xferBool(&hasStateMachine);
	if (hasStateMachine && m_deliverPayloadStateMachine==NULL) 
	{
		m_deliverPayloadStateMachine = newInstance(DeliverPayloadStateMachine)( getObject() );
	}
	if (m_deliverPayloadStateMachine && version >= 2)
	{
		xfer->xferSnapshot(m_deliverPayloadStateMachine);
	}
	
	m_deliveryDecal.xferRadiusDecal(xfer);

	if (version >= 2)
	{
		xfer->xferBool(&m_freeToExit);
	}
	if (version >= 3)
	{
		xfer->xferBool(&m_acceptingCommands);
	}
	if (version >= 4)
	{
		xfer->xferReal(&m_previousDistanceSqr);
	}


}  // end xfer

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
/*static*/ Bool DeliverPayloadStateMachine::isOffMap( State *thisState, void* userData )
{
	Object *owner = thisState->getMachineOwner();
	DeliverPayloadAIUpdate *ai = (DeliverPayloadAIUpdate*)owner->getAIUpdateInterface();
	if( !ai )
	{
		return TRUE;
	}
	return ai->isOffMap();
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// ?update@DeliveringState@@ present-unmatched
StateReturnType DeliveringState::update() // Kick a dude out every so often
{
	if (m_dropDelayLeft > 0)
	{
		--m_dropDelayLeft;
		return STATE_CONTINUE;
	}

	Object *owner = getMachineOwner();
	DeliverPayloadAIUpdate *ai = (DeliverPayloadAIUpdate*)owner->getAIUpdateInterface();
	if( !ai )
	{
		return STATE_FAILURE;
	}

	ai->friend_setFreeToExit(true);

	m_didOpen = true;
	m_dropDelayLeft = ai->getDropDelay();

	if (!ai->isCloseEnoughToTarget())
		return STATE_FAILURE;

	const ContainedItemsList* items = getRetailContain(owner) ? getRetailContain(owner)->getContainedItemsList() : NULL;
	if( (!items || !items->size()) && ai->getVisibleItemsDelivered() == ai->getData()->m_visibleNumBones )
	{
		//We are out of payload to drop AND our visible payload is empty. It's possible for deliverers to
		//have one or the other or even both.
		return STATE_SUCCESS;
	}

	//Handle contained payload delivery.
	if( items )
	{
		Object* item = items->front();

		if( ai->isFireWeapon() )
		{
			Coord3D pos = *ai->getTargetPos();
			pos.x += ai->getDropOffset().x;
			pos.y += ai->getDropOffset().y;
			pos.z += ai->getDropOffset().z;
			owner->fireCurrentWeapon( &pos );
			TheGameLogic->destroyObject( item );
		}
		else
		{
			AIUpdateInterface* itemAI = item->getAIUpdateInterface();
			if (itemAI)
			{
				itemAI->aiExit(NULL, CMD_FROM_AI);
			}
			Coord3D pos = *item->getPosition();

			if (ai->getDropVariance().x > 0)
				pos.x += GameLogicRandomValueReal(-ai->getDropVariance().x, ai->getDropVariance().x);
			if (ai->getDropVariance().y > 0)
				pos.y += GameLogicRandomValueReal(-ai->getDropVariance().y, ai->getDropVariance().y);
			if (ai->getDropVariance().z > 0)
				pos.z += GameLogicRandomValueReal(-ai->getDropVariance().z, ai->getDropVariance().z);

			pos.x += ai->getDropOffset().x;
			pos.y += ai->getDropOffset().y;
			pos.z += ai->getDropOffset().z;
			item->setPosition(&pos);

			ContainModuleInterface *contain = getRetailContain(item);
			if( ai->getData()->m_isParachuteDirectly  &&  contain )
			{
				contain->setOverrideDestination( ai->getTargetPos() );// go for the direct hit
			}
			else if (itemAI)
			{
				// This will most likely be ignored, as the item is still in the transport, and therefore Held.
				itemAI->aiMoveToPosition( ai->getMoveToPos(), CMD_FROM_AI );
			}
			
			/// @todo srj -- urg. icky.
			static NameKeyType key_GenerateMinefieldBehavior = NAMEKEY("GenerateMinefieldBehavior");
			GenerateMinefieldBehavior* mfb = (GenerateMinefieldBehavior *)item->findUpdateModule(key_GenerateMinefieldBehavior);
			if (mfb)
			{
				mfb->setMinefieldTarget(ai->getMoveToPos());
			}


			static NameKeyType key_SmartBombTargetHomingUpdate = NAMEKEY("SmartBombTargetHomingUpdate");
			SmartBombTargetHomingUpdate* smthu = (SmartBombTargetHomingUpdate *)item->findUpdateModule(key_SmartBombTargetHomingUpdate);
			if (smthu)
			{
				smthu->SetTargetPosition( *ai->getMoveToPos() );
			}


			if( ai->getData()->m_inheritTransportVelocity )
			{
				Coord3D velocity = *owner->getPhysics()->getVelocity();
				item->getPhysics()->applyForce( &velocity );
			}
		}
	}

	//Handle visible payload delivery.
	if( ai->getVisibleItemsDelivered() < ai->getData()->m_visibleNumBones )
	{
		Int attemptDrops = ai->getData()->m_visibleItemsDroppedPerInterval;
		Drawable *draw = owner->getDrawable();
		Bool updateSubObjects = false;
		while( attemptDrops && ai->getVisibleItemsDelivered() < ai->getData()->m_visibleNumBones )
		{
			//Drop an item!
			if( draw )
			{
				//First hide the subobject as it becomes the delivered payload.
				if( ai->getData()->m_visibleSubObjectName.isNotEmpty() )
				{
					AsciiString name;
					name.format( "%s%02d", ai->getData()->m_visibleSubObjectName.str(), ai->getVisibleItemsDelivered() + 1 );
					draw->showSubObject( name, false );
					updateSubObjects = true;
				}

				//Second, create the subobject for real
				if( ai->getData()->m_visiblePayloadTemplateName.isNotEmpty() )
				{
					const ThingTemplate* thing = TheThingFactory->findTemplate( ai->getData()->m_visiblePayloadTemplateName.str() );
					Object *payload = TheThingFactory->newObject( thing, owner->getControllingPlayer()->getDefaultTeam() );
					
					if( payload )
					{
						payload->setProducer( owner );

						if( ai->getData()->m_visibleDropBoneName.isNotEmpty() )
						{
							Coord3D pos;
							AsciiString bone;
							bone.format( "%s%02d", ai->getData()->m_visibleDropBoneName.str(), ai->getVisibleItemsDelivered() + 1 );
							if( draw->getPristineBonePositions( ai->getData()->m_visibleDropBoneName.str(), ai->getVisibleItemsDelivered() + 1, &pos, NULL, 1 ) > 0 )
							{
								draw->convertBonePosToWorldPos( &pos, NULL, &pos, NULL );
								payload->setPosition( &pos );
							}
							else
							{
								payload->setPosition( owner->getPosition() );
							}
						}
						else
						{
							payload->setPosition( owner->getPosition() );
						}
						payload->setOrientation( owner->getOrientation() );

						//If we want the payload to inherit the transport's velocity, do so now.
						if( ai->getData()->m_inheritTransportVelocity )
						{
							Coord3D startingForce = *owner->getPhysics()->getVelocity();
							startingForce.scale( payload->getPhysics()->getMass() );
							payload->getPhysics()->applyMotiveForce( &startingForce );

							Coord3D backPosition = *owner->getPhysics()->getVelocity();
							backPosition.scale( -1.0f );
							backPosition.add( payload->getPosition() );
							payload->setPosition( &backPosition );
						}

						//Are we firing a missile?
						Bool projectileFired = false;
						for( BehaviorModule** behaviorModule = getRetailBehaviorModules(payload); *behaviorModule; ++behaviorModule )
						{
							ProjectileUpdateInterface* pui = (*behaviorModule)->getProjectileUpdateInterface();
							if( pui  )
							{
								//Missile! 
								const WeaponTemplate *weaponTemplate = ai->getData()->m_visiblePayloadWeaponTemplate;
								if( !weaponTemplate )
								{
									DEBUG_ASSERTCRASH( 0, ("%s tried to fire missile %s via DeliverPayload, and is missing required weapon template in ObjectCreationList.ini entry.",
																				owner->getTemplate()->getName().str(), payload->getTemplate()->getName().str() ) );
									break;
								}
								VeterancyLevel v = owner->getVeterancyLevel();
								pui->projectileFireAtObjectOrPosition( NULL, ai->getTargetPos(), weaponTemplate, weaponTemplate->getProjectileExhaust(v) );
								projectileFired = true;
								//damageInfo.in.m_sourceID = pui->projectileGetLauncherID();
								break;
							}
						}

						//If not, are we dropping a bomb?
						if( !projectileFired )
						{
							//Bomb!
							if( ai->getData()->m_exitPitchRate != 0 )
							{
								//If the payload needs to pitch, do so now.
								Real pitchRate = payload->getPhysics()->getCenterOfMassOffset() * ai->getData()->m_exitPitchRate;
								payload->getPhysics()->setPitchRate( pitchRate );
							}

							//If payload can move independently, order the move. A lot of bombs don't have locomotors,
							//in which case the "start move sound" is played, but nothing else actually happens.
							if( payload->getAIUpdateInterface() )
							{
								payload->getAIUpdateInterface()->aiMoveToPosition( ai->getMoveToPos(), CMD_FROM_AI );
							}

						}
					}
				}
			}
			
			//Update the counters
			attemptDrops--;
			ai->setVisibleItemsDelivered( ai->getVisibleItemsDelivered() + 1 );
		}
		if( updateSubObjects )
		{
			draw->updateSubObjects();
		}
	}

	return STATE_CONTINUE;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/** Xfer Method */
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
