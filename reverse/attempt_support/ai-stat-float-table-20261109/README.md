# Float-only table: destructor identity prerequisite, 2026-11-09

The picker served Common/Rva00283081Dtor.cpp at table RVA 0x008615D4.
Retail's entire table is one float getter at 0x00094A94. The current
virtual-destructor-only views put a deleting destructor in that slot;
LINK-514 already records the mismatch. The paired Rva004DFED8 view in
AIStatCollector.cpp shares this address. This is cleanup of provisional
class identities, not missing code coverage.

Native facts: the 4DFC59 constructor installs this table, initializes two
vector members and puts a float at +1C. The existing four-byte getter is
rowed as get@Rva00094A94FloatField. The current destructor84, deleting
wrapper28 and EH handler10 all pass normal strict checks in the served
file. Their existing spellings use a virtual destructor family.

A private hypothesis removes virtual from the destructor, adds a virtual
float getter returning +1C, and retains the two owning vector members.
The compiler emits the native one-slot/four-byte table naturally. Its
getter independently matches retail's four bytes, and its QAE destructor
matches the complete native84 under a temporary in-memory name mapping.
No ledger, pin or live Code edit is made by that experiment. The compiler
does not emit the QAE deleting wrapper from this TU, so the candidate
cannot preserve the current row family by itself. EH spelling/admission
must follow the parent, not a manual independent change.

A scan of aligned .rdata/.data pointer words finds neither native deleting
wrapper address (283246 or 4E005E). That supports the nonvirtual hypothesis
but does not prove original class identity, access, every indirect use or
rule out a deeper base/derived explanation. Byte equality alone is not
an original-source recovery claim.

Bounded native tool review found no supported demotion route: function
--virtual is promotion only; ordinary --respell and --identity reject the
access/header change; class --fold --access only handles virtual access;
retail_identity.py has no reviewed family for either class. A proper
family would carry destructor, deleting wrapper and EH parent together.
The getter can use add_match --icf-owner after complete receiver/slot
evidence, without a new pin, but that alone does not solve the missing
natural wrapper emission or class lifetime model. Do not retract/readd
existing rows, add an artificial emission anchor or hand-add aliases.

Next: inspect the real delete callers and base/derived constructor chain,
establish legitimate nonvirtual wrapper emission/ownership and original
head facts, then review a separate identity-family tooling change with
regression tests. Reconcile every AIStatCollector emitter together and
keep all current rows and EH data exact. No bridge, source, byte-coverage,
image or runtime progress is claimed by this handoff. The live file is
unchanged; the private candidate is evidence only.
