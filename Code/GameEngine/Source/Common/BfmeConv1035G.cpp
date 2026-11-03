// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
//
// retail 0x00131C40, 35 bytes. Donor game/GameEngine/Source/Common/BfmeConv1035.cpp
// recompiled /Os emits this body byte-identically on unclaimed .text. Dedicated
// TU holding the preamble and this one body; the donor's other five bodies
// (bfmeGo1035A, bfmeGo1035B, bfmeGo1035C, bfmeGo1035E and bfmeGo1035F) are
// omitted -- bfmeGo1035C is recovered in its own TU.
class BfmeG1035;

// The name is a StringClass (wwstring.cpp): the empty test reads its private
// sentinel StringClass::m_NullChar (VA 0xE08C18) and the fix-up is the cdecl
// StringClass::Format (0x00610DD0), called with the "dyntex_%08x" literal
// (VA 0xBD2620) and this.
#include "../../../Libraries/Source/WWVegas/WWLib/StringClassData.h"

class BfmeG1035
{
public:
	char *bfmeGo1035G(void);

	char m_bfmePad[0x18];
	char *m_bfmeName;
};

char *BfmeG1035::bfmeGo1035G(void)
{
	if (*m_bfmeName == StringClass::m_NullChar)
		reinterpret_cast<StringClass *>(&m_bfmeName)->Format("dyntex_%08x", this);

	return m_bfmeName;
}
