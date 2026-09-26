// cl: /O1 /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// Shared pair initializer for LocomotorSetType maps (AIUpdate parse cluster).
// Layout-identical non-const view of the map node pair; constructs from a
// key pointer plus a template vector. The vector copy folds to the rowed
// unsigned-int spelling (twin pin).

#include <vector>

class LocomotorTemplate;

typedef _STL::vector<const LocomotorTemplate *> LocomotorTemplateVector;

struct Rva000796CBPair
{
	int first;
	LocomotorTemplateVector second;

	Rva000796CBPair(const int *key, const LocomotorTemplateVector &vec);
};

Rva000796CBPair::Rva000796CBPair(const int *key, const LocomotorTemplateVector &vec)
	: first(*key), second(vec)
{
}
