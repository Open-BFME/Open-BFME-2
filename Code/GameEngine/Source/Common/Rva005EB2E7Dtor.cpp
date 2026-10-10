// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ??1Rva005EB2E7@@UAE@XZ @0x005EB2E7 118B (the pin keeps the non-virtual
// spelling). Opaque dtor: drops this object from TheLivingWorldLogic's list at
// +0x2C through the rowed erase 0x002B7250, unloads the content at +8
// (0x0057C2CC), then the +0x34 holder clears, the two vector<GeometryShape>
// at +0x1C unwind through the EH vector destructor iterator (~vector
// 0x005EB28A, declaration-only specialisation keeps the call out of line) and
// the +0x14 holder clears. Identity of the class is unproven.
#include <vector>

struct GeometryShape;
namespace _STL
{
template <> class vector<GeometryShape, allocator<GeometryShape> >
{
public:
	~vector();

private:
	GeometryShape *m_begin;
	GeometryShape *m_finish;
	GeometryShape *m_end;
};
}

class CreateAHeroData;
class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *v);
};
struct LivingWorldLogic005EB2E7
{
	char m_pad[0x2C];
	Rva002B7250 m_holder;
};
extern LivingWorldLogic005EB2E7 *TheLivingWorldLogic;

struct Rva0057C2CC
{
	void rva0057C2CC();
};

class Rva000AD6F4
{
public:
	void clear();
	void *m_ptr;
};
struct WrapClear005EB2E7
{
	~WrapClear005EB2E7() { m_c.clear(); }
	Rva000AD6F4 m_c;
};

class Rva005EDFF8
{
public:
	virtual ~Rva005EDFF8() {}
};

class Rva005EB2E7 : public Rva005EDFF8
{
public:
	virtual ~Rva005EB2E7();
private:
	int m_04;
	Rva0057C2CC *m_08;
	int m_0C;
	int m_10;
	WrapClear005EB2E7 m_14;
	int m_18;
	_STL::vector<GeometryShape> m_1C[2];
	WrapClear005EB2E7 m_34;
};

Rva005EB2E7::~Rva005EB2E7()
{
	TheLivingWorldLogic->m_holder.rva002B7250((CreateAHeroData *)this);
	m_08->rva0057C2CC();
}
