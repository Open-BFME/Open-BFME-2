// cl: /O1 /DNDEBUG /MD
// DeletionUpdate::xfer shard.
//
// Retail 0x488483 is a frameless 39B three-call xfer:
//
//     xfer->Version1();              // 0-arg thiscall, rowed 0x53EE
//     UpdateModule::xfer(xfer);      // direct call, rowed 0x44DF9F
//     xfer->xferUnsignedInt(&m_dieFrame);  // virtual slot 0x78
//
// The home TU (DeletionUpdate.cpp) carries the ZH-donor xfer instead
// (xferVersion 2-arg temp plus slot-0x44 member call), which frames and
// schedules differently, so the body lives here with TU-local models and
// the home def is removed in the same commit (else link dupe).
// Identity: vtable 0x84B344 holds rowed update@0x48846F, this body, then
// rowed poolkey@0x48838B; table 0xBF17BC and factory news fit the class.
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
	virtual void xferUnsignedInt(unsigned int *value);
	void Version1();
};
class __declspec(novtable) UpdateModule
{
public:
	char m_pad[0x1C];
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);
};
class __declspec(novtable) DeletionUpdate : public UpdateModule
{
public:
	unsigned int m_dieFrame;
protected:
	virtual void xfer(Xfer *xfer);
};
void DeletionUpdate::xfer(Xfer *xfer)
{
	xfer->Version1();
	UpdateModule::xfer(xfer);
	xfer->xferUnsignedInt(&m_dieFrame);
}
