# AI-upgrade heuristic table boundary

Native RVA `0x00876510` is exactly two entries: callback `0x005DA67F`, then deleting destructor `0x005DA7D9`. Constructor `0x005DA831` independently installs the following table at `0x00876518` (store at `0x005DA841`); its entries are `0x005DA854` and `0x005DA663`. Its first callback therefore is not a third slot of the preceding class.

Rva005DA7F5Dtor.cpp and OpaqueScalarDeletingDtorsB16.cpp both declared an extra pure `slot2`. Removing that declaration changes their emitted `??_7Rva005DA7F5@@6B@` extent from 12 to 8 bytes and removes only the third relocation. Both earlier slot pointers stay identical. Fresh scratch compilation of the unmodified parent sources independently verifies the before objects: every other COMDAT fingerprint is unchanged in each edited unit. Comments now describe the independently installed adjacent table.

`./build.sh` passes **52/52 rows** across the six-unit class/base cohort. The three affected table emitters retain **852 -> 852 bytes, 3/3 LINKS** in the current-object scoped preview against the older aa7acf764d census. This preview has a stale-index warning; it does not establish whole-image linking.

The constructor-owned class is AIUpgradeHeuristicFactoryUnlock; native constructor/destructor stores tie the placeholder destructor family to it, and the ordinary non-prepared fold planner accepts that identity. Slot 0 still needs a real override: the existing abstract base declares `void slot0()`, whereas callback5DA67F returns an integer and consumes one four-byte argument. Factory59710E forwards one word through slot0 and stores EAX at+40. A Player* spelling in another family view is type evidence to reconcile separately; RET4 alone does not prove a source parameter type. No bridge row is retired by this boundary correction.

[Exact before/after table and COMDAT evidence](ai-upgrade-table-boundary-20261113-root20.json). Inspected parent e00363180fb; independent native review agrees with the two-table boundary.
