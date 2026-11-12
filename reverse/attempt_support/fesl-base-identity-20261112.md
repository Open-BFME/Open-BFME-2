# FESL factory destructor: use the existing base owner

Base: `4671394f636`, 2026-11-12. Served code-identity item:
`Code/GameEngine/Source/GameNetwork/Rva00803890FeslDtor.cpp`,
`??1Rva00803890Owner@@UAE@XZ`, target RVA `0x0066F8D0`, 96 bytes.

## Target evidence and change

Retail calls the seven-byte destructor at `0x00666BA0`, already rowed as
`??1Rva00666BA0@@UAE@XZ` in `DirtySock/Rva00666BA0Dtor.cpp`. The old local
`Rva00803890Base` destructor emitted different code under a pin to that address.
Use the existing out-of-line owner through a destructor-only declaration view;
remove the unused old definition, its `present-unmatched` marker and its pin.
There are no remaining `Rva00803890Base` references under `Code/`.

Declare `Rva00803890SecondaryFinalVTableAnchor` with the existing definition's
type: external C linkage, an array of four constant pointers. Its constructor
owner and four relocated slots remain unchanged. The source comment now
separates the BFME II target address from the BFME I source lead; donor names
and paths do not establish the target class's identity.

## Verification

- Private before/after proof verifies the complete 96-byte row. Three retained
  COMDATs, no additions; only the destructor's callee relocation changes.
  The obsolete base destructor, deleting destructor and table disappear.
- The primary factory table retains its four bytes and identical relocation.
  This does not repair its short extent or recover the full class interface.
- Normal `./build.sh` verifies both source files: 2/2 rows, 103 bytes, with
  string, float and import checks passing. Frozen-file check is clear.
- `repair_queue.py retire identity` passes on the root checkout's complete
  ledger-object set and removes exactly this source's one key. The temporary
  worktree's first attempt refused for missing objects and changed no register.
- `hatch_counters.py --update` removes one pin occurrence and one
  `present_unmatched` occurrence. Pin consistency passes with no new finding.
- `link_check.py --prepare-current` byte-verifies both explicit providers with
  strict reusable receipts. Their own previews preserve LINKS, 96 and 7 bytes,
  against index `aa7acf764d`, dated 2026-11-12 19:19. The index warns of four
  unrelated source-path changes since its snapshot; this is a scoped preview,
  not an actual image or a current full census.
- An independent bounded read-only review found no blocking issue in this
  callee/unused-pin/declaration scope. Full class reconciliation remains open.

## Remaining work

The factory's native primary table at RVA `0x008E3F18` has four slots; this TU
still emits one. Reconcile the constructor, destructor, dispatch and scalar
deleting-destructor views before claiming full interface or table recovery.
The base's three pure slots in its owning TU do not establish the derived
methods' signatures. No new fold row, pin, alias, private virtual method or
table expansion is admitted here. Confirm the repaired callee in the next
normal census and real image; no game-running or bridge reduction is claimed.
