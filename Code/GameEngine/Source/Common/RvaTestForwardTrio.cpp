// Three retail member forwarders (18B each) of one shape:
// push ecx, mov ecx, [esp+8], call <test>, ret 4. Each passes its own this
// as the mask operand to a matched overlap-test callee:
// 0x0023D487 -> BitFlags<11>::test (0x0023C59F),
// 0x0026197B -> BitFlags<69>::test (0x002615C0),
// 0x0035B449 -> Rva00331682Holder::test (0x00331682).
// Callee classes are declared only; their matched rows resolve the calls.
// Owner identities unproven; owner names are address-derived. The operand
// stays const void* so no template spelling leaks into the wrapper names.

template <int N>
class BitFlags
{
public:
	bool test(const void *other) const;
};

class Rva00331682Holder
{
public:
	bool test(const void *other) const;
};

class Rva0023D487Owner
{
public:
	bool check(const void *flags);
};

class Rva0026197BOwner
{
public:
	bool check(const void *flags);
};

class Rva0035B449Owner
{
public:
	bool check(const void *holder);
};

bool Rva0023D487Owner::check(const void *flags)
{
	return ((const BitFlags<11> *)flags)->test(this);
}

bool Rva0026197BOwner::check(const void *flags)
{
	return ((const BitFlags<69> *)flags)->test(this);
}

bool Rva0035B449Owner::check(const void *holder)
{
	return ((const Rva00331682Holder *)holder)->test(this);
}
