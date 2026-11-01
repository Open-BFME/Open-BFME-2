// cl: /DNDEBUG /MD
// Overridable restores its table at VA 0x00BDDC48 before clearing its chain.
// The next override at +4 is destroyed through slot 0 and globally deallocated.

#include "../../Include/Common/Overridable.h"

Overridable::~Overridable()
{
	if (m_nextOverride)
		::delete m_nextOverride;
	m_nextOverride = 0;
}
