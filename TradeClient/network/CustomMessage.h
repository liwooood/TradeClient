#ifndef CUSTOM_MESSAGE_H
#define CUSTOM_MESSAGE_H

#include <vector>

#include <boost/array.hpp>
#include <boost/scoped_array.hpp> 
#include <boost/noncopyable.hpp>
#include <boost/checked_delete.hpp>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "MsgHeader.h"


/*
����������ԭ��
1.�Ժ���Ը����ڴ�ط���
2.�첽���õ�ʱ���ʺϷ������
*/


class CustomMessage
{
public:
	CustomMessage();

private:
	// ��Ϣͷ
	struct MsgHeader m_MsgHeader;
	

	// ��Ϣ����
	std::vector<char> m_MsgContent;

	
	

public:
	void SetMsgHeader(unsigned char MsgType, int FunctionNo, unsigned char zip=0);
	bool ParseMsgHeader();
	PMSG_HEADER GetMsgHeader();
	size_t GetMsgHeaderSize();


	void SetMsgContent(std::string content);
	char * GetMsgContent();
	size_t GetMsgContentSize();
	std::string GetMsgContentString();

	
};
#endif