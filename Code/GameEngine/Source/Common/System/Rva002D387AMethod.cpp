// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva002D387A@Rva002D387A@@QAEXPAX@Z retail 0x002D387A 26 bytes. Owning-pointer
// setter at +0 that stores the new pointer then deletes the old value via rowed
// operator delete 0x0002FD60 when the new pointer differs and old is non-null.
// Evidence: caller 0x002D48B0 in unclaimed 0x002D4748; same /O1 as neighbour
// 0x002D3850; callee ??3@YAXPAX@Z rowed in mem_ops.cpp.
void __cdecl operator delete(void *p);

class Rva002D387A
{
public:
	void rva002D387A(void *p);
private:
	void *m_ptr;
};

void Rva002D387A::rva002D387A(void *p)
{
	void *old = m_ptr;
	if (p != old)
	{
		m_ptr = p;
		if (old != 0)
			operator delete(old);
	}
}
