// cl: /G7 /Ireference/shims/bfmerendobj /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
//
// Null3DObjClass name ctor (0x00180EB0 / 51B), copy ctor (0x00180EF0 / 56B)
// and operator= (0x00180F30 / 49B). Dedicated TU so nullrobj.cpp Clone keeps
// its inc-eax strcpy; /G7 emits add eax,1.

#include "rendobj.h"
#include "nullrobj.h"
#include <string.h>

Null3DObjClass::Null3DObjClass(const char * name)
{
	strcpy(Name, name);
}

Null3DObjClass::Null3DObjClass(const Null3DObjClass & src)
{
	strcpy(Name, src.Name);
}

Null3DObjClass & Null3DObjClass::operator = (const Null3DObjClass & that)
{
	strcpy(Name, that.Name);
	RenderObjClass::operator = (that);
	return *this;
}
