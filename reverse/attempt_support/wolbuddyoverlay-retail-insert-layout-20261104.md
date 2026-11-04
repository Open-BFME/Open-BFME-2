# WOLBuddyOverlay retail insertion layout, 2026-11-04

Inspected source revision: `4d07f06c24a6c3580054b674b8126f93c846a14a`.
Preview index: `5a13f2cd61`, published 2026-11-04 02:25 UTC.
Source: `Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLBuddyOverlay.cpp`.

## Repair and target facts

Enable the existing `_BFME_RETAIL_TREE_INSERT_LAYOUT` option before the
STLport headers. Its value-insertion path passes the parent node when the
insertion precedes begin(), and tests the beginning case separately from
iterator decrement. No shared header, name, pin, row or hatch changes.

The 294-byte hint insertion at 0x005DFE50 calls value insertion at
0x005DFD8D from displacement offset 276. Before this change the BuddyInfo
value-insertion COMDAT was 132 bytes; retail's body is 134 bytes. With the
option enabled, `allowed_symbols.py` classifies that call as `fold`, rather
than `wrong/extent`: the selected copy equals retail in bytes and resolved
relocations. This verifies a code-generation shape, not the BuddyInfo name
or the actual retail container element identity (see earlier identity-suspect
attempts at 0x005DFD05 in `reverse/re_attempts.log`).

## Verification

- `find_declared_unmatched.py SOURCE`: all defined functions already matched.
- `./build.sh SOURCE`: all 17/17 rows exact, including the six generated
  funclets verified through their parents' EH data; string, float and import
  checks pass. Verified both the original and changed source independently.
- A/B `allowed_symbols.py --source SOURCE`: all 36 matched-row references
  retain their target and classification except the call above, which changes
  from `wrong/extent` to `fold`. Wrong findings decrease from 5 to 4;
  divergent findings remain 5. These are local-object findings, not debt counts.
- A/B `link_check.py SOURCE`: the value-insertion COMDAT and selected-copy
  blockers disappear. The BuddyInfo `_M_create_node` COMDAT and selected-copy
  blockers remain. Whole-unit prediction stays not linking, 0 -> 0 bytes;
  the unit owns 874 bytes. No census or headline gain claimed.

## Retirement and remaining work

`repair_queue.py retire identity SOURCE` refused and changed no register:
5 ledger objects missing, 444 referenced-provider objects not proven current,
and findings absent from the shadow baseline (AsciiString destruction,
BuddyInfo node creation, and the ignore-tree erase family). The insertion
key is deliberately retained until the owning tool can pass on fresh providers.

The other queued key at 0x005E46A8 remains: range erase targets 0x005E43D1,
whose owner is the SBServer tree. Its complete relocation chain and the
BuddyInfo/LadderPref/SBServer tree identities need reconciliation; a masked
range-erase match alone does not prove the container identity. The insertion
node-creation target 0x005DFCA9 remains inconsistent with the emitted BuddyInfo
helper. The ignore-tree and AsciiString prerequisites remain as documented in
LINK-064 and LINK-181. Next: reconcile these existing container identities and
refresh the participating providers before retrying identity retirement.
