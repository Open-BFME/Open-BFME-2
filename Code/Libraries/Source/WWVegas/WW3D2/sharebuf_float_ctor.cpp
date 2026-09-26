// cl: /Ireference/shims/bfmerendobj /arch:SSE2 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep

// ShareBufferClass<float> for the FX particle draw-category size buffer.
//
// Retail 0x001A7B80 (141 bytes) installs vtable 0xBD71C0 and allocates
// count*4 bytes through operator new[] at 0x002FDE0; the deleting
// destructor at 0x001A7F70 calls the destructor at 0x001A7F90, which only
// frees RawBuffer through operator delete[] at 0x002FD80.
//
// Identity: the sole caller of the constructor (site 0x005C7839) passes the
// name "FXParticleSystem::CategoryModule<CAT_DRAW>::m_sizeBuffer" (read from
// retail .rdata at 0xC74988) alongside the sibling uchar/Vector4/Vector3
// buffers; the BFME1 W3DParticleSys donor sizes its parallel array with
// ShareBufferClass<float>, and the rowed PointGroup Set_Arrays at 0x00179A40
// takes the size buffer as ShareBufferClass<float> (M) next to the uchar
// angle buffer (E).
//
// Same recipe as the dword ShareBufferClass<unsigned long> trio (ctor
// 0x00169950, dtor 0x00169DA0, deleting dtor 0x00169D80): the constructor is
// emitted by use, the destructor is an explicit specialization declared
// before first use so it wins over the primary template's guarded body, and
// the deleting destructor needs no source once the destructor is rowed.

#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
#include "sharebuf.h"

extern void __cdecl operator delete[](void *) throw();

// ShareBufferClass<float> owns a raw float array (the FX draw-category
// particle sizes); the destructor frees it. The 0x1A7B80 constructor
// installs vtable 0xBD71C0, whose deleting destructor at 0x1A7F70 calls
// this body at 0x1A7F90.
template <>
ShareBufferClass<float>::~ShareBufferClass()
{
	::operator delete[](RawBuffer);
}

// Force-emit helper: instantiates the float constructor (and through the
// vtable the deleting destructor) with the retail buffer name. Sell nothing
// else; the helper itself is not a retail function.
// ?sharebuf_float_size_buffer_helper present-unmatched
ShareBufferClass<float> *sharebuf_float_size_buffer_helper(int count)
{
	return new ShareBufferClass<float>(count, "FXParticleSystem::CategoryModule<CAT_DRAW>::m_sizeBuffer");
}
