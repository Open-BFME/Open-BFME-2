// cl: /MD
//
// ?rva00041168@Rva00041168@@QAEXPAX@Z retail 0x00041168 28B
// Evidence: unlock lane; callee delete[] 0x0002FD80; unblocks 0x0004123B 0x0004128E; prev Rva00041004Lock same /O1 MD; setter frees old array if different.
void __cdecl operator delete[](void *block);
class Rva00041168
{
public:
	void rva00041168(void *p);
private:
	void *m_ptr00;
};
void Rva00041168::rva00041168(void *p)
{
	void *old = m_ptr00;
	if (p != old) {
		::operator delete[](old);
		m_ptr00 = p;
	}
}
