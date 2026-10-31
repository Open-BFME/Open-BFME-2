// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?AddBinding@FXShaderParameterBinder@@QAEXUTreeHintRef00217D4C@@PBD@Z @0x00153ACA 207B
// Evidence: unlock lane, this=FXShaderParameterBinder (+0x10 store via rowed PushDynamicSetStack 0x001535FF and dec 0x001531E6), virtual slot 0xF8, TreeHintRef assign 0x002174A4 and Release 0x0007DEEF, push_back 0x00153A27 stride 8, caller 0x000E2A81 builds Rva00080221 temp.
#include <vector>

struct TargetRef00217D4C { virtual void *destroy(unsigned int flags); int references; };

void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

struct TreeHintRef00217D4C
{
	TargetRef00217D4C *m_ptr;
	TreeHintRef00217D4C() : m_ptr(0) {}
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);
	~TreeHintRef00217D4C()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(m_ptr);
	}
};

struct Rva005F8F96
{
	~Rva005F8F96();
	TargetRef00217D4C *m_00;
	int m_04;
};

typedef const char *D3DXHANDLE;

// One per technique, 0x4C bytes: the handle and six binding vectors.
struct Rva00153729
{
	Rva00153729();
	~Rva00153729() {}
	Rva00153729 &rva001539BC(const Rva00153729 &other);

	D3DXHANDLE m_technique;			// +0
	_STL::vector<Rva005F8F96> m_vec[6];	// +4
};

// The stack's 4-byte elements append through the ICF-shared push_back
// 0x002E01C6, rowed under its established ScienceType spelling (as the
// PushDynamicSetStack row 0x0015354E also spells it).
enum ScienceType { SCIENCE_INVALID = -1 };

// The binder's stack parsing record: the parameter being bound and the
// dynamic-set stack (the 4-byte vector the Push/PopDynamicSetStack rows use).
class Rva0015334F
{
public:
	Rva0015334F();

	D3DXHANDLE m_current;			// +0
	_STL::vector<ScienceType> m_stack;	// +4
};

typedef long HRESULT;

struct D3DXEFFECT_DESC
{
	const char *Creator;
	unsigned int Parameters;
	unsigned int Techniques;
	unsigned int Functions;
};

#define FX_SLOT(n) virtual HRESULT __stdcall slot##n()

// Interface slots are d3dx9effect.h's ID3DXEffect order.
struct ID3DXEffect
{
	FX_SLOT(00);
	virtual unsigned long __stdcall AddRef();
	virtual unsigned long __stdcall Release();
	virtual HRESULT __stdcall GetDesc(D3DXEFFECT_DESC *desc);
	FX_SLOT(04);
	FX_SLOT(05);
	FX_SLOT(06);
	FX_SLOT(07);
	virtual D3DXHANDLE __stdcall GetParameter(D3DXHANDLE param, unsigned int index);
	FX_SLOT(09);
	FX_SLOT(10);
	FX_SLOT(11);
	virtual D3DXHANDLE __stdcall GetTechnique(unsigned int index);
	FX_SLOT(13);
	FX_SLOT(14);
	FX_SLOT(15);
	FX_SLOT(16);
	FX_SLOT(17);
	FX_SLOT(18);
	virtual D3DXHANDLE __stdcall GetAnnotationByName(D3DXHANDLE object, const char *name);
	FX_SLOT(20);
	FX_SLOT(21);
	FX_SLOT(22);
	FX_SLOT(23);
	FX_SLOT(24);
	FX_SLOT(25);
	FX_SLOT(26);
	virtual HRESULT __stdcall GetInt(D3DXHANDLE param, int *value);
	FX_SLOT(28);
	FX_SLOT(29);
	FX_SLOT(30);
	FX_SLOT(31);
	FX_SLOT(32);
	FX_SLOT(33);
	FX_SLOT(34);
	FX_SLOT(35);
	FX_SLOT(36);
	FX_SLOT(37);
	FX_SLOT(38);
	FX_SLOT(39);
	FX_SLOT(40);
	FX_SLOT(41);
	FX_SLOT(42);
	FX_SLOT(43);
	FX_SLOT(44);
	FX_SLOT(45);
	FX_SLOT(46);
	FX_SLOT(47);
	FX_SLOT(48);
	FX_SLOT(49);
	FX_SLOT(50);
	virtual HRESULT __stdcall GetString(D3DXHANDLE param, const char **string);
	FX_SLOT(52);
	FX_SLOT(53);
	FX_SLOT(54);
	FX_SLOT(55);
	FX_SLOT(56);
	FX_SLOT(57);
	FX_SLOT(58);
	FX_SLOT(59);
	FX_SLOT(60);
	FX_SLOT(61);
	virtual int __stdcall IsParameterUsed(D3DXHANDLE param, D3DXHANDLE technique);
};

class FXShaderParameterBinder
{
public:
	FXShaderParameterBinder(void *surface);
	void Init(ID3DXEffect *effect);
	void ResolveBindings(const char *address, D3DXHANDLE param);
	void PopDynamicSetStack();
	void PushDynamicSetStack(const char *name);
	void PushDynamicSetStack(ScienceType value);
	void AddBinding(TreeHintRef00217D4C arg, const char *name);

	ID3DXEffect *m_effect;				// +0
	_STL::vector<Rva00153729> m_techniques;		// +4
	Rva0015334F *m_ParsingData;			// +0x10
};

struct Rva00153A27Element
{
	TreeHintRef00217D4C m_ref;
	const char *m_name;
};

// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> void vector<Rva00153A27Element>::push_back(const Rva00153A27Element &); }

void FXShaderParameterBinder::AddBinding(TreeHintRef00217D4C arg, const char *name)
{
	if (m_ParsingData == 0)
		return;
	PushDynamicSetStack(name);
	int idx = *(m_ParsingData->m_stack.end() - 1);
	Rva00153A27Element elem;
	elem.m_ref = arg;
	elem.m_name = name;
	for (Rva00153729 *it = m_techniques.begin(); it != m_techniques.end(); ++it)
	{
		const char *cur = m_ParsingData->m_current;
		if (cur == 0)
			cur = name;
		if (cur == 0)
			continue;
		if (m_effect->IsParameterUsed(cur, it->m_technique))
			// 0x00153A27 is rowed under this element spelling of the same 8 bytes.
			reinterpret_cast<_STL::vector<Rva00153A27Element> *>(&it->m_vec[idx])->push_back(elem);
	}
	PopDynamicSetStack();
}
