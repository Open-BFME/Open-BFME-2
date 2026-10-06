// cl: /O1 /MD /DNDEBUG /arch:SSE
// ?set@Rva002A9903FloatSetter@@QAEXM@Z retail 0x002A9903 14B
// Thiscall float setter storing its argument at +0x20 (movss / movss, ret 4).
// Sits in the Player-side gap between the Coord3D setter 0x002A98F2 and the
// rowed byte setter 0x002A9911; no direct callers (vtable-reached).
// Identity not recovered: address-derived name.

class Rva002A9903FloatSetter
{
public:
	void set(float value);

private:
	char m_pad[0x20];
	float m_value; // +0x20
};

void Rva002A9903FloatSetter::set(float value)
{
	m_value = value;
}
