// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva001E7E25@Rva001E7E25@@QAEXXZ retail 0x001E7E25 83B: clears pointer array via virtual slot 0 plus delete then vector erase plus flag clears.
// Evidence: frameless thiscall with ebx index esi vector plus loop test ecx je plus push 0 call [eax] push eax call 0x0002FD60 then push end push begin call 0x0031BD55 erase then and [edi+0x10] 0 plus bytes [edi+0x14] [edi+0x15] 0; callers 0x001E86EE 0x00268364 0x00268A59 0x0026E87A 0x0026EBD4.
#include <vector>
void __cdecl operator delete(void *block);
class Rva001E7E25Elem
{
public:
	virtual void *rvaGet(int arg);
};
class Rva001E7E25
{
public:
	void rva001E7E25();
private:
	char m_pad00[4];
	_STL::vector<void *> m_vec04;
	int m_10;
	unsigned char m_14;
	unsigned char m_15;
};
void Rva001E7E25::rva001E7E25()
{
	for (unsigned int i = 0; i < m_vec04.size(); ++i)
	{
		Rva001E7E25Elem *elem = (Rva001E7E25Elem *)m_vec04[i];
		if (elem)
		{
			void *p = elem->rvaGet(0);
			::operator delete(p);
		}
	}
	m_vec04.clear();
	m_10 = 0;
	m_14 = 0;
	m_15 = 0;
}
