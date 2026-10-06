// cl: /DNDEBUG /MD
// Retail RE: ?parsePrerequisites@ThingTemplate@@KAXPAVINI@@PAX1PBX@Z @0x0033EBB5 (54B).
//
// BFME1 donor: Code/GameEngine/Source/Common/Thing/ThingTemplate_parsePrerequisites_Thunk.cpp
// (CREATE_OVERRIDES load-type check at ini+8, prereq-vector erase of
// [begin,end), then INI::initFromINI over the field-parse table). BFME2
// adaptations (all retail-measured): the prereq vector lives at instance+0x324
// (BFME1 +0x2C4); the table is the static .rdata table at 0x810C60
// ({Object,parsePrerequisiteUnit}, {Science,parsePrerequisiteScience},
// {PlayerUpgrade,parsePrerequisiteUpgrade}, terminator) referenced as a global
// (DIR32 patches from retail, no pin); initFromINI resolves via its matched
// row; the vector erase resolves via an opaque pin (its body at 0x33EB77 is a
// separate unlanded unit: finish-store plus destroy-range, role-proven by this
// call site).
// /O1 is load-bearing over the thunk's /O2: /O2 pre-loads the erase args to
// registers (63B); /O1 pushes them from memory (54B exact). Same size-axis
// family as the push-mem effects elsewhere; the whole ThingTemplate cluster
// builds /O1.

class INI
{
public:
	void initFromINI(void *store, const struct FieldParse *table);

	int m_unk0;
	int m_unk1;
	int m_loadType;
};

struct Rva0033EB77Vec
{
	void *erasePrereqVec(void *first, void *last);

	void *m_begin;
	void *m_end;
};

struct FieldParse
{
	const char *name;
	void (__cdecl *parse)(INI *, void *, void *, const void *);
	const void *userData;
	int offset;
};

extern const FieldParse g_prereqFieldParse[];

class ThingTemplate
{
protected:
	static void __cdecl parsePrerequisites(INI *ini, void *instance, void *store, const void *userData);
};

enum { INI_LOAD_CREATE_OVERRIDES = 2 };

// ?parsePrerequisites@ThingTemplate@@KAXPAVINI@@PAX1PBX@Z
void __cdecl ThingTemplate::parsePrerequisites(INI *ini, void *instance, void * /*store*/, const void * /*userData*/)
{
	unsigned char *self = (unsigned char *)instance;

	if (ini->m_loadType == INI_LOAD_CREATE_OVERRIDES)
	{
		Rva0033EB77Vec *vec = (Rva0033EB77Vec *)(self + 0x324);
		vec->erasePrereqVec(vec->m_begin, vec->m_end);
	}

	ini->initFromINI(self + 0x324, g_prereqFieldParse);
}
