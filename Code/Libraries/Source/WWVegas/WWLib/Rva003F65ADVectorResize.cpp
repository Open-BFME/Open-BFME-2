// cl: /O1 /G7 /EHsc /MD /DNDEBUG
// ?resize@Rva003F65ADVector@@QAEXIURva003F65ADRecord@@@Z @0x003F65AD 108B
// Banked attempt reverse/attempts/0x003f65ad.cpp, re-verified exact against the current ledger
// (its callees have since been rowed or pinned); landed unchanged by the
// banked-attempt sweep. Identity and evidence: see reverse/re_attempts.log.
struct Rva003F65ADRecord {~Rva003F65ADRecord();unsigned char consumed[48];};
class Rva003F65ADVector {public:
 unsigned size()const{return finish-start;} Rva003F65ADRecord*begin(){return start;} Rva003F65ADRecord*end(){return finish;}
 void resize(unsigned,Rva003F65ADRecord);
private:
 Rva003F65ADRecord*start;Rva003F65ADRecord*finish;Rva003F65ADRecord*limit;
 Rva003F65ADRecord*erase(Rva003F65ADRecord*,Rva003F65ADRecord*);
 void fill(Rva003F65ADRecord*,unsigned,const Rva003F65ADRecord&);
};
void Rva003F65ADVector::resize(unsigned count,Rva003F65ADRecord value) {
 if(count<size())erase(begin()+count,end());
 else {unsigned extra=count-size();fill(end(),extra,value);}
}
