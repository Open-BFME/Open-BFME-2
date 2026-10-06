// cl: /DNDEBUG /MD /EHsc
//
// ?rva0028C4ED@Object@@QBE_NXZ @0x0028C4ED 38B
// Object module-scan bool predicate through the +0x244 array: asks each
// module's +0x0C sub-object for slot 26 (+0x68) and returns true on the first
// true. Evidence: same +0x244 array as rowed getSpawnBehaviorInterface at
// 0x0028BCD4 and siblings rva0028BD3A (slot 33) rva0028BCF4 (slot 38)
// rva0028BD17 (slot 32); retail lea ecx [eax+0x0C] plus call [eax+0x68]
// proves the +0x0C interface and slot; callers at 0x0029340C 0x003792C8 test
// al; plain ret proves 0 args; name stays address-derived (Object owner proven
// by +0x244 and callers, identity unproven).

class BehaviorModuleInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25();
	virtual int slot26();
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
	bool rva0028C4ED() const;
};

bool Object::rva0028C4ED() const
{
	for (BehaviorModule **m = m_modules244; *m; ++m)
	{
		if ((*m)->slot26())
			return true;
	}
	return false;
}
