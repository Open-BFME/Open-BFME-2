# Four remaining AIUpdateInterface consumer prerequisites

At base 1b7a6e99402, the eleven queued original files pass 482 function rows
and 27 data rows. Seven consumer adoptions are retained separately. The four
files below retain their originals and their queue entries. AIUpdate.h and all
shared headers remain unchanged. No partial body, pin, table or escape hatch is
banked for these failures.

## GameLogic.cpp

The fake four-byte LocomotorSet and private UpdateModule views can be mapped to
the existing canonical set at AI+0x1CC and scheduler words at +0x14/+0x18/+0x1C.
Keep the raw unsigned frame word, 0x3fffffff clamp, original store order, and
null-aware -0x10 update-interface downcasts. The phase queries must remain
primary slot 12 (+0x30); cached phase is not a replacement, because post-load
clears it before querying. Earlier log entry 96212 caught a +0x2C substitution.

Canonical getUpdatePhase is protected. A legal access-only derived declaration
and member-pointer conversion compile after placing the conversion inside that
type. The resulting candidate retains 170/172 rows, but changes the 340-byte
Rva00242D1DLoadView::loadPostProcess and 203-byte GameLogic::registerObject.
It emits a new `??_9@$BDA@AE` virtual-call thunk and phaseMember helper. Those
are rejected; the original source is restored and verifies 172/172 plus all
four data rows. The JSON records the exact COMDAT difference.

Next prerequisite: reconcile canonical phase access and actual caller ownership
without new thunks or a surrogate object cast. Do not replace dispatch with the
cached phase or call the out-of-line frame helper in originally inline code.

## GameLogicInit.cpp

AI usage is pointer-only and calls the existing isMoving/destroyPath methods.
The file also declares private BehaviorModule, UpdateModuleInterface and
UpdateModule views. Canonical fields can express the index/frame operations,
but protected ObjectModule::getObject has no public canonical equivalent.
Canonical BitFlags<11> lacks test(const void*) and anyIntersectionWith.
The actual 37-byte test provider exists at RVA0x0023C59F in BitFlags11Test.cpp;
it needs a correct canonical declaration, not a new provider or pin. Preserve
the hidden-result mask temporary and the `that.test(this)` receiver direction.

The original codemod reports STLport /usr/include/pthread.h, a Sun/HP compiler
branch. That scanner diagnostic is not evidence of an MSVC compiler failure and
does not remove the concrete module/mask prerequisites above.

## W3DMouse.cpp and W3DView.cpp

Both use a declaration-only WorkerAIUpdate view and have no necessary direct AI
storage rewrite. Whole-file substitution nevertheless introduces duplicate
AsciiString and Coord3D declarations from their existing upstream headers and
the native canonical headers. Mouse also has an incompatible BitFlags template
parameter declaration, invalidating BitFlags<11>, and StringBase lifetime access
errors. Normal paired validation refuses all sixteen data rows because the
sources do not compile. Owning TU-verifier diagnostics confirm the exact errors;
this is not evidence that the original data bytes were wrong. Both original
sources are restored. Do not suppress declarations with a new macro escape.

Next prerequisite: reconcile the full-file string/coordinate/template ownership
before repeating this fixed-header adoption. Do not infer type identity or full
layout merely from the current matched bytes or a same-name declaration.
