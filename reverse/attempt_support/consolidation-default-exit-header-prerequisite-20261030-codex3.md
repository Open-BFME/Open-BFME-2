# DefaultProductionExitUpdate canonical headers — 2026-10-30 codex3

The default picker claimed the DefaultProductionExitUpdate seed, constructor,
pool-key and transfer files at 41d6e95980. The ProductionExitUpdate naming
planner's original-path leads, alternatives and blockers were read before the
composition trial. Its hints do not establish retail TU provenance. The
supported merge dry-run accepted no donors: the seed lacks rva000487F82 and
m_secondary20, and its legacy Coord3D/Xfer definitions conflict with the transfer
donor. The mixed deleting-destructor source was not changed.

## Verified prerequisite

The transfer donor now includes the existing canonical Thing and Matrix3DData
headers instead of defining those classes privately. Canonical Thing occupies
0x60 bytes, so Object's remaining padding starts at 0x60 and keeps its AI pointer
at 0x258. Matrix3D's Vector4 rows preserve the same twelve float offsets. The
existing alias-safe inline transform uses those rows through a unit helper;
its arithmetic and input copy are preserved.

Target evidence is the four existing rows and their exact compiled bytes:
xfer (0x0048805B, 62 bytes), exitObjectViaDoor (0x00488099, 463 bytes), funclet
(0x0078C2E1, 8 bytes) and handler (0x0078C2E9, 10 bytes). The canonical Thing
header separately documents target constructor/vtable/layout evidence and
Zero Hour declaration-name evidence. This change establishes neither a new
donor name nor a new retail TU placement.

Both `header_adopt_lane.py accept --class Matrix3D <donor>` and the corresponding
Thing acceptance pass, retiring **two header-queue rows** through their owner.
No header, compiler flag, ledger row, pin, data/identity register or hatch changes.
There are no source moves or deleted debt owners. The seed's three existing
present-unmatched hatches remain untouched. Searches of the header, MS-header,
gate, data and code-identity registers find no remaining key for the transfer
source.

## Verification and provider scope

- `./build.sh <donor>`: **4/4 matched**, including string, float and import
  reference checks. Frozen-file and canonical-class checks pass.
- `eh_verify.py`: **1 EXACT**, no missing objects or EH debt; renumbered $L5830
  is verified at the existing funclet row by its parent EH data.
- `link_check.py --prepare-current <donor>`: one strict current receipt.
  The ordinary check predicts **534 -> 534** linking bytes against the
  2026-10-30 10:11 census at 12b9e7a7c0. New-variant check passes.
- Converged data check: 11 addresses, no second names or unjudged rows.
  `check_csv.py` passes (99014 function rows, 9396 symbols, 2239 data rows).
- Object comparison with supported allowed_symbols/census readers preserves
  all 37 pre-existing external code bodies, including relocation identities
  after mapping the transform's old and new names. The 42 original non-debug
  sections preserve bytes, flags, relocations and COMDAT selection policies.
  SafeSEH symbol indices resolve to the same handler; compiler-generated local
  label numbers are compared by section contents, external anchors and offset.
  Root references and discardable-section reference edges are unchanged after
  mapping the helper name and accounting for the added compiler helper.

There are two provider differences to retain in the next census review:

1. The 192-byte Matrix3D::Transform_Vector COMDAT becomes
   DefaultExitTransform::Transform_Vector with identical bytes and no
   relocations. Neither name is referenced by this object's retained code.
   The census has another old-name copy in
   QueueProductionExitUpdateExitObjectViaDoor.cpp with the identical digest
   `0c31ff19fd6f`; removing this copy leaves that fallback. This is a compiler
   helper refactoring, not a newly recovered retail symbol.
2. The canonical headers emit a discardable 34-byte compiler array-constructor
   helper, `??_H@YGXPAXIHP6EPAX0@Z@Z`, with no references. External code
   definitions rise 37 -> 38 and non-debug sections 42 -> 43. The census has
   946 copies; its selected ATL provider precedes this TU and is judged retail.
   The new-variant check accepts this additional copy.

The full outgoing batch's affected-consumer/freshness result belongs to the
pre-push audit. The local index predates the checkout base, so the local checks
do not establish a complete current consumer closure or a census gain. Carry
any inconclusive batch-audit consumers into the next census rather than
counting them as verified.

Scratch evidence: build/default-exit-adoption-codex3/{before.cpp,before.obj,
after.obj,compare.py,object-proof.json,provider-scope.json,eh.json}. Object
SHA-256 values are a54546e19e1e0ae3ee96f02bde454325b5a0abe511edd69e7369d95821a15d99
(before) and 1d6580eefa260c115c2ecee26206a97d6a870518ff2ad709217c792c033faca7
(after). An expanded-arithmetic trial changed SSE evaluation order; it was
reverted and the retained helper shape reverified before publication.

## Remaining composition work

This adoption clears the two recorded header prerequisites. It does not
reconcile the seed's UpdateModule/ExitInterface receiver views, missing pool
member or constructor fields, or the legacy Coord3D/Xfer includes. The initial
merge failures are not retried unchanged. Reconcile those contracts in separate
verified changes before another merge attempt. File reduction 0; header debt
retired 2; data/identity debt retired 0; no census or image-ownership gain claimed.
