// cl: /O1 /G7 /MD
// The base initializer is now identified as the input-route constructor.
// Explicit construction in this existing storage preserves the native call
// and all27B of the derived initializer521623; no allocation is performed.
class Rva0031455E {
public:
 Rva0031455E();
 virtual ~Rva0031455E();
 virtual void Rva0031455ELink(Rva0031455E *);
 virtual void Rva00314581Unlink();
private: void *next; void *window;
};
extern "C" unsigned char bfmeVftTC[];

class BfmeThingTC
{
public:
	BfmeThingTC *bfmeInitTC(void *what);
	void *m_bfmeVft;
	unsigned char m_bfmeGap[8];
	void *m_bfmeWhat;
};

BfmeThingTC *BfmeThingTC::bfmeInitTC(void *what)
{
	((Rva0031455E*)this)->Rva0031455E::Rva0031455E();
	m_bfmeWhat = what;
	m_bfmeVft = bfmeVftTC;
	return this;
}
