// cl: /MD /DNDEBUG /DWIN32 /D_WINDOWS /O1 /arch:SSE /G7
// ?rva0016801A@Rva0016801A@@QAEPAXH@Z @0x0016801A 38B
// Evidence: pin ?rva0016801A@Rva0016801A@@QAEPAXH@Z; caller 0x001683AE in Rva001683A7Init.cpp; callee Resize 0x00167F88 rowed in wwlib_pod_container_bodies.cpp; data g_00BD41AC at 0x007D41AC.

extern const void *const g_00BD41AC[];

struct BfmePod4
{
	int a[1];
};

template <class T> class SimpleVecClass
{
public:
	SimpleVecClass(int size = 0);
	virtual ~SimpleVecClass();
	virtual bool Resize(int newsize);
	virtual bool Uninitialised_Grow(int newsize);

protected:
	T *Vector;
	int VectorMax;
};

class Rva0016801A
{
public:
	void *rva0016801A(int n);

private:
	const void *m_vtable;
	int m_04;
	int m_08;
};

// ?rva0016801A@Rva0016801A@@QAEPAXH@Z
void *Rva0016801A::rva0016801A(int n)
{
	m_vtable = g_00BD41AC;
	m_04 = 0;
	m_08 = 0;
	if (n > 0)
		((SimpleVecClass<BfmePod4> *)this)->SimpleVecClass<BfmePod4>::Resize(n);
	return this;
}
