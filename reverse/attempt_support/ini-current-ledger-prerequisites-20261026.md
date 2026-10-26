# INI linking: historical duplicates and current-evidence prerequisites

Inspected upstream `9e1ca7f93f`, BFME 1 reference `f633d0e97a`.
The default queue served the whole `Code/GameEngine/Source/Common/INI/INI.cpp`
unit, represented by `MultiIniFieldParse::add` at 0x0002BC6E (60 bytes).
No source, name, ledger, pin, register or verifier change was attempted.

The complete 1,435-line source was read; SHA-256:
`824a32ea293fbf0787a3b2394d6fb6a397de5b6225425ca4ae1d86a59b993c81`.
Its frozen-file check and normal build pass all **39 rows / 3,039 bytes**,
39 string literals, one empty-string reference and eight named imports.
All **five EH graphs are EXACT**, including the three renumbered funclets.
The ordinary preview counts 2,989 authored nonpadding bytes, a different
quantity from the sum of row extents.

## Existing repairs remain in place

The source already contains the earlier bucket/prime-search repair
`0c7ebc35a7`, the no-case `insert_unique` suppression (`145e3b12a8`) and the
inline bucket accessor that fixes `_M_find` (`00f5191892`). Their evidence is
retained in LINK-004, LINK-013 and LINK-014. The previous
[AI consumer verification](ai-constructor-current-provider-20261026.md)
also distinguishes those repairs from INI's historical-index duplicates.

`link_check.py --fetch-index` confirms that the published index is still
`f995f30157`, dated 2026-10-25 21:36 UTC; it keeps that index and imports 344
matching-candidate objects into the object store. This does not update the
census or certify the current complete provider universe.

The ordinary INI preview still reports **11 duplicate definitions and eight
wrong-selected definitions**, LINKED 0 -> 0. The duplicates concern `~INI`,
`getNextSubToken`, `parseAsciiStringVector`, `parseBitString32`, `parseColorInt`,
`parsePercentToReal`, `parseRGBAColorInt`, `scanBool`, `scanInt`, `scanReal`
and `scanUnsignedInt`. The eight selected findings are the same list excluding
the destructor, `parseAsciiStringVector` and `parsePercentToReal`.
Existing consolidation history and LINK-013 explain the historical copies;
this preview is not evidence for undoing the correct current definitions.

## Current-ledger check refuses before a linking verdict

The supported command

```text
python3 tools/link_check.py --refresh --current-ledger Code/GameEngine/Source/Common/INI/INI.cpp
```

exits 1 before judging INI: **11,481 current-ledger objects lack current
compiler evidence**. Its first examples are RvaSmallVtableCtors,
FXParticleSystem, WinMain, WWLib/ascii_string and System/Snapshot.
This is the tool's strict currency/receipt prerequisite, not a count of
11,481 byte mismatches, missing functions or newly introduced defects.
No transient LINKS result, closure result or new linked bytes are claimed.

The checker was allowed to finish; no duplicate run or gate bypass was used.
No census/index/status was published or manually rewritten, and no nightly,
link-cycle or smoke runner was started.

## Next check

The maintainer's next measured census can reconcile the current ownership
inventory with the old `/MAP`. A current-ledger preview additionally needs
accepted compiler evidence for its entire current provider set; ordinary
per-file byte checks cannot substitute for that proof. Prepare providers
through their supported owning lanes and keep LINK-008's include-inventory
limitations separate. Re-run the guarded preview after those prerequisites
change. Neither a source repair nor a verifier false reject is established
by this pass.
