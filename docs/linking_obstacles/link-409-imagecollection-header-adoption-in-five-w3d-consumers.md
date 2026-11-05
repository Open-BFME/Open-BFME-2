### LINK-409: ImageCollection header adoption in five W3D consumers
Status: Cleared for this five-source adoption scope. Updated: 2026-11-05; inspected revision: 690fe638d473.
Evidence / affected units: W3DControlBar.cpp, W3DPushButton.cpp, W3DAptComponentColorPicker.cpp, W3DGameWindow_initBorders.cpp and Rva0010461FCtor.cpp; [verification and remaining header prerequisite](../../reverse/attempt_support/imagecollection-header-five-20261105-codexb4.md).
Completed: enabled STLport 4.6, replaced private image/collection views and resolved duplicate Image and placement-new declarations; the adoption tool retired five ImageCollection queue rows.
Remaining / next check: the separate Image queue row for W3DPushButton.cpp needs Image.h/ImageClass.h unification; LINK-212's merge prerequisites remain unchanged.
Clearance: 116/116 byte-matched rows; all five ordinary previews LINKS, preserving 18,036 census-linked bytes against 3a95b274a2.
Census confirmation: awaiting a later scheduled census; no new coverage claimed.
