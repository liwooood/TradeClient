#ifndef _CONFIG_MANAGER_H_
#define _CONFIG_MANAGER_H_

#include <map>
#include <string>
#include <vector>
#include <boost/thread/detail/singleton.hpp>

class ConfigManager
{
public:
	ConfigManager(void);
	~ConfigManager(void);

	bool LoadConfig();
	std::string GetPath();
	std::string GetTradeGatewayIp();
	int GetTradeGatewayPort();

private:
	std::string m_sPath;

	std::string m_sTradeGatewayIp;
	int m_nTradeGatewayPort;

	
};
typedef boost::detail::thread::singleton<ConfigManager> gConfigManager;

#endif
