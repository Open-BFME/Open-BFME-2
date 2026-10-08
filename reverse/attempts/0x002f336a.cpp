// ?rva002F336A@Rva002F336AOwner@@QAEXPAX0@Z
// partial score=0.9 date=2026-10-08
// cl: /Os /DNDEBUG /MD /arch:SSE /G7 /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva002F336A@Rva002F336AOwner@@QAEXPAX0@Z @0x002F336A 40B: forwards two stack
// pointers and nine fields of the owner to Pathfinder::CheckForTarget.
struct Coord3D;
class Rva002CB35CObj;

class Pathfinder
{
public:
	bool CheckForTarget(void *obj, void *a2, void *a3, Rva002CB35CObj *weapon,
		void *a5, void *a6, void *a7, void *a8, Coord3D *out);
};

class Rva002F336AOwner
{
public:
	void rva002F336A(void *a2, void *a3);

private:
	Pathfinder *m_0;
	void *m_4;
	unsigned char m_8;
	void *m_c;
	Coord3D *m_10;
	void *m_14;
	void *m_18;
	Rva002CB35CObj *m_1c;
};

// ?rva002F336A@Rva002F336AOwner@@QAEXPAX0@Z @0x002F336A
void Rva002F336AOwner::rva002F336A(void *a2, void *a3)
{
	m_0->CheckForTarget(m_4, a2, a3, m_1c, m_14, m_18, m_c, (void *)m_8, m_10);
}
