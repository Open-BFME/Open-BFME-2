// ?rva002B768F@LivingWorldLogic@@QAEXXZ
// partial score=0.88 date=2026-10-08
// cl: /O1 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Integrate into existing LivingWorldLogic.cpp; declare rva002B768F and
// Rva003F287F::rva003F287F(vector<const ModuleData*>&).
// Native predicate2B3484 uses banked Rva002B3484/Arg24 spelling; admit
// its true address with pin_admission if recovering this caller.
// Existing address-derived predicate/setter providers; item identity unknown.
struct Arg24;
class Rva002B3484 {
public:
 Bool rva002B3484(Arg24 *item);
};
class Rva004E071D {
public:
 void rva004E071D(Bool value);
};

// Native 0x002B768F..0x002B778A: selected player's owned entries receive
// the predicate result through 0x004E071D. Boundary is the full EH body
// between neighboring returns. Public method name remains unresolved.
void LivingWorldLogic::rva002B768F()
{
 if (m_localPlayer != 0)
 {
  const Rva002B5334ArmyList *list = m_field0B0->m_armySet;
  if (list != 0)
  {
   _STL::vector<const ModuleData *> items;
   for (UnsignedInt i = 0; i < list->m_armies.size(); ++i)
   {
    Rva003F287F *region = (Rva003F287F *)list->m_armies[i];
    if (((Rva002B4C35Player *)m_localPlayer)->m_id == region->m_ownerPlayer)
    {
     ((_STL::vector<void *> *)&items)->clear();
     region->rva003F287F(items);
     for (UnsignedInt j = 0; j < items.size(); ++j)
     {
      const ModuleData *item = items[j];
      Bool enabled = ((Rva002B3484 *)this)->rva002B3484((Arg24 *)item);
      ((Rva004E071D *)item)->rva004E071D(enabled);
     }
    }
   }
  }
 }
}
