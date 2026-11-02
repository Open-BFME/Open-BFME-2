# ThingFactory cohort audit preparation

Inputs are the25 immutable originals listed in before.json; canonical
Common/ThingFactory.h was read unchanged. No live source/ledger/cache mutation
or gate was performed for this preparation.

- **07 ThingFactoryDtor.cpp** is the sole lifetime/table owner in the cohort.
  Its71B destructor calls freeDatabase, destroys the nontrivial+14 member and
  chains SubsystemInterface. The canonical+14 array is storage-only, so it
  cannot silently replace this lifetime. Preserve the existing noinline dtor
  relationship and normal-versus-unwind member destructor contracts.
- **08 ThingFactoryNewTemplate.cpp,09 ThingFactoryReset.cpp and14
  Rva002D06CAGet.cpp** define actual ordinary ThingFactory methods, but no
  factory ctor/dtor.08 has throw() lookup declarations absent from the
  canonical interface;09/14 use typed+14 lookup storage that is opaque in
  the header. They need independent full code/EH/binding proof.
- The other21 are factory consumers. There is **no ThingFactory constructor
  definition** among the25.05 consumes a separate inherited rva002CF1C9 API;
  the canonical header does not assert that method.06/10 directly access a
  first-template field made private by the canonical view.12 uses a TU-local
  findTemplateInline adapter absent from the canonical API.

Any lifetime emitter must preserve the complete14-slot ThingFactory table
VA C0233C (56B), base table BD77A0 and any deleting wrappers, not merely the
vptr store or first destructor slot. The W3D ctor/derived table BC4858 are
outside this cohort. For consumers, verify that adoption introduces no new
factory/base table or unintended inline-provider variant.

The existing private subsystem_bfme2/subsystem_interface.h profile defines
its own full14-slot SubsystemInterface; canonical ThingFactory instead selects
BFME_SUBSYSTEM_SLOTS before including the registered SubsystemInterface.
Sources00/09/10 and several later include chains already parse the private
surface. Duplicate definitions, short-versus-full prior selection, Bool return
spelling, inline setName and base-copy/destructor differences are real profile
constraints. Do not globally change this profile to make one trial pass.

Whole-object comparison must include unrelated tables and member-pointer data:
AwardSystemManager00, ControlBar10 and Apt callbacks11/12 are emitters of their
own classes.11 deliberately manages STL exception macros and later selects
multiple-inheritance member-pointer representation. New base visibility can
change incidental helpers/data even when factory calls themselves match.
Keep source compiler flags, existing optimization/pragma contexts and actual
global TheThingFactory binding fixed. Archive candidate objects before any
restored-original rebuild; authenticate original source hashes separately.

All25 owning trials subsequently failed and were restored. The bounded next
task is the Award00 data-row failure; this preparation does not claim any
accepted header adoption.
