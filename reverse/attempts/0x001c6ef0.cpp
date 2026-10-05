// _VP6_ConfigureMvEntropyDecoder
// partial score=0.8788 date=2026-10-05
// _VP6_ConfigureMvEntropyDecoder
// cl: /O2 /MD
// VP6 motion-model updates: target 0x001C6EF0..0x001C703A (331 bytes).
// Donor name/layout plus independently equal 34-byte update table and public
// VP62::parseVectorModelsChanges semantics. Frame type is unused in both bodies.
//
// Size-exact 331B and the loop shape now matches retail (byte pointer walks with
// `*p++` into the update table, a spilled outer pointer, and the `push ecx`
// local slot). The only residual is the callee-saved allocation: retail keeps
// the loop index in esi and the bit-reader pointer in edi, this build swaps
// them (index edi, br esi). No source form or flag tried reaches retail's pick.
struct MvPB {
    unsigned char unknown0[0x150];
    unsigned char br[32];
    unsigned char unknown1[0x704-0x170];
    unsigned char MvSignProbs[2], IsMvShortProb[2];
    unsigned char MvShortProbs[2][7];
    unsigned char unknown2[6];
    unsigned char MvSizeProbs[2][8];
};
extern unsigned char VP6_MvUpdateProbs[2][17];
int Rva009B4600DecodeBool(void *,int);
int bfmeGoUSC(void *,int);
extern "C" void VP6_ConfigureMvEntropyDecoder(MvPB *pbi,unsigned char frameType)
{
    int i;
    unsigned j;
    const unsigned char *p;
    for(i=0;i<2;++i) {
        if(Rva009B4600DecodeBool(pbi->br,VP6_MvUpdateProbs[i][0])) {
            pbi->IsMvShortProb[i]=(unsigned char)(bfmeGoUSC(pbi->br,7)<<1);
            if(!pbi->IsMvShortProb[i]) pbi->IsMvShortProb[i]=1;
        }
        if(Rva009B4600DecodeBool(pbi->br,VP6_MvUpdateProbs[i][1])) {
            pbi->MvSignProbs[i]=(unsigned char)(bfmeGoUSC(pbi->br,7)<<1);
            if(!pbi->MvSignProbs[i]) pbi->MvSignProbs[i]=1;
        }
    }
    for(i=0;i<2;++i) {
        p=VP6_MvUpdateProbs[i]+2;
        for(j=0;j<7;++j) {
            if(Rva009B4600DecodeBool(pbi->br,*p++)) {
                pbi->MvShortProbs[i][j]=(unsigned char)(bfmeGoUSC(pbi->br,7)<<1);
                if(!pbi->MvShortProbs[i][j]) pbi->MvShortProbs[i][j]=1;
            }
        }
    }
    for(i=0;i<2;++i) {
        p=VP6_MvUpdateProbs[i]+8;
        for(j=0;j<8;++j) {
            if(Rva009B4600DecodeBool(pbi->br,*++p)) {
                pbi->MvSizeProbs[i][j]=(unsigned char)(bfmeGoUSC(pbi->br,7)<<1);
                if(!pbi->MvSizeProbs[i][j]) pbi->MvSizeProbs[i][j]=1;
            }
        }
    }
}
