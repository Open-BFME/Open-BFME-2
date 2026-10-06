// cl: /DNDEBUG /MD /EHsc /DWIN32 /D_WINDOWS
// ?rva00107152@Rva00107152@@QAEXXZ @0x00107152 27B via honest-address while-delete-first-virtual
// Evidence: this+8 loop while non-null; virtual slot 0 with int 0 returning ptr deleted via rowed ??3@YAXPAX@Z; caller unclaimed 0x0009A323
void __cdecl operator delete(void *p);
class RvaNode00107152 {
public:
	virtual RvaNode00107152 *rvaFoo(int x);
};
class Rva00107152 {
	char _pad[8];
	RvaNode00107152 *m_08;
public:
	void rva00107152();
};
void Rva00107152::rva00107152()
{
	for (;;) {
		RvaNode00107152 *p = m_08;
		if (p == 0)
			break;
		delete p->rvaFoo(0);
	}
}
