// cl: /O1 /DNDEBUG /MD
// ?rva0028BC58@Object@@QAEPAXH@Z @0x0028BC58 60B
// Object module-scan getter through the +0x244 array: asks each module's
// +0x0C sub-object for slot 28 (+0x70) and returns the first non-null result
// filtered by the int argument: when the argument is zero the first result
// wins, otherwise the result's own slot 30 (+0x78) must test true.
// Evidence: same +0x244 array via +0x0C lea as rowed getSpawnBehaviorInterface
// at 0x0028BCD4 and siblings rva0028BCF4 (slot 38) rva0028BD17 (slot 32)
// rva0028C4ED (slot 26); retail lea ecx [eax+0x0C] plus calls [eax+0x70] and
// [eax+0x78] prove the two slots; 40-plus callers; LINK BONUS names this exact
// mangling for 4 waiting files.
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
	virtual void *slot28();
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

class Rva0028BC58Res
{
public:
	virtual void r00(); virtual void r01(); virtual void r02(); virtual void r03();
	virtual void r04(); virtual void r05(); virtual void r06(); virtual void r07();
	virtual void r08(); virtual void r09(); virtual void r10(); virtual void r11();
	virtual void r12(); virtual void r13(); virtual void r14(); virtual void r15();
	virtual void r16(); virtual void r17(); virtual void r18(); virtual void r19();
	virtual void r20(); virtual void r21(); virtual void r22(); virtual void r23();
	virtual void r24(); virtual void r25(); virtual void r26(); virtual void r27();
	virtual void r28(); virtual void r29();
	virtual bool slot30();
};

class Object
{
	char m_pad[0x244];
	BehaviorModule **m_modules244;

public:
	void *rva0028BC58(int a);
};

void *Object::rva0028BC58(int a)
{
	for (BehaviorModule **m = m_modules244; *m; ++m)
	{
		void *res = (*m)->slot28();
		if (!res)
			continue;
		if ((char)a == 0)
			return res;
		if (((Rva0028BC58Res *)res)->slot30())
			return res;
	}
	return 0;
}
