// ?rva003E64A6@ScriptConditions@@IAE_NPAVCondition@@PAVParameter@@1111@Z
// partial score=0.95 date=2026-10-08
// ?rva003E64A6@ScriptConditions@@IAE_NPAVCondition@@PAVParameter@@1111@Z
// partial score=0.95 date=2026-10-08
// cl: (unit) Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions_evaluateTeamStateIs.cpp, /O1 /arch:SSE /G7 /Op
// 0x003E64A6 559B, case 75 PLAYER_HAS_COMPARISON_UNIT_KIND_IN_TRIGGER_AREA. Donor: BFME 1
// ScriptConditionsRva0032ABC0.cpp. Body below compiles in that unit with these additions:
//   ThingTemplate: int rva000456AC(int kind) const;
//                  bool isKindOf(int kind) const { return (unsigned char)rva000456AC(kind) != 0; }
//   Team: bool didEnterOrExit() const { return m_enteredOrExited; }  (bool at +0x5C)
//   ScriptConditions: bool rva003E64A6(Condition *, Parameter * x5);
// Same size and instruction stream as retail except register allocation in the second
// (counting) walk: retail keeps the prototype iterator in memory ([ebp+0x1C]) and gives
// the member EDI and the template EBX (count shares EBX); VC7 here gives the iterator EBX
// and spills the member. Unchanged by: separate/hoisted iterators, raw node walk, it++,
// hoisting obj/tmpl/team, forceinline walk helper, nesting vs continue, flags (G6, no Op).
// A tmpl local is required (without it VC7 CSEs &obj->m_template and reloads after the call).
bool ScriptConditions::rva003E64A6(Condition *pCondition, Parameter *pPlayerParm, Parameter *pComparisonParm,
	Parameter *pCountParm, Parameter *pKindParm, Parameter *pTriggerParm)
{
	PolygonTrigger *pTrig = TheScriptEngine->getQualifiedTriggerAreaByName(pTriggerParm->getString());
	if (pTrig == 0)
		return false;
	int kind = pKindParm->getInt();
	int playerMask = TheScriptEngine->rva00357B82(pPlayerParm);
	int count = 0;
	while (playerMask) {
		Player *pPlayer = ThePlayerList->getEachPlayerFromMask(playerMask);
		PlayerTeamList::const_iterator it;
		bool anyChanges = false;
		if (pCondition->getCustomData() != 0 && TheScriptEngine->getFrameObjectCountChanged() <= pCondition->getCustomFrame()) {
			for (it = pPlayer->getPlayerTeams()->begin(); it != pPlayer->getPlayerTeams()->end(); ++it) {
				if (anyChanges)
					break;
				for (DLINK_ITERATOR<Team> iter = (*it)->iterate_TeamInstanceList(); !iter.done(); iter.advance()) {
					if (anyChanges)
						break;
					Team *team = iter.cur();
					if (!team)
						continue;
					if (team->didEnterOrExit())
						anyChanges = true;
				}
			}
			if (!anyChanges) {
				if (pCondition->getCustomData() == -1)
					continue;
				if (pCondition->getCustomData() == 1)
					return true;
			}
		}
		for (it = pPlayer->getPlayerTeams()->begin(); it != pPlayer->getPlayerTeams()->end(); ++it) {
			for (DLINK_ITERATOR<Team> titer = (*it)->iterate_TeamInstanceList(); !titer.done(); titer.advance()) {
				Team *team = titer.cur();
				if (!team)
					continue;
				for (DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList(); !iter.done(); iter.advance()) {
					Object *pObj = iter.cur();
					if (!pObj)
						continue;
					const ThingTemplate *tmpl = pObj->getTemplate();
					if (tmpl->isKindOf(kind)) {
						if (!tmpl->testKindOf59() && pObj->isInside(pTrig)) {
							if (!pObj->isEffectivelyDead())
								count++;
						}
					}
				}
			}
		}
	}
	bool comparison = false;
	switch (pComparisonParm->getInt()) {
		case 0: comparison = (count < pCountParm->getInt()); break;
		case 1: comparison = (count <= pCountParm->getInt()); break;
		case 2: comparison = (count == pCountParm->getInt()); break;
		case 3: comparison = (count >= pCountParm->getInt()); break;
		case 4: comparison = (count > pCountParm->getInt()); break;
		case 5: comparison = (count != pCountParm->getInt()); break;
	}
	pCondition->setCustomData(TheScriptEngine->getFrameObjectCountChanged());
	return comparison;
}
