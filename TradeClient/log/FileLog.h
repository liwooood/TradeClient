#ifndef _FILE_LOG_
#define _FILE_LOG_

#include <string>

#include <boost/thread/detail/singleton.hpp>

/*
µ˜ ‘”√
*/

class FileLog
{
public:
	FileLog(void);
	~FileLog(void);

	

	void Log(std::string log);

private:
	std::string m_sLogFile;
};

typedef boost::detail::thread::singleton<FileLog> gFileLog;

#endif
