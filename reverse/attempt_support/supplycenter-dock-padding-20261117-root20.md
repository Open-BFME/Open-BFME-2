# SupplyCenter unused-padding adoption false reject

Inspected 80848a58e08669410010d64d6a40ec90eb30554e on 2026-11-17. Source is restored byte-for-byte to the archived original. Its10rows and twoEHparents still pass; no adoption or queue retirement is claimed.

The private DockUpdateModuleData has a virtual pointer and unused unsigned-char m_basePad[12] at+4, total16bytes. The canonical16-byte prefix instead exposes inherited tag+4, approach count+8, passthrough byte+0C and finalpadding. SupplyCenter fields stay+10/+14/+18, total0x1C. The identifier occurs once, only in its declaration; no one-to-one canonicalfield spans those12bytes.

Preparation selects canonical ModuleData BEFORE ObjectModule.h to choose the native Snapshot name slot and exposes inline ModuleData::~ModuleData(){} before Dock's header to preserve7B teardown instead of a5Btailjump. That preparation passes10/10 but is not a successful adoption and was reverted. The owning adoption tool refuses the unused array because tu_views.PAD recognizes m_pad, not m_basePad. The array was not renamed to satisfy that heuristic.

A separate tooling task must prove unused byte-array storage coverage without admitting inline-body references, active access, address/sizeof uses, macro ambiguity, unions or incorrect extents. View.pad_used alone scans outside the class body and is insufficient. Keep existing shadow/include/layout and runtime-binding checks. After a verified fix lands, retry the actual adoption, strict provider context and peer/table audits.
