// cl: /EHs /MD
//
// ?Rva00500AF8Destroy@@YAXPAURva004FABE2@@0@Z @0x00500AF8 25B: range destroy.
// Destroys [first, last) with stride 0xC calling ??1Rva004FABE2@@QAE@XZ.
// Evidence: callee rowed 0x004FABE2; callers 0x00500E57 0x00500EE4;
// stride 0xC from add esi 0xC; shape matches rowed 0x00500CB8.

struct Rva004FABE2
{
	void *m_start;
	void *m_finish;
	void *m_end;
	~Rva004FABE2();
};

void __cdecl Rva00500AF8Destroy(Rva004FABE2 *first, Rva004FABE2 *last)
{
	for (; first != last; ++first)
		first->~Rva004FABE2();
}
