// cl: /G7 /Ireference/shims/bfmerendobj /arch:SSE /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
//
// DynamicVectorClass<NamedPivotMapClass::WeightInfoStruct>::Add at 0x00196880,
// split out of hanim.cpp because retail built it with /G7 -- it tests the
// allocation flag with a single cmp byte ptr [esi+0xD],0 -- while hanim.cpp's
// HAnimComboDataClass::Set_HAnim only matches without that flag.  The element
// type is private to NamedPivotMapClass, so the template is instantiated the way
// hanim.cpp does it, from NamedPivotMapClass::Add; the element assignment is
// inlined into it.  Both are copied verbatim from hanim.cpp, as are the headers.
#define Matrix4x4 Matrix4
#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
#include "winbase_shim.h"
#include "hanim.h"
#include "assetmgr.h"
#include "htree.h"
#include "motchan.h"
#include "chunkio.h"
#include "w3d_file.h"
#include "wwdebug.h"
#include <string.h>
#include "nstrdup.h"

NamedPivotMapClass::WeightInfoStruct & NamedPivotMapClass::WeightInfoStruct::operator = (WeightInfoStruct const &that)
{	
	if(Name) delete [] Name;
	assert(that.Name != 0);
	Name = nstrdup(that.Name); 
	Weight = that.Weight; 
	return *this; 
}

void NamedPivotMapClass::Add(const char *Name, float Weight)
{
	WeightInfoStruct info;
	info.Name = (char *) Name;
	info.Weight = Weight;
	WeightInfo.Add(info);	
	info.Name = 0;
}
