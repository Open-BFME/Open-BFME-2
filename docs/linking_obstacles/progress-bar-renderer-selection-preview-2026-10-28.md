### Progress-bar renderer selection preview (2026-10-28)

Status: existing renderer repair verified for this consumer; census confirmation
pending. At base `f262472e206f` and index `d92e7e6635`, W3DProgressBar.cpp
alone reports the selected PendingSurfaceStruct deleting destructor. Including
the current Render2DSentenceDrawBFME2.cpp in the same preview changes the
progress-bar unit to LINKS for 1,411 authored bytes. The renderer remains
blocked on its separate Add_Quad selected copy. Carry both units and their
selected providers into the next scheduled census; this preview does not
claim a measured linking gain. LINK-132 remains open.
