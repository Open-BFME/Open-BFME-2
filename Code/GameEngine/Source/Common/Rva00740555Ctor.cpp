// cl: /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
// ??0Rva00740555@@QAE@XZ @0x00740157 (18B). Default constructor of the SimpleSceneClass-derived
// class whose destructor is rowed at 0x00740555 (TailJumpWrappers5B.cpp) and whose scalar
// deleting destructor is 0x001042CF (slot in vtable 0x00CF1578): rowed SimpleSceneClass
// constructor 0x00142960, then the derived vtable; no member initialisation. Same shape as
// Rva00135E35Ctor.cpp. Owner of the class beyond the scene base is unproven.
// Leading slots of retail vtable 0x008F1578 (27 slots): 0 Delete_This (0x6CE57),
// 1 deleting dtor 0x1042CF, 2-5 the rowed SimpleSceneClass Add_Render_Object /
// Remove_Render_Object / Create_Iterator / Destroy_Iterator, 6 SceneClass::
// Set_Ambient_Light (0x6E265). Shared by every unit that emits ??_7Rva00740555.
class Vector3;
class RenderObjClass;
class SceneIterator;
#include "../../../Libraries/Source/WWVegas/WWLib/RefCountData.h"
class SceneClass : public RefCountClass
{
public:
	virtual void Add_Render_Object(RenderObjClass *obj) = 0;
	virtual void Remove_Render_Object(RenderObjClass *obj) = 0;
	virtual SceneIterator *Create_Iterator() = 0;
	virtual void Destroy_Iterator(SceneIterator *it) = 0;
	virtual void Set_Ambient_Light(const Vector3 &color);
};
class SimpleSceneClass : public SceneClass
{
public:
	SimpleSceneClass();
	virtual ~SimpleSceneClass();
	virtual void Add_Render_Object(RenderObjClass *obj);
	virtual void Remove_Render_Object(RenderObjClass *obj);
	virtual SceneIterator *Create_Iterator();
	virtual void Destroy_Iterator(SceneIterator *it);
private:
	char m_pad08[0x108 - 8];
};

class Rva00740555 : public SimpleSceneClass
{
public:
	Rva00740555();
	virtual ~Rva00740555();
};

__declspec(noinline) inline Rva00740555::Rva00740555()
{
}
// Select-any: another unit compiles an identical copy; the anchor keeps the rowed body emitted.
// ?bfmeAnchorRva00740555Ctor absent-from-retail
void bfmeAnchorRva00740555Ctor(Rva00740555 *p) { p->Rva00740555::Rva00740555(); }
