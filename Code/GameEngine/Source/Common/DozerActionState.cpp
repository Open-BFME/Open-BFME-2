// cl: /MD /EHsc
// ??1Rva00488D5C@@UAE@XZ retail 0x00488D5C 79B
// Own vptr C4B5C8; under EH state 0 the object at +0x24 is deleted through its
// slot-0 deleting dtor with flag 0 and the global ??3@YAXPAX@Z (a
// global-scope delete) and cleared; then the rowed base dtor
// ??1OutwardEmissionVelocityInfo@FXParticleSystem@@UAE@XZ 0x0049B47C.
// Names address-derived.

class Xfer;
class State
{
public:
	virtual ~State();
private:
	unsigned char m_pad04[0x20 - 4];
};

class Rva00488D5COwned
{
public:
	virtual ~Rva00488D5COwned();
};

class DozerActionState : public State
{
public:
	virtual ~DozerActionState();

	virtual void loadPostProcess() {}
	virtual const char *GetSnapshotName() const;
protected:
	virtual void xfer(Xfer *);
public:
	virtual int rva00488906();
	virtual void onExit(int);
	virtual void rva004888F8();
	virtual void slot07() {}
	virtual bool slot08() const { return false; }
	virtual bool slot09() const { return false; }
	virtual bool slot10() const { return false; }
	virtual bool slot11() const { return false; }
	virtual bool slot12() const { return false; }
	virtual bool slot13() const { return false; }
	virtual bool slot14() const { return false; }
	virtual bool slot15() const { return false; }
	virtual void slot16() {}

private:
	int m_value;
	Rva00488D5COwned *m_owned; // +0x24
};

DozerActionState::~DozerActionState()
{
	::delete m_owned;
	m_owned = 0;
}
