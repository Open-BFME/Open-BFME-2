// cl: /MD /DNDEBUG
// ?set@Rva002A98F2Coord3DSetter@@QAEXUCoord3D@@@Z retail 0x002A98F2 17B
// Thiscall setter copying a Coord3D passed by value into +0x0C (three movsd
// from the argument block, ret 0xC). Sits in the Player-side gap beside the
// rowed byte setter 0x002A9911 and the float setter 0x002A9903; no direct
// callers (vtable-reached). Identity not recovered: address-derived name.

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Rva002A98F2Coord3DSetter
{
public:
	void set(Coord3D value);

private:
	char m_pad[0x0C];
	Coord3D m_value; // +0x0C
};

void Rva002A98F2Coord3DSetter::set(Coord3D value)
{
	m_value = value;
}
