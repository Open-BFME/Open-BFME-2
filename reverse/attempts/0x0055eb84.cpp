// ?getVelocity@CylindricalEmissionVelocityModule@FXParticleSystem@@UAE?AUCoord3D@2@HH@Z
// partial score=0.95 date=2026-09-26
// ?getVelocity@CylindricalEmissionVelocityModule@FXParticleSystem@@UAE?AUCoord3D@2@HH@Z
// partial score=0.95 date=2026-09-26
// cl: /DNDEBUG /MD /GX- /O1 /Ob2

// ?getVelocity@CylindricalEmissionVelocityModule@FXParticleSystem@@UAE?AUCoord3D@2@HH@Z
// RVA 0x0055EB84, size 118. Virtual slot 4 (offset 0x10) of vtable 0x0081C8B8
// (class of ??0Rva003AF34F@@QAE@ABV0@@Z). Evidence: BFME1 donor
// CylindricalEmissionVelocityModuleSample.cpp (cos/sin radial trig), retail
// string C:\projects\bfme2patch103\bfme2\Code\GameEngine\Source\GameClient\
// System\FXParticleSystem\fxpsemittercylindervelocitymodule.cpp at 0x0086C2C8,
// float 6.2831853 at 0x007C746C, line 59 (0x3b), GameClientRandomVariable at
// +0x1c (radial) and +0x28 (normal), slot-4 siblings 0x0055E81F (Ortho, 3 vars)
// 0x00564AB8 (Spherical) 0x0055ECF9 (Outward).

typedef float Real;

class GameClientRandomVariable
{
public:
	enum DistributionType
	{
		CONSTANT, UNIFORM, GAUSSIAN, TRIANGULAR, LOW_BIAS, HIGH_BIAS
	};

	Real getValue() const;

private:
	DistributionType m_type;
	Real m_low;
	Real m_high;
};

extern Real GetGameClientRandomValueReal(Real low, Real high, char *file, int line);

extern "C" double __cdecl cos(double value);
extern "C" double __cdecl sin(double value);

namespace FXParticleSystem
{

struct Coord3D
{
	Coord3D() {}
	Coord3D(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}

	float x;
	float y;
	float z;
};

class CylindricalEmissionVelocityModule
{
public:
	virtual Coord3D getVelocity(int, int);

private:
	char m_pad[0x18];
	GameClientRandomVariable m_radial;
	GameClientRandomVariable m_normal;
};

// ?getVelocity@CylindricalEmissionVelocityModule@FXParticleSystem@@UAE?AUCoord3D@2@HH@Z present-unmatched
Coord3D CylindricalEmissionVelocityModule::getVelocity(int, int)
{
	float radial = m_radial.getValue();
	char *source = "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameClient\\System\\FXParticleSystem\\fxpsemittercylindervelocitymodule.cpp";
	float angle = GetGameClientRandomValueReal(0.0f, 6.28318530717958647692f, source, 59);
	Coord3D components;
	components.x = (float)cos(angle) * radial;
	components.y = (float)sin(angle) * radial;
	return Coord3D(components.x, components.y, m_normal.getValue());
}

}
