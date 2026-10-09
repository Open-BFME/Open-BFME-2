// cl: /O1 /arch:SSE /DNDEBUG /MD
// BF1 f98983a7d HordeContainAddMemberSyncXP_rva00245b20.cpp is the clean
// semantic guide: index/member storage then carrier update and level sync.
// Target replaces BF1 +1BC/+28 fields with +26C/+24 and direct tracker call.
// Target 00473197..00473212, RET16. Caller 00473212 passes primary HordeContain.
// WB 010C8B90 and the independently owned index/position helpers establish
// banner transfer purpose; original spelling is unknown. Target accesses prove
// owner +8, tracker +264, level +24 and the out-ID word at +26C.
class ThingTemplate;
class ExperienceTracker {
public:
 bool rva0039B4EC(int levels, bool feedback, bool flag);
 char unknown[0x24];
 int level;
};
class Rva003BD306Target {
public:
 void rva0039B2C7(int count, int value);
};
class Object {
public:
 char unknown[0x264];
 ExperienceTracker *tracker;
};
class HordeContain {
public:
 void rva00468E79(int object, int type, bool value);
 int getBannerCarrierIndexToUse(const Object *, const ThingTemplate **);
 void rva00473125(Object *, int *, int);
 void rva00473197(Object *, const Object *, bool, bool);
 char unknown00[8];
 Object *owner;
 char unknown0C[0x26C-0xC];
 int bannerID;
};
void HordeContain::rva00473197(Object *banner, const Object *source, bool flag, bool value)
{
 const ThingTemplate *type = 0;
 int index = getBannerCarrierIndexToUse(source, &type);
 if (index != -1) {
  rva00473125(banner, &bannerID, index);
  rva00468E79((int)banner, (int)type, value);
  if (!flag) owner->tracker->rva0039B4EC(1, true, false);
  int levels = owner->tracker->level - banner->tracker->level;
  reinterpret_cast<Rva003BD306Target *>(banner->tracker)->rva0039B2C7(levels, 0);
 }
}
