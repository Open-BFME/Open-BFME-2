// ?Rva004F6A1A@@YA?AVRva004F6318Entry@@PBHABVRva004F6093Holder@@@Z
// cl: /O1 /G7 /arch:SSE /MD /EHsc
// Retail 0x004F6A1A..0x004F6A35: hidden result at [ebp+8], key at
// [ebp+0xc], holder at [ebp+0x10]. Calls the rowed entry constructor
// 0x004F6318 and returns the result buffer in EAX. The otherwise dead
// zeroed stack word is emitted by MSVC for this return-by-value lifetime.
// Target layout: entry key at +0 and holder at +4, from that constructor;
// holder is one pointer, as in the rowed 0x004F6093 copy-constructor view.
// The factory and opaque class names are structural labels, not retail names.
class Rva004F6093Holder {public:Rva004F6093Holder(const Rva004F6093Holder&);~Rva004F6093Holder();void *referent;};
class Rva004F6318Entry {
public:Rva004F6318Entry(const int*,const Rva004F6093Holder&);
private:int key;Rva004F6093Holder holder;
};
Rva004F6318Entry Rva004F6A1A(const int*key,const Rva004F6093Holder &holder) {
 return Rva004F6318Entry(key,holder);
}
