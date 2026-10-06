// cl: /DNDEBUG /MD
//
// Two more thin FieldParse procs (original names unproven; address names):
//
// ?Rva001DEE74Parse@@YAXPAVINI@@PAX1PBX@Z 30B @0x001DEE74 (55 FieldParse rows):
//     stores the Eva event index TheEva's lookup 0x001DE9C4 returns for the
//     next token ("None" is -1) into the int at store.
// ?Rva002567EAParse@@YAXPAVINI@@PAX1PBX@Z 16B @0x002567EA (22 FieldParse rows):
//     lets the object at store parse itself from the INI through its member
//     0x00256499 (ini, 0).
// ?Rva002C8C06Parse@@YAXPAVINI@@PAX1PBX@Z 16B @0x002C8C06: the same form for
//     the 16-byte flag set behind WeaponTemplateSet "Conditions" (0x00C00A90),
//     FlagsUsedForToggle, RevealWeaponSets and ForbiddenWeaponConditions,
//     through its member 0x002C8754 (ini, 0).

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
};

class Eva
{
public:
	int rva001DE9C4(const char *name);
};

extern Eva *TheEva;

class Rva00256499
{
public:
	void rva00256499(INI *ini, void *extra);
};

class Rva002C8754
{
public:
	void rva002C8754(INI *ini, void *extra);
};

void Rva001DEE74Parse(INI *ini, void *, void *store, const void *)
{
	const char *token = ini->getNextToken();
	*(int *)store = TheEva->rva001DE9C4(token);
}

void Rva002567EAParse(INI *ini, void *, void *store, const void *)
{
	((Rva00256499 *)store)->rva00256499(ini, 0);
}

void Rva002C8C06Parse(INI *ini, void *, void *store, const void *)
{
	((Rva002C8754 *)store)->rva002C8754(ini, 0);
}
