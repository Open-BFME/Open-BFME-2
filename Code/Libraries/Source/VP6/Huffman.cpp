// cl: /MD
// Retail prefix-tree walk; PDB supplies the original VP6 identity.
// Target/donor provenance: reverse/vp6_structural_evidence.json, huffman_scalar.
// Authored from target disassembly; source-handoff body text is not imported.
// Only the initialized low byte is used before a complete edge is loaded.
union Vp6HuffmanEdge {
    unsigned value;
    struct { unsigned low:8; unsigned high:24; } bytes;
    struct { unsigned leaf:1; unsigned index:7; unsigned rest:24; } fields;
};
struct Vp6HuffmanNode {
    Vp6HuffmanEdge left;
    Vp6HuffmanEdge right;
    unsigned char probability;
};
int Rva009B4600DecodeBool(void *,int);

extern "C" int VP6_DecodeValue(void *coder,Vp6HuffmanNode *tree)
{
    Vp6HuffmanEdge edge;
    edge.bytes.low=0;
    do {
        Vp6HuffmanNode *node=&tree[edge.fields.index];
        if(Rva009B4600DecodeBool(coder,node->probability)) edge=node->right;
        else edge=node->left;
    } while(!edge.fields.leaf);
    return edge.fields.index;
}

struct Vp6EncodeCoder {
    unsigned char prefix[0x18];
    int measureCost;
};
struct Rva009AC4B0State;
extern void __cdecl Rva009AC4B0AddValue(Rva009AC4B0State *,int,int);
extern "C" void __cdecl VP6_EncodeBool(void *,int,int);

// Target identity is supported by the VP6 PDB record and existing huffman
// evidence. The cursor tree walk and field layout follow the BFME1 donor;
// measureCost's target interpretation remains supported by the banked body.
extern "C" void VP6_EncodeValue(Vp6EncodeCoder *coder,
    const Vp6HuffmanNode *nodes,int bits,int bitCount)
{
    unsigned int node=0;
    int bitIndex=bitCount;
    --bitIndex;
    if(bitIndex<0)
        return;
    do {
        int bit=(bits>>bitIndex)&1;
        if(coder->measureCost!=0)
            Rva009AC4B0AddValue((Rva009AC4B0State *)coder,bit,nodes[node].probability);
        else
            VP6_EncodeBool(coder,bit,nodes[node].probability);
        if(bit)
            node=(nodes[node].right.value>>1)&0x7f;
        else
            node=(nodes[node].left.value>>1)&0x7f;
        --bitIndex;
    } while(bitIndex>=0);
}
