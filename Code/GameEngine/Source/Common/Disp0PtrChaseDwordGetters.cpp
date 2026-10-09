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
class Rva00225A98DwordField
{
public:
	int get() const;
};
class Rva0042D703PtrChaseField
{
public:
	int get() const;
	void *m_ptr;
};
int Rva0042D703PtrChaseField::get() const
{
	const Rva00225A98DwordField *q = *(const Rva00225A98DwordField *const *)((const char *)m_ptr + 0x24);
	if (q)
		return q->get();
	return 0;
}
class Rva0042D6C6PtrChaseField
{
public:
	int get() const;
	void *m_ptr;
};
int Rva0042D6C6PtrChaseField::get() const
{
	const char *q = *(const char *const *)((const char *)m_ptr + 0x24);
	if (q)
		return (int)(q + 0x18);
	return 0;
}
class Rva0042D6D6PtrChaseField
{
public:
	int get() const;
	void *m_ptr;
};
int Rva0042D6D6PtrChaseField::get() const
{
	const char *q = *(const char *const *)((const char *)m_ptr + 0x24);
	if (q)
		return (int)(q + 4);
	return 0;
}
class Rva005C4AF9DwordField
{
public:
	int get() const;
};
class Rva0042D69DPtrChaseField
{
public:
	int get() const;
	void *m_ptr;
};
int Rva0042D69DPtrChaseField::get() const
{
	const Rva005C4AF9DwordField *q = *(const Rva005C4AF9DwordField *const *)((const char *)m_ptr + 0x24);
	if (q)
		return q->get();
	return 0;
}

// Native 2E6C18..2E6C1D and 2E6C1D..2E6C23 are complete RET0 leaves
// between the existing 2E6C0E getter and the independent 2E6C23 body.
// BF1 9cbfb551fe20 Rva002FEE90SiegeDockSearch.cpp's indirect result
// accessors supply a source guide. Retail independently proves the first
// receiver word is a pointer and selects pointee words 0 and 4; the original
// owner, names, and whether the returned words are pointers remain unknown.
class Rva002E6C18PointeeValue
{
public:
    unsigned int getBits() const;
    void *holder;
};
unsigned int Rva002E6C18PointeeValue::getBits() const
{
    return *(const unsigned int *)holder;
}

class Rva002E6C1DPointeeValue
{
public:
    unsigned int getBits() const;
    void *holder;
};
unsigned int Rva002E6C1DPointeeValue::getBits() const
{
    return *(const unsigned int *)((const char *)holder + 4);
}
