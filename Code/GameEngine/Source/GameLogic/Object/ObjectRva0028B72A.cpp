// cl: /DNDEBUG /MD
// ?rva0028B72A@Object@@QBEXXZ @0x0028B72A 31B: Object module broadcast
// through +0x244 array; calls each +0x0C sub-object slot44 (+0xB0) with no
// args. Evidence: same +0x244/+0x0C shape as sibling rva0028BA85 slot46 at
// 0x0028BA85; retail lea ecx [eax+0x0C] plus call [eax+0xB0] prove slot;
// null-terminated scan with plain ret proves 0 args void.
class BehaviorModuleInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44();
};

class BfmeObjectModule
{
public:
	virtual void slot0();

private:
	unsigned int m_data[2];
};

class BehaviorModule : public BfmeObjectModule, public BehaviorModuleInterface
{
};

class Object
{
	char m_pad[0x244];
	BehaviorModule **m_modules244;

public:
	void rva0028B72A() const;
};

void Object::rva0028B72A() const
{
	for (BehaviorModule **m = m_modules244; *m; ++m)
		(*m)->slot44();
}
