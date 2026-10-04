// cl: /O1 /DNDEBUG /MD
//
// UntamedAllegianceSpecialPower primary slot 13 (vtable 0x00C5E0E4), retail
// 0x004C7BB0 (83 bytes): nothing for an Object with status 0x39; otherwise
// the SpecialPowerModule slot-13 base 0x00493EA7 (pinned by address), then
// the Object is taken over for our Object: the pinned
// Object::rva00298979(ours, false), Object 0x002930A9 with 0 (pinned by
// address; it starts from the Object's producer, +0x78), the rowed
// setProducer(ours) and status 0x3E cleared. Named by the base's address.
template <int N> class BitFlags
{
public:
	bool any() const;
private:
	unsigned int m_bits[1];
};
enum ObjectStatusTypes
{
	OBJECT_STATUS_39 = 0x39,
	OBJECT_STATUS_3E = 0x3e
};
class Object
{
public:
	bool testStatus(ObjectStatusTypes status) const;
	void rva00298979(Object *source, bool flag);
	void rva002930A9(int value);
	void setProducer(Object *producer);
	void setStatus(ObjectStatusTypes status, bool set);
};
class ModuleData;
class SpecialPowerModule
{
public:
	virtual ~SpecialPowerModule();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void rva00493EA7(Object *obj, int value, const BitFlags<11> *disabled);
protected:
	const ModuleData *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
};
class UntamedAllegianceSpecialPower : public SpecialPowerModule
{
public:
	virtual void rva00493EA7(Object *obj, int value, const BitFlags<11> *disabled);
};
void UntamedAllegianceSpecialPower::rva00493EA7(Object *obj, int value, const BitFlags<11> *disabled)
{
	if (obj->testStatus(OBJECT_STATUS_39))
		return;
	SpecialPowerModule::rva00493EA7(obj, value, disabled);
	Object *self = m_object;
	obj->rva00298979(self, false);
	obj->rva002930A9(0);
	obj->setProducer(self);
	obj->setStatus(OBJECT_STATUS_3E, false);
}
