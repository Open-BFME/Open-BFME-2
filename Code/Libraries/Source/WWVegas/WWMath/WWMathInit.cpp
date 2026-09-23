// cl: /G7 /arch:SSE /Ireference/shims/bfmecamera /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath
//
// WWMath::Init at 0x00711AD0 and WWMath::Fast_Acos at 0x007185C0, from BFME 1's
// WWMath/wwmath.cpp built with BFME 2's /G7 /arch:SSE. WWLib/wwmath.cpp keeps
// Random_Float.
#include "wwmath.h"
#include "wwhack.h"
#include <stdlib.h>
#include "wwdebug.h"
#include "wwprofile.h"

// TODO: convert to use loouptablemanager...
float _FastAcosTable[ARC_TABLE_SIZE];
float _FastAsinTable[ARC_TABLE_SIZE];
float _FastSinTable[SIN_TABLE_SIZE];
float _FastInvSinTable[SIN_TABLE_SIZE];

void		WWMath::Init(void)
{
	// BFME drift: the retail build's WWMath::Init has no LookupTableMgrClass::Init()
	// call (present in the Generals reference); omitting it matches the shipped bytes.

	for (int a=0;a<ARC_TABLE_SIZE;++a) {
		float cv=float(a-ARC_TABLE_SIZE/2)*(1.0f/(ARC_TABLE_SIZE/2));
		_FastAcosTable[a]=acos(cv);
		_FastAsinTable[a]=asin(cv);
	}

	for (a=0;a<SIN_TABLE_SIZE;++a) {
		float cv= (float)a * 2.0f * WWMATH_PI / SIN_TABLE_SIZE; //float(a-SIN_TABLE_SIZE/2)*(1.0f/(SIN_TABLE_SIZE/2));
		_FastSinTable[a]=sin(cv);

		if (a>0) {
			_FastInvSinTable[a]=1.0f/_FastSinTable[a];
		} else {
			_FastInvSinTable[a]=WWMATH_FLOAT_MAX;
		}
	}
}


/*
** Fast_Acos is declared inline in wwmath.h, but retail carries it out of line.
** Taking its address emits that COMDAT body here; the table itself is not in
** the shipped binary.
*/
float (* _WWMath_Forced_Fast_Acos[])(float) = {
	&WWMath::Fast_Acos,
};
