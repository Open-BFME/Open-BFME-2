### LINK-113: BoneFXDamage imports the Zero Hour DamageModule Snapshot contract

Status: Cleared for the three-unit current-object preview at `5eb11e1e87` (2026-11-05); earlier snapshot repair plus shared INIException adoption pass, 9/9 rows exact; census/real-link confirmation pending. [Evidence](../../reverse/attempt_support/bonefxdamage-iniexception-20261105-codexb5.md).
Status: Cleared for BoneFXDamage.cpp's Snapshot-contract obstacle in the current-provider preview, 2026-11-05 at `05fbaef1d0`; 9/9 rows exact, `link_check.py --refresh` LINKS 322 B. [Verification and stale-index distinction](../../reverse/attempt_support/bonefxdamage-current-preview-20261105-codex.md). Real-link/census confirmation remains pending; table identity cleanup remains separate.

Status: Cleared for the original Snapshot-contract mismatch in a current-object preview, 2026-11-05; awaiting census confirmation. The repair landed in `a0e226ee89` and its prerequisites; this pass adopts canonical INIException and verifies BoneFXDamage plus its two current providers all LINKS. Evidence and remaining pool-key cleanup: [2026-11-05 verification](../../reverse/attempt_support/bonefxdamage-iniexception-20261105-codex3.md).

Historical investigation (retained):

2026-10-29 recheck at `bd9c9a4d73`, current index `85f6b7f40c`
(2026-10-29 15:08): ordinary preview still reports the three unresolved
DamageModule snapshot methods and the constructor-copy conflict (U3/L1).
The canonical Module/BehaviorModule headers now exist, but this source still
imports the ZH DamageModule declarations; the constructor provider still uses
placeholder tables. Reconcile that DamageModule contract and the existing
xfer/destructor owners together. No source trial was repeated, and no
clearance or census gain is claimed. The unchanged prerequisites are recorded
in the attempt log so the picker can defer this target.

2026-10-28 recheck at `6d7a215d6b`, refreshed index `d92e7e6635`: the
claimed BoneFXDamage consumer still reports the same three unresolved
DamageModule snapshot methods and one constructor-copy conflict (U3/L1).
No source trial was repeated; the shared-contract prerequisites below remain.

Status: Repair landed / awaiting verification. Updated: 2026-11-05; inspected revision: `dd65af9110`.
Historical status: Blocked on shared module interface and existing row identity reconciliation. Updated: 2026-10-27; inspected revision: a0b82f68445de8ab0254437ef7e97332ce48cfb0.
Evidence / affected units: `GameLogic/Object/Damage/BoneFXDamage.cpp` remains U3/L1 with the current `DamageModuleCtor.cpp` provider against ordinary-preview index `bf3dd31211`. The unresolved `DamageModule::crc`, `xfer` and `loadPostProcess` names occur in unrowed BoneFXDamage donor methods and the emitted 56-byte DamageModule primary table. They are not direct REL32 references in the matched BoneFXDamage bodies. Native constructor 0x004B979C calls the rowed base constructor 0x004B9704, which installs table 0x008598E4. That native table begins with deleting destructor 0x004B973B, load hook 0x0058B03E, DamageModule name getter 0x004B9735 and xfer 0x004CE56D; the imported table begins crc, xfer and loadPostProcess instead.
Completed: all seven BoneFXDamage rows pass byte verification, and the current-object references and native table were inspected without modifying source. Existing native owners include `UpdateModuleLoadPostProcess.cpp`, `ConstIntGetters4.cpp` and `Rva004CE56DXfer.cpp`; the latter xfer still has a placeholder owner. The base constructor provider retains LINKS. No unrelated donor body was removed and no new body or pin was added.
Remaining / next check: reconcile the shared Snapshot/module contract and the existing base xfer/destructor owner identities before replacing the imported declarations. In particular, do not invent a crc match from an unrowed donor-only reference or replace the real DamageModule method call with a placeholder. The native 27-byte xfer at 0x004CE56D is an owner-identity lead, not an approved rename.
Clearance: pending.
Census confirmation: not claimed.

2026-11-05: Upstream canonical module repair now gives 3/3 LINKS with the current destructor and DamageModule providers; INIException header debt retired, pool-key merge blocked only by stale provider-index input. Await authorized real-link confirmation; [verification and next step](../../reverse/attempt_support/bonefxdamage-canonical-exception-20261105-codexb.md).
