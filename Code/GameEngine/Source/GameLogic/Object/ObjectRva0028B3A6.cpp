// cl: /DNDEBUG /MD /EHsc
// ?rva0028B3A6@Object@@QBE_NXZ @0x0028B3A6 49B: Object module scan through
// +0x244 array; each +0x0C sub-object slot1 (+0x04) yields inner, when
// non-null its slot5 (+0x14) bool true returns true, else continues; false
// when none match. Evidence: same +0x244/+0x0C shape as sibling rva0028B3D7
// at 0x0028B3D7; retail lea/call [eax+0x04] plus call [edx+0x14] plus test
// al jne plus xor al/mov al,1 tails prove slots and bool; plain ret.
class Rva0028B3A6Inner
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual bool slot05();
};

class BehaviorModuleInterface
{
public:
	virtual void slot00();
	virtual Rva0028B3A6Inner *slot01();
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
	bool rva0028B3A6() const;
};

bool Object::rva0028B3A6() const
{
	for (BehaviorModule **m = m_modules244; *m; ++m)
	{
		Rva0028B3A6Inner *r = (*m)->slot01();
		if (r != 0 && r->slot05())
			return true;
	}
	return false;
}
