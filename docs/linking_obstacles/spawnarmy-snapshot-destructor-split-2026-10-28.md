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


**2026-11-14 superseding merge verification (merge-climb).** The supported
merge now absorbs the whole `Rva004E179ADtor.cpp` file into `SpawnArmy.cpp`
alongside two other approved donors: 87/87 rows, seven data rows, zero lost,
three files removed. ProviderGuard and LinkGuard pass with a fresh fetch
before each dry/apply run (09:53 census, SHA256
`a5dce5d8f1f697c358276325b8b5237fa360d962837eaf82bcc083acdaf79c0e`).
Paired raw objects preserve every COMDAT and weak default; the outside
Glo012F1024Item consumer's timestamp-normalized object is identical. The
old isolated split refusal remains historical; the whole-file merge has
verified selected-provider context for this cohort. Ordinary previews are
LINKS, not real-link or census clearance. Evidence:
`sweeps/merge-climb/gate-freed-landings/spawnarmy/`.
