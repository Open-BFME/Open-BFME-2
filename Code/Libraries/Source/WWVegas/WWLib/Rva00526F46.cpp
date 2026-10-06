// cl: /Ireference/shims/bfmelist /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva00526F46@Rva00526F46@@QAEPAV1@XZ @0x00526F46 58B evidence: factory news 0x1c via rowed 0x0002FDA0 then rowed ctor 0x00526275 stores at +0 returns this; caller 0x002D5863.
// Honest-address factory (naming rule).
class Rva00526275
{
public:
	Rva00526275();
private:
	char m_pad[0x1c];
};

class Rva00526F46
{
public:
	Rva00526F46 *rva00526F46();
private:
	Rva00526275 *m_ptr;
};

Rva00526F46 *Rva00526F46::rva00526F46()
{
	m_ptr = new Rva00526275;
	return this;
}
