# AssistedTargetingUpdate native callbacks, 2026-11-06

Base be723e22e6. Native factory24CC11 allocates0x20, the size of UpdateModule.
Ctor486E8D and complete destructor486E18 install primaryC4AF64 (13 slots),
behavior interfaceBEFF90 (47) and update interfaceC4B1E0 (3). The donor's two
laser-cache pointers do not fit that allocation; native assistAttack already
reads template pointers from module data+10/+14 instead.

Two verified body commits replace false cache-building implementations:

- update returns FOREVER, the complete6B native body4A6563 in interface slot0;
- post-load forwards to UpdateModule, the complete5B native body497805 in
  primary slot1 (direct target58B03E).

Each spelling is admitted through add_match's genuine ICF path, with the existing
owner and explicit fold-proof retained. Existing owners are not renamed or moved.
No new pin/alias, class/header definition, data owner, TU assignment or path is
introduced. The owning counter retires exactly the two now-rowed markers.

Normal7/7, one literal and the pool-key's EXACT EH graph pass. The normal object
has the private winner's code and provider routes; all613 remaining external
code definitions are covered by that comparison. Only the two intended methods
change. The unused donor findTemplate wrapper stops emitting; the local index
also has RTS/ScoreKeeper's copy and does not retain a reference to that spelling.
The unit still does not link because its inherited donor CRC table slot remains.
There is no new census, real-link or runtime clearance.

## Next coupled repair

The full native profile is0x20 with13/47/3 slots, and no laser-cache instance
fields. The constructor currently stores three dummies. Its canonical probe
(ctor-probe.cpp.txt, compiled privately in the original ctor source context) keeps
the84B constructor and its10B handler, with EXACT EH, and emits the13/47/3
compiler tables. The same probe emits the genuine27B xfer body: Version1 at53EE,
then public UpdateModule::xfer at44DF9F. ctor-probe-summary.json records those
code checks; lifetime names/table edges are proposals, not admitted bindings.

Main's imported Xfer is already defined before its explicit Xfer include, so
the local include replacement trial is a class redefinition, not a verification
bug. Do not add a private registered Xfer copy or a fabricated Version1 pin.
Use canonical Xfer in the constructor/native-view closure.

The existing25B/28B lifetime owners are Rva00486E18 in mixed
Rva0024A797Derived.cpp. Plain class-fold refuses because the dummy ctor does
not bind a live Assisted-named native table; the current emitted owners use
placeholder Update base qualifiers. Reconcile the named constructor/table and
lifetime owner together through supported tooling. Preserve every mixed-file
row. The complete destructor has only proposed placement in the committed map;
the deleting destructor is approved. Identity alone grants no permission to
move the complete body. No mixed-file source, constructor or lifetime row was
changed in this callback batch.
