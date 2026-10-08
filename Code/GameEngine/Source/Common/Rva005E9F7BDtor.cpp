// cl: /O1 /DNDEBUG /MD
//
// ??1Rva005E9F7B@@UAE@XZ retail 0x005E9F7B 5 bytes.
// A 5-byte jmp to the rowed base dtor ??1Rva0022167C at 0x0022167C (vtable
// 0x00BE6BA8), `this` unchanged: the destructor of a class over that base
// that adds nothing needing teardown and stores no vptr (novtable, the
// HordeGarrisonContain 0x0047A147 shape). Called by its slot-0 deleting
// wrapper (OpaqueScalarDeletingDtorsB17.cpp) and the unwind funclets in
// Rva007B6880Thunks.cpp. The base keeps its rowed non-virtual spelling; its
// vptr sits at +0 (the virtual slot below stands for it). Owner identity
// unrecovered (address name).

class Rva0022167C
{
public:
	~Rva0022167C();

private:
	virtual void slot0();
};

class __declspec(novtable) Rva005E9F7B : public Rva0022167C
{
public:
	virtual ~Rva005E9F7B();
};

Rva005E9F7B::~Rva005E9F7B()
{
}
