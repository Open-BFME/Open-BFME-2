// cl: /DNDEBUG /MD
// ?rva00525119@Rva00525119@@QAEHPAV1@@Z, retail 0x00525119 29B leaf via float compare.
// Returns other->inner->+0x10 > this->inner->+0x10; SSE comiss shape.
// Evidence: no callees; callers 0x00525481 0x00525976; prev 0x0052510C same flags plus SSE.
#include "Rva00525119.h"

int Rva00525119::rva00525119(Rva00525119 *other)
{
	if (m_ptr->m_10 < other->m_ptr->m_10)
		return 1;
	return 0;
}
