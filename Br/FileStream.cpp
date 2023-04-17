// FileStream.cpp: FileStream �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FileStream.h"

//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

// �t�@�C�����p
FileStream::FileStream(LPCTSTR lpszFilePath, LPCTSTR lpszMode, int nLineLen)
{
	ASSERT(lpszFilePath && (nLineLen > 0));
	m_nType = FILEPATH;
	m_nLineLen = nLineLen;
	// Modified by izaty on Aug.12,'08
	// start
	//m_pszLineBuf = new char[m_nLineLen];
	m_pszLineBuf = new char[2*m_nLineLen+1];
	// end
	_tfopen_s(&m_file.fp, lpszFilePath, lpszMode);
	if (m_file.fp == NULL) {
		throw FsException(FsException::openError);
	}
	m_piStream = NULL;
}

// FILE �p
FileStream::FileStream(FILE *fp, int nLineLen)
{
	ASSERT(fp && (nLineLen > 0));
	m_nType = FPOINTER;
	m_nLineLen = nLineLen;
	// Modified by izaty on Aug.12,'08
	// start
	//m_pszLineBuf = new char[m_nLineLen];
	m_pszLineBuf = new char[m_nLineLen+1];
	// end
	m_file.fp = fp;
	m_piStream = NULL;
}

// iostream �p
FileStream::FileStream(iostream *is, int nLineLen)
{
	ASSERT(is && (nLineLen > 0));
	m_nType = IOSTREAM;
	m_nLineLen = nLineLen;
	// Modified by izaty on Aug.12,'08
	// start
	//m_pszLineBuf = new char[m_nLineLen];
	m_pszLineBuf = new char[m_nLineLen+1];
	// end
	m_file.is = is;
	m_piStream = NULL;
}

FileStream::~FileStream()
{
	if (m_nType == FILEPATH)
		fclose(m_file.fp);
	if (m_pszLineBuf)
		delete [] m_pszLineBuf;
	if (m_piStream)
		delete m_piStream;
}

// �P�s�ǂݍ���
char *FileStream::ReadLine()
{
	// �P�s�ǂݍ��� �� m_pszLineBuf �� NULL �ŏI��镶����𐶐�
	m_pszLineBuf[0] = '\0';
	if (m_nType == FPOINTER || m_nType == FILEPATH) {		// FILE
		// fgets() �֐��������J�X�^�}�C�Y
		int c, n = m_nLineLen;
		char *s2 = m_pszLineBuf;
		while (--n && (c = fgetc(m_file.fp)) != EOF && c != '\n') {
			*s2 = c;
			s2++;
		}
		*s2 = '\0';
		if (c == EOF && s2 == m_pszLineBuf)
			throw FsException(FsException::readError);
	}
	else if (m_nType == IOSTREAM) {	// iostream
		m_file.is->getline(m_pszLineBuf, m_nLineLen);
		if (m_file.is->fail())
			throw FsException(FsException::readError);
	}
	// istrstream �̐���
	if (m_piStream)
		delete m_piStream;
	m_piStream = new istrstream(m_pszLineBuf);

	return m_pszLineBuf;
}

// ��������
void FileStream::Write(const char *format,...)
{
	va_list args;
	va_start(args, format);
	vsprintf(m_pszLineBuf, format, args);
	va_end(args);
	if (m_nType == FPOINTER || m_nType == FILEPATH) {		// FILE
		if (fprintf(m_file.fp, m_pszLineBuf) < 0)
			throw FsException(FsException::writeError);
	}
	else if (m_nType == IOSTREAM) {	// iostream
		*(m_file.is) << m_pszLineBuf;
		if (m_file.is->fail())
			throw FsException(FsException::writeError);
	}
}
//void FileStream::Write(LPCTSTR format,...)
//{
//	CT2CA pszFormat(format);
//	Write(pszFormat);
//}

// �P�s��������
void FileStream::WriteLine(const char *format,...)
{
	va_list args;
	va_start(args, format);
	vsprintf(m_pszLineBuf, format, args);
	va_end(args);
	if (m_nType == FPOINTER || m_nType == FILEPATH) {		// FILE
		if (fprintf(m_file.fp, "%s\n", m_pszLineBuf) < 0)
			throw FsException(FsException::writeError);
	}
	else if (m_nType == IOSTREAM) {	// iostream
		*(m_file.is) << m_pszLineBuf << "\n";
		if (m_file.is->fail())
			throw FsException(FsException::writeError);
	}
}
//void FileStream::WriteLine(LPCTSTR format,...)
//{
//	CT2CA pszFormat(format);
//	WriteLine(pszFormat);
//}

void FileStream::SetBufferLength(int nLineLen)
{
	ASSERT(nLineLen > 0);
	if (m_pszLineBuf)
		delete [] m_pszLineBuf;
	m_nLineLen = nLineLen;
	// Modified by izaty on Aug.12,'08
	// start
	//m_pszLineBuf = new char[m_nLineLen];
	m_pszLineBuf = new char[m_nLineLen+1];
	// end
}

// Appended by izaty on Aug.12,'08
// start
void FileStream::SeekToBegin()
{
	if (m_nType == FPOINTER || m_nType == FILEPATH) {		// FILE
		fseek(m_file.fp, 0, SEEK_SET);
	}
	else if (m_nType == IOSTREAM) {	// iostream
		m_file.is->seekg(0);
		m_file.is->seekp(0);
	}
}
// end

FileStream& FileStream::operator>>(char *psz)
{
	if (m_piStream == NULL)
		throw FsException(FsException::readError);
	*m_piStream >> psz;
	if (m_piStream->fail())
		throw FsException(FsException::readError);
	return *this;
}

//FileStream& FileStream::operator>>(TCHAR *psz)
//{
//	char *pszTemp0 = new char[m_nLineLen+1];
//	::ZeroMemory(pszTemp0, m_nLineLen + 1);
//	operator>>(pszTemp0);
//	CA2CT pszTemp1(pszTemp0);
//	lstrcpy(psz, pszTemp1);
//	delete [] pszTemp0;
//	return *this;
//}

//FileStream& FileStream::operator>>(char& rch)
//{
//	if (m_piStream == NULL)
//		throw FsException(FsException::readError);
//	*m_piStream >> rch;
//	if (m_piStream->fail())
//		throw FsException(FsException::readError);
//	return *this;
//}

FileStream& FileStream::operator>>(TCHAR& rch)
{
	char ch;
	operator>>(ch);
	CA2CT pszTemp1(&ch);
	rch = pszTemp1[0];
	return *this;
}

#include <errno.h>
#define MAXLONGSIZ 16

FileStream& FileStream::operator>>(short& s)
{
	if (m_piStream == NULL)
		throw FsException(FsException::readError);
	// ������Ƃ��ēǂݍ���
	char szBuf[MAXLONGSIZ];
	*m_piStream >> szBuf;
	if (m_piStream->fail())
		throw FsException(FsException::readError);
	// �P�O�i���ɕϊ�
	char **endptr = NULL;
	long l = strtol(szBuf, endptr, 10);
	if (l > SHRT_MAX) {
		s = SHRT_MAX;
		throw FsException(FsException::readError);
	}
	else if (l < SHRT_MIN) {
		s = SHRT_MIN;
		throw FsException(FsException::readError);
	}
	else
		s = (short)l;
	return *this;
}

FileStream& FileStream::operator>>(unsigned short& us)
{
	if (m_piStream == NULL)
		throw FsException(FsException::readError);
	// ������Ƃ��ēǂݍ���
	char szBuf[MAXLONGSIZ];
	*m_piStream >> szBuf;
	if (m_piStream->fail())
		throw FsException(FsException::readError);
	// �P�O�i���ɕϊ�
	char **endptr = NULL;
	unsigned long ul = strtoul(szBuf, endptr, 10);
	if ( ((ul > USHRT_MAX) && (ul <= (ULONG_MAX - (-SHRT_MIN))))
	  || ((ul == ULONG_MAX) && (errno == ERANGE)) ) {
		us = USHRT_MAX;
		throw FsException(FsException::readError);
	}
	else
		us = (unsigned short)ul;
	return *this;
}

FileStream& FileStream::operator>>(int& n)
{
	if (m_piStream == NULL)
		throw FsException(FsException::readError);
	// ������Ƃ��ēǂݍ���
	char szBuf[MAXLONGSIZ];
	*m_piStream >> szBuf;
	if (m_piStream->fail())
		throw FsException(FsException::readError);
	// �P�O�i���ɕϊ�
	char **endptr = NULL;
	long l = strtol(szBuf, endptr, 10);
	if (l > INT_MAX) {
		n = INT_MAX;
		throw FsException(FsException::readError);
	}
	else if (l < INT_MIN) {
		n = INT_MIN;
		throw FsException(FsException::readError);
	}
	else
		n = (int)l;
	return *this;
}

FileStream& FileStream::operator>>(unsigned int& un)
{
	if (m_piStream == NULL)
		throw FsException(FsException::readError);
	// ������Ƃ��ēǂݍ���
	char szBuf[MAXLONGSIZ];
	*m_piStream >> szBuf;
	if (m_piStream->fail())
		throw FsException(FsException::readError);
	// �P�O�i���ɕϊ�
	char **endptr = NULL;
	unsigned long ul = strtoul(szBuf, endptr, 10);
	if ( ((ul > UINT_MAX) && (ul <= (ULONG_MAX - (unsigned long)(-INT_MIN))))
	  || ((ul == ULONG_MAX) && (errno == ERANGE)) ) {
		un = UINT_MAX;
		throw FsException(FsException::readError);
	}
	else
		un = (unsigned int)ul;
	return *this;
}

FileStream& FileStream::operator>>(long& l)
{
	if (m_piStream == NULL)
		throw FsException(FsException::readError);
	// ������Ƃ��ēǂݍ���
	char szBuf[MAXLONGSIZ];
	*m_piStream >> szBuf;
	if (m_piStream->fail())
		throw FsException(FsException::readError);
	// �P�O�i���ɕϊ�
	char **endptr = NULL;
	l = strtol(szBuf, endptr, 10);
	if (errno == ERANGE)
		throw FsException(FsException::readError);
	return *this;
}

FileStream& FileStream::operator>>(unsigned long& ul)
{
	if (m_piStream == NULL)
		throw FsException(FsException::readError);
	// ������Ƃ��ēǂݍ���
	char szBuf[MAXLONGSIZ];
	*m_piStream >> szBuf;
	if (m_piStream->fail())
		throw FsException(FsException::readError);
	// �P�O�i���ɕϊ�
	char **endptr = NULL;
	ul = strtoul(szBuf, endptr, 10);
	if ((ul == ULONG_MAX) && (errno == ERANGE))
		throw FsException(FsException::readError);
	return *this;
}

FileStream& FileStream::operator>>(float& f)
{
	if (m_piStream == NULL)
		throw FsException(FsException::readError);
	*m_piStream >> f;
	if (m_piStream->fail())
		throw FsException(FsException::readError);
	return *this;
}

FileStream& FileStream::operator>>(double& d)
{
	if (m_piStream == NULL)
		throw FsException(FsException::readError);
	*m_piStream >> d;
	if (m_piStream->fail())
		throw FsException(FsException::readError);
	return *this;
}
