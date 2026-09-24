// ??$__introsort_loop@PAHHHU?$greater@H@_STL@@@_STL@@YAXPAH00HU?$greater@H@0@@Z
// partial score=0.99 date=2026-09-24
// cl: /O1 /EHsc /MD /D_CRTIMP=
namespace _STL {
template <class T> struct greater { bool operator()(const T&, const T&) const; };
template <class T,class C> const T& __median(const T&,const T&,const T&,C);
template <class I,class T,class C> I __unguarded_partition(I,I,T,C);
template <class I,class C> void partial_sort(I,I,I,C);
template <class I,class T,class S,class C>
void __introsort_loop(I first,I last,T*,S depth,C comp) {
    while (last-first>16) {
        if (depth==0) { partial_sort(first,last,last,comp);return; }
        --depth;
        I middle = first + (last-first)/2;
        I cut=__unguarded_partition(first,last,T(__median(*first,*middle,*(last-1),comp)),comp);
        __introsort_loop(cut,last,(T*)0,depth,comp);
        last=cut;
    }
}
template void __introsort_loop<int*,int,int,greater<int> >(int*,int*,int*,int,greater<int>);
}
