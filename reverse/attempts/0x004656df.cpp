// ?exitObjectInAHurry@OpenContain@@UAEXPAVObject@@@Z
// partial score=0.65 date=2026-10-07
// ?OpenContain::exitObjectInAHurry present-unmatched
void OpenContain::exitObjectInAHurry( Object *exitObj )
{
	removeFromContain( exitObj );

	Object *me = getObject();

	m_doorCloseCountdown = getOpenContainModuleData()->m_doorOpenTime;
	if (m_doorCloseCountdown)
	{
		// srj sez: only diddle the doors if this countdown is nonzero. 
		// this allows us to prevent this module from messing with the doors
		// at all, which is required for DeliverPayloadAIUpdate.
		/// @todo srj -- for now, OpenContain assumes at most one door
		me->clearAndSetModelConditionState( MODELCONDITION_DOOR_1_CLOSING, MODELCONDITION_DOOR_1_OPENING );
	}

	Int numberExits = getOpenContainModuleData()->m_numberOfExitPaths;
	if( numberExits > 0 )
	{
		// We have ExitStart/End specified in art to use when we kick people out.  If >1, then
		// we have many and we need to decide which one to use.
		AsciiString startBone("ExitStart");
		AsciiString endBone("ExitEnd");
		Coord3D startPosition;
		Coord3D endPosition;
		if( numberExits > 1 )
		{
			char suffix[8];
			itoa(m_whichExitPath, suffix, 10);
			if( m_whichExitPath < 10 )
			{
				startBone.concat('0');
				endBone.concat('0');
			}
			
			m_whichExitPath = (m_whichExitPath % numberExits) + 1;// To cycle from 1 to n

			startBone.concat(suffix);
			endBone.concat(suffix);
		}
		me->getSingleLogicalBonePosition( startBone.str(), &startPosition, NULL );
		me->getSingleLogicalBonePosition( endBone.str(), &endPosition, NULL );

		//startPosition.x = startPosition.y = 0;
		Real exitAngle = me->getOrientation();
		exitObj->setPosition( &startPosition );
		exitObj->setOrientation( exitAngle );
		
		// Per JohnA: We need to set our layer to match our transports layer, or we'll try to pick a spot
		// on the ground.
		exitObj->setLayer( me->getLayer() );
		std::vector<Coord3D> exitPath;
		exitPath.push_back(endPosition);
		AIUpdateInterface *ai = exitObj->getAI();
		AIUpdateInterface *myAi = me->getAI();
		TheAI->pathfinder()->addObjectToPathfindMap( exitObj );
		if (ai) 
		{
			if (myAi && myAi->isIdle() && me->isKindOf(KINDOF_VEHICLE)) {
				TheAI->pathfinder()->removeUnitFromPathfindMap(me);
				TheAI->pathfinder()->updatePos(me, me->getPosition());
				TheAI->pathfinder()->updateGoal(me, me->getPosition(), TheTerrainLogic->getLayerForDestination(me->getPosition()));
			}
			ai->ignoreObstacle(NULL);
			// The units often come out at the same position, and need to ignore collisions briefly
			// as they move out.  jba.
			ai->setIgnoreCollisionTime(LOGICFRAMES_PER_SECOND);
			TheAI->pathfinder()->adjustToPossibleDestination(exitObj, ai->getLocomotorSet(), &endPosition);
		}
		exitPath.push_back(endPosition);
		if (m_rallyPointExists) {
			exitPath.push_back(m_rallyPoint);
		}

		if( ai )
		{
			ai->doQuickExit( &exitPath );

			TheAI->pathfinder()->updateGoal(exitObj, &endPosition, TheTerrainLogic->getLayerForDestination(&endPosition));
		}
	}
	else
	{
		///< @todo This really should be automatically wrapped up in an activation sequence	for objects in general
		// tell the AI about it
		TheAI->pathfinder()->addObjectToPathfindMap( exitObj );
	}
}
