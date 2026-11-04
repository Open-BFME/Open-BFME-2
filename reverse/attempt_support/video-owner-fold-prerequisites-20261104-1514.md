# Existing video-owner identity prerequisites

The new exit-link picker at efbd3f2 reports missing VideoBuffer destruction;
the different984a4cdc4d census-only preview reports a duplicate W3DVideoBuffer
destructor. Neither dated result is current complete-image proof. Existing
723C0/7B and723C7/29B owners, BfmeOwnerCC's7280A/92B and72866/28B and the
constructor/table/state consumers already cover the relevant source bodies.
Read LINK-101 and the prior consolidation handoff before planning.

Native read-only plans:
- class --fold BfmeBaseCC --into VideoBuffer: refused because no own rowed
  constructor/destructor/deleting-destructor establishes its installed table.
- class --fold BfmeOwnerCC --into W3DVideoBuffer: refused because the provider
  source would declare the target twice, from its owner and cleanup-call views.

Remaining: reconcile these existing declarations and prove base lifetime,
then use the native identity path, verify all providers/consumers and refresh
the relevant prediction. No new body, alias, name, pin or source edit is made.
The source's17B Rva000723FB row is not the picker's243B unit total. No missing
coverage, resolved real link, runtime or memory/crash result is asserted.
