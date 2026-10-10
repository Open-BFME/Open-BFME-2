// ?getPosition@CylinderEmissionVolumeModule@FXParticleSystem@@UAE?AUCoord3D@2@MMMM@Z
// partial score=0.98 date=2026-10-11
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// ?getPosition@CylinderEmissionVolumeModule@FXParticleSystem@@UAE?AUCoord3D@2@MMMM@Z
// retail 0x0055D741, 212 bytes, RET 0x14.
//
// Ported from the Open-BFME-1 donor
// game/GameEngine/Source/GameClient/System/FXParticleSystem/CylinderEmissionVolumeModuleSample.cpp
// (reference/open-bfme-1 @ 575ba2b04). Target facts: slot 7 of the cylinder
// volume's head tables (0x0081C808, 0x0081CC00, 0x0081D0B8), beside the
// rowed xfer (0x0055D638) that transfers the hollow flag at +0x20, the radius
// at +0x24 and the length at +0x2C; BFME 2 keeps an extra real at +0x28, so
// the centre sits at +0x30. The three draws go through the rowed
// GetGameClientRandomValueReal (0x00234111) with BFME 2's own source path
// literal and lines 105, 111 and 117; cos and sin are the CRT imports. The
// donor's names are carried, not independently re-derived.

#include <math.h>

extern float GetGameClientRandomValueReal( float low, float high,
	char *file, int line );

namespace FXParticleSystem
{

struct Coord3D
{
	Coord3D( float x_, float y_, float z_ ) : x( x_ ), y( y_ ), z( z_ ) {}

	float x;
	float y;
	float z;
};

class CylinderEmissionVolumeModule
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual Coord3D getPosition( float, float, float, float );

private:
	char m_base[0x20 - 4];
	bool m_hollow;			///< +0x20
	char m_pad[3];
	float m_radius;			///< +0x24
	float m_real28;			///< +0x28
	float m_length;			///< +0x2C
	float m_centerX;		///< +0x30
	float m_centerY;		///< +0x34
	float m_centerZ;		///< +0x38
};

Coord3D CylinderEmissionVolumeModule::getPosition( float, float, float, float )
{
	char *source = "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameClient\\System\\FXParticleSystem\\fxpsemittercylindervolumemodule.cpp";
	float angle = GetGameClientRandomValueReal( 0.0f, 6.28318530717958647692f, source, 105 );
	float radius = m_hollow ? m_radius : GetGameClientRandomValueReal( 0.0f, m_radius, source, 111 );

	Coord3D result( 0.0f, 0.0f, 0.0f );
	result.x = radius * (float)cos( angle ) + m_centerX;
	result.y = radius * (float)sin( angle ) + m_centerY;

	float halfLength = m_length * 0.5f;
	float z = GetGameClientRandomValueReal( -halfLength, halfLength, source, 117 ) + m_centerZ;
	return Coord3D( result.x, result.y, z );
}

}
