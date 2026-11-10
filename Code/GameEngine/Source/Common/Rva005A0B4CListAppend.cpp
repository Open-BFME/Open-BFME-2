// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?append@Rva005A0B4CList@@QAEXPAURva002BA8F1Listener@@@Z retail 0x005A0B4C 22B
// Append listener as ModuleData to vector. Evidence: named pin plus rowed
// vector push_back 0x004DFCB0; 40+ callers.
// Keep this inlined unsigned max overload local; retail has one external owner.
// Define it for speed, then restore this unit's flags for its vector bodies.
#pragma optimize("t", on)
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>
class ModuleData;
struct Rva002BA8F1Listener { char opaque[4]; };
class Rva005A0B4CList
{
public:
	void append(Rva002BA8F1Listener *p);
private:
	_STL::vector<const ModuleData *> m_vec;
};
void Rva005A0B4CList::append(Rva002BA8F1Listener *p)
{
	const ModuleData *moduleData = (const ModuleData *)(void *)p;
	m_vec.push_back(moduleData);
}

// Native 1FA574..1FA584 (16B): a file-static forwarder in cl 7.1's register
// convention (owner in ECX, caller-cleaned argument) appending a listener to
// the list at owner+0xC4 through append above, then a plain ret. No call to
// it survives in the image; the anchor below only forces cl to emit it in
// that convention. Owner and name are address-derived.
static __declspec(noinline) void Rva001FA574Append(char *owner, Rva002BA8F1Listener *p)
{
	((Rva005A0B4CList *)(owner + 0xC4))->append(p);
}

// ?Rva001FA574Anchor absent-from-retail
void Rva001FA574Anchor(char *owner, Rva002BA8F1Listener *p)
{
	Rva001FA574Append(owner, p);
}
