// cl: /O1 /MD
//
// ?Rva00190F8E_BindStandardSemantics@@YAXPAVFXShaderParameterBinder@@@Z @
// 0x00190F8E (217 bytes), called only from FXShaderParameterBinder::Init
// (0x00153F08) once the SasBindAddress annotations are bound. Target
// evidence: the binder's effect at +0, GetParameterBySemantic (ID3DXEffect
// slot 10) and the binder's bind-address resolver 0x0015306D. Each of the
// five matrix semantics ("World" .. "WorldViewProjection", 32-byte .data
// slots at 0x00DB6518) is tried bare, "Inverse" and "InverseTranspose"
// (0x00DB66F8) and bound to its Sas address (64-byte slots at 0x00DB65B8)
// with ".<suffix>" appended; then "Time" and "Ambient" (0x00DB6758) are bound
// to "Sas.Time.Now" and "Sas.AmbientLight[0].Color" (0x00DB6798). The name
// keeps the address token: the owner is unproven.

extern "C" {
char *__cdecl strcpy(char *d, const char *s);
char *__cdecl strcat(char *d, const char *s);
}

typedef long HRESULT;
typedef const char *D3DXHANDLE;

#define FX_SLOT(n) virtual HRESULT __stdcall slot##n()

struct ID3DXEffect
{
	FX_SLOT(00);
	FX_SLOT(01);
	FX_SLOT(02);
	FX_SLOT(03);
	FX_SLOT(04);
	FX_SLOT(05);
	FX_SLOT(06);
	FX_SLOT(07);
	FX_SLOT(08);
	FX_SLOT(09);
	virtual D3DXHANDLE __stdcall GetParameterBySemantic(D3DXHANDLE param, const char *semantic);
};

class FXShaderParameterBinder
{
public:
	void ResolveBindings(const char *address, D3DXHANDLE param);

	ID3DXEffect *m_effect;	// +0
};

static char s_matrixSemantics[5][32] = {
	"World",
	"View",
	"Projection",
	"WorldView",
	"WorldViewProjection"
};

static char s_matrixAddresses[5][64] = {
	"Sas.Skeleton.MeshToJointToWorld[0]",
	"Sas.Camera.WorldToView",
	"Sas.Camera.Projection",
	"Sas.Skeleton.MeshToJointToView[0]",
	"Sas.Skeleton.MeshToJointToProjection[0]"
};

static char s_matrixSuffixes[3][32] = {
	"",
	"Inverse",
	"InverseTranspose"
};

static char s_otherSemantics[2][32] = {
	"Time",
	"Ambient"
};

static char s_otherAddresses[2][32] = {
	"Sas.Time.Now",
	"Sas.AmbientLight[0].Color"
};

void __cdecl Rva00190F8E_BindStandardSemantics(FXShaderParameterBinder *binder)
{
	ID3DXEffect *effect = binder->m_effect;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 3; j++) {
			char semantic[64];
			strcpy(semantic, s_matrixSemantics[i]);
			strcat(semantic, s_matrixSuffixes[j]);
			D3DXHANDLE param = effect->GetParameterBySemantic(0, semantic);
			if (param != 0) {
				strcpy(semantic, s_matrixAddresses[i]);
				if (s_matrixSuffixes[j][0] != 0) {
					strcat(semantic, ".");
					strcat(semantic, s_matrixSuffixes[j]);
				}
				binder->ResolveBindings(semantic, param);
			}
		}
	}
	for (int k = 0; k < 2; k++) {
		D3DXHANDLE param = effect->GetParameterBySemantic(0, s_otherSemantics[k]);
		if (param != 0)
			binder->ResolveBindings(s_otherAddresses[k], param);
	}
}
