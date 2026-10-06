// cl: /MD
// ?Rva003B242CGet@@YAEXZ 0x003B242C 59B
// Evidence: NameKey cache at 0x00DBDF1C via rowed get 0x00148F5E,
// Dict at 0x00E00944 via rowed getBool 0x00313198, host bool at
// 0x00DFE16C via rowed rva00203688 0x00203688; returns dict-flag equality;
// caller 0x003B7951.
extern class ScriptEngine *TheScriptEngine;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class Rva00148F5ECache
{
public:
	NameKeyType get();
	NameKeyType m_key;
	const char *m_name;
};

// g_00DBDF1C: VA 0x00dbdf1c (.data); retail bytes 00 00 00 00 8c 97 c0 00,
// with the name pointer resolving to "isLivingWorldScriptHolder".
Rva00148F5ECache g_00DBDF1C = { NAMEKEY_INVALID, "isLivingWorldScriptHolder" };
#define TheRva00148F5ECache g_00DBDF1C

class Dict
{
public:
	bool getBool(int key, bool *exists) const;

private:
	struct DictPairData;
	DictPairData *m_data;
};

// g_Va00E00944: VA 0x00e00944 (.data/bss); retail initial bytes 00 00 00 00.
Dict g_Va00E00944;
#define TheDict g_Va00E00944

class Rva00203688Host
{
public:
	bool rva00203688();
};

#define TheRva00203688Host (*(Rva00203688Host **)&TheScriptEngine)

unsigned char Rva003B242CGet()
{
	bool flag;
	bool dictVal = TheDict.getBool(TheRva00148F5ECache.get(), &flag);
	bool b = dictVal;
	if (!flag)
		b = false;
	return b == TheRva00203688Host->rva00203688();
}
