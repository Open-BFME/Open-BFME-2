// cl: /DNDEBUG /MD
//
// ?loadPostProcess@PartTheHeavensUpdate@@MAEXXZ, retail 0x004ACBE8, 16 bytes.
// Slot 1 of vftable 0x00C54DA4 (??_7PartTheHeavensUpdate, slot 0 is the rowed ??_G,
// slot 3 the xfer). The body chains to the rowed UpdateModule::loadPostProcess
// and then tail-calls a no-argument member at 0x004ACADA (identity not
// recovered; address-named and pinned), the usual ZH loadPostProcess override
// shape: base first, then rebuild transient state.

class UpdateModule
{
protected:
	virtual void loadPostProcess();
};

class PartTheHeavensUpdate : public UpdateModule
{
protected:
	virtual void loadPostProcess();

private:
	void rva004ACADA();
};

// ?loadPostProcess@PartTheHeavensUpdate@@MAEXXZ @0x004ACBE8
void PartTheHeavensUpdate::loadPostProcess()
{
	UpdateModule::loadPostProcess();
	rva004ACADA();
}
