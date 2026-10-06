// cl: /MD
// ?set@Rva0009990D@@QAEXPAX@Z retail 0x000998EA 35B guarded pointer swap with
// LockClass dtor plus delete. Evidence: named pin plus rowed dtor 0x00613AC0
// plus delete 0x0002FD60; callers at 0x002256FD 0x0038B200.
void __cdecl operator delete(void *p);
struct MutexClass { struct LockClass { ~LockClass(); }; };
class Rva0009990D
{
public:
	void set(void *p);
	void clear();
private:
	MutexClass::LockClass *m_ptr;
};
void Rva0009990D::set(void *p)
{
	MutexClass::LockClass *old = m_ptr;
	if (p == old)
		return;
	m_ptr = (MutexClass::LockClass *)p;
	if (old == 0)
		return;
	old->~LockClass();
	::operator delete(old);
}
// ?clear@Rva0009990D@@QAEXXZ retail 0x0009990D 26B clear pointer with dtor plus
// delete. Evidence: named pin plus same callees as set; 23 callers.
void Rva0009990D::clear()
{
	MutexClass::LockClass *old = m_ptr;
	m_ptr = 0;
	if (old == 0)
		return;
	old->~LockClass();
	::operator delete(old);
}
