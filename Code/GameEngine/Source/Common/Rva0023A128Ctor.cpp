// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ??0Rva0023A128@@QAE@PAX0H@Z @0x0023A128 130B.
// Constructor of an object registered on two lists through the rowed append
// 0x005A0B4C: itself (first base at +0) on the holder passed as a1, and its
// second base at +4 on the list at +0x4C of the singleton TheLivingWorldLogic. Retail's
// unwind map: states 0 and 1 destroy the two base subobjects (+0 and +4,
// both through the folded 7-byte vptr setter 0x00238D97); state 2 the
// Rva0042D8D4 at +0x14 (rowed ctor 0x0042D8D4); states 3-4 the two zeroed
// members at +0x18/+0x1C, whose destructor is out of line (0x0023932B). The
// +4 slot first takes the second base's vtable and then this class's second
// vtable. m_08/m_0C are this class's own members (addressed from the object,
// not the base). Replaces the banked 0.92 attempt, which stored vtable
// addresses as data behind an empty base.

class LivingWorldLogic;
LivingWorldLogic *TheLivingWorldLogic;
// Retail initializer in GameEngine::init (0x0022E2E4) names this singleton.
// Matched DIR32 references bind it to RVA 0x009FEF10; the retail slot is zero.
// BFME 1 donor ba7ddda7 defines the same named singleton, without proving its target layout.
struct Rva002BA8F1Listener;
class Rva005A0B4CList
{
public:
	void append(Rva002BA8F1Listener *p);
private:
	char m_pad[12];
};
struct Rva0023A128Holder
{
	char pad[4];
	Rva005A0B4CList list;
};
class Rva002BA8F1Logic
{
public:
	char pad[0x4c];
	Rva005A0B4CList list;
};


class Rva0042D8D4
{
public:
	Rva0042D8D4();
	~Rva0042D8D4();
private:
	int m_0;
};
class Rva0023932BMember
{
public:
	Rva0023932BMember() : m_ptr(0) {}
	~Rva0023932BMember();
private:
	void *m_ptr;
};
struct Rva0023A128Listener
{
	Rva0023A128Listener() {}
	virtual ~Rva0023A128Listener();
};
struct Rva0023A128Link
{
	Rva0023A128Link() {}
	virtual ~Rva0023A128Link();
};
class Rva0023A128 : public Rva0023A128Listener, public Rva0023A128Link
{
public:
	Rva0023A128(void *a0, void *a1, int a2);
	virtual ~Rva0023A128();
private:
	void *m_08;
	void *m_0C;
	int m_10;
	Rva0042D8D4 m_14;
	Rva0023932BMember m_18;
	Rva0023932BMember m_1C;
};
Rva0023A128::Rva0023A128(void *a0, void *a1, int a2)
	: m_08(a0), m_0C(a1), m_10(a2)
{
	((Rva0023A128Holder *)m_0C)->list.append((Rva002BA8F1Listener *)static_cast<Rva0023A128Listener *>(this));
	(*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->list.append((Rva002BA8F1Listener *)static_cast<Rva0023A128Link *>(this));
}
