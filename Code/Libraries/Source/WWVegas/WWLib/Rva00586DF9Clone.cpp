// cl: /O1 /arch:SSE /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva00586DF9@HordeMeleeFormation@@QAEPAV1@PAX@Z @0x00586DF9 60B. Class identity is established by vtable slot 1 and the adjacent HordeMeleeFormation ctor/dtor; method name remains address-derived.
// stlport
#include <vector>

struct BfmeE16 { float x, y, z, w; };

class Rva005D6FCC
{
public:
	Rva005D6FCC(void *held);
	virtual ~Rva005D6FCC();
	void *m_held;
};

class HordeMeleeFormation : public Rva005D6FCC
{
public:
	HordeMeleeFormation(void *held, void *other);
	virtual ~HordeMeleeFormation();
	HordeMeleeFormation *rva00586DF9(void *arg);

private:
	_STL::vector<BfmeE16> m_vec;
	bool m_flag;
	void *m_other;
};

HordeMeleeFormation *HordeMeleeFormation::rva00586DF9(void *arg)
{
	return new HordeMeleeFormation(arg, this);
}
