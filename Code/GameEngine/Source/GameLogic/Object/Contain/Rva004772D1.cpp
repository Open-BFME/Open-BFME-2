// cl: /DNDEBUG /MD
// Target evidence: Ghidra boundary 0x004772D1, 52 bytes. The body receives an
// Object pointer and reads a begin/end pointer pair from the second argument.
// It tests each UpgradeTemplate through the existing 0x002940B9 Object pin,
// then applies accepted entries with matched Object::rva00293077. The pair's
// larger owner/type and this utility's higher-level identity remain unresolved.

class UpgradeTemplate;

class Object
{
public:
	bool rva002940B9(const UpgradeTemplate *upgrade);
	void rva00293077(const void *upgrade);
};

struct Rva004772D1RangePrefix
{
	UpgradeTemplate **begin;
	UpgradeTemplate **end;
};

void rva004772D1(Object *object, const Rva004772D1RangePrefix &range)
{
	for (UpgradeTemplate **it = range.begin; it != range.end; ++it) {
		UpgradeTemplate *upgrade = *it;
		if (object->rva002940B9(upgrade))
			object->rva00293077(upgrade);
	}
}
