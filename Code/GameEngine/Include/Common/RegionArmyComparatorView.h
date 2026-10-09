#ifndef REGION_ARMY_COMPARATOR_VIEW_H
#define REGION_ARMY_COMPARATOR_VIEW_H

struct EmitVtableTag;

// Retail BE4318: pure comparison3B810 and scalar destructor20E20C.
// BE4334 overrides those two slots with20E6FB and20E6DF. Installers
// independently begin the separate one-slot visitor tables atBE4320 and
// BE433C; their adjacent pointers are not comparator slots. AddBattle20FC0F
// constructs the derived callback; sort3F4A46 passes two army pointers to
// slot0. Original interface names and full retail extent remain unproved.
class Rva0020E20C
{
public:
    Rva0020E20C() {}
    Rva0020E20C(EmitVtableTag *);
    virtual bool Compare(void *, void *) = 0;
    virtual ~Rva0020E20C() {}
};

class Rva0020E205 : public Rva0020E20C
{
public:
    Rva0020E205() {}
    Rva0020E205(EmitVtableTag *);
    virtual bool Compare(void *, void *);
    virtual ~Rva0020E205() {}
};

#endif
