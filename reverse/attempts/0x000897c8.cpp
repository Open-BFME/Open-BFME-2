// ?Rva000897C8@@YA?AURva0008B689Element@@PAVCameraClass@@@Z
// partial score=0.7892063492063492 date=2026-10-09
// cl: /O1 /G7 /DNDEBUG /MD /EHsc /Oy-
class RefCountClass {public:virtual void Delete_This();int refs;__forceinline void Add_Ref(){refs++;}__forceinline void Release_Ref(){refs--;if(refs==0)Delete_This();}};
class CameraClass : public RefCountClass {char opaque[0x3f4];};
class HAnimClass;
class HAnimComboDataClass {public:void Set_HAnim(HAnimClass*);};
struct Rva0008B689Element {
 CameraClass *pointer;
 Rva0008B689Element():pointer(0){}
 __forceinline Rva0008B689Element(CameraClass*p):pointer(p){if(pointer)pointer->Add_Ref();}
 __forceinline Rva0008B689Element(const Rva0008B689Element&o):pointer(o.pointer){if(pointer)pointer->Add_Ref();}
 __forceinline ~Rva0008B689Element(){CameraClass*p=pointer;if(p)p->Release_Ref();}
};
Rva0008B689Element Rva000897C8(CameraClass*p){
 Rva0008B689Element result;
 reinterpret_cast<HAnimComboDataClass*>(&result)->Set_HAnim(reinterpret_cast<HAnimClass*>(p));
 return result;
}
class GlobalData {public:char gap[0x62];bool reflections;};
extern GlobalData *TheWritableGlobalData;
class Rva0007BB79Owner {public:CameraClass *camera;Rva0008B689Element rva0007BB79();};
Rva0008B689Element Rva0007BB79Owner::rva0007BB79(){
 if(!TheWritableGlobalData->reflections)return Rva0008B689Element();
 return Rva0008B689Element(camera);
}
