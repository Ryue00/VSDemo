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
	int  m_allocatedId;           // ���䵽��id
	bool    m_canUse;                // �Ƿ����
};

//�ڲ���Ϣ
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
	int	m_srcPipe;	           // ����ͨ��
	int  m_msgType;	           // ��Ϣ����
	int     m_msgBodySize;	       // ��Ϣ���С
	char*   m_pMsgBody;              // ��Ϣ��ָ��
};


// ��������
struct IntData
{
    int					data;

    int GetSize()
    {
        return sizeof(data);
    }
};

// ��������
struct BoolData
{
    bool	boolData;

    int GetSize()
    {
        return sizeof(BoolData);
    }
};

// ��������
struct ChangeData
{
    int					sessionID;
    int					data;

    int GetSize()
    {
        return sizeof(ChangeData);
    }
};

// �޷�����������
struct UnsignedIntData
{
    unsigned int        data;

    int GetSize()
    {
        return sizeof(data);
    }
};

// ���ڷ�����Ϣ
struct BufferData
{
    unsigned short delayTime; // ����ǰ����ʱ�䣬��λ����
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


// �ڲ���Ϣ��
class CInnerMsgPool : public CObjectPool<InnerMessage>
{
public:
	CInnerMsgPool(const char* pName = "", int poolSize = 0);
	~CInnerMsgPool();
};


// �����ڲ���Ϣ
bool SendInnerMsg(int destPipe, int innerMsgType, char* pNetMsg);

/* 
 * �ڲ���Ϣ����
 * ��������Ϊ��ǰ׺(MSG) + ��Ϣ������(MQTT_SESSION) + ҵ������(LOGIN_SERVER)
 * ���磺MSG_MQTT_SESSION_LOGIN_SERVER
 */
enum InnerMsgType
{
	//////////////////////////////////////////////////////////////////////
	// ������Ϣ�������ж���߳���Ҫ�������Ϣ��
	MSG_COMMON_BASE = 0,
	MSG_COMMON_MQTT_SESSION_CONNECTED,
	MSG_COMMON_MQTT_SESSION_DISCONNECTED,
	MSG_COMMON_LOGIN_STATE,
	// WiFi������
	MSG_COMMON_WIFI_CONNECTED,
	// WiFi�ѶϿ�
	MSG_COMMON_WIFI_DISCONNECTED,
	// WiFi������
	MSG_COMMON_WIFI_CONFIG,


	//////////////////////////////////////////////////////////////////////
	// ���Ի����̴߳������Ϣ
	MSG_MAIN_DLG_BASE = 900,
	MSG_MAIN_DLG_SERIAL_CONNECT_STATE,

	//////////////////////////////////////////////////////////////////////
	// Wifi�ȵ�Ự�̴߳������Ϣ
	MSG_WIFI_BASE = 1000,
	MSG_WIFI_START_WIFI_CONFIG,
	MSG_WIFI_OPEN_LISTEN,
	MSG_WIFI_CLOSE_LISTEN,
	MSG_WIFI_SEND_MSG,


	//////////////////////////////////////////////////////////////////////
	// Mqtt�Ự�̴߳������Ϣ
	MSG_MQTT_SESSION_BASE = 2000,
	MSG_MQTT_SESSION_GATEWAY_INITED,
	MSG_MQTT_SESSION_GATEWAY_DEINIT,
	MSG_MQTT_SESSION_INVALID_SESSION,
	MSG_MQTT_SESSION_SEND_MSG,


	//////////////////////////////////////////////////////////////////////
	// Business�̴߳������Ϣ
	MSG_BUSINESS_BASE = 3000,
	MSG_BUSINESS_PB_MSG,
	MSG_BUSINESS_UPDATE_MSG,
	//MSG_BUSINESS_UPDATE_FEED_DOG,
	//MSG_BUSINESS_UPDATE_RESULT,
	MSG_BUSINESS_BUTTON_PRESSED,
	MSG_BUSINESS_BUTTON_RELEASED,
	MSG_BUSINESS_RECV_ZIGBEE_MSG,
	// �����ļ�����
	MSG_BUSINESS_DOWNLOAD_FILE_FINISH,
	// ��ť
	MSG_BUSINESS_RECV_KNOBS_PANEL,
	MSG_BUSINESS_KNOBS_PANEL_LOGIN_STATE,
	// �������龰��ش���
	MSG_BUSINESS_RECV_LAN_SESSION_CONNECT,
	MSG_BUSINESS_RECV_LAN_SESSION_DISCONNECT,
	MSG_BUSINESS_RECV_LAN_SESSION,
	// �쳣��־�ϴ�����
	MSG_BUSINESS_UPLOAD_EXCEPTION_LOG_FINISH,
	
	//////////////////////////////////////////////////////////////////////
	// ��������Ự�̴߳������Ϣ
	MSG_UPDATE_SESSION_BASE = 4000,
	MSG_UPDATE_SESSION_OPEN_LISTEN,
	MSG_UPDATE_SESSION_CLOSE_LISTEN,
	MSG_UPDATE_SESSION_SEND_MSG,

	//////////////////////////////////////////////////////////////////////////
	// �����̴߳������Ϣ
	MSG_SERIAL_BASE = 5000,
	MSG_SERIAL_SEND_ZIGBEE_MSG,   // ����zigbeeЭ��ջ��Ϣ
	MSG_SERIAL_CONNECT_SERIAL,                  // ���Ӵ���
	MSG_SERIAL_DISCONNECT_SERIAL,           // �Ͽ���������
	MSG_SERIAL_ZIGBEE_NETWORK_FORMED,      // zigbee�����γ�

	//////////////////////////////////////////////////////////////////////
	// Core����Ự�̴߳������Ϣ
	MSG_CORE_SESSION_BASE = 10000,
	MSG_CORE_SESSION_OPEN_LISTEN,
	MSG_CORE_SESSION_CLOSE_LISTEN,
	MSG_CORE_SESSION_SEND_MSG,

	// ͨ���̻߳Ự��Ϣ����
	MSG_UNIVERSAL_SESSION_BASE = 11000,
	MSG_UNIVERSAL_SESSION_OTA_BAK,
	// �����ļ�
	MSG_UNIVERSAL_SESSION_DOWNLOAD_FILE,
	// �ϴ��쳣��־
	MSG_UNIVERSAL_SESSION_UPLOAD_LOG,
	
	//////////////////////////////////////////////////////////////////
	// ������ͨ���̴߳�����Ϣ
	MSG_LAN_SESSION_BROADCAST,
	MSG_LAN_SESSION_SEND_SOCKET_MSG,
	MSG_LAN_SESSION_SET_HOME_ID,

	// ��������ť�߳���Ϣ����
	MSG_KNOBS_PANEL_SESSION_RECV_KNOBS_PANEL,
	MSG_KNOBS_PANEL_SESSION_RECV_SESSION_DISCONNECT,
	MSG_KNOBS_PANEL_SESSION_RECV_HOME_CHANGE,
	MSG_KNOBS_PANEL_SESSION_RECV_START_WIFI_CONFIG,
	MSG_KNOBS_PANEL_SESSION_RECV_CLIENT_REQUEST,


	// �׺в����̴߳������Ϣ
	MSG_WHITE_BOX_TEST_THREAD_CLICK,
	MSG_WHITE_BOX_TEST_THREAD_REPLY,
	MSG_WHITE_BOX_TEST_THREAD_SPEC_PROC,

	// ����ڳ���Ự��Ϣ
	MSG_BUSINESS_ENTRY_SESSION_MSG,
	MSG_BUSINESS_ENTRY_HEARTBEAT_START_MSG,
	MSG_ENTRY_SESSION_SEND_MSG,
};
   

