// cl: /O1 /G7 /DNDEBUG /MD /arch:SSE
// ?rva00466D93@Rva00466D93@@UAEHPBVThingTemplate@@PAVObject@@@Z @0x00466D93 22B
// Evidence: Native466D93..466DA9 RET8, full22B. Same ExitInterface slot1 in tables843FFC/845CFC/846F48/8472F4, between busy check and exit body. ZH ExitInterface/OpenContain declarations supply template/object arguments; native Heal update466CF3..466D01 pushes template pointer and object into corresponding shared slot. Receiver-30 primary vslot6C forwards second Object pointer and maps bool to0/-1; complete primary class identity and virtual predicate semantic name unproven, retained address names.
class Object;
class ThingTemplate;
class Rva00466D93Primary {public:
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual bool v27(Object*);};
class Rva00466D93 {public:virtual int rva00466D93(const ThingTemplate*,Object*);};
int Rva00466D93::rva00466D93(const ThingTemplate*,Object*arg){return reinterpret_cast<Rva00466D93Primary*>(reinterpret_cast<char*>(this)-0x30)->v27(arg)?0:-1;}
