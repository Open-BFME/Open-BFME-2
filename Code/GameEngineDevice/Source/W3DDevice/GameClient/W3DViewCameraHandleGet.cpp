// Also native897C8..89822: default counted temporary, raw assignment,
// copy into the hidden return and release the temporary (90B, one EH map).
// Its REL32 uses1007B0, the existing named HAnim counted-pointer assignment
// provider; both pointee prefixes are target refcount4/DeleteThis0. This
// emitted inline COMDAT must equal that provider byte-for-byte. A visible
// assignment body proves pointer flow and removes the copy/dtor alias reload;
// noinline retains the native37B out-of-line call. Names remain address-derived
// for the camera result factory and element; no new callee alias is asserted.
// Native7BB79..7BBA2 is a41B conditional counted-camera value return.
// Native global byte62 gates the owner pointer0; copy increments camera+4.
// WB7EF0B0 confirms CameraClass RefCountPtr return ownership. The original
// owner/method and gate purpose remain unknown; preserve existing opaque names.
// Raw constructor must be forceinline to match the return-buffer sequence.
// cl: /O1 /G7 /DNDEBUG /MD /EHsc /Oy
class RefCountClass {public:virtual void Delete_This();int refs;__forceinline void Add_Ref(){refs++;}__forceinline void Release_Ref(){refs--;if(refs==0)Delete_This();}};
class CameraClass : public RefCountClass {char opaque[0x3f4];};
class HAnimClass:public RefCountClass {};
class HAnimComboDataClass {HAnimClass*HAnim;public: __declspec(noinline) void Set_HAnim(HAnimClass*motion){if(motion)motion->Add_Ref();if(HAnim)HAnim->Release_Ref();HAnim=motion;}};
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
