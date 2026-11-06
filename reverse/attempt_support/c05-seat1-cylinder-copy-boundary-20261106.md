> Superseded during recovery rebase: current master supplies the typed Cylinder copy export and its native vector-deletion dependency. See [current closure and remaining separate identity gap](cylinder-volume-copy-export-20261106/README.md). The investigation below describes its original revision only.

> Recovery publication: historical investigation from 95cb210ba734. Recovered against `8bb483ac9115`; original commands and results below were not rerun during recovery. All original fleet claims were released. These are prerequisites/attempt evidence, not a completed repair or runtime result.

# Cylinder copy export: supported owner boundary

2026-11-06, worker codex-fleet-20261106-c05-seat1; base f15737ff46b.

Picker shard12/30 served fx_particle_system.cpp at the folded EventModuleInfo destructor (0x000B3FD0), attributing the actual missing CylinderEmissionVolumeInfo copy export to that file. Target facts: exports.csv ordinal225 names CylinderEmissionVolumeInfo copy at0x003A653B; functions.csv already owns that entire63-byte range as LineEmissionVolumeInfo copy in the served source. No missing bytes or lost row was established. Real-link42180682743 errors.tsv still lists the Cylinder export.

Canonical LineEmissionVolumeInfo.h describes the same32-byte shape and folded Cylinder default constructor. CylinderEmissionVolumeModuleTemplateCopyCtorThunk.cpp already calls the Line copy owner at0x003A653B. Changing that reference does not provide the missing retail export. The existing source has an inline base-copy view and six scalar copies; prior attempt (re_attempts.log, Line copy blocked class-header) shows adopting EmissionVolumeInfo.h replaces retail inline base copy with an out-of-line call.

No Code or ledger edits were made. find_declared_unmatched.py reports all defined functions already matched. tools/rename.py documents class --fold as placeholder-only, whereas both names here are real retail exports/canonical identities. A second C++ body or hand alias is excluded by the fleet brief; --icf-owner by itself would not settle that ownership requirement. This is a supported-boundary blocker, not a gate false reject.

Prerequisite: supported exported-fold provider reconciliation that preserves existing Line consumers and the inline base-copy/vtable contract, or explicit maintainer direction on this identity boundary. Neither current source row nor canonical header should be respelled speculatively. No byte/link/runtime improvement claimed; no build or gate bypass attempted. Scope claims released before seeking fresh ranked shard work.
