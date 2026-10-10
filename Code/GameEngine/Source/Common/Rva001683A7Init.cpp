// cl: /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// Dump-lane range 5: builder at 0x1683A7 (28B). Runs the pinned 0x283A7
// init on this, clears +0xC, stamps vtable 0xBD41B8, returns this.
// Address-derived names.
// The call from native16844F constructs its float-width member at D4.
// Recover the constructor ABI rather than the old return-this initializer
// spelling; both emitted 28B bodies are equal with the same base relocation.

extern const void *const g_00BD41B8[];
class Rva0016801A
{
public:
	void *rva0016801A(int n);
};
class Rva001683A7
{
public:
	Rva001683A7(int n);
private:
	const void *m_vtable;
	int m_04;
	int m_08;
	int m_0C;
};

// ??0Rva001683A7@@QAE@H@Z
Rva001683A7::Rva001683A7(int n)
{
	((Rva0016801A *)this)->rva0016801A(n);
	m_0C &= 0;
	m_vtable = (const void *)g_00BD41B8;
}
