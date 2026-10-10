// _IDct10
// partial score=0.135383 date=2026-10-10
// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reviewed specs 001d6660, 001d65a0, 001d3f30, 001d35e0 plus retail.
// Three-pointer cdecl ABI and signed low-32 product >>16 are native-established.
void __cdecl Rva009C5CA0(short *,short *,int *);
static __forceinline int multiply16(int value,int constant)
{
 return (int)((unsigned)value*(unsigned)constant)>>16;
}
static __forceinline void rowFour(int *row)
{
 if(row[0]|row[1]|row[2]|row[3]) {
  int oddSum17=multiply16(row[1],64277);
  int oddSum35=multiply16(row[3],54491);
  int oddDiff17=multiply16(row[1],12785);
  int oddDiff35=-multiply16(row[3],36410);
  int rotS=multiply16(oddSum17-oddSum35,46341);
  int rotM=multiply16(oddDiff17-oddDiff35,46341);
  int oddSS=oddSum17+oddSum35;
  int oddSM=oddDiff17+oddDiff35;
  int rotEven=multiply16(row[0],46341);
  int pairSum26=multiply16(row[2],60547);
  int pairDiff26=multiply16(row[2],25080);
  int eA=rotEven-pairSum26,eB=rotEven+pairSum26;
  int oA=rotM-pairDiff26,oB=rotM+pairDiff26;
  int fA=rotEven-rotS,fB=rotEven+rotS;
  row[0]=(short)(eB+oddSS); row[7]=(short)(eB-oddSS);
  row[1]=(short)(fB+oB); row[2]=(short)(fB-oB);
  row[3]=(short)(eA+oddSM); row[4]=(short)(eA-oddSM);
  row[5]=(short)(fA+oA); row[6]=(short)(fA-oA);
 }
}
extern "C" void __cdecl IDct10(short *input,short *quantiser,short *output)
{
 int block[64];
 Rva009C5CA0(quantiser,input,block);
 for(int r=0;r<4;++r) rowFour(block+r*8);
 output+=8;
 int *column=block;
 int remaining=8;
 do {
  if(column[0]|column[8]|column[16]|column[24]) {
   int oddSum17=multiply16(column[8],64277);
   int oddSum35=multiply16(column[24],54491);
   int oddDiff17=multiply16(column[8],12785);
   int oddDiff35=-multiply16(column[24],36410);
   int rotS=multiply16(oddSum17-oddSum35,46341);
   int rotM=multiply16(oddDiff17-oddDiff35,46341);
   int oddSS=oddSum17+oddSum35;
   int oddSM=oddDiff17+oddDiff35;
   int rotEven=multiply16(column[0],46341);
   int pairSum26=multiply16(column[16],60547);
   int pairDiff26=multiply16(column[16],25080);
   int eA=rotEven-pairSum26+8,eB=rotEven+pairSum26+8;
   int oA=rotM-pairDiff26,oB=rotM+pairDiff26;
   int fA=rotEven-rotS+8,fB=rotEven+rotS+8;
   output[-8]=(short)((eB+oddSS)>>4); output[48]=(short)((eB-oddSS)>>4);
   output[0]=(short)((fB+oB)>>4); output[8]=(short)((fB-oB)>>4);
   output[16]=(short)((eA+oddSM)>>4); output[24]=(short)((eA-oddSM)>>4);
   output[32]=(short)((fA+oA)>>4); output[40]=(short)((fA-oA)>>4);
  } else {
   output[-8]=0; output[48]=0;
   output[0]=0; output[8]=0;
   output[16]=0; output[24]=0;
   output[32]=0; output[40]=0;
  }
 ++column; ++output;
 } while(--remaining);
}