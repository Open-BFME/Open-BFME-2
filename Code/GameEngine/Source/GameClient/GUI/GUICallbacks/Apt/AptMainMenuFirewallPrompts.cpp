// cl: /O1 /G7 /arch:SSE /vmg /vmm /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD /ICode/GameEngine/Source /ICode
//
// AptMainMenu firewall confirmation prompts, retail 0x00515FAB (LAN) and
// 0x005160DE (online), 307 bytes each: when the shell has no firewall access
// (rva00514B66 false) raise the two-button "FirewallPopUp" prompt through the
// shared core 0x00437F61 with the two-callback holder (rowed ctor 0x0044BF40,
// OK/Cancel answers bound to rva00514B8D|BA1 and rva00514BB5), else leave the
// menu (state 9, next screen 6 / 10). The outer holder is built by its real ctor
// directly in the argument slot with the receiver first: the pair is passed as
// its dtor-less root view Rva004C5DD0 (rowed copy ctor 0x0044BD00) while the
// derived Rva0044BA4E temp owns the release (W7-S1 holder-ctor lever applied to
// the pair holders). Compiled without /EHsc as the split-TU measurements showed.
// Class views below are private to this unit (names address-derived).
#include "unicode_string.h"

// Screen view: only the members and callbacks these two prompts touch (state
// +0x288 becomes 9, +0x28C names the next screen; the answer callbacks are the
// unnamed rowed members 0x00514B8D, 0x00514BA1 and 0x00514BB5). The virtual
// keeps the vfptr the member-pointer bindings assume.
class AptMainMenu
{
public:
	void LAN(const char *unused);
	void OnlineButtonPressed(const char *unused);
	void rva00514B8D();
	void rva00514BA1();
	void rva00514BB5();
	virtual int rva00514950(int msg, int p1, int p2);

private:
	unsigned char m_pad04[0x288 - 4];
	int m_state; // +0x288
	int m_next; // +0x28C
};

// Native LAN/online entry callbacks share the firewall confirmation protocol.
// These views reuse the rowed 16-byte member binding and two-handle lifetime.
#include "../../../../../../Libraries/Source/Apt/AptRefTarget.h"
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
class __multiple_inheritance FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)();
struct FunctorBinding {
 FunctorTarget *target; unsigned pad; FunctorMethod method;
 FunctorBinding(FunctorMethod functorMethod,FunctorTarget *functorTarget):target(functorTarget),method(functorMethod){}
};
class FunctorWrapperHead {
public:
 FunctorWrapperHead() : m_refCount(0) {}
 virtual void anchor();
 int m_refCount;
};
class Rva0057BC63FunctorWrapper : public FunctorWrapperHead {
public:
 Rva0057BC63FunctorWrapper(const FunctorBinding &binding) : m_binding(binding) {}
 void invoke();
 FunctorBinding m_binding;
};
#include <new>
// The holder constructor (row 0x0057BC63) visible, never inlined: retail's
// compiler knew it only reads the binding (AptOptionsConstructor.cpp).
struct Rva0057BC63FunctorHolder {
 __declspec(noinline) Rva0057BC63FunctorHolder(const FunctorBinding &binding) {
  m_ptr = new Rva0057BC63FunctorWrapper(binding);
  if (m_ptr != 0)
   m_ptr->m_refCount++;
 }
 FunctorWrapperHead *m_ptr;
};
struct Rva004F6986Member {
 TargetRef00217D4C *ptr;
 __forceinline Rva004F6986Member(FunctorBinding binding) {
  reinterpret_cast<Rva0057BC63FunctorHolder *>(this)->Rva0057BC63FunctorHolder::Rva0057BC63FunctorHolder(binding);
 }
 Rva004F6986Member(const Rva004F6986Member &other):ptr(other.ptr){if(ptr)++ptr->references;}
 ~Rva004F6986Member(){if(ptr)ReleaseTreeHintRef00217D4C(ptr);}
};
#include "../../../../../Include/Common/Rva004C5DD0Ref.h"
class Rva004C5DD0 {
public:
 Rva004C5DD0(const Rva004C5DD0 &other);
 Rva004C5DD0Ref *m_00,*m_04;
};
struct Rva0044BA4E : Rva004C5DD0 {
 Rva0044BA4E(Rva004F6986Member,Rva004F6986Member);
 ~Rva0044BA4E();
};
struct Rva0044BEB9;
struct Rva0044BF40 {
 TargetRef00217D4C *ptr;
 Rva0044BF40(Rva004C5DD0 pair);
 Rva0044BF40(const Rva0044BF40 &other):ptr(other.ptr){if(ptr)++ptr->references;}
 ~Rva0044BF40(){if(ptr)ReleaseTreeHintRef00217D4C(ptr);}
};
extern "C" void __cdecl Rva00437F61(int,const UnicodeString &,const UnicodeString &,Rva0044BF40);
#include "../../../../../Include/GameClient/GameText.h"
extern GameTextInterface *TheGameText;
class Rva00514B66 {public:unsigned char rva00514B66();};
static __forceinline FunctorBinding MenuBinding(FunctorMethod method,FunctorTarget *target){return FunctorBinding(method,target);}
// Names: AptMainMenu's ctor (0x00516211) binds "AptMainMenu::LAN" to 0x00515FAB
// and "AptMainMenu::OnlineButtonPressed" to 0x005160DE.
void AptMainMenu::LAN(const char *unused) {
 if(reinterpret_cast<Rva00514B66 *>(this)->rva00514B66()) {
  Rva00437F61(2,TheGameText->fetch("GUI:FirewallPopUpTitle"),TheGameText->fetch("GUI:FirewallPopUpMessage"),
   Rva0044BF40(Rva0044BA4E(
    Rva004F6986Member(MenuBinding(reinterpret_cast<FunctorMethod>(&AptMainMenu::rva00514B8D),reinterpret_cast<FunctorTarget *>(this))),
    Rva004F6986Member(MenuBinding(reinterpret_cast<FunctorMethod>(&AptMainMenu::rva00514BB5),reinterpret_cast<FunctorTarget *>(this))))));
 } else {m_state=9;m_next=6;}
}
void AptMainMenu::OnlineButtonPressed(const char *unused) {
 if(reinterpret_cast<Rva00514B66 *>(this)->rva00514B66()) {
  Rva00437F61(2,TheGameText->fetch("GUI:FirewallPopUpTitle"),TheGameText->fetch("GUI:FirewallPopUpMessage"),
   Rva0044BF40(Rva0044BA4E(
    Rva004F6986Member(MenuBinding(reinterpret_cast<FunctorMethod>(&AptMainMenu::rva00514BA1),reinterpret_cast<FunctorTarget *>(this))),
    Rva004F6986Member(MenuBinding(reinterpret_cast<FunctorMethod>(&AptMainMenu::rva00514BB5),reinterpret_cast<FunctorTarget *>(this))))));
 } else {m_state=9;m_next=10;}
}

// ---- W6-MP1 r6 split-TU trial (2026-10-13, 307/307 size-exact, 4 diff lines) ----
// Standalone formulation: build/mp1_515fab_split.cpp (Code/.../AptMainMenuFirewallCallbacks.cpp,
// UNCOMMITTED scratch -- new-file gate needs a landed row). // cl: mirrors the bank (no /EHsc)
// plus /EHsc omitted deliberately: porting into AptMainMenuCallbacks.cpp (/EHsc) regressed EH
// states (6 vs 4 before the 0x437F61 call); without /EHsc all EH states match and only these
// 4 scheduling lines remain (twin 0x5160DE identical wall, same fix lands both = 614B):
//   retail mov esi,esp THEN mov [ebp-0x1c],esp / mov ecx,esp THEN mov [ebp-0x18],esp
//   ours   spill first, reg-save second (both pairs).
// Tried: FunctorBinding init-order swap (neutral); named m1/m2 locals (pairs match but +2B:
// an extra ReleaseTreeHintRef call at offset 305, size 309 overlapping the twin -- reverted);
// _ReadWriteBarrier in MenuBinding (far worse: frame 0x40->0x38, homes shift -- reverted).
// /vmg /vmm REQUIRED on the // cl: line (else C2440 reinterpret_cast member-pointer error);
// safe: no other member-pointer uses in a split TU (home file untouched, 32/32 rows exact).
// Next: a zero-byte scheduling fence for the esp-save order, or finding which temp the
// reg-saves serve and pinning it to esi/ecx earlier (declare-first-live-local-first).
