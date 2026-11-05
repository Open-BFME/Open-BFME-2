# WallUpgradeUpdate consolidation prerequisites

Inspected revision: 96e9022227 (2026-11-05).

The refreshed in-memory TU map offers three complete donors: PoolKey, Slots,
and Xfer. Rva0024A797Grandchildren.cpp remains mixed and is not moved.
The scoped source-layout report independently flags compiler differences,
duplicate views, internal linkage and quoted-include context; it grants no approval.

`tu_skeleton.py --merge .../WallUpgradeUpdate.cpp --dry-run` accepts no donor.
PoolKey and Xfer conflict with the seed's explicit DamageModuleInterface
vftable declaration when the canonical header defines the class. Slots also
has incompatible Object and receiver views. `tu_views.py` restores both its
Object trial (incomplete member/mask dependencies) and Rva004AB4AB trial
(missing ObjectID declaration). No view change is retained.

The attached diagnostic patch replaces the seed's private UpdateModule and
WallUpgradeUpdate views with the existing canonical header and replaces manual
vptr stores with ordinary construction and member initializers. It passes the
normal builder: 21/21 rows, two string literals and two float literals.
`find_declared_unmatched.py` also passes. However, the current-object link
preview against census c95fcfcfcd (2026-11-05 05:17) loses this unit's 1,044
census-linked bytes, reporting these four unresolved symbols:

- `??1WallUpgradeUpdate@@UAE@XZ`
- `?GetSnapshotName@WallUpgradeUpdate@@MBEPBDXZ`
- `?loadPostProcess@WallUpgradeUpdate@@MAEXXZ`
- `?onBodyDamageStateChange@WallUpgradeUpdate@@UAEXPBUDamageInfo@@W4BodyDamageType@@1@Z`

The first three need existing retail owners reconciled with the canonical
class identity; the fourth exposes DamageInfo class/struct mangling disagreement
with the existing Slots provider. Exact byte matching alone does not establish
these vtable bindings. Resolve and verify the provider identities before
repeating this header trial or merging the donors; then reconcile the complete
Object dependency closure before the Slots merge.

The trial is reverted. The restored source passes 21/21 rows and the same
literal checks. No source, ledger, baseline, header-queue or alias change is
retained; no census gain or source-file reduction is claimed.
