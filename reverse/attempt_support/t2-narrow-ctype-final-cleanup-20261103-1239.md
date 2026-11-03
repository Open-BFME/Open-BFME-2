# Finish the composed T2NarrowCtype declarations and migration marker

The merged source already includes string.h and uses STLport4.6. Remove its
redundant local memmove prototype and obsolete standalone stlport(4.5) marker;
keep stlport46. The actual compiler command/environment fingerprint is unchanged.
Native normal/frozen/EH/strict checks preserve all eight190B rows, all ten
external code bodies/relocations and every non-debug section including directives.

The owning Microsoft audit retires the one key refreshed by the merge; all
unrelated queue records remain. The outgoing batch has no net queue reduction
against its starting snapshot: the merge exposed, then this cleanup retired,
the seed's pre-existing unregistered prototype. The declaration itself is gone.
The native STLport migration queue excludes both the absent donor and the
already4.6 destination. Its cached historical report is retained because the
local trial cache is absent; old source-context trial results are not falsely
reassigned to the new composition. No global trial report is wiped.

No source body, import, compiler option, alias, pin, shared header or baseline
changes. This is a separately verified follow-up to the structural merge,
not a game-runtime, native-coverage or linked-byte gain.
