### LINK-182 Real-link repairs in Libraries and Common (2026-11-03, seat halilkkaya-codex)

Notes Codex wrote for each commit, moved here from the pre-split register.

### RTC stack.obj duplicate and Codex handoff (2026-11-04, halilkkaya-cx-o5)

Base `20f35184b7`. The real link at `efbd3f2cb2` reports one LNK2005:
`@_RTC_CheckStackVars@8`, defined in both the vendored stack.obj and
`Code/Libraries/Source/CRT/RtcStack.cpp`.

The vendored stack.obj in `vendor/msvc71crt/msvcrt.lib` defines only
`__RTC_CheckEsp` and `@_RTC_CheckStackVars@8`. With relocations masked,
both sections equal retail at 0x0075A5A2 and 0x0075A5C5. Their REL32
targets are the rowed `_RTC_Failure` at 0x0075A904 and `_RTC_StackFailure`
at 0x0075AAD6.

Row 0x0075A5A2 vendors that member, so the link pulls stack.obj in, and
stack.obj's second definition collides with RtcStack.cpp's.

Every route to a single provider is closed:

- **Vendor 0x0075A5C5 as well.** `conversion_gate.py` Rule B refuses it.
  A staged probe printed "was clean C++ at ... RtcStack.cpp, repointed to
  vendor/msvc71crt/msvcrt.lib", exited 1, and was reverted.
- **Move `__RTC_CheckEsp` into RtcStack.cpp.** It consumes the caller's ZF,
  so it would need a naked or `__asm` body, which Rule A refuses.
- **Restore the `ecbefd2e35` MASM owner.** The gates allow it. But neither
  RVA has an approved TU, and it would create a one-function file. This
  waits for an owner or maintainer exception.

The handoff has the evidence and a patch for the MASM restoration that
applies cleanly to this base. The same directory records the
ProductionPrerequisite freeBytes prerequisite: rows 0x004EE1E2/0x004EE20B
call the PerTurnStats copy constructor 0x004EE1A9, and their approved TU is
LivingWorldScoreKeeper.cpp.
[Handoff](../../reverse/attempt_support/real-link-codex-efb5fcbb60-20261104/README.md).

### Two blocked names: Rva003C2F40Owner dtor and ProductionPrerequisite freeBytes (2026-11-04, halilkkaya-cx-o5)

The real link at `f6d845ecd4` (run 41835972123: 32 unresolved and 1
duplicate, before Codex's batch landed) still reports these two names in
this slice. Neither has a supported fix today. No source changed.

- **`??1Rva003C2F40Owner@@UAE@XZ`.** All of the following belong to one
  retail class, which uses table 0x00BFE408:
  - the default ctor 0x002BAE57 (`Rva003C2F40Owner`);
  - the (unsigned, char) ctor 0x003FD64D (`BfmeRectVNI`);
  - slot 0, the deleting dtor 0x002BAE8F, rowed `??_GRva002BAEAB@@QAEPAXI@Z`.
    It calls dtor 0x002BAEAB (`??1Rva002BAEAB@@QAE@XZ`, 53 B; it calls tree
    dtor 0x002B80CE and Snapshot dtor 0x0049B47C, and stores no vptr);
  - slot 2, the name getter 0x002BAE89 (`Rva002BAE89Named`).

  `rename.py class --fold` refuses every order:
  - Owner→Rva002BAEAB: the table is not named `??_7Rva002BAEAB`.
  - Rva002BAEAB→Owner: Rva002BAEAB installs no table.
  - Owner→BfmeRectVNI: slot 0 holds a third class.

  This is recorded as a false reject in `re_attempts.log`. Once a fold
  that accepts a dtor-only placeholder whose deleting dtor sits in slot 0
  lands, `function --virtual` (QAE→UAE) on 0x002BAE8F/0x002BAEAB gives the
  constructor TU its provider.
- **ProductionPrerequisite.cpp `?freeBytes@AsciiString@@AAEXXZ`.** I tried
  a scratch-only compile under `build/scratch_cx5` that stops the
  instantiation of the local `vector<PrereqUnitRec>::_M_insert_overflow`
  (to bind push_back to the rowed 0x004F5165) and explicitly instantiates
  the two helpers.
  - MSVC 7.1 refuses it with C2248, because the ZH header keeps
    `PrereqUnitRec` private.
  - With access forced in scratch, the ZH `releaseBuffer`/`freeBytes`,
    `~AsciiString` and `??_GPrereqUnitRec` COMDATs are still emitted. That
    route therefore cannot remove the name.

  The prerequisite is unchanged: readmit 0x004EE1E2/0x004EE20B (both call
  0x004EE1A9, the PerTurnStats copy constructor) as PerTurnStats
  instantiations in the approved `LivingWorldScoreKeeper.cpp`. Then
  ProductionPrerequisite.cpp can take the canonical BFME 2 string.

  The readmission has to carry two rows with it:
  - 0x004EE233 (`_M_allocate_and_copy`). It calls 0x004EE1E2 by the
    PrereqUnitRec spelling, which `symbols.csv` also pins to 0x004F5097.
  - The PerTurnStats allocator name at the shared 12-byte allocate
    0x00395928.

  **Scratch feasibility (compiled only under `build/scratch_cx5`).** The
  probe used the TU's own `// cl:` line plus the region defaults
  `tools/flag_defaults.py` gives it (/O1 /G7 /arch:SSE). The view was a
  12-byte `LivingWorldScoreKeeper::PerTurnStats` whose copy ctor is
  declared `throw()` (without `throw()` the helpers come out 38/37 B). With
  relocations masked, every PerTurnStats instantiation below equals retail:

  | Instantiation | Retail | Size | Calls |
  |---|---|---|---|
  | `__uninitialized_copy` | 0x004EE1E2 | 41 B | REL32 to `??0PerTurnStats@LivingWorldScoreKeeper@@QAE@ABV01@@Z`, 0x004EE1A9 |
  | `__uninitialized_fill_n` | 0x004EE20B | 40 B | same |
  | STLport `vector<PerTurnStats>::_M_allocate_and_copy<PerTurnStats*>` | 0x004EE233 | 45 B | `allocator<PerTurnStats>::allocate`, then the copy helper |
  | `allocator<PerTurnStats>::allocate` (emitted) | 0x00395928 | 28 B | — (an ICF-alias candidate) |
  | implicit `_Construct<PerTurnStats>` (emitted) | 0x004EE1D0 | 18 B | — |

  One trap: that implicit `_Construct` is a SELECT_ANY COMDAT, and
  `StlportConstructCopySiblings.cpp` defines the same name as an explicit
  specialization, which is NODUPLICATES. Linking both gives LNK2005, so
  0x004EE1D0 must move into this TU with the others.

  Plan, in order:
  1. Retraction commit: the three PrereqUnitRec spellings (0x004EE1E2,
     0x004EE20B, 0x004EE233). The last one empties
     `Thing/Rva004EE233AllocateCopy.cpp`.
  2. Readmit all four rows under PerTurnStats in `LivingWorldScoreKeeper.cpp`,
     the approved TU. That includes moving 0x004EE1D0 there and dropping
     its explicit specialization. Add an `--icf-owner` alias at 0x00395928.
     Check the alias's callee `?allocate@?$allocator@D@_STL@@SAPADIPBX@Z`,
     which has no ledger row or pin.
  3. Switch ProductionPrerequisite.cpp to the canonical string
     (`/FIzh_ascii.h`).

  LivingWorldScoreKeeper.cpp LINKS today (3,347 B), so run base/tip
  `link_check` around every step.

### PerTurnStats readmission blocked by its callers (2026-11-04, halilkkaya-pt-o1)

Base `b675551755`. **Status: blocked.** No source, ledger or pin changed.
`freeBytes` stays unresolved.

The tu_map check passes: 0x004EE1D0, 0x004EE1E2, 0x004EE20B and 0x004EE233
are all approved for `LivingWorldScoreKeeper.cpp`. What blocks the plan is
something it does not cover: the callers of the three PrereqUnitRec spellings.

- **Callers (retail E8 scan).**
  - 0x004EE1E2 is called from:
    - 0x004EE6D0 (`Rva004EE6D0Insert.cpp`);
    - 0x0051ED0A, the `Rva004EE501` copy ctor in `AptTimeLine.cpp`;
    - 0x0051F7AD, in `StlSweepR3Rva0051F7AD.cpp`, whose approved TU is
      AptTimeLine.cpp.
  - 0x004EE20B is called from 0x004EE6D0.
  - 0x004EE233 is called from 0x004EE55E (`StlVectorReserveProviderRepairs.cpp`)
    and 0x0051F7AD.
  - 0x004EE1D0 has no direct caller.
- **A retraction alone is refused.** I simulated step 1 against a scratch
  ledger and restored it afterwards.
  - `name_dependents --staged` lists six units. ThingFactory.cpp is not one
    of them.
  - Each caller fails `./build.sh`: 0x004EE6D0, 0x004EE55E, 0x0051F7AD and
    0x0051ED0A.
  - The reason: the copy and fill names fall back to their pins 0x004F5097 and
    0x004F50BD (the real PrereqUnitRec helpers), and `_M_allocate_and_copy`
    falls back to nothing.
  - So steps 1 and 2 must be one commit, and every caller must be respelled to
    PerTurnStats in that same commit.
- **Some callers cannot name PerTurnStats.**
  - `Rva004EE6D0Insert.cpp` can: it already carries a private
    LivingWorldScoreKeeper stub.
  - A nested-forward stub in `StlSweepR3Rva0051F7AD.cpp` is refused by
    `class_gate`. I tested this and reverted it.
  - StlSweepR3Rva0051F7AD.cpp and StlVectorReserveProviderRepairs.cpp cannot
    include the canonical header either. Its `<vector>`/`<map>` clash with the
    `_STL` templates those files declare by hand.
  - `AptTimeLine.cpp` cannot include the canonical header either, because both
    define `Rva004EE501` on different bases: `_Vector_base<PrereqUnitRec>`
    against `_Vector_base<int>`. Its copy ctor needs the 12-byte count base
    at 0x005C8C37.
- **What `Rva004EE501` really is.** It is retail's
  `vector<LivingWorldScoreKeeper::PerTurnStats>` (structural inference):
  - 0x0051ED0A copies through 0x004EE1E2.
  - That helper's element copy, 0x004EE1A9, installs vftable 0x00C62A28,
    whose slots 2 and 3 are the rowed `PerTurnStats::GetSnapshotName` and
    `xfer`.
  - The dtor 0x004EE501, operator= 0x0051F7AD, reserve 0x004EE55E, overflow
    0x004EE6D0 and push_back 0x004EE9B1 use the same helpers.
- **Prerequisite.**
  1. Give the canonical header a nested PerTurnStats and a
     `vector<PerTurnStats>` member at +0x28.
  2. Fold the `Rva004EE501` views (header, AptTimeLine.cpp,
     RvaVectorDtorFamily.cpp) and their rows onto that vector.
  3. Then run the plan's steps 1 and 2 as one commit, together with the caller
     respellings, and step 3 after it.
- **ThingFactory.** Main asked for a check. The plan would not change
  ThingFactory's PrereqUnitRec name: its unresolved
  `??4?$vector@UPrereqUnitRec@ProductionPrerequisite@@...` is pinned at
  0x000120C0 and is outside this family.
- **Correction to the plan.** The allocate alias's callee
  `?allocate@?$allocator@D@_STL@@SAPADIPBX@Z` is rowed: `GameMemory.cpp`,
  0x000307F0.
- **Link baseline.** The four callers, StlportConstructCopySiblings.cpp,
  Rva004EE233AllocateCopy.cpp and LivingWorldScoreKeeper.cpp all LINK.
  ProductionPrerequisite.cpp (429 B) and ThingFactory.cpp (118 B) do not.

[Evidence](../../reverse/attempt_support/perturnstats-readmission-callers-20261104.md).

**Banked: `Rva004EE501` as `vector<PerTurnStats>` (2026-11-04, halilkkaya-pt-o1).**
I sized the prerequisite and did not start it. It is a reconciliation of
several headers and many rows, larger than one seat's remaining budget.

The placeholder name cannot simply take the real element. The header defines
`Rva004EE501` before `LivingWorldScoreKeeper`, because it is the member type at
+0x28. `LivingWorldScoreKeeper::PerTurnStats` cannot be named until that class is
complete. So the fix is the real `vector<PerTurnStats>`, and every row and view
below has to move to it together.

- **Canonical `LivingWorldScoreKeeper.h`.**
  - `struct Rva004EE501 : _Vector_base<int>` has a forceinline default ctor and
    an out-of-line dtor.
  - Member `Rva004EE501 m_28` sits at +0x28.
  - `PerTurnStats` is only forward-declared.
  - Header consumers: LivingWorldScoreKeeper.cpp and Rva004EE15BFwd.cpp, which
    also defines its own `PerTurnStats` body.
- **Rows named for the placeholder, which become `vector<PerTurnStats>`
  members.** Each needs a `rename.py` pass and a decision on inlining, because
  STLport's vector dtor and copy ctor are inline but retail calls them out of
  line.
  - `??1Rva004EE501@@QAE@XZ` 0x004EE501, 63 B with EH, in
    RvaVectorDtorFamily.cpp. That file also carries the hatch
    `/alternatename:??1Rva004EE501Subobject@@QAE@XZ=??1Rva004EE501@@QAE@XZ`.
  - `??0Rva004EE501@@QAE@ABV0@@Z` 0x0051ED0A, in AptTimeLine.cpp.
  - `vector<Rva0051F7ADRecord>::operator=` 0x0051F7AD, in StlSweepR3Rva0051F7AD.cpp.
  - `Rva004EE55EVector::reserve` 0x004EE55E, in StlVectorReserveProviderRepairs.cpp.
  - `Rva004EE6D0::rva004EE6D0` 0x004EE6D0 and `push_back` 0x004EE9B1, in
    Rva004EE6D0Insert.cpp.
  - `Rva004EE540::rva004EE540` 0x004EE540, in LivingWorldScoreKeeper.cpp.
  - `Rva004EE9E9XferVector` 0x004EE9E9 (element view `Elem003AF8C0`).
- **Other views of the same vector or element.**
  - AptTimeLine.cpp: `Rva004EE501 : _Vector_base<PrereqUnitRec>` (a global
    placeholder) and `Rva004EE501Subobject` at +0x20 of `Rva00520211Element`.
  - Private `LivingWorldScoreKeeper` or `PerTurnStats` bodies in
    Rva004EEE38CollectTurnStats.cpp, V3PolyCopyCtors.cpp, ConstIntGetters.cpp,
    StlportConstructCopySiblings.cpp, Rva004EE6D0Insert.cpp and
    Rva004EE15BFwd.cpp.
  - Rva004EEE38CollectTurnStats.cpp has the fullest `PerTurnStats` body:
    Snapshot base, `Short m_numRegions/m_numUnits/m_numArmies`. The retail
    name string `"LivingWorldScoreKeeper::PerTurnStats"` in ConstIntGetters.cpp
    supports the class name.
- **Callers with hand-declared `_STL` templates.** StlSweepR3Rva0051F7AD.cpp and
  StlVectorReserveProviderRepairs.cpp say those stubs exist to avoid emitting a
  second, non-retail helper family. Moving them onto real `<vector>` needs its
  own byte and link proof.

Order:
1. Put `PerTurnStats` (from Rva004EEE38CollectTurnStats.cpp's body) and a
   `vector<PerTurnStats>` member into the canonical header.
2. Rename the 0x004EE501 and 0x0051ED0A rows to that vector's members and
   drop the alternatename.
3. Adopt the header in the callers.
4. Run cx-o5's steps 1 and 2 as one commit, then step 3.

### ProductionPrerequisite freeBytes repaired without the PerTurnStats readmission (2026-11-06, halilkkaya-lk36)

Base `bd49217dc8`; real link at `306f01e6f6` listed `?freeBytes@AsciiString@@AAEXXZ`,
referenced from the unit's `?releaseBuffer@AsciiString@@IAEXXZ` COMDAT.

- Cause (target fact, current object): the unit inlines nothing from Zero Hour's
  AsciiString, so `??1PrereqUnitRec` tail-jumps to an emitted `releaseBuffer` copy,
  and that copy calls Zero Hour's `freeBytes`. Retail has neither body; its
  out-of-line `??1AsciiString@@QAE@XZ` is the row 0x0048BA39 in ascii_string.cpp
  (`jmp` to StringBase<char>'s releaseBuffer 0x00036410), and every kept copy of
  that name has the one retail digest.
- Fix: `reference/shims/zh_ascii_outofline/Common/AsciiString.h` skips its inline
  `~AsciiString` when a TU defines `BFME_ASCIISTRING_DTOR_OUTOFLINE` (the guard
  pattern of its noinline constructor). Only ProductionPrerequisite.cpp defines it.
  `??1PrereqUnitRec` now jumps to `??1AsciiString@@QAE@XZ`; the `releaseBuffer` and
  `~AsciiString` COMDATs and the `freeBytes`/`InterlockedDecrement` references are
  gone. No other external changed.
- Verified: 6/6 rows exact; ControlBar_Rva0035B03E.cpp (the shim's other user)
  rebuilt with identical non-debug sections; scoped DIR32 OK; link_check
  ProductionPrerequisite.cpp 0 -> 0 (its census unresolved `freeBytes` is gone; the
  PerTurnStats COMDAT losers above remain), ControlBar_Rva0035B03E.cpp and
  ascii_string.cpp LINKS unchanged. The PerTurnStats readmission is still the
  route to make the unit link in the census; the real link needs no more here.

### W6 native tree-find readmission (2026-11-04, halilkkaya-codex)

After retraction `39508a56f6`, ordinary `add_match.py` admission recovers the
actual STLport const tree-find operation at 0x0016DEC0 in the existing source
path. It reuses the existing Gen_p12pod key and `_M_find` provider; the latter
also compiles to all 108 native bytes in the new normal object. No application
key/container name, pin or helper alias is invented. The missing string-shaped
element comparison from artifact `612abfbebb` disappears.

Normal checks pass all nine family rows and the frozen check; true base/tip
preview preserves all eight LINKS peers and adds the wrapper's existing 21
bytes (4,332 -> 4,353). Scoped DIR32 passes nine rows with no DIR32 references.
The two commits retain final unique coverage, retire one false pin, and change
no source path. Original application type/outer container names remain unknown;
no full-image/census result is claimed.
[Retraction and readmission evidence](../../reverse/attempt_support/tree-find-16dec0-20261104-codex.md).

### Disproven W6 set-lookup retraction (2026-11-04, halilkkaya-codex)

Base `c0b890798f`: retire the wrong `set<...>::lower_bound` claim at
0x0016DEC0 and the lower-bound pin wrongly bound to the existing 108-byte
find helper. Its final equality rejection and three-integer key disprove the
old string-shaped model. The twelve removed definitions have no outside
consumer losing its provider; the actual Gen_p12pod provider family remains
exact. A separate reference reconstruction already matches the full 21-byte
wrapper and 108-byte helper, and is readmitted next. No constructor/operator
alias or invented application name is introduced.
[Native proof, orphan/path/debt audit and reconstruction](../../reverse/attempt_support/tree-find-16dec0-20261104-codex.md).

### Experience sort comparator in the mixed Crate unit (2026-11-04, halilkkaya-codex)

`CrateCreationEntryList.cpp`'s 0x00288E8D sort is called only by
ExperienceLevelStore's list-header view. Its native merge at 0x00288874
calls the existing `ExperienceLevel::operator<` at 0x00288621 (orders the
final overrides' required-experience fields). An inline-only comparator
specialization now uses that provider; it does not order actual eight-byte
crate records or claim those two element families have one identity.
The missing free crate comparison from artifact `612abfbebb` disappears,
and the merge copy now agrees with retail. The comparator emits neither a
standalone definition nor an import, and its one removed definition has no
outside consumer losing its provider.

Normal verification passes all 107 rows across the mixed unit, insert consumer,
ExperienceLevelSystem, native list providers and CrateSystem. The sort's EH
graph is EXACT and the frozen check is clean. True base/tip preview over that
family and first-copy COMDAT providers (32 units, `a62ac1c10b`) retains all
30 LINKS units and 48,315 preview bytes. Scoped DIR32 passes 107 rows plus
25 witnesses. The sort's incorrectly sized list-base constructor remains
blocked; recover the separate ExperienceLevel and crate element identities
before consolidating this mixed source. No census/full-image claim.
Receipts: `build/seat_crate_{base,tip,build,family_build}.log` and
`build/seat_crate_cohort.{txt,json}`.

### PA vector element operation providers (2026-11-04, halilkkaya-codex)

Base `e8527d1743`: `PAVectorEraseRangeFamily003AF.cpp`'s sixteen-byte copy
now uses the existing 0x0052BB9A constructor operation, and its twenty-four-byte
assignment uses the existing 0x003F2A11 operation. Inline-only adapters preserve
the opaque element spellings and footprints; they emit neither new element
methods nor imports. The constructor view is novtable so its real provider
performs the witnessed vptr initialization. No alias, pin, row or element
identity claim is added. Both artifact `612abfbebb` unresolved names disappear.

All 83 family rows verify (both owned vector rows, the constructor provider,
assignment provider and range-copy provider); the frozen check is clean.
True current-object base/tip checks of that family and first-copy COMDAT
providers (25 units, index `a62ac1c10b`) preserve all 23 LINKS units and
69,412 preview bytes. Scoped DIR32 passes 83 rows plus 50 witnesses. The
pre-existing non-retail selected overflow body is still blocked (LINK-002);
the earlier failed temporary/tag forwarder trials were not repeated.
An out-of-line assignment adapter was discarded because it introduced an
unrowed body; the retained adapters have no standalone code or import.
No whole-image/census closure is claimed. Receipts: `build/seat_pa_*`.

### Delayed spline event's Snapshot base (2026-11-04, halilkkaya-codex)

Base `35cb072fd7`: replace `Rva003C2F40TreeCtor.cpp`'s private base with the
canonical constructor-only Snapshot view. Both native constructor unwind and
the existing complete destructor reach Snapshot's 0x0049B47C body. Explicit
padding preserves the witnessed map offset +0x0C. This removes the synthetic
`Rva003C2F40Base` destructor error from artifact `612abfbebb` and the stale
empty-base constructor definition, without a new row, name, pin or alias.

All 13 rows across constructor, existing destructor, event-transfer consumer
and map provider verify; constructor EH is EXACT and its frozen check is clean.
True base/tip preview over those units and first-copy COMDAT peers (11 units,
index `a62ac1c10b`) preserves all nine LINKS units and 10,772 preview bytes.
Scoped DIR32 passes 13 rows plus eight witnesses. The owner destructor name
still lacks a provider; the native 53-byte body is already rowed under
`Rva002BAEAB`. Native seven-slot event identity/ownership reconciliation is
still required (LINK-161); this only repairs the proven base edge and does
not claim a complete native table. Receipts: `build/seat_spline_*`.

### Player's UnitRevivalTracker cleanup (2026-11-04, halilkkaya-codex)

Base `6a4bb58f9f`: `PlayerCtorBFME2.cpp` no longer declares an unsupported
virtual UnitRevivalTracker destructor. The actual constructor 0x0037F27B
installs a one-slot xfer table, and Player's native unwind destroys the +0x738
member through the existing nonvirtual eight-byte owner at 0x002B0B8E.
The local constructor view now declares the real xfer slot and expands its
nonvirtual teardown to that existing owner. No row, pin, alias or original
destructor name is invented. The sole real-link tracker-destructor error
from artifact `612abfbebb` disappears.

Player's 29 rows, owned data and complete EH graph stay exact; the three-unit
family build passes 72 rows and the frozen check is clean. True current-object
base/tip preview over constructor, destructor, tracker initializer and all
first-copy COMDAT providers (29 units, `a62ac1c10b` index) preserves all 27
base LINKS units and adds Player's 593 existing bytes (87,442 -> 88,035).
Scoped DIR32 passes 72 rows plus ten witnesses. The existing table/element
recovery issues in other family units remain; no census or full-image result
is claimed. Receipts: `build/seat_tracker_{base,tip,build,family_build}.log`
and `build/seat_tracker_cohort.{txt,json}`.

### XferSave constructor teardown providers (2026-11-04, halilkkaya-codex)

Base `2a94cc974e`: `BfmeConv881O1.cpp` now gives its two twenty-byte members
the existing opaque lifetime views used by the rowed XferSave destructor.
Construction still calls the same existing hash-map initializer names;
the +0x18 unwind now calls its actual 0x0060D0AE owner. Declaration-only
destructors for the construction-only map/table views prevent emission of
their unused teardown trees. No kept object references those declarations.
The nonexistent `Gen_t_009d80b0_p12cd` and `Gen_t_009d8120_p12cd` destructor
references disappear, resolving both real-link artifact names in this unit.
The twenty removed definitions have no outside consumer losing its provider.
This recovers lifetime edges, not the unknown map element types or names.

Normal verification passes all 121 rows in the constructor, native destructor,
0x0060D0AE owner and System/XferSave; constructor EH is EXACT and its frozen
check is clean. True base/tip checks of that family plus first-copy COMDAT
providers (33 units, index `a62ac1c10b`) retain all 31 base LINKS units and add
the constructor's 117 existing bytes (45,789 -> 45,906 preview bytes).
Scoped DIR32 passes 121 rows plus six witnesses. System/XferSave's existing
identity/selected-provider findings remain. No census/full-image claim.
Receipts: `build/seat_xfer_{base,tip,build,family_build}.log`,
`build/seat_xfer_cohort.{txt,json}`, `build/seat_xfer_removed.json`.

### R3 0x001DE3E3 duplicate-claim retirement (2026-11-04, halilkkaya-codex)

Base `bd37f44974`: retire `StlSweepR3Rva001DE3E3.cpp` and its unsupported
one-byte-element assignment claim, retaining the existing full 31-byte owner
in `Rva001DE3E3Guard.cpp`. The orphan scan found Eva's reset as the sole
assignment consumer; it now calls that owner's existing spelling and remains
exact. Fourteen other private definitions have no outside census touch and
no surviving source use. Both unused clear/copy pins are retired. The two
record copy/destructor errors from real-link artifact `612abfbebb` disappear
with the false instantiation. Source count falls by one, unique coverage is
unchanged, and no name or layout is invented.

Normal checks pass 29 rows; true base/tip 50/49-source previews retain all
47 LINKS units and 165,621 preview bytes; scoped DIR32 passes 29+24 witnesses.
Native element recovery and full-image/census confirmation remain open.
[Ownership, orphan, path/debt audit and verification](../../reverse/attempt_support/hashtable-1de3e3-overclaim-20261104-codex.md).

### AerialPathfinder constructor base (2026-11-04, halilkkaya-codex)

Base `efb5fcbb60`: replace the constructor's private `Rva0022C987Base`
with the existing canonical `SubsystemInterface`, as its rowed destructor
already does. Retail calls its constructor at 0x001B4E63 and its unwind
destructor at 0x001B4E74. The synthetic base destructor was the one error
attributed to this source in real-link artifact `612abfbebb`; its undefined
name disappears. No new provider, pin, alias or row is introduced.

Normal byte verification passes all five rows across the constructor and
destructor; the constructor's frozen-file check is clean. True current-object
base/tip previews over both units and their first-copy COMDAT providers
(`MilesAudioVolumeConstructor.cpp`, `stlport_pod_list_bodies.cpp`), against
index `a62ac1c10b`, retain all three LINKS peers and 1,907 preview bytes.
Scoped DIR32 passes five owned rows plus three witnesses. The constructor
still has the existing allocator-import and selected list-destructor findings
in preview (LINK-002); its abbreviated vtable remains separate recovery work.
No whole-image or census result is claimed. Local receipts:
`build/seat_aerial_{base,tip,build}.log` and `build/seat_aerial_cohort.json`.


### CDManager real-link donor cleanup (2026-11-03, halilkkaya-codex)

Base c1325ac0b6: remove fourteen unrowed Zero Hour methods while retaining the
two ICF getter rows and TheCDManager. All eight real-link artifact names
attributed to this source disappear from its undefined externals. Six-source
normal checks pass389 rows; true base/tip preview retains five LINKS units
and changes CDManager0->54B, with no loss. Scoped DIR32389+17 witnesses passes.
No full real-link rerun or census confirmation is claimed; the actual CDManager
implementation remains separate work. [Audit and name list](../reverse/attempt_support/real-link-cdmanager-20261103.md).


### Dynamesh/shatter real-link donor closure (2026-11-03, halilkkaya-codex)

Base02ba74b593: retain the five owned leaves and remove both unrowed donor
contexts together. All21+12 consumer undefined references disappear;25 unique
artifact names are attributed only to this pair. Normal49-row/eight-source
checks and scoped DIR3249+12 witnesses pass. True A/B retains four LINKS peers
and adds both units (246 existing bytes); matinfo and twiddler are already
blocked at base. The13 common COMDAT fingerprints are identical; no external
provider is added and no remaining outside reference loses its last provider.
Global real-link/census confirmation remains pending. Collect inline ownership,
Twiddler element identity and the particle class cohort remain open; failed
trials are restored. [Name list, audits and exact boundaries](../reverse/attempt_support/real-link-mesh-pair-20261103.md).


### LINK-175 Player donor-emission follow-up (2026-11-03, halilkkaya-codex)

Base8e7d73b3a6: remove the unrowed one-argument transferAssetsFromThat and
retain its owned getDefaultTeam emission with an ordinary member address.
Both Money consumer undefineds disappear. Twelve code rows/one data row and
179 common COMDAT fingerprints remain; ten-source218-row checks and true A/B
retain nine LINKS peers and add Player112B. Scoped DIR32218+68 passes. The
getDefaultTeam class/field identity remains unresolved; no census/full-image
credit is claimed. [Exact scope and provider audit](../reverse/attempt_support/real-link-player-donor-20261103.md).


### Apt name-entry Laser donor references (2026-11-03, halilkkaya-codex)

Base81510a474f: remove four unrowed position/decay/seven-argument-init Laser
methods from AptValueNameEntry. All11 rows and587 common COMDAT fingerprints
remain; three particle/shroud consumer undefineds disappear. Three-source29-row
normal checks, one EXACT EH graph and scoped DIR3229+35 witnesses pass. Both
linking peers stay linked in true A/B; this consumer retains three base-view
unresolveds. Its32B constructor installs native fifteen-slot Apt tableCE8BA0,
so the old DrawableModule/Snapshot constructor context needs complete identity
reconciliation. No whole-image/census credit is claimed. [Proof and boundary](../reverse/attempt_support/real-link-apt-laser-donor-20261103.md).
2026-11-04 claudeb2: Laser port replaced by the 0x006CBCB0 Apt value constructor; link_check predicts LINKS 0->410 B, awaiting census. [Evidence](../reverse/attempt_support/apt-name-entry-ctor-reidentify-20261104.md).


### Vslot AG native FieldParse providers (2026-11-03, halilkkaya-codex)

Base007bf15b24: define the three previously missing tables at VAC74540/C74630/
C74704 under their existing opaque names. Three data rows independently verify
all160B, callbacks, offsets and both complete enum lists; ten code rows remain
exact. Six-source154-row checks and scoped DIR32154+62 pass. True A/B retains
five LINKS peers/9873B and reduces this consumer U7->U4. The two ABI helpers
and two aliases of held47A69C remain open; no helper change or alias was kept.
No global/census closure is claimed. [Tables and remaining contracts](../reverse/attempt_support/real-link-vslot-fieldparse-20261103.md).


### Vslot AG member-call provider (2026-11-03, halilkkaya-codex)

Follow-up to the FieldParse providers: emit the existing opaque member
spelling at 23C7F5 beside its stdcall owner. add_match --icf-owner proves
the whole70B body and relocations, with no unique-byte credit. Both old
COMDAT fingerprints remain identical; no external provider is removed.
Six-source155-row checks and scoped DIR32 pass. True base/tip A/B preserves
five LINKS peers (9,873B), while Vslot AG U4 becomes U3. The two held RET4
helpers and bool/int provider contract remain. No full real-link rerun.
[ABI and verification evidence](../reverse/attempt_support/real-link-mode-helper-20261103.md).


### Real-link Libraries/Common batch handoff (2026-11-03, halilkkaya-codex)

Six implementation commits on c1325ac0b6 retain existing rows and add three
verified FieldParse tables plus one full-body ICF member spelling. Combined
70-unit true base/tip checks preserve all previously linking units (LINKS
29 -> 33; unresolved source/name references 226 -> 176). This is a preview,
not a new real-link measurement or census gain. Seven-source normal checks
pass 42 code rows and four data rows; scoped DIR32 passes 42 rows plus
18 witnesses. Batch audit: INCONCLUSIVE, because index984a4cdc4d predates
the base and seven changed objects lack current strict receipts. Carry the
providers and affected consumers into the next scheduled measurement.

The shader-manager roots remain blocked on ten child lists and thirteen
actual objects. Five initialized homes lack matched data owners; seven more
remain scalar stand-ins. The catalog196B extent does not prove the second
root's size (native40B). Both code rows stay exact, with no source edit.
[Landing order, all44 sources, pointer graph and claims](../reverse/attempt_support/real-link-seat-halilkkaya-codex-20261103.md)
and [original name/provider hints](../reverse/attempt_support/real-link-seat-halilkkaya-codex-20261103.tsv).


### Particle binder constructor views (2026-11-04, halilkkaya-cx-o3)

Base a24836a7f9: `Rva001F4B01Ctor.cpp` declared four invented three-slot
classes (`slot0`, `ResolveBindings`, virtual dtor), so its four vtable
COMDATs named 12 symbols nothing defines (all 12 real-link artifact names of
this unit). Retail's tables have two slots: 0x00BE171C = { 0x001F4B47,
0x001F4A90 } and 0x00BE16E8/F0/F8 = { 0x001F45C3, 0x001F69B1/0x001F73D5/
0x001F7740 }. The unit now compiles the declarations the rowed destructor
0x001F4B01 already compiles (FX binder base, `FXShaderParameterSourceNamespace_Struct`,
nested `ParticleFXShaderParameterSourceNamespace::SourceNamespace_*`), so both
installing units emit one `??_7Rva001F4B01@@6B@`. The 80B ctor stays exact;
true base/tip link_check over 15 consumer/sibling/COMDAT-sharing units: 14 -> 15
LINKS, no LINKS loss, every shared COMDAT copy identical to the census's other
copies. Scoped DIR32 passes. No census/full-image credit is claimed.

Remaining (runtime, not link): slot 1 of 0x00BE171C stays pure in both
installing units, so a linked image carries `__purecall` there instead of
0x001F4A90. 0x001F4A90 is rowed as the nonvirtual
`ParticleFXShaderParameterSourceNamespace::ResolveBindings(const char *, int, int)`.
Reconciling it needs class `Rva001F4B01` renamed to
`ParticleFXShaderParameterSourceNamespace` and 0x001F4A90 respelled
`UAEXPBD0PAVFXShaderParameterBinder@@@Z`. `rename.py class --basis canonical:wb`
refuses: `name_evidence.py` has no wb-assert candidate for the class, and the
wb_name_leads row at 0x001F4A90 still spells the stale placeholder
`Rva001F4A90Host`. The rename needs a naming approval.


### ThingTemplate armor-set donor parsers (2026-11-04, halilkkaya-cx-o3)

Base bdf42addf7 (after cf60dfc838 removed nine other donor methods,
`parseIntList` among them): remove two more unrowed Zero Hour bodies with
present-unmatched markers, `ArmorTemplateSet::parseArmorTemplateSet` and
`ThingTemplate::parseArmorTemplateSet`. Nothing else in the census touches
them. Their `ArmorSetFlags::parseFromINI` use was the unit's only reference to
the static `INI::scanIndexList` spelling and `BitFlags<11>::s_bitNameList`
(BFME 2 rows `INI::scanIndexList` as a member, 0x0002BD39). A member-pointer
compile anchor keeps the rowed `ArmorTemplateSet::clear` (0x006E00A0) emitted.
23/23 rows stay exact. The 50 dropped definitions have no orphaned consumer,
and no undefined name is added. True base/tip link_check over 54 units (Player,
ThingFactory and every census object sharing a dropped COMDAT): no status
change, LINKED unchanged. Scoped DIR32 passes. Two artifact names are resolved.

Kept, and why:
- `parseMaxSimultaneous` stays because the donor `s_objectReskinFieldParseTable`
  (referenced by ThingFactory) names it, so the static `INI::scanInt` stays too.
- The AudioEventRTS ctor, copy ctor and dtor and `setEventName` stay. Rowed
  `pair<AsciiString,AudioEventRTS>` dtor/`_M_insert` bodies are emitted only
  through `parseArbitrarySoundsIntoMap`, and `getPerUnitSound` (3 consumers)
  uses `s_audioEventNoSound`.
- `calcCostToBuild` stays because Player references it, which keeps
  `getProductionCostChangePercent` referenced. These need AudioEventRTS and
  Player identities, not removal.

### Remaining-slice triage (2026-11-04, halilkkaya-cx-o4)

Base 6a193d3101, artifact run 41706953002 (commit 4272054b98, 551
unresolved, not authoritative). Session ended at setup; no source edit.
Current per-unit counts: collect 41, twiddler 10, ThingTemplate 8,
Rva005F422CDtor 9, Rva005BA1FDCtor 7, BfmeConv1292DeferredWalkers 6.
None is a short fix:

- collect.cpp: claim refused, class:RenderObjClass is held through
  class:HLodClass (StarkillerHDX@fleet). ThingTemplate: class:ThingTemplate
  still held by halilkkaya-codex.
- Rva005BA1FDCtor and Rva005F422CDtor: every missing name is an invented
  slot (`BoxVirt`, `BaseVirt`, `M60Virt`/`M6CVirt`, `slot01..07`,
  `DoUpdate`, `CreateMovieClip`, `rva005F4710`). The fix is the cx-o3
  Particle pattern: rebuild each installed table from retail (three per
  AptOnlineOpenPlay/Rva005BA28E object; C73DCC/C73D70/C73D60 for the
  latter) with the rowed slot owners' declarations. Needs the online-screen
  deleting/lifetime hierarchy above.
- StlSweepW6Rva0016DEC0 (1 name, element `operator<`): already blocked as
  LINK-055 (re_attempts: native worker proves `find`, not `lower_bound`).
  The W4/R3 element families still need real element identities (LINK-002).

Collect follow-up (2026-11-03, base `678d949f99`): retired only the unused `CollectionDefClass` constructor and one hatch; five rows and 140 retained COMDATs stay exact, no provider consumer is orphaned, and true base/tip previews retain the same 41 unresolved names/four conflicts. Remaining constructor removal still needs EFB4C/5AD93A ownership reconciliation. [Evidence](../../reverse/attempt_support/collect-def-constructor-cleanup-20261103/README.md).

### ThingFactory.cpp Zero Hour bodies (2026-11-04, halilkkaya-lk22)

Real link 41813987742 (`612abfbebb`): 6 errors.

**Repaired: 4 names, in c6d228e7b7 and f3c6a87591.**

- The unrowed Zero Hour `newObject(const ThingTemplate *, Team *, BitFlags<45>)` is gone. It was the only
  caller of `PartitionManager::registerObject` and the Zero Hour `GameLogic::friend_createObject`. BFME 2's
  `newObject` is the row 0x002D0A23.
- The LOAD_TEST_ASSETS branch of the unrowed `findTemplateInternal` is gone. It called
  `ThingTemplate::initForLTA` and a public `newTemplate`. BFME 2's `newTemplate` is private (0x002D1B2E),
  and its `findTemplate` (0x002D06CA) is a bare hash find with no test-asset path.
- `findTemplateInternal` stays, because the Zero Hour ports in ScoreKeeper and AssistedTargetingUpdate
  still call it.
- Checks:
  - ScoreKeeper, TeamGetControllingPlayer, AssistedTargetingUpdate and stlport_hashtable_asciistring
    stay LINKS.
  - The orphan scan finds 0 orphans.

**Remaining: 2 names. Both rows link only through pins.**

- `DynamicAudioEventRTS::operator=` (0x00200BC0) copies +4 by calling 0x000366F0, the exported
  `StringBase<char>::set`. In BFME 2, the AudioEventRTS assignment at that point is therefore one inlined
  string set. The pin `??4AudioEventRTS` onto 0x366F0 provides no definition.
- `ProductionPrerequisite::operator=` (0x0042816E) copies +0 and +0xC through 0x000120C0. That address is
  the 41-byte `basic_string<char>` `operator=`, which is not a vector assignment.
- Both need the unit's `AudioEventRTS` and `ProductionPrerequisite` member views corrected. Those
  classes are shared with the rest of this unit's Zero Hour ThingTemplate code.

**Resolved in the working tree (2026-11-04, claudeb), commit 0552b49319:** both bodies moved to their approved
units, `DynamicAudioEventRTS::operator=` into INIWater.cpp and `ProductionPrerequisite::operator=` into
VersionBlockParser.cpp, and ThingFactory.cpp's two anchors dropped. ThingFactory.obj now leaves only
`InterlockedIncrement` and `AsciiString::releaseBuffer` undefined. link_check: ThingFactory 0 -> 60 B LINKS;
VersionBlockParser LINKS. The next real link should confirm this.

- 2026-11-04: the 0x0051F7AD caller now lives in AptTimeLine.cpp after a verified TU merge; its assignment uses real STLport vector, retaining the bounded external allocation specialization. PerTurnStats caller/header reconciliation is still required. [Updated caller scope and checks](../../reverse/attempt_support/apt-timeline-vector-reconcile-20261104.md).
