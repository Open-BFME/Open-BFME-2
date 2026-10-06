// cl: /DNDEBUG /MD /EHsc
//
// ?rva002637E2@Object@@QBEMPBUCoord3D@@0@Z,
// retail 0x002637E2 (57 bytes). Chain after 0x00263778 distance.
// thiscall ret 8 with two Coord3D const* args; returns
// Rva00263778Distance(a, geo.get(), this->+BC, b, 0, 0).
// Evidence: fld [ecx+0xBC] then add ecx,0xA8 + call rowed
// ?get@Rva0073A1C0FloatField@@QBEMXZ (disp 0x20 => this+0xC8),
// then call rowed ?Rva00263778Distance@@YAMPBUCoord3D@@MM0MM@Z
// with (ptr float get() float ptr 0 0); neighbours share flags/TU dir.
struct Coord3D
{
	float x;
	float y;
	float z;
};

class Rva0073A1C0FloatField
{
public:
	float get() const;
	char m_lead[0x20];
	float m_value;
};

float Rva00263778Distance(Coord3D const *a, float b, float c, Coord3D const *d, float e, float f);

class Object
{
public:
	float rva002637E2(Coord3D const *a, Coord3D const *b) const;

private:
	char m_pad0[0xA8];
	Rva0073A1C0FloatField m_geo; // +0xA8, get() reads +0xC8
};

float Object::rva002637E2(Coord3D const *a, Coord3D const *b) const
{
	float c = *(float const *)((char const *)this + 0xBC);
	return Rva00263778Distance(a, m_geo.get(), c, b, 0.0f, 0.0f);
}
