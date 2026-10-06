// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva004F711CCreate@@YGPAURva004F711CObj@@PBVRva00468520@@@Z, retail
// 0x004F711C, 34 bytes. Allocates 0x10 via rowed byte allocator 0x000307F0
// then inits embedded Rva00468520 at +8 via rowed Init 0x004F6B7B. First 8
// bytes left uninitialized (pad). Evidence: single caller at 0x005CCED9 in
// FUN_009cced5; __stdcall ret 4 matches retail.

struct Rva00468520Obj
{
	int m_00;
	int m_04;
};

class Rva00468520
{
	Rva00468520Obj *m_00;
	int m_04;
};

void __cdecl Rva004F6B7BInit(Rva00468520 *dst, const Rva00468520 *src);

namespace _STL
{

template <class T>
class allocator
{
public:
	static char *allocate(unsigned int n, const void *hint);
};

}

struct Rva004F711CObj
{
	char m_pad[8];
	Rva00468520 m_08;
};

Rva004F711CObj *__stdcall Rva004F711CCreate(const Rva00468520 *src)
{
	Rva004F711CObj *p = (Rva004F711CObj *)_STL::allocator<char>::allocate(0x10, 0);
	Rva004F6B7BInit(&p->m_08, src);
	return p;
}
