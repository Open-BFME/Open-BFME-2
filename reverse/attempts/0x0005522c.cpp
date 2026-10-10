// ?rva0005522C@MilesAudioManager@@QAEXABVAsciiString@@@Z
// partial score=0.95 date=2026-10-10
// ?rva0005522C@MilesAudioManager@@QAEXABVAsciiString@@@Z
// partial score=0.95 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /EHsc /MD
#include "ascii_string.h"
class MilesMutexGuard {
public: MilesMutexGuard(void *, int); ~MilesMutexGuard();
private: void *mutex; bool held;
};
class MilesAudioManager {
public:
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 virtual void slot7();
 virtual void slot8();
 virtual void slot9();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void slot17();
 virtual void slot18();
 virtual void slot19();
 virtual void slot20();
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
 virtual void slot24();
 virtual void slot25();
 virtual void slot26();
 virtual void slot27();
 virtual void slot28();
 virtual void slot29();
 virtual void slot30();
 virtual void slot31();
 virtual void slot32();
 virtual void slot33();
 virtual void slot34();
 virtual void slot35();
 virtual void slot36();
 virtual void slot37();
 virtual void slot38();
 virtual void slot39();
 virtual void slot40();
 virtual void slot41();
 virtual void slot42();
 virtual void slot43();
 virtual void slot44();
 virtual void slot45();
 virtual void slot46();
 virtual void slot47();
 virtual void slot48();
 virtual void slot49();
 virtual void slot50();
 virtual void slot51();
 virtual void slot52();
 virtual void slot53();
 virtual void slot54();
 virtual void slot55();
 virtual void slot56();
 virtual void slot57();
 virtual void slot58();
 virtual void slot59();
 virtual void slot60();
 virtual void slot61();
 virtual void slot62();
 virtual void slot63();
 virtual void slot64();
 virtual void slot65();
 virtual void slot66();
 virtual void slot67();
 virtual void slot68();
 virtual void slot69();
 virtual void slot70();
 virtual void slot71();
 virtual void slot72();
 virtual void slot73();
 virtual void slot74();
 virtual void slot75();
 virtual void slot76();
 virtual void slot77();
 virtual void slot78();
 virtual void slot79();
 virtual void slot80();
 virtual void slot81();
 virtual void slot82();
 virtual void slot83();
 virtual void slot84();
 virtual void slot85();
 virtual void slot86();
 virtual void slot87();
 virtual void slot88();
 virtual void slot89();
 virtual void slot90();
 virtual void slot91();
 void internalSetReverbRoomType(int);
 void rva0005522C(const AsciiString &);
private:
 char padding[0x9D4-4]; void *m_mutex;
 char padding2[0xBE4-0x9D8]; int m_atBE4;
};
struct EnvironmentNameEntry { const char *name; int environmentType; };
extern "C" const EnvironmentNameEntry s_environmentNames[26];
static inline int milesEnvironmentType(const AsciiString &name)
{
 if (name.compareNoCase("Hanger") == 0) return 10;
 for (unsigned i = 0; i < 26; ++i)
  if (name.compareNoCase(s_environmentNames[i].name) == 0)
   return s_environmentNames[i].environmentType;
 return -1;
}
void MilesAudioManager::rva0005522C(const AsciiString &name)
{
 MilesMutexGuard guard(&m_mutex, 0);
 int type = milesEnvironmentType(name);
 if (type == -1) slot91();
 else internalSetReverbRoomType(m_atBE4 = type);
}
