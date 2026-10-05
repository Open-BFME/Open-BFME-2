// ?rva0059CFAA@Rva0059CFAAClass@@QAEMHHPAURva0059CFAACallee@@PAH@Z
// partial score=0.55 date=2026-10-05
// cl: /O1 /DNDEBUG /MD /EHsc /G7 /arch:SSE
//
// ?rva0059CFAA@Rva0059CFAAClass@@QAEHMHPAVRva0059CFAACallee@@PAH@Z @0x0059CFAA 223B:
// float thiscall of 4 args. Clamps (count>0 ? m_4 : 0) at zero, calls two
// __stdcall callees through the arg3 object (callee cleans its pushes, hence
// no add esp), frees the out-pointer, then either scales by count*5 or runs a
// small float polynomial off pooled constants. Identity unproven;
// address-derived names. Callees pinned from target REL32 via decode_calls.
extern const float g_Va007BAEAC;
extern const float g_Va007C26F0;
extern const float g_Va007CFB10;
extern const float g_Va007C7508;
extern "C" void __cdecl free(void*);

struct Rva0059CFAACallee
{
	void __stdcall rva00500659(void* a1, int a2, int a3, void* a4);
	void __stdcall rva004FFB00(void* a1, int a2, int a3);
};

struct Rva0059CFAAClass
{
	char m_0[4];
	int m_4;

	float rva0059CFAA(int a1, int count, Rva0059CFAACallee* o, int* p);
};

// ?rva0059CFAA@Rva0059CFAAClass@@QAEHMHPAVRva0059CFAACallee@@PAH@Z
float Rva0059CFAAClass::rva0059CFAA(int a1, int count, Rva0059CFAACallee* o, int* p)
{
	int v = count > 0 ? m_4 : 0;
	float result = (float)v;
	if (result <= g_Va007BAEAC)
		return result;
	int w1 = 0;
	int w3 = 0;
	void* w2;
	o->rva00500659(&w1, *p + 0x14, a1, &w2);
	if (w2 != 0)
		free(w2);
	o->rva004FFB00(&w3, *p + 0x14, a1);
	if (count > 3)
	{
		count *= 5;
		result = (float)count * result;
	}
	else
	{
		float a = (float)w1 - g_Va007CFB10;
		float half = g_Va007C26F0;
		float a2 = a * a;
		a2 *= half;
		float d = g_Va007C7508 - a2;
		float e = (float)w3 * half;
		d *= result;
		float f = g_Va007C7508 - e;
		result = d * f;
	}
	return result;
}
