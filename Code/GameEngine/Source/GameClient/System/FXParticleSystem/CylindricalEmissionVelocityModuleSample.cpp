// cl: /O1 /DNDEBUG /MD
// ?getVelocity@CylindricalEmissionVelocityModule@FXParticleSystem@@QAE?AUCoord3D@2@HH@Z
// retail 0x0055EB84, 118 bytes.
//
// Ported from the Open-BFME-1 donor
// game/GameEngine/Source/GameClient/System/FXParticleSystem/CylindricalEmissionVelocityModuleSample.cpp
// (reference/open-bfme-1 @ 6583b3c1). Compiled at /O1, the donor body is a
// unique masked placement on unclaimed .text. Target facts: the two random
// variables at +0x1C and +0x28 go through the rowed
// GameClientRandomVariable::getValue (0x002341A1). The angle comes from the
// rowed GetGameClientRandomValueReal (0x00234111) with BFME 2's own source
// path literal and line 59. cos and sin are the CRT imports. The donor's
// name and layout are carried, not independently re-derived.

#include <math.h>

extern float GetGameClientRandomValueReal( float low, float high,
	char *file, int line );

class GameClientRandomVariable
{
public:
	float getValue() const;

	int distribution;
	float minimum;
	float maximum;
};

namespace FXParticleSystem
{

struct Coord3D
{
	Coord3D() {}
	Coord3D( float x_, float y_, float z_ ) : x( x_ ), y( y_ ), z( z_ ) {}

	float x;
	float y;
	float z;
};

class CylindricalEmissionVelocityModule
{
public:
	Coord3D getVelocity( int, int );

private:
	char m_base[ 0x1c ];
	GameClientRandomVariable m_radial;		///< +0x1C
	GameClientRandomVariable m_normal;		///< +0x28
};

Coord3D CylindricalEmissionVelocityModule::getVelocity( int, int )
{
	float radial = m_radial.getValue();
	char *source = "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameClient\\System\\FXParticleSystem\\fxpsemittercylindervelocitymodule.cpp";
	float angle = GetGameClientRandomValueReal( 0.0f,
		6.28318530717958647692f, source, 59 );
	Coord3D components;
	components.x = (float)cos( angle ) * radial;
	components.y = (float)sin( angle ) * radial;
	return Coord3D( components.x, components.y, m_normal.getValue() );
}

}
