// cl: /MD
// ??4Rva00072A94@@QAEAAV0@ABV0@@Z, RVA 0x00072A94, 47B. Ref-counted holder
// assignment with self-check: Add_Ref the incoming referent (inc dword at
// +4) then Release_Ref the held one (dec dword at +4, Delete_This at vtable
// slot 0 when zero) before copying the pointer. Evidence: 11 free-function
// callers pass wrapper temps built by factory 0x152C47 (ctor 0x1525FB sets
// vtable 0x007D3B1C with NumRefs=1 at +4); release halves in callers
// 0x7DB7D/0x7DBB9/0x83744/0xE1879 inline the same dec-virtual sequence;
// BfmeAssignRecord32 operator= at 0x173499 calls it 7 times. Shape follows
// OpaqueRefElement4::operator= at 0x239099 and Rva005EEFD2::operator= at
// 0x5EEFD2 with inlined non-atomic counting.
class RefCountClass
{
public:
	virtual void Delete_This();
	void Add_Ref() { ++NumRefs; }
	void Release_Ref()
	{
		--NumRefs;
		if (NumRefs == 0)
			Delete_This();
	}
private:
	int NumRefs;
};
class Rva00072A94
{
public:
	Rva00072A94 &operator=(const Rva00072A94 &other);
private:
	RefCountClass *m_ptr;
};
Rva00072A94 &Rva00072A94::operator=(const Rva00072A94 &other)
{
	if (this != &other) {
		if (other.m_ptr)
			other.m_ptr->Add_Ref();
		if (m_ptr)
			m_ptr->Release_Ref();
		m_ptr = other.m_ptr;
	}
	return *this;
}

// ?Rva000E1860Copy@@YAPAVRva00072A94@@PAV1@00@Z, RVA 0x000E1860, 47B. Forward
// copy for Rva00072A94 holders using rowed assignment 0x00072A94.
// count = last-first; if <=0 return dest; else for (i=n;i!=0;--i)
// { *dest = *first; ++first; ++dest; } return dest. Caller at 0x000E1D64.
Rva00072A94 *__cdecl Rva000E1860Copy(Rva00072A94 *first, Rva00072A94 *last, Rva00072A94 *dest)
{
	int n = last - first;
	if (n <= 0)
		return dest;
	for (int i = n; i != 0; --i) {
		*dest = *first;
		++first;
		++dest;
	}
	return dest;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?Rva000E1860Copy@@YAPAVRva00072A94@@PAV1@00PAXH@Z=?Rva000E1860Copy@@YAPAVRva00072A94@@PAV1@00@Z")
