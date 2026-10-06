// cl: /MD
// ?rva00049D20@Rva00049D20@@QAEPAXPAXH@Z @0x00049D20 36B
// evidence: 4 callers; 0x005EEAC6 fills stack 12B then PartitionManager::getShroudStatusForPlayer takes it as Coord3D; this+0x10 is table begin with end at +0x14 in caller; returns dest in EAX.
struct Payload { float f; int a; int b; };
struct Entry { char pad[8]; Payload p; };
class Rva00049D20 {
    char m_pad[16];
    Entry **m_table;
public:
    void *rva00049D20(void *dest, int index);
};
void *Rva00049D20::rva00049D20(void *dest, int index)
{
    Payload *d = (Payload *)dest;
    Payload *s = &m_table[index]->p;
    d->f = s->f;
    d->a = s->a;
    d->b = s->b;
    return dest;
}
