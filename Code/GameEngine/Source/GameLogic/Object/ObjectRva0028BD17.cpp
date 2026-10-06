// cl: /DNDEBUG /MD
// ?rva0028BD17@Object@@QBEPAXXZ, retail 0x0028BD17, 35 bytes.
// Object behavior-scan getter through the +0x244 array: asks each module's
// +0x0C sub-object for slot 32 (+0x80) and returns the first non-null result.
// Evidence: same TU shape as the rowed ?getSpawnBehaviorInterface@Object@@
// at 0x0028BCD4 (slot 30) and the just-landed ?rva0028BCF4 (slot 38); slot
// 0x80 is the retail call immediate; 40-plus callers test the result. Name
// stays address-derived with void* return; true interface name unproven.
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
	virtual void *slot32();
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
	void *rva0028BD17() const;
};

void *Object::rva0028BD17() const
{
	for (BehaviorModule **m = m_modules244; *m; ++m)
	{
		void *result = (*m)->slot32();
		if (result)
			return result;
	}
	return 0;
}
