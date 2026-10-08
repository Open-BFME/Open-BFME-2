// ?Open@InGameNotificationBoxMovieClip@@QAEXABVUnicodeString@@ABVInGameNotificationType@@H_NH@Z
// partial score=0.98 date=2026-10-09
// cl: /O1 /Ob1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii
// Notification-box ownership transfer: native004E6BF6..004E6C34 RET4;
// WorldBuilder013238A0 returns a consuming holder through a hidden result.
// Rva004E6A1D clear and Rva004E6A37 destructor/assignment establish the
// existing owner spellings. Copy empties its source before publishing the
// pointer; the returned holder has the independently rowed destructor.
// The original method name is unproven; preserve a neutral address name.
#include "unicode_string.h"
void *__cdecl operator new(unsigned int) throw();
class OpaqueRefCounted;
struct OpaqueRefElement4 {
 OpaqueRefCounted *referent;
 OpaqueRefElement4():referent(0) {}
 ~OpaqueRefElement4();
 OpaqueRefElement4 &operator=(const OpaqueRefElement4 &);
};
class Rva004E6935 {
 public:
 UnicodeString text; int value04; OpaqueRefElement4 ref; UnicodeString label;
 int value10,value14,value18; bool value1C; char unknown1D[3]; int location;
 ~Rva004E6935();
};
class Rva004E6A37 {
public:
 Rva004E6935 *m_ptr;
 Rva004E6A37(Rva004E6935 *p=0):m_ptr(p) {}
 Rva004E6A37(Rva004E6A37 &v) { Rva004E6935 *p=v.m_ptr; v.m_ptr=0; m_ptr=p; }
 ~Rva004E6A37();
 Rva004E6A37 &operator=(Rva004E6A37);
};
class Rva004E6A1D {
public:
 Rva004E6935 *m_ptr;
 Rva004E6A1D(Rva004E6935 *p):m_ptr(p) {}
 ~Rva004E6A1D() {clear();}
 void clear();
 Rva004E6A37 rva004E6BF6();
};
Rva004E6A37 Rva004E6A1D::rva004E6BF6() {
 Rva004E6A37 transfer(m_ptr);
 m_ptr=0;
 return Rva004E6A37(transfer);
}

class InGameNotificationType;
class Rva0047A6A9SelfField { public: const UnicodeString &get() const; };
class Rva005C4AD1LeaField {public: void *get() const;};
class Rva0030F45FDwordField {public: int get() const;private: char pad[8];int value;};
class Rva001DB0A8DwordField {public: int get() const;private: char pad[12];int value;};
class Rva001DB09DDwordField {public: int get() const;};
class InGameNotificationBoxMovieClip {
 public: void Open(const UnicodeString &,const InGameNotificationType &,int,bool,int);
 private: char pad00[0x40];Rva004E6A37 holder40;char pad44[12];bool enabled50;
};
void InGameNotificationBoxMovieClip::Open(const UnicodeString &label,const InGameNotificationType &kind,int value,bool flag,int location) {
 if(!enabled50) return;
 Rva004E6A1D owner(new Rva004E6935);
 Rva004E6935 *record=owner.m_ptr;
 record->text=reinterpret_cast<const Rva0047A6A9SelfField *>(&kind)->get();
 record->ref=*static_cast<const OpaqueRefElement4 *>(reinterpret_cast<const Rva005C4AD1LeaField *>(&kind)->get());
 record->value04=reinterpret_cast<const Rva0030F45FDwordField *>(&kind)->get();
 record->label=label;
 record->value10=reinterpret_cast<const Rva001DB0A8DwordField *>(&kind)->get();
 record->value14=reinterpret_cast<const Rva001DB09DDwordField *>(&kind)->get();
 record->value18=value; record->value1C=flag; record->location=location;
 holder40=Rva004E6A37(owner.rva004E6BF6());
}
