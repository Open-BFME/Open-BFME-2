// cl: /O2 /MD
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

	int m_nElements;
	int m_nCapacity;
	BfmeAptValue006DCD20 **m_aElements;
};

// The interpreter value stack at VA 0x00E182E0. The matched bodies use it only
// through AptBasePtrStack::At, so the object name is TU-local.
extern AptBasePtrStack g_aptValueStackAtE182E0;

class AptInteger
{
public:
	static BfmeAptValue006DCD20 *Create(int value);
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

// The Rva006D6360 base forwarder 0x006DCC00 (slot 0x34 native-hash mark).
class Rva006D6360
{
public:
	void rva006DCC00();
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
	void rva006D8AD0(int nIndex, BfmeAptValue006DCD20 *pNewValue);
	void rva006D95E0(int nIndex, BfmeAptValue006DCD20 *pValue);
	void rva006DD6C0(EAStringC *pBuffer);
	void rva006D94A0();

	unsigned int m_flags;
	char m_pad[0x18];
	BfmeAptValue006DCD20 **m_data;
	int mnCapacity;
	int mnLength;
};

extern BfmeAptValue006DCD20 *g_aptUndefinedAtE18078;

class EAStringC;

// EAStringC global used as the scratch key buffer at VA 0x00E18060.
class EAStringC
{
public:
	void rva006D3470();
};
extern EAStringC g_eaStringAtE18060;

// The qsort comparators at VA 0x00AD9D70 / 0x00AD9E40 / 0x00AD9F70; only their
// addresses reach these bodies, and every push is a DIR32 site masked at verify.
extern "C" int __cdecl rva006D9D70Comparator(const void *, const void *);
extern "C" int __cdecl rva006D9E40Comparator(const void *, const void *);
extern "C" int __cdecl rva006DA0C0Comparator(const void *, const void *);

// msvcr71 qsort reached through the import thunk at 0x00629B4A.
extern "C" void __cdecl qsort(void *, unsigned int, unsigned int, int (__cdecl *)(const void *, const void *));

// Scratch array handles published by the non-default sort path (VA 0x00E18044
// and 0x00E18048).
extern BfmeAptValue006DCD20 *g_rva006D9F00Handle;
extern BfmeAptValue006DCD20 **g_rva006D9F00Data;

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
		array->rva006D9500(array->mnLength + count);

		if (count != 0)
		{
			memmove(array->m_data + count, array->m_data, array->mnLength * 4);
			array->mnLength += count;
			for (int i = 0; i < count; ++i)
			{
				array->m_data[i] = 0;
				BfmeAptValue006DCD20 *value = g_aptValueStackAtE182E0.At(i);
				array->rva006D95E0(i, value);
			}
		}

		return AptInteger::Create(array->mnLength);
	}

	return g_aptUndefinedAtE18078;
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
			BfmeAptValue006DCD20 *value = g_aptValueStackAtE182E0.At(0);
			g_rva006D9F00Handle = value;
			g_rva006D9F00Data = value->rva006DCEE0()->m_data;
			qsort(array->m_data, array->mnLength, 4, rva006D9E40Comparator);
		}
	}

	return g_aptUndefinedAtE18078;
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
			g_aptValueStackAtE182E0.At(0)->rva006DD6C0(&g_eaStringAtE18060);
			qsort(array->m_data, array->mnLength, 4, rva006DA0C0Comparator);
			g_eaStringAtE18060.rva006D3470();
		}
	}

	return g_aptUndefinedAtE18078;
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
	((Rva006D6360 *)this)->rva006DCC00();

	for (int i = 0; i < mnLength; ++i)
	{
		if (rva006D8A50(i) && !((const Rva006DBB40ShrAndField *)rva006D8A50(i))->get())
		{
			((AptValue *)rva006D8A50(i))->setGCMark(true);
			((AptValue *)rva006D8A50(i))->unused13();
		}
	}
}

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?g_aptValueStackAtE182E0@@3VAptBasePtrStack@@A=?g_aptDateInterpreter@@3UAptActionInterpreter@@A")
