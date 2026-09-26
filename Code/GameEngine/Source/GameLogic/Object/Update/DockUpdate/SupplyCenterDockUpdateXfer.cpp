// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?xfer@SupplyCenterDockUpdate@@MAEXPAVXfer@@@Z, retail 0x004A0E2C, 27 bytes.
// Virtual slot 3 (offset 0x0C) of vtable 0x00851BDC (class of rowed ctor
// ??0SupplyCenterDockUpdate@@QAE@PAVThing@@PBVModuleData@@@Z in
// SupplyCenterDockUpdateConstructor.cpp). Version1 via rowed 0x53EE then base
// DockUpdate xfer via rowed 0x58A410 (landed this session). Layout is single
// inheritance from DockUpdate per ZH donor (no adjustment, mov esi ecx plus
// mov ecx esi shape). Donor is ZH SupplyCenterDockUpdate::xfer (Version plus
// base). Recipe is DockUpdateXfer slot-3 pattern minus IsLightCRC.

class Xfer
{
public:
	void Version1();
};

class Thing;
class ModuleData;

class DockUpdate
{
protected:
	virtual void xfer(Xfer *xfer);
};

class SupplyCenterDockUpdate : public DockUpdate
{
protected:
	virtual void xfer(Xfer *xfer);
};

void SupplyCenterDockUpdate::xfer(Xfer *xfer)
{
	xfer->Version1();
	DockUpdate::xfer(xfer);
}
