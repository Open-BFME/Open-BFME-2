// cl: /DNDEBUG /MD /EHsc
// ?rva0028B38D@Object@@QBEHXZ, retail 0x0028B38D, 25 bytes.
// Object AI query: if the AI at +0x258 is present returns its slot 0x168
// byte result zero-extended, else 0. Evidence: AI at +0x258 per
// Rva004884B7Check and Object_isAbleToAttack, slot 0x168 from retail call,
// callers at 0x0034B5F8 0x0036FEC0 0x003C832A test al. Int return proven by
// byte-exact movzx shape (bool outer tail-jumps to 21B).
#include "../../../Include/GameLogic/Module/AIUpdate.h"

#include "object.h"

int Object::rva0028B38D() const
{
	AIUpdateInterface *ai = m_ai;
	if (ai != 0)
		return ai->vslot090();
	return 0;
}
