# GameWindow native slot2 owner and callback ABI

Target evidence: GameWindow's rowed constructor3145F0 and destructor314A0C
select tableC0BBCC; its slot2 is the complete35-byte body at104E45. That
body reads callback+1E4, guards null, invokes it with the window plus three
stack words, and returns zero when unset. The neighboring input body uses
+1E0. These are target facts, not proof of an original method identifier.

The old nonvirtual BfmeThingEHCb owner is withdrawn and tombstoned. Its
existing identifier bfmeGoEHCb is deliberately retained on GameWindow. The
implementation stays in BfmeConv812_bfmeGoEHC.cpp: this address's current TU
map is proposed, not approved, so no source move is performed. The existing
message-word/handled-enum callback view is a structural ABI choice, not a
newly established original declaration. The11-slot prefix includes the
vptr; the callback remains at+1E4. No asm, pin, global or compiler override.

Both current GameWindow table emitters now reference the proper emitted
virtual member at slot2 instead of purecall. Ordinary admission verifies
the whole35-byte member; all114 rows in the four-source cohort pass, and
all three edited sources pass frozen-definition checks. The joint preview
is4/4 LINKS against index73061d9452, retaining4171 authored per-source
bytes; overlapping ICF rows are not unique-byte gains. Its historical
3922-to-4171 printout predates this repair. No census-linked-byte, unique
matched-byte or image ownership gain is claimed.

Remaining native table gaps are slots6,8,9,10. Slot7 is genuinely pure.
The old input helper remains because two gadget constructor units still
bind its decorated name; their existing real GameWindow::input provider
is known, but rebinding and retirement require their own claims and gates.
This pass does not recover the original system-method name or the complete
GameWindow data object. Whole-batch closure still needs complete census
consumer metadata. Model GPT-6; t=12; lane=R; budget=30m.
