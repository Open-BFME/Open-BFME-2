// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Both bodies are real C++ recovered from the target boundaries and call relationships.
// Target facts: B495B..B4979 (30B), vector50, selected70, 64B animation record mode1C;
// The mode accessor contains the former 4B IntOneGetters true-tail at B4975.
// B4A1C..B4A9F (131B), weighted selection using record weight30 and avoid-index -1.
// Identity: WB920490 calls AnimConditionInfo::pickRandomAnimation; mode accessor unnamed.
// Source guide: ZH W3DModelDraw::adjustAnimation for same animation-selection purpose,
// BFME2 adds weighted choices independently proven by native loops.
int GetGameClientRandomValue(int lo,int hi,char *file,int line);
struct AnimConditionInfoAnimationView
{
 unsigned char pad00[0x1c];
 int mode;
 unsigned char pad20[0x10];
 int weight;
 unsigned char pad34[0xc];
};
struct AnimConditionInfoVectorView
{
 AnimConditionInfoAnimationView *begin, *end, *capacity;
 __forceinline int size() const { return end-begin; }
 __forceinline bool empty() const { return begin==end; }
 __forceinline AnimConditionInfoAnimationView &operator[](int i) { return begin[i]; }
};
class AnimConditionInfo
{
 unsigned char prefix00[0x50];
 AnimConditionInfoVectorView animations;
 unsigned char pad5c[0x14];
 int selected;
public:
 int rva000B495B();
 int pickRandomAnimation(int avoid,int maximum);
};
int AnimConditionInfo::rva000B495B()
{
 if(!animations.empty() && selected>=0) return animations[selected].mode;
 return 1;
}
int AnimConditionInfo::pickRandomAnimation(int avoid,int maximum)
{
 int count=animations.size();
 if(count>maximum) count=maximum;
 if(count<2) return 0;
 int total=0;
 for(int i=0;i<count;++i)
 {
  int weight=animations[i].weight;
  if(i==avoid) --weight;
  total+=weight;
 }
 int pick=GetGameClientRandomValue(0,total-1,
 "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngineDevice\\Source\\W3DDevice\\GameClient\\Drawable\\W3DScriptedModelDraw.cpp",1118);
 for(int j=0;j<count;++j)
 {
  int weight=animations[j].weight;
  if(j==avoid) --weight;
  pick-=weight;
  if(pick<0) return j;
 }
 return 0;
}
