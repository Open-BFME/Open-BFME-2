// cl: /O2 /G6 /DNDEBUG /MD /EHsc
// Complete 10B body 14D90..14D9A calls rowed operator delete[] 2FD80
// on word 0, unconditionally. Original owner, payload type and allocation
// extent are unknown; this is only a borrowed pointer prefix.
void operator delete[](void *);
struct Rva00014D90ArrayPrefix {
    void *storage;
    void releaseArray();
};
void Rva00014D90ArrayPrefix::releaseArray() { operator delete[](storage); }
