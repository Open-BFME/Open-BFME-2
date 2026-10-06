// cl: /DNDEBUG /MD
// ?rva0028BCF4@Object@@QBEPAXXZ, retail 0x0028BCF4, 35 bytes.
// Object behavior-scan getter through the +0x244 array: asks each module's
// +0x0C sub-object for slot 38 (+0x98) and returns the first non-null result.
// Evidence: same TU shape as the rowed ?getSpawnBehaviorInterface@Object@@
// at 0x0028BCD4 which scans +0x244 via +0x0C for slot 30; slot 0x98 is the
// retail call immediate; callers at 0x00397299 0x00397211 test the result then
// call its slot 0x0C. Name stays address-derived with void* return like the
// ?rva0028C197 precedent; true interface name unproven.
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
	virtual void slot36(); virtual void slot37();
	virtual void *slot38();
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
	void *rva0028BCF4() const;
};

void *Object::rva0028BCF4() const
{
	for (BehaviorModule **m = m_modules244; *m; ++m)
	{
		void *result = (*m)->slot38();
		if (result)
			return result;
	}
	return 0;
}
