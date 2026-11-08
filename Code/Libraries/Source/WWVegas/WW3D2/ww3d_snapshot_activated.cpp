// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// WW3D::Is_Snapshot_Activated, retail 0x00065F60 (6B), unreferenced: the
// out-of-line copy of Zero Hour ww3d.h's header inline, reading the private
// static SnapshotActivated (VA 0x00DEC3FD, defined in ww3d.cpp). The pointer
// anchor (no retail counterpart) only makes this unit emit the inline body.
// WW3DClass.h declares it; this unit supplies the inline body.
#include "WW3DClass.h"

inline bool WW3D::Is_Snapshot_Activated() { return SnapshotActivated; }

extern bool (*const g_bfmeWW3DSnapshotActivatedAnchor)();
bool (*const g_bfmeWW3DSnapshotActivatedAnchor)() = &WW3D::Is_Snapshot_Activated;
