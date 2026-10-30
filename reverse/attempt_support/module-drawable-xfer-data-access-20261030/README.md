# Drawable serializer Module data access

Use canonical Module with an abstract access view for the existing protected
data getter. The serializer calls the unchanged ModuleData tag getter directly
through that pointer. Its private Module forwarding wrapper is no longer
needed; no new field, override, helper body, pin or row is introduced.

Native 0x00278777/0x0027877A and 0x002787EE/0x002787F1 independently load the
data pointer at module+4 and the tag at data+4. All three rows and EXACT EH
survive private and final strict-current normal builds. The six retained code
definitions and their relocations are identical after the public/protected
Module data-getter spelling change. The seven-byte outlined tag wrapper had
only a debug reference in the control object and is removed. No native RVA or
original method identity is assigned to that wrapper.

This removes the last observed public Module data-getter copy. The consumer
audit checks every indexed touching object, not just admitted-reference edges:
Drawable, GiantBird and Foundation. Before this adoption, only Drawable still
defined the public four-byte getter; all observed references were debug-only.
Afterward, all three current objects lack both removed names and any references
to them, while retaining the identical protected getter. The tag wrapper's only
indexed touching object was Drawable. Source/command/dependency and object hashes
are checked separately from strict include-inventory currency in the proof.
This is a bounded current closure, not a whole-image loss or census result.

Normal checks retain all three string references. The owning Module acceptance
tool retires the file's remaining header key. Ordinary preview against
ccafe54d1d preserves LINKS/409 authored bytes. No coverage or census gain is
claimed; the independent ModuleData interpretation is unchanged.
