// cl: /DNDEBUG /MD
// ?rva0028BA85@Object@@QBEXXZ @0x0028BA85 41B
// Object module broadcast through the +0x244 array: calls each module's
// +0x0C sub-object slot 46 (+0xB8) with the int at +0x45C. Evidence: same
// +0x244 array and +0x0C lea as rowed getSpawnBehaviorInterface at 0x0028BCD4
// and siblings rva0028C4ED (slot 26) rva0028C513 rva0028BD3A/BD17/BCF4;
// retail lea ecx [eax+0x0C] plus call [eax+0xB8] plus push [edi+0x45C] prove
// the interface slot and int arg; null-terminated scan with plain ret proves
// 0 args void; setter sibling at 0x0028BAAE stores +0x45C then calls this;
// name stays address-derived (Object owner proven by +0x244 and callers).

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
	virtual void slot44(); virtual void slot45();
	virtual void slot46(int v);
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
	char m_pad248[0x45c - 0x248];
	int m_val45c;

public:
	void rva0028BA85() const;
	void rva0028BAAE(int v);
};

void Object::rva0028BA85() const
{
	for (BehaviorModule **m = m_modules244; *m; ++m)
		(*m)->slot46(m_val45c);
}

void Object::rva0028BAAE(int v)
{
	m_val45c = v;
	rva0028BA85();
}
