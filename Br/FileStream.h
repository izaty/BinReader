#pragma once

#include <iostream>
#include <strstream>

using namespace std;

#pragma warning( disable : 4290 ) 

#include "MasException.h"

class FsException : public MasException {
public:
	FsException(int nCause) {m_cause = nCause;}
	// �G���[�̎��
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
	// �X�g���[���̎��
	enum {FPOINTER, IOSTREAM, FILEPATH};

	int m_nType;		// �X�g���[���̎��
	int m_nLineLen;		// �o�b�t�@�̒���
	char *m_pszLineBuf;	// �o�b�t�@

	// �X�g���[���̋��p��
	union {
		FILE *fp;				// FILE
		iostream *is;			// iostream
	} m_file;
	istrstream *m_piStream;

public:
	// �R���X�g���N�^���f�X�g���N�^
	FileStream(LPCTSTR lpszFilePath, LPCTSTR lpszMode, int nLineLen = 512);
	FileStream(FILE *fp, int nLineLen = 512);
	FileStream(iostream *is, int nLineLen = 512);
	virtual ~FileStream();

	// �P�s�̓ǂݍ���
	char *ReadLine() throw(FsException);
	// �P�s�̏�������
	void WriteLine(const char *format,...) throw(FsException);
//	void WriteLine(LPCTSTR format,...) throw(FsException);
	// ��������
	void Write(const char *format,...) throw(FsException);
//	void Write(LPCTSTR format,...) throw(FsException);
	// �o�b�t�@�̒����̐ݒ�
	void SetBufferLength(int nLineLen);
	// �o�b�t�@�̒����̎擾
	int GetBufferLength() const {return m_nLineLen;}

	// �ŏ��փV�[�N
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
