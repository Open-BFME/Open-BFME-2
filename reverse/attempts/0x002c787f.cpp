// ?getVictimAntiMask@@YAHPBVObject@@@Z
// partial score=0.99 date=2026-10-08
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
struct NativeWeaponKinds { char pad[0x108]; unsigned k108,k10C,k110; };
class Object { public: char pad0[4]; NativeWeaponKinds *m_template; char pad8[0x94-8]; unsigned m_status; };
__forceinline bool nativeBit(const void *mask,unsigned bit) { return (static_cast<const unsigned *>(mask)[bit>>5]>>(bit&31))&1; }
__declspec(noinline) static int getVictimAntiMask(const Object *victim)
{
 NativeWeaponKinds *t=victim->m_template;
 unsigned a=t->k10C;
 if(a&0x800000) return 0x12;
 if(a&0x100000) return 8;
 unsigned b=t->k110;
 if(b&0x800) return 0x40;
 unsigned c=t->k108;
 if(c&0x2000000) return 4;
 if(nativeBit(&victim->m_status,6)) {
   if(c&0x200) return 1;
   if(c&0x100) return 0x20;
   if(c&0x400) return 0x200;
   return (b>>7)&0x80;
 }
 return ((c&0x80)|1)*2;
}
class WeaponSet { public: unsigned nativeLead(const Object *); };
unsigned WeaponSet::nativeLead(const Object *v) { return v ? getVictimAntiMask(v) : 2; }
