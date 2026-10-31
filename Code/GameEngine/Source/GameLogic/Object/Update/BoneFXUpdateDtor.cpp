// cl: /FIzh_ascii.h /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE -D_STLP_USE_STATIC_LIB -DNDEBUG -DWIN32 -D_WINDOWS /Ireference/shims/bfme2_bonefxupdate /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/dockupdate /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims/bfme_namekey /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/shims -ICode/Libraries/Source/Compression/LZHCompress/CompLibHeader /Ireference/shims/bfme2htree /Ireference/shims/bfme2renderobj /Ireference/shims/bfmecamera /Ireference/shims/bfmelight /Ireference/shims/bfmeparticlehandle /Ireference/shims/bfmeparticleload /Ireference/shims/bfmeparticlequat /Ireference/shims/bfmeparticlesave /Ireference/shims/bfmeparticleline /Ireference/shims/bfme2ray /Ireference/shims/bfme2scene /Ireference/shims/bfmefrustum
// stlport
//
// ??1BoneFXUpdate@@MAE@XZ, retail 0x00487ABF, 161 bytes.
//
// BoneFXUpdate virtual dtor (MAE, protected virtual, most Module/Behavior
// precedent). Donor is ZH BoneFXUpdate.cpp dtor verbatim:
// `~BoneFXUpdate() { killRunningParticleSystems(); }` — the three Coord
// arrays, the ParticleSystemID vector and the UpdateModule base are
// compiler-generated after the body, exactly as retail: vtable reinstall
// (C4B170/BEFF90/C4B164 via three-vptr UpdateModule hierarchy,
// Flood/StructureTopple precedent), killRunning call (rowed 0x487A64),
// three reverse-order ??_M destroys (0x629110 helper, dtor rowed 0xB3FD0
// Coord/validate fold, count 0x20 size 0xC), vector storage free via rowed
// _free 0x30830, base UpdateModule dtor via pin 0x24A797 (UAE). Layout
// matches the landed ctor TU (vector +0x20, frames +0x2C/+0xAC/+0x12C,
// positions +0x1AC/+0x32C/+0x4AC, curBodyState +0x62C, bonesResolved +0x630,
// active +0x634, size 0x638). /O1 for EBP frame and push-immidiates; /GX
// for EH prologue and states 4/3/2/1/0; /arch:SSE harmless (no floats here)
// and keeps the proven ctor flag combo.

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include "GameLogic/Module/BoneFXUpdate.h"

// Keep stateless allocator wrappers inline and provide the real POD-vector
// teardown used by native exception cleanup. These bodies follow the local
// allocator shim and STLport header; reusing the allocator subobject avoids
// introducing a temporary lifetime into retail's five-state EH graph.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<ParticleSystemID>::deallocate(ParticleSystemID *__p, size_t __n) const
{
    _STLP_ASSERT((__p == 0) == (__n == 0))
    if (__p != 0) ::free((void *)__p);
}

template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<ParticleSystemID *, ParticleSystemID, allocator<ParticleSystemID> >::deallocate(ParticleSystemID *__p, size_t __n)
{
    __stl_alloc_rebind(static_cast<allocator<ParticleSystemID> &>(*this),
        (ParticleSystemID *)0).deallocate(__p, __n);
}

template <> __declspec(nothrow) __forceinline
_Vector_base<ParticleSystemID, allocator<ParticleSystemID> >::~_Vector_base()
{
    if (_M_start != 0)
        _M_end_of_storage.deallocate(_M_start, _M_end_of_storage._M_data - _M_start);
}

}

BoneFXUpdate::~BoneFXUpdate()
{
	killRunningParticleSystems();
}
