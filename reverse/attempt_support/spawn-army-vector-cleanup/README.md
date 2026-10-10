SpawnArmy existing source linking repair
=======================================

Target facts: LivingWorldCampaignObjects.cpp owns fourteen fully matched rows
(1545 unique bytes), including the native88-byte SpawnArmy record, title176,
image208/portrait211, parser135 and MoveCamera parser110. The current object
previously had six losing AsciiString/vector destruction COMDATs.

Declare the actual existing vector<AsciiString> destructor instantiation
extern, exactly as OwnedRecord900Copy.cpp already does. This removes the
competing vector destructor and five unused destruction-helper copies while
retaining the native inline StringBase<char>::releaseBuffer calls in all
fourteen bodies. The genuine kept destructor is already owned at2CC70/63B
by StlportAsciiStringVectorDtor.cpp; no new body or pin is needed.

Rejected private alternatives: BFME_ASCII_DTOR_DECL removes five losers;
matching the real provider GX policy also removes the sixth, but introduces
three actual AsciiString-destructor binding findings at native36410 instead
of its real owner48BA39. Those alternatives were not published. The final
extern-template declaration leaves the original EHsc policy and inline
cleanup intact; normal identity checking must confirm zero new findings.

BF1 donor575ba2b04743 reviewed c27be8c759a5/ecdb9d8d3bc3 canonical vector
provider-declaration repairs. They support the provider/consumer approach but
are different vector-copy/assignment bodies; exact destructor ownership is
established independently by the existing BFME2 provider and target bytes.

Supported strict preparation verifies15/15 rows across changed home and
existing real vector-destructor provider. Ordinary known-index prediction
uses the witnessed2026-10-10 11:55 d68a97b48f census, with current prepared
objects: both homes LINK; SpawnArmy0->1545 and vector63->63. This is scoped
current closure, not a new global census. No baseline, shared header, extent,
native ABI, data ownership, helper alias or compiler policy changed.

New C++ exact bytes:0. Newly linking existing unique source bytes:1545.
Source supported open bodies:1 (GetButtonHelp738, reserved for next recovery).
