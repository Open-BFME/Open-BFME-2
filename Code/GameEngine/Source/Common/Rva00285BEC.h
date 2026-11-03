#pragma once
// Native FireLogicSystem::BurningCell; address-derived class spelling retained.
// Tables BFB700/BFB6F0 and size20 are independently verified in retail.
#include "Rva00285635.h"
#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
typedef Rva00285635 Rva00285BECBase;
class __declspec(novtable) Rva00285BECSnapshotBase:public Snapshot {
public:
 virtual ~Rva00285BECSnapshotBase(){}
 // Snapshot slots 1-3 follow the spelling the included Snapshot base selected, so they always override.
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
 virtual void LoadPostProcess(){}
#else
 virtual void loadPostProcess(){}
#endif
#ifdef BFME_SNAPSHOT_NAME_SLOT
#ifdef BFME_SNAPSHOT_NONCONST_NAME_SLOT
 virtual const char*GetSnapshotName();
#else
 virtual const char*GetSnapshotName()const;
#endif
#else
 virtual void crc(Xfer*);
#endif
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
#ifdef BFME_SNAPSHOT_REFERENCE_XFER
 virtual void DoXfer(Xfer&);
#else
 virtual void DoXfer(Xfer*);
#endif
#else
 virtual void xfer(Xfer*);
#endif
};
class Rva00285BEC:public Rva00285BECBase,public Rva00285BECSnapshotBase {
public:
 struct Pair080C {
  int m_00,m_04;
  Pair080C(){}
  Pair080C(int a,int b):m_00(a),m_04(b){}
  Pair080C(Pair080C const&s):m_00(s.m_00),m_04(s.m_04){}
 };
 Rva00285BEC(int,int);
 Rva00285BEC(Rva00285BEC const&);
 virtual ~Rva00285BEC();
 virtual Rva00SlotFloat2FromInts vslot00();
 virtual Rva00SlotFloat2FromInts vslot01()const;
 virtual unsigned char* vslot02();
 virtual unsigned char const* vslot03()const;
 virtual unsigned char* vslot04();
 virtual unsigned char const* vslot05()const;
 virtual short vslot06()const;
 virtual LargeGroupAudioKeyMap* vslot07()const;
 virtual bool vslot08()const;
 virtual bool vslot09()const;
 virtual int vslot10()const;
 Pair080C m_08;
 int m_10;
};
