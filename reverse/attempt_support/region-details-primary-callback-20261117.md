# Region-details primary callback ownership

Native constructor5CC698 and destructor5CC788 install direct table874EE0;
slot0 is5CC7DC. The parent's874E6C slot0 is the distinct emptyB3FD0, so the
callback belongs to Rva005CC698 rather than Rva005CC5E5. Its proven holder8
contains the pointer forwarded to the existing Rva005E3266 method. The whole
8 bytes and tail-call target match the independent PointerFieldForwarders
provider. Constructor, destructor and descendant-constructor views now
all declare this override. Normal whole-cohort verification is16/16; no pin
or linker alias is added. Existing coverage is retained.

Descendant table8751B4 starts with the same5CC7DC callback, followed by
5CE9BF,5CE9B4,5CF703,5CF22C,5CF6B5,5CEA11. Parent874EE0 has six purecall
entries after slot0. The descendant's six bodies establish a route to the
missing interface, but their current placeholder providers are not yet
admitted as class callbacks. The5CEA11 provider's file is claimed elsewhere.
No incomplete pure-slot expansion or invented method identity is retained.
The seven-slot table bridge pass test awaits completed interface work and
an actual later published real-link receipt.

Private three-source evidence: continuation-20261117d-cc-slot0-results.json
under build/; ordinary build: continuation-20261117d-cc-slot0-build.log.

Descendant slot1 is now recovered at5CE9BF: source+C then target+4,
followed by the existing5E6826 forwarder. Whole child source passes7/7.

Descendant slot2 is independently recovered at5CE9B4 through the same
source-record target and existing5E681E forwarder. Whole child source8/8.
