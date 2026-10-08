// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// SimpleStreakRendererClass::Init: WorldBuilder 0x00A1E6A0 names the method
// in its assertion. Retail [0x00129303,0x00129428) makes alpha/additive
// Shadow.fx setups with the _CreateShadowMapStreak technique and BlendMode
// values 1/2. Its parameter storage is 36 bytes, value at +0x1C; its list
// has the STLport three-pointer header and uses the existing record helpers.
// Provider names below remain address-derived where identity is unresolved.
#include <vector>

struct BfmeAssignRecord36
{
	BfmeAssignRecord36(const char *, int);
	char m_prefix[28];
	int m_int;
	char m_tail[4];
};

// This storage wrapper calls the rowed constructor through its current
// provider spelling; its rowed destructor releases the two string handles.
struct Rva0007BB16Record
{
	Rva0007BB16Record(const char *name, int type) : m_record(name, type) {}
	~Rva0007BB16Record();
	BfmeAssignRecord36 m_record;
};

// Use the already matched destructor provider instead of emitting a second
// COMDAT under this unit's size-optimization settings.
namespace _STL {
template <> vector<Rva0007BB16Record>::~vector();
}

struct Rva00082EB8Rec;
class Rva00082EB8 : public _STL::vector<Rva0007BB16Record>
{
public:
	void rva00082EB8(const Rva00082EB8Rec &);
};

class Rva00072A94
{
public:
	Rva00072A94 &operator=(const Rva00072A94 &);
};

class FXShaderSetup
{
public:
	virtual void Delete_This();
	void Release_Ref()
	{
		--NumRefs;
		if (NumRefs == 0)
			Delete_This();
	}
private:
	int NumRefs;
};

template <class T> class RefCountPtr
{
public:
	~RefCountPtr() { if (m_ptr) m_ptr->Release_Ref(); }
	operator const Rva00072A94 &() const { return *(const Rva00072A94 *)this; }
private:
	T *m_ptr;
};

RefCountPtr<FXShaderSetup> Rva00152C47_CreateFXShaderSetup(const char *, const char *,
	const _STL::vector<Rva0007BB16Record> *, int);

class Rva007B7024Object;
extern Rva007B7024Object *g_Va00DEE870;
extern Rva007B7024Object *g_Va00DEE86C;

class SimpleStreakRendererClass
{
public:
	static void Init(bool enableShadows);
};

void SimpleStreakRendererClass::Init(bool enableShadows)
{
	if (g_Va00DEE870 || g_Va00DEE86C || !enableShadows)
		return;
	Rva00082EB8 parameters;
	Rva0007BB16Record blendMode("BlendMode", 6);
	blendMode.m_record.m_int = 1;
	parameters.rva00082EB8(*(const Rva00082EB8Rec *)&blendMode);
	*(Rva00072A94 *)&g_Va00DEE870 = Rva00152C47_CreateFXShaderSetup(
		"Shadow.fx", "_CreateShadowMapStreak", &parameters, 4);
	blendMode.m_record.m_int = 2;
	parameters.rva00082EB8(*(const Rva00082EB8Rec *)&blendMode);
	*(Rva00072A94 *)&g_Va00DEE86C = Rva00152C47_CreateFXShaderSetup(
		"Shadow.fx", "_CreateShadowMapStreak", &parameters, 4);
}
