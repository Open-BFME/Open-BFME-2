# GameSpy tree member header adoption

Inspected base:2978028b46. The served Rva0038404A header has two remaining
queued users: the GameSpyInfo destructor view and the tree destructor provider.
No donor was consulted; names remain address-derived.

The GameSpyInfo view now includes the canonical12B tree header in place of its
one-byte destructor-only class. Removing the obsolete eleven-byte padding
after each member preserves receivers+34/+40 and the following map at+4C.
Normal verification passes25/25 bodies, all funclet bindings, and the one EH
graph is EXACT. Frozen-file checks pass, a strict reusable receipt is current,
and link_check's own verdict is LINKS386->386 authored bytes at index138c18d3c9.
header_adopt_lane.py accept retires exactly this consumer's one queue row.
The shared header and provider source are unchanged; no path/pin/name changes.

A private provider experiment replaces the holder member with the canonical
pointer field and a local RAII guard holding void*&. The guard reads the head
after clear on both normal and exception paths. All218 code rows, including
the native56B destructor385BE1, still match, but EH verification passes only
78/79 graphs: one byte differs in the unwind action at77FA57 (.text$x).
This is not an acceptable adoption. The candidate is banked as a reproducible
[patch against the unchanged provider](gamespy-tree-provider-reference-guard-20261109.patch);
the provider's original source and queue row remain. Native holder cleanup
representation is still required. No overlapping object lifetime, assembly,
hand alias, header change or nonmatching Code body was introduced.

The first log entry incorrectly treated this cleanup as a new-body partial.
check_csv correctly refuses a body stash for an already-landed address. That
classification was corrected through re_log.py: the existing body stays landed,
the header task is blocked, and its patch belongs in attempt_support. The file
placement check also correctly disallows adding a standalone .cpp there;
the patch preserves the experiment without adding a game source outside Code.
Its zero-context hunks validate with git apply --unidiff-zero --check; do not
apply the known nonmatching experiment to Code as a recovery.

Reproduction and JSON/log receipts: build/tree-gamespy-header-20261109/.
The consumer's other queued class, GameSpyStagingRoom, remains separate work.
These are source/debt checks and local link previews, not an image/run result.

Publication carry-forward: Banner recovery2978028b46 landed on attempt2.
Its broad link audit was INCONCLUSIVE at index138c18d3c9/base5e962f046d:
two unchanged objects lacked current receipts, first FXParticleSystemFactories.
Its own four sources passed LINKS. Keep those consumer-selection gaps for the
next maintained census/image. Its shadow identity check also reports two
pre-existing-shaped vector-base bindings in BannerCarrierUpdateModuleData's
constructor at211E58; no identity clearance is inferred from the byte gate.

## Same-file GameSpyStagingRoom follow-up

The tree consumer landed as1e0712eda9 on attempt3; its broad audit remains
INCONCLUSIVE for unchanged AIRingHeroTactic.cpp's missing current receipt
(index138c18d3c9; the final outgoing base was3009b2d4fc). No image claim.

The consumer's final queued class is now adopted too. GameSpyStagingRoom.h
replaces its four-byte destructor-only view. The actual member starts at5E4
and occupies1020 bytes, ending at1604; retaining four padding bytes keeps the
following member at1608. Normal25/25, the exact EH graph and frozen checks
pass; link_check again says LINKS386->386. The owning acceptance tool retires
one GameSpyStagingRoom queue row. No header-debt rows remain for this file.
Neither shared header changed. The tree destructor provider and its one-byte
unwind mismatch remain the separate follow-up described above.

## Owning member lifetime recovered

The provider follow-up restores the actual cleanup-bearing first member.
RvaTreeFamilyHolder now has one shared four-byte declaration; its existing
inline destructor definition stays in RvaTreeDtorFamily.cpp, preserving the
native14B provider at7FAB3. Rva0038404A keeps its field name m_00Head, but its
type is now the holder. Count+4, opaque+8 and sizeof12 are unchanged. The
clear provider's six pointer expressions use m_00Head.m_ptr. The other holder
declaration in StlportPod248ElementDtor.cpp is reconciled with the shared
declaration too. Its enclosing tree destructor was already out of line.

This is a real member lifetime, with no overlay or local cleanup surrogate.
The private provider preserves218/218 bodies and all79 EH graphs, including
the previously differing action77FA57. Applied normal verification over the
header tool's entire18-source closure passes855/855 bodies,32 data rows,
77 string references,14 floats,11 imports and140 EXACT EH graphs. Its own
link preview reports18/18 LINKS,34306->34306 authored bytes. Frozen checks
are clean. Owning acceptance retires Rva0038404A's final provider queue row;
no header-debt row remains for that class.

The old contract recorded size8 from historical private copies. The default
contract CLI now finds no compiled private view and was restored after its
empty proposal. class_contract.decide's explicit-source API reads a scratch
probe containing the exact canonical declaration instead. Its compiler-backed
contract records class/sizeof12, the holder+0 and count+4, with one view and no
undecided attribute; those counts describe the probe, not recovered retail TUs.
The existing native stride/offset evidence in the canonical header independently
supports the extent. No original container identity or member spelling is claimed.

Scratch receipts and probe inputs: build/tree-gamespy-header-20261109/member-lifetime/.
The earlier reference-guard patch remains historical failed-attempt evidence.
The three other queued provider classes in RvaTreeDtorFamily remain separate
work; this repair does not clear their lifetime/constructor prerequisites or
claim a new image/runtime result.
