// cl: /O1 /G7 /DNDEBUG /MD /EHsc /Oy /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
// Two more inline-COMDAT instances of the counted-pointer "construct holder, assign through the HAnim combo setter,
// copy into the hidden return, release" sequence (see W3DViewCameraHandleGet.cpp, 0x000897C8): 0x00136090 (pinned
// ?Rva00136090MeshHold, MeshModelClass holder) and 0x001007D5 (same body, own EH map). Target evidence: both retail
// bodies are byte-identical to 0x000897C8 apart from the EH map reloc; REL32 0x001007B0 is the named setter.
#include "../../../../Libraries/Source/WWVegas/WWLib/RefCountData.h"
class HAnimClass:public RefCountClass {};
class HAnimComboDataClass {HAnimClass*HAnim;public: __declspec(noinline) void Set_HAnim(HAnimClass*motion){if(motion)motion->Add_Ref();if(HAnim)HAnim->Release_Ref();HAnim=motion;}};
#include "../../../../Libraries/Source/WWVegas/WW3D2/MeshModelClass.h"
struct Rva00136090MeshHolder {
 MeshModelClass *pointer;
 Rva00136090MeshHolder():pointer(0){}
 __forceinline Rva00136090MeshHolder(const Rva00136090MeshHolder&other):pointer(other.pointer){if(pointer)pointer->Add_Ref();}
 __forceinline ~Rva00136090MeshHolder(){MeshModelClass*meshModel=pointer;if(meshModel)meshModel->Release_Ref();}
};
Rva00136090MeshHolder Rva00136090MeshHold(MeshModelClass*meshModel){
 Rva00136090MeshHolder result;
 reinterpret_cast<HAnimComboDataClass*>(&result)->Set_HAnim(reinterpret_cast<HAnimClass*>(meshModel));
 return result;
}
class Rva001007D5Model : public RefCountClass {char opaque[0x20];};
struct Rva001007D5Holder {
 Rva001007D5Model *pointer;
 Rva001007D5Holder():pointer(0){}
 __forceinline Rva001007D5Holder(const Rva001007D5Holder&other):pointer(other.pointer){if(pointer)pointer->Add_Ref();}
 __forceinline ~Rva001007D5Holder(){Rva001007D5Model*p=pointer;if(p)p->Release_Ref();}
};
Rva001007D5Holder Rva001007D5Hold(Rva001007D5Model*p){
 Rva001007D5Holder result;
 reinterpret_cast<HAnimComboDataClass*>(&result)->Set_HAnim(reinterpret_cast<HAnimClass*>(p));
 return result;
}
