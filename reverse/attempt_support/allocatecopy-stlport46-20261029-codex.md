# Allocation helper STLport 4.6 migration

Base: `a1d5808a6c`, 2026-10-29. Claimed source:
`Code/GameEngine/Source/Common/Rva00568D68AllocateCopy.cpp`,
RVA `0x00568D68`, 45 bytes.

The default picker served the whole-file STLport migration. The source now
opts into STLport 4.6 and takes `__false_type` from its type_traits header,
through the library prolog/epilog. The private tag declaration is removed.
The allocator/vector views and existing owner identities remain prerequisites
for fuller source recovery; this change does not establish their native names.
The allocator's existing const signature is retained because it binds the
existing BfmeE12 provider; no new signature or pin is introduced.

The first trial passed a value-initialized library tag. VC7.1 then emitted
an extra EDI save and zeroing store, failing the 45-byte row. Default-initializing
a local empty tag preserves retail's code shape without a private constructor.
Only the verified latter change is retained.

Verification:

- Before/after `./build.sh` passes 1/1 function rows and all reference checks.
- `find_declared_unmatched.py` passes before/after.
- `add_match.py --replace-existing` re-verifies the row and adds its
  `migrated=stlport-4.6` note; `repair_queue.stlport_items()` no longer serves it.
- Saved pre-edit/current COFF facts retain the helper COMDAT fingerprint
  `0241d1ba463c` (45 bytes), both undefined externals, and no exclusive or weak
  definitions. The sole removed COMDAT is the private three-byte
  `??0__false_type@_STL@@QAE@XZ` constructor (`03ca90960a9c`). Index
  `85f6b7f40c` has 50 identical copies and no reference to that constructor;
  this is index evidence, not a current whole-tree consumer proof.
- `link_check.py --prepare-current` produces a strict reusable receipt.
- Ordinary preview retains LINKS, 45 -> 45 authored bytes, against index
  `85f6b7f40c` (2026-10-29 15:08).
- The staged-tree outgoing batch audit is INCONCLUSIVE: the index predates
  the base and affected consumer
  `Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current
  receipt. Carry that consumer and the changed provider into the next
  scheduled census. No census gain or consumer-wide clearance is claimed.

No source path move, new hatch or debt-register change.
