// cl: /MD
// ??_GMeshLoadContextClass@@AAEPAXI@Z @0x0018B3E0 30B; calls rowed ??1MeshLoadContextClass@@AAE@XZ @0x0018B180 then operator delete 0x0002FD60.
// Evidence: retail push esi/mov esi,ecx/call/test [esp+8],1 add-esp shape; AAE private non-virtual dtor so AAEPAXI; rowed dtor in MeshLoadContextCtor.cpp.
// ??_GMeshLoadContextClass@@AAEPAXI@Z @0x0018B3E0
class MeshLoadContextClass { private: ~MeshLoadContextClass(); friend void famgenDelete(MeshLoadContextClass *p); };
void famgenDelete(MeshLoadContextClass *p) { delete p; }
