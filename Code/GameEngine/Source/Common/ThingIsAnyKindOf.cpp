// ?isAnyKindOf@Thing@@QBE_NABV?$BitFlags@$0EF@@@@Z @0x0030ADC7
// Shard TU: Rva001DCD30Kind.cpp hosts isNotAnyKindOf which calls this
// out-of-line; defining it there inlines and breaks it.

template <int N>
class BitFlags
{
public:
	bool test(const void *kindOf) const;
};

struct ThingTemplate
{
	char m_pad[0x108];
	int m_kindOf;
};

class Thing
{
public:
	bool isAnyKindOf(const BitFlags<69> &mask) const;

private:
	char m_pad00[4];
	ThingTemplate *m_template;
};

// ?isAnyKindOf@Thing@@QBE_NABV?$BitFlags@$0EF@@@@Z
bool Thing::isAnyKindOf(const BitFlags<69> &mask) const
{
	const void *kindOf = &m_template->m_kindOf;
	return mask.test(kindOf);
}
