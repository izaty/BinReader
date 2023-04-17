#pragma once

#include <iostream>
#include <strstream>

using namespace std;

#pragma warning( disable : 4290 ) 

#include "MasException.h"

class FsException : public MasException {
public:
	FsException(int nCause) {m_cause = nCause;}
	// エラーの種類
	enum {
		none,
		openError,
		readError,
		writeError,
		typeError
	};
	int m_cause;
};

class FileStream  
{
protected:
	// ストリームの種類
	enum {FPOINTER, IOSTREAM, FILEPATH};

	int m_nType;		// ストリームの種類
	int m_nLineLen;		// バッファの長さ
	char *m_pszLineBuf;	// バッファ

	// ストリームの共用体
	union {
		FILE *fp;				// FILE
		iostream *is;			// iostream
	} m_file;
	istrstream *m_piStream;

public:
	// コンストラクタ＆デストラクタ
	FileStream(LPCTSTR lpszFilePath, LPCTSTR lpszMode, int nLineLen = 512);
	FileStream(FILE *fp, int nLineLen = 512);
	FileStream(iostream *is, int nLineLen = 512);
	virtual ~FileStream();

	// １行の読み込み
	char *ReadLine() throw(FsException);
	// １行の書き込み
	void WriteLine(const char *format,...) throw(FsException);
//	void WriteLine(LPCTSTR format,...) throw(FsException);
	// 書き込み
	void Write(const char *format,...) throw(FsException);
//	void Write(LPCTSTR format,...) throw(FsException);
	// バッファの長さの設定
	void SetBufferLength(int nLineLen);
	// バッファの長さの取得
	int GetBufferLength() const {return m_nLineLen;}

	// 最初へシーク
	void SeekToBegin();

	FileStream& operator>>(char *psz)			throw(FsException);
	FileStream& operator>>(char& rch)			throw(FsException);
	FileStream& operator>>(short& s)			throw(FsException);
	FileStream& operator>>(unsigned short& us)	throw(FsException);
	FileStream& operator>>(int& n)				throw(FsException);
	FileStream& operator>>(unsigned int& un)	throw(FsException);
	FileStream& operator>>(long& l)				throw(FsException);
	FileStream& operator>>(unsigned long& ul)	throw(FsException);
	FileStream& operator>>(float& f)			throw(FsException);
	FileStream& operator>>(double& d)			throw(FsException);

//	FileStream& operator>>(TCHAR *psz)			throw(FsException);
//	FileStream& operator>>(TCHAR& rch)			throw(FsException);
};
