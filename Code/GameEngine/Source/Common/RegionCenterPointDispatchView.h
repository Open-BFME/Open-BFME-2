#ifndef BFME2_REGION_CENTER_POINT_DISPATCH_VIEW_H
#define BFME2_REGION_CENTER_POINT_DISPATCH_VIEW_H
// Native 0x0020F27E: region index and an output pointer passed as a32-bit
// word; RET8 and a Boolean result. WB names the operation GetRegionCenterPoint.
// The existing neutral spelling and call ABI are shared by all consumers.
class Rva0020F27EHost { public: bool rva0020F27E(int index, int output); };
#endif
