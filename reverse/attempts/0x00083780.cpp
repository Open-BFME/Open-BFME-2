// ?rva00083780@Rva00083780Subobject@@QAEXPAX0@Z
// partial score=0.57 date=2026-10-07
// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva00083780@Rva00083780Subobject@@QAEXPAX0@Z @0x00083780 113B: add a newly allocated refcounted object to the vector at this subobject +0x40.
// Target evidence: 0x00082140 installs vftable 0x00BC70F0 at parent +0xC8; its cleanup at 0x00082289 releases the vector at parent +0x108. The call at 0x000837AA allocates 0xA4 bytes and reaches 0x00082F6A; that constructor view installs 0x00BC7364, whose deleting dtor is rowed at 0x00082C6C. The body then calls rowed vector push_back 0x00082BE6 and generic reference release 0x0007DEEF. Owner and object names remain address-derived; the operation name is structural inference.

namespace _STL {
template <class T>
class allocator {};

template <class T, class Allocator = allocator<T> >
class vector {
public:
	T *m_start;
	T *m_finish;
	T *m_end;
	void push_back(const T &value);
};
}

struct TargetRef00217D4C {
	virtual void *destroy(unsigned flags);
	int references;
};

void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

class Rva00082F6AObject {
public:
	Rva00082F6AObject(void *argument);

private:
	char m_opaque[0xA4];
};

struct Rva00082BE6Element {
	Rva00082F6AObject *m_object;

	Rva00082BE6Element(Rva00082F6AObject *object) : m_object(object)
	{
		if (m_object)
			++*(int *)((char *)m_object + 4);
	}

	~Rva00082BE6Element()
	{
		if (m_object)
			ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_object);
	}
};

class Rva00083780Subobject {
public:
	void rva00083780(void *unused, void *constructorArgument);

private:
	char m_prefix[0x40];
	_STL::vector<Rva00082BE6Element> m_objects;
};

void Rva00083780Subobject::rva00083780(void *, void *constructorArgument)
{
	register Rva00082F6AObject *created = new Rva00082F6AObject(constructorArgument);
	Rva00082BE6Element object(created);
	m_objects.push_back(object);
}
