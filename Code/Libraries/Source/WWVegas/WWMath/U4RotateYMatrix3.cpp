// cl: /MD /EHsc /O1 /arch:SSE2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Include
//
// The two `Matrix3::Rotate_Y` overloads from the upstream matrix3.h, emitted
// out of line by taking their address (WWINLINE). The helpers below are
// scaffold, not retail claims.
// Donor: the BFME1 reconstruction of the same header (their bodies 107/121B).

#include "matrix3.h"

typedef void ( Matrix3::*U4RotYFromRadians )( float );
typedef void ( Matrix3::*U4RotYFromSinCos )( float, float );

// ?u4RotYFromRadians@@YAP8Matrix3@@AEXM@ZXZ absent-from-retail
U4RotYFromRadians u4RotYFromRadians( void )
{
	return static_cast<U4RotYFromRadians>( &Matrix3::Rotate_Y );
}

// ?u4RotYFromSinCos@@YAP8Matrix3@@AEXMM@ZXZ absent-from-retail
U4RotYFromSinCos u4RotYFromSinCos( void )
{
	return static_cast<U4RotYFromSinCos>( &Matrix3::Rotate_Y );
}
