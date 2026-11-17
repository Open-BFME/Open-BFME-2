# Native base and derived callback ownership

The picker serves nine bridged tables in Rva005CDVirtualDtors.cpp. Native
vptr stores, not the old consumer aliases, establish the following bindings:

| Installed table | Callback | Adjustment |
| --- | --- | --- |
| Base 0x00C77D08 / 0x00C77D04 | 0x005E549E, eight bytes | 0x005E54A6, eight bytes |
| Derived 0x00C75020 / 0x00C7501C | 0x005E5554, seventeen bytes | 0x005CDA53, eight bytes |

The base destructor at 0x005E4F6D installs the first pair. The derived
destructor at 0x005E54F7 installs the second pair. Slot one of both direct
tables is the existing eight-byte owned-pointer dispatch at 0x005E415F.

The initial session commits attributed 0x005E5554 and 0x005CDA53 too broadly
to Rva005E4F6D::slot0, following the pre-existing consumer alias. The expanded
native-table audit disproves that base attribution. Those two session-owned
rows and their misplaced definition are retracted in a separate reviewable
commit. Their original step/thunk owners retain every byte and relocation;
the ordinary three-source retraction build passes all 92 remaining rows.
The corresponding attempt verdicts are explicitly voided.

The corrected C++ split privately verifies twenty rows. The base callback
reads its already-proven child.value at +0x10 and calls 0x005E5424. The
Rva005E54F7 override calls that base callback and then the existing run
provider at 0x005F327A through the complete receiver. An outlined base body
preserves the CALL that native 0x005E5554 makes to 0x005E549E. MSVC naturally
emits both secondary-base adjustments. These corrected bindings are to be
banked individually after the retraction. The correct base callback at
0x005E549E is now admitted against its original owner, with the existing
Rva005E39AE header declaring the already-rowed callee. The native call
boundary is retained with noinline on this outlined eight-byte method.

The base adjustment at 0x005E54A6 is also banked naturally. The derived
override is then restored under Rva005E54F7::slot0, with that override declared
in both the destructor and StrategicInGameUI views. The ordinary two-source
build verifies 89/89 rows before the derived adjustment's separate admission.
The qualified base call avoids an explicit nullable pointer conversion and
matches retail's seventeen-byte body directly.

The derived adjustment at 0x005CDA53 is separately admitted under
Rva005E54F7::slot0. The final ordinary build passes 90/90 rows across the
twenty-row destructor/provider unit and seventy-row consumer. Each base or
derived body and each adjustment has its own commit after the reviewable
retraction. This corrects the class attribution rather than preserving the
old alias's overly broad assumption.

Slot one is already correctly rowed against its existing eight-byte helper.
Both obsolete consumer alternatename directives have been removed. The
consumer's seventy rows, thirteen EH graphs and eighty-six COMDATs remain
identical. The global hatch register was claimed by another worker, so its
old allowances remain untouched. No new alias or pin was added.

Current-object pointer checks of the nine queued table names exposed the
ownership distinction above and further derived-specific overrides. Only a
later published real-link receipt can establish bridge retirement. No real
link, smoke, nightly or shadow publisher was started for this work.

The next derived owner, Rva005E6F9D, privately matches its twenty-byte slot0
at 0x005E6B8F and emits the eight-byte secondary adjustment at 0x005CDE79
(the latter still needs a named row for relocation resolution). However,
declaring that override stops emitting the already-banked base adjustment
0x005E54A6 in this mixed destructor source. Its real base constructor and
destructor live in Rva005E4F6DConstructor.cpp. No artificial emitter, new
alias or unverified override was retained. A fresh tu_skeleton merge dry run
for StrategicInGameUI.cpp refuses fewer than two donors and lists the
constructor source as mixed; proper ownership consolidation remains needed.
Scratch evidence: build/continuation-20261117c-e6-slot0-probe.json.

The independent Rva005E54F7 icon-background notification is now recovered
under its real inherited interface name. Native tables C77D20 and C75028
select 0x005E5575: the nineteen-byte body calls the existing +8 shared
interface provider at 0x005E509F, then the empty ArmyDetailsMovieClip base
notification. The compiler matches both REL32 targets. Both destructor and
consumer views declare the override. The neighboring sixteen-byte back-button
notification also matches privately with a fourth primary virtual slot; that
empty slot is folded at 0x000B3FD0, currently claimed by another worker, so
neither it nor the back-button override is applied. These private successes
are prerequisites, not banked rows or measured bridge retirement.

The sibling Rva005E6F9D icon-background override at 0x005E6894 is
independently recovered with its constructor-proven +C shared interface.
Retail C77E5C (the class's own primary table) and C750A0 (its descendant)
both select it in slot2. The ordinary paired build passes 92/92 rows,
including the original standalone nineteen-byte owner retained in the
consumer. Both call relocations agree. This adds a native class binding,
not new unique authored bytes, and still awaits a published real-link pass.

Primary slot3 at 0x005E6A00 is independently banked (ordinary93/93 paired
rows). Its seventeen-byte body retains the native empty call and tail-calls
the +20 owned listener's existing 0x005E69AC provider. Original slot names
remain unknown. The twelve-byte primary parent's native table C796D0 has
six entries (deleting destructor plus five empty callbacks); its short
current view exposes three. Full parent-slot recovery still needs the
claimed 0x000B3FD0 contract, so these derived positional bindings do not
claim that the parent's complete interface is recovered.

The seventeen-byte slot4/slot5 candidates also match privately. Slot4's
ordinary94/94 build passed, but its commit gate correctly rejected the
second row at audited-single-owner 0x005E6BB4. The session's uncommitted
lines and pending row were removed exactly, and its automatic landed
attempt verdict was voided. Slot5 at 0x005E6BA3 has the same audited-owner
restriction and was not applied. Existing owners and body_owners.csv stay
intact. These need proper consolidation and semantic ownership review,
not another ICF row or an artificial alias. The verified93-row publicable
state is retained. All nine served table names have explicit current
handoffs; native bytes alone do not complete their real-link pass test.
