// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// platformsdk
// stlport
//
// SpecialPowerStore lookups, ported from Zero Hour's GameEngine/Source/Common/
// RTS/SpecialPower.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference):
//  - findSpecialPowerTemplatePrivate, retail 0x003B11D2 (114 bytes).
//  - findSpecialPowerTemplateByID, retail 0x003B0FD0 (71 bytes).
// BFME 2 layout (target evidence): the template vector at SpecialPowerStore
// +0x0C; the templates are Overridables (friend_getFinalOverride 0x00288609)
// with the name at +0x10 and the id at +0x14 of the final override.
#include <vector>
#include "ascii_string.h"

typedef unsigned int UnsignedInt;
typedef int Int;
#include <windows.h>

#include "../../../Include/Common/Overridable.h"
#include "../../../Include/Common/SpecialPower.h"

// Retail inlines Zero Hour's override walks here: both bodies stay visible, and
// their emitted copies match the 24-byte const (0x00288609) and 14-byte mutable
// (0x001E35DF) owners.
inline Overridable *Overridable::friend_getFinalOverride()
{
	if (m_nextOverride)
		return m_nextOverride->friend_getFinalOverride();
	return this;
}
inline const Overridable *Overridable::friend_getFinalOverride() const
{
	if (m_nextOverride)
		return m_nextOverride->friend_getFinalOverride();
	return this;
}

class SpecialPowerStore
{
public:
	const SpecialPowerTemplate *findSpecialPowerTemplateByID( UnsignedInt id );
protected:
	SpecialPowerTemplate *findSpecialPowerTemplatePrivate( AsciiString name );
private:
	unsigned char m_pad00[0x0C];
	_STL::vector<SpecialPowerTemplate *> m_specialPowerTemplates; // +0x0C
};

// BFME1 d6db6bfa4f: Common/RTS/SpecialPower.cpp owns this null global.
// Target callers and the data ledger place its four-byte pointer at VA
// 0x00E02D4C, in the native .data section's zero-filled tail.
SpecialPowerStore *TheSpecialPowerStore = 0;

//-------------------------------------------------------------------------------------------------
SpecialPowerTemplate* SpecialPowerStore::findSpecialPowerTemplatePrivate( AsciiString name )
{

	// search the template list for matching name
	for( Int i = 0; i < m_specialPowerTemplates.size(); ++i )
		if( m_specialPowerTemplates[ i ]->getName() == name )
			return m_specialPowerTemplates[ i ];

	return NULL;  // not found

}

// Native 003B0FD0..003B1017 and WB C0F050 retain the donor's indexed loop.
// Both override bodies must remain visible: the compiler then emits retail's
// EBX pointer induction, EBP index and EDI cached begin. Their emitted copies
// independently match the existing 24-byte const and 14-byte mutable owners.
const SpecialPowerTemplate *SpecialPowerStore::findSpecialPowerTemplateByID( UnsignedInt id )
{
	for (Int i = 0; i < m_specialPowerTemplates.size(); ++i)
		if (m_specialPowerTemplates[i]->getID() == id)
			return m_specialPowerTemplates[i];

	return NULL;
}
