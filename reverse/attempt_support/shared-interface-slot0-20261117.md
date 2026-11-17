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
