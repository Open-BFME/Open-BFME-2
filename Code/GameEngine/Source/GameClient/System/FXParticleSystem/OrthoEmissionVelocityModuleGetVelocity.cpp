// cl: /DNDEBUG /MD /GX- /Ob2
// ?getVelocity@OrthoEmissionVelocityModule@FXParticleSystem@@UAE?AUCoord3D@2@HH@Z
// RVA 0x0055E81F size 61. Virtual slot 4 (offset 0x10) of vtable 0x0081C860
// (class of ??0Rva003AF184@@QAE@ABV0@@Z). Evidence: BFME1 donor
// OrthoEmissionVelocityModuleSample.cpp (three vars at +0x1C +0x28 +0x34);
// sibling Outward 0x0055ECF9 just landed in same page with same flags family.
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
	Coord3D(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
	float x;
	float y;
	float z;
};
class OrthoEmissionVelocityModule
{
public:
	virtual Coord3D getVelocity(int, int);
private:
	char m_pad[0x18];
	GameClientRandomVariable m_x;
	GameClientRandomVariable m_y;
	GameClientRandomVariable m_z;
};
Coord3D OrthoEmissionVelocityModule::getVelocity(int, int)
{
	float v[3];
	v[0] = m_x.getValue();
	v[1] = m_y.getValue();
	v[2] = m_z.getValue();
	return Coord3D(v[0], v[1], v[2]);
}
}
