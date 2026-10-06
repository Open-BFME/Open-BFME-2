// cl: /MD
// ?Rva00548B97Free@@YAXH@Z @0x00548B97 83B. Free cdecl void(int): if index
// 8 and global 0x00A05FA8 set calls rowed Rva003B3371Call(22), then frees
// global array 0x00A05F88[index] via virtuals slot3(int) slot8() slot1(int)
// returning pointer for operator delete plus null. Evidence: rowed free
// plus 3 virtuals plus delete; 4 callers.
class Rva00548B97Helper
{
public:
	virtual void v0();
	virtual void *v1(int a1);
	virtual void v2();
	virtual void v3(int a1);
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
};

// G00A05F88: matched references place it at VA 0xe05f88; zero-filled at retail, sized to the
// 0x20-byte gap before the next known global there.
Rva00548B97Helper *G00A05F88[8];
extern int G00A05FA8;
// G00A05FA8: matched references place it at VA 0xe05fa8 (zero-filled .bss).
int G00A05FA8;

void __cdecl Rva003B3371Call(int index);
void operator delete(void *p);

void __cdecl Rva00548B97Free(int index)
{
	if (index == 8 && G00A05FA8 != 0)
		Rva003B3371Call(22);
	Rva00548B97Helper **slot = &G00A05F88[index];
	if (*slot != 0) {
		(*slot)->v3(0);
		(*slot)->v8();
		void *q = *slot ? (*slot)->v1(0) : 0;
		::operator delete(q);
		*slot = 0;
	}
}
