// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native 005C4A39 allocates24 and calls verified constructor005C4986,
// passing the explicit argument and the receiver as two words. Original
// factory/class names and the receiver relationship remain unknown.
class Rva005C4986 {
public: Rva005C4986(unsigned int a,unsigned int b);
private: char m_pad[0x20];int m_20;
};
class Rva005C4A39Factory { public: Rva005C4986 *create(unsigned int a); };
Rva005C4986 *Rva005C4A39Factory::create(unsigned int a) {
 return new Rva005C4986(a,(unsigned int)this);
}
