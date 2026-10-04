// cl: /O1 /DNDEBUG /MD
//
// SpecialPowerTimerRefreshSpecialPower primary slot 13 (vtable 0x00BEFDB4),
// retail 0x004C38B3 (29 bytes): the SpecialPowerModule slot-13 base 0x00493EA7
// (the slot-13 entry of 23 special-power vtables, SpecialPowerModule's own
// 0x00C4E868 among them; it works on the Object it is given, pinned by
// address), then the rowed Object::rva0028B72A on that Object. Named by the
// base's address.
template <int N> class BitFlags
{
public:
	bool any() const;
private:
	unsigned int m_bits[1];
};
class Object
{
public:
	void rva0028B72A() const;
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
class SpecialPowerTimerRefreshSpecialPower : public SpecialPowerModule
{
public:
	virtual void rva00493EA7(Object *obj, int value, const BitFlags<11> *disabled);
};
void SpecialPowerTimerRefreshSpecialPower::rva00493EA7(Object *obj, int value, const BitFlags<11> *disabled)
{
	SpecialPowerModule::rva00493EA7(obj, value, disabled);
	obj->rva0028B72A();
}
