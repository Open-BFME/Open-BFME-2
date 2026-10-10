# SelectGameWindowHotKeyAction::doInvoke

Target facts: game.dat 0x0053DA75..0x0053DAD0 is a complete 91-byte
thiscall body ending in `ret 4`. WorldBuilder's complete 371-byte body at
0x01134230 names this method and the official
GameClient/Gui/SelectGameWindowHotKeyAction.cpp source (assert lines 43..46).
Its two getters, instance null check, message selection, virtual dispatch and
boolean result correspond to retail. This independently supports the identity;
the discarded GadgetCheckBoxToggle queue pairing does not.

Retail proves the window pointer at receiver+8, the owner pointer at
instance+0x14, and the four-argument manager call through vtable+0xE8. The
retail table at RVA0x00869310 places doInvoke in slot3. The other three slots
and the prefix word are left opaque. The declaration-only manager dispatch
view is never instantiated; the actual global remains
`class GameWindowManager; extern GameWindowManager *TheWindowManager`.
GameWindow getter declarations use the existing real provider names, including
the WinInstanceData class return type. No new pin or emission anchor is needed.

The former bank's cached manager pointer moved the native reload across
winGetWindowId. Calling through the canonical global expression preserves
the independently observed load and argument evaluation order. Isolated
compiler trials gave 88B and84B for the prior forms, then91B exact for the
global expression, WB ordering and the named virtual class declaration.
Normal tools/add_match.py verified the named source's complete91B with all
relocations resolved and cleared the old bank. The freeze guard reports all
definitions matched. The original boolean parameter's source meaning remains
unknown; the neutral name `flag` preserves that uncertainty.

The ordinary `tools/link_census.py --build --measure` run on fixed
d68a97b48f finished successfully on2026-10-10 at12:00UTC. It witnessed8,908
fresh compiles and linked21,828 objects, with70 data rows byte-verified and
no missing objects. Both the generated status and public `tools/link_check.py`
report this source LINKS with91 bytes and zero blockers. The measured status,
immutable index and original run output are preserved under ignored
build/reference-pass16/hotkey-current-census/. The diagnostic measurement
does not alter the published census history; unrelated repository blockers
remain separately reported there.

Source and class reservations were pushed with stable owner
codex-01a1071d-file-recovery before the Code edit. Reconstruction used target
bytes and named WorldBuilder evidence, not a BFME1 donor. Private trial receipts
remain under ignored build/reference-pass16/hotkey-91-private/. No C++ progress
is claimed from private trial outputs.

## Status-query slot1

Retail53DA53..53DA64 is a complete17B body ending in RET4. The same target
vftable places it in slot1; the existing constructor at53DAD0 installs this
table and the window pointer at+8. The body calls the actual already-rowed
GameWindow::winGetStatus at30F45F and returns `(status >>4)&1` in full EAX.
The original method name and the unused stack word's original source type
remain unknown. The neutral RVA-owned method and unsigned word describe the
observed physical ABI without claiming an original API. Reference HIDDEN=0x10
is a donor semantic lead, not an independently established target name.
The source declares opaque slots without emitting a vftable or extra bodies.
The pushed body reservation predates this edit. Normal add_match verified
both full bodies2/2; ordinary link_check against the fresh census reports
LINKS91->108 with zero blockers. Neither check required a new callee pin.

## Status-query slot2 and file closure

Retail53DA64..53DA75 independently proves the second full17B RET4 body,
vftable slot2 and the same window+8/getter30F45F access. Its full EAX result
is `(status >>3)&1`. The neutral method and unused physical word retain the
same original-name/type uncertainty; reference ENABLED=0x08 is donor-only.
Normal add_match verified all three complete bodies3/3. Ordinary link_check
reports LINKS91->125 with zero blockers. The object's only new defined
functions are these recovered methods; no opaque method or vftable is emitted.
Both independent17B siblings are kept as their own verified commits.
Supported unconverted bodies in this owned home: zero. The already-matched
constructor and destructor in other homes are not counted as new coverage.
