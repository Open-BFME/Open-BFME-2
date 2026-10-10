// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native1ED70C..1ED840 complete308B constructor; allocatedF4 by Miles
// constructor5CF5F. Native unwind states0..29 establish42 individually
// constructed four-byte owning handles, followed by five-handle arrayA8 and
// fourteen trailing handlesBC. Each uses existing null-check Release_Ref
// destructor10F149. No original complete-class name or field purpose claimed.
class OpaqueRefCounted;
class BfmeStringTailRecord156 {
public:__forceinline BfmeStringTailRecord156():referent(0){}~BfmeStringTailRecord156();
private:OpaqueRefCounted *referent;
};
class Rva001ED70C {
 BfmeStringTailRecord156 field00;
 BfmeStringTailRecord156 field04;
 BfmeStringTailRecord156 field08;
 BfmeStringTailRecord156 field0C;
 BfmeStringTailRecord156 field10;
 BfmeStringTailRecord156 field14;
 BfmeStringTailRecord156 field18;
 BfmeStringTailRecord156 field1C;
 BfmeStringTailRecord156 field20;
 BfmeStringTailRecord156 field24;
 BfmeStringTailRecord156 field28;
 BfmeStringTailRecord156 field2C;
 BfmeStringTailRecord156 field30;
 BfmeStringTailRecord156 field34;
 BfmeStringTailRecord156 field38;
 BfmeStringTailRecord156 field3C;
 BfmeStringTailRecord156 field40;
 BfmeStringTailRecord156 field44;
 BfmeStringTailRecord156 field48;
 BfmeStringTailRecord156 field4C;
 BfmeStringTailRecord156 field50;
 BfmeStringTailRecord156 field54;
 BfmeStringTailRecord156 field58;
 BfmeStringTailRecord156 field5C;
 BfmeStringTailRecord156 field60;
 BfmeStringTailRecord156 field64;
 BfmeStringTailRecord156 field68;
 BfmeStringTailRecord156 field6C;
 BfmeStringTailRecord156 field70;
 BfmeStringTailRecord156 field74;
 BfmeStringTailRecord156 field78;
 BfmeStringTailRecord156 field7C;
 BfmeStringTailRecord156 field80;
 BfmeStringTailRecord156 field84;
 BfmeStringTailRecord156 field88;
 BfmeStringTailRecord156 field8C;
 BfmeStringTailRecord156 field90;
 BfmeStringTailRecord156 field94;
 BfmeStringTailRecord156 field98;
 BfmeStringTailRecord156 field9C;
 BfmeStringTailRecord156 fieldA0;
 BfmeStringTailRecord156 fieldA4;
 BfmeStringTailRecord156 namesA8[5];
 BfmeStringTailRecord156 fieldBC;
 BfmeStringTailRecord156 fieldC0;
 BfmeStringTailRecord156 fieldC4;
 BfmeStringTailRecord156 fieldC8;
 BfmeStringTailRecord156 fieldCC;
 BfmeStringTailRecord156 fieldD0;
 BfmeStringTailRecord156 fieldD4;
 BfmeStringTailRecord156 fieldD8;
 BfmeStringTailRecord156 fieldDC;
 BfmeStringTailRecord156 fieldE0;
 BfmeStringTailRecord156 fieldE4;
 BfmeStringTailRecord156 fieldE8;
 BfmeStringTailRecord156 fieldEC;
 BfmeStringTailRecord156 fieldF0;
public:Rva001ED70C();
};
typedef char SecondarySize[sizeof(Rva001ED70C)==0xF4?1:-1];
Rva001ED70C::Rva001ED70C() {}
