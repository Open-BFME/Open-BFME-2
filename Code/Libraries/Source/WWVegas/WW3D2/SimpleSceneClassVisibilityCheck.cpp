// cl: /Ireference/shims/bfme2ray /Ireference/shims/bfme2scene /Ireference/shims/bfme2renderobj /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep /O2 /G7 /arch:SSE
// ?Visibility_Check@SimpleSceneClass@@UAEXPAVCameraClass@@@Z, retail 0x001426D0, 523 bytes.
// Native SimpleScene constructor 142960 stores vftable BD33D0; slot27 points
// at this body. ZH Visibility_Check supplies the force-visible/cull role;
// BFME2 adds changed-object spatial updates and a visible owning list.
// Callee rva00142410 is the unrowed spatial collect at 0x00142410 (pinned at land).
// Camera cull goes through the first virtual past CameraClass's own table.
// RefCountClass's inline members and deleting destructor are retail's
// size-optimised bodies: compile them for size, as hlod.cpp does.
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it; retail links the
// /O1 body at 0x00001423. Instantiate it first in an unemitted anchor (the
// lookuptable.cpp pattern) so this unit's copy is that body.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
// multilist.h's inline members are retail's size-optimised bodies: compile
// them for size (as hlod.cpp/decalsys.cpp do) so this unit's copies match.
#include "multilist.h"
#pragma optimize("", on)
#include "refcount.h"
#include "rendobj.h"
#include "aabox.h"
#include "scene.h"
#include "camera.h"
// bfme link decl-only begin
template <> RenderObjClass * RefMultiListClass<RenderObjClass>::Peek_Head();
template <> void RefMultiListClass<RenderObjClass>::Reset_List();
// bfme link decl-only end
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

#include "Gen_00943CF0_Node.h"

class Rva0006EFC8
{
public:
	bool rva0006EFC8(int arena, int size);

	int m_00;
	void *m_04;
	void *m_head;
	void *(__cdecl *m_alloc)(int size, int arg);
	void (__cdecl *m_free)(void *ptr, int arg);
	int m_14;
};

extern Rva0006EFC8 g_BfmeSceneNodePool; // owned by Rva0006EFC8Grow.cpp (VA 0xDB424C)

struct Rva0006FB50List
{
	Gen_00943CF0_Node *head;
	~Rva0006FB50List() throw()
	{
		Gen_00943CF0_Node *current = head;
		while (current) {
			Gen_00943CF0_Node *old = current;
			current = current->m_next;
			old->m_next = (Gen_00943CF0_Node *)g_BfmeSceneNodePool.m_head;
			g_BfmeSceneNodePool.m_head = old;
		}
	}
};

class Gen_00943CF0
{
	friend class SimpleSceneClass;
	void first(void *, int *, int *, int *);
};

class BfmeSceneVector
{
public:
	void rva00142410(Gen_00943CF0_Node **out, CameraClass *camera, const float *margin);
};

// Native camera extends the RenderObj/Camera prefix by sphere culling.
// Only this target call contract is asserted; original extension name unknown.
class SceneVisibilityCamera : public CameraClass
{
public:
	virtual bool rva001426D0Cull(const SphereClass &sphere) = 0;
};
typedef char SceneVisibilityCameraSize[(sizeof(SceneVisibilityCamera) == sizeof(CameraClass)) ? 1 : -1];

void SimpleSceneClass::Visibility_Check(CameraClass *camera)
{
	MultiListIterator<RenderObjClass> changed(&_bfme_changed_objects);
	for (; !changed.Is_Done(); changed.Next()) {
		RenderObjClass *obj = changed.Peek_Obj();
		volatile int outY, outX, outLevel;
		((Gen_00943CF0 *)&_bfme_spatial_index)->first(obj, (int *)&outY, (int *)&outX, (int *)&outLevel);
		int token = *(volatile int *)&SceneClass::_bfme_spatial_token(obj);
		int level = outLevel;
		int x = outX;
		int y = outY;
		if (token >= 0) {
			int key = (((y << 10) | x) << 10 | level);
			if (key == token) continue;
			_bfme_spatial_index.Remove(obj);
		}
		_bfme_spatial_index.Insert(obj, y, x, level);
	}
	MultiListClass<RenderObjClass> *dirty = &_bfme_changed_objects;
	while (dirty->Peek_Head() != 0) dirty->Remove_Head();
	++_bfme_visibility_token;
	RefMultiListClass<RenderObjClass> *visible = &_bfme_visible_objects;
	visible->Reset_List();
	Rva0006FB50List objects = {0};
	((BfmeSceneVector *)&_bfme_spatial_index)->rva00142410(&objects.head, camera, 0);
	for (Gen_00943CF0_Node *node = objects.head; node; node = (node->m_next ? node->m_next : node->m_next)) {
		RenderObjClass *obj = (RenderObjClass *)node->m_value;
		if (obj->Is_Force_Visible() || !((SceneVisibilityCamera *)camera)->rva001426D0Cull(obj->Get_Bounding_Sphere())) {
			visible->Add(obj);
			obj->Set_Visible((int)this, _bfme_visibility_token);
		}
	}
	MultiListIterator<RenderObjClass> forced(&_bfme_forced_objects);
	for (; !forced.Is_Done(); forced.Next()) {
		RenderObjClass *forcedObj = forced.Peek_Obj();
		visible->Add(forcedObj);
	}
}
