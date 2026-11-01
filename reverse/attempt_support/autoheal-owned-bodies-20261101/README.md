# AutoHeal native-body emission and link repair

The served source has five matched rows, 155 bytes. At fda344a38d the current
preview cannot link it because six imported UpgradeMux names are unresolved.
Its unrowed 98-byte donor destructor emits an incompatible 15-slot UpgradeMux
table; retail C3FC88 has 18 slots. The native 39-byte destructor already has
the Rva0045232D owner at 45232D. The donor loadPostProcess additionally calls
an unresolved upgradeMuxLoadPostProcess. These imported bodies are not native
providers. No claim is made that the original census treated them as unreachable.

The source now carries a TU-local declaration view derived from its existing
shim. It retains the current verified layout, declares the module-data
constructor/parser without copying their unverified bodies, and defines the
two already rowed AutoHeal overrides out of line. Their emission therefore no
longer depends on the donor destructor's table. The unrowed destructor,
undoUpgrade and loadPostProcess bodies are removed, along with the obsolete
list push_back anchor: its 26-byte provider already lives in
Code/Libraries/Source/WWVegas/WWLib/stlport_list_objectptr_insert.cpp.
Shared shims, headers, rows, pins and source paths are unchanged.

All five rows pass normal/frozen/strict checks. Against an original-source
control the object goes from 70 to 10 external code definitions. Eight retained
definitions keep their complete bytes and symbolic relocations; 62 donor or
incidental definitions disappear. Two new four-byte inline getter COMDATs have
only debug incoming references and no runtime/data/vtable references. Neither
changes a matched row. The new-variant check passes. A separate current-object
audit finds no occurrence of the four removed exact destructor/deleting-thunk/
postload/undo names in 18,643 matched-source objects, with none missing; its
concurrent-scan qualification is retained in the evidence.

The current preview against published index 86db074988 now predicts LINKS
0 -> 155 bytes. This clears the source's six unresolved names within that
scope; it does not repair the global UpgradeMux contract or claim a census
or runtime result. Three present-unmatched hatches retire through the owning
hatch_counters --update. No source-file count reduction is claimed.

The commit hook initially reported a shadow duplicate getter from the cached
Disp8LeaNegSbbGetters object. Its actual source no longer declares that name.
Strict preparation of that one-row provider and a fresh private control now
agree on its sole current getter; the extra cached copy is absent. Repeating
the definition audit finds no duplicate. The original/current AutoHeal getter
itself always had identical bytes, relocation hash and exclusive classification.
No common-source or register edit was needed. Both audit snapshots are retained.
