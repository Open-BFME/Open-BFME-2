# World add/remove routine

The served candidate points to OpenContain.cpp, which was inspected in full,
including its retained reference addOrRemoveObjFromWorld and its four exact
home rows. WB 01192C00 was read in full; its folded BitFlags export is not
accepted as this routine's method identity. Its callgraph and native body
00462E3A..00462F34 establish the world add/remove and rider-recursion purpose.
ZH/BFME1 is the semantic source lead. The two-argument donor declaration does
not describe the native three-argument RET12 ABI, so the target body keeps an
address-derived name in a small neighboring TU without changing that donor
declaration or deleting its unmatched body.

Native evidence establishes owner +8, position +38, object flag +454,
containment module +250, module virtual slot 70 returning a two-word result
whose second word is a list pointer, and primary virtual slot 24. The second
argument's low byte controls the branch, but its full word is forwarded to
slot 24. The third argument is unused. The result's control-word ownership
and slot argument meanings remain unresolved. Secondary slot 44 returns
the 16-byte mask corroborated independently for OpenContain's load routine;
word 1 bit 29 controls recursion. Target offsets differ from WB's.

The old attempt was blocked by a new address-named AI global. This version
uses the existing actual TheAI provider and all existing Object, Drawable
and Pathfinder providers; no pins, aliases or data-address globals are added.
The first O1/G7 trial was 255 bytes because the containment member was read
twice. Keeping its pointer in a local reproduces all 250 native bytes and
relocations exactly. The normal gate is required before admission and commit.
This is scoped byte evidence, not fresh linking or runtime proof.
