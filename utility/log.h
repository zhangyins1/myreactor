#ifndef __LOG_H_H__
#define __LOG_H_H__

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>


#define IS_DEBUG 0

#if IS_DEBUG
#define LOG_DEBUG(msg, code) CLog::log_print_to_term("[DEBUG]", (msg), (code), __FILE__, __LINE__)
#define LOG_ERROR(msg, code) CLog::log_print_to_term("[ERROR]", (msg), (code), __FILE__, __LINE__)
#define LOG_INFO(msg, code) CLog::log_print_to_term("", (msg), (code), __FILE__, __LINE__)
#define _LOG_INFO(key, msg, ...) LogInfo(__FILE__, __LINE__, "", key, msg, ##__VA_ARGS__)
#define _LOG_WARNING(key, msg, ...) LogInfo(__FILE__, __LINE__, "WARNING", key, msg, ##__VA_ARGS__)
#define _LOG_ERROR(key, msg, ...) LogInfo(__FILE__, __LINE__, "ERROR", key, msg, ##__VA_ARGS__)
#else 
#define LOG_DEBUG(msg, code) 
#define LOG_ERROR(msg, code) 
#define LOG_INFO(msg, code) 
#define _LOG_INFO(key, msg, ...) 
#define _LOG_WARNING(key, msg, ...) 
#define _LOG_ERROR(key, msg, ...) 
#endif

//获得当前时间的格式化的时分秒毫秒 HH:MM:SS.UUUUUU

class CLog
{
public:
	CLog() = delete;
	~CLog() = delete;
	CLog(const CLog& rhs) = delete; 
	CLog(const CLog&& rhs) = delete; 
	CLog& operator=(const CLog& rhs) = delete;
	CLog& operator=(const CLog&& rhs) = delete;
public:
	static void log_print_to_term(const char *flagStr, const char *errStr, int errCode, const char *file, int line);
};
enum { MAX_LOG_BUFF_SIZE = 4096, };

extern void _get_time_hmsu_head(char* s, size_t n);
extern void LogInfo(const char *file, int line, const char *flag, const char* key, const char* msg, ...);
extern void Log2Terminal(const char* section, const char *file, int line, const char* key, const char* msg, va_list& ap);
#endif // !__LOG_H_H__