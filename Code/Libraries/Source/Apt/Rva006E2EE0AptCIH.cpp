// ?rva006E2EE0@AptCIH@@QAEXXZ
// Native 0x006E2EE0..0x006E31D5 757B AptCIH class-registration hook.
// Exact in the nn-lab chain (scope-wrap of the AptActionSetup block plus a
// barrier before it); ported from build/d1/lab_006e2e/chain_0x006e2ee0.cpp.
// cl: /O2 /G6 /arch:SSE /MD
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
// ?rva006E2EE0@AptCIH@@QAEXXZ, retail 0x006E2EE0..0x006E31D5 (757 bytes).
// AptCIH class-registration hook, WorldBuilder twin 0x017966F0 (an optimized
// build with the same calls and order). For a character instance (AptCIH.h
// 0xA5 assert) that is a sprite (type 0x0D) or movie clip (type 0x12) and
// whose sprite base (0x7D assert) has mode +0x2C zero: give its native hash
// a fresh pooled prototype object (0x006DE1A0, inlined SetPrototype at +0xC)
// and the global string 0x5E object's prototype as __proto__ (+8), then find
// the export of its movie whose character is ours; when the registered-class
// table at 0x00E180E4 holds a function under that export name, take that
// function's prototype as __proto__ (rowed Set__Proto__), refresh the clip
// (0x006E2D60, slot 6 with 1), run the function as a constructor on the clip
// through the interpreter's prepare/push/callFunction/pop/cleanup, and add
// the clip to the +0x28 set of 0x00E176D0 when 0x006E0AC0 holds and it is
// not already there. Method name stays address-derived.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

#define APT_CHECK(e, s, l) do { if (!(e)) { g_bfmeAptAssertAtE17734(s, "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", l); if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak(); } } while (0)

#include "EAStringC.h"

#include "AptValue.h"
#include "AptCIHClass.h"

#include "BfmeAptValue006DCD20.h"
#include "../../../GameEngine/Include/Common/Rva006DBB30SarDwordField.h"
class Rva006DBB60ShrNAndField { public: int get() const; };
class Rva006CFCD0 { public: bool isSpriteInstBase() const; };

struct AptNativeHash
{
public:
	void Set__Proto__(AptValue *const proto);
	unsigned char m_pad00[8];
	AptValue *m_proto;		// +0x08
	AptValue *m_prototype;		// +0x0C
	__forceinline void setPrototype(AptValue *const prototype)
	{
		if (prototype)
			prototype->AddRef();
		if (m_prototype)
			m_prototype->Release();
		m_prototype = prototype;
	}
	__forceinline void setProto(AptValue *const proto)
	{
		if (proto)
			proto->AddRef();
		if (m_proto)
			m_proto->Release();
		m_proto = proto;
	}
};

struct AptExport
{
	const char *name;
	int character;
};

struct AptCharacter;
struct AptMovie
{
	unsigned char m_pad00[0x10];
	AptCharacter **characters;	// +0x10
	unsigned char m_pad14[0x28 - 0x14];
	int exportCount;		// +0x28
	AptExport *exports;		// +0x2C
};

struct AptCharacter
{
	unsigned char m_pad00[4];
	AptCharacter *base;		// +0x04
	AptMovie movie;			// +0x08
};

struct AptCharacterSpriteInstBase
{
	unsigned char m_pad00[0x0C];
	AptCharacter *character;	// +0x0C
	AptNativeHash *nativeHash;	// +0x10
	unsigned char m_pad14[0x2C - 0x14];
	int mode;			// +0x2C
};

#include "Rva006D2A60.h"
extern Rva006D2A60 *g_pChainBlockAllocatorF4;

class Rva006DE1A0
{
public:
	Rva006DE1A0();
	static void *operator new(unsigned size) { return g_pChainBlockAllocatorF4->allocBlock(size); }
	// The unwind funclet frees through the shared 22-byte forwarder 0x006F12F0.
	static void operator delete(void *p, unsigned int n) { g_pChainBlockAllocatorF4->freeBlock(p, n); }
private:
	unsigned char m_data[0x20];
};

EAStringC *Rva0070B4F0GetString(int index);
class BfmeN1034Object
{
public:
	virtual void s0(); virtual void s1(); virtual void s2();
	virtual BfmeN1034Object *asObject();	// slot 0x0C
	unsigned char m_pad04[0x0C - 4];
	AptValue *m_prototype;			// +0x0C
};
class BfmeN1034;
#include "Rva0070A5C0.h"
extern AptValue *gpGlobalGlobalObject;
#include "../../../GameEngine/Include/Common/Rva0070B380.h"
extern AptNativeHash *g_bfmeAptHashAtE180E4;

class AptCIH;
#include "AptBasePtrStack.h"
template <class T> class AptValuePtrStack
{
public:
	void push(T *value);
	void pop();
	int count, capacity;
	T **elements;
};
#include "../../../GameEngine/Include/Common/AptActionSetup.h"
struct AptActionInterpreter
{
	AptBasePtrStack stack;
	AptValuePtrStack<AptValue> contexts;	// +0x0C
	void *PrepareForExecution(AptActionSetup *setup);
	void callFunction(AptValue *context, AptValue *function, int nArgs);
	void CleanupAfterExecution(void *saved, AptActionSetup *setup);
};
extern AptActionInterpreter g_aptDateInterpreter;

class Rva006E9A40List
{
public:
	unsigned short mnElements, mnMaxElements;
	AptCIH **maElements;
	void add(AptCIH *element);
};
struct Rva006E34D0Animations
{
	unsigned char m_pad00[0x28];
	Rva006E9A40List clips;		// +0x28
};
// The pool pointer at 0x00A176D0 is the ledger's Rva006E34D0 global; read it through this view.
class Rva006E34D0;
extern Rva006E34D0 *g_bfmeAptPtrAtE176D0;

class Rva006E0AC0 { public: int rva006E0AC0(); };

// The owned int-returning flag getter is tested as a bool (retail tests al).
static __forceinline bool isFunction(void *value)
{
	return (((Rva006DBB60ShrNAndField *)value)->*reinterpret_cast<bool (Rva006DBB60ShrNAndField::*)() const>(&Rva006DBB60ShrNAndField::get))();
}

// AptCIH.h inline accessors over the canonical +0x4C instance pointer.
static __forceinline AptCharacterSpriteInstBase *getCharacterInst(AptCIH *cih)
{
	// The owned int-returning predicate is tested as a bool (retail tests al).
	APT_CHECK((((BfmeAptValue006DCD20 *)cih)->*reinterpret_cast<bool (BfmeAptValue006DCD20::*)() const>(&BfmeAptValue006DCD20::isCharacterInst))(), "isCharacterInst()", 0xa5);
	return (AptCharacterSpriteInstBase *)cih->field4C;
}
static __forceinline AptCharacterSpriteInstBase *getSpriteInstBase(AptCIH *cih)
{
	APT_CHECK(((Rva006CFCD0 *)cih)->isSpriteInstBase(), "isSpriteInstBase()", 0x7d);
	return (AptCharacterSpriteInstBase *)cih->field4C;
}
static __forceinline bool isSprite(const AptCIH *cih)
{
	return ((const Rva006DBB30SarDwordField *)cih)->get() == 0xd && !((const BfmeAptValue006DCD20 *)cih)->isUndefined();
}
static __forceinline bool isMovieClip(const AptCIH *cih)
{
	return ((const Rva006DBB30SarDwordField *)cih)->get() == 0x12 && !((const BfmeAptValue006DCD20 *)cih)->isUndefined();
}

void AptCIH::rva006E2EE0()
{
	AptCharacterSpriteInstBase *inst = getCharacterInst(this);
	if (!isSprite(this) && !isMovieClip(this))
		return;
	if (getSpriteInstBase(this)->mode != 0)
		return;

	AptCharacter *character = inst->character;
	AptMovie *movie = &character->base->movie;
	inst->nativeHash->setPrototype((AptValue *)new Rva006DE1A0);
	BfmeN1034Object *object = ((BfmeN1034Object *)((Rva0070A5C0 *)gpGlobalGlobalObject)->rva0070A5C0((int)Rva0070B4F0GetString(0x5e)))->asObject();
	inst->nativeHash->setProto(object->m_prototype);

	if (movie->exportCount <= 0)
		return;
	for (int i = 0; i < movie->exportCount; i++)
	{
		if (character != movie->characters[movie->exports[i].character])
			continue;
		if (!g_bfmeAptHashAtE180E4)
			return;
		BfmeAptValue006DCD20 *function;
		{
			EAStringC name(movie->exports[i].name);
			function = (BfmeAptValue006DCD20 *)((Rva0070B380 *)g_bfmeAptHashAtE180E4)->lookup(name);
		}
		if (!function || !isFunction(function))
			return;
		BfmeN1034Object *prototype = (BfmeN1034Object *)((BfmeN1034Object *)function)->asObject()->m_prototype;
		if (prototype && isFunction(prototype))
			inst->nativeHash->Set__Proto__((AptValue *)prototype);
		AptValue *constructor = (AptValue *)function->rva006DCEE0();
		rva006E2D60();
		setHasClass(1);
		const char *name = movie->exports[i].name;
		_ReadWriteBarrier();
		{
		AptActionSetup setup;
		setup.context = this;
		setup.value = constructor;
		setup.name = name;
		setup.action = 0x2000000;
		void *saved = g_aptDateInterpreter.PrepareForExecution(&setup);
		g_aptDateInterpreter.contexts.push(this);
		g_aptDateInterpreter.callFunction(this, constructor, 0);
		g_aptDateInterpreter.contexts.pop();
		g_aptDateInterpreter.stack.rva006FE920();
		g_aptDateInterpreter.CleanupAfterExecution(saved, &setup);
		}
		if (((Rva006E0AC0 *)this)->rva006E0AC0())
		{
			Rva006E9A40List &clips = ((Rva006E34D0Animations *)g_bfmeAptPtrAtE176D0)->clips;
			for (int j = 0; j < clips.mnMaxElements; j++)
				if (clips.maElements[j] == this)
					return;
			clips.add(this);
		}
		return;
	}
}

