// cl: /DNDEBUG /MD /EHsc

#include <new>

// Retail frees these four blocks through operator delete[]
// (??_V@YAXPAX@Z, 0x00881EF0), not the scalar operator delete at
// 0x00881EB0 -- a different 21-byte body.
#include <new>
// The base deleting destructor must call its complete destructor (retail EFAD2/28).
// Keep the base thunk out of line while preserving this owner's inline reset.
#pragma inline_depth(0)
#include "BfmeShadowPrefix.h"
#pragma inline_depth(255)

class BfmeShadowRefCount
{
public:
	virtual void Delete_This();
	int m_refCount;

	void Release_Ref()
	{
		if (--m_refCount == 0)
			Delete_This();
	}
};

struct BfmeShadowBufferEntry
{
	BfmeShadowRefCount *resource;
	void *allocation0;
	void *allocation1;
	void *allocation2;
	unsigned int unreconstructed10;
	unsigned int unreconstructed14;
};

class RenderObjClass;
class MeshClass;
class Rva00107E76Elem;
namespace _STL {
template <class T> class allocator;
template <class T, class Allocator> class vector;
}
class W3DVolumetricShadowV2 : public BfmeShadowBufferOwnerBase
{
public:
	void UpdateAndRenderZfail();
	void UpdateAndRender();
	W3DVolumetricShadowV2(W3DVolumetricShadowV2 **prevLink, RenderObjClass *resource);
	void SetShadowAngleLimit(float angle) throw();
	void rva001080B4(_STL::vector<MeshClass *, _STL::allocator<MeshClass *> > *meshes, RenderObjClass *resource);
	virtual ~W3DVolumetricShadowV2();

private:
	unsigned char m_unreconstructed_058[0x10];
	W3DVolumetricShadowV2 **m_prevLink;
	W3DVolumetricShadowV2 *m_next;
	unsigned int m_unreconstructed_070;
	BfmeShadowRefCount *m_resource;
public:
	int m_78;
	Rva00107E76Elem *m_7C;
	char m_pad80[0x8C - 0x80];
	float m_extraExtrusionPadding;
	char m_90[0x9C - 0x90];
	unsigned char m_9C;
};

W3DVolumetricShadowV2::~W3DVolumetricShadowV2()
{
	if (m_next != 0)
		m_next->m_prevLink = m_prevLink;
	*m_prevLink = m_next;

	if (m_resource != 0)
		m_resource->Release_Ref();

	for (int i = 0; i < m_78; ++i)
	{
		reinterpret_cast<BfmeShadowBufferEntry *>(m_7C)[i].resource->Release_Ref();
		::operator delete[](reinterpret_cast<BfmeShadowBufferEntry *>(m_7C)[i].allocation0);
		::operator delete[](reinterpret_cast<BfmeShadowBufferEntry *>(m_7C)[i].allocation1);
		::operator delete[](reinterpret_cast<BfmeShadowBufferEntry *>(m_7C)[i].allocation2);
	}

	::operator delete[](m_7C);
}
