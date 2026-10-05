// ?tryToIgnite@FlammableUpdate@@QAEXXZ
// partial score=0.72 date=2026-10-05
// ?tryToIgnite@FlammableUpdate@@QAEXXZ
// partial score=0.72 date=2026-10-05
void FlammableUpdate::tryToIgnite()
{
	if( m_status == FS_NORMAL )
	{
		Object *me = getObject();
		me->setStatus( MAKE_OBJECT_STATUS_MASK( OBJECT_STATUS_AFLAME ) );
		me->getBodyModule()->setAflame( TRUE );
		me->setModelConditionState( MODELCONDITION_AFLAME );
		startBurningSound();

		// bleah. this sucks. (srj)
		static const NameKeyType key_FireSpreadUpdate = NAMEKEY("FireSpreadUpdate");
		FireSpreadUpdate* fu = (FireSpreadUpdate*)getObject()->findUpdateModule(key_FireSpreadUpdate);
		if (fu != NULL)
		{
			fu->startFireSpreading();
		}

		m_status = FS_AFLAME;

		const FlammableUpdateModuleData *data = getFlammableUpdateModuleData();
		UnsignedInt now = TheGameLogic->getFrame();
		m_aflameEndFrame = now + data->m_aflameDuration;
		m_burnedEndFrame = data->m_burnedDelay ? now + data->m_burnedDelay : 0;
		m_damageEndFrame = data->m_aflameDamageDelay ? now + data->m_aflameDamageDelay : 0;

		setWakeFrame(getObject(), calcSleepTime());
	}
}
