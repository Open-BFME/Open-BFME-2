// cl: /MD
// ?rva0037F4EA@Rva0037F4EA@@QAEPAV1@H@Z retail 0x0037F4EA 48B
// Evidence: callers 0x0037F90F 0x0037F985 pass dword from +0x12c; zeroes six floats plus bool; second instance at +0x20
#include "../GameLogic/System/ArmyPlacerRecords.h"

Rva0037F4EA *Rva0037F4EA::rva0037F4EA(int v)
{
	m_00 = v;
	m_04 = 0.0f;
	m_08 = 0.0f;
	m_0c = 0.0f;
	m_10 = 0.0f;
	m_14 = 0.0f;
	m_18 = 0.0f;
	m_1c = false;
	return this;
}

// ?rva0037F8AC@Rva0037F8AC@@QAEXPAX@Z
// Native Ghidra extent 0x0037F8AC..0x0037F90F; RET 4. Each record's
// validity byte guards its update. Valid records supply the two planar
// coordinates at +0x10/+0x14 for the cached squared distance.
void Rva0037F8AC::rva0037F8AC(void *context)
{
	if (!m_00.m_1c)
		m_00.rva0037F87A(context);
	if (!m_20.m_1c)
		m_20.rva0037F87A(context);
	if (m_00.m_1c && m_20.m_1c)
	{
		float dx = m_00.m_10 - m_20.m_10;
		float dy = m_00.m_14 - m_20.m_14;
		m_40 = dx * dx + dy * dy;
		m_44 = true;
	}
}

// ?rva0037F90F@Rva0037F8AC@@QAEPAV1@PAXPAURva0037F90FInput@@1@Z
// Native Ghidra extent 0x0037F90F..0x0037F950; RET 12. Two rowed
// initializers use +0x12c, followed by a same-receiver call to 0x0037F8AC.
Rva0037F8AC *Rva0037F8AC::rva0037F90F(void *context,
	Rva0037F90FInput *first, Rva0037F90FInput *second)
{
	m_00.rva0037F4EA(first->field_12c);
	m_20.rva0037F4EA(second->field_12c);
	m_40 = 0.0f;
	m_44 = false;
	rva0037F8AC(context);
	return this;
}

// ?rva0037F950@Rva0037F8AC@@QAEPAV1@PAXPBVRva0037F51A@@1@Z
// Native Ghidra extent 0x0037F950..0x0037F985; RET 12. Copies the two
// records through the verified provider, then clears and refreshes the
// cached distance exactly as the adjacent identifier initializer does.
Rva0037F8AC *Rva0037F8AC::rva0037F950(void *context,
	const Rva0037F51A *first, const Rva0037F51A *second)
{
	reinterpret_cast<Rva0037F51A *>(&m_00)->rva0037F51A(*first);
	reinterpret_cast<Rva0037F51A *>(&m_20)->rva0037F51A(*second);
	m_40 = 0.0f;
	m_44 = false;
	rva0037F8AC(context);
	return this;
}
