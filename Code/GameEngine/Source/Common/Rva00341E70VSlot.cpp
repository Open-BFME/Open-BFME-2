// cl: /MD /EHsc
// ?update@AIGuardRetaliateState@@UAEHXZ @0x00341F5D 60B: AIGuardRetaliateState virtual slot 6 (offset 0x18) of vtable 0x008117F0.
// Evidence: vslot packet; class of ??1AIGuardRetaliateState@@UAE@XZ; calls rowed ?getGoalObject@TurretStateMachine@@QAEPAVObject@@XZ twice plus vtable slots 0x38 (setGoalObject) and 0x10 tail.
class Object;
class TurretStateMachine
{
public:
	Object *getGoalObject();
	virtual void _rsvd00();
	virtual void _rsvd01();
	virtual void _rsvd02();
	virtual void _rsvd03();
	virtual int _rsvd04();
	virtual void _rsvd05();
	virtual void _rsvd06();
	virtual void _rsvd07();
	virtual void _rsvd08();
	virtual void _rsvd09();
	virtual void _rsvd10();
	virtual void _rsvd11();
	virtual void _rsvd12();
	virtual void _rsvd13();
	virtual void setGoalObject(Object *o);
};
namespace FXParticleSystem {
class WindModuleInfo
{
public:
	virtual ~WindModuleInfo();
	int m_id;
	int m_successStateID;
	int m_failureStateID;
	void *m_transitionsFirst;
	void *m_transitionsLast;
	TurretStateMachine *m_machine;
	bool m_tail1C;
	char m_pad1D[0x20 - 0x1D];
};
}
class AIGuardRetaliateState : public FXParticleSystem::WindModuleInfo
{
public:
	virtual void _s01();
	virtual void _s02();
	virtual void _s03();
	virtual void _s04();
	virtual void _s05();
	virtual int update();
private:
	TurretStateMachine *m_20;
};
int AIGuardRetaliateState::update()
{
	if (!m_20)
		return -2;
	Object *goal = m_machine->getGoalObject();
	if (goal) {
		Object *goal2 = m_20->getGoalObject();
		if (goal != goal2)
			m_20->setGoalObject(goal);
	}
	return m_20->_rsvd04();
}
