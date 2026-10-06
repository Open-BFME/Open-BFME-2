// cl: /MD
// ?rva004FC9CE@Rva004FC9CE@@QAEPAXABVRva0059E2FD@@@Z @0x004FC9CE 62B.
// Linear search over the +0x98/+0x9C pointer range: first entry whose
// rowed Rva0059E2FD::rva0059E31F accepts the key answers rowed
// Rva0059E2AB::rva0059E2AB on the key, else the key itself.
// Evidence: ret 4 one arg in ebp; thiscall ecx passthrough; 2 callers;
// LINK BONUS via 0x002F2B88. Array elements address both rowed classes
// with identical this (offset-0 overlap unproven); the reinterpret cast
// documents it. Row 0x0059E2FD takes const Rva0059E2FD and row 0x0059E2AB
// takes void star, so the key stays a const reference throughout.
class Rva0059E2FD
{
public:
	bool rva0059E31F(const Rva0059E2FD &o);
};

class Rva0059E2AB
{
public:
	void *rva0059E2AB(void *def);
};

class Rva004FC9CE
{
public:
	void *rva004FC9CE(const Rva0059E2FD &key);
private:
	char m_pad00[0x98];
	Rva0059E2AB **m_98;
	Rva0059E2AB **m_9C;
};

void *Rva004FC9CE::rva004FC9CE(const Rva0059E2FD &key)
{
	Rva0059E2AB **begin = m_98;
	Rva0059E2AB **end = m_9C;
	for (Rva0059E2AB **p = begin; p != end; ++p)
	{
		Rva0059E2AB *e = *p;
		if (((Rva0059E2FD *)e)->rva0059E31F(key))
			return e->rva0059E2AB((void *)&key);
	}
	return (void *)&key;
}
