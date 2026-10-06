// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS
//
// ?Create_Render_Obj@@YAPAVRenderObjClass@@PBD@Z,
// retail 0x00136175, 199 bytes. Dedicated TU.
//
// Free render-object factory: a null name yields null; otherwise the name is
// lowercased through a stack AsciiString (StringBase ctor pin + toLower pin +
// releaseBuffer dtor, OptionPreferences_getCampaignDifficulty idiom), the
// counted prototype comes from the asset registry through the hidden-return
// slot (GetHTree idiom: non-trivial HierarchyPrototypeRef + 4-byte owner
// constructed by the pinned 0x136001 copy ctor), the object is produced by
// the prototype's slot-15 virtual, initialized with the name through the
// pinned 0x13BE70 call, and the owner reference is released on every path.
// Identity is proven by the matched caller bfmeCall71BA0 @0x1A3140 (which
// passes its +0x20 name here); BFME1 carries the same free function as a
// 278B naked lift (Create_Render_Obj_plain.cpp), so this is a clean-C++
// recovery of the shared factory shape, not a port.

typedef bool Bool;
typedef int Int;

template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "ascii_string.h"


class RenderObjClass;

class Rva0013BE70Host
{
public:
	void opaqueCall(const char *name);
};

class HierarchyPrototype
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual RenderObjClass *slot15();
	void Release_Ref();
};

// Counted registry reference returned by value from the asset registry.
// Non-trivial inline releasing destructor (GetHTree idiom): it forces the
// hidden-return slot, emits the guarded release inline after the owner copy,
// and shares the shell with the sibling TUs (duplicate emissions across TUs
// pass the gates, boxrobj precedent).
class HierarchyPrototypeRef
{
public:
	~HierarchyPrototypeRef()
	{
		if (m_object != 0)
			m_object->Release_Ref();
	}

private:
	HierarchyPrototype *m_object;
};

// Four-byte owner: holds the prototype pointer, constructed by the pinned
// 0x136001 copy ctor, released by the inline destructor at each exit (the
// success arm and the shared fail arm, matching the two owner-release sites;
// the temp release above is the third 0x61ED10 site).
class Rva00136001
{
public:
	Rva00136001(const HierarchyPrototypeRef &source);
	~Rva00136001()
	{
		if (m_prototype != 0)
			m_prototype->Release_Ref();
	}

	HierarchyPrototype *m_prototype; // +0x00
};

// Asset-registry prototype lookup (retail 0x0061F230, pinned).
extern HierarchyPrototypeRef __cdecl Rva0061F230_GetPrototype(const char *name);

// ?Create_Render_Obj@@YAPAVRenderObjClass@@PBD@Z
RenderObjClass *Create_Render_Obj(const char *name)
{
	if (name == 0)
		return 0;

	AsciiString lowered(name);
	lowered.toLower();

	Rva00136001 owner(Rva0061F230_GetPrototype(lowered.str()));

	if (owner.m_prototype != 0) {
		RenderObjClass *created = owner.m_prototype->slot15();
		if (created != 0) {
			((Rva0013BE70Host *)created)->opaqueCall(name);
			return created;
		}
	}
	return 0;
}
