// cl: /MD
// Same-shape family as FamilyDeletingDtors3.cpp but caller cleanup as
// add-esp (je+9, 30B) instead of pop-ecx (je+7, 28B); /O2 speed opts pick
// add-esp where /O1 size-opts pop-ecx (probe-proven). Members selected by a
// rowed dtor callee; the dtor call resolves through that row.

// ??_GDX8MeshRendererClass@@QAEPAXI@Z @0x11cbf0
class DX8MeshRendererClass { public: ~DX8MeshRendererClass(); };
void famgenDelete(DX8MeshRendererClass *p) { delete p; }

// ??_GBfmeEnumerationCaps@@QAEPAXI@Z @0x11fe00
class BfmeEnumerationCaps { public: ~BfmeEnumerationCaps(); };
void famgenDelete(BfmeEnumerationCaps *p) { delete p; }

// Native 0x0013D550 calls the real destructor at 0x0013C990.
// vertmaterial.cpp already emits its matching scalar wrapper.
class VertexMaterialClass { public: virtual ~VertexMaterialClass(); };
void famgenDelete(VertexMaterialClass *p) { delete p; }

// Native 0x006560C0 calls the real seven-byte destructor at 0x00658650.
// Its scalar wrapper is emitted by DirtySock/BfmeDirtyBaseDtor.cpp.
// Defining a placeholder here emitted a wrong fourteen-byte destructor copy.
class BfmeDirtyBase { public: virtual ~BfmeDirtyBase(); };
void famgenDelete(BfmeDirtyBase *p) { delete p; }

// ??_GRva009A45A0CollisionData@@QAEPAXI@Z @0x7588c0
class Rva009A45A0CollisionData { public: ~Rva009A45A0CollisionData(); };
void famgenDelete(Rva009A45A0CollisionData *p) { delete p; }
