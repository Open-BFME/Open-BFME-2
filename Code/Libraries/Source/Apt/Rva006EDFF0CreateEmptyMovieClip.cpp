// cl: /DNDEBUG /MD /EHsc
// Native EDFF0..EE1A1 (434B): the createEmptyMovieClip callback. With other
// than two arguments it returns undefined. Otherwise it reads the instance
// name (stack argument 0) and depth (argument 1), allocates a 0x40-byte
// empty character from the 0xE176E8 chain pool (AptCharacter.cpp 0x5BD
// "pCharacter" assert), marks it type 5 with cleared fields and the
// receiver movie's resource word, and submits it through the pinned
// AptDisplayList submit 0x006F8B70 to the receiver's display list at depth
// + 0x4000 under the name, after AptCIH.h's isCharacterInst() (0xA5) and
// isSpriteInstBase() (0x7D) asserts. A CIH result has its 0x006E3C80 record
// flagged at +0x2C. Returns undefined. Callback name address-derived.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

class AptCIH;
class EAStringC
{
	void *data;
public:
	EAStringC();
	~EAStringC();
};
class AptValue
{
public:
	AptCIH *c_cih(bool bUndefinedOK);
	int toInteger() const;
	void toString(EAStringC &) const;
};
class BfmeAptValue006DCD20
{
public:
	int isCharacterInst() const;
	bool isCIH(bool bUndefinedOK) const;
};
class Rva006CFCD0
{
public:
	bool isSpriteInstBase() const;
};
class Rva006E3C80 {public:int rva006E3C80();};
class AptBasePtrStack {public:AptValue *At(int);};
struct AptActionInterpreter {AptBasePtrStack stack;};
extern AptActionInterpreter g_aptDateInterpreter;
extern AptValue *gpUndefinedValue;
class Rva006DB160
{
public:
	void *allocBlock(int);
};
class Rva006DB270;
extern Rva006DB270 *g_pChainBlockAllocator;
class BfmeSubmitter1283
{
public:
	void *bfmeSubmit1283(AptCIH *a1, int a2, int a3, int a4, int a5, int a6, int a7, float *a8, int a9, int a10, int a11, int a12);
};

struct Rva006EDFF0Resource { char m_pad[0x10]; int *m_word; };
struct Rva006EDFF0Movie { char m_pad[8]; Rva006EDFF0Resource m_resource; };
struct Rva006EDFF0File { char m_pad[4]; Rva006EDFF0Movie *m_movie; };
struct Rva006EDFF0Inst { char m_pad[0xC]; Rva006EDFF0File *m_file; char m_pad10[0x24 - 0x10]; BfmeSubmitter1283 m_displayList; };
struct Rva006EDFF0CIH
{
	char m_pad[0x4C];
	Rva006EDFF0Inst *m_inst;
	Rva006EDFF0Inst *characterInst()
	{
		// The ledger spells isCharacterInst with an int return; retail tests al.
		if (!(unsigned char)((const BfmeAptValue006DCD20 *)this)->isCharacterInst()) {
			g_bfmeAptAssertAtE17734("isCharacterInst()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0xA5);
			if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
		}
		return m_inst;
	}
	Rva006EDFF0Inst *spriteInst()
	{
		if (!((const Rva006CFCD0 *)this)->isSpriteInstBase()) {
			g_bfmeAptAssertAtE17734("isSpriteInstBase()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0x7D);
			if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
		}
		return m_inst;
	}
};
struct Rva006EDFF0Character
{
	int m_type;
	int m_resourceWord;
	int m_08, m_0C, m_10;
	char m_pad[0x40 - 0x14];
};

AptValue *__cdecl Rva006EDFF0CreateEmptyMovieClip(AptValue *self, int count)
{
	if (count != 2)
		return gpUndefinedValue;
	AptValue *nameValue = g_aptDateInterpreter.stack.At(0);
	int depth = g_aptDateInterpreter.stack.At(1)->toInteger();
	Rva006EDFF0Character *pCharacter = (Rva006EDFF0Character *)((Rva006DB160 *)g_pChainBlockAllocator)->allocBlock(0x40);
	if (!pCharacter) {
		g_bfmeAptAssertAtE17734("pCharacter", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptCharacter.cpp", 0x5BD);
		if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
	}
	pCharacter->m_type = 5;
	pCharacter->m_08 = 0;
	pCharacter->m_0C = 0;
	pCharacter->m_10 = 0;
	Rva006EDFF0Resource *resource = &((Rva006EDFF0CIH *)self->c_cih(false))->characterInst()->m_file->m_movie->m_resource;
	pCharacter->m_resourceWord = *resource->m_word;
	EAStringC name;
	nameValue->toString(name);
	Rva006EDFF0CIH *parent = (Rva006EDFF0CIH *)self->c_cih(false);
	void *created = parent->spriteInst()->m_displayList.bfmeSubmit1283(0, depth + 0x4000, (int)pCharacter, (int)&name, (int)parent, 1, -1, 0, 0, 0, 0, 0);
	if (((BfmeAptValue006DCD20 *)created)->isCIH(false))
		((int *)((Rva006E3C80 *)created)->rva006E3C80())[11] = 1;
	return gpUndefinedValue;
}
