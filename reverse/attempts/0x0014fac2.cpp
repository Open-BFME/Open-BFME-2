// ?ResolveBindings@Rva0014FAC2SceneNamespace@@UAEXPBD0PAVFXShaderParameterBinder@@@Z
// partial score=0.97 date=2026-10-07
// cl: /O1 /arch:SSE /MD /GX-
//
// ?ResolveBindings@Rva0014FAC2SceneNamespace@@UAEXPBD0PAVFXShaderParameterBinder@@@Z
// @0x0014FAC2 390B: slot 1 of a FX shader parameter namespace whose members at
// +0x04 (Camera), +0x10 (Time), +0x14 (AmbientLight), +0x2C (DirectionalLight),
// +0x44 (PointLight), +0x5C (Shadow) and +0xB8 (Skeleton) are themselves
// binders (a virtual slot-1 call through each). Splits the parameter name with
// the rowed Rva001530E9Parse 0x001530E9, then, as for the particle "Draw" binder
// 0x001F69B1, compares the head with _strcmpi in a fixed order: Camera, Time
// and Skeleton forward the path remainder, the other member names forward the
// whole name, and NumAmbientLights / NumDirectionalLights / NumPointLights /
// NumShadows bind a callback through FXShaderParameterBinder::AddBinding
// 0x00153ACA (NumShadows binds an object+method delegate built through
// Rva00579E47 0x00579E47 with this as the object).
// Evidence: retail body only (strings read from the image); the namespace name
// and the callback names are address tokens, not known identities.
inline void *operator new(unsigned int, void *p) { return p; }
void __cdecl Rva001530E9Parse(const char *name, void *volatile path);
extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *, const char *);

struct ID3DXEffect;
typedef void (__cdecl *Rva0014FAC2Callback)(ID3DXEffect *effect, const char *handle);

struct DelegateDesc
{
	void *m_object;
	void *m_method;
};

struct TargetRef00217D4C
{
	virtual void *destroy(unsigned flags);
	int references;
};

class Rva00080221
{
public:
	Rva00080221(const int *arg);
	TargetRef00217D4C *m_ptr;
};

class Rva00579E47
{
public:
	Rva00579E47(const DelegateDesc &desc);
	TargetRef00217D4C *m_ptr;
};

struct TreeHintRef00217D4C
{
	TargetRef00217D4C *m_ptr;
	TreeHintRef00217D4C(Rva0014FAC2Callback callback)
	{
		new (this) Rva00080221((const int *)&callback);
	}
	TreeHintRef00217D4C(const DelegateDesc &desc)
	{
		new (this) Rva00579E47(desc);
	}
};

class FXShaderParameterBinder
{
public:
	void AddBinding(TreeHintRef00217D4C callback, const char *handle);
};

struct Rva001530E9Path
{
	char m_name[0x40];
	bool m_hasStar;
	bool m_hasBracket;
	int m_index;
	const char *m_rest;
};

class Base
{
public:
	virtual ~Base() {}
	virtual void ResolveBindings(const char *name, const char *handle, FXShaderParameterBinder *registry) = 0;
};

void __cdecl Rva0014D595NumAmbientLights(ID3DXEffect *effect, const char *handle);
void __cdecl Rva0014D64CNumDirectionalLights(ID3DXEffect *effect, const char *handle);
void __cdecl Rva0014D7B1NumPointLights(ID3DXEffect *effect, const char *handle);
void __cdecl Rva0014F86CNumShadows();

class Rva0014FAC2SceneNamespace : public Base
{
public:
	virtual void ResolveBindings(const char *name, const char *handle, FXShaderParameterBinder *registry);
private:
	Base *member(int offset) { return (Base *)((char *)this + offset); }
};

void Rva0014FAC2SceneNamespace::ResolveBindings(const char *name, const char *handle, FXShaderParameterBinder *registry)
{
	Rva001530E9Path path;
	Rva001530E9Parse(name, &path);
	if (_strcmpi(path.m_name, "Camera") == 0)
		member(0x04)->ResolveBindings(path.m_rest, handle, registry);
	else if (_strcmpi(path.m_name, "Time") == 0)
		member(0x10)->ResolveBindings(path.m_rest, handle, registry);
	else if (_strcmpi(path.m_name, "NumAmbientLights") == 0)
		registry->AddBinding(Rva0014D595NumAmbientLights, handle);
	else if (_strcmpi(path.m_name, "AmbientLight") == 0)
		member(0x14)->ResolveBindings(name, handle, registry);
	else if (_strcmpi(path.m_name, "NumDirectionalLights") == 0)
		registry->AddBinding(Rva0014D64CNumDirectionalLights, handle);
	else if (_strcmpi(path.m_name, "DirectionalLight") == 0)
		member(0x2C)->ResolveBindings(name, handle, registry);
	else if (_strcmpi(path.m_name, "NumPointLights") == 0)
		registry->AddBinding(Rva0014D7B1NumPointLights, handle);
	else if (_strcmpi(path.m_name, "PointLight") == 0)
		member(0x44)->ResolveBindings(name, handle, registry);
	else if (_strcmpi(path.m_name, "NumShadows") == 0)
	{
		DelegateDesc desc;
		desc.m_object = this;
		desc.m_method = (void *)Rva0014F86CNumShadows;
		registry->AddBinding(TreeHintRef00217D4C(desc), handle);
	}
	else if (_strcmpi(path.m_name, "Shadow") == 0)
		member(0x5C)->ResolveBindings(name, handle, registry);
	else if (_strcmpi(path.m_name, "Skeleton") == 0)
		member(0xB8)->ResolveBindings(path.m_rest, handle, registry);
}
