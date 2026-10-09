// ?rva003E59B0@ScriptConditions@@QAE_NPBVAsciiString@@0PAVParameter@@_N@Z
// partial score=0.93 date=2026-10-09
// BANK for ?rva003E59B0@ScriptConditions@@QAE_NPBVAsciiString@@0PAVParameter@@_N@Z
// (retail 0x003E59B0, 313 bytes, RET 0x10). Add to
// Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions_Rva003E6ED0.cpp
// (the team twin) with Object gaining getPosition (+0x38), didEnter 0x0028D718
// and didExit 0x0028D757, and the class declaration of the method; needs /O1
// (the host file's default flags give 412 bytes), so a separate /O1 unit with
// the same views is the likely home. Under /O1 it compiles to 314 bytes with
// the same instructions except: retail keeps the unit in ESI and spills it to
// the dead unitName argument slot (castle reuses ESI, the CastleBehavior stays
// in EDI across the area loop), and the shared return-false block sits at the
// castle-null test rather than the unit-null test.

// ScriptConditions::rva003E59B0, retail 0x003E59B0, 313 bytes (RET 0x10): the
// unit form of the castle area test below -- the named unit against the named
// castle or, with no castle name and a player parameter naming no player, the
// closest KindOf-120 object to the unit through the same filter chain; the
// unit's didEnter / didExit against the castle's areas 1..7.
bool ScriptConditions::rva003E59B0(const AsciiString *unitName, const AsciiString *castleName,
	Parameter *playerParm, bool entered)
{
	Object *obj = TheScriptEngine->getUnitNamed(*unitName);
	if (!obj)
		return false;
	Object *castle;
	if (castleName) {
		castle = TheScriptEngine->getUnitNamed(*castleName);
	} else {
		if (!playerParm)
			return false;
		Player *player = ThePlayerList->getPlayerFromMask(TheScriptEngine->rva00357475(playerParm->getString(), 0));
		if (player)
			return false;
		castle = ThePartitionManager->getClosestObject(obj->getPosition(), REALLY_FAR, 0,
			Rva0004584D(BfmeFixedStorage0004543D(0, 0x78), *(const BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype)
				.link(&Rva0026137EFilter(player, true)));
	}
	if (!castle)
		return false;
	CastleBehavior *behavior = (CastleBehavior *)castle->findModule(CastleBehavior::rva0003955DA());
	if (!behavior)
		return false;
	int i = 0;
	do {
		++i;
		PolygonTrigger *area = behavior->rva00395E53(i);
		if (!area)
			return false;
		if (entered ? obj->didEnter(area) : obj->didExit(area))
			return true;
	} while (i < 7);
	return false;
}
