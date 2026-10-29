# MultiplayerSettings: native virtual lifetime and remaining integration

## 1. Scope and inputs

This change repairs `MultiplayerSettingsCtor.cpp` in place. It supplies the
native virtual destructor machinery through ordinary compiler emission, while
preserving the constructor's existing row and all six teardown/EH row owners.
It does not complete their ABI-ledger transition or TU consolidation.

The initial investigation used BFME 2 `7bce474fdfba292c1dbffaf187708316ff594550`;
the final source proof ran on `d4cc5cd822993d0d34a925a75d876997ea6ab1bf` plus
this patch. The relevant source and tool inputs did not change between them.
The native-layout prerequisite from PR #127 is already in the base.

- Retail `game.dat` SHA-256:
  `f008b587570bad693981dc7218588c81d192a1e064b0f7f861539c51156a7640`.
- Constructor source SHA-256:
  `b6c811552759215fc5bd6331abd30e0fc010195ce4202c8d1f5566bf7d410046`.
- Checked production object SHA-256:
  `8884976ea69dccae20b450e1a57240b9ad5f1e9888cde89064b700148c149ffb`.
- BFME 1 inputs remain at the repository's accepted `0424131c818fba6641613ef826222ecf30845025`.
  These claims use the target image and current compiler output, not donor names.

## 2. What was wrong

The old constructor used an empty, non-virtual private `SubsystemInterface`
view, explicit padding and a manually stored `g_00C191B8` pointer. It requested
`??1SubsystemInterface@@QAE@XZ`, although the real base destructor is virtual.
The current complete/deleting destructor ledger rows also spell non-virtual
`QAE` identities. Their explanation incorrectly says no vtable references the
deleting destructor.

Retail disproves that inference: constructor RVA `0x003811D8` installs table
RVA `0x008191B8`; its first entry is deleting destructor `0x00381277`, which
calls complete destructor `0x00381293`. `SubsystemSlot<MultiplayerSettings>` at
`0x00226CEB` deletes the object through slot zero (`call [eax]`). The complete
destructor's lack of a derived-vptr store does **not** make it non-virtual.

The table contains fourteen pointers, exactly 56 bytes, followed by UTF-16
data. Its native entries, as RVAs, are:

```text
381277 B3FD0 1B5384 B3FD0 5CB9FF 47A699 D43D0
47A69C B3FD0 B3FD0 B3FD0 5CB9FF B3FD0 47A69C
```

## 3. Implemented repair and exact evidence

The constructor now uses the same native declaration as the approved seed:
the existing fourteen-slot base shim, a real 0x0C map at `+0x34`, two full
0x40-byte colors at `+0x44/+0x84`, and a 0xC4 complete object. Declaration-only
map-constructor/tree-destructor specializations retain existing providers at
`0x003811A2` and `0x0038103F`. The member at `+0x10` remains unknown and receives
10000; the actual countdown at `+0x14` receives zero. Compiler flags are unchanged.

Ordinary construction emits the implicit virtual destructor and its deleting
wrapper. An explicit empty virtual destructor instead emits 89 bytes: an extra
six-byte vptr store starts at offset `+0x11`; retail is 83 bytes. That variant
was rejected. No emission helper, source alias, new pin or counted hatch is used.
The table's compiler-generated weak external `??_E -> ??_G` is ordinary COFF
metadata, not a source-added alias.

The current constructor object proves the following existing native extents:

| Body | RVA | Bytes |
|---|---|---:|
| Constructor | `0x003811D8` | 159 |
| Scalar deleting destructor | `0x00381277` | 28 |
| Complete destructor | `0x00381293` | 83 |
| EH handler | `0x0077F326` | 10 |
| Base cleanup | `0x0077F308` | 8 |
| Map cleanup | `0x0077F310` | 11 |
| Color cleanup | `0x0077F31B` | 11 |

All 310 bytes, the complete 56-byte table and its relocations agree with retail.
Both parent EH graphs are exact and share native FuncInfo `0x00929958`.
The three cleanup targets resolve to `0x001B4E74`, `0x0038119D` and
`0x0048BA39`, respectively. Their local labels come from the actual verified
parent graph; numeric `$L` labels are not portable ownership evidence.
These are emitted-body proofs, **not seven new or moved rows**.

## 4. Linking and provider limits

Against published index `d92e7e6635` (2026-10-28 15:58), the ordinary constructor
preview changes from blocked to **LINKS / 159 bytes**. Both unresolved names
disappear: `??1SubsystemInterface@@QAE@XZ` and `?g_00C191B8@@3QBQBXB`.

A paired old/current constructor overlay at its index position reports zero
removed definitions, new outside COMDAT losses, wrong-selected providers,
new variants, duplicate definitions or remaining unresolved names. Six holders
change from absent to newly supplied: the native complete/deleting destructors,
vtable and empty `init/reset/update` methods. No earlier holder is displaced.
Outside providers remain the published-index snapshot; this is not a fresh
whole-ledger census or an exhaustive current-object proof.

## 5. Stock merge results and next steps

The scoped consolidation planner completed before and after the source edit.
The stock merger rebuilt the stale committed TU map in memory and ran:

```text
python tools/tu_skeleton.py --merge Code/GameEngine/Source/Common/MultiplayerSettings.cpp --dry-run
approved: 43
accepted: []
blocked: no verified merge of two or more donors
exit: 2
```

The constructor and deleting-destructor donors report `no baseline match`
under the carried seed environment. The complete-destructor donor loses three
rows under the carried `-G7 -arch:SSE` override. The report also retains the
existing `SubsystemInterface` header-adoption prerequisite. Three mixed donors
stay outside the merge. This is a real baseline/compile-environment refusal;
it is not a demonstrated commit or PR rejection. That trial applied no merge.

**Flag-default follow-up (2026-10-29, base `b31de0a2`):** isolated
`flag_defaults generate` scans of the seed under `current` and `default`
both compile and preserve its two rows. The exception's `-G7 -arch:SSE`
retained the compiler's initial `/O2`; the region default is
`-O1 -arch:SSE -G7`. Its recorded three-row/two-loss requirement is obsolete
after the native seed reconciliation. `flag_defaults propose` therefore
removes this one override through the supported retirement path.

No source or row identity changes accompany that retirement. The ordinary
seed build passes 2/2 code rows and its singleton data row. All 22 emitted
COMDAT bodies and relocations are identical between current/default/production
objects; both full INI tables (112 and 192 bytes, 34 relocations) are unchanged.
The paired published-index provider check reports no removed definitions,
selection changes, new losses or new variants. Ordinary preview keeps the
seed LINKS/97 bytes and the constructor LINKS/159 bytes against `d92e7e6635`.
This retires one obsolete override; it does not establish a new census result
or approve a merge by itself.

**Stock consolidation follow-up (2026-10-29, after `4a200354`):** the refreshed
planner and stock dry-run now accept the seed, `MultiplayerColorDefinitionCtor.cpp`
and `MultiplayerColorDefinitionCopy.cpp`. The stock apply preserves all 11 rows
(486 bytes), moves nine row owners and removes two source files. The ordinary
build passes 11/11 code rows and the singleton data row; both parent EH graphs
are EXACT, and declaration, class, ledger and scoped data checks pass. The stock
link guard preserves the absorbed donors against the published index.
The upstream `477e2a0887` placement rule independently keeps the copy constructor
approved by `C=0x00380C4E..0x00380D7F`, after removing its old Z/S/N evidence.
All seven lifetime rows, their three source files and the native constructor
proof remain unchanged. The lifetime donors still fail composition; no ABI
transition, header-debt retirement or census gain is claimed.

The remaining sequence is:

1. Reconcile the remaining rejected lifetime donors before further consolidation.
   Keep the existing header-adoption debt unless its normal acceptance passes;
   the updated tool still requires the registered canonical header or an
   explicitly listed companion, which the full subsystem shim is not.
2. Correct the complete/deleting destructor and handler identities from `QAE`
   to `UAE`, retaining their existing RVAs/extents, old-identity tombstones,
   consistent consumers and all three cleanup `parent=` notes. This corrects
   the existing ABI; it does not establish a new canonical class name.
3. Transfer the existing rows through a supported verified operation into the
   current approved `MultiplayerSettings.cpp` TU. Preserve the recently rehomed
   base cleanup `0x0077F308` as well as the other two cleanups. Do not manually
   merge donors or copy stale local labels.
4. Verify the composed TU, protected-register ownership and affected consumers,
   then obtain normal outgoing checks and a later census result.

## 6. Reproduction and review

From the repository root, with the normal project Python environment:

```text
python reverse/attempt_support/multiplayer-settings-lifetime-20261029/reproduce.py
```

The script checks the target image hash, invokes the ordinary `tools/build.py`
CLI used by `build.sh`, records source/object hashes, then verifies native bodies, table and relocations,
both EH graphs, all three cleanups and the handler. It rejects nonzero addends
where its manual relocation checks require zero. The proof report is written
to `build/scratch/multiplayer-settings-lifetime-20261029/proof.json`; the
ordinary build may refresh its normal object/dependency cache. No source,
ledger, pin or register is admitted by this script.

The final reproduction passed on the current production object without
recompilation. Normal declaration/class/EH/data checks passed. A separate clean
review session independently checked the retail dispatch, all seven bodies,
fourteen table slots, EH relationships and provider-change interpretation.
The later stock color-definition merge removes two source files. No full-game
link, census gain or runtime test is claimed.
