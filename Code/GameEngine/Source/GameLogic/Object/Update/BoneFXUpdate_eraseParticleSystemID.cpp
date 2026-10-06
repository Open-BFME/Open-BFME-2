// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// ?erase@?$vector@W4ParticleSystemID@@V?$allocator@W4ParticleSystemID@@@_STL@@@_STL@@QAEPAW4ParticleSystemID@@PAW43@0@Z,
// retail 0x00532803, 38 bytes. Dedicated TU.
//
// STLport implements vector::clear() as erase(begin(), end()), so the
// BoneFXUpdate clear() calls resolve here. ParticleSystemID is a 4-byte
// global enum, so the range erase is a trivial memmove with no element
// destruction. Anchor calls it directly to force the COMDAT emission.

#define _STLP_NO_EXCEPTIONS
#include <vector>

enum ParticleSystemID
{
	INVALID_PARTICLE_SYSTEM_ID = 0
};

typedef _STL::vector<ParticleSystemID, _STL::allocator<ParticleSystemID> > ParticleSystemIDVec;

// Anchor: emits the erase(first, last) COMDAT this TU exists to place.
ParticleSystemID *eraseParticleSystemRange(ParticleSystemIDVec *vec, ParticleSystemID *first, ParticleSystemID *last)
{
	return vec->erase(first, last);
}
