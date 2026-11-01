// cl: /Oy- /DNDEBUG /MD /GX- /Oi-
// platformsdk
//
// ?rva00255D58@Rva00255D58@@QAE_NPBDPA_N1@Z @0x00255D58 308B
// Single-token KindOf bitstring worker over TheKindOfBitNames at 0x00DBBE18.
// Evidence: 0x1c memset (7 words), "NONE" + "you may not mix normal and +- ops
// in bitstring lists" immediates, three rva002bcab_scanIndex calls with the
// KindOf table, two call sites in 0x00256499 driving it per token (false = NONE break).
// Direct transfer of the landed VeterancyLevel sibling ?rva0033AFBB@Rva0033AFBB (308B, same shape).

#include <string.h>
#include <windows.h>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef const char *ConstCharPtr;
typedef const ConstCharPtr *ConstCharPtrArray;

extern const char *TheKindOfBitNames[]; ///< retail [0x00DBBE18]

#include "../../../Include/Common/INI/FieldParse.h"

class Rva00255D58
{
public:
	Bool rva00255D58(const char *token, Bool *foundNormal, Bool *foundAddOrSub);

private:
	unsigned m_words[7];
};

extern "C" int rva002bcab_scanIndex(const char *token, ConstCharPtrArray nameList, Bool *found, Bool doThrow);

Bool Rva00255D58::rva00255D58(const char *token, Bool *foundNormal, Bool *foundAddOrSub)
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
		UnsignedInt bitIndex = rva002bcab_scanIndex(token + 1, TheKindOfBitNames, &found, true);
		m_words[bitIndex >> 5] |= (1u << (bitIndex & 31));
		*foundAddOrSub = true;
	} else if (token[0] == '-') {
		if (*foundNormal) {
			throw INIException(2, "you may not mix normal and +- ops in bitstring lists");
		}
		UnsignedInt bitIndex = rva002bcab_scanIndex(token + 1, TheKindOfBitNames, &found, true);
		m_words[bitIndex >> 5] &= ~(1u << (bitIndex & 31));
		*foundAddOrSub = true;
	} else {
		if (*foundAddOrSub) {
			throw INIException(2, "you may not mix normal and +- ops in bitstring lists");
		}

		if (!*foundNormal)
			memset(m_words, 0, sizeof(m_words));

		UnsignedInt bitIndex = rva002bcab_scanIndex(token, TheKindOfBitNames, &found, true);
		m_words[bitIndex >> 5] |= (1u << (bitIndex & 31));
		*foundNormal = true;
	}
	return true;
}
