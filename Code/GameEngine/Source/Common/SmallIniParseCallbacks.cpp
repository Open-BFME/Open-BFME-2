// cl: /DNDEBUG /MD /EHsc
// Six small INI parse callbacks (trimmed to the placed
// GeometryRotationAnchorOffset body; the other seven are declared-only here).

#include "../../Include/Common/INI/INI.h"

// ?parseGeometryRotationAnchorOffset@@YAXPAVINI@@PAX1PBX@Z
void parseGeometryRotationAnchorOffset( INI *ini, void *instance, void *store, const void *userData )
{
	INI::parseCoord2D( ini, instance, (char *)store + 8, userData );
}

void parseOnlyIfEnemyThreatAbove( INI *ini, void *, void *store, const void * );
void parseOnlyIfEnemyThreatBelow( INI *ini, void *, void *store, const void * );
void parseRva00427670Type( INI *ini, void *, void *store, const void * );
void parseCanMoveBackwards( INI *ini, void *, void *store, const void * );
void parseExtraFriction( INI *ini, void *, void *store, const void * );
void parsePreferredAgainst( INI *ini, void *instance, void *, const void * );
void parseOnlyAgainst( INI *ini, void *instance, void *, const void * );
