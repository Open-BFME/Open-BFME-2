// cl: /DNDEBUG /MD
//
// Small vtable-slot bodies with no ledger owner and no Ghidra entry, batch
// AC. As in VslotSmallBodiesA-AB, each class and method is address-derived
// unless the ledger already names it, and models only what its body
// touches. Meanings are not recovered.

typedef int Int;

enum NameKeyType
{
	NK_UNKNOWN = 0
};
NameKeyType Rva0045EE2CGet();

class Module;
class Object;
class StancesBehavior
{
public:
	Int rva0045ED4B() const;
};
class AIUpdateInterface
{
public:
	Object *getCurrentVictim() const;
};
class Object
{
protected:
	Module *findModule(NameKeyType key) const;
	friend class Rva005D7305;
public:
	char m_pad00[0x258];
	AIUpdateInterface *m_ai258;
};

// 0x005D7305 (table VA 0x00C75CE0): false when the argument's
// StancesBehavior (rowed name key, pinned Object::findModule) classifies
// its stance as 1, else whether its AI has no current victim.
class Rva005D7305
{
public:
	bool rva005D7305(Object *obj);
};
bool Rva005D7305::rva005D7305(Object *obj)
{
	NameKeyType key = Rva0045EE2CGet();
	StancesBehavior *stances = (StancesBehavior *)obj->findModule(key);
	if (stances->rva0045ED4B() != 1)
		return obj->m_ai258->getCurrentVictim() == 0;
	return false;
}

// 0x00214AC7 (table VA 0x00BE534C): only tail-calls the rowed
// Rva00214A8A::rva00214A8A (Rva00214A8AClear.cpp).
class Rva00214A8A
{
public:
	void rva00214A8A();
	void rva00214AC7();
};
void Rva00214A8A::rva00214AC7()
{
	rva00214A8A();
}

// 0x004AE972 (tables VA 0x00C3EFF0/0x00C55460) and 0x004DF8C2 (table VA
// 0x00BFBE40): UpdateModuleInterface slot 1 overrides answering the
// disabled mask of bits 3 and 4 (resp. 3 and 8), built by the rowed
// two-bit BitFlags<11> constructor 0x005E5963.
template <int NUM_BITS>
class BitFlags
{
public:
	enum BogusInitType
	{
		kInit = 0
	};
	BitFlags(BogusInitType init, Int b0, Int b1);
private:
	unsigned int m_words[1];
};
typedef BitFlags<11> DisabledMaskType;
class Rva004AE972
{
public:
	virtual DisabledMaskType getDisabledTypesToProcess() const;
};
DisabledMaskType Rva004AE972::getDisabledTypesToProcess() const
{
	return DisabledMaskType(DisabledMaskType::kInit, 3, 4);
}
class Rva004DF8C2
{
public:
	virtual DisabledMaskType getDisabledTypesToProcess() const;
};
DisabledMaskType Rva004DF8C2::getDisabledTypesToProcess() const
{
	return DisabledMaskType(DisabledMaskType::kInit, 3, 8);
}
