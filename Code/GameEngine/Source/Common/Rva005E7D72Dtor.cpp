// cl: /O1 /MD /EHsc
//
// ??1Rva005E7D72@@UAE@XZ retail 0x005E7D72 5 bytes.
// A 5-byte jmp to the rowed Rva005E7C19 destructor at 0x005E7C19, `this` unchanged: the
// destructor of a class over that base that adds nothing needing teardown and
// stores no vptr (novtable, the HordeGarrisonContain 0x0047A147 shape). Its
// deleting destructor 0x005E7F94 (rowed in Rva005E7C19Dtor.cpp) and the owned-pointer resets in
// OwnedPointerResets.cpp call it. Owner identity unrecovered (address name).

class Rva005E7C19
{
public:
	virtual ~Rva005E7C19();
};

class __declspec(novtable) Rva005E7D72 : public Rva005E7C19
{
public:
	virtual ~Rva005E7D72();
};

Rva005E7D72::~Rva005E7D72()
{
}
