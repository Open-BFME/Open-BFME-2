// cl: /O1 /G7 /EHsc /MD /DNDEBUG
// Native3F65AD..3F6619 and3F664F..3F6672. STLport4.5.3 resize
// algorithm; native ctor3F5322/dtor3F535B and 48B stride establish the
// element ABI. Replace obsolete helper placeholders with the independently
// recovered range erase3F5EC4 and fill insert3F61C6 providers. The latter
// scoped record view has the same independently verified48B element ABI;
// it does not establish an original application type. New wrapper constructs
// that element directly in the outgoing by-value argument as retail does.
struct Rva003F610FElement {
 Rva003F610FElement();Rva003F610FElement(const Rva003F610FElement&);~Rva003F610FElement();
 unsigned char consumed[48];
};
struct Rva003F61C6Record;
namespace _STL {
template<class T>class allocator;
template<class T,class A>class vector;
template<>class vector<Rva003F610FElement,allocator<Rva003F610FElement> > {
public:Rva003F610FElement*erase(Rva003F610FElement*,Rva003F610FElement*);
};
template<>class vector<Rva003F61C6Record,allocator<Rva003F61C6Record> > {
public:void _M_fill_insert(Rva003F61C6Record*,unsigned,const Rva003F61C6Record&);
};
}
class Rva003F65ADVector {public:
 unsigned size()const{return finish-start;} Rva003F610FElement*begin(){return start;} Rva003F610FElement*end(){return finish;}
 void resize(unsigned,Rva003F610FElement);
private:Rva003F610FElement*start,*finish,*limit;
};
void Rva003F65ADVector::resize(unsigned count,Rva003F610FElement value) {
 if(count<size()) ((_STL::vector<Rva003F610FElement,_STL::allocator<Rva003F610FElement> >*)this)->erase(begin()+count,end());
 else {unsigned extra=count-size();((_STL::vector<Rva003F61C6Record,_STL::allocator<Rva003F61C6Record> >*)this)->_M_fill_insert((Rva003F61C6Record*)end(),extra,(const Rva003F61C6Record&)value);}
}
class Rva003F664FOwner {public:void rva003F664F(unsigned int);};
void Rva003F664FOwner::rva003F664F(unsigned int count){
((Rva003F65ADVector*)this)->resize(count,Rva003F610FElement());
}
