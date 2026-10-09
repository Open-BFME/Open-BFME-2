// cl: /O1 /G7 /MD /DNDEBUG
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
class Rva002195E6 { public: __declspec(nothrow) Rva002195E6(); unsigned char data[0x6C]; };
class CreateAHeroManager {
public:
 class CreateAHeroSubClass {};
 class CreateAHeroClass { friend class CreateAHeroManager; private:const CreateAHeroSubClass *rva00219B9E(unsigned) const; char data[0x20]; };
 const Rva002195E6 *GetViewInfo(unsigned,unsigned);
 char prefix[0x14C]; CreateAHeroClass *begin,*end,*capacity;
};
const Rva002195E6 *CreateAHeroManager::GetViewInfo(unsigned c,unsigned s){
 static Rva002195E6 fallback;
 if(c>=(unsigned)(((char *)end-(char *)begin)>>5))return &fallback;
 _ReadWriteBarrier();
 const CreateAHeroSubClass *p=begin[c].rva00219B9E(s);
 if(!p)return &fallback;
 return reinterpret_cast<const Rva002195E6 *>((const char *)p+0x6C);
}

// Identity: WB B7AF90 asserts GetViewInfo at CreateAHero.cpp1468/1471;
// target219F36..219F8E RET8 and AptMyHero callers5B0473/5B0487 agree.
// Layout: target manager vector14C/150 stride20 and native subclass lookup
// 219B9E (private member) prove the class path; view offset6C and ctor2195E6
// establish the opaque6C record. Original record/type field names unknown.
// Native lazy default has guardDFE3DC/objectDFE370 and no destructor callback.
// Existing sibling getter barrier prevents cached begin/early receiver-pop.
