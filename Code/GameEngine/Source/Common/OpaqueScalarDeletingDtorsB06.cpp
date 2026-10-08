// cl: /O1 /DNDEBUG /MD /Ireference/shims/bfmelist /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// Opaque scalar deleting destructors, batch B06: 28-byte wrappers that
// call the destructor, test bit 0 of the flags, conditionally free through
// operator delete (0x0002FD60) and return this (ret 4), found in vtable slots
// with no ledger owner. Each destructor is declared, not defined, so the call
// resolves to its pin in reverse/symbols.csv (address names unless the
// destructor already carried one); the dummy tag constructors (no retail
// counterpart) only make this TU emit each vtable and with it the deleting
// destructor. Owner identities are not recovered, and these declarations
// model no layout (docs/reconstruction/deleting-destructor-identity-audit.md)
// beyond the secondary-base offsets their adjustor thunks prove.
//
//   wrapper     dtor        vtable#slot
//   0x002D628F  0x002D5380  0x00C02DC0#0
//   0x002D724B  0x002D6C1C  0x00C0331C#0
//   0x002DF2DA  0x002DE58D  0x00C0402C#0
//   0x002E2CF4  0x002E2AAE  0x00C04B50#0
//   0x002FED37  0x002FEBB7  0x00C073D0#0
//   0x00309DDA  0x00309D9E  0x00C082E8#0
//   0x0030DE92  0x0030DBD5  0x00C08A2C#0
//   0x0030F8E3  0x0030F4AF  0x00C09840#0
//   0x0031861B  0x00318637  0x00C0C734#0
//   0x0031A00E  0x00319D01  0x00C0C82C#0
//   0x0031EB7A  0x0031DCF0  0x00C0CC88#0
//   0x00328CDC  0x00328CF8  0x00C0D8D8#0
//   0x0032A0B2  0x0032989F  0x00C0D8FC#0
//   0x0032EF22  0x0032EC63  0x00C0DA98#0
//   0x00337C70  0x00337AA8  0x00C0E390#0
//   0x0033E90B  0x0033DDA1  0x00C10C4C#0
//   0x00352B25  0x003516F3  0x00C14CD0#0
//   0x00355BBE  0x00355BDA  0x00C14E14#0
//   0x0035686D  0x003561BE  0x00C14EBC#0
//   0x0035978C  0x00359290  0x00C15398#0
//   0x0035ABA4  0x0035A9C1  0x00C153E0#0
//   0x0036027C  0x003601C5  0x00C16778#0
//   0x003604AA  0x003603D4  0x00C16808#0
//   0x00362E73  0x00362CF2  0x00C16FE8#0
//   0x00362E8F  0x00362D6C  0x00C17068#0

struct EmitVtableTag;

class Rva002D5380
{
public:
	Rva002D5380(EmitVtableTag *);
public:
	virtual ~Rva002D5380();
};

// ?<Rva002D5380::Rva002D5380> absent-from-retail
Rva002D5380::Rva002D5380(EmitVtableTag *)
{
}

class Rva002D6C1C
{
public:
	Rva002D6C1C(EmitVtableTag *);
public:
	virtual ~Rva002D6C1C();
};

// ?<Rva002D6C1C::Rva002D6C1C> absent-from-retail
Rva002D6C1C::Rva002D6C1C(EmitVtableTag *)
{
}

class Rva002DE58DBase0
{
public:
	virtual ~Rva002DE58DBase0();
private:
	char m_unmodelled_04[0xC - 0x04];
};

// Secondary base at +0xC: the this-adjusting deleting-destructor thunk
// (sub ecx, 0xC) at 0x002DE585 in its vtable is target evidence for it.
class Rva002DE58DBaseC
{
public:
	virtual ~Rva002DE58DBaseC();
};
class Rva002DE58D : public Rva002DE58DBase0, public Rva002DE58DBaseC
{
public:
	Rva002DE58D(EmitVtableTag *);
public:
	virtual ~Rva002DE58D();
};

// ?<Rva002DE58D::Rva002DE58D> absent-from-retail
Rva002DE58D::Rva002DE58D(EmitVtableTag *)
{
}

class Rva002E2AAE
{
public:
	Rva002E2AAE(EmitVtableTag *);
public:
	virtual ~Rva002E2AAE();
};

// ?<Rva002E2AAE::Rva002E2AAE> absent-from-retail
Rva002E2AAE::Rva002E2AAE(EmitVtableTag *)
{
}

class Rva002FEBB7Base0
{
public:
	virtual ~Rva002FEBB7Base0();
private:
	char m_unmodelled_04[0xC - 0x04];
};

// Secondary base at +0xC: the this-adjusting deleting-destructor thunk
// (sub ecx, 0xC) at 0x002FEB32 in its vtable is target evidence for it.
class Rva002FEBB7BaseC
{
public:
	virtual ~Rva002FEBB7BaseC();
};
class Rva002FEBB7 : public Rva002FEBB7Base0, public Rva002FEBB7BaseC
{
public:
	Rva002FEBB7(EmitVtableTag *);
public:
	virtual ~Rva002FEBB7();
};

// ?<Rva002FEBB7::Rva002FEBB7> absent-from-retail
Rva002FEBB7::Rva002FEBB7(EmitVtableTag *)
{
}

class Rva00309D9E
{
public:
	Rva00309D9E(EmitVtableTag *);
public:
	virtual ~Rva00309D9E();
};

// ?<Rva00309D9E::Rva00309D9E> absent-from-retail
Rva00309D9E::Rva00309D9E(EmitVtableTag *)
{
}

class Rva0030F4AF
{
public:
	Rva0030F4AF(EmitVtableTag *);
public:
	virtual ~Rva0030F4AF();
};

// ?<Rva0030F4AF::Rva0030F4AF> absent-from-retail
Rva0030F4AF::Rva0030F4AF(EmitVtableTag *)
{
}

class Rva00318637Base0
{
public:
	virtual ~Rva00318637Base0();
private:
	char m_unmodelled_04[0xC - 0x04];
};

// Secondary base at +0xC: the this-adjusting deleting-destructor thunk
// (sub ecx, 0xC) at 0x00318613 in its vtable is target evidence for it.
class Rva00318637BaseC
{
public:
	virtual ~Rva00318637BaseC();
};
class Rva00318637 : public Rva00318637Base0, public Rva00318637BaseC
{
public:
	Rva00318637(EmitVtableTag *);
public:
	virtual ~Rva00318637();
};

// ?<Rva00318637::Rva00318637> absent-from-retail
Rva00318637::Rva00318637(EmitVtableTag *)
{
}

class Rva00319D01
{
public:
	Rva00319D01(EmitVtableTag *);
public:
	virtual ~Rva00319D01();
};

// ?<Rva00319D01::Rva00319D01> absent-from-retail
Rva00319D01::Rva00319D01(EmitVtableTag *)
{
}

class Rva0031DCF0
{
public:
	Rva0031DCF0(EmitVtableTag *);
public:
	virtual ~Rva0031DCF0();
};

// ?<Rva0031DCF0::Rva0031DCF0> absent-from-retail
Rva0031DCF0::Rva0031DCF0(EmitVtableTag *)
{
}

class Rva00328CF8Base0
{
public:
	virtual ~Rva00328CF8Base0();
private:
	char m_unmodelled_04[0xC - 0x04];
};

// Secondary base at +0xC: the this-adjusting deleting-destructor thunk
// (sub ecx, 0xC) in its vtable is target evidence for it.
class Rva00328CF8BaseC
{
public:
	virtual ~Rva00328CF8BaseC();
};
class Rva00328CF8 : public Rva00328CF8Base0, public Rva00328CF8BaseC
{
public:
	Rva00328CF8(EmitVtableTag *);
public:
	virtual ~Rva00328CF8();
};

// ?<Rva00328CF8::Rva00328CF8> absent-from-retail
Rva00328CF8::Rva00328CF8(EmitVtableTag *)
{
}

class Rva0032989F
{
public:
	Rva0032989F(EmitVtableTag *);
public:
	virtual ~Rva0032989F();
};

// ?<Rva0032989F::Rva0032989F> absent-from-retail
Rva0032989F::Rva0032989F(EmitVtableTag *)
{
}

class Rva0032EC63Base0
{
public:
	virtual ~Rva0032EC63Base0();
private:
	char m_unmodelled_04[0xC - 0x04];
};

// Secondary base at +0xC: the this-adjusting deleting-destructor thunk
// (sub ecx, 0xC) at 0x0032ED59 in its vtable is target evidence for it.
class Rva0032EC63BaseC
{
public:
	virtual ~Rva0032EC63BaseC();
};
class Rva0032EC63 : public Rva0032EC63Base0, public Rva0032EC63BaseC
{
public:
	Rva0032EC63(EmitVtableTag *);
public:
	virtual ~Rva0032EC63();
};

// ?<Rva0032EC63::Rva0032EC63> absent-from-retail
Rva0032EC63::Rva0032EC63(EmitVtableTag *)
{
}

class Rva00337AA8
{
public:
	Rva00337AA8(EmitVtableTag *);
public:
	virtual ~Rva00337AA8();
};

// ?<Rva00337AA8::Rva00337AA8> absent-from-retail
Rva00337AA8::Rva00337AA8(EmitVtableTag *)
{
}

class Rva0033DDA1
{
public:
	Rva0033DDA1(EmitVtableTag *);
public:
	virtual ~Rva0033DDA1();
};

// ?<Rva0033DDA1::Rva0033DDA1> absent-from-retail
Rva0033DDA1::Rva0033DDA1(EmitVtableTag *)
{
}

class Rva003516F3
{
public:
	Rva003516F3(EmitVtableTag *);
public:
	virtual ~Rva003516F3();
};

// ?<Rva003516F3::Rva003516F3> absent-from-retail
Rva003516F3::Rva003516F3(EmitVtableTag *)
{
}

class Rva00355BDABase0
{
public:
	virtual ~Rva00355BDABase0();
private:
	char m_unmodelled_04[0xC - 0x04];
};

// Secondary base at +0xC: the this-adjusting deleting-destructor thunk
// (sub ecx, 0xC) at 0x00355BB6 in its vtable is target evidence for it.
class Rva00355BDABaseC
{
public:
	virtual ~Rva00355BDABaseC();
};
class Rva00355BDA : public Rva00355BDABase0, public Rva00355BDABaseC
{
public:
	Rva00355BDA(EmitVtableTag *);
public:
	virtual ~Rva00355BDA();
};

// ?<Rva00355BDA::Rva00355BDA> absent-from-retail
Rva00355BDA::Rva00355BDA(EmitVtableTag *)
{
}

class Rva003561BE
{
public:
	Rva003561BE(EmitVtableTag *);
public:
	virtual ~Rva003561BE();
};

// ?<Rva003561BE::Rva003561BE> absent-from-retail
Rva003561BE::Rva003561BE(EmitVtableTag *)
{
}

class Rva00359290
{
public:
	Rva00359290(EmitVtableTag *);
public:
	virtual ~Rva00359290();
};

// ?<Rva00359290::Rva00359290> absent-from-retail
Rva00359290::Rva00359290(EmitVtableTag *)
{
}

class Rva0035A9C1
{
public:
	Rva0035A9C1(EmitVtableTag *);
public:
	virtual ~Rva0035A9C1();
};

// ?<Rva0035A9C1::Rva0035A9C1> absent-from-retail
Rva0035A9C1::Rva0035A9C1(EmitVtableTag *)
{
}

class Rva003601C5
{
public:
	Rva003601C5(EmitVtableTag *);
public:
	virtual ~Rva003601C5();
};

// ?<Rva003601C5::Rva003601C5> absent-from-retail
Rva003601C5::Rva003601C5(EmitVtableTag *)
{
}

class Rva003603D4
{
public:
	Rva003603D4(EmitVtableTag *);
public:
	virtual ~Rva003603D4();
};

// ?<Rva003603D4::Rva003603D4> absent-from-retail
Rva003603D4::Rva003603D4(EmitVtableTag *)
{
}

class Rva00362CF2
{
public:
	Rva00362CF2(EmitVtableTag *);
public:
	virtual ~Rva00362CF2();
};

// ?<Rva00362CF2::Rva00362CF2> absent-from-retail
Rva00362CF2::Rva00362CF2(EmitVtableTag *)
{
}

class Rva00362D6C
{
public:
	Rva00362D6C(EmitVtableTag *);
public:
	virtual ~Rva00362D6C();
};

// ?<Rva00362D6C::Rva00362D6C> absent-from-retail
Rva00362D6C::Rva00362D6C(EmitVtableTag *)
{
}

// AI::reset at 0x002FEB3A..0x002FEBB7. Source lead: GeneralsMD
// GameLogic/AI/AI.cpp at BFME1 donor revision 34f59164f6d1efd413c5fd37f4894ec834c3c0fe.
// Target facts: receiver +0x10 pathfinder; +0x14 group-list sentinel;
// +0x18 override-data head, whose next link is +0x100; +0x1C and +0x20
// are the reset counters. Matched AI::destroyGroup (0x002FE712) supports
// the group list and virtual deleteInstance(0) followed by scalar delete.
// The donor supplies the reset purpose and field roles; the complete AI
// and override-data layouts remain unrecovered. Retail returns at FEBB6,
// followed immediately by the independently pinned destructor FEBB7.
#include <list>
class Pathfinder { public: void rva002F462C(); };
class AIGroup;
struct Rva002FEB3AData
{
    virtual void *deleteInstance(int flags);
    char opaque04[0x100 - 4];
    Rva002FEB3AData *next;
};
class AI
{
public:
    void reset();
    void destroyGroup(AIGroup *);
private:
    char opaque00[0x10];
    Pathfinder *pathfinder;
    _STL::list<int> groups;
    Rva002FEB3AData *data;
    unsigned int nextGroupID;
    int nextFormationID;
};
void AI::reset()
{
    pathfinder->rva002F462C();
    while (data && data->next)
    {
        Rva002FEB3AData *cur = data;
        data = data->next;
        ::operator delete(cur ? cur->deleteInstance(0) : 0);
    }
    while (groups.size())
    {
        AIGroup *group = reinterpret_cast<AIGroup *>(groups.front());
        if (group)
            destroyGroup(group);
        else
            groups.pop_front();
    }
    nextGroupID = 0;
    nextFormationID = 0;
    ++nextFormationID;
}
