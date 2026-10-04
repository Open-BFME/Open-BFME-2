// ?findSpecialPowerTemplateByID@SpecialPowerStore@@QAEPBVSpecialPowerTemplate@@I@Z
// partial score=0.8 date=2026-10-04
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// SpecialPowerStore lookups, ported from Zero Hour's GameEngine/Source/Common/
// RTS/SpecialPower.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference):
//  - findSpecialPowerTemplateByID, retail 0x003B0FD0 (71 bytes);
//  - findSpecialPowerTemplatePrivate, retail 0x003B11D2 (114 bytes).
// BFME 2 layout (target evidence): the template vector at SpecialPowerStore
// +0x0C; the templates are Overridables (friend_getFinalOverride 0x00288609)
// with the name at +0x10 and the id at +0x14 of the final override.
#include <vector>
#include "ascii_string.h"

typedef unsigned int UnsignedInt;
typedef int Int;
#define NULL 0

class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;
};

class SpecialPowerTemplate : public Overridable
{
public:
	const AsciiString &getName() const { return getFO()->m_name; }
	UnsignedInt getID() const { return getFO()->m_id; }
private:
	const SpecialPowerTemplate *getFO() const { return (const SpecialPowerTemplate *)friend_getFinalOverride(); }
	unsigned char m_pad00[0x10];
	AsciiString m_name; // +0x10
	UnsignedInt m_id; // +0x14
};

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

//-------------------------------------------------------------------------------------------------
SpecialPowerTemplate* SpecialPowerStore::findSpecialPowerTemplatePrivate( AsciiString name )
{

	// search the template list for matching name
	for( Int i = 0; i < m_specialPowerTemplates.size(); ++i )
		if( m_specialPowerTemplates[ i ]->getName() == name )
			return m_specialPowerTemplates[ i ];

	return NULL;  // not found

}

//-------------------------------------------------------------------------------------------------
/** Find a special power template given unique ID */
//-------------------------------------------------------------------------------------------------
const SpecialPowerTemplate *SpecialPowerStore::findSpecialPowerTemplateByID( UnsignedInt id )
{

	// search the template list for matching name
	for( Int i = 0; i < m_specialPowerTemplates.size(); ++i )
		if( m_specialPowerTemplates[ i ]->getID() == id )
			return m_specialPowerTemplates[ i ];

	return NULL;  // not found

}
