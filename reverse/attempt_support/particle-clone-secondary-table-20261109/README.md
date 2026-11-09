# Wind secondary-table consumers

The native Wind constructor at 003A58A6 independently installs the existing
compiler table at 0081CEE8: its DIR32 operand at 003A58DC contains 00C1CEE8.
WindModuleConstructor.cpp already emits a sixteen-byte SELECT_ANY table under
`??_7Rva005FEAD0DefaultModule7@FXParticleSystem@@6BRva005FEA50WindInfoBase@1@@`.
This placement is a target fact, not proof of the original class name or of
the compiler table's method identities.

ParticleModuleTemplateClones.cpp also defined a strong sixteen-byte Slot3
array at that address. This repair removes that array and rebinds every live
consumer in the served source, ConcreteModuleTemplateCopyCtors.cpp and
ModuleCtorChainsA.cpp to the existing compiler symbol. The two split
ModuleCtorChainsA sources retain only unused declarations; their strict-current
objects contain neither the old symbol nor a relocation to it. They are not
edited. No method row, data owner, pin, alias, source path or shared header
changes. No new C++ body or class recovery is claimed.

Normal four-source verification preserves 33 code rows, fourteen data rows,
one path string, one float and seven exact EH graphs. The three changed objects
preserve every retained code/data body, relocation position, flag, selection
policy, external definition, weak binding and linker directive, after exactly
one table-reference substitution. Only the strong array and its three now-unused
slot references disappear. The copy constructor uses a const-correct pointer
store with identical native bytes.

The five-source ordinary link preview is 5/5 LINKS, 1,856 authored bytes, against
index 717b70f4ab. The fifth source is the already repaired
GpuDrawModuleInfoCopyCtor.cpp from 26b8c19de9: omitting that current producer
would compare the clone source with its obsolete short copy in the older index
and report a GPU table COMDAT conflict. These are scoped previews, not census
or real-image gains.

The fixed-order eight-object before/after replay removes one strong-definition
refusal and generates the same Wind secondary bridge with the same four
selected native slots. The existing compiler table still needs that bridge;
its destructor, no-op, name and transfer identities are not recovered here.
The unchanged OpaqueScalarDeletingDtorsB02.cpp, WWMath/region.cpp and
ConstIntGetters4.cpp support caches lack strict receipts (the last also lacks
general currency). Their state is explicit in replay.json. The replay uses
private native-verified before/candidate objects for the three changed sources;
it does not establish a current global plan, an image or runtime behaviour.

The factory table at 0081C608, clone-primary at 0081CEF8 and four GPU runtime
strong arrays remain. Wind's primary table is independently bound at 0081C60C
and its pure category tables at 0081C780; they cannot replace those two clone
tables merely because their names or sizes resemble them. Genuine polymorphic
producers and supported method-family recovery remain prerequisites. LINK-004
and LINK-627 retain this scope. LINK-584 is currently claimed by another worker;
this packet supplies its relevant follow-up without touching that claim.

Local reproducibility: build/particle-clone-tables-20261109/secondary-trial.py,
verify-secondary.py, secondary-replay.py and the secondary-* logs/objects.
The native rows and whole-object comparison are repeated against normal build
objects; proof.json records the final strict receipts separately from the
bounded support-cache caveat. No donor was used.

Previous GPU producer package 26b8c19de9 landed on its first push attempt in
51.4 seconds, with post-publication strict/native proofs passing. Its broader
audit was INCONCLUSIVE for unchanged AIBuildable.cpp's missing current receipt
(index 717b70f4ab, outgoing base 48b9eff16e). That consumer and this repaired
table scope must be carried into the next maintained census and real image.
