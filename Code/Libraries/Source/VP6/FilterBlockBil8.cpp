// cl: /O2 /G6 /DNDEBUG /MD
// Clean-room implementation from reviewed specs001b8b70 and001b8560.
// Native1B8B70..1B8E6E proves pointer ordering, both inlined eight-row byte
// filters, and the diagonal call at1B8E61 to owned FilterBlock2dBil_8.
// The reviewed specs supply the FilterBlockBil_8_C name and purpose.
// Existing g_vp6BilinearWeights owns the retail bilinear weights atVA DB70E8;
// target immediates independently prove the phase stride and rounding.
// No external decoder source was consulted.
extern const int g_vp6BilinearWeights[8][2];
extern "C" void __cdecl FilterBlock2dBil_8(const unsigned char *,unsigned short *,int,const int *,const int *);
static void BilinearByteBlock(const unsigned char *source,unsigned char *destination,
 unsigned int pitch,unsigned int step,unsigned int rows,unsigned int columns,const int *weights)
{
 for(unsigned int row=0;row<rows;++row) {
  for(unsigned int column=0;column<columns;++column) {
   destination[column]=(unsigned char)((source[step]*weights[1]+source[0]*weights[0]+64)>>7);
   ++source;
  }
  source+=pitch-columns;
  destination+=columns;
 }
}
extern "C" void FilterBlockBil_8_C(const unsigned char *first,const unsigned char *second,
 unsigned char *destination,unsigned int pitch,int horizontal,int vertical)
{
 int distance=second-first;
 if(distance<0) {
  const unsigned char *temporary=first;
  first=second;
  second=temporary;
  distance=second-first;
 }
 if(distance==1) BilinearByteBlock(first,destination,pitch,1,8,8,g_vp6BilinearWeights[horizontal]);
 else if(distance==(int)pitch) BilinearByteBlock(first,destination,pitch,pitch,8,8,g_vp6BilinearWeights[vertical]);
 else if(distance==(int)(pitch-1)) FilterBlock2dBil_8(first-1,(unsigned short *)destination,pitch,g_vp6BilinearWeights[horizontal],g_vp6BilinearWeights[vertical]);
 else if(distance==(int)(pitch+1)) FilterBlock2dBil_8(first,(unsigned short *)destination,pitch,g_vp6BilinearWeights[horizontal],g_vp6BilinearWeights[vertical]);
}
