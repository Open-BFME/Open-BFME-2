// cl: /O1 /G7 /arch:SSE /Oy- /DNDEBUG /MD /EHsc
// Native3B56DC..3B573E is the full98-byte drain, a masked instruction twin
// of verified3B6676. The sole callee difference selects owned BfmeNodeZ
// destructor3B3F5E instead of BfmeNodeZ destructor; both node links are0.
// Native head1C,20-byte record stride, next-index0, node-cell10 and countE
// prove the accessed layout. The owner/method spellings remain neutral.
// Matched sibling supplies the same-valued record/node pointer forms.
void __cdecl operator delete(void *block);
class BfmeNodeZ
{
public:
    ~BfmeNodeZ();
    BfmeNodeZ *next;
};
struct Rva003B56DCRecord
{
    int previous;
    int next;
    void *name;
    unsigned char released;
    unsigned char padding;
    unsigned short references;
    BfmeNodeZ **nodes;
};
class Rva003B573E
{
public:
    void rva003B56DC();
private:
    char sorted[12];
    Rva003B56DCRecord *records;
    void *finish;
    void *capacity;
    int freeHead;
    int head;
};
void Rva003B573E::rva003B56DC()
{
    for (int index = head; index != -1; index = records[index].previous)
    {
        Rva003B56DCRecord *record = &records[index];
        // Codegen: same-valued PHIs on record and node close the native register roles of the bucket walk.
        BfmeNodeZ **cell = (record?record:record)->nodes;
        while (*cell)
        {
            BfmeNodeZ *node = *cell;
            BfmeNodeZ *next = (node?node:node)->next;
            if (node)
            {
                (node?node:node)->BfmeNodeZ::~BfmeNodeZ();
                ::operator delete(node);
            }
            *cell = next;
        }
        (record?record:record)->references = 1;
    }
}
