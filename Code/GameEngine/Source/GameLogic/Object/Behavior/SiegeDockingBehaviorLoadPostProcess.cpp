// cl: /DNDEBUG /MD
//
// ?loadPostProcess@SiegeDockingBehavior@@MAEXXZ, retail 0x0045A16D, 16 bytes.
// Slot 1 of ??_7SiegeDockingBehavior (slot 0 the ??_G). The body first calls
// a no-argument member at 0x00459E05 (identity not recovered; address-named
// and pinned) and then tail-calls the rowed UpdateModule::loadPostProcess.

class UpdateModule
{
protected:
	virtual void loadPostProcess();
};

class SiegeDockingBehavior : public UpdateModule
{
protected:
	virtual void loadPostProcess();

private:
	void rva00459E05();
};

// ?loadPostProcess@SiegeDockingBehavior@@MAEXXZ @0x0045A16D
void SiegeDockingBehavior::loadPostProcess()
{
	rva00459E05();
	UpdateModule::loadPostProcess();
}
