// cl: /DNDEBUG /MD /EHsc
// ?rva0028B38D@Object@@QBEHXZ, retail 0x0028B38D, 25 bytes.
// Object AI query: if the AI at +0x258 is present returns its slot 0x168
// byte result zero-extended, else 0. Evidence: AI at +0x258 per
// Rva004884B7Check and Object_isAbleToAttack, slot 0x168 from retail call,
// callers at 0x0034B5F8 0x0036FEC0 0x003C832A test al. Int return proven by
// byte-exact movzx shape (bool outer tail-jumps to 21B).
class AIUpdateInterface
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
	virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
	virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
	virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55();
	virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
	virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63();
	virtual void v64(); virtual void v65(); virtual void v66(); virtual void v67();
	virtual void v68(); virtual void v69(); virtual void v70(); virtual void v71();
	virtual void v72(); virtual void v73(); virtual void v74(); virtual void v75();
	virtual void v76(); virtual void v77(); virtual void v78(); virtual void v79();
	virtual void v80(); virtual void v81(); virtual void v82(); virtual void v83();
	virtual void v84(); virtual void v85(); virtual void v86(); virtual void v87();
	virtual void v88(); virtual void v89();
	virtual bool slot90();
};

class Object
{
public:
	int rva0028B38D() const;
private:
	char m_pad[0x258];
	AIUpdateInterface *m_ai; // +0x258
};

int Object::rva0028B38D() const
{
	AIUpdateInterface *ai = m_ai;
	if (ai != 0)
		return ai->slot90();
	return 0;
}
