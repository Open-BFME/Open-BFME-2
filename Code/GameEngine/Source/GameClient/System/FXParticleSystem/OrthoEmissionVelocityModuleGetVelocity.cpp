// cl: /DNDEBUG /MD /GX- /Ob2
// ?getVelocity@OrthoEmissionVelocityModule@FXParticleSystem@@UAE?AUCoord3D@2@HH@Z
// RVA 0x0055E81F size 61. Virtual slot 4 (offset 0x10) of vtable 0x0081C860
// (class of ??0Rva003AF184@@QAE@ABV0@@Z). Evidence: BFME1 donor
// OrthoEmissionVelocityModuleSample.cpp (three vars at +0x1C +0x28 +0x34);
// sibling Outward 0x0055ECF9 just landed in same page with same flags family.
typedef float Real;
class Xfer
{
public:
	void Version1();
};
class GameClientRandomVariable;
Xfer &xferRandomVariable(Xfer &xfer, GameClientRandomVariable &var);
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
protected:
	virtual void xfer(Xfer *xfer);
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

// ?xfer@OrthoEmissionVelocityModule@FXParticleSystem@@MAEXPAVXfer@@@Z
// RVA 0x0055E85C size 53: slot 3 (offset 0x0C) of the same vtable 0x0081C860
// (ICF-shared with the slot-3 entries of 0x0081CAE0 and 0x0081CF94):
// Version1, then the three variables through the rowed xferRandomVariable
// 0x00306183, as the one-variable Rva003AF22E::xfer 0x0055EA8E does.
void OrthoEmissionVelocityModule::xfer(Xfer *xfer)
{
	xfer->Version1();
	xferRandomVariable(*xfer, m_x);
	xferRandomVariable(*xfer, m_y);
	xferRandomVariable(*xfer, m_z);
}
}
