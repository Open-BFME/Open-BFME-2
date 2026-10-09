// cl: /O1 /arch:SSE /G7 /Oy- /MD
// Native 002F6F90..002F70E5, thiscall RET8 AL. WB D6A690 and target
// diagnostics support adjustment predicate role; original context name unknown.
// Clean BFME1 IsCheckForAdjust003F2B60 donor revision 9cbfb551 supplies the
// predicate control flow; field offsets, kind bit and ABI come from retail.
struct Rva002F600CCoord { float x, y, z; };
struct Rva002F600CMetadata
{
    unsigned char prefix0C[12];
    unsigned int packed;
};
class Rva002F52A7Query
{
public:
    bool rva002F52A7(unsigned int a, unsigned int b, unsigned char mode,
        unsigned int c, unsigned int d, unsigned int kind, unsigned int e,
        unsigned char option, Rva002F600CCoord *position, unsigned int zero,
        float value, unsigned int *word, unsigned int finalZero);
};

struct PathfinderLogFile;
extern "C" int __cdecl fprintf(PathfinderLogFile *,const char *,...);
extern unsigned char g_00E03745;
extern void *g_00DFEFF0;
struct Rva002F6F90Template { unsigned char pad[0x114]; unsigned int flags; };
struct Rva002F6F90Object { unsigned int word0; Rva002F6F90Template *objectTemplate; };
class Rva002F6F90Context {
public: bool rva002F6F90(unsigned int first,int second);
private:
 Rva002F52A7Query *query;
 Rva002F6F90Object *object;
 unsigned int word08;
 unsigned char mode0C,option0D,pad0E[2];
 unsigned int word10,word14,word18;
 float value1C;
 unsigned int saved20;
 int saved24,minimum28;
 unsigned int word2C;
 Rva002F600CCoord position30;
};
// ?rva002F6F90@Rva002F6F90Context@@QAE_NIH@Z
bool Rva002F6F90Context::rva002F6F90(unsigned int first,int second)
{

 if(g_00E03745 && g_00DFEFF0)
  fprintf((PathfinderLogFile*)g_00DFEFF0,"\t\t  Pathfinder_IsCheckForAdjust() called with cell=%d,%d",first,second);
 int count;
 if(!query->rva002F52A7((unsigned int)object,word08,mode0C,first,second,word18,word10,option0D,&position30,word14,value1C,(unsigned int*)&count,word2C)) {
  if(g_00E03745 && g_00DFEFF0)
   fprintf((PathfinderLogFile*)g_00DFEFF0,"\t\t  Pathfinder_IsCheckForAdjust() checkAdjust failed");
  return false;
 }

 if(!count || (object->objectTemplate->flags & 0x20000000)) {
  if(g_00E03745 && g_00DFEFF0)
   fprintf((PathfinderLogFile*)g_00DFEFF0,"\t\t  Pathfinder_IsCheckForAdjust() allyCount=%s, isInfantry=%s, returning true",count?"TRUE":"FALSE",(object->objectTemplate->flags&0x20000000)?"TRUE":"FALSE");
  return true;
 }
 if(count<minimum28 || !minimum28) {
  minimum28=count;saved20=first;saved24=second;
  if(g_00E03745 && g_00DFEFF0)
   fprintf((PathfinderLogFile*)g_00DFEFF0,"\t\t  Pathfinder_IsCheckForAdjust() allyCount=%d, m_foundWithAllies=%d",count,minimum28);
 }
 if(g_00E03745 && g_00DFEFF0)
  fprintf((PathfinderLogFile*)g_00DFEFF0,"\t\t  Pathfinder_IsCheckForAdjust() total failure, return false",count,minimum28);
 return false;
}
