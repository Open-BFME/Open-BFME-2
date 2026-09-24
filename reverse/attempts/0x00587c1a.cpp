// ?erase@?$vector@UBfmePod60@@V?$allocator@UBfmePod60@@@_STL@@@_STL@@QAEPAUBfmePod60@@PAU3@0@Z
// partial score=0.97 date=2026-09-24
// cl: /O1 /EHsc /MD /D_CRTIMP=
struct BfmePod28 { int a[7]; };
struct BfmePod44 { int a[11]; };
struct BfmePod52 { int a[13]; };
struct BfmePod60 { int a[15]; };
namespace _STL {
struct __false_type {};
template<class T> T* __copy_ptrs(T* first,T* last,T* result,const __false_type&);
template<class T> class allocator {};
template<class T,class A> class vector {
public:
    T* erase(T* first,T* last);
private:
    T* m_start;
    T* m_finish;
    T* m_endOfStorage;
};
template<class T,class A>
T* vector<T,A>::erase(T* first,T* last) {
    __false_type tag;
    T* i=__copy_ptrs(last,m_finish,first,tag);
    m_finish=i;
    return first;
}
template BfmePod28* vector<BfmePod28,allocator<BfmePod28> >::erase(BfmePod28*,BfmePod28*);
template BfmePod44* vector<BfmePod44,allocator<BfmePod44> >::erase(BfmePod44*,BfmePod44*);
template BfmePod52* vector<BfmePod52,allocator<BfmePod52> >::erase(BfmePod52*,BfmePod52*);
template BfmePod60* vector<BfmePod60,allocator<BfmePod60> >::erase(BfmePod60*,BfmePod60*);
}
