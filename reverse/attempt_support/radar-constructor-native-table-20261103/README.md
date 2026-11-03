# RadarUpdate constructor table and orphan cleanup, 2026-11-03

Base 674745bad6; retained census index 23b85ddde5 (2026-11-03 18:36).

## Target evidence and change

The native 53-byte constructor at RVA 004A0C72 installs primary table 00851A0C, BehaviorModuleInterface table 007EFF90, and update-interface table 00851A00. The constructor body was already matched; the emitted tables were wrong. ObjectModule.h had read Snapshot before UpdateModule.h could select the native name slot. The primary table also inherited UpdateModule::xfer, left getModuleNameKey pure, and appended three invented anchor virtuals; the update facet left update pure.

Select BFME_SNAPSHOT_NAME_SLOT before the first Snapshot inclusion. Declare RadarUpdate's actual virtual overrides. The primary table now has 13 slots, with xfer at 004A0CC3 and getModuleNameKey at 004A0C2D, and its update facet names the existing 004A0D5F owner. All ledger-resolved native entries agree: primary 10/10, update 3/3, behavior 45/45. Primary slots 0/5 and behavior slots 1/19 use unchanged compiler-emitted providers, so this comparison does not independently establish their native identity. Slot 2's target is the six-byte 004A0C27 owner still named Rva004A0C27Named::name. Its file and body are claimed by another worker. This change supplies the required GetSnapshotName declaration, without renaming the held owner, adding a pin, alias, wrapper, stub or duplicate row.

The constructor's 60 external definitions and binding properties are preserved; only its primary/update table payloads change. All other code, data and relocation payloads remain identical. SupplyCenterDockUpdateConstructor.cpp loses only the three obsolete Radar anchor C3 bodies and their isolated dummy class. Every other one of its 64 definitions and binding properties remains identical. The retained index found no consumers except the old constructor; both rebuilt objects contain zero references to any retired anchor. No pins or aliases owned the anchors. The hatch tool computes the three present_unmatched retirements; unrelated stale register entries and admission stamps were preserved.

## Verification and limits

Normal build.sh: 2/2 rows exact (Radar 53B, Supply 49B); both strict frozen-file checks pass. No ledger rows, function sizes or source paths change. The current-object link preview retains Supply's 49B and leaves Radar unresolved solely on ?GetSnapshotName@RadarUpdate@@MBEPBDXZ. Before the change Radar was already unresolved solely on nonexistent UpdateModule::crc. This is installer correctness and three retired hatches, not a claimed census/link/ownership gain.

The other worker can now apply the supported to-class rename at 004A0C27 after verifying current installer objects and coordinating its held scope. RadarUpdateView.h's separate canonical duplicate cleanup and TU merge remain open. Do not infer complete class recovery or original field names from this scoped constructor view.

## Prior audit carried to the next scheduled census

Push a76ab8d1cd was INCONCLUSIVE: index23b85ddde5, outgoing base2278a89146ddb57ac91d5e111f161306326780b2, one source-object receipt gap, first Code/GameEngine/Source/Common/Rva0057702EClear.cpp. Recheck that source and its owning-pointer consumers (Rva005770F7Dtor.cpp, Rva00576C4BDtor.cpp and GameClient/GUI/Rva005776A7Ctor.cpp) in the next scheduled census; no whole-unit/whole-game clearance was claimed. Earlier scopes remain carried in their existing packets.
