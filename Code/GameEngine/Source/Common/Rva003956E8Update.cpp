// cl: /DNDEBUG /MD /EHsc
// ?rva003956E8@Rva003956E8@@QAEXXZ, retail 0x003956E8, 32 bytes.
// Module-style update: chain the rowed Rva00497805::loadPostProcess on our
// own this, then when the +0x34 flag is set forward our +0x08 object to the
// pathfinder shim reached through TheAI (0x00DFF0F8) at +0x10 via the rowed
// BFMEPathfinderMapShim::rva002E718A. Evidence: direct call 0x00497805 with
// ecx=this; cmpl $0,0x34; mov eax,[0xdff0f8]; push 0x8(esi);
// mov ecx,[eax+0x10]; call 0x002E718A.
class Object;

class BFMEPathfinderMapShim
{
public:
	void rva002E718A(Object *object);
};

class UpdateModule
{
protected:
	virtual void loadPostProcess();
};

class Rva00497805 : public UpdateModule
{
protected:
	void loadPostProcess();
};

class AI
{
public:
	char m_pad00[0x10];
	BFMEPathfinderMapShim *m_shim10;
};
extern AI *TheAI;

class Rva003956E8 : public Rva00497805
{
public:
	void rva003956E8();
private:
	char m_pad04[4];
	Object *m_08;
	char m_pad0C[0x34 - 0x0C];
	int m_34;
};

void Rva003956E8::rva003956E8()
{
	// Qualified to the Rva00497805 spelling: retail calls 0x00497805
	// directly, not through the module vtable slot.
	Rva00497805::loadPostProcess();
	if (m_34)
	{
		TheAI->m_shim10->rva002E718A(m_08);
	}
}
