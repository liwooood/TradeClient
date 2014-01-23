#include "stdafx.h"



#include <list>

#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/algorithm/string.hpp>

#include "xml/pugixml.hpp"

#include "ConfigManager.h"


ConfigManager::ConfigManager(void)
{
}

ConfigManager::~ConfigManager(void)
{
}

bool ConfigManager::LoadConfig()
{
	char szPath[255];
	memset(szPath, 0x00, sizeof(szPath));

	::GetModuleFileName(NULL, szPath, sizeof(szPath));

	boost::filesystem::path p(szPath);
	m_sPath = p.parent_path().string() + "\\";

	std::string sConfigFile;		
	sConfigFile = m_sPath + "TradeClient.xml";
	
	pugi::xml_document doc;
	if (!doc.load_file(sConfigFile.c_str()))
		return false;

	pugi::xpath_node node;
	node = doc.select_single_node("/config/TradeGateway");
	std::string serverInfo = node.node().child_value();
	/*
	std::vector<std::string> key_values;
	boost::split(key_values, serverInfo, boost::is_any_of(":"));
	m_sTradeGatewayIp = key_values[0];
	m_nTradeGatewayPort = boost::lexical_cast<int>(key_values[1]);
	*/
	return true;
}

std::string ConfigManager::GetPath()
{
	return m_sPath;
}

std::string ConfigManager::GetTradeGatewayIp()
{
	return m_sTradeGatewayIp;
}

int ConfigManager::GetTradeGatewayPort()
{
	return m_nTradeGatewayPort;
}



