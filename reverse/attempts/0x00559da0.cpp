// ?rva00559DA0@Rva00559DA0@@QAEHPAURva00559DA0Record@@E@Z
// partial score=0.85 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
class Rva005B8053 {
public: void *rva005B8053(const unsigned char *);
 void *header;char opaque[8];
};
struct Rva00559DA0Node {char opaque[0x12];unsigned short value;};
struct Rva00559DA0Record {
 char opaque00[4];Rva005B8053 first,second;
 char opaque1c[0x150-0x1c];int enabled;
};
class Rva00559DA0 {
 char opaque00[0x2c];float scaleFirst,scaleSecond;
public:int rva00559DA0(Rva00559DA0Record *,unsigned char);
};
int Rva00559DA0::rva00559DA0(Rva00559DA0Record *record,unsigned char code) {
 if(!record->enabled)return 0;
 int amount=0;
 unsigned char key=code;
 Rva00559DA0Node *node=(Rva00559DA0Node *)record->first.rva005B8053(&key);
 if(node!=record->first.header)amount=node->value;
 int result=(int)(amount*scaleFirst);
 amount=0;
 key=code;
 node=(Rva00559DA0Node *)record->second.rva005B8053(&key);
 if(node!=record->second.header)amount=node->value;
 result=(int)(result+amount*scaleSecond);
 int zero=0;
 const int &maximum=result<zero ? zero : result;
 return maximum;
}
