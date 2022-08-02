#pragma once
#include "ObjectPool.h"

class CPoolObject
{
public:
	CPoolObject() : m_allocatedId(0), m_canUse(true) {}

	void SetAllocatedId(int id) { this->m_allocatedId = id; }
	int GetAllocatedId() const { return m_allocatedId; }
	bool IsAllocatedObj() { return this->m_allocatedId > 0; }
	void SetCanUse(bool canUse) { this->m_canUse = canUse; }
	bool CanUse() { return this->m_canUse; }

private:
	int  m_allocatedId;           // 分配到的id
	bool    m_canUse;                // 是否可用
};

//内部消息
class InnerMessage : public CPoolObject
{
public:
	InnerMessage(int msgType = 0);
	~InnerMessage();
	InnerMessage& operator=(const InnerMessage& other);
	InnerMessage(int msgType, int bodySize, const char* data);
private:
	void InitData();
	void SetData(int msgType, int bodySize, const char* data);

public:
	int	m_srcPipe;	           // 发送通道
	int  m_msgType;	           // 消息类型
	int     m_msgBodySize;	       // 消息体大小
	char*   m_pMsgBody;              // 消息体指针
};


// 整形数据
struct IntData
{
    int					data;

    int GetSize()
    {
        return sizeof(data);
    }
};

// 布尔数据
struct BoolData
{
    bool	boolData;

    int GetSize()
    {
        return sizeof(BoolData);
    }
};

// 更改数据
struct ChangeData
{
    int					sessionID;
    int					data;

    int GetSize()
    {
        return sizeof(ChangeData);
    }
};

// 无符号整形数据
struct UnsignedIntData
{
    unsigned int        data;

    int GetSize()
    {
        return sizeof(data);
    }
};

// 串口发送消息
struct BufferData
{
    unsigned short delayTime; // 发送前后间隔时间，单位毫秒
    unsigned short dataLen;
	char pData[1] = { 0 };

    BufferData()
    {
        delayTime = 0;
        dataLen = 0;
    }

    int GetSize()
    {
        return sizeof(BufferData) - sizeof(pData) + dataLen;
    }
};


// 内部消息池
class CInnerMsgPool : public CObjectPool<InnerMessage>
{
public:
	CInnerMsgPool(const char* pName = "", int poolSize = 0);
	~CInnerMsgPool();
};


// 发送内部消息
bool SendInnerMsg(int destPipe, int innerMsgType, char* pNetMsg);

/* 
 * 内部消息类型
 * 命名规则为：前缀(MSG) + 消息处理器(MQTT_SESSION) + 业务名称(LOGIN_SERVER)
 * 例如：MSG_MQTT_SESSION_LOGIN_SERVER
 */
enum InnerMsgType
{
	//////////////////////////////////////////////////////////////////////
	// 公共消息（可能有多个线程需要处理的消息）
	MSG_COMMON_BASE = 0,
	MSG_COMMON_MQTT_SESSION_CONNECTED,
	MSG_COMMON_MQTT_SESSION_DISCONNECTED,
	MSG_COMMON_LOGIN_STATE,
	// WiFi已连接
	MSG_COMMON_WIFI_CONNECTED,
	// WiFi已断开
	MSG_COMMON_WIFI_DISCONNECTED,
	// WiFi配置中
	MSG_COMMON_WIFI_CONFIG,


	//////////////////////////////////////////////////////////////////////
	// 主对话框线程处理的消息
	MSG_MAIN_DLG_BASE = 900,
	MSG_MAIN_DLG_SERIAL_CONNECT_STATE,

	//////////////////////////////////////////////////////////////////////
	// Wifi热点会话线程处理的消息
	MSG_WIFI_BASE = 1000,
	MSG_WIFI_START_WIFI_CONFIG,
	MSG_WIFI_OPEN_LISTEN,
	MSG_WIFI_CLOSE_LISTEN,
	MSG_WIFI_SEND_MSG,


	//////////////////////////////////////////////////////////////////////
	// Mqtt会话线程处理的消息
	MSG_MQTT_SESSION_BASE = 2000,
	MSG_MQTT_SESSION_GATEWAY_INITED,
	MSG_MQTT_SESSION_GATEWAY_DEINIT,
	MSG_MQTT_SESSION_INVALID_SESSION,
	MSG_MQTT_SESSION_SEND_MSG,


	//////////////////////////////////////////////////////////////////////
	// Business线程处理的消息
	MSG_BUSINESS_BASE = 3000,
	MSG_BUSINESS_PB_MSG,
	MSG_BUSINESS_UPDATE_MSG,
	//MSG_BUSINESS_UPDATE_FEED_DOG,
	//MSG_BUSINESS_UPDATE_RESULT,
	MSG_BUSINESS_BUTTON_PRESSED,
	MSG_BUSINESS_BUTTON_RELEASED,
	MSG_BUSINESS_RECV_ZIGBEE_MSG,
	// 下载文件返回
	MSG_BUSINESS_DOWNLOAD_FILE_FINISH,
	// 旋钮
	MSG_BUSINESS_RECV_KNOBS_PANEL,
	MSG_BUSINESS_KNOBS_PANEL_LOGIN_STATE,
	// 局域网情景相关处理
	MSG_BUSINESS_RECV_LAN_SESSION_CONNECT,
	MSG_BUSINESS_RECV_LAN_SESSION_DISCONNECT,
	MSG_BUSINESS_RECV_LAN_SESSION,
	// 异常日志上传结束
	MSG_BUSINESS_UPLOAD_EXCEPTION_LOG_FINISH,
	
	//////////////////////////////////////////////////////////////////////
	// 升级程序会话线程处理的消息
	MSG_UPDATE_SESSION_BASE = 4000,
	MSG_UPDATE_SESSION_OPEN_LISTEN,
	MSG_UPDATE_SESSION_CLOSE_LISTEN,
	MSG_UPDATE_SESSION_SEND_MSG,

	//////////////////////////////////////////////////////////////////////////
	// 串口线程处理的消息
	MSG_SERIAL_BASE = 5000,
	MSG_SERIAL_SEND_ZIGBEE_MSG,   // 发送zigbee协议栈消息
	MSG_SERIAL_CONNECT_SERIAL,                  // 连接串口
	MSG_SERIAL_DISCONNECT_SERIAL,           // 断开串口连接
	MSG_SERIAL_ZIGBEE_NETWORK_FORMED,      // zigbee网络形成

	//////////////////////////////////////////////////////////////////////
	// Core程序会话线程处理的消息
	MSG_CORE_SESSION_BASE = 10000,
	MSG_CORE_SESSION_OPEN_LISTEN,
	MSG_CORE_SESSION_CLOSE_LISTEN,
	MSG_CORE_SESSION_SEND_MSG,

	// 通用线程会话消息处理
	MSG_UNIVERSAL_SESSION_BASE = 11000,
	MSG_UNIVERSAL_SESSION_OTA_BAK,
	// 下载文件
	MSG_UNIVERSAL_SESSION_DOWNLOAD_FILE,
	// 上传异常日志
	MSG_UNIVERSAL_SESSION_UPLOAD_LOG,
	
	//////////////////////////////////////////////////////////////////
	// 局域网通用线程处理消息
	MSG_LAN_SESSION_BROADCAST,
	MSG_LAN_SESSION_SEND_SOCKET_MSG,
	MSG_LAN_SESSION_SET_HOME_ID,

	// 伯尔尼旋钮线程消息处理
	MSG_KNOBS_PANEL_SESSION_RECV_KNOBS_PANEL,
	MSG_KNOBS_PANEL_SESSION_RECV_SESSION_DISCONNECT,
	MSG_KNOBS_PANEL_SESSION_RECV_HOME_CHANGE,
	MSG_KNOBS_PANEL_SESSION_RECV_START_WIFI_CONFIG,
	MSG_KNOBS_PANEL_SESSION_RECV_CLIENT_REQUEST,


	// 白盒测试线程处理的消息
	MSG_WHITE_BOX_TEST_THREAD_CLICK,
	MSG_WHITE_BOX_TEST_THREAD_REPLY,
	MSG_WHITE_BOX_TEST_THREAD_SPEC_PROC,

	// 与入口程序会话消息
	MSG_BUSINESS_ENTRY_SESSION_MSG,
	MSG_BUSINESS_ENTRY_HEARTBEAT_START_MSG,
	MSG_ENTRY_SESSION_SEND_MSG,
};
   

