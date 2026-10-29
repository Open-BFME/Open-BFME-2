# Fill helper STLport 4.6 migration

Base: `6a36399b76`, 2026-10-29. Scope:
`Code/GameEngine/Source/Common/Rva00577CA0Fill.cpp`, RVA `0x00577CA0` (37 bytes).

The default picker served this whole-file STLport trial. Replace its private
`_STL::__false_type` with the declaration from STLport 4.6's `stl/type_traits.h`,
using the library's prolog/epilog and the supported `// stlport46` opt-in.
The function body, caller/callee identities and source path remain unchanged.
Repoint the sole ledger row with `add_match.py --replace-existing` and the
`migrated=stlport-4.6` note. This removes a private library tag declaration;
it does not recover the unresolved owning-reference type or function name.

Verification:

- Before and after `./build.sh` pass the sole 37-byte row and reference checks.
- `find_declared_unmatched.py` passes before and after.
- `link_census.object_facts` agrees exactly between the saved pre-edit object
  and the verified migrated object: one COMDAT fingerprint, one exclusive
  definition, one undefined external and no weak externals.
- `link_check.py --prepare-current` produces a strict reusable byte receipt.
- Ordinary link preview preserves LINKS, 37 -> 37 authored bytes, against
  index `85f6b7f40c` (2026-10-29 15:08).
- The owning `repair_queue.stlport_items()` no longer serves this source.
- The staged batch audit is INCONCLUSIVE: the index predates the base, and
  `Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current
  affected-consumer receipt. Carry that consumer and this provider into the
  next scheduled census; no consumer-wide closure or census gain is claimed.

No source move, new pin, escape hatch or debt-register change.
