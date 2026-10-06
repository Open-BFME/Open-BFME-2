// cl: /DNDEBUG /MD
//
// ?Rva006CD5A0Copy@@YAPAVRva006CD5A0Elem@@PAV1@00@Z, retail 0x006CD5A0, 60B.
// AptValueNameEntry-style 8B copy: EAStringC at +0 via rowed operator=
// 0x006D3030 plus int at +4, first/last/dest pointers, returns dest end.
// Callers 0x006CE8FE/0x006D011A prove three-pointer __cdecl shape.
class EAStringC
{
public:
	EAStringC &operator=(const EAStringC &other);
	void *m_pData;
};

class Rva006CD5A0Elem
{
public:
	EAStringC m_name;
	int m_value;
};

Rva006CD5A0Elem *__cdecl Rva006CD5A0Copy(Rva006CD5A0Elem *first, Rva006CD5A0Elem *last, Rva006CD5A0Elem *dest)
{
	for (; first != last; ++first) {
		Rva006CD5A0Elem *cur = dest++;
		cur->m_name = first->m_name;
		cur->m_value = first->m_value;
	}
	return dest;
}
