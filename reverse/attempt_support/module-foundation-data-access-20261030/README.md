# Foundation canonical Module data access

Adopt the existing Module header through an abstract public access view for its
protected data getter. No fields, override, or helper body are added. The
existing BfmeItemE63 partial view retains its gap after the eight-byte base and
its keep/castle IDs at +0x14/+0x18; no original complete identity is recovered.

Native 0x00455817 loads module+4 and 0x0045581A tests data+0x74. The native
reads/writes at 0x00455A78 through 0x00455A81 independently retain both item-ID
offsets. The existing CastleBehaviorModuleData interpretation stays separate.

Private before/trial builds and the final strict-current object preserve five
rows, EXACT EH and all 26 external code definitions/relocations after the one
public-to-protected getter spelling change. Both getter bodies remain exactly
8B 41 04 C3 with no relocations. Observed current Drawable, Worker and GiantBird
copies keep the public/protected providers; this is not a sole-provider removal.
The index's admitted-reference graph has no incoming public-getter edge; that
is not a claim that every raw executable reference elsewhere was inspected.

Normal verification passes the string and three float references. The owning
Module acceptance tool retires one key; preview against ccafe54d1d retains
LINKS/1,182 authored bytes. No new coverage or census gain is claimed. The
Thing/Matrix3D ownership prerequisites remain documented in the separate
foundation-header-ownership-prerequisites handoff, with both keys still open.
