// cl: /O2 /G7 /arch:SSE /MD /DNDEBUG /EHs-c-
// Native0013B6D0..0013B707 RET0 =55B. RenderObjClass's target vtable
// BD2F68 slot188 and the matched Set_Visible body13B710 associate this
// query with the scene token at88. Original name/type details are not
// asserted: the existing shared donor header's flag-only Is_Visible body
// does not implement this target-specific token test.
// Target independently proves self slot104(+1A0), Scene pointer78 and
// Scene slot17(+44) returning a token. Nonzero self result short-circuits;
// otherwise scene/token must exist and scene's current token must agree.
// Uncalled reserved virtual declarations preserve only slot positions.
// Separate negative guard puts the native false epilogue after true.
struct SceneTokenView {  virtual void v0();
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
 virtual void v16(); virtual unsigned int slot17(); };
class Rva0013B6D0 {
public:
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
 virtual void v27();
 virtual void v28();
 virtual void v29();
 virtual void v30();
 virtual void v31();
 virtual void v32();
 virtual void v33();
 virtual void v34();
 virtual void v35();
 virtual void v36();
 virtual void v37();
 virtual void v38();
 virtual void v39();
 virtual void v40();
 virtual void v41();
 virtual void v42();
 virtual void v43();
 virtual void v44();
 virtual void v45();
 virtual void v46();
 virtual void v47();
 virtual void v48();
 virtual void v49();
 virtual void v50();
 virtual void v51();
 virtual void v52();
 virtual void v53();
 virtual void v54();
 virtual void v55();
 virtual void v56();
 virtual void v57();
 virtual void v58();
 virtual void v59();
 virtual void v60();
 virtual void v61();
 virtual void v62();
 virtual void v63();
 virtual void v64();
 virtual void v65();
 virtual void v66();
 virtual void v67();
 virtual void v68();
 virtual void v69();
 virtual void v70();
 virtual void v71();
 virtual void v72();
 virtual void v73();
 virtual void v74();
 virtual void v75();
 virtual void v76();
 virtual void v77();
 virtual void v78();
 virtual void v79();
 virtual void v80();
 virtual void v81();
 virtual void v82();
 virtual void v83();
 virtual void v84();
 virtual void v85();
 virtual void v86();
 virtual void v87();
 virtual void v88();
 virtual void v89();
 virtual void v90();
 virtual void v91();
 virtual void v92();
 virtual void v93();
 virtual void v94();
 virtual void v95();
 virtual void v96();
 virtual void v97();
 virtual void v98();
 virtual void v99();
 virtual void v100();
 virtual void v101();
 virtual void v102();
 virtual void v103();
 virtual int slot104();
 int queryVisible();
private:
 unsigned char gap[0x74]; SceneTokenView *scene; unsigned char gap7c[0xC]; unsigned int token;
};
int Rva0013B6D0::queryVisible() {
 if(slot104()) return 1;
 if(!scene || !token || scene->slot17()!=token) return 0;
 return 1;
}
