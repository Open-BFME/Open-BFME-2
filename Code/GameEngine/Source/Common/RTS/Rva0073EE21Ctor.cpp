// cl: /MD
// ??0Rva0073EE21@@QAE@XZ @0x0073EE21 44B
// Ctor pattern twin of FXListRva001E28B8Ctor: base Rva0040F9D(1 0 0 0) plus member at +8.
// Evidence: call rowed 0x00040F64 with 1 0 0 0; and [0xC] 0 plus base member vtable 0x00BC6F20
// plus own vtable 0x008F1538 plus member vtable 0x008F1534; caller 0x0073F3DC.

struct Rva0040F9DBase
{
	Rva0040F9DBase() : m_handle(0) {}
	void *m_handle;
};

class Rva0040F9D : public Rva0040F9DBase
{
public:
	Rva0040F9D(int a1, int a2, char const *a3, void *a4);
	virtual ~Rva0040F9D();
};

extern const void *const g_00BC6F20[];
extern const void *const g_00CF1538[];
extern const void *const g_00CF1534[];

struct Rva0073EE21Member
{
	Rva0073EE21Member() : m_vtable((void *)g_00BC6F20), m_04(0) {}
	void *m_vtable;
	int m_04;
};

class Rva0073EE21 : public Rva0040F9D
{
public:
	Rva0073EE21();
private:
	Rva0073EE21Member m_08;
};

Rva0073EE21::Rva0073EE21() : Rva0040F9D(1, 0, 0, 0)
{
	*(const void **)this = g_00CF1538;
	m_08.m_vtable = (void *)g_00CF1534;
}
