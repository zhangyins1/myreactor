#include "TypeDef.h"
#ifndef ST_WIN32
#include <sys/time.h>
#endif
#include "Log.h"

void _get_time_hmsu_head(char* s, size_t n)
{
	struct timeval tv;
	if (gettimeofday(&tv, NULL) == 0)
	{
		time_t& t = tv.tv_sec;
		struct tm* tm2 = localtime(&t);

		snprintf(s, n, "%02d:%02d:%02d.%02d", tm2->tm_hour, tm2->tm_min, tm2->tm_sec, tv.tv_usec);
	}
	else
	{
		snprintf(s, n, "??:??:??.??");
	}
}

void LogInfo(const char *file, int line, const char *flag, const char* key, const char* msg, ...)
{
	va_list ap;
	memset(&ap, 0, sizeof ap);

	va_start(ap, msg);
	Log2Terminal(flag, file, line, key, msg, ap);
	va_end(ap);
}

template <size_t size>
void _Log(char(&strDest)[size], const char* section, const char *file, int line, const char* key, const char* msg, va_list& ap)
{
	char szHmsu[32];
	memset(szHmsu, 0, 32);

	_get_time_hmsu_head(szHmsu, sizeof(szHmsu));

	int n1 = snprintf(strDest, (int)size, "%s  [%s][%s][%s:%d]", szHmsu, section, key, file, line);
	if (n1 > 0 && n1 < (int)size)
	{
		int n2 = vsnprintf(strDest + n1, (int)size - n1, msg, ap);
		if (n2 > 0 && (n1 + n2) < (int)size)
		{
			strDest[n1 + n2] = '\0';
		}
	}
}

void Log2Terminal(const char* section, const char *file, int line, const char* key, const char* msg, va_list& ap)
{
	char szTmp[MAX_LOG_BUFF_SIZE];
	memset(szTmp, 0, MAX_LOG_BUFF_SIZE * sizeof(char));

	_Log(szTmp, section, file, line, key, msg, ap);
	printf("%s\n", szTmp);
}

void CLog::log_print_to_term(const char *flagStr, const char *errStr, int errCode, const char *file, int line)
{
	char timestr[32] = { 0 };
	_get_time_hmsu_head(&timestr[0], sizeof(timestr));

	int loglen = strlen(errStr) + strlen(timestr) + strlen(flagStr) + strlen(file) + 128;
	char *logstr = new char[loglen];

	memset(logstr, 0x00, loglen);
	snprintf(logstr, loglen, "%s [%s]: code: %d, msg: %s, [%s:%d]\n", flagStr, timestr, errCode, errStr, file, line);
	printf("%s", logstr);

	delete[] logstr;
	logstr = nullptr;
}