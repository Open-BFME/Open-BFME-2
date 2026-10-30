# KeepObjectDie header acceptance: stale mixed peer

Current KeepObjectDie.cpp already includes canonical ObjectModule/DieModule
and Thing/ThingTemplate; onDie uses inherited m_object. The old m_08 and
constructor-view errors no longer describe this merged TU. Fresh normal and
strict verification pass all ten rows, three literals and both parent EH
graphs. No source edit is proposed.

Owning-tool ObjectModule acceptance still refuses: its ordinary single-source
preview reports a duplicate ?name@Rva00486C8FNamed@@QBEPBDXZ. The ccafe54d1d
index retains that strong definition in mixed ModuleNameGetters3.cpp. Current
ModuleNameGetters3 has no such definition. Its 101 remaining rows/literals
pass fresh strict verification; the merged KeepObjectDie getter is native
exact at 0x00486C8F (6 B). proof.json records both current object/source hashes,
the exact getter and the stale index provider.

Ordinary two-source preview: both LINKS, KeepObjectDie 431 -> 437 authored
bytes and the remaining mixed peer 701 -> 605 against the old index. These
are source moves since that index, not a newly measured loss or gain.
The acceptance tool has no peer argument. Both ObjectModule and Thing keys
remain registered; no hand retirement, checker change or index mutation.

Boundary: false-reject header_adopt_lane caused by a stale mixed peer. Retry
the owning acceptance after a supported current index refresh, or have a
separate tooling change supply verified affected peers to the retirement
guard. A full index refresh presently reaches 1,483 stale units, so this
small cleanup pass does not attempt that unrelated rebuild. No donor facts
or newly recovered native bodies are claimed.
