// cl: /MD
//
// ?rva00271496@Rva00271496@@QAEXXZ retail 0x00271496 30 bytes.
// If handle at +0x344 non-null call DisplayStringManager slot 0x3C free then
// null it. Unblocks 0x00278064. Prev/next in Common with /O1 /MD.
// Evidence: callers 0x00278083 0x0037A58D plus manager 0x00DFEAD8 plus slot 0x3C.

class DisplayString;

class DisplayStringManager
{
public:
	virtual ~DisplayStringManager() {}
	virtual void managerSlot04() = 0;
	virtual void managerSlot08() = 0;
	virtual void managerSlot0C() = 0;
	virtual void managerSlot10() = 0;
	virtual void managerSlot14() = 0;
	virtual void managerSlot18() = 0;
	virtual void managerSlot1C() = 0;
	virtual void managerSlot20() = 0;
	virtual void managerSlot24() = 0;
	virtual void managerSlot28() = 0;
	virtual void managerSlot2C() = 0;
	virtual void managerSlot30() = 0;
	virtual void managerSlot34() = 0;
	virtual DisplayString *newDisplayString();
	virtual void freeDisplayString(DisplayString *s);
};

extern DisplayStringManager *TheDisplayStringManager;

class Rva00271496
{
public:
	void rva00271496();

private:
	unsigned char m_pre[0x344];
	DisplayString *m_ptr;
};

void Rva00271496::rva00271496()
{
	if (m_ptr != 0)
		TheDisplayStringManager->freeDisplayString(m_ptr);
	m_ptr = 0;
}
