// cl: /O2 /MD
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

// ??_GVertexMaterialClass@@UAEPAXI@Z @0x13d550
class VertexMaterialClass { public: __declspec(noinline) virtual ~VertexMaterialClass(); private: int m_famgen; };
VertexMaterialClass::~VertexMaterialClass() { m_famgen = 0; }
void famgenDelete(VertexMaterialClass *p) { delete p; }

// ??_GMaterialInfoClass@@UAEPAXI@Z @0x170960
class MaterialInfoClass { public: __declspec(noinline) virtual ~MaterialInfoClass(); private: int m_famgen; };
MaterialInfoClass::~MaterialInfoClass() { m_famgen = 0; }
void famgenDelete(MaterialInfoClass *p) { delete p; }

// ??_GBfmeDirtyBase@@UAEPAXI@Z @0x6560c0
class BfmeDirtyBase { public: __declspec(noinline) virtual ~BfmeDirtyBase(); private: int m_famgen; };
BfmeDirtyBase::~BfmeDirtyBase() { m_famgen = 0; }
void famgenDelete(BfmeDirtyBase *p) { delete p; }

// ??_GRva009A45A0CollisionData@@QAEPAXI@Z @0x7588c0
class Rva009A45A0CollisionData { public: ~Rva009A45A0CollisionData(); };
void famgenDelete(Rva009A45A0CollisionData *p) { delete p; }
