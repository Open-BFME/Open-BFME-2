// cl: /O1 /G7 /arch:SSE /EHsc /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?Add_Rendering_Task@Rva00DF6F94GapFillerContext@@...@Z, retail 0x00174AAD (249B, EH frame, RET 8).
// FXShaderRenderer::Add_Rendering_Task (WorldBuilder assert string; the address-derived context class name
// stays until the ledger rename lands): queues a mesh with its rendering-method stack. A stack of more than six
// methods is dropped. Otherwise the mesh's light environment picks one of the context's three 32-byte-record
// queues (+0 plain; +0xC when the environment's +0x19 bit 2 is set and the byte behind its +0xBC is nonzero; +0x18
// when the bit is set and that byte is zero); a record {mesh, method count, up to six methods} is appended
// through the rowed grower 0x00174A8A and filled with the rowed holder assignment 0x00072A94. The by-value mesh
// pointer is released on exit. Evidence: target bytes; callee MeshClass::Render 0x0014BB90 (MeshClassRender.cpp)
// and the three-queue layout of Rva00DF6F94GapFillerContext (MeshGapFillerFlush.cpp). Field names are structural.
// The queues are real STLport vectors of the 32-byte record (size()/back() inline, as retail reads them); the
// rowed holder assignment is defined visibly here (inline noinline, byte-identical to its row), which is what
// lets cl drop the main-path null test of the mesh release exactly as retail does.
#include <vector>

class RefCountClass
{
public:
	virtual void Delete_This(void);
	__forceinline void Add_Ref(void) { ++NumRefs; }
	__forceinline void Release_Ref(void) { --NumRefs; if (NumRefs == 0) Delete_This(); }

protected:
	int NumRefs;
};

template <class T>
class RefCountPtr
{
public:
	RefCountPtr(const RefCountPtr &rhs) : Referent(rhs.Referent)
	{
		if (Referent) {
			Referent->Add_Ref();
		}
	}
	~RefCountPtr(void)
	{
		if (Referent) {
			Referent->Release_Ref();
		}
	}
	T *operator->() const { return Referent; }
	T *Referent;
};

namespace FXShader {
class RenderingMethod : public RefCountClass
{
};
}

struct Rva00174AADLightEnv
{
	char m_pad00[0x19];
	unsigned char m_flags;
	char m_pad1A[0xBC - 0x1A];
	unsigned char *m_ptrBC;
};

class MeshClass : public RefCountClass
{
public:
	char m_pad08[0xC4 - 0x08];
	Rva00174AADLightEnv *m_lightEnv;
};

typedef _STL::vector<RefCountPtr<FXShader::RenderingMethod>, _STL::allocator<RefCountPtr<FXShader::RenderingMethod> > > RenderingMethodStackType;

// The rowed holder assignment (0x00072A94) the record fill goes through.
class Rva00072A94
{
public:
	Rva00072A94 &operator=(const Rva00072A94 &other);
private:
	RefCountClass *m_ptr;
};
inline __declspec(noinline) Rva00072A94 &Rva00072A94::operator=(const Rva00072A94 &other)
{
	if (this != &other) {
		if (other.m_ptr)
			other.m_ptr->Add_Ref();
		if (m_ptr)
			m_ptr->Release_Ref();
		m_ptr = other.m_ptr;
	}
	return *this;
}

struct Rva00174AADRecord
{
	Rva00072A94 mesh;
	int count;
	Rva00072A94 methods[6];
};

// The rowed grower 0x00174A8A (resize to n with a default record).
class Rva00174A8A
{
public:
	void rva00174A8A(int n);
};
typedef _STL::vector<Rva00174AADRecord, _STL::allocator<Rva00174AADRecord> > Rva00174AADQueue;

class Rva00DF6F94GapFillerContext
{
public:
	void Add_Rendering_Task(RefCountPtr<MeshClass> mesh, const RenderingMethodStackType &renderingMethodStack);

private:
	Rva00174AADQueue m_plain;	// +0
	Rva00174AADQueue m_second;	// +0xC
	Rva00174AADQueue m_third;	// +0x18
};

void Rva00DF6F94GapFillerContext::Add_Rendering_Task(RefCountPtr<MeshClass> mesh, const RenderingMethodStackType &renderingMethodStack)
{
	if (renderingMethodStack.size() > 6)
		return;
	Rva00174AADRecord *record;
	Rva00174AADLightEnv *env = mesh->m_lightEnv;
	if (env->m_flags & 4)
	{
		if (*env->m_ptrBC)
		{
			((Rva00174A8A *)&m_second)->rva00174A8A((int)m_second.size() + 1);
			record = &m_second.back();
		}
		else
		{
			((Rva00174A8A *)&m_third)->rva00174A8A((int)m_third.size() + 1);
			record = &m_third.back();
		}
	}
	else
	{
		((Rva00174A8A *)&m_plain)->rva00174A8A((int)m_plain.size() + 1);
		record = &m_plain.back();
	}
	record->mesh = *(const Rva00072A94 *)&mesh;
	record->count = (int)renderingMethodStack.size();
	for (unsigned int i = 0; i < renderingMethodStack.size(); ++i)
		record->methods[i] = *(const Rva00072A94 *)&renderingMethodStack[i];
}

// Template instantiations take the optimize state at the end of the TU: retail's
// RefCountPtr<MeshClass>::~RefCountPtr (MeshClassRender.cpp) is the speed form.
#pragma optimize("t", on)
