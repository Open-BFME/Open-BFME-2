// cl: /MD
// ??0Rva000E771B@@QAE@XZ 0x000E771B 25B
// Default ctor constructing 3x Region2D at +0x10 size 0x10 via rowed
// vector_constructor_iterator 0x1423 with rowed empty ctor 0x47A6A9.
// Evidence: pushes 0x87A6A9 3 0x10 lea +0x10 call 0x1423 mov eax,esi;
// prev Rva000E76B8 ends at 0xE771B; caller at 0x000E98C5.

struct Region2D
{
	Region2D();
	float x_min;
	float y_min;
	float x_max;
	float y_max;
};

class Rva000E771B
{
public:
	Rva000E771B();
private:
	char _pad0[0x10];
	Region2D m_arr[3];
};

Rva000E771B::Rva000E771B()
{
}
