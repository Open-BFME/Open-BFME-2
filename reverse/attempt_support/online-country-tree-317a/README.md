# Online login country-table reconciliation

BFME 1 donor revision: `34f59164f6d1efd413c5fd37f4894ec834c3c0fe`.
Semantic donor: `game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/OnlineLoginPopulateCountryList.cpp`.

BFME 2 native `56FEA8..5700A0` retrieves localized Unicode country labels,
stores locale numbers 2 through 37 through `56FE2C`, and reads each node's
Unicode key at +10 and locale word at +14. The map purpose follows the donor;
these offsets, copy/destruction operations and scalar uses follow target bytes.
`int` is the four-byte storage/semantic view, not a claim about retail's original
enum spelling. The table header is 12 bytes and a node is 24 bytes.

Nine existing bodies now share the consistent STLport map/tree view. Five obsolete
private-view units were removed; the other shared instantiation units keep their
unrelated bodies. The existing retail-shaped insertion algorithm is retained.
The native erase operation destroys the pair's only nontrivial member through
the existing UnicodeString destructor, avoiding a second destructor spelling.

`closure.json` records an exploratory comparison of all 18 reachable compiled
bodies and their call targets. Each compares exactly; this read-only probe used
the object produced by explain_mismatch and did not write the shared cache.
Formal build verification covered 36 rows across the reconciled unit and the two
affected shared units. The normal commit hooks additionally verify EH and pins.

Four new names on shared bodies were admitted with the verifier's full
`fold-proof=` check, including every callee and relocation, not masked placement.
An attempted additional node-creator fold pin was refused because the old opaque
placement helper's EH DIR32 slot names a different TU-local symbol. No such pin
was added. The node creator and placement helper were instead reconciled by
renaming their owners to the established pair operations. No verifier code or
exception baseline was changed.

This receipt establishes byte recovery and target ABI evidence. It makes no claim
about link-census gain, game runtime behavior, or completion of the login module.
