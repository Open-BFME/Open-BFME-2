// cl: /DNDEBUG /MD
//
// ??0Rva0007671F@@QAE@XZ @0x0007671F (22B).
// Honest address ctor for a 0x40 class whose first (and only) member is
// Region2D m_arr[4] at +0. Retail pushes element ctor VA 0x87A6A9 (rowed
// Region3D/Region2D empty ctor at 0x47A6A9, all 3B ICF twins), count 4,
// stride 0x10, and calls rowed vector_constructor_iterator at 0x1423.
// Element size 0x10 matches Region2D (x_min/y_min/x_max/y_max), not Region3D
// (0x18); Region2D ctor shares the same folded address, so the push bytes
// match. Callers construct 0x40 locals via this ctor (0x0014D44C,
// 0x0007C1AE, 0x0007C220) and use them in Matrix4::Multiply chains.
class Region2D
{
public:
	Region2D();
	float x_min;
	float y_min;
	float x_max;
	float y_max;
};
class Rva0007671F
{
public:
	Rva0007671F();
private:
	Region2D m_arr[4];
};
Rva0007671F::Rva0007671F()
{
}
