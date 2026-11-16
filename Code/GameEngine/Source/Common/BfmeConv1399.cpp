// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Open-BFME5 conversions.

#define BFME_STRINGBASE_PUBLIC_COPY
#include "../../../../reference/shims/bfme2_ascii/string_base.h"

struct BfmeBlockVKE
{
	int m_bfmeArr[16];
};

class BfmeThingVKE
{
public:
	BfmeThingVKE *bfmeInitVKE(const BfmeThingVKE &other);
	unsigned char m_bfme00[sizeof(StringBase<char>)];
	char m_bfme04;
	char m_bfmePad05[3];
	int m_bfme08;
	int m_bfme0c;
	int m_bfme10;
	int m_bfme14;
	BfmeBlockVKE m_bfme18;
};

BfmeThingVKE *BfmeThingVKE::bfmeInitVKE(const BfmeThingVKE &other)
{
	// Retail constructs the leading string through its native copy constructor.
	reinterpret_cast<StringBase<char> *>(m_bfme00)->StringBase<char>::StringBase(*reinterpret_cast<const StringBase<char> *>(other.m_bfme00));
	m_bfme04 = other.m_bfme04;
	m_bfme08 = other.m_bfme08;
	m_bfme0c = other.m_bfme0c;
	m_bfme10 = other.m_bfme10;
	m_bfme14 = other.m_bfme14;
	m_bfme18 = other.m_bfme18;
	return this;
}
