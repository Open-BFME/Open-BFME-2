// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// Official EA Zero Hour / clean BFME1 PersistentStorageThread.cpp at
// 89f1588225645d9fb90151bd651aa62c489f36ae supplies the queue-lock/map/merge
// semantic guide. Copyright2025 Electronic Arts Inc.; GPL-3.0-or-later.
// BFME2 WB13E9630/13E98A0/13E9B10 independently name the three virtual
// trackPlayer*Stats members. Retail559480..55954E /55954E..55961C /
// 55961C..5596EA are each206B; RET1A8/190/208 proves the by-value records.
// Target record layouts and all out-of-line lifetime providers already live
// in PersistentStorageThread.cpp: tournament1A8, open-play190, strategic208;
// each has id150. PSPlayerAllStats is548B with blocks8/1B0/340. These views
// leave their unused state opaque; only their witnessed vptr/lifetime/id ABI
// is exposed here. Queue mutex4 and int-key map90 agree with named WB bodies
// and the existing typed getter family. The canonical WWLib mutex is reused.
// The three incorporate providers retain their established provisional
// source-view names; their declared pointer ABI matches the observed call.
// This file defines only the three queue members; record and interface
// declarations emit no competing lifetime or vtable definitions.
#include <mutex.h>
#include <map>
class Rva00385333 {
public:
 virtual void reset();
 ~Rva00385333();
 unsigned char prefix[0x150-4]; int m_id; unsigned char tail[0x1A8-0x154];
};
class Rva003844D7 {
public:
 virtual void reset();
 ~Rva003844D7();
 unsigned char prefix[0x150-4]; int m_id; unsigned char tail[0x190-0x154];
};
class Rva0038454E {
public:
 virtual void reset();
 ~Rva0038454E();
 unsigned char prefix[0x150-4]; int m_id; unsigned char tail[0x208-0x154];
};
class Rva00552D7BSrc;class Rva00552DDASrc;class Rva00552E3CSrc;
class PSPlayerAllStats {
public:
 PSPlayerAllStats(int);
 ~PSPlayerAllStats();
 PSPlayerAllStats &operator=(const PSPlayerAllStats &);
 void incorporate(const Rva00552D7BSrc *);
 void incorporate(const Rva00552DDASrc *);
 void incorporate(const Rva00552E3CSrc *);
private:
 int id,locale; Rva00385333 tournament; Rva003844D7 open;Rva0038454E strategic;
};
typedef _STL::map<int,PSPlayerAllStats> StatsMap;
template <> PSPlayerAllStats &StatsMap::operator[](const int &);
class GameSpyPSMessageQueue {
public:
 virtual void trackPlayerTournamentStats(Rva00385333);
 virtual void trackPlayerOpenPlayStats(Rva003844D7);
 virtual void trackPlayerStrategicStats(Rva0038454E);
private:
 MutexClass mutex;
 char padding[0x90-0xC];
 StatsMap playerStats;
};
void GameSpyPSMessageQueue::trackPlayerTournamentStats(Rva00385333 stats) {
 MutexClass::LockClass lock(mutex);
 PSPlayerAllStats combined(0);
 int id=stats.m_id;
 StatsMap::iterator it=playerStats.find(id);
 if(it._M_node!=playerStats.end()._M_node) combined=it->second;
 combined.incorporate(reinterpret_cast<const Rva00552D7BSrc *>(&stats));
 id=stats.m_id;
 playerStats[id]=combined;
}
void GameSpyPSMessageQueue::trackPlayerOpenPlayStats(Rva003844D7 stats) {
 MutexClass::LockClass lock(mutex);
 PSPlayerAllStats combined(0);
 int id=stats.m_id;
 StatsMap::iterator it=playerStats.find(id);
 if(it._M_node!=playerStats.end()._M_node) combined=it->second;
 combined.incorporate(reinterpret_cast<const Rva00552DDASrc *>(&stats));
 id=stats.m_id;
 playerStats[id]=combined;
}
void GameSpyPSMessageQueue::trackPlayerStrategicStats(Rva0038454E stats) {
 MutexClass::LockClass lock(mutex);
 PSPlayerAllStats combined(0);
 int id=stats.m_id;
 StatsMap::iterator it=playerStats.find(id);
 if(it._M_node!=playerStats.end()._M_node) combined=it->second;
 combined.incorporate(reinterpret_cast<const Rva00552E3CSrc *>(&stats));
 id=stats.m_id;
 playerStats[id]=combined;
}

