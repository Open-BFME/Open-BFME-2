// cl: /O1 /DNDEBUG /MD /arch:SSE
// Retail0x005084FC186B; vtable00864048 slot14 owned by matched Made002CC5E1
// deleting destructor/constructor. Original method name unknown. This scoped
// view emits the method body only and deliberately does not model the vtable.
// BFME1 b25 DamageNugget generateDamageInfo is the fill-helper semantic lead,
// not this apply wrapper. Nativehelper508120 RET20 receives weapon opaque
// pointer target Object DamageInfo flag and Coord3D position; nativecall2615E3
// establishes lastarg coordinate pointer (not float). DamageInfo ctor263895
// and offsets10/20/70/74 from native loads and matched Object/heal siblings.
// Target healing passes target itself; source bonus healing passes null.
// Bonus tests !=0 (unordered included) whereas final result tests >0.
// Parent correction of uncompiled router artifact; native wrapper5084FC186B.
// DamageInfo local uses already-pinned ctor263895 and actual named attemptDamage.
struct Coord3D;
class DamageInfo
{
public:
 DamageInfo();
 unsigned char pad00[0x10];
 int damageType10;
 unsigned char pad14[0x0C];
 float amount20;
 unsigned char pad24[0x4C];
 float value70;
 float value74;
 unsigned char pad78[4];
};
class Rva005084FCModuleView
{
public:
 unsigned char pad00[0x10B];
 unsigned char flags10B;
};
class Object
{
public:
 void attemptDamage(DamageInfo *info);
 void attemptHealing(float amount, const Object *source);
 unsigned char pad00[4];
 Rva005084FCModuleView *module04;
};
enum ObjectID { INVALID_ID = 0 };
class GameLogic
{
public:
 Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;
struct Rva005084FCWeaponView
{
 unsigned char pad00[8];
 int sourceID08;
};
class Rva00507823
{
public:
 virtual ~Rva00507823();
};
class Made002CC5E1 : public Rva00507823
{
public:
 bool rva005084FC(void *weapon, Object *target, const Coord3D *position);
private:
 unsigned char pad04[0x194 - 4];
 bool flag194;
 unsigned char pad195[3];
 float value198;
 bool rva00508120(void *weapon, Object *target, DamageInfo *info, bool flag, const Coord3D *position);
};
bool Made002CC5E1::rva005084FC(void *weapon, Object *target, const Coord3D *position)
{
 DamageInfo info;
 if (rva00508120(weapon, target, &info, false, position) == true)
 {
  if (info.damageType10 == 7)
   target->attemptHealing(info.amount20, target);
  else
  {
   target->attemptDamage(&info);
   float factor = value198 * info.value70;
   if (flag194)
   {
    if (factor != 0.0f)
    {
     Object *source = TheGameLogic->findObjectByID((ObjectID)static_cast<Rva005084FCWeaponView *>(weapon)->sourceID08);
     if (source && !(source->module04->flags10B & 2))
      source->attemptHealing(factor, 0);
    }
   }
  }
 }
 if (info.value74 > 0.0f)
  return true;
 return false;
}
