// cl: /MD
// VP6_DecodeFrameMbs candidate: full target 0x001BC9C0..0x001BCC30, 625 bytes.
// Donor PB_INSTANCE names/layout are checked only at the accesses used here.
// Public MFNode VP62 defaultModelsInit/decode flow provides semantic context;
// its class layout and full implementation are not transferred.
// Callee identity and field provenance: reverse/vp6_structural_evidence.json.
// Reconstructed C++; no original On2 implementation text is incorporated.
struct FrameQuantizer {
    unsigned char unknown[0x13c];
    unsigned int *scan;
};
struct FramePB {
    unsigned char unknown0[4];
    void *coefficients;
    unsigned char unknown1[0x13c-8];
    FrameQuantizer *quantizer;
    unsigned char unknown2[0x150-0x140];
    unsigned char br[32];
    unsigned char unknown3[0x1ac-0x170];
    unsigned char FrameType;
    unsigned char unknown4[0x1dc-0x1ad];
    int Interlaced;
    unsigned char unknown5[0x228-0x1e0];
    unsigned MacroBlocks, MBRows, MBCols;
    unsigned char unknown6[0x39c-0x234];
    int LastMode;
    unsigned char unknown7[0x57c-0x3a0];
    unsigned char MergedScanOrder[64];
    unsigned char ModifiedScanOrder[64];
    unsigned char EobOffsetTable[64];
    unsigned char ScanBands[64];
    unsigned char MBModeProb[11], BModeProb[11];
    unsigned char unknown8[0x6e8-0x692];
    int probInterlaced;
    void *MBInterlaced;
    unsigned char *predictionMode;
    unsigned char unknown9[0x704-0x6f4];
    unsigned char MvSignProbs[2], IsMvShortProb[2];
    unsigned char MvShortProbs[14];
    unsigned char unknown10[6];
    unsigned char MvSizeProbs[16];
    unsigned char probXmitted[80];
    unsigned char unknown11[0x4520-0x77c];
    int UseHuffman;
    unsigned CurrentDcRunLen[2], CurrentAc1RunLen[2];
};
// defaultModeProbs: matched references place it at VA 0xbd98b8 (retail .rdata contents).
unsigned char defaultModeProbs[80] = {
	0x2au, 2u, 7u, 0x2au, 0x16u, 3u, 2u, 5u,
	1u, 0u, 0x45u, 1u, 1u, 0x2cu, 6u, 1u,
	0u, 1u, 0u, 0u, 8u, 1u, 8u, 0u,
	0u, 2u, 1u, 0u, 1u, 0u, 0xe5u, 1u,
	0u, 0u, 0u, 1u, 0u, 0u, 1u, 0u,
	0x23u, 1u, 6u, 0x22u, 0u, 2u, 1u, 1u,
	1u, 0u, 0x7au, 1u, 1u, 0x2eu, 0u, 1u,
	0u, 0u, 1u, 0u, 0x40u, 0u, 0x40u, 0x40u,
	0x40u, 0u, 0u, 0u, 0u, 0u, 0x40u, 0u,
	0x40u, 0x40u, 0x40u, 0u, 0u, 0u, 0u, 0u,
};
extern unsigned char defaultIsMvShort[2], defaultMvShort[14];
extern unsigned char defaultMvSign[2], defaultMvSize[16];
extern unsigned char DefaultInterlacedScanBands[64], DefaultNonInterlacedScanBands[64];
extern "C" void *memset(void *,int,unsigned);
extern "C" void *memcpy(void *,const void *,unsigned);
#pragma intrinsic(memset,memcpy)
struct Rva009AAFE0Context;
struct Rva009AB7F0Context;
struct Rva009AB760Context;
void Rva009B6A30LoadTables(unsigned char *);
void Rva009AAFE0BuildTable(Rva009AAFE0Context *,const unsigned char *);
void Rva009AB7F0Reset(Rva009AB7F0Context *);
void Rva009AB760Initialize(Rva009AB760Context *);
void Rva009B5DB0Vp6DecodeBlock(unsigned char *,int,unsigned);
int bfmeGoUSC(void *,int);
extern "C" void VP6_ConfigureMvEntropyDecoder(FramePB *,unsigned char);
extern "C" void VP6_ConfigureEntropyDecoder(FramePB *,unsigned char);
extern "C" void ConvertBoolTrees(FramePB *);

extern "C" void VP6_DecodeFrameMbs(FramePB *pbi)
{
    unsigned rows=pbi->MBRows;
    unsigned cols=pbi->MBCols;
    if(pbi->FrameType) {
        Rva009B6A30LoadTables((unsigned char *)pbi);
        VP6_ConfigureMvEntropyDecoder(pbi,pbi->FrameType);
        pbi->LastMode=0;
    } else {
        memcpy(pbi->probXmitted,defaultModeProbs,80);
        memcpy(pbi->IsMvShortProb,defaultIsMvShort,2);
        memcpy(pbi->MvShortProbs,defaultMvShort,14);
        memcpy(pbi->MvSignProbs,defaultMvSign,2);
        memcpy(pbi->MvSizeProbs,defaultMvSize,16);
        memset(pbi->MBModeProb,128,11);
        memset(pbi->BModeProb,128,11);
        memset(pbi->predictionMode,1,pbi->MacroBlocks);
        if(pbi->Interlaced==1) memcpy(pbi->ScanBands,DefaultInterlacedScanBands,64);
        else memcpy(pbi->ScanBands,DefaultNonInterlacedScanBands,64);
        Rva009AAFE0BuildTable((Rva009AAFE0Context *)pbi,pbi->ScanBands);
    }
    VP6_ConfigureEntropyDecoder(pbi,pbi->FrameType);
    for(unsigned i=0;i<64;++i)
        pbi->MergedScanOrder[i]=(unsigned char)pbi->quantizer->scan[pbi->ModifiedScanOrder[i]];
    if(pbi->UseHuffman) ConvertBoolTrees(pbi);
    if(pbi->Interlaced==1) pbi->probInterlaced=(unsigned char)bfmeGoUSC(pbi->br,8);
    Rva009AB7F0Reset((Rva009AB7F0Context *)pbi);
    memset(pbi->coefficients,0,768);
    pbi->CurrentDcRunLen[0]=0; pbi->CurrentDcRunLen[1]=0;
    pbi->CurrentAc1RunLen[0]=0; pbi->CurrentAc1RunLen[1]=0;
    for(unsigned row=3;row<rows-3;++row) {
        Rva009AB760Initialize((Rva009AB760Context *)pbi);
        for(unsigned col=3;col<cols-3;++col)
            Rva009B5DB0Vp6DecodeBlock((unsigned char *)pbi,row,col);
    }
}
