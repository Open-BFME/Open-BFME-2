// cl: /Ob0

#include "../../Include/Common/Rva004733E0Obj.h"

#include "../../Include/Common/Rva004733E0.h"

Rva004733E0 *Rva004733E0::set(const Rva004733E0 *src)
{
	m_00 = src->m_00;
	m_04 = src->m_04;
	if (m_04)
		m_04->m_04++;
	return this;
}
