// cl: /MD
//
// ?clear80@Rva001EAE6FHelper@@QAEPAV1@XZ, retail 0x001EAE6F, 23 bytes.
// Dedicated TU (kept apart from its callers so the shared body is placed
// once; 48 call sites across Contain/Module families).
//
// Shared zeroing helper: memsets 0x80 bytes at this and returns this.
// Semantic identity unproven (pinned opaque); the memset import resolves
// through the existing _memset pin.

#include <string.h>

class Rva001EAE6FHelper
{
public:
	Rva001EAE6FHelper *clear80();

private:
	char m_pad[0x80];
};

// ?clear80@Rva001EAE6FHelper@@QAEPAV1@XZ
Rva001EAE6FHelper *Rva001EAE6FHelper::clear80()
{
	memset(this, 0, 0x80);
	return this;
}
