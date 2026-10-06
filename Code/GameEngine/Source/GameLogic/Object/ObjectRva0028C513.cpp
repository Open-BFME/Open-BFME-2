// cl: /DNDEBUG /MD /EHsc
//
// ?rva0028C513@Object@@QBE?AW4ObjectID@@XZ @0x0028C513 39B
// Object module-scan ObjectID getter through the +0x244 array: asks each
// module's +0x0C sub-object for slot 26 (+0x68); on the first non-null result
// tail-forwards to its slot 0 which returns the ID, else INVALID_ID.
// Evidence: same +0x244 array and +0x0C lea as sibling rva0028C4ED (slot 26
// bool) and void* siblings rva0028BD3A/BD17/BCF4; retail call [eax+0x68] plus
// jmp [edx] immediates prove slot and tail; caller at 0x00293422 pushes eax
// to rowed findObjectByID which takes W4ObjectID proving ObjectID return;
// plain ret proves 0 args; name stays address-derived (Object owner proven by
// +0x244 and callers, identity unproven).

enum ObjectID
{
	INVALID_ID = 0
};

class Rva0028C513Result
{
public:
	virtual ObjectID slot0();
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
	virtual void slot24(); virtual void slot25();
	virtual Rva0028C513Result *slot26();
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
	ObjectID rva0028C513() const;
};

ObjectID Object::rva0028C513() const
{
	for (BehaviorModule **m = m_modules244; *m; ++m)
	{
		Rva0028C513Result *r = (*m)->slot26();
		if (r != 0)
			return r->slot0();
	}
	return INVALID_ID;
}
