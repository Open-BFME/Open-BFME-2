// ?selectTeamToReinforce@AIPlayer@@MAE_NH@Z
// partial score=0.9 date=2026-10-08
// Bank for AIPlayer::selectTeamToReinforce (0x4F3DB1, 985 B), 996 B / 307 diff lines.
// Apply this patch to Code/GameEngine/Source/GameLogic/AI/AIPlayerTeamBuild.cpp at 0126876dae
// (the TU's flags and types); the patch adds the Team MI layout, TeamPrototype fields and the body.
#if 0
--- Code/GameEngine/Source/GameLogic/AI/AIPlayerTeamBuild.cpp	2026-10-08 04:19:53.848261226 +0000
+++ build/str_bank_AIPlayerTeamBuild.cpp	2026-10-08 04:19:48.852215830 +0000
@@ -732,6 +732,8 @@
 };
 extern AI *TheAI;
 
+template <class OBJCLASS> class DLINK_ITERATOR;
+
 struct TCreateUnitsInfo
 {
 	Int minUnits;			// +0x00
@@ -742,6 +744,18 @@
 	Int m_14;			// +0x14
 };
 
+// TeamPrototype +0x130 (ZH's TeamTemplateInfo m_teamTemplate).
+struct TeamTemplateInfo
+{
+	TCreateUnitsInfo m_unitsInfo[7];	// +0x00
+	Int m_numUnitsInfo;			// +0xA8
+	Coord3D m_homeLocation;			// +0xAC
+	char m_padB8[0xE3 - 0xB8];
+	Bool m_automaticallyReinforce;		// +0xE3
+	char m_padE4[0xEC - 0xE4];
+	Int m_productionPriority;		// +0xEC
+};
+
 class TeamPrototype
 {
 public:
@@ -759,6 +773,8 @@
 	AsciiString m_owner;			// +0x10
 	AsciiString m_name;			// +0x14
 	Int m_flags;				// +0x18
+	const TeamTemplateInfo *getTemplateInfo() const { return (const TeamTemplateInfo *)m_unitsInfo; }
+
 	char m_pad01C[0x130 - 0x1C];
 	TCreateUnitsInfo m_unitsInfo[7];	// +0x130
 	Int m_numUnitsInfo;			// +0x1D8
@@ -766,7 +782,9 @@
 	Bool m_hasHomeLocation;			// +0x1E8
 	char m_pad1E9[0x210 - 0x1E9];
 	Bool m_bfme210;				// +0x210
-	char m_pad211[0x218 - 0x211];
+	char m_pad211[0x213 - 0x211];
+	Bool m_automaticallyReinforce;		// +0x213
+	char m_pad214[0x218 - 0x214];
 	Int m_maxInstances;			// +0x218
 	Int m_productionPriority;		// +0x21C
 	char m_pad220[0x23C - 0x220];
@@ -775,6 +793,10 @@
 	char m_pad241[0x31C - 0x241];
 	Bool m_bfme31C;				// +0x31C
 	Bool m_bfme31D;				// +0x31D
+	char m_pad31E[0x334 - 0x31E];
+	Team *m_dlinkhead_TeamInstanceList;	// +0x334
+
+	DLINK_ITERATOR<Team> iterate_TeamInstanceList() const;
 };
 
 template <class OBJCLASS> class DLINK_ITERATOR
@@ -804,21 +826,32 @@
 	unsigned char m_state[20];
 };
 
+class MemoryPoolObject
+{
+public:
+	virtual ~MemoryPoolObject();
+};
+
+// The subobject at Team +0x04 (ZH's Snapshot base); 0x0055B156 pushes onto
+// its list.
 class Rva0055B156
 {
 public:
 	void rva0055B156(int val);
 };
 
-class Team
+// Two bases, as retail's Team: its member pointers carry an adjustor
+// (TeamPrototype's instance-list iterator stores {0x005C4AF5, 0}).
+class Team : public MemoryPoolObject, public Rva0055B156
 {
 public:
 	virtual ~Team();
-	Rva0055B156 m_bfme04;			// +0x04
+	Rva0055B156 &bfme04() { return *this; }
 	char m_pad005[0x30 - 0x05];
 	TeamPrototype *m_proto;			// +0x30
 	unsigned int m_id;			// +0x34
-	char m_pad038[0x5D - 0x38];
+	Object *m_dlinkhead_TeamMemberList;	// +0x38
+	char m_pad03C[0x5D - 0x3C];
 	Bool m_active;				// +0x5D
 	Bool m_created;				// +0x5E
 	char m_pad05F[0x110 - 0x5F];
@@ -830,6 +863,10 @@
 	Object *tryToRecruit(const ThingTemplate *thing, const Coord3D *pos, Real maxDist, Int a, Int b, Int c);
 	Bool rva0039DFF8();
 	Bool hasAnyObjects(Bool ignoreBuilding);
+	Bool rva0039DEC4();		// any member of a kind (ZH hasAnyUnits)
+	void countObjectsByThingTemplate(Int numTmplates, const ThingTemplate * const *things, Bool ignoreDead, Int *counts, Bool ignoreUnderConstruction) const;
+	Team *dlink_next_TeamInstanceList() const;
+	Object *getFirstItemIn_TeamMemberList() const { return m_dlinkhead_TeamMemberList; }
 	void setActive() { if (!m_active) { m_created = true; m_active = true; } }
 	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
 	const AsciiString &getOwnerName() const { return m_proto == 0 ? AsciiString::TheEmptyString : m_proto->getOwnerName(); }
@@ -839,6 +876,11 @@
 	__forceinline void deleteInstance() { ::delete this; }
 };
 
+inline DLINK_ITERATOR<Team> TeamPrototype::iterate_TeamInstanceList() const
+{
+	return DLINK_ITERATOR<Team>(m_dlinkhead_TeamInstanceList, &Team::dlink_next_TeamInstanceList);
+}
+
 class WorkOrder
 {
 public:
@@ -1435,9 +1477,9 @@
 		{
 			for (Int i = order->m_numCompleted; i < order->m_numRequired; i++)
 			{
-				void *unit = record->rva004EC088(1, &team->m_bfme04, &order->m_thing->getName());
+				void *unit = record->rva004EC088(1, &team->bfme04(), &order->m_thing->getName());
 				if (unit)
-					team->m_bfme04.rva0055B156((int)unit);
+					team->bfme04().rva0055B156((int)unit);
 			}
 		}
 		order->m_bfmeFlag28 = true;
@@ -1864,6 +1906,112 @@
 	return false;
 }
 
+Bool AIPlayer::selectTeamToReinforce(Int minPriority)
+{
+	PlayerTeamList::const_iterator t;
+	Team *curTeam = NULL;
+	Int curPriority = minPriority;
+	const ThingTemplate *curThing = NULL;
+	Int curRecruitKind = -1;
+	for (t = m_player->getPlayerTeams()->begin(); t != m_player->getPlayerTeams()->end(); ++t)
+	{
+		TeamPrototype *proto = (*t);
+		Bool busy = false;
+		for (DLINK_ITERATOR<TeamInQueue> iter = iterate_TeamBuildQueue(); !iter.done(); iter.advance())
+		{
+			TeamInQueue *team = iter.cur();
+			if (team->m_team->getPrototype() == proto)
+				busy = true;
+		}
+		if (busy) continue;
+		if (proto->m_automaticallyReinforce && proto->m_productionPriority > curPriority)
+		{
+			for (DLINK_ITERATOR<Team> iter = proto->iterate_TeamInstanceList(); !iter.done(); iter.advance())
+			{
+				Team *team = iter.cur();
+				if (team->rva0039DEC4() == false)
+					continue;
+				const TCreateUnitsInfo *unitInfo = &team->getPrototype()->m_unitsInfo[0];
+				for (int i = 0; i < team->getPrototype()->m_numUnitsInfo; i++)
+				{
+					if (unitInfo[i].maxUnits < 1) continue;
+					const ThingTemplate *thing = TheThingFactory->findTemplate(unitInfo[i].unitThingName);
+					if (thing == NULL) continue;
+					Int count = 0;
+					team->countObjectsByThingTemplate(1, &thing, false, &count, true);
+					if (count < unitInfo[i].maxUnits)
+					{
+						if (NULL != findFactory(thing, false, NULL))
+						{
+							curTeam = team;
+							curPriority = proto->m_productionPriority;
+							curThing = thing;
+							curRecruitKind = unitInfo[i].m_14;
+						}
+					}
+				}
+			}
+		}
+	}
+	if (curTeam && curThing)
+	{
+		TeamInQueue *teamQ = NULL;
+		WorkOrder *order = NULL;
+		if (!g_00DFEEF8->rva002A8AB1(m_player))
+		{
+			teamQ = new TeamInQueue;
+			prependTo_TeamBuildQueue(teamQ);
+			teamQ->m_priorityBuild = false;
+			teamQ->m_reinforcement = true;
+			order = new WorkOrder;
+			order->m_factoryID = (ObjectID)0;
+			order->m_next = NULL;
+			order->m_thing = curThing;
+			order->m_numRequired = 1;
+			order->m_required = true;
+			teamQ->m_workOrders = order;
+			teamQ->m_frameStarted = TheGameLogic->getFrame();
+			teamQ->m_team = curTeam;
+			AsciiString teamName = curTeam->getPrototype()->getName();
+			teamName.concat(" - AutoReinforcing one ");
+			teamName.concat(curThing->getName());
+			TheScriptEngine->AppendDebugMessage(teamName, false);
+		}
+		Coord3D origin;
+		origin = curTeam->getPrototype()->m_homeLocation;
+		if (curTeam->getFirstItemIn_TeamMemberList())
+			origin = curTeam->getFirstItemIn_TeamMemberList()->m_pos;
+		Object *unit = curTeam->tryToRecruit(curThing, &origin, TheAI->getAiData()->m_maxRecruitDistance, curRecruitKind, 0, 0);
+		if (unit)
+		{
+			if (order)
+				order->m_numCompleted = 1;
+			AsciiString teamStr = "Team '";
+			teamStr.concat(curTeam->getPrototype()->getName());
+			teamStr.concat("' recruits ");
+			teamStr.concat(curThing->getName());
+			teamStr.concat(" from team '");
+			teamStr.concat(unit->m_team->getPrototype()->getName());
+			teamStr.concat("'");
+			TheScriptEngine->AppendDebugMessage(teamStr, false);
+			unit->setTeam(curTeam);
+			if (teamQ)
+				teamQ->m_reinforcementID = unit->getID();
+			AIUpdateInterface *ai = unit->getAI();
+			if (ai)
+				ai->getCommandInterface()->aiIdle(CMD_FROM_AI);
+		}
+		else if (!g_00DFEEF8->rva002A8AB1(m_player))
+		{
+			startTraining(order, teamQ->m_priorityBuild, teamQ->m_team->getName());
+		}
+		m_teamDelay = 0;
+		return true;
+	}
+	return false;
+}
+
+
 void AIPlayer::checkReadyTeams()
 {
 	{
#endif
