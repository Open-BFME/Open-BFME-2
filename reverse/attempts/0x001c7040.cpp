// _VP6_BuildModeTree
// partial score=0.34 date=2026-10-09
// cl: /O2 /G6 /MD
// Clean-room: reverse/vp6_cleanroom/specs/001c7040.md and retail.
struct VP6ModeDecoderState {
 unsigned char pad000[0x72c];
 unsigned char transmitted[3][2][10];
 unsigned char pad768[0x14];
 unsigned char sameMode[3][10];
 unsigned char pad79a[0xa];
 unsigned char tree[3][10][9];
};
extern "C" void VP6_BuildModeTree(VP6ModeDecoderState *state)
{
 int weights[10];
 int previous=0;
 int offset=-10;
 const unsigned char *statisticsBase=&state->transmitted[0][1][0];
 unsigned char *treeBase=&state->tree[0][0][1];
 do {
  const unsigned char *statistics=statisticsBase;
  unsigned char *same=(unsigned char *)statistics+0x46;
  unsigned char *tree=treeBase;
  int types=3;
  do {
   int total=0;
   for(int mode=0;mode<10;++mode) {
    if(previous==mode) weights[mode]=0;
    else weights[mode]=100*statistics[offset+mode];
    total+=weights[mode];
   }
   *same=255-(255*statistics[0])/(1+statistics[0]+statistics[-10]);
   unsigned int group34=weights[3]+weights[4];
   unsigned int group0234=group34+weights[2]+weights[0];
   tree[-1]=1+(255U*group0234)/(1+total);
   unsigned int group02=weights[2]+weights[0];
   tree[0]=1+(255U*group02)/(1+group0234);
   unsigned int group89=weights[8]+weights[9];
   unsigned int group5689=group89+weights[6]+weights[5];
   unsigned int group17=weights[1]+weights[7];
   tree[1]=1+(255U*group17)/(1+group5689+weights[7]+weights[1]);
   tree[2]=1+(255U*weights[0])/(1+group02);
   tree[3]=1+(255U*weights[3])/(1+group34);
   tree[4]=1+(255U*weights[1])/(1+group17);
   unsigned int group56=weights[6]+weights[5];
   tree[5]=1+(255U*group56)/(1+group5689);
   tree[6]=1+(255U*weights[5])/(1+group56);
   tree[7]=1+(255U*weights[8])/(1+group89);
   statistics+=20;
   tree+=90;
   same+=10;
  } while(--types);
  ++previous;
  ++statisticsBase;
  treeBase+=9;
  --offset;
 } while(offset>-20);
}
