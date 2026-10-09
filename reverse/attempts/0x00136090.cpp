// ?Rva00136090MeshHold@@YA?AURva00136090MeshHolder@@PAVMeshModelClass@@@Z
// partial score=0.75 date=2026-10-09
// ?Rva00136090MeshHold@@YA?AURva00136090MeshHolder@@PAVMeshModelClass@@@Z
// partial score=0.75 date=2026-10-09
// cl: /O1 /Ob2 /DNDEBUG /MD /EHsc
// Native136090..1360EA; BFME1 refcount.h lifetime semantics (rev9cbfb551).
class MeshModelClass {public:virtual void Delete_This();int refs;
 void Add_Ref(){++refs;}
 void Release_Ref(){--refs;if(refs==0)Delete_This();}};
class HAnimClass;
class HAnimComboDataClass{public:void Set_HAnim(HAnimClass *);};
struct Rva00136090MeshHolder {
 MeshModelClass *pointer;
 Rva00136090MeshHolder():pointer(0){}
 Rva00136090MeshHolder(const Rva00136090MeshHolder &p){MeshModelClass *v=p.pointer;pointer=v;if(v)v->Add_Ref();}
 __forceinline ~Rva00136090MeshHolder(){MeshModelClass *v=pointer;if(v)v->Release_Ref();}
};
Rva00136090MeshHolder Rva00136090MeshHold(MeshModelClass *p){Rva00136090MeshHolder result;reinterpret_cast<HAnimComboDataClass *>(&result)->Set_HAnim(reinterpret_cast<HAnimClass *>(p));return result;}
