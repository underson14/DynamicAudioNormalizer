///////////////////////////////////////////////////////////////////////////////
// Dynamic Audio Normalizer
// Copyright (C) 2014 LoRd_MuldeR <MuldeR2@GMX.de>
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version, but always including the *additional*
// restrictions defined in the "License.txt" file.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//
// http://www.gnu.org/licenses/gpl-2.0.txt
///////////////////////////////////////////////////////////////////////////////

#pragma once

//============================================================================
// COMMON
//============================================================================

#include <cstdlib>
#include <stdint.h>
#include <cstdio>
#include <cstring>
#include <cstdarg>

#include <sys/types.h>
#include <sys/stat.h>

void SYSTEM_INIT(void);

//============================================================================
// WINDOWS
//============================================================================

#ifdef _WIN32 /*Windows only*/

#include <io.h>

#define _TXT(X) L##X
#define TXT(X) _TXT(X)
#define MAIN wmain
#define FMT_CHAR L"%S"

typedef wchar_t CHR;
typedef struct _stat64 STAT64;

inline static int PRINT(const CHR *const format, ...)
{
	va_list ap;
	va_start(ap, format);
	const int result = vwprintf_s(format, ap);
	va_end(ap);
	return result;
}

inline static void FLUSH(void)
{
	fflush(stderr);
}

inline static FILE *FOPEN(const CHR *const fileName, const CHR *const mode)
{
	FILE *temp;
	if(_wfopen_s(&temp, fileName, mode) == 0)
	{
		return temp;
	}
	return NULL;
}

inline static int FILENO(FILE *const file)
{
	return _fileno(file);
}

inline static int FSTAT64(const int fd, STAT64 *stat)
{
	return _fstat64(fd, stat);
}

inline static int FSEEK64(FILE *const file, int64_t offset, const int origin)
{
	return _fseeki64(file, offset, origin);
}

inline static int64_t FTELL64(FILE *const file)
{
	return _ftelli64(file);
}

inline static int ACCESS(const CHR *const fileName, const int mode)
{
	return _waccess(fileName, mode);
}

inline static int STRCASECMP(const CHR *const s1, const CHR *const s2)
{
	return _wcsicmp(s1, s2);
}

inline static const CHR *STRCHR(const CHR *const str, const CHR c)
{
	return wcschr(str, c);
}

inline static const CHR *STRRCHR(const CHR *const str, const CHR c)
{
	return wcsrchr(str, c);
}

inline static int SNPRINTF(CHR *const buffer, size_t buffSize, const CHR *const format, ...)
{
	va_list ap;
	va_start(ap, format);
	const int result = _vsnwprintf_s(buffer, buffSize, _TRUNCATE, format, ap);
	va_end(ap);
	return result;
}

inline static int SSCANF(const CHR *const str, const CHR *const format, ...)
{
	va_list ap;
	va_start(ap, format);
	const int result = vswscanf(str, format, ap);
	va_end(ap);
	return result;
}

#endif //_WIN32

//============================================================================
// LINUX
//============================================================================

#ifdef __linux /*Linux only*/

#include <unistd.h>

#define _TXT(X) X
#define TXT(X) _TXT(X)
#define MAIN main
#define FMT_CHAR "%s"

typedef char CHR;
typedef struct stat64 STAT64;

inline static int PRINT(const CHR *const format, ...)
{
	va_list ap;
	va_start(ap, format);
	const int result = vprintf(format, ap);
	va_end(ap);
	return result;
}

inline static void FLUSH(void)
{
	fflush(stderr);
}

inline static FILE *FOPEN(const CHR *const fileName, const CHR *const mode)
{
	return fopen(fileName, mode);
}

inline static int FILENO(FILE *const file)
{
	return fileno(file);
}

inline static int FSTAT64(const int fd, STAT64 *stat)
{
	return fstat64(fd, stat);
}

inline static int FSEEK64(FILE *const file, int64_t offset, const int origin)
{
	return fseeko64(file, offset, origin);
}

inline static int64_t FTELL64(FILE *const file)
{
	return ftello64(file);
}

inline static int ACCESS(const CHR *const fileName, const int mode)
{
	return access(fileName, mode);
}

inline static int STRCASECMP(const CHR *const s1, const CHR *const s2)
{
	return strcasecmp(s1, s2);
}

inline static const CHR *STRCHR(const CHR *const str, const CHR c)
{
	return strchr(str, c);
}

inline static const CHR *STRRCHR(const CHR *const str, const CHR c)
{
	return strrchr(str, c);
}

inline static int SNPRINTF(CHR *const buffer, size_t buffSize, const CHR *const format, ...)
{
	va_list ap;
	va_start(ap, format);
	const int result = vsnprintf(buffer, buffSize, format, ap);
	va_end(ap);
	return result;
}

inline static int SSCANF(const CHR *const str, const CHR *const format, ...)
{
	va_list ap;
	va_start(ap, format);
	const int result = vsscanf(str, format, ap);
	va_end(ap);
	return result;
}

#endif //__linux

