// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Complete 10B body 531D36..531D40 calls rowed operator delete[] 2FD80
// on word 8, unconditionally. No element-destructor call or clearing store.
// Original owner and payload type remain unknown; a borrowed prefix only.
void operator delete[](void *);
struct Rva00531D36ArrayPrefix {
    unsigned char prefix[8];
    void *storage;
    void releaseArray();
};
void Rva00531D36ArrayPrefix::releaseArray() { operator delete[](storage); }
