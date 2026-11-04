### LINK-237: RefCountClass adoption shifts a private RenderObj hierarchy

Evidence / scope: `Code/GameEngineDevice/Source/W3DDevice/GameClient/RTS3DSceneRenderOneObject.cpp`; [handoff](../../reverse/attempt_support/refcount-renderobj-prerequisite-20261104-1410.md).
Completed: native whole-parent differences isolated to twelve dispatch offsets
increasing by4; the original source is restored and byte-verified. Related
RenderingMethod consumers are reconciled through both existing headers.
Remaining / next check: reconcile this source's extra private inherited slot1
under the real RenderObj destructor/layout evidence, then reverify parent/EH,
all provider/consumer code and linking. class:RenderObjClass is held by another
contributor; no reservation is overridden. No new alias, pin or guessed name.
