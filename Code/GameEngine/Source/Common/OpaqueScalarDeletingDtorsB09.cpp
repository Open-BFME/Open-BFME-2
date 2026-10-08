// cl: /O1 /GX /DNDEBUG /MD /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /Ireference/shims/moduledata
//
// Opaque scalar deleting destructors, batch B09: the 28-byte wrappers of the
// classes OpaqueScalarDeletingDtors.cpp modelled with a stand-in three-vptr
// MI layout, moved here because their this-adjusting deleting-destructor
// thunks (sub ecx, N; jmp to the wrapper) prove the real secondary-base
// offsets. Each class now carries exactly those bases (a virtual destructor
// at each proven +N) so this unit emits the thunks beside the wrapper. The
// 51D93 and 5813E destructors are recovered below using the canonical audio
// prefix. Other destructors remain declared so their wrapper calls resolve
// to their pins in reverse/symbols.csv; the dummy tag constructors (no retail
// counterpart) only make this TU emit each vtable. Owner identities are not
// recovered and the declarations model no layout beyond those offsets
// (docs/reconstruction/deleting-destructor-identity-audit.md).
//
//   wrapper     dtor        thunks (offset @ address)
//   0x0004C97F  0x0004C743  +0xC @ 0x0004C912
//   0x0004CF47  0x0004CE36  +0xC @ 0x0004CE2E
//   0x00050109  0x0004FA1F  +0x4 @ 0x0004FA17
//   0x000510B3  0x0005109D  +0xC @ 0x00051C9A
//   0x00051DB0  0x00051D93  +0x88 @ 0x00051D57
//   0x00058122  0x0005813E  +0x88 @ 0x00051DEE
//   0x00061AA1  0x00060FE2  +0xC @ 0x0005D41D
//   0x00062E8D  0x00062AF7  +0x4 @ 0x00062E6A
//   0x0006D58B  0x0006D0D7  +0x8 @ 0x0006D05A, +0xC8 @ 0x0006D062
//   0x0006DE21  0x0006DD51  +0x8 @ 0x0006DD67
//   0x0006F24A  0x0006ED6F  +0x108 @ 0x0006F02E
//   0x0006FB2F  0x0006F7BD  +0x108 @ 0x0006F796
//   0x0007C5B9  0x0007C454  +0x8 @ 0x0007C3FC
//   0x0008230D  0x00082140  +0x4 @ 0x000822FD, +0xC @ 0x00082305
//   0x0008DE5E  0x0008BD5E  +0xB4 @ 0x0008BD43
//   0x0008E533  0x0008E4EC  +0x8 @ 0x0008E52B
//   0x0008F379  0x0008F00D  +0xC @ 0x0008F371
//   0x00092123  0x0009203A  +0x4 @ 0x00092032

#include "Common/BfmeAudioEventPrefix136.h"
#include "Common/Snapshot.h"

struct EmitVtableTag;

class Rva004C743Base0
{
public:
	virtual ~Rva004C743Base0();
private:
	char m_unmodelled[0x8];
};

// Secondary base at +0xC: the this-adjusting deleting-destructor thunk
// (sub ecx, 0xC) at 0x0004C912 in its vtable is target evidence for it.
class Rva004C743BaseC
{
public:
	virtual ~Rva004C743BaseC();
};
class Rva004C743 : public Rva004C743Base0, public Rva004C743BaseC
{
public:
	Rva004C743(EmitVtableTag *);
public:
	virtual ~Rva004C743();
};

// ?<Rva004C743::Rva004C743> absent-from-retail
Rva004C743::Rva004C743(EmitVtableTag *)
{
}

class Rva004CE36Base0
{
public:
	virtual ~Rva004CE36Base0();
private:
	char m_unmodelled[0x8];
};

// Secondary base at +0xC: the this-adjusting deleting-destructor thunk
// (sub ecx, 0xC) at 0x0004CE2E in its vtable is target evidence for it.
class Rva004CE36BaseC
{
public:
	virtual ~Rva004CE36BaseC();
};
class Rva004CE36 : public Rva004CE36Base0, public Rva004CE36BaseC
{
public:
	Rva004CE36(EmitVtableTag *);
public:
	virtual ~Rva004CE36();
};

// ?<Rva004CE36::Rva004CE36> absent-from-retail
Rva004CE36::Rva004CE36(EmitVtableTag *)
{
}

class Rva004FA1FBase0
{
public:
	virtual ~Rva004FA1FBase0();
};

// Secondary base at +0x4: the this-adjusting deleting-destructor thunk
// (sub ecx, 0x4) at 0x0004FA17 in its vtable is target evidence for it.
class Rva004FA1FBase4
{
public:
	virtual ~Rva004FA1FBase4();
};
class Rva004FA1F : public Rva004FA1FBase0, public Rva004FA1FBase4
{
public:
	Rva004FA1F(EmitVtableTag *);
public:
	virtual ~Rva004FA1F();
};

// ?<Rva004FA1F::Rva004FA1F> absent-from-retail
Rva004FA1F::Rva004FA1F(EmitVtableTag *)
{
}

// Native5109D..510B3: the +C Snapshot base is proved by rowed
// adjusting thunk51C9A. Its inline destructor restores canonical BBB554;
// the primary base tail-calls the rowed14B destructor1B4E74. Primary
// fields are opaque here; that provider accesses its owned word at +8.
class GameEngineDeletingBase
{
public:
    GameEngineDeletingBase();
    virtual ~GameEngineDeletingBase();
private:
    char m_unknown04[8];
};
class Rva005109D : public GameEngineDeletingBase, public Snapshot
{
public:
    Rva005109D(EmitVtableTag *);
    __declspec(noinline) virtual ~Rva005109D();
};

// ?<Rva005109D::Rva005109D> absent-from-retail
Rva005109D::Rva005109D(EmitVtableTag *)
{
}

// Native51D62 copies the canonical 136B event prefix, then initializes
// the secondary virtual base at +88 and its counter at +8C. Native51D93
// restores both derived tables, the secondary base table BC5128, then
// tail-calls the canonical prefix destructor2D9A43. The one-slot secondary
// table BC5128 belongs to the already rowed Rva00051E4D deleting destructor.
// Release_Ref50ED3 passes its +4 count to InterlockedDecrement; the native
// constructor clears that count after the base vptr is initialized.
class Rva00051E4D
{
public:
    Rva00051E4D() { m_count = 0; }
    virtual ~Rva00051E4D() {}
private:
    volatile int m_count;
};
class Rva0051D93 : public BfmeAudioEventPrefix136, public Rva00051E4D
{
public:
    Rva0051D93(EmitVtableTag *);
    Rva0051D93(const OpaqueRefElement4 &reference, int value30);
    Rva0051D93(const BfmeAudioEventPrefix136 &source);
    __declspec(noinline) virtual ~Rva0051D93();
};

// ?<Rva0051D93::Rva0051D93> absent-from-retail
Rva0051D93::Rva0051D93(EmitVtableTag *tag)
    : BfmeAudioEventPrefix136(*reinterpret_cast<OpaqueRefElement4 *>(tag), 0)
{
}

// Native51D22..51D57 RET8; caller51DF9 passes the event reference and zero.
// Prefix constructor2D97D6 then secondary base vptr/counter initialization.
Rva0051D93::Rva0051D93(const OpaqueRefElement4 &reference, int value30)
    : BfmeAudioEventPrefix136(reference, value30)
{
}

// Native51D62..51D93 RET4; callers51DD3, 5F830 and 5C92CC. The prefix copy
// constructor2D99E3, then the secondary base vptr with a fresh zero count.
Rva0051D93::Rva0051D93(const BfmeAudioEventPrefix136 &source)
    : BfmeAudioEventPrefix136(source)
{
}

Rva0051D93::~Rva0051D93()
{
}

class AudioManager;
extern AudioManager *TheAudio;
class MilesAudioManager
{
public:
    void rva00057948(const void *input);
};

// Native5813E..5818B (77B): both derived vptrs, nullable TheAudio,
// same-this callback57948 and the verified51D93 base destructor. Table
// BC5324 owns rowed deleting dtor58122; secondary BC5320 owns rowed
// -88 adjusting thunk51DEE. No additional data fields are accessed.
class Rva005813E : public Rva0051D93
{
public:
    Rva005813E(EmitVtableTag *);
    Rva005813E(const BfmeAudioEventPrefix136 &source);
    __declspec(noinline) virtual ~Rva005813E();
};

// ?<Rva005813E::Rva005813E> absent-from-retail
Rva005813E::Rva005813E(EmitVtableTag *tag) : Rva0051D93(tag)
{
}

// Native51DCC..51DEE RET4; its one caller5289C wraps a fresh 0x90-byte copy
// of the played event (the AudioManager::addAudioEvent copy in GeneralsMD).
Rva005813E::Rva005813E(const BfmeAudioEventPrefix136 &source) : Rva0051D93(source)
{
}

Rva005813E::~Rva005813E()
{
    if (TheAudio)
        reinterpret_cast<MilesAudioManager *>(TheAudio)->rva00057948(this);
}

class Rva0060FE2Base0
{
public:
	virtual ~Rva0060FE2Base0();
private:
	char m_unmodelled[0x8];
};

// Secondary base at +0xC: the this-adjusting deleting-destructor thunk
// (sub ecx, 0xC) at 0x0005D41D in its vtable is target evidence for it.
class Rva0060FE2BaseC
{
public:
	virtual ~Rva0060FE2BaseC();
};
class Rva0060FE2 : public Rva0060FE2Base0, public Rva0060FE2BaseC
{
public:
	Rva0060FE2(EmitVtableTag *);
public:
	virtual ~Rva0060FE2();
};

// ?<Rva0060FE2::Rva0060FE2> absent-from-retail
Rva0060FE2::Rva0060FE2(EmitVtableTag *)
{
}

class Rva0062AF7Base0
{
public:
	virtual ~Rva0062AF7Base0();
};

// Secondary base at +0x4: the this-adjusting deleting-destructor thunk
// (sub ecx, 0x4) at 0x00062E6A in its vtable is target evidence for it.
class Rva0062AF7Base4
{
public:
	virtual ~Rva0062AF7Base4();
};
class Rva0062AF7 : public Rva0062AF7Base0, public Rva0062AF7Base4
{
public:
	Rva0062AF7(EmitVtableTag *);
public:
	virtual ~Rva0062AF7();
};

// ?<Rva0062AF7::Rva0062AF7> absent-from-retail
Rva0062AF7::Rva0062AF7(EmitVtableTag *)
{
}

class Rva006D0D7Base0
{
public:
	virtual ~Rva006D0D7Base0();
private:
	char m_unmodelled[0x4];
};

// Secondary base at +0x8: the this-adjusting deleting-destructor thunk
// (sub ecx, 0x8) at 0x0006D05A in its vtable is target evidence for it.
class Rva006D0D7Base8
{
public:
	virtual ~Rva006D0D7Base8();
private:
	char m_unmodelled[0xBC];
};

// Secondary base at +0xC8: the this-adjusting deleting-destructor thunk
// (sub ecx, 0xC8) at 0x0006D062 in its vtable is target evidence for it.
class Rva006D0D7BaseC8
{
public:
	virtual ~Rva006D0D7BaseC8();
};
class Rva006D0D7 : public Rva006D0D7Base0, public Rva006D0D7Base8, public Rva006D0D7BaseC8
{
public:
	Rva006D0D7(EmitVtableTag *);
public:
	virtual ~Rva006D0D7();
};

// ?<Rva006D0D7::Rva006D0D7> absent-from-retail
Rva006D0D7::Rva006D0D7(EmitVtableTag *)
{
}

class Rva006DD51Base0
{
public:
	virtual ~Rva006DD51Base0();
private:
	char m_unmodelled[0x4];
};

// Secondary base at +0x8: the this-adjusting deleting-destructor thunk
// (sub ecx, 0x8) at 0x0006DD67 in its vtable is target evidence for it.
class Rva006DD51Base8
{
public:
	virtual ~Rva006DD51Base8();
};
class Rva006DD51 : public Rva006DD51Base0, public Rva006DD51Base8
{
public:
	Rva006DD51(EmitVtableTag *);
public:
	virtual ~Rva006DD51();
};

// ?<Rva006DD51::Rva006DD51> absent-from-retail
Rva006DD51::Rva006DD51(EmitVtableTag *)
{
}

class Rva006ED6FBase0
{
public:
	virtual ~Rva006ED6FBase0();
private:
	char m_unmodelled[0x104];
};

// Secondary base at +0x108: the this-adjusting deleting-destructor thunk
// (sub ecx, 0x108) at 0x0006F02E in its vtable is target evidence for it.
class Rva006ED6FBase108
{
public:
	virtual ~Rva006ED6FBase108();
};
class Rva006ED6F : public Rva006ED6FBase0, public Rva006ED6FBase108
{
public:
	Rva006ED6F(EmitVtableTag *);
public:
	virtual ~Rva006ED6F();
};

// ?<Rva006ED6F::Rva006ED6F> absent-from-retail
Rva006ED6F::Rva006ED6F(EmitVtableTag *)
{
}

class Rva006F7BDBase0
{
public:
	virtual ~Rva006F7BDBase0();
private:
	char m_unmodelled[0x104];
};

// Secondary base at +0x108: the this-adjusting deleting-destructor thunk
// (sub ecx, 0x108) at 0x0006F796 in its vtable is target evidence for it.
class Rva006F7BDBase108
{
public:
	virtual ~Rva006F7BDBase108();
};
class Rva006F7BD : public Rva006F7BDBase0, public Rva006F7BDBase108
{
public:
	Rva006F7BD(EmitVtableTag *);
public:
	virtual ~Rva006F7BD();
};

// ?<Rva006F7BD::Rva006F7BD> absent-from-retail
Rva006F7BD::Rva006F7BD(EmitVtableTag *)
{
}

class Rva007C454Base0
{
public:
	virtual ~Rva007C454Base0();
private:
	char m_unmodelled[0x4];
};

// Secondary base at +0x8: the this-adjusting deleting-destructor thunk
// (sub ecx, 0x8) at 0x0007C3FC in its vtable is target evidence for it.
class Rva007C454Base8
{
public:
	virtual ~Rva007C454Base8();
};
class Rva007C454 : public Rva007C454Base0, public Rva007C454Base8
{
public:
	Rva007C454(EmitVtableTag *);
public:
	virtual ~Rva007C454();
};

// ?<Rva007C454::Rva007C454> absent-from-retail
Rva007C454::Rva007C454(EmitVtableTag *)
{
}

class Rva0082140Base0
{
public:
	virtual ~Rva0082140Base0();
};

// Secondary base at +0x4: the this-adjusting deleting-destructor thunk
// (sub ecx, 0x4) at 0x000822FD in its vtable is target evidence for it.
class Rva0082140Base4
{
public:
	virtual ~Rva0082140Base4();
private:
	char m_unmodelled[0x4];
};

// Secondary base at +0xC: the this-adjusting deleting-destructor thunk
// (sub ecx, 0xC) at 0x00082305 in its vtable is target evidence for it.
class Rva0082140BaseC
{
public:
	virtual ~Rva0082140BaseC();
};
class Rva0082140 : public Rva0082140Base0, public Rva0082140Base4, public Rva0082140BaseC
{
public:
	Rva0082140(EmitVtableTag *);
public:
	virtual ~Rva0082140();
};

// ?<Rva0082140::Rva0082140> absent-from-retail
Rva0082140::Rva0082140(EmitVtableTag *)
{
}

class Rva008BD5EBase0
{
public:
	virtual ~Rva008BD5EBase0();
private:
	char m_unmodelled[0xB0];
};

// Secondary base at +0xB4: the this-adjusting deleting-destructor thunk
// (sub ecx, 0xB4) at 0x0008BD43 in its vtable is target evidence for it.
class Rva008BD5EBaseB4
{
public:
	virtual ~Rva008BD5EBaseB4();
};
class Rva008BD5E : public Rva008BD5EBase0, public Rva008BD5EBaseB4
{
public:
	Rva008BD5E(EmitVtableTag *);
public:
	virtual ~Rva008BD5E();
};

// ?<Rva008BD5E::Rva008BD5E> absent-from-retail
Rva008BD5E::Rva008BD5E(EmitVtableTag *)
{
}

class Rva008E4ECBase0
{
public:
	virtual ~Rva008E4ECBase0();
private:
	char m_unmodelled[0x4];
};

// Secondary base at +0x8: the this-adjusting deleting-destructor thunk
// (sub ecx, 0x8) at 0x0008E52B in its vtable is target evidence for it.
class Rva008E4ECBase8
{
public:
	virtual ~Rva008E4ECBase8();
};
class Rva008E4EC : public Rva008E4ECBase0, public Rva008E4ECBase8
{
public:
	Rva008E4EC(EmitVtableTag *);
public:
	virtual ~Rva008E4EC();
};

// ?<Rva008E4EC::Rva008E4EC> absent-from-retail
Rva008E4EC::Rva008E4EC(EmitVtableTag *)
{
}

class Rva008F00DBase0
{
public:
	virtual ~Rva008F00DBase0();
private:
	char m_unmodelled[0x8];
};

// Secondary base at +0xC: the this-adjusting deleting-destructor thunk
// (sub ecx, 0xC) at 0x0008F371 in its vtable is target evidence for it.
class Rva008F00DBaseC
{
public:
	virtual ~Rva008F00DBaseC();
};
class Rva008F00D : public Rva008F00DBase0, public Rva008F00DBaseC
{
public:
	Rva008F00D(EmitVtableTag *);
public:
	virtual ~Rva008F00D();
};

// ?<Rva008F00D::Rva008F00D> absent-from-retail
Rva008F00D::Rva008F00D(EmitVtableTag *)
{
}

class Rva009203ABase0
{
public:
	virtual ~Rva009203ABase0();
};

// Secondary base at +0x4: the this-adjusting deleting-destructor thunk
// (sub ecx, 0x4) at 0x00092032 in its vtable is target evidence for it.
class Rva009203ABase4
{
public:
	virtual ~Rva009203ABase4();
};
class Rva009203A : public Rva009203ABase0, public Rva009203ABase4
{
public:
	Rva009203A(EmitVtableTag *);
public:
	virtual ~Rva009203A();
};

// ?<Rva009203A::Rva009203A> absent-from-retail
Rva009203A::Rva009203A(EmitVtableTag *)
{
}
