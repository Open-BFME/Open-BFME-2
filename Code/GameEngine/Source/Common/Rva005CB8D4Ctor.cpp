// cl: /MD
// ??0Rva005CB8D4@@QAE@XZ retail 0x005CB8AC 40B
// Outer default ctor (vtable 0x00874DA8): allocates the 0x1C-byte inner elem
// with operator new 0x0002FDA0 and constructs it with the rowed inner ctor
// 0x005CB4C7 passing its own this storing to +4 (null on alloc failure).
// Frameless no-EH shape because the inner zeroing ctor cannot throw
// (declared throw() here per throw() callee rule). Precedent is outer
// Rva005CD1A9Ctor.cpp (same new-inner pattern with EH for its throwing
// list member). Callers at 0x00574320; dtor rowed at 0x005CB8D4; neighbours
// share // cl: /O1 /MD.
class Rva005CB8D4;
class Rva005CB4E6Elem
{
public:
	Rva005CB4E6Elem(Rva005CB8D4 *owner) throw();
private:
	Rva005CB8D4 *m_owner;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
};
class Rva005CB8D4
{
public:
	Rva005CB8D4();
	virtual ~Rva005CB8D4();
private:
	Rva005CB4E6Elem *m_elem;
};
void *__cdecl operator new(unsigned int);
Rva005CB8D4::Rva005CB8D4()
{
	m_elem = new Rva005CB4E6Elem(this);
}
