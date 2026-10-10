// ?rva003B6676@Rva003B573E@@QAEXXZ
// partial score=0.83 date=2026-10-10
// ?rva003B6676@Rva003B573E@@QAEXXZ
// partial score=0.83 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /Oy- /DNDEBUG /MD /EHsc
// Native3B6676 walks 20B records from head1C, clearing node cells10 and
// setting referencesE to1. The rowed node destructor448C and element drain
// supply ownership; field purposes beyond that remain neutral.
void __cdecl operator delete(void *block);
class Rva003B448C
{
public:
    ~Rva003B448C();
    Rva003B448C *next;
};
struct Rva003B6676Record
{
    int previous;
    int next;
    void *name;
    unsigned char released;
    unsigned char padding;
    unsigned short references;
    Rva003B448C **nodes;
};
class Rva003B573E
{
public:
    void rva003B6676();
private:
    char sorted[12];
    Rva003B6676Record *records;
    void *finish;
    void *capacity;
    int freeHead;
    int head;
};
void Rva003B573E::rva003B6676()
{
    for (int index = head; index != -1; index = records[index].previous)
    {
        Rva003B6676Record *record = &records[index];
        Rva003B448C **cell = record->nodes;
        while (*cell)
        {
            Rva003B448C *node = *cell;
            Rva003B448C *next = node->next;
            if (node)
            {
                node->Rva003B448C::~Rva003B448C();
                ::operator delete(node);
            }
            *cell = next;
        }
        record->references = 1;
    }
}
