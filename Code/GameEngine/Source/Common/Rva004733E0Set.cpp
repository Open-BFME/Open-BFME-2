// cl: /Ob0

#include "../../Include/Common/Rva004733E0Obj.h"

class Rva004733E0
{
	int m_00;
	Rva004733E0Obj *m_04;

public:
	Rva004733E0 *set(const Rva004733E0 *src);
};

Rva004733E0 *Rva004733E0::set(const Rva004733E0 *src)
{
	m_00 = src->m_00;
	m_04 = src->m_04;
	if (m_04)
		m_04->m_04++;
	return this;
}
