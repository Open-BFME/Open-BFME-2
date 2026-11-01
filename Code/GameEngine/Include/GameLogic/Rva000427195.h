/* Target facts: this placeholder covers non-polymorphic STLport hash-table views, with no evidenced base or virtual functions. Copy construction (RVA 0x001FE300) calls assignment (0x001FDEBC); assignment self-checks, clears at 0x003A2A41 and calls the copy worker at 0x001FDC0F. Destruction (0x001FDEDB) calls clear and frees the pointer at +4 through 0x00030830; neither body stores a vptr. Their existing ledger signatures use struct references (ABU0 and AAU0).
   Target layout: bucketIndex (0x00223149) subtracts the +4 bucket pointer from the +8 end pointer, divides by four and reduces the string hash (0x00055041) modulo that count. Resize (0x00212858) swaps the three-word vector at +4; clear (0x003A2A41) walks node links at +0, destroys nodes through 0x001FD9EF, clears buckets and zeroes the element count at +0x10. Aggregate assignment 0x001FE78E calls this table at receiver +0x100 (0x001FE85E), then the next subobject at +0x114 (0x001FE870), bounding the modeled storage to 0x14 bytes; the leading four bytes remain opaque. first (0x00427195) fills a two-word cursor with the first node and this. insertUniqueNoresize (0x00419331), insertUnique (0x004193AD), insertWithGrow (0x001F93A3) and createNode (0x002CF9DC) retain their ledger names; the two insert overloads are 0x00415662 and 0x002E03EF.
   Target declarations: each rvaXXXXXXXX method below retains the existing ledger spelling at RVA 0xXXXXXXXX, except the existing pinned node-helper spellings at 0x00056E53, 0x00212354, 0x002ACFD6 and 0x004152E6, called by retail insert bodies 0x00058C6F, 0x00212A5A, 0x001F8F2A and 0x0041539F respectively. Parameter and result placeholder types do not identify the original hash specializations. All rowed special members and helpers are declared out of line. */
#pragma once

class AsciiString;
class Rva000411084;
class Rva0022304A;
class Rva00415B54;
class Gen_003A8BE0;
struct NoCaseTreeValue4;
struct TreeHintPayload00207343;
struct TreeHintPayload00410A86;
struct TreeHintPayload00410B17;
struct TreeHintPayload00410E23;
struct TreeHintPayload0005808E;
struct Rva002241ACNode;
struct HashNode00056E53;
struct AudioCacheCursor;
struct VideoPair;
struct InsertRet001F8F2A;
struct InsertRet00212A5A;
struct InsertRet002E01F7;
struct InsertRet0041539F;
struct InsertRet00419331;
struct InsertRet0041FA92;
namespace _STL { template<class A, class B> struct pair; }

struct Rva000427195
{
    Rva000427195(const Rva000427195 &);
    Rva000427195 &operator=(const Rva000427195 &);
    ~Rva000427195();

    void rva003A2A41();
    void rva00212858(unsigned int);
    int bucketIndex(const AsciiString *);
    int rva00223429(const AsciiString *);
    void *first(Rva000411084 *);
    AudioCacheCursor rva00427195();
    void rva002ADCE1(const VideoPair &);
    void rva003A37DC(VideoPair);
    void *rva000A7976(const _STL::pair<const AsciiString, NoCaseTreeValue4> *);
    void *createNode(const _STL::pair<const AsciiString, NoCaseTreeValue4> *);
    void *rva00410997(const void *);
    void *rva00410A86(const void *);
    void *rva00212354(const void *);
    void *rva002ACFD6(const void *);
    void *rva004152E6(const void *);
    HashNode00056E53 *rva00056E53(const _STL::pair<const AsciiString, TreeHintPayload0005808E> &);
    Rva002241ACNode *rva002241AC(const Rva0022304A &);
    void *rva0020D613(const _STL::pair<const AsciiString, NoCaseTreeValue4> &);
    void *rva0020D638(const _STL::pair<const AsciiString, NoCaseTreeValue4> &);
    void *rva000A7A63(const _STL::pair<const AsciiString, NoCaseTreeValue4> *);
    _STL::pair<const AsciiString, NoCaseTreeValue4> *rva002234BA(const _STL::pair<const AsciiString, NoCaseTreeValue4> *);
    void *rva0031C7D6(const _STL::pair<const AsciiString, NoCaseTreeValue4> &);
    void *rva003A2F08(const _STL::pair<const AsciiString, TreeHintPayload00207343> &);
    _STL::pair<const AsciiString, TreeHintPayload00410A86> *rva00410DDF(const _STL::pair<const AsciiString, TreeHintPayload00410A86> *);
    _STL::pair<const AsciiString, TreeHintPayload00410B17> *rva00410E67(const _STL::pair<const AsciiString, TreeHintPayload00410B17> *);
    _STL::pair<const AsciiString, TreeHintPayload00410E23> *rva00410E23(const _STL::pair<const AsciiString, TreeHintPayload00410E23> *);
    _STL::pair<const AsciiString, TreeHintPayload0005808E> *rva00058C6F(const _STL::pair<const AsciiString, TreeHintPayload0005808E> *);
    _STL::pair<const AsciiString, Gen_003A8BE0> *rva00216D5C(const _STL::pair<const AsciiString, Gen_003A8BE0> &);
    void *rva000A7B3C(const AsciiString *);
    void *rva0041112B(const AsciiString *);
    void *rva004112A0(const AsciiString *);
    void **rva0031DB83(const AsciiString &);
    void *rva003F78A9(void *, const AsciiString *);
    void *rva003F797C(void *, const AsciiString *);
    void *rva003F7B0E(void *, const AsciiString *);
    InsertRet001F8F2A rva001F8F2A(const void *);
    InsertRet001F8F2A insertWithGrow(const void *);
    InsertRet00212A5A rva00212A5A(const void *);
    InsertRet00212A5A rva00213925(const void *);
    InsertRet002E01F7 rva002E01F7(const void *);
    InsertRet002E01F7 rva002E035B(const void *);
    InsertRet0041539F rva0041539F(const void *);
    InsertRet0041539F rva0041557A(const void *);
    InsertRet00419331 insertUniqueNoresize(const void *);
    InsertRet00419331 insertUnique(const void *);
    InsertRet00419331 rva004198EB(const void *);
    InsertRet00419331 rva00419967(const void *);
    InsertRet00419331 rva004193D1(const void *);
    InsertRet00419331 rva0041998B(const void *);
    InsertRet0041FA92 rva0041FA92(const void *);
    InsertRet0041FA92 rva0041FC77(const void *);
    InsertRet0041FA92 rva0041FCD6(const void *);
    InsertRet0041539F insert(const _STL::pair<const AsciiString, Rva00415B54 *> &);
    InsertRet002E01F7 insert(const _STL::pair<const AsciiString, int> &);

    unsigned char field00[4];
    void **m_beginBuckets;
    void **m_endBuckets;
    void **m_storageEnd;
    unsigned int m_numElements;
};
