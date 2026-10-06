// cl: /O1 /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// Dump-lane range 5: builder at 0x1683A7 (28B). Runs the pinned 0x283A7
// init on this, clears +0xC, stamps vtable 0xBD41B8, returns this.
// Address-derived names.

extern const void *const g_00BD41B8[];
class Rva0016801A
{
public:
	void *rva0016801A(int n);
};
class Rva001683A7
{
public:
	Rva001683A7 *rva001683A7(int n);
private:
	const void *m_vtable;
	int m_04;
	int m_08;
	int m_0C;
};

// ?rva001683A7@Rva001683A7@@QAEPAV1@H@Z
Rva001683A7 *Rva001683A7::rva001683A7(int n)
{
	((Rva0016801A *)this)->rva0016801A(n);
	m_0C &= 0;
	m_vtable = (const void *)g_00BD41B8;
	return this;
}
