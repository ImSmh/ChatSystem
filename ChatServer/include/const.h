#pragma once
#include <functional>
#include "Log.h"

static Logger::ptr g_logger = LOG_NAME("ChatServer");


enum ErrorCodes {
	Success = 0,
	Error_Json = 1001,  
	RPCFailed = 1002,  
	VarifyExpired = 1003, 
	VarifyCodeErr = 1004,
	UserExist = 1005,       
	PasswdErr = 1006,   
	EmailNotMatch = 1007,  
	PasswdUpFailed = 1008,  
	PasswdInvalid = 1009,   
	TokenInvalid = 1010, 
	UidInvalid = 1011, 
};


// Defer��
class Defer {
public:
	// ����һ��lambda����ʽ���ߺ���ָ��
	Defer(std::function<void()> func) : func_(func) {}

	// ����������ִ�д���ĺ���
	~Defer() {
		func_();
	}

private:
	std::function<void()> func_;
};

#define MAX_LENGTH 1024*2
//ͷ���ܳ���
#define HEAD_TOTAL_LEN 4
//ͷ��id����
#define HEAD_ID_LEN 2
//ͷ�����ݳ���
#define HEAD_DATA_LEN 2
#define MAX_RECVQUE 10000
#define MAX_SENDQUE 1000


enum MSG_IDS {
	MSG_CHAT_LOGIN				= 1005, //�û���½
	MSG_CHAT_LOGIN_RSP			= 1006, //�û���½�ذ�
	ID_SEARCH_USER_REQ			= 1007, //�û���������
	ID_SEARCH_USER_RSP			= 1008, //�����û��ذ�
	ID_ADD_FRIEND_REQ			= 1009, //�������Ӻ�������
	ID_ADD_FRIEND_RSP			= 1010, //�������Ӻ��ѻظ�
	ID_NOTIFY_ADD_FRIEND_REQ	= 1011, //֪ͨ�û����Ӻ�������
	ID_AUTH_FRIEND_REQ			= 1013, //��֤��������
	ID_AUTH_FRIEND_RSP			= 1014, //��֤���ѻظ�
	ID_NOTIFY_AUTH_FRIEND_REQ	= 1015, //֪ͨ�û���֤��������
	ID_TEXT_CHAT_MSG_REQ		= 1017, //�ı�������Ϣ����
	ID_TEXT_CHAT_MSG_RSP		= 1018, //�ı�������Ϣ�ظ�
	ID_NOTIFY_TEXT_CHAT_MSG_REQ = 1019, //֪ͨ�û��ı�������Ϣ
};

#define USERIPPREFIX  "uip_"
#define USERTOKENPREFIX  "utoken_"
#define IPCOUNTPREFIX  "ipcount_"
#define USER_BASE_INFO "ubaseinfo_"
#define LOGIN_COUNT  "logincount"
#define NAME_INFO  "nameinfo_"


