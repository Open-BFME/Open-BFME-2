// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /ICode/Libraries/Include/Lib
// stlport
//
// ?Visibility_Check@RTS3DScene@@UAEXPAVCameraClass@@@Z, retail 0x00071245..0x00071606
// (961 bytes) thiscall RET 4.
//
// BFME 2's RTS3DScene::Visibility_Check (Zero Hour GeneralsMD W3DScene.cpp
// is the semantic guide; Customized_Render 0x0007054F calls it through the
// scene vtable). Target facts from the retail body: first the pending list at
// +0xBC (head +0xC0) feeds each render object to the spatial index at +0x34
// (rowed Gen_00943CF0::update 0x001416F0) and is cleared (rowed 0x0006F282);
// the frame counter at +0x104 is bumped and the occluder/occludee/translucent/
// non-occluder counters (+0x808/+0x80C/+0x7F0/+0x810) are zeroed; the render
// list at +0xEC is reset; the spatial index (unrowed 0x00142410, pinned) fills
// a node list from the camera frustum; each node's render object is added to
// the render list when force visible, or when its sphere (grown by a virtual
// margin) passes the camera's Cull_Sphere (+0x204), stamping the object's
// visibility slot (+0x18C) with the scene and the counter; objects that fail
// the drawable gate (flag 0xDEDA05 selects rowed 0x0006F3B2, else template
// byte +0x121 bit 4; rowed 0x00270260 or the +0x440 shroud byte) are removed
// again and stamped 0, translucent drawables (opacity getter 0x00272C9E or the
// object slot +0x64 below 1.0f) go to the buffer at +0x7F4 (flags 8), and the
// rest are sorted into the occluder (+0x7FC, flags 2), occludee (+0x800,
// flags 4) and non-occluder (+0x804, flags 0x10) buffers against the global
// data limits +0x974..+0x980. A second walk adds the list at +0xD4 to the
// render list. The BFME 2 differences from ZH (no behind-building-marker
// gate, bounded buffers in the scene, spatial index) are read from the bytes.
//
// Codegen findings: the three "remove and stamp 0" and two "add and stamp
// counter" sequences are the scene's inline show/hide helpers (that is what
// gives the shared tail and the stack slot order); the node list is STLport's
// slist<int> (ICF-folded rowed _Slist_base<int> ctor 0x0006FA99 and
// _M_erase_after 0x0006FABF) built with _STLP_NO_EXCEPTIONS so the compiler
// treats the end-of-function erase as nothrow like retail.
// Frame pointers stay omitted (no /Oy-): retail's slist<int>(const allocator &)
// at 0x00071233, the COMDAT this TU emits just ahead of Visibility_Check, is the
// 18-byte frameless body, which /Oy- turned into a 21-byte ebp-framed copy.
#include <slist>

#include "../../../../Libraries/Source/WWVegas/WWMath/Vector3Data.h"

class SphereClass
{
public:
	__forceinline SphereClass(const SphereClass &sphere) : Center(sphere.Center), Radius(sphere.Radius) {}
	Vector3 Center;
	float Radius;
};

class RTS3DScene;
class Drawable;
class Object;

#include "../../../../GameEngine/Include/GameClient/DrawableInfoClass.h"

class CameraClass
{
public:
	virtual void cameraSlot000();
	virtual void cameraSlot004();
	virtual void cameraSlot008();
	virtual void cameraSlot00C();
	virtual void cameraSlot010();
	virtual void cameraSlot014();
	virtual void cameraSlot018();
	virtual void cameraSlot01C();
	virtual void cameraSlot020();
	virtual void cameraSlot024();
	virtual void cameraSlot028();
	virtual void cameraSlot02C();
	virtual void cameraSlot030();
	virtual void cameraSlot034();
	virtual void cameraSlot038();
	virtual void cameraSlot03C();
	virtual void cameraSlot040();
	virtual void cameraSlot044();
	virtual void cameraSlot048();
	virtual void cameraSlot04C();
	virtual void cameraSlot050();
	virtual void cameraSlot054();
	virtual void cameraSlot058();
	virtual void cameraSlot05C();
	virtual void cameraSlot060();
	virtual void cameraSlot064();
	virtual void cameraSlot068();
	virtual void cameraSlot06C();
	virtual void cameraSlot070();
	virtual void cameraSlot074();
	virtual void cameraSlot078();
	virtual void cameraSlot07C();
	virtual void cameraSlot080();
	virtual void cameraSlot084();
	virtual void cameraSlot088();
	virtual void cameraSlot08C();
	virtual void cameraSlot090();
	virtual void cameraSlot094();
	virtual void cameraSlot098();
	virtual void cameraSlot09C();
	virtual void cameraSlot0A0();
	virtual void cameraSlot0A4();
	virtual void cameraSlot0A8();
	virtual void cameraSlot0AC();
	virtual void cameraSlot0B0();
	virtual void cameraSlot0B4();
	virtual void cameraSlot0B8();
	virtual void cameraSlot0BC();
	virtual void cameraSlot0C0();
	virtual void cameraSlot0C4();
	virtual void cameraSlot0C8();
	virtual void cameraSlot0CC();
	virtual void cameraSlot0D0();
	virtual void cameraSlot0D4();
	virtual void cameraSlot0D8();
	virtual void cameraSlot0DC();
	virtual void cameraSlot0E0();
	virtual void cameraSlot0E4();
	virtual void cameraSlot0E8();
	virtual void cameraSlot0EC();
	virtual void cameraSlot0F0();
	virtual void cameraSlot0F4();
	virtual void cameraSlot0F8();
	virtual void cameraSlot0FC();
	virtual void cameraSlot100();
	virtual void cameraSlot104();
	virtual void cameraSlot108();
	virtual void cameraSlot10C();
	virtual void cameraSlot110();
	virtual void cameraSlot114();
	virtual void cameraSlot118();
	virtual void cameraSlot11C();
	virtual void cameraSlot120();
	virtual void cameraSlot124();
	virtual void cameraSlot128();
	virtual void cameraSlot12C();
	virtual void cameraSlot130();
	virtual void cameraSlot134();
	virtual void cameraSlot138();
	virtual void cameraSlot13C();
	virtual void cameraSlot140();
	virtual void cameraSlot144();
	virtual void cameraSlot148();
	virtual void cameraSlot14C();
	virtual void cameraSlot150();
	virtual void cameraSlot154();
	virtual void cameraSlot158();
	virtual void cameraSlot15C();
	virtual void cameraSlot160();
	virtual void cameraSlot164();
	virtual void cameraSlot168();
	virtual void cameraSlot16C();
	virtual void cameraSlot170();
	virtual void cameraSlot174();
	virtual void cameraSlot178();
	virtual void cameraSlot17C();
	virtual void cameraSlot180();
	virtual void cameraSlot184();
	virtual void cameraSlot188();
	virtual void cameraSlot18C();
	virtual void cameraSlot190();
	virtual void cameraSlot194();
	virtual void cameraSlot198();
	virtual void cameraSlot19C();
	virtual void cameraSlot1A0();
	virtual void cameraSlot1A4();
	virtual void cameraSlot1A8();
	virtual void cameraSlot1AC();
	virtual void cameraSlot1B0();
	virtual void cameraSlot1B4();
	virtual void cameraSlot1B8();
	virtual void cameraSlot1BC();
	virtual void cameraSlot1C0();
	virtual void cameraSlot1C4();
	virtual void cameraSlot1C8();
	virtual void cameraSlot1CC();
	virtual void cameraSlot1D0();
	virtual void cameraSlot1D4();
	virtual void cameraSlot1D8();
	virtual void cameraSlot1DC();
	virtual void cameraSlot1E0();
	virtual void cameraSlot1E4();
	virtual void cameraSlot1E8();
	virtual void cameraSlot1EC();
	virtual void cameraSlot1F0();
	virtual void cameraSlot1F4();
	virtual void cameraSlot1F8();
	virtual void cameraSlot1FC();
	virtual void cameraSlot200();
	virtual bool Cull_Sphere(const SphereClass &sphere); // +0x204
};

class RefCountClass
{
public:
	virtual ~RefCountClass();
	int refs;
};

#include "../../../../Libraries/Source/WWVegas/WWLib/MultiListObjectClass.h"

class RenderObjClass : public RefCountClass, public MultiListObjectClass
{
public:
	virtual void renderSlot004();
	virtual void renderSlot008();
	virtual void renderSlot00C();
	virtual void renderSlot010();
	virtual void renderSlot014();
	virtual void renderSlot018();
	virtual void renderSlot01C();
	virtual void renderSlot020();
	virtual void renderSlot024();
	virtual void renderSlot028();
	virtual void renderSlot02C();
	virtual void renderSlot030();
	virtual void renderSlot034();
	virtual void renderSlot038();
	virtual void renderSlot03C();
	virtual void renderSlot040();
	virtual void renderSlot044();
	virtual void renderSlot048();
	virtual void renderSlot04C();
	virtual void renderSlot050();
	virtual void renderSlot054();
	virtual void renderSlot058();
	virtual void renderSlot05C();
	virtual void renderSlot060();
	virtual float Get_Transparency() const; // +0x64, tested < 1.0f like the drawable opacity
	virtual void renderSlot068();
	virtual void renderSlot06C();
	virtual void renderSlot070();
	virtual void renderSlot074();
	virtual void renderSlot078();
	virtual void renderSlot07C();
	virtual void renderSlot080();
	virtual void renderSlot084();
	virtual void renderSlot088();
	virtual void renderSlot08C();
	virtual void renderSlot090();
	virtual void renderSlot094();
	virtual void renderSlot098();
	virtual void renderSlot09C();
	virtual void renderSlot0A0();
	virtual void renderSlot0A4();
	virtual void renderSlot0A8();
	virtual void renderSlot0AC();
	virtual void renderSlot0B0();
	virtual void renderSlot0B4();
	virtual void renderSlot0B8();
	virtual void renderSlot0BC();
	virtual void renderSlot0C0();
	virtual void renderSlot0C4();
	virtual void renderSlot0C8();
	virtual void renderSlot0CC();
	virtual void renderSlot0D0();
	virtual void renderSlot0D4();
	virtual void renderSlot0D8();
	virtual void renderSlot0DC();
	virtual void renderSlot0E0();
	virtual void renderSlot0E4();
	virtual void renderSlot0E8();
	virtual void renderSlot0EC();
	virtual void renderSlot0F0();
	virtual void renderSlot0F4();
	virtual void renderSlot0F8();
	virtual void renderSlot0FC();
	virtual void renderSlot100();
	virtual const SphereClass &Get_Bounding_Sphere() const; // +0x104
	virtual void renderSlot108();
	virtual void renderSlot10C();
	virtual void renderSlot110();
	virtual void renderSlot114();
	virtual void renderSlot118();
	virtual float Get_Culling_Margin() const; // +0x11C, added to the sphere radius
	virtual void renderSlot120();
	virtual void renderSlot124();
	virtual void renderSlot128();
	virtual void renderSlot12C();
	virtual void renderSlot130();
	virtual void renderSlot134();
	virtual void renderSlot138();
	virtual void renderSlot13C();
	virtual void renderSlot140();
	virtual void renderSlot144();
	virtual void renderSlot148();
	virtual void renderSlot14C();
	virtual void renderSlot150();
	virtual void renderSlot154();
	virtual void renderSlot158();
	virtual DrawableInfo *Get_User_Data() const; // +0x15C
	virtual void renderSlot160();
	virtual void renderSlot164();
	virtual void renderSlot168();
	virtual void renderSlot16C();
	virtual void renderSlot170();
	virtual void renderSlot174();
	virtual void renderSlot178();
	virtual void renderSlot17C();
	virtual void renderSlot180();
	virtual void renderSlot184();
	virtual void renderSlot188();
	virtual void Set_Visible_Frame(RTS3DScene *scene, int frame); // +0x18C
	virtual int Is_Hidden() const; // +0x190
	virtual void renderSlot194();
	virtual void renderSlot198();
	virtual void renderSlot19C();
	virtual int Is_Force_Visible() const; // +0x1A0
};

class MultiListNodeClass
{
public:
	MultiListNodeClass *prev, *next, *nextList;
	MultiListObjectClass *object;
	void *list;
};

class GenericMultiListClass
{
public:
	virtual ~GenericMultiListClass();
	MultiListNodeClass Head;
};

class RefRenderObjListIterator
{
public:
	RefRenderObjListIterator(GenericMultiListClass *genericMultiList) : List(genericMultiList), CurNode(genericMultiList->Head.next) {}
	bool Is_Done() const { return CurNode == &List->Head; }
	void Next() { CurNode = CurNode->next; }
	MultiListObjectClass *Current_Object() const { return CurNode->object; }
	RenderObjClass *Peek_Obj() const { return (RenderObjClass *)Current_Object(); }
	GenericMultiListClass *List;
	MultiListNodeClass *CurNode;
};

template<class T> class RefMultiListClass : public GenericMultiListClass
{
public:
	bool Add(T *obj, bool onlyonce);
	bool Remove(T *obj);
	void Reset_List();
};

// Rowed spatial-index members (0x001416F0 update) and the unrowed collector at
// 0x00142410 (pinned; the partial bank of that body names it this way).
class Gen_00943CF0
{
public:
	void update(void *obj);
};

struct Gen_00943CF0_Node
{
	Gen_00943CF0_Node *m_next;
	void *m_value;
};

class BfmeSceneVector
{
public:
	void rva00142410(Gen_00943CF0_Node **out, CameraClass *camera, const float *margin);
};

class Rva0006F282
{
public:
	void rva0006F282();
};

template <int N> class BitFlags
{
public:
	unsigned m_words[7];
};

struct Rva0006EE7A : public BitFlags<69>
{
	Rva0006EE7A(int unused, int b1, int b2);
	Rva0006EE7A(int unused, int b1, int b2, int b3, int b4);
};

#include "../../../../GameEngine/Source/Common/Thing/thing.h"

class Player;
enum ObjectStatusTypes { OBJECT_STATUS_RVA_3A = 0x3A };
enum KindOfType { KINDOF_RVA_1BA = 0x1BA };

class Object
{
public:
	Player *getControllingPlayer() const;
	bool testStatus(ObjectStatusTypes status) const;
	bool isKindOf(KindOfType kind) const;
	char gap0[0x428];
	unsigned occlusionFrame; // +0x428
	char gap42C[0x438 - 0x42C];
	unsigned char flags438;
};

struct ThingTemplateView
{
	char gap[0x108];
	unsigned char kind[0x20]; // kindof mask at +0x108
};

class Rva0006F3B2
{
public:
	bool rva0006F3B2();
};

#include "../../../../GameEngine/Include/Common/Rva00270260.h"

class Drawable
{
public:
	float rva00272C9E(int key);
	char gap0[4];
	ThingTemplateView *tpl; // +4
	char gap8[0xFC - 8];
	Object *obj; // +0xFC
	char gap100[0x440 - 0x100];
	bool fullyObscured; // +0x440
};

extern bool bfmeCameraProjectionOverride;
class GameLogic;
extern GameLogic *TheGameLogic;
struct GameLogicView
{
	char gap[0x40];
	unsigned frame;
};
class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct GlobalDataView
{
	char gap0[0xCC];
	unsigned defaultOcclusionDelay;
	char gapD0[0x974 - 0xD0];
	int maxTranslucent;
	int maxOccluders;
	int maxOccludees;
	int maxNonOccluderOrOccludee;
};

class RTS3DScene
{
public:
	virtual void Visibility_Check(CameraClass *camera);
	char gap04[0x34 - 4];
	char spatial[0x28]; // +0x34 spatial index (Gen_00943CF0 / BfmeSceneVector view)
	char gap5C[0xBC - 0x5C];
	GenericMultiListClass pendingList; // +0xBC
	GenericMultiListClass visibleList; // +0xD4
	RefMultiListClass<RenderObjClass> RenderList; // +0xEC
	int visibilityCounter; // +0x104
	char gap108[0x7F0 - 0x108];
	int translucentCount; // +0x7F0
	RenderObjClass **translucentBuffer; // +0x7F4
	char gap7F8[4];
	RenderObjClass **occluderBuffer; // +0x7FC
	RenderObjClass **occludeeBuffer; // +0x800
	RenderObjClass **nonOccluderBuffer; // +0x804
	int occluderCount; // +0x808
	int occludeeCount; // +0x80C
	int nonOccluderCount; // +0x810

	__forceinline void showObject(RenderObjClass *robj)
	{
		RenderList.Add(robj, true);
		robj->Set_Visible_Frame(this, visibilityCounter);
	}
	__forceinline void hideObject(RenderObjClass *robj)
	{
		RenderList.Remove(robj);
		robj->Set_Visible_Frame(this, 0);
	}
};

#define VISIBILITY_GLOBALS ((GlobalDataView *)TheWritableGlobalData)

void RTS3DScene::Visibility_Check(CameraClass *camera)
{
	GenericMultiListClass *pending = &pendingList;
	for (RefRenderObjListIterator it(pending); !it.Is_Done(); it.Next())
		((Gen_00943CF0 *)spatial)->update(it.Peek_Obj());
	((Rva0006F282 *)pending)->rva0006F282();

	++visibilityCounter;
	occluderCount = 0;
	occludeeCount = 0;
	translucentCount = 0;
	nonOccluderCount = 0;

	RefMultiListClass<RenderObjClass> *renderList = &RenderList;
	renderList->Reset_List();

	// ICF-folded: retail's node list is an slist of render object pointers whose
	// rowed ctor and erase helpers are the <int> instantiations.
	_STL::slist<int> found;
	((BfmeSceneVector *)spatial)->rva00142410((Gen_00943CF0_Node **)&found, camera, 0);

	unsigned currentFrame = 0;
	if (TheGameLogic)
		currentFrame = ((GameLogicView *)TheGameLogic)->frame;
	if (currentFrame <= VISIBILITY_GLOBALS->defaultOcclusionDelay)
		currentFrame = VISIBILITY_GLOBALS->defaultOcclusionDelay + 1;

	for (Gen_00943CF0_Node *node = *(Gen_00943CF0_Node **)&found; node; node = node->m_next)
	{
		RenderObjClass *robj = (RenderObjClass *)node->m_value;
		if (robj->Is_Force_Visible())
		{
			showObject(robj);
			continue;
		}
		if (robj->Is_Hidden())
			continue;
		SphereClass sphere = robj->Get_Bounding_Sphere();
		sphere.Radius += robj->Get_Culling_Margin();
		if (camera->Cull_Sphere(sphere))
			continue;
		showObject(robj);
		DrawableInfo *drawInfo = robj->Get_User_Data();
		if (!drawInfo)
			continue;
		Drawable *draw = drawInfo->m_drawable;
		if (!draw)
			continue;
		if (bfmeCameraProjectionOverride)
		{
			if (!((Rva0006F3B2 *)draw)->rva0006F3B2())
			{
				hideObject(robj);
				continue;
			}
		}
		else if (draw->tpl->kind[0x121 - 0x108] & 4)
		{
			hideObject(robj);
			continue;
		}
		if (((Rva00270260 *)draw)->rva00270260() || draw->fullyObscured)
		{
			hideObject(robj);
			continue;
		}
		drawInfo->m_flags = 0;
		if (draw->rva00272C9E((int)robj) < 1.0f || robj->Get_Transparency() < 1.0f)
		{
			if (translucentCount < VISIBILITY_GLOBALS->maxTranslucent)
			{
				drawInfo->m_flags = 8;
				translucentBuffer[translucentCount++] = robj;
				continue;
			}
		}
		Object *object = draw->obj;
		if ((draw->tpl->kind[0] & 0x80) && occluderCount < VISIBILITY_GLOBALS->maxOccluders && !(draw->tpl->kind[0x115 - 0x108] & 0x80))
		{
			occluderBuffer[occluderCount++] = robj;
			drawInfo->m_flags |= 2;
		}
		else if (object && occludeeCount < VISIBILITY_GLOBALS->maxOccludees && !(object->flags438 & 1)
			&& ((Thing *)draw)->isAnyKindOf(Rva0006EE7A(0, 8, 10, 9, 11))
			&& !((Thing *)draw)->isAnyKindOf(Rva0006EE7A(0, 0x2F, 0x59))
			&& object->occlusionFrame <= currentFrame
			&& object->getControllingPlayer()
			&& !object->testStatus(OBJECT_STATUS_RVA_3A)
			&& !object->isKindOf(KINDOF_RVA_1BA))
		{
			occludeeBuffer[occludeeCount++] = robj;
			drawInfo->m_flags |= 4;
		}
		else if (drawInfo->m_flags == 0 && nonOccluderCount < VISIBILITY_GLOBALS->maxNonOccluderOrOccludee)
		{
			nonOccluderBuffer[nonOccluderCount++] = robj;
			drawInfo->m_flags |= 0x10;
		}
	}

	for (RefRenderObjListIterator it(&visibleList); !it.Is_Done(); it.Next())
		renderList->Add(it.Peek_Obj(), true);
}
