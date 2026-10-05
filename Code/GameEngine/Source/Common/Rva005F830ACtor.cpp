// cl: /O1 /EHsc /MD /DNDEBUG
// ??0Rva005F830A@@QAE@PAX000@Z @0x005F830A 80B
// Constructor: own vtable 0x00C79A90, heap member at +4 allocated via rowed
// operator new 0x0002FDA0 (0x68 bytes) and constructed by pinned 0x005F7F21
// when non-null; the init return (or null) lands in +4. Same
// new-plus-conditional-init EH shape as 0x005F3E93; states stay 0 (no base).
class Rva005F830AHeap
{
public:
	Rva005F830AHeap(void *s, void *a1, void *a2, void *a3, void *a4);
private:
	char m_pad[0x68];
};

class Rva005F830A
{
public:
	Rva005F830A(void *a1, void *a2, void *a3, void *a4);
	virtual ~Rva005F830A();
private:
	Rva005F830AHeap *m_04;
};

Rva005F830A::Rva005F830A(void *a1, void *a2, void *a3, void *a4)
	: m_04(new Rva005F830AHeap(this, a1, a2, a3, a4))
{
}
