# AptMyHero item008: window and transition caller adoption

**Two source-only prerequisites are ready for Root's normal admission.**
Basis: f22af79cdcbe2f6beadc10fe9142d5c8f5c8300f. The approved whole-TU
consolidation remains open; no completed queue item, removed donor, new exact
byte, new link measurement or runtime improvement is claimed here.

## Apply

Use **combined.patch**, SHA-256
`c203d5d413067a25d91c890e3f20642d407420aa8a8e721732d705e9bda475a6`.
The two final complete sources are `AptMyHero.combined.cpp.txt` and
`AptMyHero_Unresolved.combined.cpp.txt`. Manifest hashes are in
windows-final-inputs.json; every source artifact uses literal LF.

Only the existing two source files change. No header, flag, macro, contract,
alias, pin, pragma, tool or register edit is proposed. Root owns source claims
and has separately reserved class:GameWindowManager and
class:GameWindowTransitionsHandler.

For separate commits instead, apply window-manager.patch first and
transitions-after-window.patch second. The latter is deliberately based on
the first patch's output. transitions.patch is an independent original-basis
control, not the sequential second patch. windows-native-facts.json records
the original, intermediate and combined source hashes.

## Behavior and independently established bindings

1. Replace both private GameWindowManager declarations with the existing
   GameClient/GameWindowManager.h. The old `TheWindowManager->slot28()` uses
   byte offset0x28, virtual slot10, **update()**. It becomes that already
   declared canonical method. The existing full canonical view is64 bytes,
   SubsystemInterface at+0, with the proven fourteen-slot base prefix.
2. Replace both private GameWindowTransitionsHandler declarations with its
   existing shared, deliberately opaque/method-only header. Its nonvirtual
   calls retain the same public declarations. The old slot24 call uses byte
   offset0x24, virtual slot9, **reset()**. Dispatch that one call through
   `reinterpret_cast<SubsystemInterface *>(TheTransitionHandler)->reset()`.
   Include the actual existing shared SubsystemInterface header explicitly.
   Its fourteen-slot form was already active through CreateAHeroManager;
   this change defines no selecting macro or replacement header.

The latter is an observed base-prefix conversion. It does **not** add a full
108-byte GameWindowTransitionsHandler declaration or pretend that its current
opaque canonical header fully reconstructs the target hierarchy.

### Transition base0 and real reset slot

- Retail constructor RVA0x001DCBC3, complete124 bytes, keeps the receiver in
  ESI and calls SubsystemInterface's0x001B4E63 at0x001DCBD7 on the unchanged
  ECX receiver. It installs VA0x00BDBC30 at0x001DCBE4. Native lifetime-source
  CodeView independently reports sizeof108 and SubsystemInterface at+0.
- The allocation/factory at GameWindowManager::init (row0x002C0A0F,77B)
  allocates0x6C, calls this constructor, stores TheTransitionHandler at
  VA0x00DFDC14, then loads/initializes it. Teardown clears this same pointer.
- Direct retail table read at RVA0x007DBC30 gives14 code entries. Entry9 is
  VA0x005DBE6E, the already rowed **72-byte** virtual
  GameWindowTransitionsHandler::reset atRVA0x001DBE6E in
  Code/GameEngine/Source/GameClient/GUI/GameWindowTransitions.cpp.
- That body releases current/pending/secondary/draw groups and clears+0x69;
  its no-argument void thiscall/RET0 ABI matches the actual shared base reset
  dispatch. No method name was guessed from byte similarity.
- The sole data-ledger owner of TheTransitionHandler is
  Code/GameEngine/Source/Main/WinMain.cpp, shared class-pointer global at
  RVA0x009FDC14. Its initial retail word iszero. This change neither declares
  a second data owner nor adds an address alias.

### Window manager update slot

- Base constructorRVA0x002C5334 is a matched100-byte row under its retained
  address-derived owner Rva002C5398. It calls SubsystemInterface's constructor
  at0x002C5347 on the unchanged receiver, then installsVA0x00BFF658.
  Native base-source CodeView reports64 bytes and base+0.
- The matched18-byte derived constructor0x0008FC51 calls it and installs
  VA0x00BC7C90. The actual factory allocates0x40 bytes.
- Both original base/device tables, RVAs0x007FF658 and0x007C7C90, hold
  VA0x006C0A74 at entry10. It is the already rowed **21-byte** virtual
  GameWindowManager::update, RVA0x002C0A74, in GameWindowManagerModal.cpp:
  processDestroyList followed by a tail dispatch of the transition update.
- The existing shared GameWindowManager header declares this override with
  the correct no-argument void thiscall ABI. The sole data-ledger owner of
  TheWindowManager is GameClient/GUI/GameWindowManager.cpp atRVA0x009FEF1C.
  Its initial retail word iszero.

Complete PE words, constructor disassemblies, provider rows/paths and global
bindings are retained in **windows-native-facts.json**.

## Private verification

**windows-probe.json** separately checks the unchanged controls, each individual
adoption and the combined source. All three candidates retain **43/43 +16/16**
rows, **5,218 existing bytes**, unmasked, zero unresolved references. Native
Verifier code/managed flags are unchanged; only temporary inputs, objects and
layout caches were redirected to explicit private build paths. BFME_OBJSTORE
was off. No shared match object, link index, production file or claim changed.

**windows-full-audit.json**, for every individual and combined candidate:

| Actual COFF property | Seed | Destructor file |
|---|---:|---:|
| Strong external code bodies, raw bytes + full named relocations identical |58/58|13/13|
| Public/weak records and actual DEFAULT identities identical |143/143|70/70|
| Physically identical linkable code/data section graph |142/142|38/38|
| COMDAT selections and associative section bindings |unchanged|unchanged|
| Native source definition inventory |unchanged|unchanged|

Only diagnostic debug sections are excluded from the physical graph. Local EH
label spellings are compared by their actual section/value/storage bindings;
public and weak names are never elided. This is supporting evidence, not an
alternative admission gate. All actual virtual-call bytes and global relocations
are preserved, including AptMyHero::rva005B21DA and FrameUpdate; the actual
AptMyHero vtable is unchanged as part of the same data graph.

## Existing full-family limitations, explicitly retained

Native CodeView was read for the original transition lifetime, reset, factory,
window base lifetime and window update units, not just the two caller bodies.
Their existing private views disagree with each other and with target slots:

- Transition lifetime view:108 bytes, SubsystemInterface+0, but its short base
  context exposes only the destructor slot.
- Factory view:108 bytes, base+0, with its own short-context init/reset/update
  numbering. The reset provider itself uses a baseless108-byte partial view
  whose local compiler slot numbers are0/1/2, not the original table's9/12/10.
- Window update provider uses a44-byte field prefix and placeholders, whereas
  the actual base lifetime and current shared header establish64 bytes.

These are pre-existing declaration/table debts. Neither those source files nor
their vtable providers change here. Their incomplete CV slots are not taken as
retail truth; the real PE table, complete existing body and constructor/base
evidence bind the caller dispatch. The canonical transition header remains an
opaque interface. This package claims neither full108-byte class reconstruction
nor convergence of all declarations or retirement of any real-link bridge.

## Root's normal next steps

Apply combined.patch, `./build.sh` both full files, then run ordinary
header_adopt_lane.py accept separately for GameWindowManager and
GameWindowTransitionsHandler on both sources. Native acceptance owns the four
header queue keys. Run find_declared_unmatched.py, commit verified source work,
and run the actual tu_skeleton whole-TU merge dry-run against the new inputs.
No regenerated tu_map.csv, hand-moved row or intermediate completed-TU credit.

Root admission: GameWindowManager passed the ordinary two-source build and native header-adoption acceptance. This is a retained-byte prerequisite, with zero completed whole-TU item credit.
