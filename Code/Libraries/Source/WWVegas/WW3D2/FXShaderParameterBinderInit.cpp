// cl: /O1 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?Init@FXShaderParameterBinder@@QAEXPAUID3DXEffect@@@Z @ 0x00153F08 (336
// bytes), called from the binder ctor 0x00154058. Target evidence: the
// per-technique vector at +4 is emptied through the rowed range erase
// 0x00153C2C, the previous effect at +0 released (slot 2) and the new one
// AddRef'd (slot 1); a stack parsing record (rowed ctor 0x0015334F, a
// handle at +0 and a 4-byte handle vector at +4 seeded with one null through
// the rowed push_back 0x002E01C6) is published at +0x10 for the duration.
// GetDesc sizes the technique vector (rowed resize 0x00153EE5, stride 0x4C)
// and fills each entry's +0 with GetTechnique; every parameter carrying a
// "SasBindAddress" string annotation is bound through 0x0015306D with the
// parameter as the record's current handle, and 0x00190F8E then binds the
// standard semantics. Interface slots are d3dx9effect.h's ID3DXEffect order.

#define strchr _stlport_hides_strchr
#define strncpy _stlport_hides_strncpy
#define _strcmpi _stlport_hides_strcmpi
#include <vector>
#undef strchr
#undef strncpy
#undef _strcmpi

extern "C" {
__declspec(dllimport) char *__cdecl strchr(const char *s, int c);
__declspec(dllimport) char *__cdecl strncpy(char *d, const char *s, unsigned int n);
__declspec(dllimport) int __cdecl _strcmpi(const char *a, const char *b);
}

typedef long HRESULT;
typedef const char *D3DXHANDLE;

struct D3DXEFFECT_DESC
{
	const char *Creator;
	unsigned int Parameters;
	unsigned int Techniques;
	unsigned int Functions;
};

#define FX_SLOT(n) virtual HRESULT __stdcall slot##n()

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
	FX_SLOT(27);
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

struct Rva005F8F96
{
	~Rva005F8F96();
	void *m_00;
	int m_04;
};

// One per technique, 0x4C bytes: the handle and six binding vectors.
struct Rva00153729
{
	Rva00153729();
	~Rva00153729();

	D3DXHANDLE m_technique;			// +0
	_STL::vector<Rva005F8F96> m_04[6];	// +4
};

class FXShaderParameterBinder;

class FXShaderParameterSourceNamespace
{
public:
	virtual ~FXShaderParameterSourceNamespace();
	virtual void ResolveBindings(const char *name, D3DXHANDLE parameter, FXShaderParameterBinder *binder) = 0;
};

// The registered namespaces (rowed register 0x00153565): a 64-byte name and
// the namespace object, in the vector the pointer at 0x00DF6F20 owns.
struct BfmePod68
{
	char m_name[0x40];
	FXShaderParameterSourceNamespace *m_namespace;
};

extern _STL::vector<BfmePod68> *g_Rva00153565Vec;

// 0x00190F8E: binds the standard semantic tables to the effect.
void __cdecl Rva00190F8E_BindStandardSemantics(FXShaderParameterBinder *binder);

class FXShaderParameterBinder
{
public:
	void Init(ID3DXEffect *effect);

	void ResolveBindings(const char *address, D3DXHANDLE param);

private:
	ID3DXEffect *m_effect;				// +0
	_STL::vector<Rva00153729> m_techniques;		// +4
	Rva0015334F *m_parsing;				// +0x10
};

void FXShaderParameterBinder::Init(ID3DXEffect *effect)
{
	_STL::vector<Rva00153729> *techniques = &m_techniques;
	techniques->erase(techniques->begin(), techniques->end());
	if (m_effect != 0) {
		m_effect->Release();
		m_effect = 0;
	}
	m_effect = effect;
	effect->AddRef();

	Rva0015334F parsing;
	m_parsing = &parsing;
	ScienceType top = (ScienceType)0;
	parsing.m_stack.push_back(top);

	int num_params = 0;
	int num_techniques = 0;
	D3DXEFFECT_DESC desc;
	if (m_effect->GetDesc(&desc) >= 0) {
		num_params = desc.Parameters;
		num_techniques = desc.Techniques;
	}

	techniques->resize(num_techniques);
	for (int t = 0; t < num_techniques; t++) {
		Rva00153729 &entry = (*techniques)[t];
		entry.m_technique = m_effect->GetTechnique(t);
	}

	for (int i = 0; i < num_params; i++) {
		D3DXHANDLE param = m_effect->GetParameter(0, i);
		if (param == 0)
			continue;
		D3DXHANDLE annotation = m_effect->GetAnnotationByName(param, "SasBindAddress");
		if (annotation == 0)
			continue;
		const char *address = 0;
		if (m_effect->GetString(annotation, &address) < 0)
			continue;
		m_parsing->m_current = param;
		ResolveBindings(address, param);
		m_parsing->m_current = 0;
	}

	Rva00190F8E_BindStandardSemantics(this);
	m_parsing = 0;
}

// 0x0015306D: splits "Namespace.Member" at the first '.', finds the
// registered namespace by case-insensitive name and lets it resolve the
// member for this parameter.
void FXShaderParameterBinder::ResolveBindings(const char *address, D3DXHANDLE param)
{
	const char *dot = strchr(address, '.');
	if (dot == 0)
		return;
	unsigned int length = dot - address;
	if (length >= 0x40)
		return;
	char name[0x40];
	strncpy(name, address, length);
	name[length] = 0;
	for (BfmePod68 *it = g_Rva00153565Vec->begin(); it != g_Rva00153565Vec->end(); ++it) {
		if (_strcmpi(it->m_name, name) == 0) {
			it->m_namespace->ResolveBindings(dot + 1, param, this);
			return;
		}
	}
}
