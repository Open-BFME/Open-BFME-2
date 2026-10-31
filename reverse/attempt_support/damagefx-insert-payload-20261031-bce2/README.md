# Opaque insertion payload extent and remaining resize blocker

Base: `e847af92bf6226209bc09dc0392d53229bacbafc`. The picker served the
existing 73-byte insertion at `0x003609F7..0x00360A40` in
`StlSweepW4Rva003609F7.cpp`. This is a layout prerequisite, not a new match,
an application-type rename or a claim that the unit now links.

## Target evidence and retained change

Native insertion calls resize `0x0053F1EC` (184 bytes) and node creation
`0x00360939..0x00360961` (40 bytes). The latter allocates `0x788` bytes:
four-byte next pointer, four-byte key and `0x780` mapped bytes. Its copy
leaf at `0x00360917` is 34 bytes, with no relocations. Existing rowed
DamageFX node/copy providers and DamageFXHashSubscript independently expose
the same extent and 480-dword mapped copy. Those are target-image facts;
they do not settle every application field, hash/key identity or TU placement.

Change only `Rva003609F7Element::bytes[1]` to `bytes[0x780]`. Retain the
opaque name and all existing declarations, flags and caller spellings.
The old helper allocated `0x0C`; the corrected helper allocates `0x788`.
Do not extend DamageFXHashSubscript's existing container/pair reinterpretation.
No ledger row, pin, alias, hatch, shared header or source path changes.

## Verification and limits

- The complete 73-byte insertion COMDAT, relocations and both direct target
  identities are unchanged. Its digest remains `76aaa121f433`.
- The emitted node is now exactly the native 40-byte body after masking its
  two REL32 slots. Its digest is `dcaf91424c90`; the targets are the existing
  raw allocator at `0x000307F0` and the exact 34-byte copy leaf at `0x00360917`.
  The copy leaf compares unmasked, with no relocations.
- Four external copies change: node, copy leaf, pair copy constructor and
  typed node allocator. No copies are added or removed; strong, undefined
  and weak symbol sets are identical. The pair constructor has no incoming
  code edge in this object. The typed allocator has an incoming alloc_proxy
  wrapper; its closed incoming component is not reached from the matched
  insertion or node. This is object-local evidence, not global consumer closure.
- Normal build passes 1/1 rows. Strict preparation passes 16/16 rows across
  this fragment, DamageFX_hashtableNewNode.cpp, DamageFX_pairConstruct.cpp
  and DamageFXHashSubscript.cpp. Frozen-file checks pass; EH is EXACT 1.
- Ordinary preview at census `12902e9e1b` (2026-10-31 23:18) reduces this
  fragment's losing/selected-wrong helpers from L2/S2 to L1/S1. It still
  does not link. The three existing provider/caller units retain LINKS and
  their census 326 + 64 + 175 = 565 authored bytes. No census gain is claimed.
- Name-based binding qualification still reports node `wrong/unknown` for
  the opaque spelling; the direct native body graph proof does not retire
  an identity key or authorize a new alias.
- The staged-tree batch audit is INCONCLUSIVE: its index predates the base,
  and affected consumer `Code/GameEngine/Source/Common/AIGameTeam.cpp` lacks
  a current receipt. Carry that consumer and this cohort into the next
  scheduled census. Whole-image selected-provider safety remains unverified.

## Rejected resize experiments and next work

The original resize is 220 bytes (`1ca0775fa5fa`), versus native 184.
Removing declaration-only trivial destructors produced 211 bytes; adding
the primitive-vector swap's nonthrowing declaration produced 191. Reversing
the indexing operand order did not improve it. These are rejected compiler
profile experiments, not recovered bodies. Every such edit is reverted:
the original resize's full byte/relocation digest is restored. The archived
`resize-191-rejected.patch` records the rejected edits for comparison only;
do not apply them as recovered code.

Next: reconcile actual NameKeyType/DamageFX names and native resize codegen
coherently with existing owners, without new pins or container casts.
The resize body and its ABI/compiler profile remain the link blocker.
Neither this bounded layout fix nor its local preview closes the broader
opaque-STL obstacle or the game's exit test.

Receipts are adjacent. `prove_extent.py` rechecks the normal build object
against retail and the archived before-facts; run from the repository root
with the usual session environment after a normal build. It does not compile.
