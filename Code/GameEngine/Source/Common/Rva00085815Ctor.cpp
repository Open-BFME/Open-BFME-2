// cl: /MD /EHsc /DNDEBUG
// ??0Rva00085815@@QAE@XZ, retail 0x00085815, 67 bytes.
// Ctor with Region3D[3] at +0 and +0x30 via vector ctor plus ParabolicEase
// at +0x68 via rowed 0x0008517E with (0 0 1). Evidence: rowed Region3D ctor
// 0x0047A6A9 and vector iterator 0x00001423; caller 0x0008B888.
typedef float Real;

class ParabolicEase
{
public:
	ParabolicEase *rva0008517E(Real easeInTime, Real easeOutTime, Real duration);
private:
	Real m_in;
	Real m_out;
};

class Region3D
{
public:
	Region3D();
private:
	unsigned char m_pad[0x10];
};

class Rva00085815
{
public:
	Rva00085815();
private:
	Region3D m_00[3];
	Region3D m_30[3];
	unsigned char m_pad60[8];
	ParabolicEase m_68;
};

Rva00085815::Rva00085815()
{
	m_68.rva0008517E(0.0f, 0.0f, 1.0f);
}
