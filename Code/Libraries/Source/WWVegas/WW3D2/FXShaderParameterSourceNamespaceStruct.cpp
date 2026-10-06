// cl: /O1 /DNDEBUG /MD /EHsc
// ?ResolveBindings@FXShaderParameterSourceNamespace_Struct@@UAEXPBD0PAVFXShaderParameterBinder@@@Z @0x00153664 134B evidence: chain from 0x001535FF; slots 0x10 0x20 0x04; reuses the binder's +0x10 and its pop 0x001531E6
// Identity: WorldBuilder's fxshaderparameterbinder.cpp:386-403 defines
// FXShaderParameterSourceNamespace_Struct::ResolveBindings with this body
// (GetParameterDesc, D3DXPC_STRUCT check, PushDynamicSetStack, then each
// member's desc and a virtual ResolveBindings, then PopDynamicSetStack). It is
// slot 1 of the default binder vftable 0x00BC6F24+8 (Rva000E19A3Dtor.cpp),
// which is why the old pin spelled it as that view's virtual.
class FXShaderParameterBinder
{
public:
	void PushDynamicSetStack(const char *name);
	void PopDynamicSetStack();
private:
	unsigned char m_pad00[0x10];
	void *m_store10;
};

struct EsiObj
{
	virtual int __stdcall s00();
	virtual int __stdcall s04();
	virtual int __stdcall s08();
	virtual int __stdcall s0C();
	virtual int __stdcall s10(const void *a, void *b);
	virtual int __stdcall s14();
	virtual int __stdcall s18();
	virtual int __stdcall s1C();
	virtual void *__stdcall s20(const void *a, int b);
};

struct QueryResult
{
	int m00;
	int m04;
	int m08;
	int m0C;
	int m10;
	int m14;
	int m18;
	int m1C;
	int m20;
	int m24;
	int m28;
};

class FXShaderParameterSourceNamespace_Struct
{
public:
	virtual ~FXShaderParameterSourceNamespace_Struct();
	virtual void ResolveBindings(const char *arg1, const char *arg2, FXShaderParameterBinder *arg3);
};

void FXShaderParameterSourceNamespace_Struct::ResolveBindings(const char *arg1, const char *arg2, FXShaderParameterBinder *arg3)
{
	if (arg1 != 0)
		return;
	EsiObj *esi = *(EsiObj **)arg3;
	QueryResult qr;
	int r = esi->s10(arg2, &qr);
	if (r < 0)
		return;
	if (qr.m08 != 5)
		return;
	arg3->PushDynamicSetStack(arg2);
	int count = qr.m20;
	if (count <= 0)
		goto done;
	for (int i = 0; i < count; i++) {
		void *found = esi->s20(arg2, i);
		if (found == 0)
			continue;
		int r2 = esi->s10(found, &qr);
		if (r2 < 0)
			continue;
		ResolveBindings((const char *)qr.m00, (const char *)found, arg3);
	}
done:
	arg3->PopDynamicSetStack();
}
