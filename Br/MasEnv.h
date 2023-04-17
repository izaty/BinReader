// MasEnv.h: MasEnv クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MASENV_H__131E2381_57D1_11D3_AAC6_00A0C924BC0A__INCLUDED_)
#define AFX_MASENV_H__131E2381_57D1_11D3_AAC6_00A0C924BC0A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class AFX_EXT_CLASS MasEnv  
{
public:
	//
	// not used
	//
	MasEnv();
	virtual ~MasEnv();

public:
	//
	// Directory
	//
	enum DIRSTATUS {
		EXIST = 0,
		NOT_EXIST,
		NOT_REGISTERED,
		NOT_DIRECTORY,
		// Appended by izaty on Aug.5,'05
		// start
		EXIST_OLD,
		// end
	};
	// System Directory
	static void PASCAL GetSystemEnv(CString& strDir);
	// Private Directory
	static void PASCAL GetPrivateEnv(CString& strDir, DIRSTATUS& rStatus);
	// Modified by izaty on Apr.19,'04
	// start
	static void PASCAL SetPrivateEnv(CString strDir, 
		BOOL bCreateShortCut = TRUE);
	//static void PASCAL SetPrivateEnv(CString strDir);
	// end
	static CString PASCAL GetDefaultPrivateDir();
	static void PASCAL RegPrivateEnv(CString strDir);

	static void PASCAL GetSystemEnv(CString& strSysDir, CString& strSysPath, 
		CString& strDefPath);
	static void PASCAL GetPrivateEnv(CString& strPrvDir, CString& strPrvPath);

	// Appended by izaty on Mar.15,'05
	// start
	static CString PASCAL GetSystemIniName();
	static CString PASCAL GetPrivateIniName();
	// end

	// Appended by izaty on Aug.22,'06
	// start
	static void PASCAL GetCACheEnv(CString& strDir, DIRSTATUS& rStatus);
	static void PASCAL SetCACheEnv(CString& strDir);
	// end
public:
	//
	// Ini File
	//
	enum DIRTYPE {
		// Module
		MODULE = 0, 
		// System
		SYS_DATA,			// Data
		SYS_MOLECULAR,		// MolDB
		SYS_CRYSTAL,		// CryDB
		SYS_MOLCRYSTAL,		// McrDB
		SYS_POTLIB,			// PotLib
		SYS_ANALYSIS,		// Analysis
		SYS_TEMPLATE,		// Template
		SYS_BITMAPS,		// Bitmaps
		// Appended by izaty on Apr.5,'05
		// start
		SYS_MATERIALS,		// Materials
		SYS_COND,			// CondTmpl
		// end
		// Appended by izaty on Jul.8,'05
		// start
		SYS_POLYMER,		// Polymer
		// end
		SYS_END,			// (End of System)
		// User
		DATA,				// Data
		MOLECULAR,			// MolDB
		CRYSTAL,			// CryDB
		MOLCRYSTAL,			// McrDB
		POTLIB,				// PotLib
		ANALYSIS,			// Analysis
		// Appended by izaty on Apr.22,'05
		// start
		TEMPLATE,			// Template
		// end
		// Appended by izaty on Apr.5,'05
		// start
		MATERIALS,			// Materials
		COND,				// CondTmpl
		// end
		// Appended by izaty on Jul.8,'05
		// start
		POLYMER,			// Polymer
		// end
		USER_END,			// (End of User)
		// Count
		DIRCOUNT
	};

	enum TAILTYPE {MOL = 0, CRY, MCR, BDL, INP, POT, EXP,
		SIM, RST, ERR, LST, MAS, SPL, STS, TPOT, TRUNC, WRN, FRC, TMP,
		// Modified by izaty on Apr.20,'05
		// start
		// Modified by izaty on Aug.30,'05
		// start
		// Modified by izaty on Aug.18,'06
		// start
		IPAR, IDIF, DIF, PAR, RIN, BMP, INI, HFX, CSF, TAILCOUNT};
		//IPAR, IDIF, DIF, PAR, RIN, BMP, INI, HFX, TAILCOUNT};
		// end
		//IPAR, IDIF, DIF, PAR, RIN, BMP, INI, TAILCOUNT};
		// end
		//IPAR, IDIF, DIF, PAR, RIN, BMP, TAILCOUNT};
		// end

	// Appended by izaty on Mar.10,'05
	// start
	enum {LSCOUNT = 8};
	struct LIGHTSRC {
		int nStatus;
		int nLocal;
		float szPos[3];
		float szAmb[3];
		float szDif[3];
		float szSpc[3];
	};
	// end

	// Appended by izaty on Mar.23,'05
	// start
	enum {GBCOUNT = 100};
	// end
protected:
	enum LIGHTTYPE {LPOSITION = 0, LAMBIENT, LDIFFUSE, LSPECULAR,
		LMSPECULAR, LSHININESS, LIGHTCOUNT};

	// File Path
	static CString m_filePrvName;
	static CString m_filePrvPath;
	static CString m_fileSysName;
	static CString m_fileSysPath;
	static CString m_fileDefName;
	static CString m_fileDefPath;
	// File Status
	static CFileStatus m_filePrvStatus;
	// Parameters
	static CString paraSlices;
	static CString paraRadScale;
	static CString paraDir[DIRCOUNT];
	static CString paraAtomHead;
	static CString paraDatomHead;
	static CString paraBondHead;
	static CString paraLightHead;
	static CString paraLight[LIGHTCOUNT];
	static CString paraPassword;
	// Appended by izaty on Mar.23,'05
	// start
	// Ini File Values
	static CString iniDir[DIRCOUNT];
	// end
	// Default Values
	static CString defDir[DIRCOUNT];
	// Values
	static int slices;
	static CString dir[DIRCOUNT];
	static float light[LIGHTCOUNT][3];
	static CString password;
	// Tail
	static CString tail[TAILCOUNT];

	// Appended by izaty on Mar.10,'05
	// start
	enum LIGHTSRCTYPE {LSSTATUS = 0, LSLOCAL, LSPOSITION, 
		LSAMBIENT, LSDIFFUSE, LSSPECULAR, LSTYPECOUNT};

	static CString paraLightSrcHead;
	static CString paraLightSrc[LSTYPECOUNT];

	static struct LIGHTSRC lightSrc[LSCOUNT];
	// end

	// Appended by izaty on Mar.23,'05
	// start
	static int garbageCount;
	static CString garbage[GBCOUNT];
	// end

public:
	static BOOL PASCAL Read();
	static BOOL PASCAL ReadSystem();
	static BOOL PASCAL ReadPrivate();
	// Appended by izaty on Jun.23,'05
	// start
	static BOOL PASCAL ReadDefaults();
	static BOOL PASCAL ReadPrivate(CString strPrvDir, CString strPrvPath,
		CString& filePrvPath, CFileStatus& filePrvStatus);
	// end
	// Appended by izaty on Mar.23,'05
	// start
	static BOOL PASCAL WritePrivate();
	// end
	static BOOL PASCAL IsModified();

	// Appended by izaty on Mar.23,'05
	// start
	static CString PASCAL GetInisDir(DIRTYPE i);
	// end
	static CString PASCAL GetDefaultDirName(DIRTYPE i);
	static CString PASCAL GetDir(DIRTYPE i);
	static int PASCAL GetSphereSlices();
	// Deleted by izaty on Mar.23,'05
	// start
	/*
	static void PASCAL GetLightPosition(float& x, float& y, float& z);
	static void PASCAL GetLightAmbient(float& r, float& g, float& b);
	static void PASCAL GetLightDiffuse(float& r, float& g, float& b);
	static void PASCAL GetLightSpecular(float& r, float& g, float& b);
	static void PASCAL GetLightMSpecular(float& r, float& g, float& b);
	static void PASCAL GetLightShininess(float& s);
	*/
	// end
	// Appended by izaty on Mar.23,'05
	// start
	static void PASCAL GetLightMSpecular(float& r, float& g, float& b);
	static void PASCAL GetLightShininess(float& s);
	static LIGHTSRC* PASCAL GetLightSrc(int nSrc);
	// end

	static CString PASCAL GetPassword();

	static CString PASCAL GetTail(TAILTYPE i);
	static CString PASCAL GetExt(TAILTYPE i);
	static CString PASCAL GetFinder(DIRTYPE i, TAILTYPE j);
	static CString PASCAL GetFinder(CString strDir, TAILTYPE j);

	// Appended by izaty on Mar.23,'05
	// start
	static void PASCAL SetDir(DIRTYPE i, LPCTSTR lpszDir);
	static void PASCAL SetSphereSlices(int s);
	static void PASCAL SetLightMSpecular(float r, float g, float b);
	static void PASCAL SetLightShininess(float s);
	static void PASCAL SetLightSrc(int nSrc, LIGHTSRC *pSrc);
	// end

	static void PASCAL SetPassword(LPCTSTR lpszPswd);

protected:
	static void PASCAL GetLight(LIGHTTYPE i, float& r, float& g, float& b);
};

#endif // !defined(AFX_MASENV_H__131E2381_57D1_11D3_AAC6_00A0C924BC0A__INCLUDED_)
