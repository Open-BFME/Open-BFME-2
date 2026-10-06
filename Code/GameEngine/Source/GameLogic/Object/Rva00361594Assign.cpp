// cl: /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva00361594Assign@@YAXPAVRva0036105B@@00PAX@Z @0x00361594 29B
// Range-assign wrapper over the rowed __copy core at 0x003614F4: materializes
// the random_access tag on stack and forwards (first, last, dest, tag, null).
// Evidence: chain from 0x003614F4 which muse-05 just landed; identical 29B
// shape to the landed ?Rva00288A5CAssign@@YAXPAUCameraMarker@@00PAX@Z at
// 0x00288A5C; caller at 0x00361638 passes 4 words (last is ignored dummy
// like the CameraMarker precedent's (void*)((char*)&first+3)); prev
// 0x003614F4 and next 0x003615B1 STL TUs. The core row spells the tag by
// value (U) but retail passes its address (const ref ABU, the true STLport
// spelling); the TU declares the ABU twin which is pinned at the same RVA.

namespace _STL
{
	struct random_access_iterator_tag
	{
	};
}

class Rva0036105B;

Rva0036105B *Rva003614F4Copy(Rva0036105B *first, Rva0036105B *last, Rva0036105B *dest, const _STL::random_access_iterator_tag &tag, int *extra);

void Rva00361594Assign(Rva0036105B *first, Rva0036105B *last, Rva0036105B *dest, void *unused)
{
	const _STL::random_access_iterator_tag tag;
	Rva003614F4Copy(first, last, dest, tag, (int *)0);
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?Rva00361594Assign@@YAPAVRva0036105B@@PAV1@00PAX@Z=?Rva00361594Assign@@YAXPAVRva0036105B@@00PAX@Z")
