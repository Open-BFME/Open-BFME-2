// cl: /DNDEBUG /MD /EHsc
// Xfer::operator==(Version &), ported from Open-BFME-1's
// XferVersionTransfer.cpp. BFME 2 inserts one virtual ahead of the raw
// transfer, so it is slot +0x98 here (BFME 1: +0x94); the version checks and
// their exceptions are unchanged.
//
// XferException's (tag, format, ...) constructor is the formatter the ledger
// holds as _bfmeFormatText at 0x0060C36E: a cdecl varargs member that stores
// the tag and a heap copy of the formatted text.

#include "../../../Include/Common/XferException.h"

#include "XferVectorTypes.h"
#include "../../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	unsigned char data[2];	// [0] earliest supported, [1] current
};

Xfer &Xfer::operator==(Xfer::Version &v)
{
	if (IsStoring())
	{
		XferData(('v' << 16) | ('e' << 8) | 'r', &v.data[1], 1);
	}
	else
	{
		unsigned char previousVersion;
		unsigned char loadedVersion;
		unsigned char earliestVersion;
		{
			previousVersion = v.data[1];
			XferData(('v' << 16) | ('e' << 8) | 'r', &v.data[1], 1);
			loadedVersion = v.data[1];
			earliestVersion = v.data[0];
		}
		if (loadedVersion < earliestVersion)
			throw XferException(2, "Found version %i but the earliest supported is %i",
				loadedVersion, earliestVersion);
		if (loadedVersion > previousVersion)
			throw XferException(3, "Don't know how to load version %i (most recent is %i)",
				loadedVersion, previousVersion);
	}
	return *this;
}
