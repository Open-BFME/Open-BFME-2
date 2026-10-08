// ?evaluateSkirmishValueInArea@ScriptConditions@@IAE_NPAVCondition@@PAVParameter@@111@Z
// partial score=0.93 date=2026-10-08
// 0x003E719C SKIRMISH_VALUE_IN_AREA (case 86), 587 bytes; call site 0x3eba70, ret 0x14.
// Donor: BFME 1 ScriptConditionsSkirmishValueInArea.cpp (per-player mask loop),
// BFME2 sums the template float at +0x51C instead of the build cost.
// Status: 596 vs 587, only the member loop differs: VC7 CSEs &pObj->m_template
// into EDI and spills pObj to [ebp+0xC] (team in ESI); retail keeps team in EDI,
// pObj in ESI and reloads [esi+4]. Tried: null-pObj check (616), nested vs continue,
// isKindOf59 Object inline, tmpl local, hoisted pObj/tt/team, separate list iterators,
// oiter.cur() per use (584, worse), bit-math isKindOf (not inlined), virtual Object dtor,
// G6/Ob1/Ow, accessor-numbering perturbations. All 243 masked diffs.
// The compare must read pValueParm->m_real directly: the TU's /Op loads an inline
// getReal() into xmm1, retail compares against memory for cases 2-5.
// TU decls needed (ScriptConditions_evaluateTeamStateIs.cpp): ThingTemplate float
// m_51C at +0x51C (getRva51C), Team bool m_enteredOrExited at +0x5C (didEnterOrExit),
// Object::isKindOf59() { return m_template->testKindOf59(); }, ScriptConditions decl.
bool ScriptConditions::evaluateSkirmishValueInArea(Condition *pCondition, Parameter *pSkirmishPlayerParm,
	Parameter *pComparisonParm, Parameter *pValueParm, Parameter *pTriggerParm)
{
	int mask = TheScriptEngine->rva00357B82(pSkirmishPlayerParm);
	float total = 0;
	while (mask) {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (!player) continue;
		PolygonTrigger *pTrig = TheScriptEngine->getQualifiedTriggerAreaByName(pTriggerParm->getString());
		if (!pTrig) continue;
		PlayerTeamList::const_iterator it;
		bool anyChanges = false;
		if (pCondition->getCustomData() == 0) anyChanges = true;
		for (it = player->getPlayerTeams()->begin(); it != player->getPlayerTeams()->end(); ++it) {
			if (anyChanges) break;
			for (DLINK_ITERATOR<Team> iter = (*it)->iterate_TeamInstanceList(); !iter.done(); iter.advance()) {
				if (anyChanges) break;
				Team *team = iter.cur();
				if (!team) continue;
				if (team->didEnterOrExit()) anyChanges = true;
			}
		}
		if (TheScriptEngine->getFrameObjectCountChanged() != pCondition->getCustomFrame()) anyChanges = true;
		if (!anyChanges) {
			if (pCondition->getCustomData() == -1) continue;
			if (pCondition->getCustomData() == 1) return true;
		}
		for (it = player->getPlayerTeams()->begin(); it != player->getPlayerTeams()->end(); ++it) {
			for (DLINK_ITERATOR<Team> iter = (*it)->iterate_TeamInstanceList(); !iter.done(); iter.advance()) {
				Team *team = iter.cur();
				if (!team) continue;
				for (DLINK_ITERATOR<Object> oiter = team->iterate_TeamMemberList(); !oiter.done(); oiter.advance()) {
					Object *pObj = oiter.cur();
					if (pObj->isKindOf59()) continue;
					if (!pObj->isInside(pTrig)) continue;
					if (pObj->isEffectivelyDead()) continue;
					const ThingTemplate *tt = pObj->getTemplate();
					if (!tt) continue;
					total += tt->getRva51C();
				}
			}
		}
	}
	bool comparison = false;
	switch (pComparisonParm->getInt()) {
	case 0: comparison = total < pValueParm->m_real; break;
	case 1: comparison = total <= pValueParm->m_real; break;
	case 2: comparison = total == pValueParm->m_real; break;
	case 3: comparison = total >= pValueParm->m_real; break;
	case 4: comparison = total > pValueParm->m_real; break;
	case 5: comparison = total != pValueParm->m_real; break;
	}
	pCondition->setCustomFrame(TheScriptEngine->getFrameObjectCountChanged());
	if (comparison) { pCondition->setCustomData(1); return true; }
	pCondition->setCustomData(-1);
	return false;
}