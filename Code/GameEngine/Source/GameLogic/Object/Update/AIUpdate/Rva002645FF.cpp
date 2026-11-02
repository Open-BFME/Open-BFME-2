// cl: /DNDEBUG /MD
// ?rva002645FF@Rva002645FF@@QAE_NXZ retail 0x002645FF 87B.
// AIUpdate slot 0x1B8 (110) shared by Siege/Transport/Wander/HordeWorker vtables.
// Evidence: vtable slot 110 of 0x00847B98 0x0084D330 0x008505F8 0x008508C8 0x00853AA8 0x00853D30;
// callers 0x003681E8 0x0048E643 0x0048F46D tail-jump here; callee rowed 0x0004E536 testStatus.
// ?rva00264F3D@Rva00264F3D@@QAEHXZ retail 0x00264F3D 33B.
// Neighbour of 0x002645FF same TU same flags. Returns +0x38 field or 0 with 0x0A status gate.
// Evidence: caller 0x0034BDBD; callee rowed 0x0004E536 testStatus.
// ?rva00264E93@Rva00264E93@@QAEPAXXZ retail 0x00264E93 35B.
// Neighbour same TU same flags. Status 0x16 plus +0x40 gate returns +0x30+0x24 or 0.
// Evidence: callers 0x004789FB 0x00478A80 0x00478B42; callee rowed 0x0004E536 testStatus.
#include "../../../../../Include/GameLogic/Module/AIUpdate.h"
#include "../../../../../Include/Common/StateMachineClass.h"

enum ObjectStatusTypes;

class Mid
{
public:
	char m_pad00[0x258];
	AIUpdateInterface *m_slot; // +0x258
};

class Object
{
public:
	bool testStatus(ObjectStatusTypes bit) const;
	char m_pad00[0x274];
	Mid *m_mid; // +0x274
	char m_pad278[0x438 - 0x274 - 4];
	unsigned char m_flag438; // +0x438
};

class Rva002645FF
{
public:
	bool rva002645FF();
	char m_pad00[8];
	Object *m_object; // +8
	char m_pad0C[0x30 - 0x0C];
	StateMachine *m_machine; // +0x30
};

class Inner00264F3D
{
public:
	char m_pad00[0x38];
	int m_val38; // +0x38
	unsigned char m_flag3C; // +0x3C
};

class Rva00264F3D
{
public:
	int rva00264F3D();
	char m_pad00[4];
	Inner00264F3D *m_inner; // +4
	Object *m_object; // +8
};

class Rva00264E93
{
public:
	void *rva00264E93();
	char m_pad00[8];
	Object *m_object; // +8
	char m_pad0C[0x30 - 0x0C];
	char *m_ptr30; // +0x30
	char m_pad34[0x40 - 0x34];
	int m_flag40; // +0x40
};

bool Rva002645FF::rva002645FF()
{
	Object *obj = m_object;
	if ((obj->m_flag438 & 1) != 0)
		return true;
	if (obj->testStatus((ObjectStatusTypes)0x26)) {
		Mid *mid = obj->m_mid;
		if (mid != 0) {
			AIUpdateInterface *slot = mid->m_slot;
			if (slot != 0) {
				if (slot->isIdle())
					return true;
			}
		}
	}
	StateMachine *sm = m_machine;
	if (sm->m_currentState != 0)
		// Existing canonical slot8 spelling; this does not name the enclosing placeholder.
		return sm->m_currentState->isAttack();
	return true;
}

int Rva00264F3D::rva00264F3D()
{
	Inner00264F3D *inner = m_inner;
	if (inner->m_flag3C != 0) {
		Object *obj = m_object;
		if (!obj->testStatus((ObjectStatusTypes)0x0A))
			return 0;
	}
	return inner->m_val38;
}

void *Rva00264E93::rva00264E93()
{
	if (m_object->testStatus((ObjectStatusTypes)0x16)) {
		if (m_flag40 == 0)
			return m_ptr30 + 0x24;
	}
	return 0;
}
