// cl: /O1 /DNDEBUG /MD /GX-
// Rva003F1540_LookupRegionBonus (retail 0x003F1540, 47 bytes). Looks a
// region-bonus name up in the {name, value} table at 0xC36880 through the
// rowed StringBase<char>::compare at 0x00069B1, returning the paired value
// or 0 when no name matches. Serves INI::Rva003F156F_ParseRegionBonus below
// (RegionBonus entry of the table at 0x836560). The function name stays
// address-derived; the table is BFME2-new (no BFME1 donor).

template <class T> class StringBase
{
public:
	int compare(const char *text) const throw();
};

class AsciiString
{
public:
	int compare(const char *text) const { return ((const StringBase<char> *)this)->compare(text); }

private:
	void *m_data;
};

struct RegionBonusNameValue
{
	const char *name;
	int value;
};

extern RegionBonusNameValue g_regionBonusNameValues[]; // retail 0x00C36880

// ?Rva003F1540_LookupRegionBonus@@YAHABVAsciiString@@@Z
int Rva003F1540_LookupRegionBonus(const AsciiString &name)
{
	const RegionBonusNameValue *entry = g_regionBonusNameValues;
	while (entry->name != 0) {
		if (name.compare(entry->name) == 0)
			return entry->value;
		++entry;
	}
	return 0;
}
