// cl: /DNDEBUG /MD /EHsc
// Retail RE: ?rva0033B677@@YAXPAVINI@@PAX1PBX@Z @0x0033B677 (197B).
//
// BFME2-new Flammability FuelFactor INI callback. Target facts from retail
// bytes + tables (all independently read this round):
// - Sub-table RVA 0x9BF8D8 entry1 (at 0x9BF8E8 runtime): token FuelFactor
//   (VA 0x00C10544 -> "FuelFactor"), parse 0x33B677, user instance,
//   off 0. Proven by 0x33BC6A body: mov [0xDBF8E8],0xC10544 /
//   mov [0xDBF8EC],0x73B677 / mov [0xDBF8F0],edx(instance) / mov [0xDBF8F4],0.
//   File at 0x9BF8D8 shows only entry0 (Fuel/dup) preset, rest zero;
//   runtime fills entries 1-4 + terminator.
// - Main table RVA 0x9BECD8 entry178 at 0x9BF7F8: token Flammability
//   (RVA 0x80ECF4), parse 0x33BC6A, user 0, off 0x314. Receiver is
//   ThingTemplate+0x314 (Flammability object); store here is that +0.
// - ABI static void __cdecl (INI*,void*,void*,const void*), plain ret (C3).
//   [ebp+8]=INI*, [ebp+0xC]=instance(unused), [ebp+0x10]=store(int*),
//   [ebp+0x14]=userData(ThingTemplate* captured as instance in 0x33BC6A).
// - Parent +0x2E4/+0x2E8: ThingTemplate+0x2E4 is behavior ModuleInfo
//   (m_begin at +0x2E4, m_end at +0x2E8), proven by rowed
//   ModuleInfoGetNthData.cpp (pad 0x2E4) + ThingTemplateSetCopiedFromDefault
//   (+0x2E4/+0x2F0/+0x2FC/+0x308) + ModuleInfoAddModuleInfo (0x2E4).
//   Count = (m_end-m_begin)/20 via signed idiv (push 0x14/cdq/pop ecx/idiv).
// - Matched 0x33ACE8 call: ?getNthData@ModuleInfo@@QBEPBVModuleData@@H@Z
//   43B in ModuleInfoGetNthData.cpp. Two calls with ecx=ModuleInfo*,
//   push index; REL32 e845f6ffff / e8fef5ffff decode to VA 0x73ACE8.
// - Virtual [edx+0x1C] is Body check: StructureBody vtable at VA 0xBF4028
//   slot7 (+0x1C) is 0x50B5C6 (mov al,1;ret) vs false stub 0x47A699
//   (xor al,al;ret) in slots 4-6,8-9. Loop searches behavior modules for
//   first Body; not found -> INIException(3,"Can't use FuelFactor without
//   defining Body first") via rowed 0x2F681 + _CxxThrowException 0x629094
//   with ThrowInfo 0xCFE2FC.
// - Data: BodyModuleData+8 float scale; parsed FuelFactor float via rowed
//   getNextToken 0x2DF97 (75B) + scanReal 0x2EDA5 (107B), fmul [esi+8],
//   __ftol2 0x629228 (117B, masm_dumps/ftol2.asm) to int, bound 0xFFFF,
//   else INIException(3,"value out of range, expected 0..%d instead of %d",
//   max,value) + throw; store int to [ebp+0x10].
// Donor-carried only: ZH/BFME1 FieldParse {token,parse,userData,offset} +
// INI callback shape + initFromINI delegate (no Flammability/FuelFactor in
// BFME1 6583b3c1 or ZH; searched, absent). All tokens/maxes/offsets/guard,
// Body-search loop, float scale, and bound are BFME2 target facts.
// No shared-header edits; TU-scoped views only.

class INI
{
public:
	const char *getNextToken(const char *seps);
	float scanReal(const char *token);
};

struct _s__ThrowInfo;
extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);
extern "C" void __stdcall rva002f681_fill(void *e, int argCount, const char *format, ...);
// Retail ThrowInfo VA 0x00CFE2FC is the compiler COMDAT __TI1?AVINIException@@
// (16B: attributes 0, unwind ??1INIException@@QAE@XZ 0x0042BD30, forward 0,
// one catchable type). Genuine provider is the C++ throw in
// Code/GameEngine/Source/Common/System/INI_parseFXList.cpp (60 objects emit
// digest ddd8f3eb8737); this TU is a consumer only and defines no ThrowInfo.
// extern "C" adds one leading underscore, so single-underscore text emits the
// actual COMDAT __TI1?AVINIException@@ (double underscore). Double-underscore
// text would emit ___TI1 (triple), which nothing defines.
extern "C" const struct _s__ThrowInfo __identifier("_TI1?AVINIException@@");

// Canonical 8-byte INIException layout (char *mFailureMessage at +0, int at +4;
// dtor ??1INIException@@QAE@XZ 0x0042BD30, copy ??0INIException@@QAE@ABV0@@Z
// 0x004588C5, filler ??0INIException@@QAA@HPBDZZ 0x0002F681). The throw object
// below is this class's storage filled by the filler; destruction at unwind is
// via the ThrowInfo's pmfnUnwind, preserved by keeping size 8.
class INIException
{
public:
	INIException(int argumentCount, const char *format, ...);
	INIException(const INIException &other);
	~INIException();
	char *mFailureMessage;
	int m_argumentCount;
};

class ModuleData
{
public:
	virtual ~ModuleData();
	virtual void vf01();
	virtual void vf02();
	virtual void vf03();
	virtual bool vf04() const;
	virtual bool vf05() const;
	virtual bool vf06() const;
	virtual bool isBodyLike() const;
	int m_tag;
	float m_scale;
};

class ModuleInfo
{
public:
	const void *m_begin;
	const void *m_end;
	const void *m_storage;
	int getCount() const
	{
		return ((const char *)m_end - (const char *)m_begin) / 20;
	}
	__declspec(noinline) const ModuleData *getNthData(int i) const;
};

class ThingTemplate
{
	char m_pad[0x2E4];
public:
	ModuleInfo m_behaviorModuleInfo;
};

// ?rva0033B677@@YAXPAVINI@@PAX1PBX@Z
void __cdecl rva0033B677(INI *ini, void * /*instance*/, void *store, const void *userData)
{
	// Storage for INIException (8 bytes); filled by the filler, destroyed via
	// the ThrowInfo unwind. Sized from the canonical decl, not an invented struct.
	char exc[sizeof(INIException)];
	const ThingTemplate *parent = (const ThingTemplate *)userData;
	const ModuleInfo *info = &parent->m_behaviorModuleInfo;
	int idx = 0;
	if (info->getCount() > 0) {
		do {
			const ModuleData *d = info->getNthData(idx);
			if (d->isBodyLike())
				break;
			++idx;
		} while (idx < info->getCount());
	}
	if (idx == info->getCount()) {
		rva002f681_fill(&exc, 3, "Can't use FuelFactor without defining Body first");
		_CxxThrowException(&exc, &__identifier("_TI1?AVINIException@@")); __assume(0);
	}
	{
		const ModuleData *body = info->getNthData(idx);
		float f = ini->scanReal(ini->getNextToken(0));
		int v = (int)(f * body->m_scale);
		if ((unsigned)v > 0xFFFF) {
			rva002f681_fill(&exc, 3, "value out of range, expected 0..%d instead of %d", 0xFFFF, v);
			_CxxThrowException(&exc, &__identifier("_TI1?AVINIException@@")); __assume(0);
		}
		*(int *)store = v;
		return;
	}
}
