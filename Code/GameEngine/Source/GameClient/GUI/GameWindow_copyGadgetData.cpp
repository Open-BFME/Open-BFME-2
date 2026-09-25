// cl: /Os /DNDEBUG /MD

// GameWindow gadget-duplication snapshot, retail 0x003146DC (126B).
// BFME2-new code (no Zero Hour / BFME1 donor): the LivingWorld/Bink gadget
// copier (caller 0x00411755) snapshots a source window into a 0x34-byte
// creation block that createGadget (0x00316518) consumes. The wrapper
// (0x003174CB) zeroes the block with the VehicleCurveClass ArcInfoStruct
// ctor, stores the owner at +0x00, and this method fills the rest:
//
//   +0x04 status, +0x10/+0x14 size, +0x18 vtable-slot-7 result,
//   +0x1C/+0x20/+0x24/+0x28/+0x2C callbacks at +0x1E4/+0x1E0/+0x1E8/+0x1EC/+0x1F0,
//   +0x30 address of this window's instance data.
//
// With flag set, the non-transferable linkage is cleared: the instance
// owner's m_owner (+0x14) plus the three trailing instance-data pointers
// (+0x19C/+0x1A0/+0x1A4, text/tooltip/video per the "cannot be transferred"
// comment in the reference WinInstanceData.h).
//
// The slot-7 virtual's identity is unwitnessed (indirect call through
// [eax+0x1C] emits no relocation, so any 8-virtual layout matches); it is
// declared as a descriptive pure virtual and the class is never constructed
// in this TU, so no vtable is emitted.

class GameWindow;

struct WinInstanceData
{
	unsigned char m_pad0[0x14];
	GameWindow *m_owner;
	unsigned char m_pad1[0x19C - 0x18];
	void *m_tail0;
	void *m_tail1;
	void *m_tail2;
};

struct GadgetCopyBlock
{
	GameWindow *m_owner;
	int m_status;
	int m_unk08;
	int m_unk0C;
	int m_sizeX;
	int m_sizeY;
	void *m_copyTag;
	void *m_system;
	void *m_input;
	void *m_draw;
	void *m_tooltip;
	void *m_extra;
	WinInstanceData *m_instData;
};

class GameWindow
{
public:
	virtual void _slot000() = 0;
	virtual void _slot001() = 0;
	virtual void _slot002() = 0;
	virtual void _slot003() = 0;
	virtual void _slot004() = 0;
	virtual void _slot005() = 0;
	virtual void _slot006() = 0;
	virtual void *winGetCopyTag() = 0;

	void copyGadgetData_Rva003146DC(GadgetCopyBlock *block, bool clearLinkage);

private:
	void *m_anchor;
	int m_status;
	int m_sizeX;
	int m_sizeY;
	unsigned char m_pad0[0x30 - 0x14];
	WinInstanceData m_instData;
	void *m_inputData;
	void *m_inputExtra;
	void *m_input;
	void *m_system;
	void *m_draw;
	void *m_tooltip;
	void *m_extra;
};

void GameWindow::copyGadgetData_Rva003146DC(GadgetCopyBlock *block, bool clearLinkage)
{
	block->m_copyTag = winGetCopyTag();
	block->m_status = m_status;
	block->m_sizeX = m_sizeX;
	block->m_sizeY = m_sizeY;
	WinInstanceData *inst = &m_instData;
	block->m_instData = inst;
	block->m_input = m_input;
	block->m_system = m_system;
	block->m_draw = m_draw;
	block->m_tooltip = m_tooltip;
	block->m_extra = m_extra;
	if (clearLinkage)
	{
		inst->m_owner = 0;
		block->m_instData->m_tail0 = 0;
		block->m_instData->m_tail1 = 0;
		block->m_instData->m_tail2 = 0;
	}
}
