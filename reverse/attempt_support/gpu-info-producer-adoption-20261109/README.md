# Two canonical GpuDrawModuleInfo table producers

ParticleModuleTemplateClones.cpp owns the 35B default constructor and
supplies its register-preservation facts to the same-file 115B runtime
constructor. Its private GpuDrawModuleInfo emitted a one-slot table.
GpuDrawModuleInfoCopyCtor.cpp emitted the earlier such table in census
order. Adopting only the served source preserved all ten code rows but
lost the COMDAT comparison against that private copy, so both producers
are repaired together.

Both sources now include the registered canonical info header. Member uses
map by proven offsets to m_04/m_08/m_0C/m_10; this does not preserve the old
private view's swapped frame-count terminology as a naming claim. The default
constructor's noinline attribute moves to its out-of-class definition,
preserving the same-file caller optimization. The served source uses the
shim's existing constructor-only Snapshot surface to avoid extra base emitters.
The copy source uses the ordinary Snapshot base and removes its fictitious
GpuDrawModuleInfoBase view. Its three replacement header helpers independently
match the existing native Snapshot copy constructor, destructor and scalar
deleting-destructor rows. Retained code bytes, relocation positions, flags
and selection policies agree after that exact base-family mapping.

Both compiler copies of ??_7GpuDrawModuleInfo now have all four native slots
over sixteen bytes, at RVA 0081C1E8 (retail export ordinal1011). The added
references are the already rowed LoadPostProcess, GetSnapshotName and DoXfer.
The copy source's Snapshot table also has its native four slots. There is
no new pin, alias, data owner, source-path move or shared-header edit.

Normal verification passes twelve code rows, seven exact EH graphs and one
float literal. The existing scoped EH proof resolves the served source's
renumbered funclet without a new pin or row edit. Both own link verdicts are
LINKS, totaling 663B against index 717b70f4ab; the comparison is a preview
against an older census, not measured global gain. The header lane retires
exactly two queue rows, leaving three other queued GpuDrawModuleInfo users.
Final normal-object and strict-receipt facts are recorded separately.

The selected three runtime hand tables and four GPU runtime arrays remain
unchanged. There is no complete native compiler substitute for Rva003AECE6's
factory at 0081C608 or clone-primary at 0081CEF8. Wind's compiler primary
binds to 0081C60C, and its pure secondary tables bind to 0081C780; neither
is a substitute for those addresses. The 0081CEE8 alternative is independently
placed by Wind constructor operand003A58DC and is a 16B SELECT_ANY table,
but its four target names are unrowed and it remains bridged. A separately
verified rebind could remove that strong stand-in while retaining its bridge;
complete class recovery must resolve the member/thunk identities. The raw
index's _Rva003AED3E_v14/v1c aliases exist only in an obsolete, non-current
cached object, not current source. They are not additional providers.

No donor was read. This is canonical class/header cleanup with complete native
info tables, not full runtime-module recovery or a real-image/gameplay result.
Local trials, logs and verifier are in build/particle-clone-tables-20261109/.
