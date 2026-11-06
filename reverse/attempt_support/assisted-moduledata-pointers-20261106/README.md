# Assisted laser template pointer types

Correct the two laser members of the existing0x18 module-data factory view from
const char pointers to const ThingTemplate pointers. No field name, offset,
initializer or runtime instruction is changed. The existing explicit folded
vtable reference is retained; native inheritance/table recovery remains open.

Target evidence: the admitted80B FieldParse atC4AFE8 selects the byte-matched
INI::parseThingTemplate(33940F/236) for offsets10 and14. That callback stores
TheThingFactory->findTemplate's result. Assisted's matched attack body reads
those same offsets as ThingTemplate pointers and passes them to the laser
factory. These facts establish the BFME2 types. Zero Hour's corresponding
ModuleData uses AsciiString names and is a different layout/behavior; it is not
the evidence for the recovered pointer types.

Private control and candidate both match constructor253C08/27 and factory
253C23/68. All external bytes/relocations, binding/COMDAT properties and symbol
routes remain equal. Normal build verifies both rows. This is type cleanup;
no new authored bytes, TU approval, merge or image behavior is claimed.

Publication audit carried from92b1dc257f: INCONCLUSIVE, index7bd55416c6,
outgoing base6f332c985e87903d3c1450f8a58b2ffcbb22e3db, one missing current receipt
for AssistedTargetingUpdate.cpp. Current-consumer and real-image confirmation
remain open for the next census/maintainer run.
