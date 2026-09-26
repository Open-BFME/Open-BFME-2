// cl: /O2 /MD
// ??_G?$SimpleDynVecClass@E@@UAEPAXI@Z @0x001A8050 30B
// Deleting dtor slot 0 of vtable 0x007D71EC; calls pinned ??1?$SimpleDynVecClass@E@@UAE@XZ at 0x001A7F20 then rowed operator delete at 0x0002FD60; StreakLine donor virtual dtor; ICF-folded with bfmeGo943E.
template<class T> class SimpleDynVecClass { public: __declspec(noinline) virtual ~SimpleDynVecClass(); private: int m_famgen; };
template<> SimpleDynVecClass<unsigned char>::~SimpleDynVecClass() { m_famgen = 0; }
void famgenDelete(SimpleDynVecClass<unsigned char> *p) { delete p; }
