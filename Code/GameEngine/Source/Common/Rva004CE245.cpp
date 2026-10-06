// cl: /MD
// ?Rva004CE245@@YAXPAX@Z retail 0x004CE245 34B
// Free helper: if (!o->cond()) { o->step(); o->finish(0); } via vtable slots 0x1C/0x20/0x24.
// Evidence: 2 callers 0x0028DA28 0x00290D42 passing pointer; unlocks 1 ready.
class Cls {
public:
    virtual ~Cls();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual bool cond();
    virtual void step();
    virtual void finish(int x);
};
void __cdecl Rva004CE245(void *p)
{
    Cls *o = (Cls *)p;
    if (o->cond())
        return;
    o->step();
    o->finish(0);
}
