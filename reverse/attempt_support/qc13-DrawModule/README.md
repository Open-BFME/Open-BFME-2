# qc-13 item 5318 DrawModule prerequisites

Base: 45afcff3a6. No Code adoption retained.
Target: DrawableModule constructor RVA 306B19 stores its ModuleData argument at +4 and Thing virtual-slot-4 result at +8; DrawModule constructor B19A1 delegates to it and installs VA BC9690. Extent is 12 bytes. The complete native constructor and two 62-entry tables are attached. Contract majority and reused ledger symbol names are not semantic proof of slot names.

ProjectileStream constructor D1370 currently reads +4 through a field misleadingly named m_drawable. The light DoDraw body reads module data at +4 and drawable at +8. Giving the projectile body canonical drawable storage would change its byte-matched behavior. No alias, fallback, second field, or layout variant was added to conceal this incompatibility.

The retail parent is DrawableModule. It has no canonical registered header; only private shim copies exist. Establish its actual Snapshot profile and full virtual providers first. The DrawModule native table is 62 entries (ledger 248 bytes); guessed slots 62..64 from derived views cannot be included in this table. No root adoption or sampled contract is admitted. The attached generator refusal is evidence, not the sole reason for deferral.

Donor facts: pinned BFME1 7a8a034afa7d ZH DrawModule.h derives from DrawableModule; this agrees with the target constructor call but does not prove BFME2 slots. Official BFME1 upstream checked at 3d787aa1656d; pointer retained, no freshness success recorded because no full reference-update gate was run.

Next: canonical DrawableModule parent/profile, native DrawModule virtual declarations and derived provider closure, then preserve the projectile +4 access under an evidence-supported ModuleData operation. Full native target-slot audit remains required before adoption.
