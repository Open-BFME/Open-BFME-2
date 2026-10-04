// cl: /O1 /DNDEBUG /MD
// ?rva0023C7D2@Rva0023C7D2@@QAEXXZ @0x0023C7D2 35B
// Evidence: leaf lane called from 3 unclaimed sites; neighbours 0x0023C7B0 0x0023C7F5; unfolded vf0(0)+free delete idiom per CDownloadDtor and DX8MeshRendererClass_Invalidate_Thunk precedents.
void __cdecl operator delete(void *ptr);

class Rva0023C7D2Pointee
{
public:
	virtual void *scalarDeletingDestructor(unsigned int flags);
};

class Rva0023C7D2
{
public:
	void rva0023C7D2();
private:
	char m_pad[0x120];
	Rva0023C7D2Pointee *m_ptr;
};

void Rva0023C7D2::rva0023C7D2()
{
	if (m_ptr != 0)
	{
		::operator delete(m_ptr->scalarDeletingDestructor(0));
		m_ptr = 0;
	}
}
