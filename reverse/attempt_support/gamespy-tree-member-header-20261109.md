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
