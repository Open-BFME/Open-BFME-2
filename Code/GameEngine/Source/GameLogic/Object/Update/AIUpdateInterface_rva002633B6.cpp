// cl: /DNDEBUG /MD
//
// ?rva002633B6@AIUpdateInterface@@QAEXXZ @0x002633B6 (61B).
// AI slot advance: if +0x38 is set delete the +0x30 tracked object through
// its slot15 virtual then its slot0 deleteInstance(0) return-fed to the rowed
// operator delete at 0x0002FD60 then move +0x38 to +0x30. Layout follows the
// rowed AIUpdateInterface machine at +0x30 (rva002630FD). Caller at 0x0029A1E0
// passes the Object+0x258 AI. Sibling of 0x0026331C which moves +0x34.

#include <new>

#include "../../../../Include/GameLogic/Module/AIUpdate.h"
#include "../../../../Include/GameLogic/AIStateMachineClass.h"

void AIUpdateInterface::rva002633B6()
{
	if (m_field038 != 0) {
		if (m_stateMachine != 0) {
			m_stateMachine->halt();
			::delete m_stateMachine;
			m_stateMachine = 0;
		}
		m_stateMachine = m_field038;
		m_field038 = 0;
	}
}
