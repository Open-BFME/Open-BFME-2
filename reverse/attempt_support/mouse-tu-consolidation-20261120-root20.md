# Mouse translation unit consolidation

The fresh plan lists 66 approved rows for Input/Mouse.cpp. The three-file
control build passes all 64 function rows, four data rows, and eight
exception-handling graphs. The mixed GapBodiesGE51.cpp and FontLibraryInit.cpp
also contain rows assigned to other translation units. They stay in place.

Three shared-header adoptions passed queue acceptance. The seed now uses the
registered Rva001EDDBBForwarder. The tooltip donor uses the shared RGBAColorInt
and registered Mouse declarations. The tooltip's native body, handler and
funclet match under the default compiler profile. Its seven external COMDAT
fingerprints and reference edges match the original object.

Carrying the tooltip donor's old override into the seed initially cost ten
matched rows. The flag tool retired the override after a scoped default-profile
scan passed all three tooltip rows. The ordinary full commit gate verified
102,329 function rows, 2,361 data rows, and the no-op patch. The final dry run
reached compilation for both donors.

- The tooltip composition now fails three compiler checks. The seed already
  defines RGBColor and RGBAColorInt through its legacy headers, and the
  registered Mouse header refuses to follow the short SubsystemInterface
  definition.
- The lifetime composition still redefines RGBAColorInt, ICoord2D and
  CursorInfo. Its cursor-field spellings and integer assignments also disagree
  with the seed's fields and enums. A scratch trial for an explicit
  CursorInfo destructor missed the destructor and six EH rows. The existing
  emission anchor stays in the seed.

The final owning dry run accepted zero donors. The current map and all source
paths remain in place. The logs are under build/root-resume-20261120/mouse-merge.

[Authoritative run 382](https://github.com/Open-BFME/Open-BFME-2/actions/runs/44752924204)
records a four-byte selected Mouse vtable at RVA 0x007E0358 and a 30-slot bridge.
The target of slot 9 is the rowed forwarder at 0x001EDDBB. The canonical
Mouse::reset is still a different provider spelling. Slot 14 resolves to the
nonvirtual parseIni at 0x001EE483, and slots 26 and 27 use the standalone
setter/getter providers at 0x000419CF and 0x000419DC. The lifetime merge needs
one proven class and provider set across those contexts. LINK-332 records the
prior consumer audit.
