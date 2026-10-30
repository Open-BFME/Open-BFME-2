# Buddy constructor native string cleanup binding

Inspected base `2ea103ccc1`; provider index `ccafe54d1d` (2026-10-30 15:43).
The constructor unit's sole preview blocker is a const narrow-allocator copy
backed by the stock node allocator. Unlike the earlier downloader copies,
this allocator chain has live callers. Replacing it with raw free would change
the allocator operation and is not the repair.

Retail's five constructor string-cleanup funclets at `79894E`, `798959`,
`798964`, `79896F` and `79897D` all jump to the existing 14-byte narrow-string
destructor at `142D70`. Add only its declaration-only specialization beside
the existing string-constructor specialization. This binds the native cleanup
calls to the already rowed owner and avoids instantiating eleven incompatible
or unnecessary local lifetime helpers. The same declaration is already used
by the sibling Buddy connection callback. No Buddy destructor declaration,
class rename, row, pin, alias, hatch, header or compiler-setting change.

Private before/after objects pass all ten owned rows and the native constructor
EH graph. All retained external raw bodies are identical. Only five symbolic
relocations in the pre-existing implicit Buddy destructor change from
`_M_deallocate_block` to the string destructor; both existing bindings include
native `142D70`. All other retained symbolic relocations are unchanged. The
implicit Buddy body remains an unrowed 140-byte view, distinct from the
170-byte native body rowed as `Rva0055133F`. No exact-match, identity repair or
new admission is claimed for that pre-existing implicit body.

All globally referenced removed helper names retain their previous selected
providers. Both the first selected string-destructor provider
`stlport_locale_global.cpp` and the rowed owner
`stlport_narrow_num_get_double.cpp` independently reproduce all 14 native bytes.
The actual strict constructor object reproduces the private candidate.
[Native targets, object changes and provider selection](proof.json).

Literal build.sh, frozen checks and strict three-source preparation pass
27/27 rows, one data row and one named import. All seven cohort EH graphs
are EXACT. The ordinary preview retains 3/3 LINKS, 1,607 -> 1,837 authored
bytes: constructor 0 -> 230, both existing providers unchanged. This is a
bounded link prediction, not additional native coverage or a new census.
Full affected-consumer selection/loss checks and scheduled census confirmation
remain separate. The Buddy complete/deleting-destructor identities and wider
class-consolidation prerequisites remain open.

Ready-batch audit: INCONCLUSIVE on older `ccafe54d1d` versus outgoing base
`2ea103ccc1` and the missing current CreateAHeroManager consumer receipt.
Carry all removed helpers, lifetime rebindings and affected consumers into
the next scheduled census; no full-image selection/loss clearance is claimed.
