// cl: /O2 /MD /EHsc
// Source guide b44700bdab0a24a7 AptCIH.cpp jumpToFrame. Native dispatch
// Next/Prev/Goto consumers establish identity; native335B proves sprite
// frame18 hash10 display24 goto28 and bounds. Does not imply link closure:
// doFrameControls70F370 temporary70F040 mergeState6F9410 remain unrowed.
// Destroy(1) binds existing byte-verified scalar deleting destructor provider.
class AptCIH;
class AptNativeHash;
class Rva006DB160 { public: void *allocBlock(int); };
class Rva006DB270;
extern Rva006DB270 *g_pChainBlockAllocator;
class AptPseudoDisplayList {
public:
 AptPseudoDisplayList(AptCIH *);
 static void *operator new(unsigned int n) {return ((Rva006DB160 *)g_pChainBlockAllocator)->allocBlock(n);}
 static void operator delete(void *,unsigned int);
 AptPseudoDisplayList *Destroy(int);
 void *head; AptCIH *parent;
};
class AptDisplayList { public: void *state; void mergeState(AptPseudoDisplayList *,AptNativeHash *,bool); };
class AptMovie { public: int nFrames; void doFrameControls(AptDisplayList *,AptCIH *,int); void DoTemporaryFrameControls(AptPseudoDisplayList *,int); void queueFrameActions(AptCIH *,int); };
struct AptCharacter { unsigned char prefix[8]; AptMovie movie; };
struct AptCharacterSpriteInstBase { unsigned char prefix[12]; AptCharacter *character; AptNativeHash *nativeHash; int unknown14; int mnFrame; int flags; void *actions; AptDisplayList display; int mnGotoAnded; };
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
class AptCIH {
public:
 unsigned char prefix[0x4c]; AptCharacterSpriteInstBase *character;
 bool IsSpriteInstBase() const;
 AptCharacterSpriteInstBase *GetSpriteInstBase() const {
  if(!IsSpriteInstBase()) {
   g_bfmeAptAssertAtE17734("isSpriteInstBase()","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h",0x7d);
   if(g_bfmeAptBreakOnAssertAtDDC01C) {__asm int 3}
  }
  return character;
 }
 void jumpToFrame(int);
};
void AptCIH::jumpToFrame(int frame) {
 AptCharacterSpriteInstBase *sprite=GetSpriteInstBase();
 if(frame<0 || frame>=sprite->character->movie.nFrames) return;
 if(frame==sprite->mnFrame) return;
 else if(frame==sprite->mnFrame+1) {
  sprite->mnFrame=frame;
  sprite->character->movie.doFrameControls(&sprite->display,this,sprite->mnFrame);
 } else {
  AptNativeHash *old=sprite->nativeHash;
  AptPseudoDisplayList *test=new AptPseudoDisplayList(this);
  bool ahead=sprite->mnFrame<frame;
  for(sprite->mnFrame=sprite->mnFrame<frame ? sprite->mnFrame : 0;
      sprite->mnFrame<=frame && sprite->mnFrame<sprite->character->movie.nFrames; ++sprite->mnFrame)
   sprite->character->movie.DoTemporaryFrameControls(test,sprite->mnFrame);
  sprite->mnFrame=frame;
  sprite->display.mergeState(test,old,ahead);
  if(test) test->Destroy(1);
 }
 sprite->mnGotoAnded=sprite->mnFrame;
 sprite->character->movie.queueFrameActions(this,sprite->mnFrame);
}
#pragma comment(linker, "/alternatename:??3AptPseudoDisplayList@@SAXPAXI@Z=?Rva006D8680Free@@YAXPAXH@Z")
#pragma comment(linker, "/alternatename:?Destroy@AptPseudoDisplayList@@QAEPAV1@H@Z=?rva006E2A00@Rva006E2A00@@QAEPAV1@H@Z")

#pragma comment(linker, "/alternatename:?queueFrameActions@AptMovie@@QAEXPAVAptCIH@@H@Z=?rva0070F680@Rva0070F680@@QAEXPAXH@Z")
#pragma comment(linker, "/alternatename:?IsSpriteInstBase@AptCIH@@QBE_NXZ=?isSpriteInstBase@Rva006CFCD0@@QBE_NXZ")
