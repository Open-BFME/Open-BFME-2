// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
//
// ??1DX8MeshRendererClass@@QAE@XZ at retail 0x00147F60 (172B). Dedicated TU:
// the Code/ dx8renderer.cpp TU builds against the ZH header (file-static
// delete lists, no such members), so the member-tearing-down BFME2 dtor
// cannot live there (same reason Clear_Pending_Delete_Lists, Shutdown and
// the member-constructing ctor live in dedicated TUs).
//
// Layout (all retail-measured, matching BFME1's dx8renderer.h member order):
// enable_lighting +0, camera +4, rigid SimpleDynVecClass +8 (vptr/Vec/Max/
// Count), skin list +0x18, TextureCategoryList member +0x1C, FVFCategoryList
// member +0x34. Every callee resolves to a ledger row or pin: Invalidate
// @0x145FA0, Clear_Pending_Delete_Lists @0x144580, scalar operator delete
// @0x2FD60, FVFCategoryList dtor @0x144750, TextureCategoryList dtor
// @0x1446F0, array operator delete @0x2FD80.
//
// Three codegen levers, each probe-proven:
// - The global deletes are declared throw() (BFME1
//   DX8MeshRendererDestructorNothrow.cpp pattern). Without it the
//   SimpleDynVecClass member teardown stays an out-of-line call; with it the
//   derived-plus-base guarded deletes inline with per-level vptr stores.
// - The skin release is spelled ::delete (global qualifier). Plain delete
//   folds to a single ??_G(1) call, but retail calls ??_G with flag 0 and
//   then the global delete separately, which is exactly the ::delete shape.
// - TextureCategoryList must be 0x18 bytes (vptr + 5-pointer Head) so the
//   FVF member sits at +0x34; a 0x14 replica shifts it to +0x30.

#include "simplevec.h"

void __cdecl operator delete(void *) throw();
void __cdecl operator delete[](void *) throw();

class CameraClass;
class DecalMeshClass;

class MultiListObjectClass
{
public:
	virtual ~MultiListObjectClass();
	void *ListNode;
};

class MultiListNodeClass
{
public:
	void *Prev;
	void *Next;
	void *NextList;
	void *Object;
	void *List;
};

class GenericMultiListClass
{
public:
	MultiListNodeClass Head;

	virtual ~GenericMultiListClass();
};

class FVFCategoryList : public GenericMultiListClass
{
public:
	virtual ~FVFCategoryList();
};

class TextureCategoryList : public GenericMultiListClass
{
public:
	virtual ~TextureCategoryList();
};

class DX8MeshRendererClass
{
public:
	~DX8MeshRendererClass();
	void Invalidate(bool shutdown);
	void Clear_Pending_Delete_Lists();

private:
	bool m_enableLighting;
	CameraClass *m_camera;
	SimpleDynVecClass<FVFCategoryList *> m_rigidLists;
	FVFCategoryList *m_skinList;
	TextureCategoryList m_textureDeleteList;
	FVFCategoryList m_fvfDeleteList;
	DecalMeshClass *m_visibleDecals;
};

// ??1DX8MeshRendererClass@@QAE@XZ
DX8MeshRendererClass::~DX8MeshRendererClass()
{
	Invalidate(true);
	Clear_Pending_Delete_Lists();
	if (m_skinList != NULL) {
		::delete m_skinList;
	}
}
