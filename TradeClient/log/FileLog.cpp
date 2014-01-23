#include "stdafx.h"

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/filesystem.hpp>

#include "FileLog.h"

#include "config/ConfigManager.h"


FileLog::FileLog(void)
{
}


FileLog::~FileLog(void)
{
}

void FileLog::Log(std::string log)
{
	TRACE("调试内容输出：%s\n", log.c_str());

	

	// 创建目录
	std::string sLogDir = gConfigManager::instance().GetPath() + "log\\";

	boost::filesystem::path p(sLogDir);
	if (!boost::filesystem::exists(p))
	{
		boost::filesystem::create_directories(p);
	}

	m_sLogFile = "debug_";

	

	boost::gregorian::date day = boost::gregorian::day_clock::local_day();
	m_sLogFile += to_iso_extended_string(day);
	m_sLogFile += ".log";


	std::ofstream outfile(m_sLogFile.c_str(), std::ios_base::app);
	if (outfile.is_open())
	{
		boost::posix_time::ptime beginTime =  boost::posix_time::microsec_clock::local_time();
		std::string sBeginTime = boost::gregorian::to_iso_extended_string(beginTime.date()) + " " + boost::posix_time::to_simple_string(beginTime.time_of_day());
		outfile << "时间：" << sBeginTime << "\n";

		outfile << "内容：" << log << "\n";
			
		// 隔一行
		outfile << "\n";

		outfile.close();
	}

}
