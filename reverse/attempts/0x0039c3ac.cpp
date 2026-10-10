// ?getObjectsDestroyedMap@ScoreKeeper@@QAEPAV?$map@PBVThingTemplate@@HU?$less@PBVThingTemplate@@@_STL@@V?$allocator@U?$pair@QBVThingTemplate@@H@_STL@@@3@@_STL@@H@Z
// partial score=0.99 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Retail39C3AC..39C40A94B and whole WBFA3D70 getter: ScoreKeeper.cpp848.
// Parent code is94/94 and its EH graph is EXACT. This is not an admitted
// recovery: emitted constructor and dynamic cleanup require complete native
// helper identity/relocation closure before this unit can link as retail.
// BF1 donor575ba2b ScoreKeeperCounters.cpp gives the template-pointer/int
// count-map semantic lead; BFME2 calls and map counter39BEC3 confirm the
// pointers/count storage. The target maps have stride12 at+1FC and twenty
// indices. Invalid indices return static mapE02838 guarded atE02844.
// The existing custom ScoreKeeper allocator view gave33B tree base instead
// of native36B; ordinary donor allocator emits the native36B tree base.
// EHs also fixes the tree destructor frame compared with EHsc.
// Remaining: constructor42B at1F068F and destructor56B at357C6A recursive
// fold proof; map destructor5B and dynamic cleanup10B identity; static-data
// owner reconciliation with existing g_Va00E02838. No alias/pin invented.
#include <map>
class ThingTemplate;
typedef _STL::map<const ThingTemplate*,int> ScoreCountMap;
class ScoreKeeper {
 char pad00[0x1fc];
 ScoreCountMap objectsDestroyed[20];
public: ScoreCountMap *getObjectsDestroyedMap(int);
};
ScoreCountMap *ScoreKeeper::getObjectsDestroyedMap(int index) {
 if(index>=0 && (unsigned)index<20) return &objectsDestroyed[index];
 static ScoreCountMap emptyMap;
 return &emptyMap;
}
