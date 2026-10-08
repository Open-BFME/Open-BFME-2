// ?resize@?$vector@UBfmePod28@@V?$allocator@UBfmePod28@@@_STL@@@_STL@@QAEXI@Z
// cl: /O1 /G7 /arch:SSE /MD /EHsc
// Native00584A3D..00584A75(56B) is the one-count member wrapper for the
// existing by-value28B resize overload005849F4. ECX remains the vector and
// ret4 consumes one count, refuting the old free-function guess.
// Target default writes: word0 zero; float slots4/8/C zero; byte10 one;
// words14/18 zero. Padding11..13 stays unspecified; no element identity claim.
// BfmePod28 retains the existing stride-only provider spelling. Its special
// member declarations model native direct construction into the outgoing
// value argument and empty cleanup; these C++ lifetime details are compiler-
// shape inference, not a donor class or target-name assertion. No copy call
// or destructor symbol is emitted. All56B and the sole helper relocation match.
struct BfmePod28 {
 int state;float x,y,z;bool flag;char pad[3];int a,b;
 BfmePod28(const BfmePod28 &);
 ~BfmePod28(){}
 BfmePod28():state(0),flag(true),a(0),b(0) {x=0.0f;y=0.0f;z=0.0f;}
};
namespace _STL {
template<class T>class allocator {};
template<class T,class A>class vector {
public:
 void resize(unsigned int n,BfmePod28 value);
 void resize(unsigned int n);
private:
 T *start,*finish,*limit;
};
template<class T,class A>void vector<T,A>::resize(unsigned int n) {resize(n,BfmePod28());}
template void vector<BfmePod28,allocator<BfmePod28> >::resize(unsigned int);
}
