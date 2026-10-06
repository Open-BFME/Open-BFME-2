// cl: /DNDEBUG /MD
//
// ?isAircraftThatAdjustsDestination@AIUpdateInterface@@QBE_NXZ, retail 0x00262CBE, 52 bytes.
// ?getTreatAsAircraftForLocoDistToGoal@AIUpdateInterface@@UBE_NXZ, retail 0x00262CF2, 59 bytes.
// ZH donor AIUpdate.cpp aircraft destination and distance-to-goal methods.

struct LocomotorTemplate
{
	char m_pad00[0x74];
	int m_appearance; // +0x74
};

class Locomotor
{
public:
	char m_pad00[4];
	LocomotorTemplate *m_template; // +0x04
};

#define VM10(p) \
	virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3(); virtual void p##4(); \
	virtual void p##5(); virtual void p##6(); virtual void p##7(); virtual void p##8(); virtual void p##9();

class AIUpdateInterfaceBase
{
public:
	VM10(v0_)
	VM10(v1_)
	VM10(v2_)
	VM10(v3_)
	VM10(v4_)
	VM10(v5_)
	VM10(v6_)
	VM10(v7_)
	VM10(v8_)
	virtual bool vslot90() const; // slot 90 -> offset 0x168
	VM10(v9_)
	VM10(v10_)
	VM10(v11_)
	VM10(v12_)
	virtual void v131();
	virtual void v132();
	virtual void v133();
	virtual void v134();
	virtual void v135();
	virtual void v136();
	virtual bool isDoingGroundMovement() const; // slot 137 -> offset 0x224
};

class AIUpdateInterface : public AIUpdateInterfaceBase
{
	char m_pad04[0x168 - 4];
	float m_pathExtraDistance; // +0x168
	char m_pad16C[0x1F0 - 0x16C];
	Locomotor *m_curLocomotor; // +0x1F0; target bodies below (donor: +0x1CC)
public:
	bool isAircraftThatAdjustsDestination() const;
	virtual bool getTreatAsAircraftForLocoDistToGoal() const;
	Locomotor *getCurLocomotor()
	{
		return m_curLocomotor;
	}
};

bool AIUpdateInterface::isAircraftThatAdjustsDestination() const
{
	if (vslot90())
		return true;
	Locomotor *curLocomotor = const_cast<AIUpdateInterface *>(this)->getCurLocomotor();
	if (!curLocomotor)
		return false;
	if (curLocomotor->m_template->m_appearance == 2)
		return true;
	if (curLocomotor->m_template->m_appearance == 3)
		return true;
	return false;
}

bool AIUpdateInterface::getTreatAsAircraftForLocoDistToGoal() const
{
	bool treatAsAircraft = !isDoingGroundMovement();
	if (m_pathExtraDistance > 1.0f)
		treatAsAircraft = true;
	if (m_curLocomotor && m_curLocomotor->m_template->m_appearance == 2)
		treatAsAircraft = true;
	return treatAsAircraft;
}
