// cl: /ICode/Libraries/Include /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Sphere position callback at BFME2 RVA 0x0055D48C (129 bytes).
// Donor: Open-BFME-1 34f59164f6d1efd413c5fd37f4894ec834c3c0fe,
// game/GameEngine/Source/GameClient/System/FXParticleSystem/SphereEmissionVolumeModuleGetPosition.cpp.
// The donor supplies the named module and inheritance model; target bytes
// prove hollow +0x20, radius +0x24, RET 0x14, the full source literal at
// line 86, and calls to the existing random and unit-vector providers.
#include "Lib/Coord3DCtorView.h"
#include "../../../../Include/GameClient/EmissionVolumeInfo.h"
#include "../../../../Include/GameClient/SphereEmissionVolumeInfo.h"

float __cdecl GetGameClientRandomValueReal(float low, float high, char *file, int line);
Coord3D *__cdecl Rva003AFA64FillUnitVector(Coord3D *out);

namespace FXParticleSystem
{

class __declspec(novtable) ParticleModulePrimary
{
public:
	virtual ~ParticleModulePrimary() = 0;

private:
	unsigned char m_state[0x10];
};

class __declspec(novtable) ParticleModuleClassInterface
{
public:
	virtual void *getModuleClass() const = 0;
};

class __declspec(novtable) EmissionVolumeModuleInterface
{
public:
	virtual Coord3D getVelocity(const Coord3D *, float, float) = 0;
};

template <int Category>
class DefaultParticleModule
	: public ParticleModulePrimary,
	  public ParticleModuleClassInterface,
	  public EmissionVolumeModuleInterface
{
};

class SphereEmissionVolumeModule
	: public DefaultParticleModule<5>, public SphereEmissionVolumeInfo
{
public:
	virtual Coord3D getPosition(float, float, float, float);
};

typedef char DefaultParticleModuleLayout[
	(sizeof(DefaultParticleModule<5>) == 0x1c) ? 1 : -1];
typedef char SphereEmissionVolumeModuleLayout[
	(sizeof(SphereEmissionVolumeModule) == 0x28) ? 1 : -1];

Coord3D SphereEmissionVolumeModule::getPosition(float, float, float, float)
{
	char *source =
		"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameClient\\System\\FXParticleSystem\\fxpsemitterspherevolumemodule.cpp";
	float radius = m_04 ? m_radius :
		GetGameClientRandomValueReal(0.0f, m_radius, source, 86);
	Coord3D randomPoint;
	Coord3D unit;
	unit = *Rva003AFA64FillUnitVector(&randomPoint);
	Coord3D result;
	result.x = unit.x * radius; result.y = unit.y * radius; result.z = unit.z * radius;
	return result;
}

}
