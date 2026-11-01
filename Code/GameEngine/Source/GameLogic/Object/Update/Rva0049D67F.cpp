// cl: /Oy- /DNDEBUG /MD /GX- /Oi-
// platformsdk
//
// ?rva0049D67F@Rva0049D67F@@QAE_NPBDPA_N1@Z @0x0049D67F 308B
// Single-token Disability bitstring worker. Direct transfer of the landed
// VeterancyLevel sibling ?rva0033AFBB@Rva0033AFBB (308B, same shape) with the
// Disability table. Evidence: DisabilityTypeNames at 0x00DC828C baked in as
// an immediate, the "you may not mix normal and +- ops in bitstring lists"
// INIException filler-throw matches INI_parseBitString32, and the two call
// sites in 0x0049DD83 drive it per token (false return = NONE break).

#include <string.h>
#include <windows.h>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef const char *ConstCharPtr;
typedef const ConstCharPtr *ConstCharPtrArray;

// DisabilityTypeNames: the retail string table at VA 0xdc828c.
const char *DisabilityTypeNames[11] = {
	"DEFAULT",
	"DISABLED_USER_PARALYZED",
	"DISABLED_EMP",
	"DISABLED_HELD",
	"DISABLED_PARALYZED",
	"DISABLED_UNMANNED",
	"DISABLED_UNDERPOWERED",
	"DISABLED_FREEFALL",
	"DISABLED_TEMPORARILY_BUSY",
	"DISABLED_SCRIPT_DISABLED",
	"DISABLED_SCRIPT_UNDERPOWERED",
};

#include "../../../../Include/Common/INI/FieldParse.h"

class Rva0049D67F
{
public:
	Bool rva0049D67F(const char *token, Bool *foundNormal, Bool *foundAddOrSub);

private:
	unsigned m_words[1];
};

extern "C" int rva002bcab_scanIndex(const char *token, ConstCharPtrArray nameList, Bool *found, Bool doThrow);

Bool Rva0049D67F::rva0049D67F(const char *token, Bool *foundNormal, Bool *foundAddOrSub)
{
	Bool found;

	if (_strcmpi(token, "NONE") == 0) {
		if (*foundNormal || *foundAddOrSub) {
			throw INIException(2, "you may not mix normal and +- ops in bitstring lists");
		}
		memset(m_words, 0, sizeof(m_words));
		return false;
	}

	if (token[0] == '+') {
		if (*foundNormal) {
			throw INIException(2, "you may not mix normal and +- ops in bitstring lists");
		}
		UnsignedInt bitIndex = rva002bcab_scanIndex(token + 1, DisabilityTypeNames, &found, true);
		m_words[bitIndex >> 5] |= (1u << (bitIndex & 31));
		*foundAddOrSub = true;
	} else if (token[0] == '-') {
		if (*foundNormal) {
			throw INIException(2, "you may not mix normal and +- ops in bitstring lists");
		}
		UnsignedInt bitIndex = rva002bcab_scanIndex(token + 1, DisabilityTypeNames, &found, true);
		m_words[bitIndex >> 5] &= ~(1u << (bitIndex & 31));
		*foundAddOrSub = true;
	} else {
		if (*foundAddOrSub) {
			throw INIException(2, "you may not mix normal and +- ops in bitstring lists");
		}

		if (!*foundNormal)
			memset(m_words, 0, sizeof(m_words));

		UnsignedInt bitIndex = rva002bcab_scanIndex(token, DisabilityTypeNames, &found, true);
		m_words[bitIndex >> 5] |= (1u << (bitIndex & 31));
		*foundNormal = true;
	}
	return true;
}
