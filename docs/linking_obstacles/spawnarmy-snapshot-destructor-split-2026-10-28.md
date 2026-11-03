### SpawnArmy snapshot destructor split (2026-10-28)

Status: Blocked on selected vtable context. At `a6d64019bb`, the supported
split of `Common/Rva004E179ADtor.cpp` into the approved SpawnArmy TU matches
all seven carved rows in isolation, but its link guard rejects moving selected
`??_7Rva004E179A@@6B@` without matching private/weak-free context. No source
or ledger paths moved. Review the existing
[snapshot binding proof](../../reverse/attempt_support/spawn-building-snapshot-link-20261020/readme.md)
and establish the selected table's complete relocation and weak-symbol context
before retrying. The larger 41-donor merge dry run was interrupted without a
verdict; it does not establish a mergeable set. No link or census gain is claimed.
