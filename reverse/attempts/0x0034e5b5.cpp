// ?update@AIFollowPathAsTeamState@@UAE?AW4StateReturnType@@XZ
// partial score=0.93 date=2026-10-09
// Patch against Code/GameEngine/Source/GameLogic/AI/AIAttackApproachTargetStateOnEnter.cpp at 8bed71659d: apply with git apply (unit-level stash; the unit exceeds the 64 KiB stash cap).
diff --git a/Code/GameEngine/Source/GameLogic/AI/AIAttackApproachTargetStateOnEnter.cpp b/Code/GameEngine/Source/GameLogic/AI/AIAttackApproachTargetStateOnEnter.cpp
index bee4807b80..159d4b1604 100644
--- a/Code/GameEngine/Source/GameLogic/AI/AIAttackApproachTargetStateOnEnter.cpp
+++ b/Code/GameEngine/Source/GameLogic/AI/AIAttackApproachTargetStateOnEnter.cpp
@@ -179,6 +179,7 @@ public:
 };
 
 class Rva002C9B80Owner;
+class LocomotorSet;
 
 class Pathfinder
 {
@@ -187,6 +188,7 @@ public:
 	Bool CanApproachToTarget(Object *obj, const Coord3D *targetPos, Rva002C9B80Owner *weapon, Bool flag);
 	Bool QuickDoesPathExistToStructure(Object *obj, const Coord3D *fromPos, Object *structure, Int flag);
 	Bool QuickDoesPathExist(Object *obj, const Coord3D *fromPos, const Coord3D *toPos, Int flag);
+	Bool adjustDestination(Object *obj, const LocomotorSet &locomotorSet, Coord3D *dest, const Coord3D *groupDest);
 };
 
 enum NameKeyType
@@ -302,9 +304,10 @@ template <> class AIApproachAISlots<0>
 {
 };
 
-class AIUpdateInterface : public AIApproachAISlots<136>
+class AIUpdateInterface : public AIApproachAISlots<135>
 {
 public:
+	virtual void slot135(Real angle) = 0; // turns the owner toward angle
 	virtual void slot136() = 0;
 	virtual Bool isDoingGroundMovement() const = 0;
 	virtual void slot138() = 0;
@@ -326,6 +329,12 @@ public:
 	void setCurrentVictim(const Object *victim);
 	Bool computeQuickPath(const Coord3D *destination);
 	Object *checkForCrateToPickup();
+	Object *getNextMoodTarget(Bool calledByAI, Bool calledDuringIdle);
+	void rva00262AEA();
+	void rva00262ACE();
+	void setDesiredSpeed(Real speed);
+	void rva00262FEB(Int id); // +0x164 setter (ZH ignoreObstacleID)
+	const LocomotorSet *getLocomotorSet() const { return (const LocomotorSet *)m_locomotorSet; }
 	void requestPath(Coord3D *destination, Bool isFinalGoal);
 	void requestAttackPath(ObjectID victimID, const Coord3D *victimPos);
 	void destroyPath();
@@ -345,7 +354,11 @@ private:
 public:
 	class Rva00346FA5 *m_goalPath; // +0x30
 private:
-	unsigned char m_pad034[0x70 - 0x34];
+	unsigned char m_pad034[0x48 - 0x34];
+public:
+	Int m_48; // +0x48
+private:
+	unsigned char m_pad04C[0x70 - 0x4C];
 public:
 	const AttackPriorityInfo *m_attackInfo; // +0x70
 private:
@@ -359,7 +372,7 @@ public:
 	unsigned char m_pad18C[0x194 - 0x18C];
 	Int m_currentGoalPathIndex; // +0x194
 	unsigned char m_pad198[0x1A0 - 0x198];
-	Int m_1a0; // +0x1A0
+	Real m_1a0; // +0x1A0
 	unsigned char m_pad1A4[0x1CC - 0x1A4];
 	unsigned char m_locomotorSet[0x1F0 - 0x1CC]; // +0x1CC
 private:
@@ -401,6 +414,7 @@ public:
 	const ThingTemplate *getTemplate() const { return m_template; }
 	const Coord3D *getPosition() const { return &m_position; }
 	const Coord3D *getUnitDirectionVector2D() const;
+	void setOrientation(Real angle);
 private:
 	unsigned char m_pad00[0x04];
 	const ThingTemplate *m_template; // +0x04
@@ -461,6 +475,7 @@ public:
 	Bool rva0028ADE0() const;
 	const Rva0028AC4EEntry *rva0028AC4E() const;
 	void rva0028CDB6();
+	void rva0028AE6D();
 	Real GetRelativeAngle(const Coord3D *pos) const;
 	Real getOrientation() const { return m_orientation; }
 	Bool rva002943B2(const Player *player);
@@ -485,7 +500,9 @@ public:
 	Int m_id; // +0x74
 	unsigned char m_pad078[0xB8 - 0x78];
 	Real m_geometryRadiusB8; // +0xB8
-	unsigned char m_pad0BC[0x1C0 - 0xBC];
+	unsigned char m_pad0BC[0x110 - 0xBC];
+	UnsignedInt m_110; // +0x110 (bit 29 cleared by the team path wait)
+	unsigned char m_pad114[0x1C0 - 0x114];
 	Real m_1c0; // +0x1C0
 	unsigned char m_pad1C4[0x1C8 - 0x1C4];
 	UnsignedInt m_1c8; // +0x1C8
@@ -613,6 +630,7 @@ public:
 	void setGoalPosition(const Coord3D *pos);
 	Object *getOwner() const { return m_owner; }
 	Object *getGoalObject();
+	inline Bool isInIdleState() const;
 	const Coord3D *getGoalPosition() const { return &m_goalPosition; }
 private:
 	StateIdView *m_currentState; // +0x04
@@ -670,6 +688,7 @@ public:
 protected:
 	virtual Bool computePath();
 	void setAdjustsDestination(Bool b) { m_adjustsDestination = b; }
+	Bool getAdjustsDestination() const;
 	unsigned char m_pad1C[0x20 - 0x1C];
 	Coord3D m_goalPosition; // +0x20
 	unsigned char m_pad2C[0x48 - 0x2C];
@@ -830,20 +849,37 @@ public:
 	virtual void setLocomotorGoalOrientation(Real angle);
 };
 
-// The AI's goal path (+0x30): position by index (0x00346FA5).
+// The AI's goal path (+0x30): position by index (0x00346FA5, defined below
+// before its AIStates callers).
 class Rva00346FA5
 {
 public:
 	void *rva00346FA5(Int index) const;
+private:
+	char m_pad[0x3C];
+	int m_begin3C;
+	int m_end40;
 };
 
-class Rva0034E3A5Helper
+// A state's slot 8 (Zero Hour's State::isIdle), as
+// StateMachine::isInIdleState asks the current state.
+class StateIdleView : public VirtualSlots<8>
 {
 public:
-	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04();
-	virtual void rva0034E3CESlot5();
-	virtual void s06(); virtual void s07();
-	virtual void rva0034E3D8Slot8(Int value);
+	virtual Bool isIdle() const;
+};
+
+inline Bool StateMachine::isInIdleState() const
+{
+	return m_currentState ? ((const StateIdleView *)m_currentState)->isIdle() : true;
+}
+
+// The state's owner AI's current locomotor speed (0x00340E5E, rowed under
+// this name in Rva00340E5EFloat.cpp).
+class Rva00340E5E
+{
+public:
+	Real rva00340E5E() const;
 };
 
 // AIFollowPathAsTeamState, vtable 0x00C121E8.
@@ -851,17 +887,20 @@ class AIFollowPathAsTeamState : public AIInternalMoveToState
 {
 public:
 	virtual StateReturnType onEnter();
+	virtual StateReturnType update();
 protected:
 	virtual Bool computePath();
 private:
+	Bool rva00349E74(); // the team-ready wait (0x00349E74, after onExit)
 	Int m_index; // +0x4C
-	unsigned char m_pad50[0x54 - 0x50];
+	Int m_retryCount; // +0x50
 	Bool m_adjustFinal; // +0x54
-	unsigned char m_pad55[0x57 - 0x55];
+	Bool m_adjustFinalOverride; // +0x55
+	Bool m_waitingForTeam; // +0x56
 	Bool m_57; // +0x57
 	Int m_lastCommandSource; // +0x58
-	Rva0034E3A5Helper *m_5c; // +0x5C
-	Int m_60; // +0x60
+	StateMachine *m_5c; // +0x5C (the team member's own attack machine)
+	Real m_60; // +0x60 (the facing to take at the end of the path)
 	Bool m_64; // +0x64
 };
 
@@ -1812,6 +1851,27 @@ Bool AIFollowPathAsTeamState::computePath()
 	return AIInternalMoveToState::computePath();
 }
 
+// Retail 0x00346FA5, 43 bytes: the bounds-checked 12-byte element accessor
+// of the AI goal path (+0x3C begin, +0x40 end). It sits in the AIStates unit
+// ahead of the path states that call it: AIFollowPathAsTeamState::update keeps
+// ECX and XMM1-XMM3 live across its calls, which cl only does for a callee it
+// has already compiled in the same unit.
+extern "C" void _ReadWriteBarrier(void);
+#pragma intrinsic(_ReadWriteBarrier)
+void *Rva00346FA5::rva00346FA5(int index) const
+{
+	if (index >= 0)
+	{
+		int count = (m_end40 - m_begin3C) / 12;
+		if ((unsigned)index < (unsigned)count)
+		{
+			_ReadWriteBarrier();
+			return (void *)(m_begin3C + index * 12);
+		}
+	}
+	return 0;
+}
+
 // Retail 0x0034E3A5, 528 bytes: slot 4 of AIFollowPathAsTeamState (vtable
 // 0x00C121E8). Zero Hour's AIFollowPathState::onEnter with BFME 2's team
 // additions: the +0x5C helper is reset (slots 5 and 8), the AI's last command
@@ -1827,8 +1887,8 @@ StateReturnType AIFollowPathAsTeamState::onEnter()
 	m_index = 0;
 	if (m_5c)
 	{
-		m_5c->rva0034E3CESlot5();
-		m_5c->rva0034E3D8Slot8(0);
+		m_5c->slot05();
+		m_5c->setState(AI_IDLE);
 	}
 	m_lastCommandSource = ai->slot143();
 	m_64 = false;
@@ -1897,6 +1957,204 @@ StateReturnType AIFollowPathAsTeamState::onEnter()
 	return ret;
 }
 
+// Retail 0x0034E5B5, 1481 bytes: slot 6 of AIFollowPathAsTeamState (vtable
+// 0x00C121E8). The team member first lets its own machine (+0x5C) finish an
+// attack, then picks up crates (state 0x27) or mood targets (state 10, AI
+// +0x48 = 2, +0x3C7); after the last point it turns to the +0x60 facing
+// (within PI/10 it snaps and succeeds). The movement half is Zero Hour's
+// AIFollowPathState::update with BFME 2's team wait (+0x56, rva00349E74), the
+// retry count (+0x50), the step-back flag (+0x57), the skip-behind test of the
+// next point, CritterDesync 47/48/35, and a failed adjustDestination halving
+// the way to the goal.
+static inline Real angleBetween(Real a, Real b)
+{
+	return normalizeAngle(a - b);
+}
+
+StateReturnType AIFollowPathAsTeamState::update()
+{
+	Object *obj = getMachineOwner();
+	AIUpdateInterface *ai = obj->getAI();
+	Bool resumed = false;
+	if (m_5c)
+	{
+		Bool wasBusy = false;
+		if (!m_5c->isInIdleState())
+		{
+			Object *goal = getMachineGoalObject();
+			if (goal && goal != m_5c->getGoalObject())
+				m_5c->setGoalObject(goal);
+			m_5c->updateStateMachine();
+			if (!m_5c || !m_5c->isInIdleState())
+				return STATE_CONTINUE;
+			wasBusy = true;
+			resumed = true;
+			ai->m_48 = m_lastCommandSource;
+		}
+		if (m_5c->isInIdleState())
+		{
+			Object *crate = ai->checkForCrateToPickup();
+			if (crate)
+			{
+				m_5c->setGoalObject(crate);
+				m_5c->setState(AI_PICK_UP_CRATE);
+				return STATE_CONTINUE;
+			}
+			Object *target = ai->getNextMoodTarget(!wasBusy, false);
+			if (target)
+			{
+				ai->rva00262AEA();
+				m_5c->setGoalObject(target);
+				m_5c->setState(AI_ATTACK_OBJECT);
+				ai->m_48 = 2;
+				ai->m_3c7 = true;
+				return STATE_CONTINUE;
+			}
+		}
+	}
+
+	getMachine()->setGoalPosition(&m_goalPosition);
+	StateReturnType status = STATE_SUCCESS;
+	if (m_64)
+	{
+		if (angleBetween(m_60, obj->getOrientation()) < 0.31415927f)
+		{
+			obj->setOrientation(m_60);
+			return STATE_SUCCESS;
+		}
+		ai->slot135(m_60);
+		return STATE_CONTINUE;
+	}
+
+	if (m_waitingForTeam)
+	{
+		if (((const unsigned char *)&obj->m_110)[3] & 0x20)
+		{
+			obj->m_110 &= ~0x20000000;
+			obj->rva0028AE6D();
+		}
+	}
+	else
+	{
+		status = AIInternalMoveToState::update();
+		if (status == STATE_FAILURE)
+		{
+			if (m_retryCount > 0)
+				m_retryCount--;
+			else
+				status = STATE_SUCCESS;
+		}
+		if (status != STATE_SUCCESS && status != STATE_FAILURE && !resumed)
+			return status;
+	}
+
+	if (!m_waitingForTeam && status == STATE_SUCCESS)
+	{
+		if (m_57 && m_index > 0)
+			m_index--;
+		const Coord3D *pos = (const Coord3D *)ai->m_goalPath->rva00346FA5(m_index + 1);
+		if (pos)
+		{
+			Real speed = ((const Rva00340E5E *)this)->rva00340E5E();
+			if (ai->isDoingGroundMovement())
+				ai->setDesiredSpeed(speed);
+			Real relative = obj->GetRelativeAngle(pos);
+			ai->slot135(normalizeAngle(obj->getOrientation() + relative));
+		}
+		m_index++;
+		ai->m_currentGoalPathIndex = m_index;
+		m_waitingForTeam = pos != 0;
+	}
+	if (m_waitingForTeam && !rva00349E74())
+		return STATE_CONTINUE;
+
+	m_waitingForTeam = false;
+	m_57 = false;
+	{
+		Object *obj = getMachineOwner();
+		AIUpdateInterface *ai = obj->getAI();
+		Real ownerX = obj->getPosition()->x;
+		Real ownerY = obj->getPosition()->y;
+		const Coord3D *pos = (const Coord3D *)ai->m_goalPath->rva00346FA5(m_index);
+		Bool tooClose = true;
+		while (pos && tooClose)
+		{
+			Real dx = pos->x - ownerX;
+			Real dy = pos->y - ownerY;
+			tooClose = false;
+			if (dy * dy + dx * dx < PATHFIND_CELL_SIZE_F * PATHFIND_CELL_SIZE_F)
+				tooClose = true;
+			Int nextIndex = m_index + 1;
+			const Coord3D *nextPos = (const Coord3D *)ai->m_goalPath->rva00346FA5(nextIndex);
+			if (nextPos && (nextPos->y - pos->y) * (pos->y - ownerY) + (nextPos->x - pos->x) * dx < 0.0f)
+				tooClose = true;
+			if (tooClose)
+			{
+				m_index = nextIndex;
+				pos = (const Coord3D *)ai->m_goalPath->rva00346FA5(nextIndex);
+			}
+		}
+
+		ai->rva00262FEB(0);
+		if (pos == 0)
+		{
+			m_64 = true;
+			ai->slot135(m_60);
+			return STATE_CONTINUE;
+		}
+
+		ai->rva00262ACE();
+		m_goalPosition = *pos;
+		const Coord3D *nextPos = (const Coord3D *)ai->m_goalPath->rva00346FA5(m_index + 1);
+		if (nextPos)
+		{
+			Coord2D delta;
+			delta.x = nextPos->x - pos->x;
+			delta.y = nextPos->y - pos->y;
+			Real offset = delta.length();
+			const Coord3D *followingPos = (const Coord3D *)ai->m_goalPath->rva00346FA5(m_index + 2);
+			if (followingPos)
+				offset += 4 * PATHFIND_CELL_SIZE_F;
+			ai->setPathExtraDistance(offset);
+			critterDesyncLog("CritterDesync: setAdjustDestination(FALSE) 47");
+			setAdjustsDestination(false);
+		}
+		else
+		{
+			ai->setPathExtraDistance(0.0f);
+			if (g_00E03745 && theLogicRandomLogFile)
+				fprintf(theLogicRandomLogFile,
+					"CritterDesync: setAdjustDestination(m_adjustFinal=%s && (m_adjustFinalOverride=%s || ai->isDoingGroundMovement()=%s) 48",
+					m_adjustFinal ? "TRUE" : "FALSE", m_adjustFinalOverride ? "TRUE" : "FALSE",
+					ai->isDoingGroundMovement() ? "TRUE" : "FALSE");
+			setAdjustsDestination(m_adjustFinal && (m_adjustFinalOverride || ai->isDoingGroundMovement()));
+			if (getAdjustsDestination())
+			{
+				Coord3D *goal = &m_goalPosition;
+				if (!TheAI->pathfinder()->adjustDestination(getMachineOwner(), *ai->getLocomotorSet(), goal, 0))
+				{
+					if (--m_retryCount > 0)
+					{
+						goal->x = obj->getPosition()->x + goal->x;
+						goal->y = obj->getPosition()->y + goal->y;
+						goal->z = obj->getPosition()->z + goal->z;
+						goal->x *= 0.5f;
+						goal->y *= 0.5f;
+						goal->z *= 0.5f;
+						m_57 = true;
+					}
+					else
+						return STATE_FAILURE;
+				}
+				getMachineOwner()->rva0028ACDC(goal);
+			}
+		}
+	}
+	critterDesyncLog("CritterDesync: ComputePath35");
+	computePath();
+	return STATE_CONTINUE;
+}
+
 // A state's slot 8, ZH State::isAttack.
 class StateAttackView : public VirtualSlots<8>
 {
