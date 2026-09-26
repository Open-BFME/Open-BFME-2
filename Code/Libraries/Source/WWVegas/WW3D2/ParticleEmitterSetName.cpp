// cl: /Ireference/shims /Ireference/shims/bfmerendobj /arch:SSE /G7 /DNDEBUG /MD
// ?Set_Name@ParticleEmitterClass@@UAEXPBD@Z @ 0x001A2220 (55B NameString+0x120).
//
// BFME1 donor: reference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2/part_emt.cpp
// (ParticleEmitterClass::Set_Name via free + strdup verbatim logic).
// Evidence: vtable slot 7 offset 0x1C of 0x007D69F8 for ctor 0x001A1070 class;
// retail frees [esi+0x120] via 0x00030830 then strdup via 0x006C4C70;
// twin 46B Def Set_Name at 0x001AF880 proves free plus strdup shape.
// Split TU because part_emt.cpp resolves free and strdup through dllimport
// while retail calls 0x00030830 and 0x006C4C70 directly.
// Import-deflection recipe from ParticleEmitterDefSetName.cpp:
// _CRTIMP defused for <stdlib.h> for direct free and strdup renamed aside
// then redeclared direct as extern C.

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

class ParticleEmitterClass
{
public:
	virtual void Set_Name(const char *pname);

	unsigned char _pad[0x11C];
	char *NameString;
};

void ParticleEmitterClass::Set_Name(const char *pname)
{
	if (NameString) {
		::free(NameString);
		NameString = 0;
	}
	NameString = ::strdup(pname);
}
