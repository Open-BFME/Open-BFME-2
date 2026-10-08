// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfmealloc
// stlport
//
// The insert path of map<int, Gen_004E9FD0>: its pair copy (0x00416055) copies
// one key word, then calls the rowed Gen_004E9FD0 copy constructor (0x00415FAB,
// BfmeMixedSixCopyWN.cpp) for the value, and its node constructor (0x004168FD)
// allocates 0x30 bytes, a 0x10-byte tree header plus the 0x20-byte pair. The
// value is 28 bytes. The key is a
// signed 32-bit type (the inserts compare it signed); int stands in, as in
// stlport_map_int_int_os.cpp. Recipe and flags are
// stlport_map_int_vector_pod128.cpp's. Only the insert overloads are
// instantiated alongside the native subscript below.

#include <map>

class Gen_004E9FD0
{
public:
	Gen_004E9FD0(const Gen_004E9FD0 &other);
    Gen_004E9FD0() {
        m_words[1]=0; m_words[2]=0; m_words[3]=0;
        m_words[5]=0; m_words[6]=0;
    }
    ~Gen_004E9FD0();
private:
    unsigned int m_words[7];
};

typedef _STL::map<int, Gen_004E9FD0> IntGen004E9FD0Map;

template _STL::pair<IntGen004E9FD0Map::iterator, bool> IntGen004E9FD0Map::insert(const IntGen004E9FD0Map::value_type &);
template IntGen004E9FD0Map::iterator IntGen004E9FD0Map::insert(IntGen004E9FD0Map::iterator, const IntGen004E9FD0Map::value_type &);

// The subscript at 0x416BD9 constructs only the five string words, as does
// BuddyInfo's verified default constructor at 0x415F97. Native calls connect
// the existing Gen copy/insertion cluster to BuddyInfo's destructor3820FE.
// Keep the address-derived value name: the ledger has not reconciled the two
// class names. The aliases below record the proven common call ABIs.
template<> Gen_004E9FD0 &IntGen004E9FD0Map::operator[](const int &key)
{
    iterator it=lower_bound(key);
    if(it==end() || key < it->first)
        it=insert(it,value_type(key,Gen_004E9FD0()));
    return it->second;
}
Gen_004E9FD0 &(IntGen004E9FD0Map::*emitGenSubscript)(const int &)=&IntGen004E9FD0Map::operator[];

// The lower-bound helper observes only the common tree header and signed key.
// The pair constructor accepts the same two addresses and copies the same value.
#pragma comment(linker, "/alternatename:??1Gen_004E9FD0@@QAE@XZ=??1BuddyInfo@@QAE@XZ")
