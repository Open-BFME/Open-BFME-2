// cl: /MD
// C++ reconstruction from retail boolean-encoder arithmetic and carry handling.
// Names and 32-byte coder field interpretation are corroborated by donor PDB.
// Source-handoff placements supplied candidate addresses; no source body imported.
// Target/donor evidence: reverse/vp6_structural_evidence.json, boolean_encoders.
// Coder output is caller-owned; the carry walk preserves retail buffer behavior.
struct Vp6BoolEncoder {
    unsigned low;
    unsigned range;
    unsigned value;
    int count;
    unsigned position;
    unsigned char *buffer;
    unsigned measureCost;
    unsigned bitCounter;
};

extern "C" void VP6_EncodeBool(Vp6BoolEncoder *coder,int bit,int probability)
{
    unsigned initialRange=coder->range;
    int count=coder->count;
    unsigned low=coder->low;
    unsigned range=1+(((initialRange-1)*probability)>>8);
    if(bit) {
        low+=range;
        range=initialRange-range;
    }
    while(range<128) {
        range<<=1;
        if(low&0x80000000u) {
            int cursor=coder->position-1;
            while(cursor>=0 && coder->buffer[cursor]==255) {
                coder->buffer[cursor]=0;
                --cursor;
            }
            ++coder->buffer[cursor];
        }
        low<<=1;
        if(++count==0) {
            count=-8;
            coder->buffer[coder->position]=(unsigned char)(low>>24);
            ++coder->position;
            low&=0x00ffffff;
        }
    }
    coder->low=low;
    coder->range=range;
    coder->count=count;
}

extern "C" void VP6_EncodeBoolZero(Vp6BoolEncoder *coder,int bit,int probability)
{
    unsigned initialRange=coder->range;
    int count=coder->count;
    unsigned low=coder->low;
    unsigned range=1+(((initialRange-1)*probability)>>8);
    while(range<128) {
        range<<=1;
        if(low&0x80000000u) {
            int cursor=coder->position-1;
            while(cursor>=0 && coder->buffer[cursor]==255) {
                coder->buffer[cursor]=0;
                --cursor;
            }
            ++coder->buffer[cursor];
        }
        low<<=1;
        if(++count==0) {
            count=-8;
            coder->buffer[coder->position]=(unsigned char)(low>>24);
            ++coder->position;
            low&=0x00ffffff;
        }
    }
    coder->low=low;
    coder->range=range;
    coder->count=count;
}

extern "C" void VP6_EncodeBoolOne(Vp6BoolEncoder *coder,int bit,int probability)
{
    unsigned range=coder->range;
    int count=coder->count;
    unsigned low=coder->low;
    unsigned split=1+(((range-1)*probability)>>8);
    range-=split;
    low+=split;
    while(range<128) {
        range<<=1;
        if(low&0x80000000u) {
            int cursor=coder->position-1;
            while(cursor>=0 && coder->buffer[cursor]==255) {
                coder->buffer[cursor]=0;
                --cursor;
            }
            ++coder->buffer[cursor];
        }
        low<<=1;
        if(++count==0) {
            count=-8;
            coder->buffer[coder->position]=(unsigned char)(low>>24);
            ++coder->position;
            low&=0x00ffffff;
        }
    }
    coder->low=low;
    coder->range=range;
    coder->count=count;
}

// Clean-room spec001bcf70 and complete native5B tail jump to1C4F80.
// Preserve the genuine existing provider ABI; this introduces no alias.
struct Rva009B4680State;
int Rva009B4680Normalize(Rva009B4680State *);
extern "C" int VP6_bitread1(Rva009B4680State *coder)
{
    return Rva009B4680Normalize(coder);
}
