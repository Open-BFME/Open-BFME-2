// cl: -D_STLP_USE_STATIC_LIB -Ireference/open-bfme-1/game/GameEngine/Source/Common
// stlport46
// Retail's caller at 0x00451E60 supplies the bidirectional iterator tag and
// reaches this __partition body through the ILT at 0x00043004. The earlier
// synthetic __uninitialized_copy pin cannot describe the in-place pointer
// swaps; the three byte fields and six mask bits are all directly observable.
#include <algorithm>

struct Rva00450B90Item
{
	char m_beforeFlags[0x24];
	bool m_flag24;
	bool m_flag25;
	bool m_flag26;
};

class Rva00450B90Predicate
{
public:
	bool operator()(const Rva00450B90Item *item) const;

	unsigned int m_mask;
};

typedef Rva00450B90Item **(*Rva00450B90PartitionFn)(
	Rva00450B90Item **, Rva00450B90Item **, Rva00450B90Predicate);

Rva00450B90PartitionFn Rva00450B90PartitionAnchor =
	&_STL::partition<Rva00450B90Item **, Rva00450B90Predicate>;
