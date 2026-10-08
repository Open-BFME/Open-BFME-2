// cl: /Oy- /DNDEBUG /MD
//
// ?parseScatterTarget@WeaponTemplate@@CAXPAVINI@@PAX1PBX@Z, retail 0x002CE813
// (54B). Zero Hour's WeaponTemplate::parseScatterTarget (Weapon.cpp) on the
// BFME 2 layout: the scatter-target vector sits at +0x40, the zeroed Coord2D
// is stored through SSE (xorps/movss, /arch:SSE) and the append is the
// out-of-line 8-byte-element push_back fold at 0x00539A2E. Target evidence:
// the WeaponTemplate FieldParse row ScatterTarget (0x00C01198) points here.
// Split from the Zero Hour port in Weapon.cpp, whose header layout puts the
// vector at +0x50 and inlines the push_back.

#define NULL 0

typedef float Real;

struct Coord2D
{
	Real x;
	Real y;
};

class INI
{
public:
	static void parseCoord2D(INI *ini, void *instance, void *store, const void *userData);
};

struct BfmeE8;
namespace _STL
{
template <class T> class allocator
{
};
template <class T, class A> class vector;
// The 8-byte push_back fold at 0x00539A2E is rowed under vector<BfmeE8>.
template <> class vector< ::BfmeE8, allocator< ::BfmeE8> >
{
public:
	void push_back(const ::BfmeE8 &x);
};
template <> class vector<Coord2D, allocator<Coord2D> >
{
public:
	void push_back(const Coord2D &x);
private:
	Coord2D *m_start;
	Coord2D *m_finish;
	Coord2D *m_endOfStorage;
};
}

class WeaponTemplate
{
private:
	static void parseScatterTarget(INI *ini, void *instance, void *store, const void *userData);

	unsigned char m_unreconstructed_00[0x40];
	_STL::vector<Coord2D, _STL::allocator<Coord2D> > m_scatterTargets;	// +0x40
};

// ?parseScatterTarget@WeaponTemplate@@CAXPAVINI@@PAX1PBX@Z
void WeaponTemplate::parseScatterTarget(INI *ini, void *instance, void * /*store*/, const void * /*userData*/)
{
	// Accept multiple listings of Coord2D's.
	WeaponTemplate *self = (WeaponTemplate *)instance;

	Coord2D target;
	target.x = 0;
	target.y = 0;
	INI::parseCoord2D(ini, NULL, &target, NULL);

	((_STL::vector<BfmeE8, _STL::allocator<BfmeE8> > *)&self->m_scatterTargets)->push_back(*(const BfmeE8 *)&target);
}
