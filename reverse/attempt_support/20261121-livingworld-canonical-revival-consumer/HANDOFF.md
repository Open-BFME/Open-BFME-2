# Native header item 021: private LivingWorld consumer candidate

Status: the single frozen, unapplied source-only candidate has completed its
authorized private proof. Root acquired all 88 extra native scopes, refused none,
and retained the UnitRevivalEntry class lease. There were exactly two normal
compiles (original/candidate), two diagnostic -Z7 compiles of those same sources,
and four preprocessing snapshots around the diagnostic compiles, at most two
workers. No production, header, ledger, claim, Git, owning-tool adoption/verdict,
or shared-build-cache writes. Existing provider strict-current refresh and normal
Root acceptance are still required. This is at most one partial class-adoption
item, zero new recovered bodies or bytes.

Basis: BFME2 HEAD `64b343fb4109505cdb9073ebc21796b5c02d9500`.
The four complete served source files, canonical headers, original provider rows,
eight complete original code extents, and the November 4 handoff were read.
`SCOPE_AND_EVIDENCE.json` is explicitly the precompile preparation snapshot: it
binds their hashes and preserves the original bytes and disassembly. Its
untested status describes that earlier snapshot, not the subsequent results.
`SOURCE_CONTROL.json`, `RUNTIME_CLOSURE.json`, `TYPE_AND_PREPROCESS.json`, and
`TYPE_GRAPH_CLOSURE.json` contain the new private results. No stale trial verdict
is reused. The final manifest rechecks current source/header hashes separately
against the later Root integration head. At final recheck that head is
57b5fd6c7583173a890fe10a64141cb7bc7147a2: the intervening changes concern the
separate FlammableUpdateDtor adoption, its handoff, and header_queue.tsv. None of
this package's frozen sources, headers, or actually opened inputs changed.

## Proposed single consumer

Source:
`Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldPlayer.cpp`

Original SHA-256:
`1d1c030af14ae42e6e450bb7a0c90dd72d19280a8d3433dfbcb961e4e3c07c3a`

Private candidate: `LivingWorldPlayer.cpp`, SHA-256:
`1b785c93771d91ef35eaa8d8b19ea3a782783a9ed7c7414f510eb6b286907a10`

Unapplied source patch: `LivingWorldPlayer.patch`, SHA-256:
`720c4d186b43f2254ac4a75c0468463295d1dc309b2ccc595d004c1dc272d2fb`

The patch replaces the private declaration-only UnitRevivalEntry class with its
registered canonical header, replaces the two direct legacy FixedStorage128
includes with the registered Common/BfmeFixedStorage128.h, and maps only reviewed
UnitRevivalEntry member accesses and the two explicit mask word accesses. No
algorithm, compiler profile, calling convention, global, provider source,
header definition, or row identity is deliberately changed. The function-body
edits are the reviewed member spellings shown in the patch. The compiled code,
data, EH, and provider results are detailed below.

The old UnitRevivalEntry constructor/copy/destructor are declarations only. The
consumer continues to call the same out-of-line lifetime functions; the patch
does not define, flatten, or manually replace that lifetime. D8 size and member
offsets have independent original copy/accessor evidence in the existing header
and the retained complete original code. The legacy and canonical mask class
both have a declared 128-byte copy contract; the consumed native 0004548B provider
copies exactly 128 bytes through memcpy. The two local masks in rva002E14E9 are
explicitly copy-constructed. The canonical empty default constructor must not be
assumed equivalent to providers that clear 128 bytes; this candidate changes no
such provider.

## Exact additional reservations

`ROOT_REQUIRED_CLAIMS.json` is the complete machine-readable list:

- `class:BfmeFixedStorage128`.
- `file:Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldPlayer.cpp`.
- All 85 existing function RVAs from the source, including its existing EH rows.
- Existing data RVA `0x008049D8`, 128 bytes,
  `?g_00C049D8@@3QBUFieldParse@@B`.

Thus the existing whole-file inventory is **85 functions + one data row = 86
unique RVAs**. The prior 86-functions wording was incorrect. No extra data is
being added. Root already holds class:UnitRevivalEntry and its seven-lock native
class lease; those locks are not individual file/RVA claim refs. Both canonical
headers remain byte-for-byte unchanged and require no header edit.

## Completed private proof

Both complete source forms compiled under the same actual proper-TU profile:
the native baseline -O2 is followed by the region's effective -O1 -arch:SSE -G7,
with the unchanged original MD/EHs/STL/include flags. Native command equality
was asserted after removing only source/output paths. Literal relative includes
were mapped to the same physical canonical files, with every mapping hashed.
Object store was disabled; all source/object/sidecar/log outputs are private.
No owning adoption CLI or shared compile path was used.

- Both forms pass all **85/85** existing native row byte/REL32 checks, with zero
  unresolved and zero masked rows. All seven EH-owning parents report EXACT;
  the rest have no independent EH mismatch. Native DIR32 row-pair sets are also
  identical between the complete original and candidate.
- The existing 128-byte FieldParse table matches all original non-relocation
  bytes and all **14** relocation targets through the unmodified native data
  relocation checker in both forms. Fresh diagnostic S_GDATA32 records bind
  their type index to the actual COFF symbol using SECREL/SECTION relocations;
  the compiler's type is FieldParse[8], size128, in each. No implicit sizer or
  extra sizeof compiler probe was called.
- The only emitted-definition change is removal of the local 27-byte ANY2
  BfmeFixedStorage128 copy-constructor section. After precisely that removal
  and the resulting ordinal remap, **every other runtime section and relocation
  is exactly identical**, as are all other external definitions and all retained
  COMDAT selection/association facts. Runtime sections191 ->190. Weak bindings
  and directives are unchanged. The exact expected undefined change is adding
  that copy constructor and removing the sole local-copy dependency on memcpy.
- Neither form emits a BfmeFixedStorage128 default constructor, a
  UnitRevivalEntry constructor/copy constructor, or its destructor. Existing
  UnitRevivalEntry default/copy/dtor call identities remain external. No emitter,
  address-taker, or fake lifetime helper was introduced.
- Each diagnostic -Z7 object is independently runtime-identical to its own
  corresponding normal object. Within each source form, the preprocessing output
  immediately before and after that diagnostic compile is identical, and all
  opened inputs remain hash-stable. **The original and candidate full expanded
  streams are deliberately different**: the two class definitions and mapped
  field uses change. All common non-target expanded class bodies are identical;
  no class body is added or removed. Compiler macro options are unchanged; the
  patch introduces no source macro/alias/mode flip. The existing canonical
  include guards are the intended new include context.
- Fresh native CodeView layouts preserve167 complete class definitions and four
  complete enums. Only UnitRevivalEntry and BfmeFixedStorage128 differ. The
  private read-only semantic graph comparison parses all4003/4016 observed type
  records, retaining method CC/attributes, return/argument/this types, adjustment,
  pointer/modifier attributes, enum identity, and complete class definitions.
  Five removed and18 added semantic record forms belong entirely to these two
  target subgraphs; there are zero unrelated graph changes. Nominal class refs
  are leaves while every complete definition is independently compared, avoiding
  transitive permission for an unrelated class change. Raw type bytes and type
  indices are not claimed identical. This diagnostic supplements, rather than
  replaces, the native owning gates.

## Required ordinary provider refresh and Root acceptance

The current normal Object260Copy.obj independently matches the genuine
0004548B/27 retail row, without masking. Its raw copy body and complete normalized
memcpy relocation identity exactly match the removed local copy. Its ordinary
receipt is current, but its **strict** include-inventory receipt is not current;
no compiler refresh was performed by this worker. Root must rebuild it normally
and obtain strict-current evidence before acceptance.

The exact unchanged provider source is
`Code/Libraries/Source/WWVegas/WWLib/Object260Copy.cpp`, SHA256
`0d4120c49205515aad0e1ab1957dc19345d99b2c77bf116fdd7bdd406945065d`.
Its whole-file existing scope is three rows: 0004548B/27 mask copy,
002CF495/49 BfmeFixedObject260 copy, and 002CF8E8/18 _STL::_Construct.
`ROOT_PROVIDER_REFRESH_SCOPE.json` contains its file key and all three RVA keys
for Root to reserve if required. It introduces no source/header change or body
credit.

Read-only census snapshot a6e997404b4762fd69e6645dd5d9c1847c0478427c1ec29423284ba2593af8e7
places Object260Copy first at806, then LivingWorldPlayer7563,
UnitRevivalTracker7592, OwnedRecord900Copy12502; all four stored COMDAT digests
are c629fed2eba4 and classified retail. There is no symbol-specific actual MAP
exception. This records the **existing cached link order**, not a new real-link,
currency, selected-provider, or header-acceptance verdict. Ordinary Root preview
must establish current provider preservation.

Private normal .deps creation reported that include-search inventories changed
during the parallel probe. The private row/object results above are real; these
private sidecars are not used to claim strict currency. Fresh before/after
preprocessing around diagnostic compilation and complete runtime identity bind
the diagnostic evidence, but do not mint native strict-current receipts. Do not
repeat or reclassify this as a master baseline defect. Root's normal build/accept
is authoritative; none of these private objects should enter its match cache.

Root's ordered normal commands are in `ROOT_COMMANDS.json`: ordinary provider
build, apply/check the frozen source patch under the current scopes, normal
consumer build, and the regular owning-tool path for this one consumer:

`python3 tools/header_adopt_lane.py accept --class UnitRevivalEntry Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldPlayer.cpp`

The ordinary class/byte/provider/link gates decide retirement. No native accept
result has yet been obtained; no queue row was retired by this worker.
The two other providers and FreelistPool remain part of the served-file review,
with the genuine blockers below, rather than being described as complete.

## Remaining three served units: genuine lifetime prerequisite

UnitRevivalEntry.cpp uses the 128-byte clear helper in its constructor member
initializer plus a real B0 subrecord constructor. UnitRevivalTracker.cpp owns
typed record copy construction and real UnicodeString/AsciiString cleanup.
FreelistPool.cpp's empty UnitRevivalEntry destructor naturally emits the original
78-byte order: D4 string, D0 string, then B0 record destructor.

The current canonical header represents B0 only as `char[0x18]`. Replacing those
providers with it would discard owned record lifetime. A destructor-body call
runs before automatic member teardown and cannot preserve the required order;
manual destruction would cause duplicate cleanup of the actual string members.
The 32-byte FreelistPool view additionally covers trailing trivial C8/CC storage,
while the native record provider itself covers 24 bytes. No source-only raw
storage substitute has been attempted.

The original B0 record nominal type is unknown. Existing genuine providers are
Rva004E04FD default 004E04FD/22, Rva001EB15A copy 001EB15A/89, and
001EB05E/54 record destruction, with current independently rowed aliases. Other
source consumers have differing nominal/class-key/byte-flag declarations.
A future coherent owned record representation needs its own complete current
scope and provider/type/lifetime reconciliation; it is neither authorized nor
part of this source-only patch. Do not brute-force canonical char storage or
claim all four served units adopted.

Confidence: the private scoped byte/EH/data/runtime/type results and the three
provider lifetime blockers are directly evidenced. A current ordinary provider
refresh, owning acceptance, whole-image link, and runtime success remain separate
claims; this package makes none of them.
