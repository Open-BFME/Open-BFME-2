// cl: /O1 /Oy- /DNDEBUG /MD /GX-
// Rva003F156F_ParseRegionBonus (retail 0x003F156F, 50 bytes). Reads one
// token through the rowed getNextTokenOrNull at 0x002DEED with the
// m_sepsColon separators at ini+0x420, wraps it in a stack AsciiString
// (homed in the dead ini param slot, torn down by tail-jump), and stores
// the rowed Rva003F1540_LookupRegionBonus result at 0x003F1540 as an int.
// The temp constructs through the pinned AsciiString const-char ctor at
// 0x00037BA0 and tears down through the pinned AsciiString dtor at
// 0x00036410 (both twin-pinned onto the identical StringBase bodies;
// empty-derived layout). Serves the RegionBonus entry of the table at
// 0x836560. The callback name stays address-derived; the owning struct is
// BFME2-new (no BFME1 donor).

template <class T> class StringBase
{
public:
	int compare(const char *text) const throw();

private:
	void *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString(const char *text);
	~AsciiString();
	int compare(const char *text) const { return ((const StringBase<char> *)this)->compare(text); }
};

class INI
{
public:
	const char *getNextTokenOrNull(const char *seps);
	static void Rva003F156F_ParseRegionBonus(INI *ini, void *instance, void *store, const void *userData);

private:
	char _pad[0x420];
	const char *m_sepsColon;
};

int Rva003F1540_LookupRegionBonus(const AsciiString &name);

// ?Rva003F156F_ParseRegionBonus@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva003F156F_ParseRegionBonus(INI *ini, void *instance, void *store, const void *userData)
{
	AsciiString name(ini->getNextTokenOrNull(ini->m_sepsColon));
	*(int *)store = Rva003F1540_LookupRegionBonus(name);
}
