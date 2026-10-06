// cl: /DNDEBUG /MD
// ?rva0028BD5D@Object@@QBEPAXH@Z @0x0028BD5D 53B
// Object behavior-scan predicate through the +0x244 array: asks each
// module's +0x0C sub-object for slot 25 (+0x64); when non-null asks its
// slot 4 (+0x10) bool and returns the first pointer whose predicate is true,
// else null. Takes one unused int (retail ret 4 with no stack reads).
// Evidence: same +0x244 array and +0x0C lea as rowed getSpawnBehaviorInterface
// at 0x0028BCD4 and siblings rva0028BD3A (slot 33) rva0028BCF4 (slot 38);
// retail lea ecx [eax+0x0C] plus call [eax+0x64] plus call [eax+0x10] plus
// test al jne prove slots and bool; callers at 0x0036E20F 0x0041BB51;
// name stays address-derived (Object owner proven by +0x244).

class Rva0028BD5DResult
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual bool slot04();
};

class BehaviorModuleInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24();
	virtual Rva0028BD5DResult *slot25();
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
	void *rva0028BD5D(int unused) const;
};

void *Object::rva0028BD5D(int unused) const
{
	(void)unused;
	for (BehaviorModule **m = m_modules244; *m; ++m)
	{
		Rva0028BD5DResult *r = (*m)->slot25();
		if (r != 0 && r->slot04())
			return r;
	}
	return 0;
}
