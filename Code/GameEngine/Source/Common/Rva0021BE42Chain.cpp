// cl: /MD
// CreateAHeroManager::CreateAHeroClass::GetAttributeMinValue/MaxValue/
// DefaultValue (0x0021BE42/0x0021BE62/0x0021BE82, 32B) and
// CreateAHeroManager::CreateAHeroSubClass::GetAttributeMinValue/MaxValue/
// DefaultValue (0x0021BDAB/0x0021BDD3/0x0021BDFB, 40B), named by WorldBuilder
// (reverse/wb_name_leads.csv; WB asserts attrib at CreateAHero.cpp:713).
// Retail callees agree: each class getter selects the subclass through
// 0x00219B9E (null yields -1 via or eax,-1) and forwards the attribute to the
// subclass getter of the same name, which looks the attribute up through
// 0x0021BD22 then reads it through 0x0021BD41 at +4/+8/+0xC (both unnamed in
// WB; 0x0021BD22 is rowed in Rva0021BD22Find.cpp). 0x0021BD41 is rowed as
// CreateAHeroSubClass::GetBlingIndex(int, const AsciiString &) from a WB lead
// (Rva0021BD41GetBlingIndex.cpp); these getters reach it with the attribute
// and a pointer into the found record, the same thiscall ABI. That the lookup
// here is a bling index is the row's naming claim, not evidence from these
// callers.
typedef unsigned int UnsignedInt;
class AsciiString;

class CreateAHeroManager
{
public:
	class CreateAHeroSubClass
	{
	public:
		int *rva0021BD22(int attribute) const;
		int GetBlingIndex(int attribute, const AsciiString &value);
		int GetAttributeMinValue(UnsignedInt attribute) const;
		int GetAttributeMaxValue(UnsignedInt attribute) const;
		int GetAttributeDefaultValue(UnsignedInt attribute) const;
	};

	class CreateAHeroClass
	{
	public:
		int GetAttributeMinValue(UnsignedInt attribute, UnsignedInt subClassIndex);
		int GetAttributeMaxValue(UnsignedInt attribute, UnsignedInt subClassIndex);
		int GetAttributeDefaultValue(UnsignedInt attribute, UnsignedInt subClassIndex);

	private:
		const CreateAHeroSubClass *rva00219B9E(UnsignedInt subClassIndex) const;	// 0x00219B9E
	};
};

typedef CreateAHeroManager::CreateAHeroClass CreateAHeroClass;
typedef CreateAHeroManager::CreateAHeroSubClass CreateAHeroSubClass;

int CreateAHeroClass::GetAttributeMinValue(UnsignedInt attribute, UnsignedInt subClassIndex)
{
	const CreateAHeroSubClass *createAHeroSub = rva00219B9E(subClassIndex);
	return createAHeroSub ? createAHeroSub->GetAttributeMinValue(attribute) : -1;
}

int CreateAHeroClass::GetAttributeMaxValue(UnsignedInt attribute, UnsignedInt subClassIndex)
{
	const CreateAHeroSubClass *createAHeroSub = rva00219B9E(subClassIndex);
	return createAHeroSub ? createAHeroSub->GetAttributeMaxValue(attribute) : -1;
}

int CreateAHeroClass::GetAttributeDefaultValue(UnsignedInt attribute, UnsignedInt subClassIndex)
{
	const CreateAHeroSubClass *createAHeroSub = rva00219B9E(subClassIndex);
	return createAHeroSub ? createAHeroSub->GetAttributeDefaultValue(attribute) : -1;
}

// Subclass getters: look the attribute up through 0x0021BD22, then read it
// through 0x0021BD41 with the entry offset (+4/+8/+0xC).
// The if/else-return form (not early return, not ternary) reproduces
// retail's jne-forward layout with the or-eax,-1 fall-through, and the
// (index, pointer) argument order reproduces the add-then-push sequence.
int CreateAHeroSubClass::GetAttributeMinValue(UnsignedInt attribute) const
{
	int minValue;
	void *minAttributeData = rva0021BD22(attribute);
	if (!minAttributeData)
		minValue = -1;
	else
		minValue = const_cast<CreateAHeroSubClass *>(this)->GetBlingIndex(attribute, *(const AsciiString *)((char *)minAttributeData + 4));
	return minValue;
}

int CreateAHeroSubClass::GetAttributeMaxValue(UnsignedInt attribute) const
{
	int maxValue;
	void *maxAttributeData = rva0021BD22(attribute);
	if (!maxAttributeData)
		maxValue = -1;
	else
		maxValue = const_cast<CreateAHeroSubClass *>(this)->GetBlingIndex(attribute, *(const AsciiString *)((char *)maxAttributeData + 8));
	return maxValue;
}

int CreateAHeroSubClass::GetAttributeDefaultValue(UnsignedInt attribute) const
{
	int defaultValue;
	void *defaultAttributeData = rva0021BD22(attribute);
	if (!defaultAttributeData)
		defaultValue = -1;
	else
		defaultValue = const_cast<CreateAHeroSubClass *>(this)->GetBlingIndex(attribute, *(const AsciiString *)((char *)defaultAttributeData + 0xC));
	return defaultValue;
}
