// cl: /O1 /DNDEBUG /MD
//
// ??_GTerrainLogic@@UAEPAXI@Z, retail 0x00285177 (28 bytes): slot 0
// of vtable 0x00BFB2C8, whose slot-2 name getter returns "TerrainLogic" (the only
// vtable using that getter). Scalar deleting destructor: calls the
// destructor at 0x0028418A and then the global operator delete when bit 0 of
// the flags is set. That destructor re-stores vtable 0x00BFB2C8, which
// identifies it as TerrainLogic::~TerrainLogic (pinned in reverse/symbols.csv beside the
// opaque ??1Rva0028418A pin that the derived W3D destructor tail-calls).
// Class shape from Zero Hour's GameLogic/TerrainLogic.h (public virtual ~TerrainLogic).
// BFME 2's form frees through the global operator delete.
// The destructor is declared, not defined, so the call resolves to the pin;
// the dummy tag constructor (no retail counterpart) only makes this TU emit
// the vtable and with it the deleting destructor.

struct EmitVtableTag;

// The this-adjusting deleting-destructor thunk (sub ecx, 0x4) in the
// secondary vtable proves a second base with a virtual destructor at +0x4;
// these two bases model only that.
class TerrainLogicBase0
{
public:
	virtual ~TerrainLogicBase0();
};

class TerrainLogicBase4
{
public:
	virtual ~TerrainLogicBase4();
};

class TerrainLogic : public TerrainLogicBase0, public TerrainLogicBase4
{
public:
	TerrainLogic(EmitVtableTag *);
	virtual ~TerrainLogic();
};

// ?<TerrainLogic::TerrainLogic> absent-from-retail
TerrainLogic::TerrainLogic(EmitVtableTag *)
{
}
