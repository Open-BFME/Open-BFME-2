// cl: /O1 /MD
//
// ??1Rva000AD71D@@UAE@XZ retail 0x000AD71D 5 bytes.
// A 5-byte jmp to the rowed Rva00328A75 destructor at 0x00328A75, `this` unchanged: the
// destructor of a class over that base that adds nothing needing teardown and
// stores no vptr (novtable, the HordeGarrisonContain 0x0047A147 shape). Its
// deleting destructor 0x000ADE29 (rowed in Rva000AD6F4Members.cpp) and the owned-pointer resets in
// OwnedPointerResets.cpp call it. Owner identity unrecovered (address name).

class Rva00328A75
{
public:
	virtual ~Rva00328A75();
};

class __declspec(novtable) Rva000AD71D : public Rva00328A75
{
public:
	virtual ~Rva000AD71D();
};

Rva000AD71D::~Rva000AD71D()
{
}
