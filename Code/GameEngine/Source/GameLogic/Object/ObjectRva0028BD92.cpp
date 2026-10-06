// cl: /DNDEBUG /MD
// ?rva0028BD92@Object@@QAEPAXH@Z @0x0028BD92 69B: Object scan of +0x244
// module array; each +0x0C sub-object slot25 (+0x64) yields B; when B non-null
// and its slot1 (+0x04) bool true, B-0x20 is Rva0044EF2C whose rowed int
// getter is compared to the int arg, returning adjusted B on match else null.
// Evidence: same +0x244/+0x0C/slot25 shape as rowed rva0028BD5D at 0x0028BD5D
// and siblings rva0028BD3A/BD17/BCF4; retail lea ecx [eax+0x0C] plus calls
// [eax+0x64] [eax+0x04] 0x0044EF2C plus cmp [esp+0x0C] prove slots and arg.
class Rva0028BD92Result
{
public:
	virtual void slot00();
	virtual bool slot01();
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
	virtual Rva0028BD92Result *slot25();
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

class Rva0044EF2C
{
public:
	int rva0044EF2C();
};

class Object
{
	char m_pad[0x244];
	BehaviorModule **m_modules244;

public:
	void *rva0028BD92(int key);
};

void *Object::rva0028BD92(int key)
{
	for (BehaviorModule **m = m_modules244; *m; ++m)
	{
		Rva0028BD92Result *r = (*m)->slot25();
		if (r != 0 && r->slot01())
		{
			Rva0044EF2C *adj = reinterpret_cast<Rva0044EF2C *>(reinterpret_cast<char *>(r) - 0x20);
			if (adj->rva0044EF2C() == key)
				return adj;
		}
	}
	return 0;
}
