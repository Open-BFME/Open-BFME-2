// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX-
//
// Four LivingWorld AutoResolve FieldParse procs (99B each, one shape): look
// the next token up in one of the global Rva0041811D tables through the rowed
// lookup 0x0041811D, store the hit at store, and throw INIException (rowed
// varargs ctor 0x0002F681, ThrowInfo 0x00CFE2FC) naming the token when the
// lookup fails. Target evidence per proc (table global, FieldParse token,
// message literal):
//   0x00418143  0x00E030A8  AutoResolveLeadership   "Unknown LivingWorldAutoResolveLeadership %s"
//   0x00418853  0x00E030B0  AutoResolveBody         "Unknown LivingWorldAutoResolveBody %s"
//   0x00419182  0x00E030B8  AutoResolveCombatChain  "Unknown LivingWorldAutoResolveCombatChain %s"
//   0x00419726  0x00E030C0  Weapon                  "Unknown LivingWorldAutoResolveWeapon %s"
// No EH frame around the AsciiString temporary: the unit is built without
// exception unwinding (/GX-). Names stay address-derived.
//
// Same AutoResolveWeapon table (0x00C3AAC8): DamagePerRound -> 0x0041951D
// reads "Damage" then "Against" sub-tokens and stores the real into the
// store's float array at the index scanIndexList finds in the VA 0x00DC85C4
// name table.

#include "ascii_string.h"

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	const char *getNextSubToken(const char *expected);
	float scanReal(const char *token);
	int scanIndexList(const char *token, const char *const *names);
};

class INIException
{
public:
	char *mFailureMessage;
	int m_argCount;
	INIException(int argCount, const char *format, ...);
	INIException(const INIException &other);
	~INIException();
};

class Rva0041811D
{
public:
	void *rva0041811D(const AsciiString *name);
};

extern Rva0041811D *g_Va00E030A8;
extern Rva0041811D *g_Va00E030B0;
extern Rva0041811D *g_Va00E030B8;
extern Rva0041811D *g_Va00E030C0;

// ?Rva00418143Parse@@YAXPAVINI@@PAX1PBX@Z
void Rva00418143Parse(INI *ini, void *, void *store, const void *)
{
	const char *token = ini->getNextToken();
	{
		AsciiString name(token);
		*(void **)store = g_Va00E030A8->rva0041811D(&name);
	}
	if (*(void **)store == 0)
		throw INIException(1, "Unknown LivingWorldAutoResolveLeadership %s", token);
}

// ?Rva00418853Parse@@YAXPAVINI@@PAX1PBX@Z
void Rva00418853Parse(INI *ini, void *, void *store, const void *)
{
	const char *token = ini->getNextToken();
	{
		AsciiString name(token);
		*(void **)store = g_Va00E030B0->rva0041811D(&name);
	}
	if (*(void **)store == 0)
		throw INIException(1, "Unknown LivingWorldAutoResolveBody %s", token);
}

// ?Rva00419182Parse@@YAXPAVINI@@PAX1PBX@Z
void Rva00419182Parse(INI *ini, void *, void *store, const void *)
{
	const char *token = ini->getNextToken();
	{
		AsciiString name(token);
		*(void **)store = g_Va00E030B8->rva0041811D(&name);
	}
	if (*(void **)store == 0)
		throw INIException(1, "Unknown LivingWorldAutoResolveCombatChain %s", token);
}

// ?Rva00419726Parse@@YAXPAVINI@@PAX1PBX@Z
void Rva00419726Parse(INI *ini, void *, void *store, const void *)
{
	const char *token = ini->getNextToken();
	{
		AsciiString name(token);
		*(void **)store = g_Va00E030C0->rva0041811D(&name);
	}
	if (*(void **)store == 0)
		throw INIException(1, "Unknown LivingWorldAutoResolveWeapon %s", token);
}

extern const char *g_00DC85C4[];

// ?Rva0041951DParse@@YAXPAVINI@@PAX1PBX@Z
void Rva0041951DParse(INI *ini, void *, void *store, const void *)
{
	float damage = ini->scanReal(ini->getNextSubToken("Damage"));
	const char *against = ini->getNextSubToken("Against");
	int index = ini->scanIndexList(against, g_00DC85C4);
	((float *)store)[index] = damage;
}
