// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native complete body 28C0E3..28C0F2: forward the first stack argument,
// adjust the interface receiver by -0x70, call rowed Object geometry test
// 28B35B and return while removing three 4-byte arguments. AL is passed through.
// BFC290 table slot +20 independently contains this entry; existing constructor
// 298EA9 / destructor 299CE4 evidence places that interface at Object+70.
// Accepted runtime packet (archive SHA256 3d974bf055b14b83983430e6ed98de423a60901217b4b9cd815c5b1b401e41b9)
// confirms a transfer from 758E87 through that slot. This packet proves a call
// relationship, not an original method name. Unsigned arguments below describe
// only the two ignored 4-byte ABI slots; their original types remain unknown.
class Object { public: bool rva0028B35B(const Object *) const; };
class Rva0028C0E3Receiver { public: bool geometryTest(const Object *,unsigned,unsigned) const; };
bool Rva0028C0E3Receiver::geometryTest(const Object *other,unsigned,unsigned) const {
 return ((const Object *)((const char *)this-0x70))->rva0028B35B(other);
}
