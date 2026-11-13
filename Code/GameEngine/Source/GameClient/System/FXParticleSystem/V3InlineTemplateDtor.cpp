// cl: /O1 /G7 /MD
// ??1Rva003AE13C@@UAE@XZ, retail 0x003A583E, 24 bytes.
// V3-inline template destructor for Rva003AE13C (copy rowed at 0x003AE13C in
// V3InlineTemplateCopyCtors.cpp): restores its two vftables (+8 null-guarded
// 0x00C1C780 via neg/lea/sbb/and, then +0 plain 0x00C1B320) and returns with
// no base call (base Rva005EA430 at 0x003ADDEC has trivial dtor). Layout
// matches the copy (m_v0 +0, pad +4, m_v8 +8, flag +0x0C); novtable suppresses
// the implicit derived store so only the manual stores remain, in retail order
// +8 then +0. Vtable 0x0081D2C0 slot 0 is the ??_G at 0x003AE16E which calls
// here; callers also include Unwind funclets for EH cleanup.

extern "C" const void *const __identifier("??_7?$CategoryModuleInfo@$00@FXParticleSystem@@6B@")[];  // folded, 35 classes

extern "C" const void *const __identifier("??_7V3Vt01111D90@@6B@")[];

class __declspec(novtable) Rva003AE13C
{
public:
    virtual ~Rva003AE13C();
private:
    void *m_v0;
    char m_pad04[4];
    void *m_v8;
    unsigned char m_flag0c;
};

Rva003AE13C::~Rva003AE13C()
{
    unsigned char *vtableSlot = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)vtableSlot = ((unsigned int)__identifier("??_7?$CategoryModuleInfo@$00@FXParticleSystem@@6B@"));
    *(volatile unsigned int *)this = ((unsigned int)__identifier("??_7V3Vt01111D90@@6B@"));
}

// Rva0055BCD2 (ctor 0x0055BCD2, unit Rva0055B52EPermuted.cpp): its vtable
// 0x00C1D164 slot 0 is the same ??_G 0x003AE16E, so this 24B body is its
// destructor too (ICF alias row); same two-table layout.
class __declspec(novtable) Rva0055BCD2
{
public:
    virtual ~Rva0055BCD2();
private:
    void *m_v0;
    char m_pad04[4];
    void *m_v8;
    unsigned char m_flag0c;
};

__declspec(noinline) inline Rva0055BCD2::~Rva0055BCD2()
{
    unsigned char *b08 = this ? (unsigned char *)this + 8 : 0;
    *(volatile unsigned int *)b08 = ((unsigned int)__identifier("??_7?$CategoryModuleInfo@$00@FXParticleSystem@@6B@"));
    *(volatile unsigned int *)this = ((unsigned int)__identifier("??_7V3Vt01111D90@@6B@"));
}

// Keep the shared select-any destructor emitted in its row's home unit.
// ?bfmeAnchorRva0055BCD2Dtor absent-from-retail
void bfmeAnchorRva0055BCD2Dtor(Rva0055BCD2 *p)
{
    p->Rva0055BCD2::~Rva0055BCD2();
}

// The primary eight bytes carry no resources; the parent below performs both
// native vptr restorations. This local base view is structural inference.
class __declspec(novtable) Rva003ADFDBPrimary {
public:
 virtual ~Rva003ADFDBPrimary(){}
private:unsigned argument4;
};
#include "../../../../Include/Common/Iface00C1C780.h"
class __declspec(novtable) Rva003ADFDB:public Rva003ADFDBPrimary,public Iface00C1C780 {public:Rva003ADFDB(unsigned);virtual ~Rva003ADFDB();};
// Target C1D294 and C1D2C0 both select 3AE16E; it calls native24 at3A583E.
// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline Rva003ADFDB::~Rva003ADFDB(){
 unsigned char* b08=this?(unsigned char*)this+8:0;
 *(volatile unsigned int*)b08=((unsigned int)__identifier("??_7?$CategoryModuleInfo@$00@FXParticleSystem@@6B@"));
 *(volatile unsigned int*)this=((unsigned int)__identifier("??_7V3Vt01111D90@@6B@"));
}

// ?bfmeAnchorRva003ADFDBDtor absent-from-retail
void bfmeAnchorRva003ADFDBDtor(Rva003ADFDB *p)
{
	p->Rva003ADFDB::~Rva003ADFDB();
}

