# BridgeBehavior pool-head link repair, 2026-11-04

Inspected source revision: `9b8a497ccb` (upstream base `3973f27370`).

The real-link picker still lists `?g_freeList@@3PAXA` for
`Code/GameEngine/Source/GameLogic/Object/Behavior/BridgeBehavior.cpp`.
Provider repair `b83078ec2e` removed the separate head datum and gave
`g_freelistPool` its complete 24-byte storage at VA 0x00DA60E8. Its head is
at +8 (VA 0x00DA60F0). The existing pool reset/deallocator consumers already
access that field. The bridge shim retained the old standalone declaration.

The shim allocator now reads and writes +8 of the existing pool, using a local
reference named `freeHead`. No new global, alias, pin or ledger row is added.
The shim's sole consumer in current cached compiler dependency receipts is
BridgeBehavior.cpp; the other sources including a BridgeBehavior header use
other include paths. The commit hook must also judge the dependency closure.
No naming proposal is needed for this clear new local.

Verification:

- `./build.sh Code/GameEngine/Source/GameLogic/Object/Behavior/BridgeBehavior.cpp`:
  51/51 rows matched; 5 string literals and 4 empty-string references, 9 float
  literals and 3 imports verified. Existing renamed funclet labels verified.
- `find_declared_unmatched.py` passes for the source and shim after the edit.
- `link_check.py Code/GameEngine/Source/GameLogic/Object/Behavior/BridgeBehavior.cpp`:
  LINKS, 4,673 -> 4,673 authored bytes, against the index dated
  2026-11-04 17:56 at `8c757ea0db` (census 16:16 at `2f0cb97f52`).
- Read the rebuilt object's COFF external symbols through the existing parser:
  `?g_freeList@@3PAXA` is absent; `?g_freelistPool@@3VFreelistPool@@A` is present.
- Whitespace checked with `core.whitespace=cr-at-eol`, preserving the shim's
  existing CRLF convention.

This clears the stale standalone-head reference in this consumer. No new
census bytes are claimed: the published index already counts this unit linked.
The next official real link must confirm removal of the old artifact blocker;
no runtime or smoke run was started.
