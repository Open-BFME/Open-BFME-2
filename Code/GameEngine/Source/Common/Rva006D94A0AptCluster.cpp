// cl: /MD
// Apt array helpers from the retail ABI at 0x006D94A0..0x006DA557. Layout
// (m_data +0x20, mnCapacity +0x24, mnLength +0x28) and the array-value role
// follow the rowed helpers in AptValueArrayAt.cpp and Rva006D94A0Cluster.cpp;
// the assert string and file spelling are read from each body's own operands.

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;

extern "C" void *__cdecl memmove(void *, const void *, unsigned int);

class BfmeAptValue006DCD20;
class EAStringC;

class AptBasePtrStack
{
public:
	BfmeAptValue006DCD20 *At(int nPos);
	void Push(BfmeAptValue006DCD20 *pValue);
	void rva006FE920();

	int m_nElements;
	int m_nCapacity;
	BfmeAptValue006DCD20 **m_aElements;
};

// The interpreter value stack is the first member of the ledger global
// g_aptDateInterpreter at VA 0x00E182E0 (AptDate.cpp). The matched bodies
// use it only through AptBasePtrStack, so they read it through that view.
struct AptActionInterpreter;
extern AptActionInterpreter g_aptDateInterpreter;
#define aptValueStack (*(AptBasePtrStack *)&g_aptDateInterpreter)

class AptValue;
class AptInteger
{
public:
	static AptValue *Create(int value);
};

// The growth helper 0x006D9500 is rowed as Rva006D9500::rva006D9500.
class Rva006D9500
{
public:
	void rva006D9500(int nCapacity);
};

// Value-object GC views shared with AptNativeHashMark.cpp: the shr-and-field
// word at +4 and the 14-slot AptValue vtable whose slot 13 (0x34) is the mark
// dispatch. Only the field word and the slot offset are used here.
class Rva006DBB40ShrAndField
{
public:
	bool get() const;
};

class AptValue
{
public:
	virtual void AddRef();
	virtual void Release();
	virtual void unused2();
	virtual void unused3();
	virtual void unused4();
	virtual void unused5();
	virtual void unused6();
	virtual void unused7();
	virtual void unused8();
	virtual void unused9();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	void setGCMark(bool value);
};

// The Rva006D6360 base forwarder 0x006DCC00 (slot 0x34 native-hash mark);
// retail calls it through its one-jump vtable thunk 0x0070DFD0, rowed as
// Rva0070DFD0::rva0070DFD0.
class AptObject
{
public:
	virtual void RegisterReferences() const;
};

class BfmeAptValue006DCD20
{
public:
	virtual void slot0();
	virtual void slot1();

	int isArray() const;
	BfmeAptValue006DCD20 *rva006DCFA0();
	BfmeAptValue006DCD20 *rva006DCEE0();
	BfmeAptValue006DCD20 *rva006D8A50(int nIndex);
	void rva006D9500(int nCapacity);
	void SetAt(int nIndex, BfmeAptValue006DCD20 *pNewValue);
	void rva006D95E0(int nIndex, BfmeAptValue006DCD20 *pValue);
	void rva006DD6C0(EAStringC *pBuffer);
	void rva006D94A0();
	int toInteger() const;
	int isObject() const;
	BfmeAptValue006DCD20 *rva006DD0E0();

	unsigned int m_flags;
	char m_pad[0x18];
	BfmeAptValue006DCD20 **m_data;
	int mnCapacity;
	int mnLength;
};

class AptValue; extern AptValue *gpUndefinedValue;

class EAStringC;

// EAStringC global used as the scratch key buffer at VA 0x00E18060.
class EAStringC
{
public:
	void rva006D3470();
	const char *rva00620090() const;
};
extern void *g_eaStringAtE18060Storage;

// The qsort comparators at VA 0x00AD9D70 / 0x00AD9E40 / 0x00AD9F70; only their
// addresses reach these bodies, and every push is a DIR32 site masked at verify.
extern "C" int __cdecl rva006D9D70Comparator(const void *, const void *);
extern "C" int __cdecl rva006D9E40Comparator(const void *, const void *);
extern "C" int __cdecl rva006DA0C0Comparator(const void *, const void *);

// msvcr71 qsort reached through the import thunk at 0x00629B4A.
extern "C" void __cdecl qsort(void *, unsigned int, unsigned int, int (__cdecl *)(const void *, const void *));

// Scratch array handles published by the non-default sort path (VA 0x00E18044
// and 0x00E18048).
// Only this unit's sort path and its comparators touch them; zero at load.
BfmeAptValue006DCD20 *g_rva006D9F00Handle;
BfmeAptValue006DCD20 **g_rva006D9F00Data;

// ?rva006D9CE0@@YAPAVBfmeAptValue006DCD20@@PAV1@H@Z @0x006D9CE0 (143 bytes).
// Prepends `count` interpreter-stack values to the array: the backing store is
// moved right by count, the slots are nulled, and each is filled through the
// checked store 0x006D95E0. Returns the new length as an AptInteger, or the
// shared undefined value when the receiver is not an array.
// Evidence: own immediates and callees isArray 0x006DC3A0, cast 0x006DCFA0,
// resize 0x006D9500, set 0x006D8AD0, store 0x006D95E0, At 0x006FE580 and
// AptInteger::Create 0x006D8520.
BfmeAptValue006DCD20 *rva006D9CE0(BfmeAptValue006DCD20 *pValue, int count)
{
	if (static_cast<unsigned char>(pValue->isArray()))
	{
		BfmeAptValue006DCD20 *array = pValue->rva006DCFA0();
		((Rva006D9500 *)array)->rva006D9500(array->mnLength + count);

		if (count != 0)
		{
			memmove(array->m_data + count, array->m_data, array->mnLength * 4);
			array->mnLength += count;
			for (int i = 0; i < count; ++i)
			{
				array->m_data[i] = 0;
				BfmeAptValue006DCD20 *value = aptValueStack.At(i);
				array->rva006D95E0(i, value);
			}
		}

		return (BfmeAptValue006DCD20 *)AptInteger::Create(array->mnLength);
	}

	return (*(BfmeAptValue006DCD20 * *)&gpUndefinedValue);
}

// _rva006D9E40Comparator @0x006D9E40 (181 bytes). Ghidra-unlisted qsort
// comparator for the script-function sort path of rva006D9F00 below: with a
// published handle it runs the script function through the interpreter
// (setup named "AptArraySortScriptFunction", action 0x1000000, retail
// literals) with the two elements pushed right then left, takes the integer
// result from stack slot 0, pops it and restores the interpreter. A null
// handle compares equal. The interpreter object is the stack's own address;
// callees are the rowed PrepareForExecution, Push, callFunction, toInteger,
// pop and CleanupAfterExecution.
struct AptActionSetup
{
	BfmeAptValue006DCD20 *context, *value;
	const char *name;
	int action;
};
struct AptActionInterpreter
{
	void *PrepareForExecution(AptActionSetup *);
	void CleanupAfterExecution(void *, AptActionSetup *);
	void callFunction(AptValue *, AptValue *, int);
};

extern "C" int __cdecl rva006D9E40Comparator(const void *a, const void *b)
{
	if (!g_rva006D9F00Handle)
		return 0;
	BfmeAptValue006DCD20 *left = *(BfmeAptValue006DCD20 **)a;
	BfmeAptValue006DCD20 *right = *(BfmeAptValue006DCD20 **)b;
	AptActionInterpreter *interpreter = &g_aptDateInterpreter;
	AptActionSetup setup;
	setup.context = (BfmeAptValue006DCD20 *)g_rva006D9F00Data;
	setup.value = g_rva006D9F00Handle;
	setup.name = "AptArraySortScriptFunction";
	setup.action = 0x1000000;
	void *saved = interpreter->PrepareForExecution(&setup);
	aptValueStack.Push(right);
	aptValueStack.Push(left);
	interpreter->callFunction((AptValue *)g_rva006D9F00Data, (AptValue *)g_rva006D9F00Handle, 2);
	int result = aptValueStack.At(0)->toInteger();
	aptValueStack.rva006FE920();
	interpreter->CleanupAfterExecution(saved, &setup);
	return result;
}

// _rva006DA0C0Comparator @0x006D9F70 (335 bytes). Ghidra-unlisted sortOn
// comparator the rowed rva006DA0C0 passes to qsort: compares the field named
// by the scratch key at E18060, looked up in two objects' native hashes
// (rowed Lookup; 0 when either is missing) or, for two arrays, read at the
// key's atoi index (undefined when out of range or empty), through the
// rowed string comparator above. Other pairs hit the AptArray.cpp line
// 0x328 NOT_REACHED assert (retail texts) and compare equal.
class AptNativeHash
{
public:
	AptValue *Lookup(const EAStringC *const key) const;
};
extern "C" int __cdecl atoi(const char *);

static __forceinline BfmeAptValue006DCD20 *rva006DA0C0Element(BfmeAptValue006DCD20 *value, int i)
{
	BfmeAptValue006DCD20 *array = value->rva006DCFA0();
	if (i >= 0 && i < array->mnLength)
	{
		BfmeAptValue006DCD20 *element = array->rva006D8A50(i);
		if (element)
			return element;
	}
	return (*(BfmeAptValue006DCD20 * *)&gpUndefinedValue);
}

extern "C" int __cdecl rva006DA0C0Comparator(const void *a, const void *b)
{
	BfmeAptValue006DCD20 *left = *(BfmeAptValue006DCD20 **)a;
	BfmeAptValue006DCD20 *right = *(BfmeAptValue006DCD20 **)b;
	EAStringC *key = reinterpret_cast<EAStringC *>(&g_eaStringAtE18060Storage);

	if (static_cast<unsigned char>(left->isObject()) && static_cast<unsigned char>(right->isObject()))
	{
		BfmeAptValue006DCD20 *leftObject = left->rva006DD0E0();
		BfmeAptValue006DCD20 *rightObject = right->rva006DD0E0();
		BfmeAptValue006DCD20 *leftField = (BfmeAptValue006DCD20 *)((const AptNativeHash *)((char *)leftObject + 8))->Lookup(key);
		if (leftField)
		{
			BfmeAptValue006DCD20 *rightField = (BfmeAptValue006DCD20 *)((const AptNativeHash *)((char *)rightObject + 8))->Lookup(key);
			if (rightField)
				return rva006D9D70Comparator(&leftField, &rightField);
		}
		return 0;
	}
	if (static_cast<unsigned char>(left->isArray()) && static_cast<unsigned char>(right->isArray()))
	{
		BfmeAptValue006DCD20 *leftField = rva006DA0C0Element(left, atoi(key->rva00620090()));
		BfmeAptValue006DCD20 *rightField = rva006DA0C0Element(right, atoi(key->rva00620090()));
		return rva006D9D70Comparator(&leftField, &rightField);
	}
	g_bfmeAptAssertAtE17734("NOT_REACHED", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptArray.cpp", 0x328);
	if (g_bfmeAptBreakOnAssertAtDDC01C)
		__asm int 3
	return 0;
}

// ?rva006D9F00@@YAPAVBfmeAptValue006DCD20@@PAV1@H@Z @0x006D9F00 (103 bytes).
// Array sort native: sorts the element pointer vector in place with qsort.
// mode 0 uses the comparator at 0x00AD9D70; any other mode first reads stack
// slot 0, publishes it and its element pointer through the two handle globals
// and uses the comparator at 0x00AD9E40. Non-arrays and the sort both return
// the shared undefined value.
// Evidence: own immediates; callees isArray 0x006DC3A0, cast 0x006DCFA0,
// checked cast 0x006DCEE0, At 0x006FE580 and qsort 0x00629B4A.
BfmeAptValue006DCD20 *rva006D9F00(BfmeAptValue006DCD20 *pValue, int mode)
{
	if (static_cast<unsigned char>(pValue->isArray()))
	{
		BfmeAptValue006DCD20 *array = pValue->rva006DCFA0();

		if (mode == 0)
		{
			qsort(array->m_data, array->mnLength, 4, rva006D9D70Comparator);
		}
		else
		{
			BfmeAptValue006DCD20 *value = aptValueStack.At(0);
			g_rva006D9F00Handle = value;
			g_rva006D9F00Data = value->rva006DCEE0()->m_data;
			qsort(array->m_data, array->mnLength, 4, rva006D9E40Comparator);
		}
	}

	return (*(BfmeAptValue006DCD20 * *)&gpUndefinedValue);
}

// ?rva006DA0C0@@YAPAVBfmeAptValue006DCD20@@PAV1@H@Z @0x006DA0C0 (97 bytes).
// Array sort native with a positive-count guard: builds a scratch EAStringC
// key from stack slot 0 through the pinned 0x006DD6C0, sorts the element
// pointer vector in place with qsort and the comparator at 0x00AD9F70, then
// releases the scratch key through EAStringC::rva006D3470. Non-arrays and
// non-positive counts return the shared undefined value.
// Evidence: own immediates; callees isArray 0x006DC3A0, cast 0x006DCFA0,
// At 0x006FE580, 0x006DD6C0 (unknown callee, 1430B), qsort 0x00629B4A and
// EAStringC::rva006D3470 0x006D3470.
BfmeAptValue006DCD20 *rva006DA0C0(BfmeAptValue006DCD20 *pValue, int mode)
{
	if (static_cast<unsigned char>(pValue->isArray()))
	{
		BfmeAptValue006DCD20 *array = pValue->rva006DCFA0();

		if (mode > 0)
		{
			aptValueStack.At(0)->rva006DD6C0(&(*reinterpret_cast<EAStringC *>(&g_eaStringAtE18060Storage)));
			qsort(array->m_data, array->mnLength, 4, rva006DA0C0Comparator);
			(*reinterpret_cast<EAStringC *>(&g_eaStringAtE18060Storage)).rva006D3470();
		}
	}

	return (*(BfmeAptValue006DCD20 * *)&gpUndefinedValue);
}

// ?rva006D94A0@BfmeAptValue006DCD20@@QAEXXZ @0x006D94A0 (92 bytes).
// Array GC-mark traversal (AptValue vtable slot 13 / 0x34): forwards to the
// Rva006D6360 slot-0x34 native-hash mark, then walks every element, and for
// each unmarked value sets its GC mark and recurses through the same slot.
// Every access re-reads the element through At 0x006D8A50, matching retail's
// four separate calls per iteration.
// Evidence: vtable 0x008EA778 slot 0x34 = this body; forwarder thunk 0x0070DFD0
// -> 0x006DCC00; callees At 0x006D8A50, get 0x006DBB40, setGCMark 0x006DBC50.
void BfmeAptValue006DCD20::rva006D94A0()
{
	((AptObject *)this)->AptObject::RegisterReferences();

	for (int i = 0; i < mnLength; ++i)
	{
		if (rva006D8A50(i) && !((const Rva006DBB40ShrAndField *)rva006D8A50(i))->get())
		{
			((AptValue *)rva006D8A50(i))->setGCMark(true);
			((AptValue *)rva006D8A50(i))->unused13();
		}
	}
}
