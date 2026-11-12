// cl: /Ob0

#include "../../Include/Common/Rva00468520Obj.h"

#include "../../Include/Common/Rva00468520.h"

Rva00468520 *Rva00468520::set(const Rva00468520 *src)
{
	m_00 = src->m_00;
	if (m_00)
		m_00->m_04++;
	m_04 = src->m_04;
	return this;
}
