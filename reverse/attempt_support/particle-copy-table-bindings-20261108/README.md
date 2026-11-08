# Particle template copy table bindings, 2026-11-08

ParticleModuleTemplateCopyCtors.cpp replaces its 21 one-byte table stand-ins
with existing compiler table symbols. Rva003AF27BClone.cpp changes the only
live outside reference, Rva003AF208_v18, in the same batch. The other source
search hit is a comment in ParticleSystemTemplate.cpp. No data_rows or
data_converged entry owns a removed char; no new provider is defined. The
d171e84869 census index touches the old symbols only in these two sources.

provider-proof.json records each replacement's native table RVA, extent,
existing emitted symbol, rowed constructor operand, zero-addend DIR32 site
and cached emitter object hash. Every native operand contains the exact
table VA. These are target address facts and cached provider evidence, not
recovered original class names, hierarchy, donor paths or a current image.
Opaque class names remain unchanged.

The nine existing alternatename directives also disappear. Their shared
one-pure-slot table at RVA 0x0081C780 already has independently witnessed
compiler symbols for each construction stage. A private trial using just
one common symbol matched only five of nine constructors: the compiler
coalesced stores across stages in the four 77-byte constructors. Distinct
existing DefaultParticleModule<3> and derived-module slice symbols retain
all stores and all nine matches. No alias, pin, flag or hatch is introduced.
The tool-generated hatch register shrink is restricted to these nine
removed aliases; all records outside this source are byte-identical.

Normal ./build.sh verifies all ten rows, totaling 579 bytes of row extents;
the clone's one EH graph is EXACT. Both files are unfrozen and pass strict
receipt preparation. All code COMDAT facts, relocation positions and section
flags agree after normalizing only the independently proved old/new table
referents. Exactly 21 external definitions disappear and none is added.
The standalone guard correctly rejects dropping the shared char while the
old clone still references it. The normal paired staged-peer check passes
with the clone updated. Ordinary current-object preview conserves LINKS in
both files, 577 authored census bytes at d171e84869 (not a full link).

The bounded bridge replay includes these two sources, cached constructor
emitters and native slot owners. Starting with the 21 affected table
addresses, the planner follows constructor references to 29 tables and
115 slots. Strong-definition refusals decrease from 21 to zero; the same
29 bridges and 115 slots remain. bridge-before.json and bridge-after.json
retain their scoped entries. No real-image, bridge-retirement or runtime
clearance is claimed, and no generated queue/pass test is edited.

Remaining work: reconcile the complete concrete/template classes and their
real table emitters, then confirm the effect on the next published real
link and image. LINK-636 and LINK-619 retain this boundary. The prior clone
packet's shared-char prerequisite is now resolved within this cohort.

Published as 7efac5f6d8; first attempt landed in 29.4 seconds. Required
row/EH/scoped-DIR32 checks pass after rebase. Broader link audit remains
INCONCLUSIVE: index d171e84869 versus outgoing base
0292da473397a175f09d211b8414f863e409d73a; Common/AIBaseBuilder.cpp lacks a
current receipt. Carry that consumer into the next census/image check;
this publication does not establish full link closure or runtime progress.
