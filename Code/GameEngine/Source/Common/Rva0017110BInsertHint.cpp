// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
//
// ?rva0017110B@Rva00170BFF@@QAE?AURva00170EFEIter@@U2@ABVRva00170999@@@Z
// Candidate 0x0017110B, 29B. Forwards hint-insert (position, value) to the
// rowed worker 0x00170EFE on the same Rva00170BFF tree; caller 0x00171128
// passes this through in ecx with hidden return pointer. Boundary from int3
// padding; byte verification decides.
#include <map>

class Rva00170999;

#include "../../Include/Common/Rva00170EFENode.h"

struct Rva00170EFEIter
{
	Rva00170EFENode *node;
	Rva00170EFEIter(Rva00170EFENode *p) : node(p) {}
	Rva00170EFEIter(const Rva00170EFEIter &other) : node(other.node) {}
};

#include "../../Include/Common/Rva00170BFF.h"

Rva00170EFEIter Rva00170BFF::rva0017110B(Rva00170EFEIter position,
	const Rva00170999 &value)
{
	return rva00170EFE(position, value);
}
