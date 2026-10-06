// cl: /MD
// ?rva00603C5F@Rva00604465@@QAEHPBD@Z @0x00603C5F 68B: vtable slot 3 method checking tree lookup with normalized path. Evidence: vtable 0x0087A94C slot 3 plus rowed ji_00629176 plus rowed Rva00605365 plus rowed rva00603C0F plus neighbours 0x00603C57 0x00603CA3.
class Rva00603C0F { public: const void *rva00603C0F(const char *a, const char *b); };
void __cdecl ji_00629176();
char *Rva00605365(char *p);
class Rva00604465 { public: int rva00603C5F(const char *a); };
int Rva00604465::rva00603C5F(const char *a)
{
    char buf[260];
    ((char *(__cdecl *)(char *, const char *))&ji_00629176)(buf, a);
    const char *n = Rva00605365(buf);
    const void *found = ((Rva00603C0F *)this)->rva00603C0F(buf, n);
    return found != 0;
}
