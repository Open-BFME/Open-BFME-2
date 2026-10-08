// cl: /O1 /EHsc /MD
// Target identity: WorldBuilder fxshadernamespaceww3d.cpp:102 names
// FXShaderParameterSourceNamespaceWW3D::SourceNamespace_Fog::ResolveBindings.
// Retail 0x0018BFCE has the same IsEnabled/Color/RangeStart/RangeEnd strings,
// the default struct binder 0x00153664, parser 0x001530E9 and AddBinding
// 0x00153ACA. Callback RVAs come from its own four address stores.
// The callback handle's inline conversion is shared with the byte-matched
// water binder; 0x00080221 constructs it from the callback argument's address.

struct ID3DXEffect;
typedef const char *D3DXHANDLE;
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
