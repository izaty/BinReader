// MasEnv.cpp: MasEnv クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdtbl.h"
#include "MasEnv.h"
#include "RegManager.h"
#include "DirBrowser.h"
#include "DirManager.h"
#include <fstream>
#include <strstream>

using namespace std;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define MASENV_LINELEN 512
// File Name
CString MasEnv::m_filePrvName = _T("Matx.ini");
CString MasEnv::m_fileSysName = _T("SysMatx.ini");
CString MasEnv::m_fileDefName = _T("DefMatx.ini");
CString MasEnv::m_filePrvPath;
CString MasEnv::m_fileSysPath;
CString MasEnv::m_fileDefPath;

// File Status
CFileStatus MasEnv::m_filePrvStatus;

// Parameters
CString MasEnv::paraDir[DIRCOUNT] = {
	_T(""),
	_T("data-dir"),
	_T("molecular-dir"), 
	_T("crystal-dir"), 
	_T("molcrystal-dir"), 
	_T("potential_lib_sys-dir"), 
	_T("analysis-dir"), 
	_T("template-dir"), 
	_T("bitmap-dir"), 
	// Appended by izaty on Apr.8,'05
	// start
	_T(""), 
	_T(""), 
	// end
	// Appended by izaty on Jul.8,'05
	// start
	_T(""), 
	// end
	_T(""),
	_T("data-dir"),
	_T("molecular-dir"), 
	_T("crystal-dir"), 
	_T("molcrystal-dir"), 
	_T("potential_lib_sys-dir"), 
	_T("analysis-dir"), 
	// Appended by izaty on Apr.22,'05
	// start
	_T(""), 
	// end
	// Appended by izaty on Apr.8,'05
	// start
	_T(""), 
	_T(""), 
	// end
	// Appended by izaty on Jul.8,'05
	// start
	_T(""), 
	// end
	_T("")
};
CString MasEnv::paraSlices    = _T("SPHERE_SLICES");
CString MasEnv::paraRadScale  = _T("RADIUS_SCALE");
CString MasEnv::paraAtomHead  = _T("ATOM_");
CString MasEnv::paraDatomHead = _T("DATOM_");
CString MasEnv::paraBondHead  = _T("BOND_");
CString MasEnv::paraLightHead = _T("LIGHT_");
CString MasEnv::paraLight[LIGHTCOUNT] = {
	_T("POSITION"),
	_T("AMBIENT"),
	_T("DIFFUSE"),
	_T("SPECULAR"),
	_T("MSPECULAR"),
	_T("SHININESS")
};
CString MasEnv::paraPassword  = _T("PASSWORD");

// Parameters
// Appended by izaty on Mar.23,'05
// start
CString MasEnv::iniDir[DIRCOUNT];
// end
CString MasEnv::defDir[DIRCOUNT] = {
	_T(""),
	_T("Data"),
	_T("MolDB"), 
	_T("CryDB"), 
	_T("McrDB"), 
	_T("PotLib"), 
	_T("Analysis"), 
	_T("Template"), 
	_T("Bitmaps"), 
	// Appended by izaty on Apr.5,'05
	// start
	_T("Materials"), 
	_T("CondTmpl"), 
	// end
	// Appended by izaty on Jul.8,'05
	// start
	_T("Polymer"), 
	// end
	_T(""),
	_T("Data"),
	_T("MolDB"), 
	_T("CryDB"), 
	_T("McrDB"), 
	_T("PotLib"), 
	_T("Analysis"), 
	// Appended by izaty on Apr.22,'05
	// start
	_T("Template"),
	// end
	// Appended by izaty on Apr.5,'05
	// start
	_T("Materials"), 
	_T("CondTmpl"), 
	// end
	// Appended by izaty on Jul.8,'05
	// start
	_T("Polymer"), 
	// end
	_T("")
};

// Values
int MasEnv::slices = 16;
CString MasEnv::dir[DIRCOUNT];
float MasEnv::light[LIGHTCOUNT][3] = {
	{0.8f, 0.8f, 0.8f},
	{0.2f, 0.2f, 0.2f},
	{1.0f, 1.0f, 1.0f},
	{1.0f, 1.0f, 1.0f}, 
	{0.0f, 0.0f, 0.0f},
	{0.0f, 0.0f, 0.0f}
};
CString MasEnv::password;

// Tail
CString MasEnv::tail[TAILCOUNT] = {
	_T(".mol"),
	_T(".cry"), 
	_T(".mcr"),
	_T(".bdl"),
	_T(".inp"),
	_T(".pot"),
	_T(".exp"),
	_T(".sim"),
	_T(".rst"),
	_T(".err"),
	_T(".lst"),
	_T(".mas"),
	_T(".spl"),
	_T(".sts"),
	_T(".tpot"),
	_T(".trunc"),
	_T(".wrn"),
	_T(".frc"),
	_T(".tmp"),
	_T(".ipar"),
	_T(".idif"),
	_T(".dif"),
	_T(".par"),
	_T(".rin"),
	_T(".bmp"),
	// Appended by izaty on Apr.20,'05
	// start
	_T(".ini"),
	// end
	// Appended by izaty on Aug.30,'05
	// start
	_T(".hfx"),
	// end
	// Appended by izaty on Aug.18,'06
	// start
	_T(".csf"),
	// end
};

// Appended by izaty on Mar.10,'05
// start
CString MasEnv::paraLightSrcHead = _T("LIGHTSRC_");
CString MasEnv::paraLightSrc[LSTYPECOUNT] = {
	_T("_STATUS"),
	_T("_LOCAL"),
	_T("_POSITION"),
	_T("_AMBIENT"),
	_T("_DIFFUSE"),
	_T("_SPECULAR")
};
MasEnv::LIGHTSRC MasEnv::lightSrc[LSCOUNT] = {
	{1, 0, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}},
	// Modified by izaty on Nov.25,'05
	// start
	{0, 1, {50.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}},
	{0, 1, {-50.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}},
	//{1, 1, {50.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}},
	//{1, 1, {-50.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}},
	// end
	{0, 1, {0.0f, 0.0f, 50.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.2f, 0.2f, 0.2f}},
	{0, 1, {0.0f, 50.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}},
	{0, 1, {0.0f, -50.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}},
	{0, 1, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}},
	{0, 1, {0.0f, 50.0f, -50.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f}}
};
// end

// Appended by izaty on Mar.23,'05
// start
CString MasEnv::garbage[GBCOUNT];
int MasEnv::garbageCount = 0;
// end

// Registry Values
AFX_STATIC_DATA const TCHAR _afxCommon[] = _T("Common Environment");
// Modified by izaty on Aug.5,'05
// start
//AFX_STATIC_DATA const TCHAR _afxLocation[] = _T("Location");
AFX_STATIC_DATA const TCHAR _afxLocation[]  = _T("Location4");
AFX_STATIC_DATA const TCHAR _afxLocation3[] = _T("Location");
// end
// Appended by izaty on Aug.22,'06
// start
AFX_STATIC_DATA const TCHAR _afxCACheLocation[]  = _T("CACheLocation");
// end

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

MasEnv::MasEnv()
{

}

MasEnv::~MasEnv()
{

}

// Appended by izaty on Mar.15,'05
// start
CString PASCAL MasEnv::GetSystemIniName() {return m_fileSysName;}
CString PASCAL MasEnv::GetPrivateIniName() {return m_filePrvName;}
// end

CString PASCAL MasEnv::GetDefaultPrivateDir()
{
	// Modified by izaty on Oct.8,'03
	// start
	/*
	TCHAR szPath[_MAX_PATH];
	if (SHGetSpecialFolderPath(NULL, szPath, CSIDL_APPDATA, FALSE)) {
	}
	else if (SHGetSpecialFolderPath(NULL, szPath, CSIDL_DESKTOP, FALSE)) {
	}
	else {
		return _T("C:\\Temp");
	}
	CString strDir;
	CRegManager rm;
	strDir.Format("%s\\%s\\%s", szPath, 
		rm.GetCompanyName(), rm.GetProductName());
	return strDir;
	*/
	// Modified by izaty on Aug.5,'05
	// start
	//CString strDir;
	//CRegManager rm;
	//strDir.Format("%s%s", _T("C:\\"), rm.GetProductName());
	//return strDir;
	// Modified by izaty on Oct.17,'07
	// start
	//return _T("C:\\MatX4.0");
	return _T("C:\\MatX5.0");
	// end
	// end
	// end
}

void PASCAL MasEnv::GetPrivateEnv(CString& strDir, 
								  DIRSTATUS& rStatus)
{
	CRegManager rm;
	strDir = rm.GetProfileString(_afxCommon, _afxLocation, "");
	if (strDir.GetLength() > 0) {
		CFileStatus rFileStatus;
		if (CFile::GetStatus(strDir, rFileStatus)) {
			if (rFileStatus.m_attribute & CFile::directory) {
				rStatus = EXIST;
			}
			else {
				rStatus = NOT_DIRECTORY;
			}
		}
		else {
			rStatus = NOT_EXIST;
		}
	}
	else {
		rStatus = NOT_REGISTERED;
		// Appended by izaty on Aug.5,'05
		// start
		strDir = rm.GetProfileString(_afxCommon, _afxLocation3, "");
		if (strDir.GetLength() > 0) {
			rStatus = EXIST_OLD;
		}
		// end
	}
}

void PASCAL MasEnv::RegPrivateEnv(CString strDir)
{
	CRegManager rm;
	rm.WriteProfileString(_afxCommon, _afxLocation, strDir);
}

// Modified by izaty on Apr.19,'04
// start
//
// The voronoi.* files will always get overwritten.
// Other than that, if the file/folder exists, it will be kept as it is.
// If not exist, it will be created.
//
//void PASCAL MasEnv::SetPrivateEnv(CString strDir)
void PASCAL MasEnv::SetPrivateEnv(CString strDir, BOOL bCreateShortCut)
// end
{
	// Register
	RegPrivateEnv(strDir);
	// Create an environment
	DirManager::WriteDir(strDir);
	strDir += _T("\\");
	// Get Private ini file
	CString strPrvPath = strDir + m_filePrvName;
	// Get Default ini file
	CString strSysDir;
	GetSystemEnv(strSysDir);
	strSysDir += _T("\\");
	CString strDefPath = strSysDir + m_fileDefName;
	// Copy Private ini file
	// Modified by izaty on Aug.5,'05
	// start
	//::CopyFile(strDefPath, strPrvPath, FALSE);
	// Modified by izaty on Jun.16,'06
	// start
	//::CopyFile(strDefPath, strPrvPath, TRUE);
	if (::CopyFile(strDefPath, strPrvPath, TRUE) == 0) {
		if (::GetLastError() != ERROR_FILE_EXISTS) {
			LPVOID lpMsgBuf;
			::FormatMessage(			// エラー表示文字列作成
				FORMAT_MESSAGE_ALLOCATE_BUFFER | 
				FORMAT_MESSAGE_FROM_SYSTEM | 
				FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL, GetLastError(),
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
				(LPTSTR)&lpMsgBuf, 0, NULL);
			AfxMessageBox((LPCTSTR)lpMsgBuf);
			LocalFree(lpMsgBuf);
		}
	}
	// end
	// end
	// Create sub directories
	DirManager::WriteDir(strDir + defDir[DATA]);
	DirManager::WriteDir(strDir + defDir[MOLECULAR]);
	DirManager::WriteDir(strDir + defDir[MOLCRYSTAL]);
	DirManager::WriteDir(strDir + defDir[POTLIB]);
	DirManager::WriteDir(strDir + defDir[ANALYSIS]);
	// Appended by izaty on Sep.30,'05
	// start
	DirManager::WriteDir(strDir + defDir[TEMPLATE]);
	// end
	// Appended by izaty on Apr.5,'05
	// start
	DirManager::WriteDir(strDir + defDir[MATERIALS]);
	DirManager::WriteDir(strDir + defDir[COND]);
	// end
	// Appended by izaty on Aug.5,'05
	// start
	CString strPolyDir = strDir + defDir[POLYMER];
	DirManager::WriteDir(strPolyDir);
	DirManager::WriteDir(strPolyDir + _T("\\connectionlist"));
	DirManager::WriteDir(strPolyDir + _T("\\monomer\\head"));
	DirManager::WriteDir(strPolyDir + _T("\\monomer\\middle"));
	DirManager::WriteDir(strPolyDir + _T("\\monomer\\tail"));
	DirManager::WriteDir(strPolyDir + _T("\\polymer"));
	DirManager::WriteDir(strPolyDir + _T("\\monolib"));
	DirManager::WriteDir(strPolyDir + _T("\\pbset"));
	DirManager::WriteDir(strPolyDir + _T("\\rbset"));
	DirManager::WriteDir(strPolyDir + _T("\\rblist"));
	DirManager::WriteDir(strPolyDir + _T("\\md_data"));
	DirManager::WriteDir(strPolyDir + _T("\\tmp"));
	// end
	// Appended by izaty on Oct.28,'03
	// start
	CString strVoroXsl("\\voronoi.xsl");
	CString strVoroDtd("\\voronoi.dtd");
	CString strSysVoroXsl = strSysDir + defDir[ANALYSIS] + strVoroXsl;
	CString strSysVoroDtd = strSysDir + defDir[ANALYSIS] + strVoroDtd;
	CString strPrvVoroXsl = strDir + defDir[ANALYSIS] + strVoroXsl;
	CString strPrvVoroDtd = strDir + defDir[ANALYSIS] + strVoroDtd;
	::CopyFile(strSysVoroXsl, strPrvVoroXsl, FALSE);	// Always overwritten
	::CopyFile(strSysVoroDtd, strPrvVoroDtd, FALSE);	// Always overwritten
	// end
	// Create shortcuts of common data
	// Appended by izaty on Apr.19,'04
	// start
	if (bCreateShortCut) {
	// end
	// Appended by izaty on Apr.18,'03
	// start
	CString strShortcut("\\Common Data.lnk");
	DirManager::CreateLinkFile(
		strDir + defDir[DATA]       + strShortcut, "", dir[SYS_DATA]);
	DirManager::CreateLinkFile(
		strDir + defDir[MOLECULAR]  + strShortcut, "", dir[SYS_MOLECULAR]);
	DirManager::CreateLinkFile(
		strDir + defDir[MOLCRYSTAL] + strShortcut, "", dir[SYS_MOLCRYSTAL]);
	DirManager::CreateLinkFile(
		strDir + defDir[POTLIB]     + strShortcut, "", dir[SYS_POTLIB]);
	DirManager::CreateLinkFile(
		strDir + defDir[ANALYSIS]   + strShortcut, "", dir[SYS_ANALYSIS]);
	// end
	// Appended by izaty on Apr.19,'04
	// start
	}
	// end
}

void PASCAL MasEnv::GetSystemEnv(CString& strDir)
{
	char szModFilePath[_MAX_PATH+1];
	GetModuleFileName(AfxGetInstanceHandle(), szModFilePath, _MAX_PATH);
	CString strModFilePath = _T(szModFilePath);
	int nModDirLen = strModFilePath.GetLength()
		- strlen("\\")
		- strlen(AfxGetApp()->m_pszExeName)
		- strlen(".exe");
	strDir = strModFilePath.Left(nModDirLen);
}

void PASCAL MasEnv::GetPrivateEnv(CString& strPrvDir,
								  CString& strPrvPath)
{
	DIRSTATUS rStatus;
	GetPrivateEnv(strPrvDir, rStatus);
	// Modified by izaty on Aug.5,'05
	// start
	//f (rStatus == NOT_REGISTERED) {
	if (rStatus == NOT_REGISTERED || rStatus == EXIST_OLD) {
	// end
		strPrvDir = _T("");
		strPrvPath = _T("");
	}
	else {
		strPrvDir += _T("\\");
		strPrvPath = strPrvDir + m_filePrvName;
	}
}

void PASCAL MasEnv::GetSystemEnv(CString& strSysDir,
								 CString& strSysPath,
								 CString& strDefPath)
{
	GetSystemEnv(strSysDir);
	strSysDir += _T("\\");
	strSysPath = strSysDir + m_fileSysName;
	strDefPath = strSysDir + m_fileDefName;
}

BOOL PASCAL MasEnv::IsModified()
{
	CFileStatus rStatus;
	if (!CFile::GetStatus(m_filePrvPath, rStatus))
		return FALSE;
	// Modified by izaty on Jul.2,'07
	// start
	// %D が VS2005 より受け付けられない仕様になったため。
	CString strR = rStatus.m_mtime.Format("%m %d %y %H %M %S");
	CString strP = m_filePrvStatus.m_mtime.Format("%m %d %y %H %M %S");
	//CString strR = rStatus.m_mtime.Format("%D %H %M %S");
	//CString strP = m_filePrvStatus.m_mtime.Format("%D %H %M %S");
	// end
	return (rStatus.m_mtime != m_filePrvStatus.m_mtime);
}

BOOL PASCAL MasEnv::ReadSystem()
{
	CString strSysDir, strSysPath;
	GetSystemEnv(strSysDir, strSysPath, m_fileDefPath);
	// load_module-dir
	dir[MODULE] = strSysDir.Left(strSysDir.GetLength() - 1);
	// default dir
	volatile int i;
	for (i = SYS_DATA; i < SYS_END; i++) {
		dir[i] = strSysDir + defDir[i];
		// Appended by izaty on Mar.23,'05
		// start
		iniDir[i] = dir[i];
		// end
	}

	// Open SysMatx.ini
	// Appended by izaty on Feb.20,'08
	// start
	_tsetlocale(LC_ALL,_T(""));
	// end
	ifstream ifs;
	ifs.open(strSysPath, ios::in);
	if (!ifs) {	// not found
		m_fileSysPath = _T("");
	}
	else {
		m_fileSysPath = strSysPath;

		// Read SysMatx.ini
		while (!ifs.eof()) {
			// Read a line
			char buf[MASENV_LINELEN];
			ifs.getline(buf, MASENV_LINELEN);
			// Set strstream
			strstream sts;
			sts << buf;
			// Get Parameter
			char pstr[MASENV_LINELEN];
			CString penv, ptmp;
			sts >> pstr;
			penv = _T(pstr);

			// Check
			// PASSWORD
			if (penv == paraPassword) {
//				sts.eatwhite();
				sts.getline(pstr, MASENV_LINELEN);
				password = _T(pstr);
				password.TrimLeft(); password.TrimRight();
			}
			// DIRECTORY
			else {
				for (i = SYS_DATA; i < SYS_END; i++) {
					// Appended by izaty on Apr.8,'05
					// start
					if (!paraDir[i].GetLength())
						continue;
					// end
					if (penv == paraDir[i]) {
//						sts.eatwhite();
						sts.getline(pstr, MASENV_LINELEN);
						// Modified by izaty on Mar.23,'05
						// start
						iniDir[i] = _T(pstr);
						iniDir[i].TrimLeft(); iniDir[i].TrimRight();
						if (iniDir[i].Mid(1, 2) != _T(":\\"))
							dir[i] = strSysDir + iniDir[i];
						else
							dir[i] = iniDir[i];
						//dir[i] = _T(pstr);
						//if (dir[i].Mid(1, 2) != _T(":\\"))
						//	dir[i] = strSysDir + dir[i];
						// end
						break;
					}
				}
			}
		}
		ifs.close();
	}

	BOOL bReturnCode = TRUE;
	if (!m_fileSysPath.GetLength()) {
		AfxMessageBox("SysMatx.ini not found.\n\
Some functions may not work correctly.");
		bReturnCode = FALSE;
	}
	return bReturnCode;
}

BOOL PASCAL MasEnv::ReadPrivate()
{
	CString strPrvDir, strPrvPath;
	GetPrivateEnv(strPrvDir, strPrvPath);
// Appended by izaty on Jun.23,'05
// start
	return ReadPrivate(strPrvDir, strPrvPath, m_filePrvPath, m_filePrvStatus);
}

BOOL PASCAL MasEnv::ReadDefaults()
{
	CString strSysDir, strSysPath, strDefPath;
	GetSystemEnv(strSysDir, strSysPath, strDefPath);
	CString strDummy;
	CFileStatus stsDummy;
	return ReadPrivate(strSysDir, strDefPath, strDummy, stsDummy);
}

BOOL PASCAL MasEnv::ReadPrivate(CString strPrvDir, CString strPrvPath,
								CString& filePrvPath,
								CFileStatus& filePrvStatus)
{
// end
	// default dir
	volatile int i;
	for (i = DATA; i < USER_END; i++) {
		dir[i] = strPrvDir + defDir[i];
		// Appended by izaty on Mar.23,'05
		// start
		iniDir[i] = dir[i];
		// end
	}
	// Open Matx.ini
	// Appended by izaty on Feb.20,'08
	// start
	_tsetlocale(LC_ALL,_T(""));
	// end
	ifstream ifs;
	ifs.open(strPrvPath, ios::in);
	// Modified by izaty on Jun.23,'05
	// start
	//if (!ifs) {	// not found
	//	m_filePrvPath = _T("");
	//}
	//else {
	//	m_filePrvPath = strPrvPath;
	//
	//	// Get Status of Matx.ini
	//	CFile::GetStatus(strPrvPath, m_filePrvStatus);
	if (!ifs) {
	}
	else {
		filePrvPath = strPrvPath;

		// Get Status of Matx.ini
		CFile::GetStatus(strPrvPath, filePrvStatus);
	// end

		// Appended by izaty on Mar.23,'05
		// start
		BOOL bLightSrcFlag = FALSE;
		garbageCount = 0;
		// end

		// Read Matx.ini
		while (!ifs.eof()) {
			// Read a line
			char buf[MASENV_LINELEN];
			ifs.getline(buf, MASENV_LINELEN);
			// Set strstream
			strstream sts;
			sts << buf;
			// Get Parameter
			char pstr[MASENV_LINELEN];
			CString penv, ptmp;
			sts >> pstr;
			penv = _T(pstr);

			// Check
			// ATOM
			if (penv.Find(paraAtomHead) == 0) {
				int col[3];
				double rad, mas;
				sts >> col[0] >> col[1] >> col[2] >> rad >> mas;
				penv = penv.Right(penv.GetLength() - paraAtomHead.GetLength());
				if (penv.GetLength() == 1)
					penv += _T(" ");
				TblAtom::SetColor(penv, Color4V(col[0], col[1], col[2]));
				TblAtom::SetRadius(penv, rad);
				TblAtom::SetMass(penv, mas);
			}
			// DATOM
			else if (penv.Find(paraDatomHead) == 0) {
				int col[3];
				double rad, mas;
				sts >> col[0] >> col[1] >> col[2] >> rad >> mas;
				penv = penv.Right(penv.GetLength() - paraDatomHead.GetLength());
				if (penv.GetLength() == 1)
					penv += _T(" ");
				TblAtom::SetColor(penv, Color4V(col[0], col[1], col[2]));
				TblAtom::SetRadius(penv, rad);
				TblAtom::SetMass(penv, mas);
			}
			// BOND
			else if (penv.Find(paraBondHead) == 0) {
				int col[3];
				double wid;
				sts >> col[0] >> col[1] >> col[2] >> wid;
				penv = penv.Right(penv.GetLength() - paraBondHead.GetLength());
				if (penv.GetLength() == 1)
					penv += _T(" ");
				TblBond::SetColor(penv, Color4V(col[0], col[1], col[2]));
				TblBond::SetWidth(penv, wid);
			}
			// LIGHT
			else if (penv.Find(paraLightHead) == 0) {
				for (i = 0; i < LIGHTCOUNT; i++) {
					ptmp = paraLightHead;
					ptmp += paraLight[i];
					if (penv == ptmp) {
						if (i == LSHININESS)
							sts >> light[i][0];
						else
							sts >> light[i][0] >> light[i][1] >> light[i][2];
						break;
					}
				}
			}
			// SLICES
			else if (penv == paraSlices)
				sts >> slices;
			// RADIUS SCALE
			else if (penv == paraRadScale) {
				double rScale;
				sts >> rScale;
				TblAtom::SetRadiusScale(rScale);
			}
			// Appended by izaty on Mar.10,'05
			// start
			else if (penv.Find(paraLightSrcHead) == 0) {
				for (i = 0; i < LSCOUNT; i++) {
					CString pptmp;
					pptmp.Format("%s%d", paraLightSrcHead, i);
					for (volatile int j = 0; j < LSTYPECOUNT; j++) {
						ptmp = pptmp;
						ptmp += paraLightSrc[j];
						if (penv == ptmp) {
							// Appended by izaty on Mar.23,'05
							// start
							bLightSrcFlag = TRUE;
							// end
							if (j == LSSTATUS)
								sts >> lightSrc[i].nStatus;
							else if (j == LSLOCAL)
								sts >> lightSrc[i].nLocal;
							else if (j == LSPOSITION)
								sts >> lightSrc[i].szPos[0] >> lightSrc[i].szPos[1] >> lightSrc[i].szPos[2];
							else if (j == LSAMBIENT)
								sts >> lightSrc[i].szAmb[0] >> lightSrc[i].szAmb[1] >> lightSrc[i].szAmb[2];
							else if (j == LSDIFFUSE)
								sts >> lightSrc[i].szDif[0] >> lightSrc[i].szDif[1] >> lightSrc[i].szDif[2];
							else if (j == LSSPECULAR)
								sts >> lightSrc[i].szSpc[0] >> lightSrc[i].szSpc[1] >> lightSrc[i].szSpc[2];
							break;
						}
					}
				}
			}
			// end
			// DIRECTORY
			else {
				for (i = DATA; i < USER_END; i++) {
					// Appended by izaty on Apr.8,'05
					// start
					if (!paraDir[i].GetLength())
						continue;
					// end
					if (penv == paraDir[i]) {
//						sts.eatwhite();
						sts.getline(pstr, MASENV_LINELEN);
						// Modified by izaty on Mar.23,'05
						// start
						iniDir[i] = _T(pstr);
						iniDir[i].TrimLeft(); iniDir[i].TrimRight();
						if (iniDir[i].Mid(1, 2) != _T(":\\"))
							dir[i] = strPrvDir + iniDir[i];
						else
							dir[i] = iniDir[i];
						//dir[i] = _T(pstr);
						//if (dir[i].Mid(1, 2) != _T(":\\"))
						//	dir[i] = strPrvDir + dir[i];
						// end
						break;
					}
				}
				// Appended by izaty on Mar.23,'05
				// start
				if (i == USER_END) {
					if (garbageCount < GBCOUNT) {
						garbage[garbageCount] = _T(buf);
						garbageCount++;
					}
				}
				// end
			}
		}
		ifs.close();

		// Appended by izaty on Mar.23,'05
		// start
		// LIGHTSRC parameters not found
		if (!bLightSrcFlag) {
			lightSrc[0].nStatus = 1;
			lightSrc[0].nLocal = 0;
			lightSrc[0].szPos[0] = light[LPOSITION][0];
			lightSrc[0].szPos[1] = light[LPOSITION][1];
			lightSrc[0].szPos[2] = light[LPOSITION][2];
			lightSrc[0].szAmb[0] = light[LAMBIENT][0];
			lightSrc[0].szAmb[1] = light[LAMBIENT][1];
			lightSrc[0].szAmb[2] = light[LAMBIENT][2];
			lightSrc[0].szDif[0] = light[LDIFFUSE][0];
			lightSrc[0].szDif[1] = light[LDIFFUSE][1];
			lightSrc[0].szDif[2] = light[LDIFFUSE][2];
			lightSrc[0].szSpc[0] = light[LSPECULAR][0];
			lightSrc[0].szSpc[1] = light[LSPECULAR][1];
			lightSrc[0].szSpc[2] = light[LSPECULAR][2];
		}
		// end
	}

	BOOL bReturnCode = TRUE;
	// Modified by izaty on Jun.23,'05
	// start
	if (!filePrvPath.GetLength()) {
		CString strText;
		strText.Format("%s Matx.ini not found.\n\
Some functions may not work correctly.", filePrvPath);
		AfxMessageBox(strText);
		bReturnCode = FALSE;
	}
//	if (!m_filePrvPath.GetLength()) {
//		AfxMessageBox("Matx.ini not found.\n\
//Some functions may not work correctly.");
//		bReturnCode = FALSE;
//	}
	// end
	return bReturnCode;
}

// Appended by izaty on Mar.23,'05
// start
#include "FileStream.h"

BOOL PASCAL MasEnv::WritePrivate()
{
	CString strPrvDir, strPrvPath;
	GetPrivateEnv(strPrvDir, strPrvPath);

	FILE *fp = fopen(strPrvPath, "w");
	if (fp == NULL) {
		return FALSE;
	}

	try {
		volatile int i;
		FileStream fs(fp);

		// (garbages)
		for (i = 0; i < garbageCount; i++) {
			fs.WriteLine(garbage[i]);
		}

		// (directory)
		for (i = DATA; i < USER_END; i++) {
			// Modified by izaty on Apr.8,'05
			// start
			if (paraDir[i].GetLength()) {
				fs.WriteLine("%-24s %s", paraDir[i], iniDir[i]);
			}
			//fs.WriteLine("%-24s %s", paraDir[i], iniDir[i]);
			// end
		}

		// LIGHT_
		{
			CString str;
			// MSPECULAR
			str = paraLightHead + paraLight[LMSPECULAR];
			fs.WriteLine("%-16s %8.4f %8.4f %8.4f", str,
				light[LMSPECULAR][0], light[LMSPECULAR][1], 
				light[LMSPECULAR][2]);
			// SHININESS
			str = paraLightHead + paraLight[LSHININESS];
			fs.WriteLine("%-16s %8.4f", str, light[LSHININESS][0]);
		}

		// LIGHTSRC_
		for (i = 0; i < LSCOUNT; i++) {
			CString strHead;
			strHead.Format("%s%d", paraLightSrcHead, i);
			CString str;
			// _STATUS
			str = strHead + paraLightSrc[LSSTATUS];
			fs.WriteLine("%-21s %d", str, lightSrc[i].nStatus);
			// _LOCAL
			str = strHead + paraLightSrc[LSLOCAL];
			fs.WriteLine("%-21s %d", str, lightSrc[i].nLocal);
			// _POSITION
			str = strHead + paraLightSrc[LSPOSITION];
			fs.WriteLine("%-21s %8.4f %8.4f %8.4f", str,
				lightSrc[i].szPos[0], lightSrc[i].szPos[1], 
				lightSrc[i].szPos[2]);
			// _AMBIENT
			str = strHead + paraLightSrc[LSAMBIENT];
			fs.WriteLine("%-21s %8.4f %8.4f %8.4f", str,
				lightSrc[i].szAmb[0], lightSrc[i].szAmb[1], 
				lightSrc[i].szAmb[2]);
			// _DIFFUSE
			str = strHead + paraLightSrc[LSDIFFUSE];
			fs.WriteLine("%-21s %8.4f %8.4f %8.4f", str,
				lightSrc[i].szDif[0], lightSrc[i].szDif[1], 
				lightSrc[i].szDif[2]);
			// _SPECULAR
			str = strHead + paraLightSrc[LSSPECULAR];
			fs.WriteLine("%-21s %8.4f %8.4f %8.4f", str,
				lightSrc[i].szSpc[0], lightSrc[i].szSpc[1], 
				lightSrc[i].szSpc[2]);
		}

		// BOND_
		for (i = 0; i < TblBond::MAX_BOND; i++) {
			CString str = MasEnv::paraBondHead + TblBond::GetName(i);
			Color4V col = TblBond::GetColor(i);
			int cr, cg, cb, ca;
			col.GetRgba(cr, cg, cb, ca);
			double wid = TblBond::GetWidth(i);
			fs.WriteLine("%-16s %8d %8d %8d %8.4f", str, cr, cg, cb, wid);
		}

		// ATOM_
		for (i = 0; i < TblAtom::MAX_PERIO_ATOM; i++) {
			if (TblAtom::IsNameWildcard(i)) {
				continue;
			}
			CString str = MasEnv::paraAtomHead + TblAtom::GetName(i);
			Color4V col = TblAtom::GetColor(i);
			int cr, cg, cb, ca;
			col.GetRgba(cr, cg, cb, ca);
			double rad = TblAtom::GetRadius(i);
			double mas = TblAtom::GetMass(i);
			fs.WriteLine("%-16s %8d %8d %8d %8.4f %8.4f", 
				str, cr, cg, cb, rad, mas);
		}

		// DATOM_
		for ( ; i < TblAtom::MAX_ATOM; i++) {
			if (TblAtom::IsNameWildcard(i)) {
				continue;
			}
			CString str = MasEnv::paraDatomHead + TblAtom::GetName(i);
			Color4V col = TblAtom::GetColor(i);
			int cr, cg, cb, ca;
			col.GetRgba(cr, cg, cb, ca);
			double rad = TblAtom::GetRadius(i);
			double mas = TblAtom::GetMass(i);
			fs.WriteLine("%-16s %8d %8d %8d %8.4f %8.4f", 
				str, cr, cg, cb, rad, mas);
		}

		// SPHERE_SLICES, RADIUS_SCALE
		{
			// SPHERE_SLICES
			fs.WriteLine("%-16s %8d", paraSlices, slices);
			// RADIUS_SCALE
			double rad = TblAtom::GetRadiusScale();
			fs.WriteLine("%-16s %8.4f", paraRadScale, rad);
		}
	}
	catch (FsException&) {
		fclose(fp);
		return FALSE;
	}

	fclose(fp);
	return TRUE;
}
// end

BOOL PASCAL MasEnv::Read()
{
	BOOL bReturnSys = ReadSystem();
	BOOL bReturnPrv = ReadPrivate();
	return (bReturnSys & bReturnPrv);
}

// Appended by izaty on Mar.24,'05
// start
CString PASCAL MasEnv::GetInisDir(DIRTYPE i)
{
	if (iniDir[i].GetLength())
		return iniDir[i];
	else
		return _T(".");
}
// end

CString PASCAL MasEnv::GetDefaultDirName(DIRTYPE i)
{
	if (defDir[i].GetLength())
		return defDir[i];
	else
		return _T(".");
}

CString PASCAL MasEnv::GetDir(DIRTYPE i)
{
	if (dir[i].GetLength())
		return dir[i];
	else
		return _T(".");
}

int PASCAL MasEnv::GetSphereSlices()
{
	return slices;
}

// Appended by izaty on Mar.23,'05
// start
void PASCAL MasEnv::SetDir(DIRTYPE i, LPCTSTR lpszDir)
{
	iniDir[i] = _T(lpszDir);
	if (iniDir[i].Mid(1, 2) != _T(":\\")) {
		CString strDir;
		if (i < SYS_END) {
			GetSystemEnv(strDir);
		}
		else {
			CString strPath;
			GetPrivateEnv(strDir, strPath);
		}
		dir[i] = strDir + iniDir[i];
	}
	else {
		dir[i] = iniDir[i];
	}
}

void PASCAL MasEnv::SetSphereSlices(int s)
{
	slices = s;
}
// end

// Deleted by izaty on Mar.23,'05
// start
/*
void PASCAL MasEnv::GetLight(LIGHTTYPE i,
							 float& r, float& g, float& b)
{
	r = light[i][0];
	g = light[i][1];
	b = light[i][2];
}
void PASCAL MasEnv::GetLightPosition(float& x, float& y, float& z)
{
	GetLight(LPOSITION, x, y, z);
}

void PASCAL MasEnv::GetLightAmbient(float& r, float& g, float& b)
{
	GetLight(LAMBIENT, r, g, b);
}

void PASCAL MasEnv::GetLightDiffuse(float& r, float& g, float& b)
{
	GetLight(LDIFFUSE, r, g, b);
}

void PASCAL MasEnv::GetLightSpecular(float& r, float& g, float& b)
{
	GetLight(LSPECULAR, r, g, b);
}

void PASCAL MasEnv::GetLightMSpecular(float& r, float& g, float& b)
{
	GetLight(LMSPECULAR, r, g, b);
}

void PASCAL MasEnv::GetLightShininess(float& s)
{
	s = light[LSHININESS][0];
}
*/
// end

CString PASCAL MasEnv::GetPassword()
{
	return password;
}

CString PASCAL MasEnv::GetTail(TAILTYPE i)
{
	if (tail[i].GetLength())
		return tail[i];
	else
		return _T(".");
}

CString PASCAL MasEnv::GetExt(TAILTYPE i)
{
	CString strTail = GetTail(i);
	return strTail.Right(strTail.GetLength() - 1);
}

CString PASCAL MasEnv::GetFinder(DIRTYPE i, TAILTYPE j)
{
	return GetFinder(GetDir(i), j);
}

CString PASCAL MasEnv::GetFinder(CString strDir, TAILTYPE j)
{
	CString wCard = strDir;
	wCard += _T("\\*");
	wCard += GetTail(j);
	return wCard;
}

void PASCAL MasEnv::SetPassword(LPCTSTR lpszPswd)
{
	password = lpszPswd;
	FILE *fp = fopen(m_fileSysPath, "a");
	if (fp != NULL) {
		fprintf(fp, "\n");
	//	fprintf(fp, "#\n");
	//	fprintf(fp, "# password\n");
	//	fprintf(fp, "#\n");
		if (password.GetLength()) {
			fprintf(fp, "%s %s\n", paraPassword, password);
		}
		fclose(fp);
	}
	// Appended by izaty on Dec.1,'04
	// start
	else {
		AfxMessageBox("Failed to save your license key or password.\
(Permission denied.)\nTry again later with administrative privileges.");
	}
	// end
}

// Appended by izaty on Mar.23,'05
// start
//
// Light Source
//
void PASCAL MasEnv::GetLightMSpecular(float& r, float& g, float& b)
{
	r = light[LMSPECULAR][0];
	g = light[LMSPECULAR][1];
	b = light[LMSPECULAR][2];
}

void PASCAL MasEnv::GetLightShininess(float& s)
{
	s = light[LSHININESS][0];
}

MasEnv::LIGHTSRC* PASCAL MasEnv::GetLightSrc(int nSrc)
{
	return &lightSrc[nSrc];
}

void PASCAL MasEnv::SetLightMSpecular(float r, float g, float b)
{
	light[LMSPECULAR][0] = r;
	light[LMSPECULAR][1] = g;
	light[LMSPECULAR][2] = b;
}

void PASCAL MasEnv::SetLightShininess(float s)
{
	light[LSHININESS][0] = s;
}

void PASCAL MasEnv::SetLightSrc(int nSrc, LIGHTSRC *pSrc)
{
	lightSrc[nSrc].nStatus = pSrc->nStatus;
	lightSrc[nSrc].nLocal = pSrc->nLocal;
	for (volatile int i = 0; i < 3; i++) {
		lightSrc[nSrc].szPos[i] = pSrc->szPos[i];
		lightSrc[nSrc].szAmb[i] = pSrc->szAmb[i];
		lightSrc[nSrc].szDif[i] = pSrc->szDif[i];
		lightSrc[nSrc].szSpc[i] = pSrc->szSpc[i];
	}
}
// end

// Appended by izaty on Aug.22,'06
// start
void PASCAL MasEnv::GetCACheEnv(CString& strDir, DIRSTATUS& rStatus)
{
	CRegManager rm;
	strDir = rm.GetProfileString(_afxCommon, _afxCACheLocation, "");
	if (strDir.GetLength() > 0) {
		CFileStatus rFileStatus;
		if (CFile::GetStatus(strDir, rFileStatus)) {
			if (rFileStatus.m_attribute & CFile::directory) {
				rStatus = EXIST;
			}
			else {
				rStatus = NOT_DIRECTORY;
			}
		}
		else {
			rStatus = NOT_EXIST;
		}
	}
	else {
		rStatus = NOT_REGISTERED;
		rm.SetReadOnly();
		rm.SetTopKey(HKEY_LOCAL_MACHINE);
		rm.SetCompanyName("Fujitsu");
		rm.SetProductName("CAChe");
		strDir = rm.GetProfileString("", "CACheUserPath", "");
		if (strDir.GetLength() > 0) {
			rStatus = EXIST;
		}
		else {
			strDir = _T("C:\\CAChe");
		}
	}
}
void PASCAL MasEnv::SetCACheEnv(CString& strDir)
{
	// Register
	CRegManager rm;
	rm.WriteProfileString(_afxCommon, _afxCACheLocation, strDir);
}
// end