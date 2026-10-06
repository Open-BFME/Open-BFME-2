// cl: /DNDEBUG /MD
//
// ClearanceTestingSlowDeathBehavior::rva00483C69, retail 0x00483C69, 12
// bytes: slot 13 of the primary vtable 0x00C49E4C that
// ClearanceTestingSlowDeathBehavior's ctors (0x00483C35, 0x00483D50) install,
// the slot after UpdateModule::getUpdatePhase: hands out the interface the
// class carries at +0x50 (null-safe base conversion, neg/sbb/and). Which
// interface it is is not established; names by address.
class UpdateModule
{
public:
	virtual ~UpdateModule();
private:
	unsigned char m_pad04[0x50 - 4];
};

class Rva00483C69Interface
{
public:
	virtual void rva00483C69InterfaceAnchor();
};

class ClearanceTestingSlowDeathBehavior : public UpdateModule, public Rva00483C69Interface
{
public:
	virtual void slot1(); virtual void slot2(); virtual void slot3(); virtual void slot4();
	virtual void slot5(); virtual void slot6(); virtual void slot7(); virtual void slot8();
	virtual void slot9(); virtual void slot10(); virtual void slot11(); virtual void slot12();
	virtual Rva00483C69Interface *rva00483C69();
};

Rva00483C69Interface *ClearanceTestingSlowDeathBehavior::rva00483C69()
{
	return this;
}
