// cl: /DNDEBUG /MD /GX- /Ob2
// ?getVelocity@OutwardEmissionVelocityModule@FXParticleSystem@@UAE?AUCoord3D@2@PBU32@PAVEmissionVolumeModuleInterface@2@@Z
// RVA 0x0055ECF9 size 59. Virtual slot 4 (offset 0x10) of vtable 0x0081C8DC
// (class of ??0Rva003AF3F9@@QAE@ABV0@@Z). Evidence: BFME1 donors
// CylindricalEmissionVelocityModuleSample.cpp and OrthoEmissionVelocityModuleSample.cpp
// (slot-4 getVelocity siblings 0x0055EB84 0x0055E81F 0x00564AB8); Zero Hour
// ParticleSys.cpp OUTWARD case with two speeds; retail Speed/OtherSpeed in
// Outward writeINI 0x0055ED5F; vtable shares slot 3 DoXfer 0x0055ED34 with
// Cylindrical; volume getVelocity via EmissionVolumeModuleInterface slot 0.
typedef float Real;
class GameClientRandomVariable
{
public:
	Real getValue() const;
private:
	int m_type;
	Real m_low;
	Real m_high;
};
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
class EmissionVolumeModuleInterface
{
public:
	virtual Coord3D getVelocity(const Coord3D *pos, float speed, float otherSpeed) = 0;
};
class OutwardEmissionVelocityModule
{
public:
	virtual Coord3D getVelocity(const Coord3D *pos, EmissionVolumeModuleInterface *vol);
private:
	char m_pad[0x18];
	GameClientRandomVariable m_speed;
	GameClientRandomVariable m_otherSpeed;
};
Coord3D OutwardEmissionVelocityModule::getVelocity(const Coord3D *pos, EmissionVolumeModuleInterface *vol)
{
	float speed = m_speed.getValue();
	float otherSpeed = m_otherSpeed.getValue();
	return vol->getVelocity(pos, speed, otherSpeed);
}
}
