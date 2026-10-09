// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?rva004E00D9@Rva004E02D7Owner@@QAEXXZ @0x004E00D9 98B: clear of the owner's two pointer vectors, byte-identical
// in shape to Rva00283CB3::rva00283505 (Map/TerrainLogicRva00283CE7.cpp): destroy and free every element of the
// vector at +0x10 (rowed destructor 0x00281A06), clear it, then pass every element of the vector at +4 to the
// same-receiver member 0x004DFF2C (rowed as Rva004E00BAOwner::rva004DFF2C in Rva004E00BA.cpp). Target evidence:
// retail body read byte for byte; the follow-up call's callee read at its REL32. Class identity unresolved; names
// are address-derived.
#include <vector>

class Object;

class Rva00281A06 { public: ~Rva00281A06(); };

class Rva004E00BAOwner
{
public:
	void rva004DFF2C(Object *object);
};

class Rva004E02D7Owner
{
public:
	void rva004E00D9();

private:
	char unknown00[4];
	_STL::vector<void *> records;
	_STL::vector<void *> holders;
};

void Rva004E02D7Owner::rva004E00D9()
{
	void **end = holders.end();
	for (void **i = holders.begin(); i != end; ++i)
		delete (Rva00281A06 *)*i;
	holders.clear();
	if (!records.empty()) {
		void **last = records.end();
		for (void **i = records.begin(); i != last; ++i)
			((Rva004E00BAOwner *)this)->rva004DFF2C((Object *)*i);
	}
}
