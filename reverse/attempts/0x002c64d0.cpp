// ?rva002C64D0@Rva002C5FE8@@QAEXPBUCoord3D@@H@Z
// partial score=0.9 date=2026-10-08
// cl: /MD /EHs /arch:SSE
// ?rva002C5FE8@Rva002C5FE8@@QAEPAXH@Z 0x002C5FE8 34B search pointer table at +0x20/+0x24 for entry whose first dword equals key
// Evidence: retail loops eax=[ecx+0x20] to edx=[ecx+0x24], double-derefs each element and compares to stack arg, returns entry or null; caller 0x005AB7C4 passes its own arg through
struct Coord3D { float x, y, z; };
struct Rva002C6234
{
    Rva002C6234(const Coord3D *position, float radius, void *owner);
    int id;
    Coord3D position;
    char unmodelled10[0x10];
};
class ModuleData;
namespace _STL {
template <class _Tp> class allocator {};
template <class _Tp, class _Alloc> class vector {
public:
    void **erase(void **__pos);
    void push_back(const _Tp &value);
    unsigned int size() const { return _M_finish - _M_start; }
    _Tp *_M_start, *_M_finish, *_M_end_of_storage;
};
}
void __cdecl operator delete(void *p);

class Rva002C5FE8
{
public:
	void *rva002C5FE8(int key);
	void rva002C60A9(unsigned int key);
    void rva002C64D0(const Coord3D *position, int id);
    char unmodelled00[8];
    void *owner;
    char unmodelled0C[0x14];
	void **m_begin;
	void **m_end;
};
void *Rva002C5FE8::rva002C5FE8(int key)
{
	void **end = m_end;
	for (void **p = m_begin; p != end; ++p)
	{
		if (*(int *)*p == key)
			return *p;
	}
	return 0;
}

void Rva002C5FE8::rva002C60A9(unsigned int key)
{
	typedef _STL::vector<void *, _STL::allocator<void *> > Vec;
	Vec *vec = (Vec *)&m_begin;
	for (void **p = m_begin; p != m_end;)
	{
		if (*(int *)*p == (int)key)
		{
			void *elem = *p;
			if (elem)
				operator delete(elem);
			p = vec->erase(p);
		}
		else
		{
			++p;
		}
	}
}

// Retail 0x002C64D0..0x002C65EB: complete 283-byte EH body ending RET 8.
// The +0x20 pointer list and ID-removal provider are established by the
// matched siblings above. Entry allocation is 0x20; ctor 0x002C6234 copies
// a position into +4/+8/+0xC. Original owner/method/entry names remain unknown.
void Rva002C5FE8::rva002C64D0(const Coord3D *position, int id)
{
    typedef _STL::vector<void *, _STL::allocator<void *> > EraseVec;
    EraseVec *vec = (EraseVec *)&m_begin;
    if (vec->size() >= 20)
    {
        void *entry = *m_begin;
        if (entry) operator delete(entry);
        vec->erase(m_begin);
    }
    int closest = -1;
    float nearest = -1.0f;
    void **end = m_end;
    for (void **p = m_begin; p != end; ++p)
    {
        Rva002C6234 *entry = (Rva002C6234 *)*p;
        float dx = entry->position.x - position->x;
        float dy = entry->position.y - position->y;
        float distance = dy * dy + dx * dx;
        if (nearest > distance || nearest < 0.0f)
        {
            nearest = distance;
            closest = entry->id;
        }
    }
    if (nearest >= 360000.0f || nearest == -1.0f)
    {
        position = (const Coord3D *)new Rva002C6234(position, 300.0f, owner);
        if (id != -1) ((Rva002C6234 *)position)->id = id;
        typedef _STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > PushVec;
        ((PushVec *)vec)->push_back((const ModuleData *const &)position);
    }
    else if (closest != -1)
    {
        rva002C60A9(closest);
        rva002C64D0(position, closest);
    }
}
