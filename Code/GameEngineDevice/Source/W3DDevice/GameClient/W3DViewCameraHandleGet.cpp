// Native7BB79..7BBA2 is a41B conditional counted-camera value return.
// Native global byte62 gates the owner pointer0; copy increments camera+4.
// WB7EF0B0 confirms CameraClass RefCountPtr return ownership. The original
// owner/method and gate purpose remain unknown; preserve existing opaque names.
// Raw constructor must be forceinline to match the return-buffer sequence.
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
class GlobalData {public:char gap[0x62];bool reflections;};
extern GlobalData *TheWritableGlobalData;
class Rva0007BB79Owner {public:CameraClass *camera;Rva0008B689Element rva0007BB79();};
Rva0008B689Element Rva0007BB79Owner::rva0007BB79(){
 if(!TheWritableGlobalData->reflections)return Rva0008B689Element();
 return Rva0008B689Element(camera);
}
