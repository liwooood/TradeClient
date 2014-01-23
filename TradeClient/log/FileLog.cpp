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
	TRACE("�������������%s\n", log.c_str());

	

	// ����Ŀ¼
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
		outfile << "ʱ�䣺" << sBeginTime << "\n";

		outfile << "���ݣ�" << log << "\n";
			
		// ��һ��
		outfile << "\n";

		outfile.close();
	}

}
