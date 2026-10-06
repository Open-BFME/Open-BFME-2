// cl: /Ireference/shims /Ireference/shims/bfmerendobj /DNDEBUG /MD
// ParticleEmitterDefClass::Set_Name + Set_User_String at retail 0x001AF880
// (46B, m_pName+4) and 0x001AF850 (46B, m_pUserString+8).
//
// BFME1 donor: reference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2/part_ldr.cpp
// (Set_Name / Set_User_String via SAFE_FREE + ::_strdup, verbatim logic).
// Split TU because the shared part_ldr.cpp TU resolves free/strdup through
// dllimport (FF15) while retail calls 0x00030830 / 0x006C4C70 directly (E8).
// Import-deflection recipe from Code/Libraries/Source/WWVegas/WW3D2/hlod.cpp:
// _CRTIMP defused for <stdlib.h> (direct free), strdup renamed aside then
// redeclared direct (extern "C").

// Rename the dllimport strdup declaration out of the way before any header
// can declare it.
#define strdup __bfme_strdup_dllimport

#include <sweep/winbase_shim.h>

#include <string.h>
#define _CRTIMP
#include <stdlib.h>
#include "winbase_shim.h"

// Every header that declares strdup has now had its declaration renamed aside;
// this is the spelling the unit calls to reach 0x006C4C70 directly.
#undef strdup
extern "C" char * __cdecl strdup(const char *);

class ParticleEmitterDefClass
{
public:
	virtual void Set_Name(const char *pname);
	virtual void Set_User_String(const char *pstring);

	char *m_pName;
	char *m_pUserString;
};

// ?Set_Name@ParticleEmitterDefClass@@UAEXPBD@Z
void ParticleEmitterDefClass::Set_Name(const char *pname)
{
	if (m_pName) {
		::free(m_pName);
		m_pName = 0;
	}
	m_pName = ::strdup(pname);
}

// ?Set_User_String@ParticleEmitterDefClass@@UAEXPBD@Z
void ParticleEmitterDefClass::Set_User_String(const char *pstring)
{
	if (m_pUserString) {
		::free(m_pUserString);
		m_pUserString = 0;
	}
	m_pUserString = ::strdup(pstring);
}
