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

class Rva0045A1B6;

class SiegeDockingBehavior : public UpdateModule
{
protected:
	virtual void loadPostProcess();

private:
	friend class Rva0045A1B6;
	void rva00459E05();
	void rva00459B68() const;
};

// ?loadPostProcess@SiegeDockingBehavior@@MAEXXZ @0x0045A16D
void SiegeDockingBehavior::loadPostProcess()
{
	rva00459E05();
	UpdateModule::loadPostProcess();
}

class Rva0045A1B6
{
public:
	unsigned int rva0045A1B6();

private:
	char m_pad00[0x20];
	bool m_initialized;
};

extern int g_00DBA4E4;

// Target Ghidra boundary: 35B at 0x0045A1B6. Both direct calls receive
// this-0x10: 0x00459E05 on the clear-flag path and 0x00459B68 otherwise.
// The byte at this+0x20 gates those paths and is set after initialization;
// the return word is loaded from absolute address 0x00DBA4E4. The interface
// identity and returned word's meaning remain unresolved.
// ?rva0045A1B6@Rva0045A1B6@@QAEIXZ
unsigned int Rva0045A1B6::rva0045A1B6()
{
	SiegeDockingBehavior *behavior = (SiegeDockingBehavior *)((char *)this - 0x10);
	if (!m_initialized)
	{
		behavior->rva00459E05();
		m_initialized = true;
	}
	else
	{
		behavior->rva00459B68();
	}
	return g_00DBA4E4;
}
