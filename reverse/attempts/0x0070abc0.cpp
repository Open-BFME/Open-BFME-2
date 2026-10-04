// ?rva0070ABC0@AptNativeHash@@QAEXXZ
// partial score=0.99 date=2026-10-04
// ?rva0070ABC0@AptNativeHash@@QAEXXZ
// partial score=0.99 date=2026-10-04
// ?rva0070ABC0@AptNativeHash@@QAEXXZ
// partial score=0.99 date=2026-10-04
// ?rva0070ABC0@AptNativeHash@@QAEXXZ
// Seat-4 re-bank of the 0x0070ABC0 partial. The swap tail was rewritten from the
// bank's two-operand-at-a-time spelling to four captured operands, ordered so that
// both newTable fields are read before either is stored:
//   od = mpData; nd = newTable.mpData; ns = newTable.mnTotalSize;
//   mpData = nd; os = mnTotalSize; newTable.mpData = od;
//   mnTotalSize = ns; newTable.mnTotalSize = os;
// That is the only source form this compiler emits retail's tail schedule under.
// The bank asserted no ordering of the four assignments reaches it; a search over
// all 8! orderings of the eight tail statements shows the opposite -- several
// orderings DO reproduce it -- but only of a tail that captures all four operands.
// Every ordering of the bank's three capture shapes (with mpData[i].value kept in
// the loop) stays at 6 differing bytes, so the captures are what matters, not their
// order. This takes the residual from 6 differing bytes to ONE (offset 103).
//
// The remaining byte is a pure SIB base/index role swap in the migrated-value
// load: retail reads mov ebx,[ebx+ecx*1+0x4] -- base=EBX, the loop's i*8 byte
// offset -- where this build emits mov ebx,[ecx+ebx*1+0x4], base=ECX. Same base and
// index registers, same displacement, same loaded value; only the SIB byte's
// base/index fields differ. It is structurally forced here, swept and rejected:
//   - reading the value through the entry pointer (e->value, &e->value, char*-plus-4
//     offsets, const-qualified, and a two-local spelling) either collapses the body
//     to 183B with the first difference moving to +0x18 (the i*8 offset is then only
//     live through ESI, never in EBX) or is byte-identical;
//   - re-deriving the entry address in the loop (a second Entry*, a char* cast,
//     an index-free loop head) is byte-identical at 1 differing byte;
//   - every /G* flag (G3 G4 G5 G6 Gd Gr Gs Gs- Gt Gw Gw- Gy Gy- Gi) is identical,
//     as are /Ot /Ob2 /Ox /Gs /Oi-; /G7 is worse (7 differing from +0x1E), /Oy-
//     regresses to a 190B ebp frame, and /O1 to 167B.
// Cl 7.1 orders the SIB base before the index for both roles, so this single byte is
// not reachable from source.
// cl: /O2 /MD
// Reconstructed from BFME2 and APT 0.19.03 Xbox final donor evidence, matching
// the layout and flags of Code/Libraries/Source/Apt/AptNativeHashBFME2.cpp.
// Retail body 0x0070ABC0, 194 bytes: AptNativeHash::Resize(). It builds a
// second hash twice the current table size, migrates every live entry whose key
// is neither null-backed nor empty, then swaps the two tables and destroys the
// old one.
//
// Evidence (retail bytes):
//   mov eax,[edi]; shl eax,1          new size = mnTotalSize * 2
//   lea ecx,[esp+0xc]; call 0x0070A740 AptNativeHash::AptNativeHash(int) on the
//                                    stack temporary at esp+0xc
//   lea ecx,[esp+8];  call 0x0070AB30 rva0070AB30 (alloc + memset the new table)
//   cmp [edi],ebp; jle done           loop over the OLD mnTotalSize entries
//   mov esi,[edi+4]; lea ebx,[ebp*8]; add esi,ebx    old[i] (8-byte entries)
//   call 0x006CD4A0 AsciiString::hasData ; if false, skip
//   call 0x006D2F30 EAStringC::IsEmpty ; if true, skip
//   mov ecx,[edi+4]; mov ebx,[ebx+ecx+4]   old[i].value
//   push ebx; push esi; lea ecx,[esp+0x18]; call 0x0070AC90   insert(new, key, value)
//   swap [esp+0xc]/[esp+8] with [edi+4]/[edi], i.e. mnTotalSize <-> new.mnTotalSize
//   and mpData <-> new.mpData
//   call 0x0070A8B0 DestroyGCPointers on the old table
//   call 0x0070A840 the old table's destructor
//
// The insert helper 0x0070AC90 is not recovered here; it is declared under an
// address-derived name and resolves through its symbols.csv pin. Its body opens
// with the same "block must be non-null" assert this file already spells for
// rva0070A680/rva0070A610, so the identity is carried from the donor, not
// assumed from the address.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
extern "C" void *__cdecl memset(void *, int, unsigned int);
#pragma intrinsic(memset)
void __debugbreak();
#pragma intrinsic(__debugbreak)
// class-gate: allow AsciiString the shared bfme2_ascii shim spells the accessor
// isEmpty(), while the Apt donor spells it hasData(); both spellings have to
// coexist across the AptNativeHash bodies and only hasData() is called here.
class EAStringC {
public:
	bool IsEmpty() const;
};
class AsciiString {
	void *m_data;
public:
	bool hasData() const;
};
class AptValue {
public:
	virtual void AddRef();
	virtual void Release();
};
class AptNativeHash {
	struct Entry { AsciiString key; AptValue *value; };
	int mnTotalSize;
	Entry *mpData;
	AptValue *mp__proto__;
	AptValue *mpPrototype;
	unsigned int nEventHandlers;
public:
	AptNativeHash(int size);
	~AptNativeHash();
	void rva0070AB30();
	void DestroyGCPointers();
	// The resize helper 0x0070AC90: insert one migrated entry. Declared under
	// an address-derived name; its body is pinned, not recovered here.
	void rva0070AC90(const Entry *key, AptValue *value);
	// Resize: double the table and migrate every live entry.
	void rva0070ABC0();
};


void AptNativeHash::rva0070ABC0()
{
	AptNativeHash newTable(mnTotalSize * 2);
	newTable.rva0070AB30();
	for (int i = 0; i < mnTotalSize; ++i)
	{
		Entry *e = mpData + i;
		if (e->key.hasData())
		{
			if (!((const EAStringC *)&e->key)->IsEmpty())
			{
				AptValue *v = mpData[i].value;
				newTable.rva0070AC90(e, v);
			}
		}
	}
	Entry *od = mpData;
	Entry *nd = newTable.mpData;
	int ns = newTable.mnTotalSize;
	mpData = nd;
	int os = mnTotalSize;
	newTable.mpData = od;
	mnTotalSize = ns;
	newTable.mnTotalSize = os;
	newTable.DestroyGCPointers();
}

// The retail destructor at the tail of the resize body is 0x0070A840, already
// named ??1Rva0070A840@@QAE@XZ in reverse/symbols.csv. The local
// AptNativeHash::~AptNativeHash above is emission scaffolding for that call, so
// bind the two spellings the same way AptNativeHashBFME2.cpp binds
// ?handle@Gen0089C880@@QAEXXZ to ?DestroyGCPointers@AptNativeHash@@QAEXXZ.
#pragma comment(linker, "/alternatename:??1AptNativeHash@@QAE@XZ=??1Rva0070A840@@QAE@XZ")