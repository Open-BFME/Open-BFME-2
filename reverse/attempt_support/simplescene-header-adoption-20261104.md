# SimpleSceneClass.h adoption: 2 of 7 units done, 5 walled (2026-11-04)

Adopted (header_adopt_lane accept): SimpleSceneCreateIterator.cpp (RenderList +0x5C,
Head.Next) and SimpleSceneClass_Post_Render_Processing.cpp (ReleaseList +0xA4); 3/3 rows
byte-matched, both still LINK.

Remaining queue rows, target facts and the wall each hits:

- WW3D2/SimpleSceneClassConstructorBFME2.cpp and Common/Rva006ED6FDtor.cpp include rendobj.h
  (and camera.h/dx8wrapper.h), which pull the donor refcount.h/multilist.h; the canonical
  header's RefCountData.h/GenericMultiListClass.h then fail C2011. Same prerequisite as the
  IndexBufferClass entry (docs/linking_obstacles/index-buffer-canonical-prerequisites-20261103-1638.md):
  rendobj.h's stack must see the canonical RefCountClass first.
- WW3D2/SimpleSceneClass_dtor.cpp: retail 0x00141DF0 inlines the empty SceneClass and
  RefCountClass destructors (RefCountClass table restored at 0x00141ED7, no SceneClass store);
  SimpleSceneClass.h and RefCountData.h declare both out of line, and no ??1SceneClass row exists
  (its body folds onto 0x00724510). The unwind funclet's pinned ??1BfmeSceneBase layer has no
  canonical counterpart. Needs an inline ~SceneClass decision in the header (full gate) plus the
  refcount prerequisite.
- Common/W3DAptComponentView3D.cpp: C1083 inside the 1237-line Apt TU; LINK-191.
- W3DDevice/GameClient/Rva001041BDASlot1.cpp: one-slot private view vs the 28-slot table
  (LINK-177 item on cause 18befef11f).
