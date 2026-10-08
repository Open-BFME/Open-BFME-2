// ?Rva0018BDCFFogColor@@YAXPAUID3DXEffect@@PBD@Z
// partial score=0.55 date=2026-10-08
// cl: /O1 /EHsc /MD
// Target identity: WorldBuilder fxshadernamespaceww3d.cpp:102 names
// FXShaderParameterSourceNamespaceWW3D::SourceNamespace_Fog::ResolveBindings.
// Retail 0x0018BFCE has the same IsEnabled/Color/RangeStart/RangeEnd strings,
// the default struct binder 0x00153664, parser 0x001530E9 and AddBinding
// 0x00153ACA. Callback RVAs come from its own four address stores.
// The callback handle's inline conversion is shared with the byte-matched
// water binder; 0x00080221 constructs it from the callback argument's address.

typedef const char *D3DXHANDLE;
struct FogVector { float x, y, z, w; };
struct ID3DXEffect {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21();
    virtual long __stdcall SetBool(D3DXHANDLE parameter, int value); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29();
    virtual long __stdcall SetFloat(D3DXHANDLE parameter, float value); virtual void v31();
    virtual void v32(); virtual void v33();
    virtual long __stdcall SetVector(D3DXHANDLE parameter, const FogVector *value);
};
typedef void (*FogCallback)(ID3DXEffect *, D3DXHANDLE);

struct TargetRef00217D4C {
    virtual void *destroy(unsigned flags);
    int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

class Rva00080221 {
public:
    Rva00080221(const int *arg);
    TargetRef00217D4C *m_ptr;
};

struct TreeHintRef00217D4C : public Rva00080221 {
    TreeHintRef00217D4C(FogCallback callback) : Rva00080221((const int *)&callback) {}
    ~TreeHintRef00217D4C() {
        if (m_ptr)
            ReleaseTreeHintRef00217D4C(m_ptr);
    }
};

class FXShaderParameterBinder {
public:
    void AddBinding(TreeHintRef00217D4C callback, const char *handle);
};

class FXShaderParameterSourceNamespace_Struct {
public:
    virtual ~FXShaderParameterSourceNamespace_Struct();
    virtual void ResolveBindings(const char *name, const char *handle, FXShaderParameterBinder *registry);
};

class FXShaderParameterSourceNamespaceWW3D {
public:
    class SourceNamespace_Fog : public FXShaderParameterSourceNamespace_Struct {
    public:
        virtual void ResolveBindings(const char *name, const char *handle, FXShaderParameterBinder *registry);
    };
};

struct Rva001530E9Path {
    char m_name[0x48];
    const char *m_rest;
};
void __cdecl Rva001530E9Parse(const char *name, void *volatile path);
extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *, const char *);

void Rva0018BDB8FogIsEnabled(ID3DXEffect *effect, D3DXHANDLE handle);
void Rva0018BDCFFogColor(ID3DXEffect *effect, D3DXHANDLE handle);
void Rva0018BE4CFogRangeStart(ID3DXEffect *effect, D3DXHANDLE handle);
void Rva0018BE65FogRangeEnd(ID3DXEffect *effect, D3DXHANDLE handle);

// The same globals are written by the rowed fog setup at 0x0006F0BB.
// DX8Wrapper's donor API names FogEnable/FogColor; the two range aliases
// retain the existing BFME 2 ledger spelling.
class DX8Wrapper {
public:
    __forceinline static bool Get_Fog_Enable() { return FogEnable; }
    __forceinline static unsigned long Get_Fog_Color() { return FogColor; }
    __forceinline static FogVector Convert_Color(unsigned color) {
        FogVector col;
        col.w = ((color & 0xff000000) >> 24) / 255.0f;
        col.x = ((color & 0xff0000) >> 16) / 255.0f;
        col.y = ((color & 0xff00) >> 8) / 255.0f;
        col.z = ((color & 0xff) >> 0) / 255.0f;
        return col;
    }
protected:
    static bool FogEnable;
    static unsigned long FogColor;
};
// The existing range-start alias had consumers but no definition. Retail's
// initial .data value is zero; this provider lets those consumers link.
float g_Va00DEDA28 = 0.0f;
extern float g_Va00DEDA2C;

void Rva0018BDB8FogIsEnabled(ID3DXEffect *effect, D3DXHANDLE handle)
{
    effect->SetBool(handle, DX8Wrapper::Get_Fog_Enable());
}

void Rva0018BDCFFogColor(ID3DXEffect *effect, D3DXHANDLE handle)
{
    // BFME 1 ba7ddda7e8, game/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h:
    // Convert_Color(unsigned) supplies the channel order and division shape.
    // Retail independently proves the packed global, four channels, unsigned
    // blue conversion and SetVector slot at +0x88.
    const FogVector &col = DX8Wrapper::Convert_Color(DX8Wrapper::Get_Fog_Color());
    effect->SetVector(handle, &col);
}

void Rva0018BE4CFogRangeStart(ID3DXEffect *effect, D3DXHANDLE handle)
{
    effect->SetFloat(handle, g_Va00DEDA28);
}

void Rva0018BE65FogRangeEnd(ID3DXEffect *effect, D3DXHANDLE handle)
{
    effect->SetFloat(handle, g_Va00DEDA2C);
}

void FXShaderParameterSourceNamespaceWW3D::SourceNamespace_Fog::ResolveBindings(
    const char *name, const char *handle, FXShaderParameterBinder *registry)
{
    FXShaderParameterSourceNamespace_Struct::ResolveBindings(name, handle, registry);
    if (name) {
        Rva001530E9Path path;
        Rva001530E9Parse(name, &path);
        if (_strcmpi(path.m_name, "IsEnabled") == 0)
            registry->AddBinding(Rva0018BDB8FogIsEnabled, handle);
        else if (_strcmpi(path.m_name, "Color") == 0)
            registry->AddBinding(Rva0018BDCFFogColor, handle);
        else if (_strcmpi(path.m_name, "RangeStart") == 0)
            registry->AddBinding(Rva0018BE4CFogRangeStart, handle);
        else if (_strcmpi(path.m_name, "RangeEnd") == 0)
            registry->AddBinding(Rva0018BE65FogRangeEnd, handle);
    }
}
