// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?xfer@SupplyWarehouseDockUpdate@@MAEXPAVXfer@@@Z, retail 0x004A7D7B, 42 bytes.
// Virtual slot 3 (offset 0x0C) of vtable 0x00853790 (class of rowed dtor
// ??1Rva004A7D55@@UAE@XZ in Rva0058A0F4Derived.cpp). Version1 via rowed
// 0x53EE then base DockUpdate xfer via rowed 0x58A410 then int at +0x88 via
// Xfer slot 0x7C. Layout is single inheritance from DockUpdate per ZH donor
// (no adjustment) with int m_boxesStored at +0x88 giving 0x8C total (factory
// news 0x8C per SupplyWarehouseDockUpdateFriendNew.cpp). Donor is ZH
// SupplyWarehouseDockUpdate::xfer (Version plus base plus xferInt). Recipe is
// DeletionUpdateXfer slot-3 pattern with DockUpdate base.

class Xfer
{
public:
	virtual void _slot00();
	virtual void _slot01();
	virtual void _slot02();
	virtual void _slot03();
	virtual void _slot04();
	virtual void _slot05();
	virtual void _slot06();
	virtual void _slot07();
	virtual void _slot08();
	virtual void _slot09();
	virtual void _slot10();
	virtual void _slot11();
	virtual void _slot12();
	virtual void _slot13();
	virtual void _slot14();
	virtual void _slot15();
	virtual void _slot16();
	virtual void _slot17();
	virtual void _slot18();
	virtual void _slot19();
	virtual void _slot20();
	virtual void _slot21();
	virtual void _slot22();
	virtual void _slot23();
	virtual void _slot24();
	virtual void _slot25();
	virtual void _slot26();
	virtual void _slot27();
	virtual void _slot28();
	virtual void _slot29();
	virtual void _slot30();
	virtual void xferInt(int *value);
	void Version1();
};

class __declspec(novtable) DockUpdate
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	char m_pad[0x88 - 4];
};

class SupplyWarehouseDockUpdate : public DockUpdate
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	int m_boxesStored;
};

void SupplyWarehouseDockUpdate::xfer(Xfer *xfer)
{
	xfer->Version1();
	DockUpdate::xfer(xfer);
	xfer->xferInt(&m_boxesStored);
}
