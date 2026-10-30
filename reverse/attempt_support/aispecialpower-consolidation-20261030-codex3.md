# AISpecialPowerUpdate consolidation prerequisites, 2026-10-30

Base: `b80d10e1ef`. The default picker claimed the approved Update TU and
six whole-file donors. The supported dry run initially accepts none: all
six fail compilation with incompatible private class declarations. All nine
AISpecialPower sources in this directory pass find_declared_unmatched.

The scoped naming planner completed with no missing inputs. Its editor-path
hint places update and post-init under Object/AISpecialPower; that is donor
routing evidence, not target TU approval. The planner leaves the existing
seed unresolved. The current map rebuilt in memory by tu_skeleton approves
16 rows for Object/Update/AISpecialPowerUpdate.cpp (including two mixed-source
rows). The merge lane follows that approval, without asserting the original
retail path or committing a regenerated map.

The first prerequisite reconciles only the seed and update donor. Both now
spell the same AISpecialPowerUpdate getter/post-init interface, Object method
set and Rva004B2F7B field layout. All declarations and offsets come from these
existing target reconstructions; no new recovery name or class-layout proof
is claimed. Bodies, ledger identities, compiler flags and data definitions stay
unchanged. No register or header-queue key belongs to either edited source.

Verification:

- Normal build passes 6/6 rows, one string reference and one float reference.
- Both files still pass find_declared_unmatched; whitespace checks pass.
- The seven external COMDAT digests, five strong-definition records, undefined
  external sets and weak/COMMON bindings are identical before and after.
  The attached JSON records these object facts; null retail verdicts mean the
  comparison records digests, not a separate retail identity judgement.
- Ordinary link preview retains LINKS: seed 199 -> 199 authored bytes and
  update donor 211 -> 211, index 6fe1089c24 (2026-10-30 04:25).

Remaining whole-file prerequisites: constructor/destructor/xfer have different
UpdateModule and AISpecialPowerUpdate base clauses; mapLoadPostProcess uses a
separate secondary-interface view; post-init adds incompatible ModuleData
class/struct and NameKeyGenerator/Object declarations. Reconcile those in
separate verified changes. ModuleNameGetters.cpp and ModuleDataBuildFieldParse.cpp
remain mixed and are not split inside this merge. Next step is a fresh
supported composition of the repaired pair, followed by the full path-consumer
and provider audit. No census, runtime or image-ownership gain is claimed.
