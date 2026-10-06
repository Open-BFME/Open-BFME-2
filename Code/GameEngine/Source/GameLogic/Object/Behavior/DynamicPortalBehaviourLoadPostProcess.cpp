// cl: /DNDEBUG /MD
//
// ?loadPostProcess@DynamicPortalBehaviour@@MAEXXZ, retail 0x00461274, 16 bytes.
// Slot 1 of vftable 0x00C428C4 (??_7DynamicPortalBehaviour, slot 0 is the rowed ??_G,
// slot 3 the xfer). The body chains to the rowed UpdateModule::loadPostProcess
// and then tail-calls a no-argument member at 0x00461257 (identity not
// recovered; address-named and pinned), the usual ZH loadPostProcess override
// shape: base first, then rebuild transient state.

class UpdateModule
{
protected:
	virtual void loadPostProcess();
};

class DynamicPortalBehaviour : public UpdateModule
{
protected:
	virtual void loadPostProcess();

private:
	void rva00461257();
};

// ?loadPostProcess@DynamicPortalBehaviour@@MAEXXZ @0x00461274
void DynamicPortalBehaviour::loadPostProcess()
{
	UpdateModule::loadPostProcess();
	rva00461257();
}
