// cl: /DNDEBUG /MD
// DeletionUpdate::xfer shard.
//
// Retail 0x488483 is a frameless 39B three-call xfer:
//
//     xfer->Version1();              // 0-arg thiscall, rowed 0x53EE
//     UpdateModule::xfer(xfer);      // direct call, rowed 0x44DF9F
//     *xfer == m_dieFrame;           // unsigned-int overload, slot 0x78
//
// The home TU (DeletionUpdate.cpp) carries the ZH-donor xfer instead
// (xferVersion 2-arg temp plus slot-0x44 member call), which frames and
// schedules differently, so the body lives here with TU-local models and
// the home def is removed in the same commit (else link dupe).
// Identity: vtable 0x84B344 holds rowed update@0x48846F, this body, then
// rowed poolkey@0x48838B; table 0xBF17BC and factory news fit the class.
#include "UpdateXferTypes.h"
#include "../../../../Include/Common/BfmeXfer.h"
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
	*xfer == m_dieFrame;
}
