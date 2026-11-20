// cl: /DNDEBUG /MD /EHsc
// Six small INI parse callbacks (trimmed to the placed
// GeometryRotationAnchorOffset body; the other seven are declared-only here).

#include "../../Include/Common/INI/INI.h"

// ?parseGeometryRotationAnchorOffset@@YAXPAVINI@@PAX1PBX@Z
void parseGeometryRotationAnchorOffset( INI *ini, void *instance, void *store, const void *userData )
{
	INI::parseCoord2D( ini, instance, (char *)store + 8, userData );
}
