// cl: /DNDEBUG /MD /EHsc
//
// ?iniParseEatObjectEntry@AutoPickUpUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z
// retail 0x004964EF, 409 bytes.
//
// Identity (target): the nine retail literals the body pushes name it --
// "MyHealth", "TargetHealth", "Filter" and the six
// "AutoPickUpUpdateModuleData::iniParseEatObjectEntry -- ..." messages at
// 0x00C4F188..0x00C4F428. Callees are rowed: INI::getNextTokenOrNull
// 0x0002DEED, INI::parsePercentToReal 0x0002F1BA, iniParseObjectFilter
// 0x00361CA5, the filter ctor 0x003623E5 and dtor 0x00360D26,
// INIException 0x0002F681; the push_back at 0x004964BB is rowed from
// AutoPickUpUpdateEatObjectEntryVector.cpp.
//
// Donor: BFME 1 game/GameEngine/Source/GameLogic/Object/Update/
// AutoPickUpUpdate.cpp at 6583b3c1 (same token order, messages, layout).
// BFME 2 delta, read from the target: the entry keeps its filter's real
// lifetime and the vector is the entry's own instantiation, whose growth
// path destroys elements (0x00496292), so no POD stand-in cast.

typedef float Real;

extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *a, const char *b);
extern "C" int __cdecl strcmp(const char *a, const char *b);

class INI
{
public:
	const char *getNextTokenOrNull(const char *seps);
	const char *getSepsColon() const { return m_sepsColon; }
	static void parsePercentToReal(INI *ini, void *instance, void *store, const void *userData);

private:
	char m_unreconstructed[0x420];
	const char *m_sepsColon; // +0x420
};

class INIException
{
public:
	INIException(int code, const char *format, ...);
	INIException(const INIException &other);
	~INIException();

private:
	char *m_failureMessage;
	int m_argCount;
};

// The four-byte object-filter handle: pool ctor 0x003623E5 and dtor 0x00360D26.
class Rva00360D26Member
{
public:
	Rva00360D26Member();
	~Rva00360D26Member();

private:
	unsigned int m_handle;
};

struct AutoPickUpEatObjectEntry
{
	AutoPickUpEatObjectEntry() : m_myHealth(0), m_targetHealth(1.0f) {}

	Rva00360D26Member m_filter;
	Real m_myHealth;
	Real m_targetHealth;
};

namespace _STL
{
template <class T> class allocator
{
};

template <class T, class A = allocator<T> > class vector
{
public:
	void push_back(const T &value);
};
}

void iniParseObjectFilter(INI *ini, void *instance, void *store, const void *userData);

class AutoPickUpUpdateModuleData
{
public:
	static void iniParseEatObjectEntry(INI *ini, void *instance, void *store, const void *userData);
};

#define THROW_EAT_OBJECT_ENTRY_ERROR(format, token) \
	do { \
		throw INIException(3, format, token); \
	} while (0)

void AutoPickUpUpdateModuleData::iniParseEatObjectEntry(INI *ini, void *instance, void *store, const void *)
{
	AutoPickUpEatObjectEntry entry;

	const char *token = ini->getNextTokenOrNull(ini->getSepsColon());
	if (token == 0 || _strcmpi(token, "MyHealth") != 0)
		THROW_EAT_OBJECT_ENTRY_ERROR(
			"AutoPickUpUpdateModuleData::iniParseEatObjectEntry -- Expecting 'MyHealth' entry. You specified %s.",
			token);
	if (strcmp(token, "MyHealth") != 0)
		THROW_EAT_OBJECT_ENTRY_ERROR(
			"AutoPickUpUpdateModuleData::iniParseEatObjectEntry -- Entry for 'MyHealth' is case sensitive. You specified %s.",
			token);
	INI::parsePercentToReal(ini, instance, &entry.m_myHealth, 0);

	token = ini->getNextTokenOrNull(ini->getSepsColon());
	if (token == 0 || _strcmpi(token, "TargetHealth") != 0)
		THROW_EAT_OBJECT_ENTRY_ERROR(
			"AutoPickUpUpdateModuleData::iniParseEatObjectEntry -- Expecting 'TargetHealth' entry. You specified %s.",
			token);
	if (strcmp(token, "TargetHealth") != 0)
		THROW_EAT_OBJECT_ENTRY_ERROR(
			"AutoPickUpUpdateModuleData::iniParseEatObjectEntry -- Entry for 'TargetHealth' is case sensitive. You specified %s.",
			token);
	INI::parsePercentToReal(ini, instance, &entry.m_targetHealth, 0);

	token = ini->getNextTokenOrNull(ini->getSepsColon());
	if (token == 0 || _strcmpi(token, "Filter") != 0)
		THROW_EAT_OBJECT_ENTRY_ERROR(
			"AutoPickUpUpdateModuleData::iniParseEatObjectEntry -- Expecting 'Filter' entry. You specified %s.",
			token);
	if (strcmp(token, "Filter") != 0)
		THROW_EAT_OBJECT_ENTRY_ERROR(
			"AutoPickUpUpdateModuleData::iniParseEatObjectEntry -- Entry for 'Filter' is case sensitive. You specified %s.",
			token);
	iniParseObjectFilter(ini, instance, &entry.m_filter, 0);

	((_STL::vector<AutoPickUpEatObjectEntry> *)store)->push_back(entry);
}
