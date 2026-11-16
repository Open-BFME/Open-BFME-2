// LivingWorldRegionEffectsManager: canonical declarations for the members units call through private views of it.
// Retail allocates 0x58 bytes (0x003EF4AF) for ctor 0x003EEAFB, which stores ints at +0x14 and +0x44;
// the rest of the layout stays opaque.
#ifndef CANONICAL_LIVINGWORLDREGIONEFFECTSMANAGER_H
#define CANONICAL_LIVINGWORLDREGIONEFFECTSMANAGER_H

namespace _STL { template <class T> class allocator; template <class T, class A> class vector; }
struct FieldParse;

class LivingWorldRegionEffectsManager
{
public:
	void SyncRegion(int value);
	void rva003EF13E(int value, int, int);
	void rva003EF2FF();
	void rva003EE84A(int regionAddress, int b);
	void rva003EE884(int regionArg);
	void rva003EF1D9(const _STL::vector<int, _STL::allocator<int> > &vec);

	static FieldParse s_parseTable[];

	char m_pad00[0x14];	// vftable 0x008363C8, +0x04 and the map holder the ctor builds at +0x08
	int m_14;	// retail ctor stores 0
	char m_pad18[0x44 - 0x18];
	int m_44;	// region selector SyncRegion switches on
	char m_pad48[0x58 - 0x48];
};

#endif // CANONICAL_LIVINGWORLDREGIONEFFECTSMANAGER_H
