// cl: /O1 /MD
// Native 0x002B2590..0x002B25BF RET12; WB 0x00D7E840 names the operation
// LivingWorldLogic::spawnBuilding. Retain the caller's existing admitted
// Rva0059E647World::Apply member ABI until the full class contract is known.
// ECX is unused by the target; this does not establish a free-function identity.
// The recovered OwnershipSet caller loads the world into ECX before this call.
// Region +13C must equal player +14. Resolve its slot through 3F0588 and send
// that slot plus the template to 3EFE72. The offset-based provider views below
// preserve the existing declarations and the full 47-byte body unchanged.
class Rva002B2590P3
{
public:
	unsigned char m_pad00[0x14];
	void *m_14;
};

class Rva002B2590P2
{
public:
	void *rva003F0588();
	void rva003EFE72(void *result, void *extra);

public:
	unsigned char m_pad00[0x13C];
	void *m_13C;
};

struct Rva0059E647Entry;
struct Rva0059E647Arg;
struct Rva0059E647World
{
    void Apply(Rva0059E647Entry *, void *, Rva0059E647Arg *);
};
void Rva0059E647World::Apply(Rva0059E647Entry *templateView, void *regionView, Rva0059E647Arg *playerView)
{
    void *p1 = templateView;
    Rva002B2590P2 *p2 = (Rva002B2590P2 *)regionView;
    Rva002B2590P3 *p3 = (Rva002B2590P3 *)playerView;
    if (p2->m_13C != p3->m_14)
        return;
    void *result = p2->rva003F0588();
    if (result == 0)
        return;
    p2->rva003EFE72(result, p1);
}

class Rva0060EF3E
{
public:
	bool rva0060EF3E(int v);
};

class Rva002B25BFOwner
{
public:
	bool rva002B25BF(int v);

private:
	unsigned char m_pad00[0xB0];
	Rva0060EF3E *m_B0;
};

// ?rva002B25BF@Rva002B25BFOwner@@QAE_NH@Z
bool Rva002B25BFOwner::rva002B25BF(int v)
{
	if (v == 0)
		return false;
	return m_B0->rva0060EF3E(v);
}
