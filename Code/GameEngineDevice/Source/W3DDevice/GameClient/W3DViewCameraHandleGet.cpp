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
// cl: /O1 /G7 /DNDEBUG /MD /EHsc /Oy /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
#include "../../../../Libraries/Source/WWVegas/WW3D2/CameraClass.h"
struct Rva0008B689Element {
 CameraClass *pointer;
 Rva0008B689Element():pointer(0){}
 __forceinline Rva0008B689Element(CameraClass*camera):pointer(camera){if(pointer)pointer->Add_Ref();}
 __forceinline Rva0008B689Element(const Rva0008B689Element&other):pointer(other.pointer){if(pointer)pointer->Add_Ref();}
 __forceinline ~Rva0008B689Element(){CameraClass*camera=pointer;if(camera)camera->Release_Ref();}
};
#include "../../../../GameEngine/Include/Common/GlobalData.h"
extern GlobalData *TheWritableGlobalData;
#include "../../../Include/W3DDevice/GameClient/Rva0007BB79Owner.h"
Rva0008B689Element Rva0007BB79Owner::rva0007BB79(){
 if(!TheWritableGlobalData->m_useShadowMapping)return Rva0008B689Element();
 return Rva0008B689Element(camera);
}

// Native7FD57..7FD89 RET8, camera raw argument refreshes owner before
// copying the counted camera handle at FC. WB744500 agrees on both operations.
