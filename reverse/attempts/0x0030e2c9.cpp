// ?Rva0030E2C9Visit@@YAXPAX@Z
// partial score=0.886 date=2026-10-04
// cl: /O1 /MD /EHs-c-
// Clean donor: Open-BFME-1 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24,
// game/GameEngine/Source/Common/BfmeConv888.cpp, bfmeGoEYE.
// Target evidence: complete 35-byte entry30E2C9 stores its sole cdecl
// argument at VA E00938 and walks the head reached through VA E00940.
// Each node is the receiver of native492-byte entry30DEAE; next is +4.
// Original owner/global identities and the callee's behavior are unknown.
// The caller ignores the callee's return; void here is only a call-site view.
// No retail storage providers or body for30DEAE have been recovered here.
struct Rva0030DEAENode
{
    void visit();
    unsigned char opaque00[4];
    Rva0030DEAENode *next04;
};

struct Rva0030E2C9List
{
    Rva0030DEAENode *head00;
};

extern void *Rva00E00938Context;
extern Rva0030E2C9List *Rva00E00940List;

void __cdecl Rva0030E2C9Visit(void *context)
{
    Rva00E00938Context = context;
    for (Rva0030DEAENode *node = Rva00E00940List->head00;
         node; node = node->next04)
        node->visit();
}
