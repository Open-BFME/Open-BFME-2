// cl: /DNDEBUG /MD
// Retail leaf helpers use the shared DeployStyleAIUpdate layout.
#include "../../../../../Include/GameLogic/Module/DeployStyleAIUpdateClass.h"

// ?Rva0048E634Reset@DeployStyleAIUpdate@@QAEXXZ @0x48E634
void DeployStyleAIUpdate::Rva0048E634Reset()
{
	m_member3E4.m_000 |= -1;
	m_4A9 = false;
}

// ?rva0048E6D2@DeployStyleAIUpdate@@QAEXXZ @0x0048E6D2 38B DeployStyle file-unit leaf over +0x4B4 +0x4D5 +0x4D6; caller 0x004AE611 passes embedded DeployStyle at +0x258
void DeployStyleAIUpdate::rva0048E6D2()
{
	m_4D5 = false;
	if (m_4B4 == 0 || m_4B4 == 3)
		m_4D6 = false;
	else
		m_4D6 = true;
}

// ?rva0048E6AB@DeployStyleAIUpdate@@QAEXXZ @0x0048E6AB 39B mirror leaf over +0x4B4 +0x4D6 +0x4D5; caller 0x004AE76A passes embedded DeployStyle
void DeployStyleAIUpdate::rva0048E6AB()
{
	m_4D6 = false;
	if (m_4B4 == 2 || m_4B4 == 1)
		m_4D5 = false;
	else
		m_4D5 = true;
}
