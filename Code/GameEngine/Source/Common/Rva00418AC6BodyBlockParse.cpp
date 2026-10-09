// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /EHsc /MD /DNDEBUG
// ?Rva00418AC6Parse@@YAXPAVINI@@@Z @0x00418AC6 241B.
// LivingWorld AutoResolveBody INI block parse: the parse function of the
// block-parse entry at 0x009C8248 (name VA 0x00C10D64 parser VA 0x00818AC6)
// and its only reference. Reads the block name then the store's default body
// through rowed 0x00418825 on TheLivingWorldAutoResolveBodyStore (0x00A030B0
// registered by GameEngine::init) and builds the body value from a name copy
// and that default (rowed ctor 0x00418797) and the (name value) record
// (rowed ctor 0x0041894C) then inserts it through the store's hash table at
// +0x0C (rowed 0x00418A8E). The temporaries die through rowed 0x0022D1DF
// (record) 0x0022D01B (body) and releaseBuffer 0x00036410. A duplicate name
// throws INIException(8 "Duplicate AutoResolveBody entries named %s") through
// ThrowInfo 0x00CFE2FC; otherwise the inserted value at node+8 is filled by
// INI::initFromINI with the FieldParse table at 0x0083A8B0. WorldBuilder
// twin 0xC6B940 (LivingWorldAutoResolveBody.cpp by strings) is unnamed.
// class-gate: allow Rva004188B6 proved codegen view: retail destroys the body temporary through the folded out-of-line dtor 0x0022D01B and the canonical header's implicit dtors emit unpinned ??1Rva00418797/??1Rva0041890FRecord calls instead
// class-gate: allow Rva0041890FRecord proved codegen view: retail destroys the record temporary through the folded out-of-line dtor 0x0022D1DF which only a Rva0022D1DF base reproduces without new pins
// class-gate: allow Rva00418A8EHost proved codegen view: companion of the two dtor views above (the canonical header defines all three together)
// class-gate: allow Rva00418A12Node proved codegen view: companion of the dtor views above (same canonical header)
// class-gate: allow Rva00418A12Result proved codegen view: companion of the dtor views above (same canonical header)
#include "ascii_string.h"

struct FieldParse;

class INI
{
public:
	const char *getNextToken(const char *seps);
	void initFromINI(void *what, const FieldParse *parseTable);
};

// Dtor-only views for the out-of-line destructors retail calls on the two
// temporaries.
class Rva0022D01B
{
public:
	~Rva0022D01B();
private:
	char m_pad[0x20];
};

class Rva0022D1DF
{
public:
	~Rva0022D1DF();
private:
	char m_pad[0x24];
};

struct Rva004188B6 : Rva0022D01B
{
};

class Rva00418797 : public Rva004188B6
{
public:
	Rva00418797(const AsciiString &name, const Rva00418797 *other);
};

struct Rva0041890FRecord : Rva0022D1DF
{
	Rva0041890FRecord(const AsciiString &name, const Rva004188B6 &mapped);
};

struct Rva00418A12Node
{
	Rva00418A12Node *next;
	AsciiString key;
	char value[0x20];
};

struct Rva00418A12Result
{
	Rva00418A12Node *node;
	void *table;
	bool inserted;
};

class Rva00418A8EHost
{
public:
	int outer(int outputAddress, int recordAddress);
	// The hash_map insert wrapper; going through it puts the +0x0C this
	// adjustment between the output lea and its push as retail has it.
	__forceinline Rva00418A12Result *insert(Rva00418A12Result *output, const Rva0041890FRecord &record)
	{
		return (Rva00418A12Result *)outer((int)output, (int)&record);
	}
};

class Rva0041811D
{
public:
	void *rva00418825();
	char m_base[0x0C];
	Rva00418A8EHost m_table0C;
};

extern Rva0041811D *g_Va00E030B0;
extern const FieldParse Rva00418AC6FieldParseTable[];

struct INIException
{
	char *mFailureMessage;
	int mErrorCode;
	INIException(int argCount, const char *format, ...);
};

struct _s__ThrowInfo;
extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);
extern "C" const struct _s__ThrowInfo __identifier("_TI1?AVINIException@@");

void __cdecl Rva00418AC6Parse(INI *ini)
{
	const char *token = ini->getNextToken(0);
	const Rva00418797 *defaults = (const Rva00418797 *)g_Va00E030B0->rva00418825();
	Rva00418A12Result result;
	g_Va00E030B0->m_table0C.insert(&result, Rva0041890FRecord(token, Rva00418797(token, defaults)));
	if (!result.inserted)
	{
		INIException e(8, "Duplicate AutoResolveBody entries named %s", token);
		_CxxThrowException(&e, &__identifier("_TI1?AVINIException@@"));
		__assume(0);
	}
	ini->initFromINI(result.node->value, Rva00418AC6FieldParseTable);
}
