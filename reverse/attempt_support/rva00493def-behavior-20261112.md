# Special-power destructor Behavior base

Inspected 2026-11-12 at 93f9903fe4e. Scope:
Rva00493DEFDerived.cpp, StopSpecialPowerCtor.cpp and
Update/SupplyTruckAIUpdateCtor.cpp (the HordeDispatch constructor).

## Native evidence and repair

The three matched destructors restore vptrs at +0, +0x0C and +0x10 and
tail-call the existing 0x00493DEF destructor. The +0x0C table at RVA
0x007EFCF8 has 47 entries: 42 point to the three-byte zero-return body
0x000D43D0; slots 8, 43 and 44 point to 0x002533D3, 0x00251C11 and
0x00251C24; slots 45 and 46 point to the three-byte ret-4 body 0x0047A69C.
It is not a table of pure calls.

Make the existing opaque Rva00493DEF view inherit canonical BehaviorModule.
That header supplies the ObjectModule core and its +0x0C interface, so the
old eight-byte pad and extra MiBase1 base are removed. The remaining +0x10
interface stays explicitly incomplete. This recovers existing canonical
defaults without asserting a complete SpecialPowerModule or donor identity.

The compiler now qualifies the three primary tables with ObjectModule and
leaves the tertiary table names unqualified. Two constructors are the only
indexed external consumers of the old names. Rebind their hard externs to
the actual emitted replacements, with no added linker alias:

- Stop primary: VA 0x00C5DE6C, ObjectModule-qualified name.
- Stop tertiary: VA 0x00C5DE08, unqualified Rva004C67A0 table name.
- HordeDispatch tertiary: VA 0x00C5E828, unqualified Rva004C8A16 table name.

Native DIR32 sites establish these addresses with zero addends. All source
paths and ledger rows remain in place. The four existing f2 alternatenames
remain: the CashHack one still serves its split TU and is not dead.

## Checks and remaining work

- Private controls preserve all six destructor/deleting-destructor rows.
  The normal three-source build passes all eight rows; strict reusable
  compiler receipts were prepared for all three sources afterward.
- Current link_check against census 2026-11-12 17:55 at 9ca25659d0 reads
  LINKS for all three: 159 -> 159, 46 -> 46 and 42 -> 42 bytes.
- Each of the three 188-byte Behavior tables now has 44 of 47 native slot
  bodies correct. Only slots 8, 43 and 44 differ. This is a bounded source
  check, not proof of winning selections or a linked image.
- Independent source/object/index review finds no remaining external
  consumer of a removed table name after the two constructor changes.
  Active source, data-owner, pin, tool, hook and workflow searches find no
  additional consumer requiring migration.
- An initial abstract-BehaviorModuleInterface trial preserved the six code
  rows but emitted 47 pure calls. It was restored, not banked as source.

The family-specific getSpecialPower and slots 43/44 remain. In particular,
retail's 0x00251C11 forwards a float, whereas canonical slot43 still takes
int; LINK-514 records the prerequisite signature repair before moving that
method's ownership. Primary and SpecialPower-interface slot recovery and
the existing split/fold prerequisites also remain. All nine served table
repairs remain open; published real-link confirmation is not claimed.

MiBase1's existing header-queue entry remains unchanged. Its owning accept
command refuses a source that no longer includes MiBase1.h, even though the
old type is gone. The rejection is recorded for the tooling lane; no unused
include or manual queue deletion is used to satisfy it.

## Publication carry-forward

The preceding page batch bc3ca393782/93f9903fe4e passed its hooks and both
own link previews. Its broad audit was INCONCLUSIVE against index 9ca25659d0
and outgoing base 1b5be3fe20d: Disp8ByteOneSetters.cpp lacked a strict receipt
after its comment-only source edit. Its shadow replay check also judged the
two ledger commits through the net outgoing diff only. Carry these limits
into the next census. They are not a game-run result.
