// cl: /MD
//
// ?isFactionStructure@Object@@QBE_NXZ @0x0028D491 (51B).
// Object KindOf gate: builds a 28-byte (7-word) BitFlags<69> mask on the
// stack via CRT memset then ORs bits 62+63 (byte 7 0xC0), 64+65 (dword 2
// value 3) and 135 (byte 16 0x80), then returns Thing::isAnyKindOf(mask).
// Retail shape is push 0x1C plus lea plus push 0 plus call to the rowed
// memset thunk 0x6291AE, three ORs, add esp 0xC, lea plus push plus call to
// the rowed Thing::isAnyKindOf at 0x30ADC7. Callers at 0x0028D4D0 plus
// 0x00293874 plus 0x0040601A plus 0x0041C4A3 plus 0x0041C566 plus
// 0x004C014C. No donor name claimed, so the name keeps the address token
// with the proven Object owner (Object derives Thing, same +0x4 template
// slot other Object TUs document).

#include <string.h>

template<int N>
class BitFlags
{
public:
	unsigned int m_words[7];
};


#include "../../Common/Thing/thing.h"
#include "../../../Include/Common/ThingTemplate.h"

class Object : public Thing
{
public:
	bool isFactionStructure() const;
	int isNonFactionStructure() const;
};

bool Object::isFactionStructure() const
{
	BitFlags<69> mask;
	memset(&mask, 0, 0x1C);
	((unsigned char *)&mask)[7] |= 0xC0;
	((unsigned int *)&mask)[2] |= 3;
	((unsigned char *)&mask)[16] |= 0x80;
	return isAnyKindOf(mask);
}

// ?isNonFactionStructure@Object@@QBEHXZ, retail 0x0028D4C4 (28B): template flag 0x80 at
// +0x108 gates the KindOf helper above; a false helper result reports true.
int Object::isNonFactionStructure() const
{
	if ((m_template->m_kindof[0] & 0x80) != 0)
	{
		if (!isFactionStructure())
		{
			return 1;
		}
	}
	return 0;
}
