# Production queue canonical Module data access

Replace the private Module field view with canonical Module and a partial
derived access view exposing its existing protected ModuleData pointer.
Interpret that pointer as the existing local data view only at the call site;
do not declare a second typed Module::m_moduleData. Native queueUpgrade calls
the existing CastleBehavior lookup at 0x0049D960, loads return+4 at 0x0049D96A,
then tests data+0x18 at 0x0049D96D. The 81-byte lookup at 0x00395708 and
43-byte Object::findModule at 0x0028B6D6 return the raw Module pointer.

Fresh private before/trial and final normal verification preserve all 47 rows
and parent EH graphs. All 137 external code bodies and symbolic relocations
are identical. The owning acceptance tool retires one Module header key;
ordinary preview retains LINKS/8,298 authored bytes against ccafe54d1d.
No new body, symbol, shared header, pin, path or complete CastleBehavior
hierarchy/field-name recovery is claimed. Native facts and final object
invariants are recorded in proof.json; no donor facts are used for this change.
