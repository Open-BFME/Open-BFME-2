// Disp0 pointer-chase dword getters: six-byte __thiscall members with one shape:
//
//     mov eax,[ecx] / mov eax,[eax+<DISP>] / ret
//
// A pointer is read at +0 from `this`, then a dword is read at a second
// displacement from that pointer and returned. MSVC 7.1 emits `8B 01` for
// the zero-displacement first load plus `8B 40 XX` and `ret` for six bytes.
// Identity is not recovered: every name is derived from its address.
// No // cl: line (defaults match the frameless six-byte shape).
class Rva0042D697PtrChaseField
{
public:
	int get() const;
	void *m_ptr;
};
int Rva0042D697PtrChaseField::get() const
{
	return *(int *)((char *)m_ptr + 0x30);
}
class Rva0042D6AEPtrChaseField
{
public:
	int get() const;
	void *m_ptr;
};
int Rva0042D6AEPtrChaseField::get() const
{
	return *(int *)((char *)m_ptr + 0x28);
}
class Rva0042D6B4PtrChaseField
{
public:
	int get() const;
	void *m_ptr;
};
int Rva0042D6B4PtrChaseField::get() const
{
	return *(int *)((char *)m_ptr + 0x18);
}
class Rva0042D6BAPtrChaseField
{
public:
	int get() const;
	void *m_ptr;
};
int Rva0042D6BAPtrChaseField::get() const
{
	return *(int *)((char *)m_ptr + 0x1C);
}
class Rva0042D6C0PtrChaseField
{
public:
	int get() const;
	void *m_ptr;
};
int Rva0042D6C0PtrChaseField::get() const
{
	return *(int *)((char *)m_ptr + 0x38);
}
class Rva0042D6E6PtrChaseField
{
public:
	int get() const;
	void *m_ptr;
};
int Rva0042D6E6PtrChaseField::get() const
{
	return *(int *)((char *)m_ptr + 0x20);
}
class Rva0042D6FDPtrChaseField
{
public:
	int get() const;
	void *m_ptr;
};
int Rva0042D6FDPtrChaseField::get() const
{
	return *(int *)((char *)m_ptr + 0x34);
}
class Rva0042D714PtrChaseField
{
public:
	int get() const;
	void *m_ptr;
};
int Rva0042D714PtrChaseField::get() const
{
	return *(int *)((char *)m_ptr + 0x2C);
}
