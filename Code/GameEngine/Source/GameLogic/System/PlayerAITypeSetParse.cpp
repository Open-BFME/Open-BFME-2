// cl: /O1 /Oy- /G7 /MD /EHsc
// BF1 BfmeConv1950 resize guide and native215AF1..215B14 RET4.
// Actual16B record holds a narrow name and owning12B library-map vector.
// Verified15334F default constructor only clears those fields; verified
// record copy2154F3 is deep. An explicit copy declaration therefore replaces
// the unsupported shallow implicit copy and permits direct by-value creation.
// Existing BfmeItemERE/BfmeVecERE names preserve the owned resize ABI only.
class Rva0015334F { public: __declspec(nothrow) Rva0015334F(); private: char storage[16]; };
struct BfmeItemERE : Rva0015334F { __declspec(nothrow) __forceinline BfmeItemERE():Rva0015334F(){} BfmeItemERE(const BfmeItemERE&); ~BfmeItemERE(); };
class BfmeVecERE {public:void bfmeResizeERE(unsigned count,BfmeItemERE item);};
class Rva00215AF1 { public: void rva00215AF1(unsigned count); };
void Rva00215AF1::rva00215AF1(unsigned count) { ((BfmeVecERE*)this)->bfmeResizeERE(count,BfmeItemERE()); }
