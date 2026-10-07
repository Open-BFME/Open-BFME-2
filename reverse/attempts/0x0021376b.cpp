// ?Rva0021376BParse@@YAXPAVINI@@@Z
// partial score=0.9 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// stlport
// ?Rva0021376BParse@@YAXPAVINI@@@Z retail 0x0021376B 257B.
// LivingWorldObject BlockParse via BlockParse node 0x00DB9A20. Throws via filler
// 0x0002F681 plus _CxxThrowException when TheLivingWorldManager is null then
// getNextToken plus NameKeyGenerator plus LivingWorldManager lookup 0x002122D4
// then clone-or-new Rva00210F3D via 0x00211142 plus FieldParse 0x00C378F0 plus
// validate 0x000B3FD0 plus map insert at manager+0x2B4. Row 0x001E35DF types as
// void but body uses eax result so declared as Overridable getFinalOverride per
// its pin. Callers none. Chain over 0x00211142.
#include <map>

struct FieldParse
{
	const char *token;
	void (__cdecl *parse)(void *ini, void *instance, void *store, const void *userData);
	const void *userData;
	int offset;
};

class INI
{
public:
	const char *getNextToken(const char *seps);
	void initFromINI(void *what, const FieldParse *parseTable);
	int m_00;
	int m_04;
	int m_type;
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class Rva00210F3D;

class LivingWorldManager
{
public:
	int rva002122D4(int rawKey);
	Rva00210F3D *clone(Rva00210F3D *src);
	char m_pad[0x2b4];
	_STL::map<int, int> m_map;
};
extern LivingWorldManager *TheLivingWorldManager;

class Overridable
{
public:
	const Overridable *getFinalOverride() const;
	void *m_vtable;
	Overridable *m_next;
};

class Rva00210F3D
{
public:
	virtual ~Rva00210F3D();
	const FieldParse *getFieldParse() const;
	Rva00210F3D *m_04;
	unsigned char m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
};

class Rva003FA776 : public Rva00210F3D
{
public:
	Rva003FA776();
};

void *__cdecl operator new(unsigned int size);

Rva00210F3D *__stdcall Rva00211142Clone(Rva00210F3D *src);
int Rva003FA6FFGet(void);

class INI;
void __cdecl Rva0021376BParse(INI *ini);

template <typename T> class StringBase
{
	friend void __cdecl Rva0021376BParse(INI *ini);
	void validate() const;
};

struct INIExceptionBuf
{
	char *mMsg;
	int mCode;
};

struct _s__ThrowInfo;
extern "C" void rva002f681_fill(void *e, int argCount, const char *format, ...);
extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);
extern "C" const struct _s__ThrowInfo __identifier("_TI1?AVINIException@@");

void __cdecl Rva0021376BParse(INI *ini)
{
	if (TheLivingWorldManager == 0) {
		INIExceptionBuf e;
		rva002f681_fill(&e, 3, "TheLivingWorldManager==NULL");
		_CxxThrowException(&e, &__identifier("_TI1?AVINIException@@"));
	}
	LivingWorldManager *mgr = TheLivingWorldManager;
	const char *token = ini->getNextToken(0);
	int key = TheNameKeyGenerator->nameToKey(token);
	Rva00210F3D *found = (Rva00210F3D *)mgr->rva002122D4(key);
	Rva00210F3D *obj = found;
	bool isCloned = false;
	if (found != 0) {
		if (ini->m_type == 2) {
			Rva00210F3D *src;
			Overridable *next = (Overridable *)found->m_04;
			if (next != 0)
				src = (Rva00210F3D *)next->getFinalOverride();
			else
				src = found;
			obj = mgr->clone(src);
			isCloned = true;
		} else {
			obj = found;
			isCloned = true;
		}
	} else {
		Rva003FA776 *fresh = (Rva003FA776 *)operator new(0x1c);
		if (fresh != 0)
			new (fresh) Rva003FA776;
		obj = fresh;
		if (ini->m_type == 2)
			fresh->m_08 = 1;
	}
	const FieldParse *table = obj->getFieldParse();
	ini->initFromINI(obj, table);
	((StringBase<unsigned short> *)obj)->validate();
	if (!isCloned) {
		int &slot = mgr->m_map.operator[](key);
		slot = (int)obj;
	}
}
