// cl: /MD /EHsc /O1 /arch:SSE2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Include
//
// Matrix3 rotation overloads from the upstream matrix3.h, emitted
// out of line by taking their address (WWINLINE). The helpers below are
// scaffold, not retail claims.
// Donor: the BFME1 reconstruction of the same header (their bodies 107/121B).
// Z-rotation donor: BFME1 4367fc698990427e26cc1c399989d074d8ee9bbe,
// game/Libraries/Source/WWVegas/WWMath/Matrix3Rotation.cpp and matrix3.h.
// Target 0x003F946D (113B) and 0x003F94DE (135B) have Ghidra extents
// agreeing with their terminal ret and adjacent complete function starts.
// Target stores independently establish the nine-float layout and rows
// [cos -sin 0; sin cos 0; 0 0 1]. The angle overload calls sin/cos first.
// Those semantics support the donor names; original target spelling is unproven.
// /O1 /arch:SSE2 from the matched Rotate_Y siblings reproduces both bodies.

// /O1 preserves retail's double sin/cos calls in the angle overloads, but
// VC7.1 math.h otherwise exports 17B sinf/cosf copies where retail has 7B
// intrinsic wrappers. Keep these inline CRT adapters local to this TU.
// The four rotation bodies and their relocations are unchanged by this scope.
#define inline static inline
#include <math.h>
#undef inline
#include "../../../../../reference/shims/bfme_matrix3_rotation_link/matrix3.h"
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

typedef Matrix3 ( *U4CreateZFromSinCos )( float, float );
typedef Matrix3 ( *U4CreateZFromRadians )( float );

// ?u4CreateZFromSinCos@@YAP6A?AVMatrix3@@MM@ZXZ absent-from-retail
U4CreateZFromSinCos u4CreateZFromSinCos( void )
{
	return &Create_Z_Rotation_Matrix3;
}

// ?u4CreateZFromRadians@@YAP6A?AVMatrix3@@M@ZXZ absent-from-retail
U4CreateZFromRadians u4CreateZFromRadians( void )
{
	return &Create_Z_Rotation_Matrix3;
}
