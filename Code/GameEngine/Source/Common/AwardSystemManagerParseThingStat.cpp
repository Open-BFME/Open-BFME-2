// cl: /O1 /G7 /arch:SSE /EHsc /DNDEBUG /MD /Ireference/shims/bfme2_ascii
// ?parseThingStat@AwardSystemManager@@SAXPAVINI@@PAX1PBX@Z
// Retail 0x0040BC7C..0x0040BEA0 (548 bytes; the compiled body also emits the
// int3 after the final throw, which matches retail).
//
// AwardSystemManager::parseThingStat, the "ThingStat" entry (0x00839424) of
// the award system's block table next to "ObjectAward"; named by its own
// messages. Parses a thing statistic (rowed default ctor 0x0040AF1D / dtor
// 0x0040AFF3) through the field table at 0x00DC1DD8; rejects an invalid,
// "None" or empty name key (keys cached in function statics) and a name the
// award system (g_00E02F74, rowed lookup 0x0040AAF8) already has; finishes
// the lists (rowed 0x0040B4F9); requires every included / excluded template
// key (rowed 0x0040A7F1 / 0x0040A80F) to name an existing ThingTemplate
// (TheThingFactory lookup 0x002D06CA); then adds it (rowed 0x0040BAD0).
// WB twin 0x010851A0 (ThingStatistic::GetIncluded/ExcludedTemplateNameKey,
// ThingFactory::findTemplateInternal). The %s arguments use StringBase's
// str() (its TheNullChr static), not the shared header's inline "" select.
#include "ascii_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
	const AsciiString &keyToName(NameKeyType key);
};
extern NameKeyGenerator *TheNameKeyGenerator;

struct FieldParse;

class INI
{
public:
	void initFromINI(void *what, const FieldParse *parseTable);
};

class INIException
{
public:
	char *mFailureMessage;
	int mErrorCode;
	INIException(int argCount, const char *format, ...);
	INIException(const INIException &that);
	~INIException();
};

// The thing statistic (0x68 bytes): its name key at +0x00, the included and
// excluded template key lists at +0x04 / +0x10. The ledger rows its default
// ctor (0x0040AF1D) and dtor (0x0040AFF3) under two placeholder names.
class Rva0040AFF3
{
public:
	~Rva0040AFF3();

	NameKeyType m_name;		// +0x00
	int *m_includedBegin;		// +0x04
	int *m_includedEnd;		// +0x08
	int *m_includedCap;		// +0x0C
	int *m_excludedBegin;		// +0x10
	int *m_excludedEnd;		// +0x14
	int *m_excludedCap;		// +0x18
	unsigned char m_pad1C[0x68 - 0x1C];
};
class Rva0040AF1D : public Rva0040AFF3
{
public:
	Rva0040AF1D();
	UnsignedInt getIncludedCount() const { return UnsignedInt(m_includedEnd - m_includedBegin); }
	UnsignedInt getExcludedCount() const { return UnsignedInt(m_excludedEnd - m_excludedBegin); }
};
class Rva0040B4F9 { public: void rva0040B4F9(); };		// finishes the parsed lists
class Rva0040A7F1 { public: int rva0040A7F1(int index) const; };	// included template key
class Rva0040A80F { public: int rva0040A80F(int index) const; };	// excluded template key
class Rva0040AF66;

class Rva0040BAD0
{
public:
	int rva0040AAF8(int nameKey);				// finds a statistic by name
	bool rva0040BAD0(Rva0040AF66 *stat);			// adds a statistic
};
class Rva0040AAD5;
extern Rva0040AAD5 *g_00E02F74;					// the award system

class ThingTemplate;
class Rva002D06CA { public: void *rva002D06CA(const AsciiString *name); };	// template lookup
class ThingFactory;
extern ThingFactory *TheThingFactory;

extern const FieldParse g_00DC1DD8[];

// StringBase<char>::str() (its own empty-string static, which the linker
// folds onto the shared empty literal).
#define STR(s) (((const StringBase<char> *)&(s))->str())				// the ThingStat field table

class AwardSystemManager
{
public:
	static void parseThingStat(INI *ini, void *instance, void *store, const void *userData);
};

void AwardSystemManager::parseThingStat(INI *ini, void *, void *, const void *)
{
	Rva0040AF1D stat;
	ini->initFromINI(&stat, g_00DC1DD8);

	NameKeyType name = stat.m_name;
	static NameKeyType noneKey = TheNameKeyGenerator->nameToKey("None");
	static NameKeyType emptyKey = TheNameKeyGenerator->nameToKey("");
	if (name == NAMEKEY_INVALID || name == noneKey || name == emptyKey)
		throw INIException(3, "No thingStat name specified while parsing ThingStat in thingStat system.");

	const Rva0040AFF3 *existing = (const Rva0040AFF3 *)((Rva0040BAD0 *)g_00E02F74)->rva0040AAF8(name);
	if (existing != 0)
	{
		AsciiString statName = TheNameKeyGenerator->keyToName(existing->m_name);
		throw INIException(3, "An ThingStatistic with the name %s already exists.", STR(statName));
	}

	((Rva0040B4F9 *)&stat)->rva0040B4F9();

	UnsignedInt i;
	for (i = 0; i < stat.getIncludedCount(); ++i)
	{
		AsciiString templateName = TheNameKeyGenerator->keyToName((NameKeyType)((const Rva0040A7F1 *)&stat)->rva0040A7F1(i));
		const ThingTemplate *tmpl = (const ThingTemplate *)((Rva002D06CA *)TheThingFactory)->rva002D06CA(&templateName);
		if (tmpl == 0)
			throw INIException(3, "The ThingTemplate %s does not exist in AwardSystemManager::parseThingStat.", STR(templateName));
	}
	for (i = 0; i < stat.getExcludedCount(); ++i)
	{
		AsciiString templateName = TheNameKeyGenerator->keyToName((NameKeyType)((const Rva0040A80F *)&stat)->rva0040A80F(i));
		const ThingTemplate *tmpl = (const ThingTemplate *)((Rva002D06CA *)TheThingFactory)->rva002D06CA(&templateName);
		if (tmpl == 0)
			throw INIException(3, "The ThingTemplate %s does not exist in AwardSystemManager::parseThingStat.", STR(templateName));
	}

	((Rva0040BAD0 *)g_00E02F74)->rva0040BAD0((Rva0040AF66 *)&stat);
}
