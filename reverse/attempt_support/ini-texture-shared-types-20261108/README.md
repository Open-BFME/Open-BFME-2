# Texture diagnostics shares the string and vector types

INIStatsRecordTextures.cpp includes canonical StringClassData.h and the
pinned BFME1 WWLib vector.h instead of redeclaring VectorClass and
DynamicVectorClass. Two private template copies leave the source. The donor
header is class/template evidence, not a claim that its external path is this
BFME2 translation unit's original source path.

The existing one-pointer StringClass conversion stays inline in this TU,
using the canonical class's member. Declaration-only specializations keep the
already-rowed allocating and virtual operations with their existing providers.
The explicit destructor specialization keeps the original qualified Clear
call and existing dllimport/forceinline declaration context. /DNDEBUG selects
the normal release header surface: the first trial without it introduced an
assert call in operator[]. No debug assertion or new pin is suppressed by a
custom shim or verifier exception.

All five code rows, including the 435-byte parent and its three cleanups,
pass normal verification; the parent EH graph is EXACT. The source remains
unfrozen. The private LinkGuard is clean. All 16 external COMDAT names,
extents and normalized body/relocation fingerprints are unchanged, with no
added or removed definitions. StringClass header acceptance passes; this
source has no pending StringClass queue key, so no debt retirement is claimed.
Strict preparation verifies this one owned source with a reusable receipt;
it does not update the census, index or linking status. Ordinary preview
retains LINKS and 435 authored bytes against index eba83a23be (2026-11-08 14:08).

The served VectorClass<StringClass> table at 0x007D0D80 still has LINK-619's
recorded provider/alignment boundary. The native row is owned by dx8wrapper;
the real-link queue selects this earlier path-ordered copy. No alignment
exception, row, pin or source-path move is applied. Publication and a new
actual image must decide current selection and bridge retirement; this
source cleanup does not establish runtime progress.

Published as e17651338f, first attempt 42.9 seconds. All five rows, the
parent EH graph, scoped DIR32 and converged data pass. The strict source
receipt resolves this source's own audit-receipt gap. The broader audit is
still INCONCLUSIVE: index eba83a23be versus base
0fbd488b314b440e163d497ec0b5fc11af609e9a, with the affected
Common/0CreateAHeroManager21FE49.cpp consumer lacking a current receipt.
Carry that consumer and actual selection into the next census/image.

The code-identity shadow report retains the existing cleanup binding to
DynamicVectorClass<StringClass>'s destructor: this TU emits an 11-byte
vptr-store/Clear tail call, while native 0x00121E20 is the 67-byte
VectorClass<StringClass> destructor that inlines storage release. This is
unchanged by the shared-type cleanup (all 16 fingerprints remain equal).
A private imported/forceinline DynamicVector destructor trial preserves
only four rows and introduces an unresolved __imp_ cleanup call. Ordinary
and early extern-template declarations preserve all five rows but change
none of the 16 COMDATs. These trials are not applied. A proper provider/
outlining reconciliation remains necessary; no import pin or alias is added.
