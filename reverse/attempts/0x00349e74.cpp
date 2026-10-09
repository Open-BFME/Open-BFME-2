// ?rva00349E74@AIFollowPathAsTeamState@@AAE_NXZ
// partial score=0.96 date=2026-10-09
// Patch against Code/GameEngine/Source/GameLogic/AI/AIAttackApproachTargetStateOnEnter.cpp at f51fc086d9: git apply (unit-level stash).
diff --git a/Code/GameEngine/Source/GameLogic/AI/AIAttackApproachTargetStateOnEnter.cpp b/Code/GameEngine/Source/GameLogic/AI/AIAttackApproachTargetStateOnEnter.cpp
index d95227283a..e8514eef38 100644
--- a/Code/GameEngine/Source/GameLogic/AI/AIAttackApproachTargetStateOnEnter.cpp
+++ b/Code/GameEngine/Source/GameLogic/AI/AIAttackApproachTargetStateOnEnter.cpp
@@ -1,4 +1,4 @@
-// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
+// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /DNDEBUG /MD /EHsc
 //
 // AIAttackApproachTargetState::onEnter, retail 0x0034CD3A (783 bytes): slot 4
 // of vtable 0x00C12610 (slot-2 name getter "AIAttackApproachTargetState";
@@ -92,6 +92,7 @@
 #include "../../Common/GameLogicObjectLookupView.h"
 #include "../../../../Libraries/Include/Lib/Coord3D.h"
 #include "../../../../Libraries/Include/Lib/Coord2D.h"
+#include "Common/Snapshot.h"
 
 typedef bool Bool;
 typedef float Real;
@@ -178,6 +179,8 @@ public:
 	Bool m_aiCrushesInfantry; // +0x8C
 	unsigned char m_pad8D[0x94 - 0x8D];
 	Real m_94; // +0x94 (the squish retarget range)
+	unsigned char m_pad98[0xB8 - 0x98];
+	Bool m_teamPathWait; // +0xB8 (team path members wait for each other)
 };
 
 class Rva002C9B80Owner;
@@ -242,6 +245,7 @@ public:
 		PRECISE_Z_POS
 	};
 	Real getMaxTurnRate(Object *obj) const;
+	const struct LocomotorTemplateView *getTemplate() const { return m_template; }
 	void setUsePreciseZPos(Bool b)
 	{
 		if (b)
@@ -250,10 +254,19 @@ public:
 			m_flags &= ~(1 << PRECISE_Z_POS);
 	}
 private:
-	unsigned char m_pad00[0x44];
+	unsigned char m_pad00[0x04];
+	const struct LocomotorTemplateView *m_template; // +0x04
+	unsigned char m_pad08[0x44 - 0x08];
 	unsigned int m_flags; // +0x44
 };
 
+// Locomotor template byte +0x10B (set for walking locomotors).
+struct LocomotorTemplateView
+{
+	unsigned char m_pad00[0x10B];
+	Bool m_10b; // +0x10B
+};
+
 // Locomotor speed for an object (0x001E46E1), rowed under this name.
 class Rva001E46E1
 {
@@ -412,27 +425,96 @@ private:
 	Coord3D m_position; // +0x38
 };
 
+class Team;
 class TeamPrototype
 {
 public:
 	unsigned char m_pad00[0x216];
 	Bool m_216; // +0x216
+	unsigned char m_pad217[0x334 - 0x217];
+	Team *m_dlinkhead_TeamInstanceList; // +0x334
+};
+
+template<class OBJCLASS>
+class DLINK_ITERATOR
+{
+public:
+	typedef OBJCLASS* (OBJCLASS::*GetNextFunc)() const;
+private:
+	OBJCLASS* m_cur;
+	GetNextFunc m_getNextFunc;
+public:
+	DLINK_ITERATOR(OBJCLASS* cur, GetNextFunc getNextFunc) : m_cur(cur), m_getNextFunc(getNextFunc)
+	{
+	}
+	void advance()
+	{
+		if (m_cur)
+			m_cur = ((*m_cur).*(m_getNextFunc))();
+	}
+	Bool done() const
+	{
+		return m_cur == 0;
+	}
+	OBJCLASS* cur() const
+	{
+		return m_cur;
+	}
 };
 
-class Team
+// The member walk (rowed iterate_TeamMemberList 0x00263864 and advance
+// 0x00263526), as ScriptActions_doPlayerForceEmotion.cpp declares it.
+template <>
+class DLINK_ITERATOR<Object>
+{
+private:
+	Object *m_cur;
+	unsigned char m_targetAbiState[20];
+public:
+	void advance();
+	bool done() const { return m_cur == 0; }
+	Object *cur() const { return m_cur; }
+};
+
+class MemoryPoolObject
+{
+public:
+	virtual ~MemoryPoolObject();
+};
+
+// Team derives from MemoryPoolObject and Snapshot, so its member pointers
+// carry a this adjustment (the 8-byte PMF in the team instance walk).
+class Team : public MemoryPoolObject, public Snapshot
 {
 public:
 	Object *getTeamTargetObject();
 	void rva0039D84A(Object *target);
-	unsigned char m_pad00[0x30];
+	Team *dlink_next_TeamInstanceList() const;
+	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
+	unsigned char m_pad08[0x30 - 0x08];
 	TeamPrototype *m_proto; // +0x30
 };
 
+inline DLINK_ITERATOR<Team> iterate_TeamInstanceList(const TeamPrototype *proto)
+{
+	return DLINK_ITERATOR<Team>(proto->m_dlinkhead_TeamInstanceList, &Team::dlink_next_TeamInstanceList);
+}
+
+struct PlayerTeamNode
+{
+	PlayerTeamNode *m_next;
+	PlayerTeamNode *m_prev;
+	TeamPrototype *m_value;
+};
+
 class Player
 {
 public:
+	PlayerTeamNode *getPlayerTeams() const { return m_playerTeamPrototypes; }
 	unsigned char m_pad00[0x5C];
 	Int m_playerType; // +0x5C
+	unsigned char m_pad60[0x32C - 0x60];
+	PlayerTeamNode *m_playerTeamPrototypes; // +0x32C
 };
 
 class Object : public Thing
@@ -465,6 +547,7 @@ public:
 	Bool rva0028ADE0() const;
 	const Rva0028AC4EEntry *rva0028AC4E() const;
 	void rva0028CDB6();
+	Bool rva0028C264(Int *out, Int kind);
 	Real GetRelativeAngle(const Coord3D *pos) const;
 	Real getOrientation() const { return m_orientation; }
 	Bool rva002943B2(const Player *player);
@@ -504,7 +587,9 @@ public:
 	Object *m_containedBy; // +0x274
 	unsigned char m_pad278[0x304 - 0x278];
 	Team *m_team; // +0x304
-	unsigned char m_pad308[0x438 - 0x308];
+	unsigned char m_pad308[0x410 - 0x308];
+	Int m_410; // +0x410 (the team path group)
+	unsigned char m_pad414[0x438 - 0x414];
 	UnsignedInt m_438; // +0x438
 };
 
@@ -859,6 +944,7 @@ public:
 protected:
 	virtual Bool computePath();
 private:
+	Bool rva00349E74(); // the team path wait (0x00349E74, after onExit)
 	Int m_index; // +0x4C
 	unsigned char m_pad50[0x54 - 0x50];
 	Bool m_adjustFinal; // +0x54
@@ -2007,6 +2093,58 @@ StateReturnType AIFollowPathAsTeamState::onEnter()
 	return ret;
 }
 
+// Retail 0x00349E74, 348 bytes (after AIFollowPathAsTeamState::onExit; the
+// team path update asks it before leaving a path point). With TAiData +0xB8
+// set, an owner still on its first two path points with a walking locomotor
+// (template byte +0x10B) waits until every other member of its controlling
+// player's teams in the same path group (+0x410) that is following the path
+// (AI state 0x36, walking) has reached the same point; the 0x0028C264 kind-4
+// query on the owner or on any member ends the wait.
+Bool AIFollowPathAsTeamState::rva00349E74()
+{
+	if (!TheAI->getAiData()->m_teamPathWait)
+		return true;
+	Object *owner = getMachineOwner();
+	AIUpdateInterface *ai = owner->getAI();
+	if (!ai)
+		return true;
+	Int group = owner->m_410;
+	Int index = ai->m_currentGoalPathIndex;
+	if (index > 1)
+		return true;
+	if (ai->getCurLocomotor() && !ai->getCurLocomotor()->getTemplate()->m_10b)
+		return true;
+	Int unused;
+	if (owner->rva0028C264(&unused, 4))
+		return true;
+
+	Bool ready = true;
+	Player *player = owner->getControllingPlayer();
+	for (PlayerTeamNode *it = player->getPlayerTeams()->m_next; it != player->getPlayerTeams(); it = it->m_next)
+	{
+		for (DLINK_ITERATOR<Team> iter = iterate_TeamInstanceList(it->m_value); !iter.done(); iter.advance())
+		{
+			Team *team = iter.cur();
+			if (!team)
+				continue;
+			for (DLINK_ITERATOR<Object> objIter = team->iterate_TeamMemberList(); !objIter.done(); objIter.advance())
+			{
+				Object *member = objIter.cur();
+				if (member->m_410 != group || member == owner)
+					continue;
+				AIUpdateInterface *memberAI = member->getAI();
+				if (member->rva0028C264(&unused, 4))
+					return true;
+				if (memberAI && memberAI->rva00260DED() == 0x36 &&
+					(!memberAI->getCurLocomotor() || memberAI->getCurLocomotor()->getTemplate()->m_10b) &&
+					memberAI->m_currentGoalPathIndex != index)
+					ready = false;
+			}
+		}
+	}
+	return ready;
+}
+
 // A state's slot 8, ZH State::isAttack.
 class StateAttackView : public VirtualSlots<8>
 {
