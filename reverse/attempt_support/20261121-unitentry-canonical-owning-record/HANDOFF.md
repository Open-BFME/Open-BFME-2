# The revival entry owns its real 24-byte record

The existing authored UnitRevivalEntry header now includes the native
Rva001EB15A header and uses that owning type at+B0, replacing only its former
24-byte raw array. The existing original-offset explanation is updated;
all other fields and declared APIs remain unchanged. The already banked two
qualified LWP address expressions keep using the same existing assignment
worker. This step does not add an operator, emitter, alias or method body.

Normal before/after verification covers all11header consumers and5provider
contexts:429code/EH and3data rows in16sources. Native link_check reports LINKS
for16/16 (the+16 census comparison predates this change). Independently bound
diagnostics preserve1153complete runtime nodes and67SafeSEH entries, with no
byte/relocation/definition/COMDAT/handler deltas across the16actual objects.
The corresponding32object snapshots remain outside Git at recorded hashes.

This is an ordinary correction to an existing authored header. The saved
outer class contract still has27undecided decisions and is not regenerated,
overridden or represented as a decided contract. A later fixed-header native
adopt/accept must still finish each of the three queued private providers.
No queue row retires here; no new body, unique-byte, full-image or runtime
credit is claimed. Global mask and string defaults are unchanged.
