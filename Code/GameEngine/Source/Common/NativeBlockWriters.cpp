// cl: /O1 /MD
// Three independently bounded native block writers. 0x0028A5D5/19B
// copies 128 bytes to receiver+0x10; 0x0052AF5F/17B copies 12 bytes to
// +0x18; 0x005975E1/17B copies 12 bytes to +0x30. Each takes one source
// pointer on the stack and returns with RET4; ESI/EDI are saved/restored.
// Raw DWORD aggregates encode observed copy sizes and offsets. Original
// classes, payload meanings and complete object extents remain unknown.
struct Block128 { unsigned int words[32]; };
struct Block12 { unsigned int words[3]; };
class Rva0028A5D5 { public: void write(const Block128 &b); private: char pad[0x10]; Block128 block; };
void Rva0028A5D5::write(const Block128 &b) { block=b; }
class Rva0052AF5F { public: void write(const Block12 &b); private: char pad[0x18]; Block12 block; };
void Rva0052AF5F::write(const Block12 &b) { block=b; }
class Rva005975E1 { public: void write(const Block12 &b); private: char pad[0x30]; Block12 block; };
void Rva005975E1::write(const Block12 &b) { block=b; }
