#ifndef _IDM_NET_SDK_H_
#define _IDM_NET_SDK_H_

#if (defined(_WIN32))
#if defined(_MAKE_STATIC)
#define IDM_API
#else
#if defined(_DLLIMPORT)
#define IDM_API  extern "C" __declspec(dllimport)
#else
#define IDM_API  extern "C" __declspec(dllexport)
#endif
#endif
#define CALLBACK __stdcall
#define VOID void
typedef int                 INT;
typedef unsigned int        UINT;
typedef long                LONG;
typedef unsigned long       ULONG;
typedef short               SHORT;
typedef unsigned short      USHORT;
typedef char                CHAR;
typedef unsigned char       UCHAR;
typedef float               FLOAT;
typedef long long           LLONG;
typedef unsigned long long  ULLONG;
#elif defined(__linux__) || defined(__APPLE__)
#define IDM_API __attribute__((visibility("default")))
#define CALLBACK
typedef void                VOID;
typedef int                 INT;
typedef unsigned int        UINT;
typedef int                 LONG;
typedef unsigned int        ULONG;
typedef short               SHORT;
typedef unsigned short      USHORT;
typedef char                CHAR;
typedef unsigned char       UCHAR;
typedef float               FLOAT;
typedef long long           LLONG;
typedef unsigned long long  ULLONG;
#endif

#if 0
/* 基础宏定义 */
#endif

#define IDM_SUCCESS                         0
#define IDM_ERROR_DEFINED                   1012120000
#define IDM_ERROR_UNINITIALIZED             (IDM_ERROR_DEFINED + 1)         /* SDK未初始化 */
#define IDM_ERROR_PASSWORD                  (IDM_ERROR_DEFINED + 2)         /* 用户名密码错误 */
#define IDM_ERROR_INVALID_HANDLE            (IDM_ERROR_DEFINED + 3)         /* 无效的句柄 */
#define IDM_ERROR_CHANNEL_NUMBER            (IDM_ERROR_DEFINED + 4)         /* 通道号错误 */
#define IDM_ERROR_MAX_NUM                   (IDM_ERROR_DEFINED + 5)         /* 超过最大数量 */
#define IDM_ERROR_CONNECT_FAILED            (IDM_ERROR_DEFINED + 6)         /* 连接设备失败 */
#define IDM_ERROR_SEND_FAILED               (IDM_ERROR_DEFINED + 7)         /* 发送失败 */
#define IDM_ERROR_RECEIVE_FAILED            (IDM_ERROR_DEFINED + 8)         /* 接收失败 */
#define IDM_ERROR_RECEIVE_TIMEOUT           (IDM_ERROR_DEFINED + 9)         /* 接收超时 */
#define IDM_ERROR_DATA                      (IDM_ERROR_DEFINED + 10)        /* 发送或者接收的数据错误 */
#define IDM_ERROR_PARAMETER                 (IDM_ERROR_DEFINED + 11)        /* 参数错误 */
#define IDM_ERROR_OPERATE                   (IDM_ERROR_DEFINED + 12)        /* 操作错误 */
#define IDM_ERROR_BUFFER_NOT_ENOUGH         (IDM_ERROR_DEFINED + 13)        /* 数据缓冲区不足 */
#define IDM_ERROR_CREATE_SOCKET             (IDM_ERROR_DEFINED + 14)        /* 创建SOCKET失败 */
#define IDM_ERROR_SET_SOCKET                (IDM_ERROR_DEFINED + 15)        /* 主动注册模式下 找不到设备ID */
#define IDM_ERROR_BIND_SOCKET               (IDM_ERROR_DEFINED + 16)        /* 绑定SOCKET失败 */
#define IDM_ERROR_LISTEN_SOCKET             (IDM_ERROR_DEFINED + 17)        /* 监听SOCKET失败 */
#define IDM_ERROR_CREATE_FILE               (IDM_ERROR_DEFINED + 18)        /* 创建文件失败 */
#define IDM_ERROR_OPEN_FILE                 (IDM_ERROR_DEFINED + 19)        /* 打开文件失败 */
#define IDM_ERROR_WRITE_FILE                (IDM_ERROR_DEFINED + 20)        /* 写文件失败 */
#define IDM_ERROR_LOAD_LIVE                 (IDM_ERROR_DEFINED + 21)        /* 预览组件加载失败 */
#define IDM_ERROR_LOAD_VOD                  (IDM_ERROR_DEFINED + 22)        /* 回放组件加载失败 */
#define IDM_ERROR_LOAD_ALARM                (IDM_ERROR_DEFINED + 23)        /* 报警组件加载失败 */
#define IDM_ERROR_LOAD_VOICETALK            (IDM_ERROR_DEFINED + 24)        /* 语音对讲组件加载失败 */
#define IDM_ERROR_NOT_SUPPORT               (IDM_ERROR_DEFINED + 25)        /* 设备不支持 */
#define IDM_ERROR_ALLOC_FAILED              (IDM_ERROR_DEFINED + 26)        /* 分配内存失败 */
#define IDM_ERROR_NULLPTR                   (IDM_ERROR_DEFINED + 27)        /* 空指针 */
#define IDM_ERROR_LOAD_PDSP                 (IDM_ERROR_DEFINED + 28)        /* 设备搜索组件加载失败 */
#define IDM_ERROR_KEEPALIVE_TIMEOUT         (IDM_ERROR_DEFINED + 29)        /* 接收心跳超时 */
#define IDM_ERROR_INVALID_SOCKET            (IDM_ERROR_DEFINED + 30)        /* 网络套接字失效 */
#define IDM_ERROR_NO_NETCARD                (IDM_ERROR_DEFINED + 31)        /* 网卡列表加载失败 */

#define IDM_IPV4_ADDRESS_LEN                16
#define IDM_IPV6_ADDRESS_LEN                64
#define IDM_DOMAIN_NAME_LEN                 64
#define IDM_SERIAL_NUMBER_LEN               64
#define IDM_MAC_ADDRESS_LEN                 64
#define IDM_DEVICE_ID_LEN                   64
#define IDM_DEVICE_NAME_LEN                 64
#define IDM_DEVICE_MODEL_LEN                64
#define IDM_DEVICE_IP_MAX_LEN               16
#define IDM_USERNAME_MAX_LEN                64
#define IDM_PASSWORD_MAX_LEN                64
#define IDM_RTSPURL_MAX_LEN                 256

#define IDM_UPNP_PORT_NUM                   32
#define IDM_ALARM_OUT_MAX_NUM               16
#define IDM_CHANNEL_MAX_NUM                 256
#define IDM_HARDDISK_MAX_NUM                64

#define EXCEPTION_KEEPALIVE                 0
#define EXCEPTION_REALPLAY                  1
#define EXCEPTION_PLAYBACK                  2
#define EXCEPTION_ALARM                     3
#define EXCEPTION_VOICE                     4
#define EXCEPTION_RECONNECT					5

#define STREAM_VIDEO                        0
#define STREAM_AUDIO                        1
#define STREAM_PRIVATE                      2

#define PLAYBACK_START                      0
#define PLAYBACK_PAUSE                      1
#define PLAYBACK_RESUME                     2
#define PLAYBACK_SPEED                      3
#define PLAYBACK_FRAME                      4
#define PLAYBACK_FORWARD                    5
#define PLAYBACK_BACKWARD                   6
#define PLAYBACK_SET_SEEK                   7
#define PLAYBACK_GET_SEEK                   8
#define PLAYBACK_SET_TIME                   9
#define PLAYBACK_GET_TIME                   10
#define PLAYBACK_AUDIO_ON                   11
#define PLAYBACK_AUDIO_OFF                  12
#define PLAYBACK_SET_VOLUME                 13

#define PTZ_LIGHT                           1
#define PTZ_WIPER                           2
#define PTZ_FAN                             3
#define PTZ_HEATER                          4
#define PTZ_INFRARED                        5
#define PTZ_FOCUS_NEAR                      11
#define PTZ_FOCUS_FAR                       12
#define PTZ_ZOOM_IN                         13
#define PTZ_ZOOM_OUT                        14
#define PTZ_IRIS_OPEN                       15
#define PTZ_IRIS_CLOSE                      16
#define PTZ_UP                              21
#define PTZ_DOWN                            22
#define PTZ_LEFT                            23
#define PTZ_RIGHT                           24
#define PTZ_LEFT_UP                         25
#define PTZ_RIGHT_UP                        26
#define PTZ_LEFT_DOWN                       27
#define PTZ_RIGHT_DOWN                      28
#define PTZ_AUTO_SCAN                       29
#define PTZ_AUTO_FOCUS                      30
#define PTZ_RESET_LENS                      31
#define PTZ_3D_ZOOM                         32
#define PTZ_UP_ZOOM_IN                      33
#define PTZ_UP_ZOOM_OUT                     34
#define PTZ_DOWN_ZOOM_IN                    35
#define PTZ_DOWN_ZOOM_OUT                   36
#define PTZ_LEFT_ZOOM_IN                    37
#define PTZ_LEFT_ZOOM_OUT                   38
#define PTZ_RIGHT_ZOOM_IN                   39
#define PTZ_RIGHT_ZOOM_OUT                  40
#define PTZ_LEFT_UP_ZOOM_IN                 41
#define PTZ_LEFT_UP_ZOOM_OUT                42
#define PTZ_RIGHT_UP_ZOOM_IN                43
#define PTZ_RIGHT_UP_ZOOM_OUT               44
#define PTZ_LEFT_DOWN_ZOOM_IN               45
#define PTZ_LEFT_DOWN_ZOOM_OUT              46
#define PTZ_RIGHT_DOWN_ZOOM_IN              47
#define PTZ_RIGHT_DOWN_ZOOM_OUT             48
#define PTZ_SETUP_PRESET                    51
#define PTZ_CLEAR_PRESET                    52
#define PTZ_GOTO_PRESET                     53
#define PTZ_SETUP_ZERO                      54
#define PTZ_CLEAR_ZERO                      55
#define PTZ_GOTO_ZERO                       56
#define PTZ_START_RECORD_TRAIL              57
#define PTZ_STOP_RECORD_TRAIL               58
#define PTZ_START_RUN_TRAIL                 59
#define PTZ_STOP_RUN_TRAIL                  60
#define PTZ_CLEAR_TRAIL                     61
#define PTZ_CLEAR_ALL_TRAIL                 62
#define PTZ_START_RUN_CRUISE                63
#define PTZ_STOP_RUN_CRUISE                 64
#define PTZ_CLEAR_CRUISE                    65
#define PTZ_LOCK                            67
#define PTZ_UNLOCK                          68
#define PTZ_IRCUT                           69
#define ONE_TOUCH_PARK						70 //设置并开启一键守望
#define ONE_TOUCH_CRUISE					71 //调用一键巡航
#define SET_PTZ_INIT_POS					72 //设置枪球联动球机云台初始位置
#define MANUAL_TRACK						73 //手动跟踪（枪球联动）

#define SYSTEM_RESTORE                      0
#define SYSTEM_REBOOT                       1

#if 0
/* 参数配置命令宏定义 */
#endif

/* 系统 */
#define CONFIG_SYSTEM_TIME                  0x00000001
#define CONFIG_SYSTEM_INFO                  0x00000002
#define CONFIG_SYSTEM_INFO_V2               0x00000003

/* 网络 */
#define CONFIG_NET_PARAM                    0x00000101
#define CONFIG_NET_DDNS                     0x00000102
#define CONFIG_NET_PPPOE                    0x00000103
#define CONFIG_NET_UPNP                     0x00000104
#define CONFIG_NET_NTP                      0x00000105
/* 通道管理 */
#define CONFIG_CHAN_ADD_DEVICE              0x00000301
#define CONFIG_CHAN_MODIFY_DEVICE           0x00000302
#define CONFIG_CHAN_DELETE_DEVICE           0x00000303
#define CONFIG_CHAN_QUERY_DEVICES           0x00000304
#define CONFIG_CHAN_DELETE_DEVICES           0x00000305

/* 通道参数 */
#define CONFIG_VIDEO_OSD                    0x00000401
#define CONFIG_VIDEO_CFG                    0x00000402
#define CONFIG_AUDIO_CFG                    0x00000403
#define CONFIG_VIDEO_OSD_V2                 0x00000404
/* 云台 */
#define CONFIG_PTZ_PRESET_INFO              0x00000501
#define CONFIG_PTZ_CRUISE_INFO              0x00000502
#define CONFIG_PTZ_WATCH_INFO               0x00000503
/* 算法配置*/
#define CONFIG_INTELLIGENCE_AIUNITE         0x00000601
#define CONFIG_INTELLIGENCE_PARKING         0x00000602
#define CONFIG_INTELLIGENCE_SPEED           0x00000603
#define CONFIG_INTELLIGENCE_PERIMETER       0x00000604

/* 报警输入输出 */
#define CONFIG_ALARM_OUTPUT                 0x00000701
#define CONFIG_ALARM_LINKAGE                0x00000702
#define CONFIG_ALARM_GUARDPLAN              0x00000703
/* 报警语音 */
#define CONFIG_VOICE_LIST                   0x00000801
#define CONFIG_VOICE_INFO                   0x00000802
#if 0
/* 能力集获取命令宏定义 */
#endif
#define DEVICE_PTZ_CAPABILITIES             0x00000001
#define DEVICE_VIDEO_CAPABILITIES           0x00000002
#define DEVICE_AUDIO_CAPABILITIES           0x00000003

#if 0
/* 报警命令宏定义 */
#endif

/* 事件 */
#define ALARM_EVENT_JSON                    0           /* 通用事件报警 */
/* Device Common */
#define ALARM_DC_MOBILE_DETECTION           0x01010001  /* 移动侦测 */
#define ALARM_DC_ALARM_IN                   0x01010002  /* 报警输入 */
/* Device Failure */
#define ALARM_DF_OFFLINE                    0x01020001  /* 设备离线 */
#define ALARM_DF_FREQUENT_OFFLINE           0x01020002  /* 设备频繁离线 */
#define ALARM_DF_LONG_TIME_OFFLINE          0x01020003  /* 设备长时间离线 */
#define ALARM_DF_PORT_ALARM                 0x01020004  /* 端口报警 */
#define ALARM_DF_STREAM_FAILURE             0x01020005  /* 取流失败 */
#define ALARM_DF_STREAM_TIMEOUT             0x01020006  /* 取流频繁超时 */
#define ALARM_DF_AUDIO_DETECTION            0x01020007  /* 音频检测 */
#define ALARM_DF_IP_CONFLICT                0x01020008  /* IP冲突 */
#define ALARM_DF_MAC_CONFLICT               0x01020009  /* MAC冲突 */
#define ALARM_DF_NET_ABORT                  0x0102000a  /* 断网报警 */
#define ALARM_DF_NO_DISK                    0x0102000b  /* 无硬盘报警 */
#define ALARM_DF_STORAGE_ERROR              0x0102000c  /* 存储错误 */
#define ALARM_DF_STORAGE_FULL               0x0102000d  /* 存储空间满 */
#define ALARM_DF_ONLINE                     0x0102000e  /* 设备上线 */
/* Video Quality*/
#define ALARM_VQ_VIDEO_LOSS                 0x01030001  /* 视频信号丢失 */
#define ALARM_VQ_CONTRAST_LOW               0x01030002  /* 对比度低 */
#define ALARM_VQ_VIDEO_BLURRED              0x01030003  /* 图像模糊 */
#define ALARM_VQ_VIDEO_BRIGHT               0x01030004  /* 图像过亮 */
#define ALARM_VQ_VIDEO_DARK                 0x01030005  /* 图像过暗 */
#define ALARM_VQ_VIDEO_CAST                 0x01030006  /* 图像偏色 */
#define ALARM_VQ_VIDEO_BINARY               0x01030007  /* 黑白图像 */
#define ALARM_VQ_VIDEO_NOSIE                0x01030008  /* 噪声干扰 */
#define ALARM_VQ_SCREEN_FREEZE              0x01030009  /* 画面冻结 */
#define ALARM_VQ_VIDEO_STREAK               0x0103000a  /* 条纹干扰 */
#define ALARM_VQ_VIDEO_JITTER               0x0103000b  /* 视频抖动 */
#define ALARM_VQ_VIDEO_UPHEAVAL             0x0103000c  /* 视频剧变 */
#define ALARM_VQ_SCENE_CHANGE               0x0103000d  /* 场景变更 */
#define ALARM_VQ_VIDEO_COVER                0x0103000e  /* 视频遮挡 */
#define ALARM_VQ_PTZ_OUT_CONTROL            0x0103000f  /* 云台失控 */
#define ALARM_VQ_VIRTUAL_FOCUS              0x01030010  /* 虚焦 */
/* Behavior Analysis */
#define ALARM_BA_PEOPLE_TOGATHER            0x02010001  /* 人员聚集 */
#define ALARM_BA_CROSS_LINE                 0x02010016  /* 单绊线检测 */
#define ALARM_BA_LOITER                     0x02010017  /* 徘徊检测 */
#define ALARM_BA_REGION_INTRUSION           0x02010018  /* 周界入侵 */
#define ALARM_BA_THINGS_LEFT                0x02010019  /* 物品遗留 */
#define ALARM_BA_THINGS_TAKE                0x0201001a  /* 物品拿取 */
#define ALARM_BA_REGION_ENTER               0x0201001b  /* 区域进入 */
#define ALARM_BA_REGION_LEAVE               0x0201001c  /* 区域离开 */
#define ALARM_BA_RAPID_MOVE                 0x0201001d  /* 快速移动 */
#define ALARM_BA_CROSS_LINES                0x0201001e  /* 多绊线检测 */
#define ALARM_BA_FALLING_OBJECTS            0x0201001f  /* 高空抛物 */
#define ALARM_BA_PERSON_LONG_STAY           0x02010025  /* 人员停留 */
/* Target Recognition */
#define ALARM_TR_PLATE_RECOGNITION          0x02020001  /* 车牌识别 */
/* Target Detection */
#define ALARM_TD_FACE_SNAP                  0x02030005  /* 人脸抓拍 */
#define ALARM_TD_FACE_CONTRAST              0x02030006  /* 人脸比对 */
#define ALARM_TD_PEOPLE_SNAP                0x02030007  /* 人员抓拍 */
#define ALARM_TD_PEOPLE_CONTRAST            0x02030008  /* 人员比对 */
#define ALARM_TD_NONMOTOR_VEHICLE_SNAP      0x02030009  /* 非机动车抓拍 */
#define ALARM_TD_NONMOTOR_VEHICLE_CONTRAST  0x0203000a  /* 非机动车比对 */
#define ALARM_TD_MOTOR_VEHICLE_SNAP         0x0203000b  /* 机动车抓拍 */
#define ALARM_TD_MOTOR_VEHICLE_CONTRAST     0x0203000c  /* 机动车比对 */
#define ALARM_TD_PEOPLE_FOLLOW              0x02030012  /* 人员尾随 */
#define ALARM_TD_FACE_FEATURE               0x02030013  /* 人脸抓拍 特征值上报*/
/* Target Number */
#define ALARM_TN_PASSENGER_FLOW             0x02040001  /* 客流量统计 */
#define ALARM_TN_PASSENGER_DENSITY          0x02040002  /* 人员密度 */

/* Intelligent Analysis */
#define ALARM_IA_PIC_SNAP                   0x02060001  /* 通用图片抓拍 */

/* Traffic Industry */
#define ALARM_TI_TRAFFIC_STATISTICS         0x03010001  /* 车流量统计 */
#define ALARM_TN_VEHICLE_REGION_ACCESS      0x03010002  /* 机动车区域出入 */
#define ALARM_TN_VEHICLE_ACCESSCOUNT        0x03010003  /* 机动车区域过车计数 */

#define ALARM_TI_ILLEGAL_PARKING            0x03040001  /* 违法停车 */
#define ALARM_TI_INTERSECTION_CONGEST       0x03040006  /* 路口滞留 */
#define ALARM_TI_END_NUMBER_LIMIT           0x03040007  /* 尾号限行 */
#define ALARM_TI_ILLEGAL_UTURN              0x0304000a  /* 违法掉头 */
#define ALARM_TI_DISOBEY_PEDESTRIAN         0x0304000b  /* 不礼让行人 */
#define ALARM_TI_OCCUPY_EMERGENCY_LANE      0x0304000c  /* 占用应急车道 */
#define ALARM_TI_OCCUPY_NONMOTOR_LANE       0x0304000e  /* 机动车占用非机动车道 */
#define ALARM_TI_NO_TRUCK                   0x0304000f  /* 禁止货车 */
#define ALARM_TI_PEDESTRIANS_RUN_RED_LIGHT  0x03040010  /* 行人闯红灯 */
#define ALARM_TI_PRESS_LINE                 0x03040013  /* 压线 */
#define ALARM_TI_RETROGRADE                 0x03040014  /* 逆行 */
#define ALARM_TI_OCCUPY_BUS_LANE            0x03040015  /* 占用公交车道 */
#define ALARM_TI_CHANGE_LANE                0x03040016  /* 变道 */
#define ALARM_TI_DRIVING_WITHOUT_GUIDANCE   0x03040017  /* 不按导向行驶 */
#define ALARM_TI_YELLOW_PLATE_OCCUPIED_ROAD 0x03040018  /* 黄牌车占道 */
#define ALARM_TI_PRESS_YELLOW_LINE          0x03040019  /* 压黄线 */
#define ALARM_TI_CUT_IN_LINE                0x0304001a  /* 加塞 */
#define ALARM_TI_RUN_THE_RED_LIGHT          0x0304001b  /* 闯红灯 */
#define ALARM_TI_SMALL_TURN                 0x0304001c  /* 大弯小转 */
#define ALARM_TI_CROSS_LINE                 0x0304001d  /* 越线停车 */
#define ALARM_TI_LEFT_NOT_YIELD_STRAIGHT    0x0304001e  /* 左转不让直行 */
#define ALARM_TI_RIGHT_NOT_YIELD_STRAIGHT   0x0304001f  /* 右转不让直行 */
#define ALARM_TI_RIGHT_NOT_YIELD_NONMOTOR   0x03040020  /* 右转不让非机动车 */
#define ALARM_TI_ILLEGAL_REVERSING          0x03040021  /* 违法倒车 */
#define ALARM_TI_CHECK_POINT                0x03040022  /* 卡口 */
#define ALARM_TI_TRUCK_OCCUPIED_ROAD        0x03040023  /* 货车占道 */
#define ALARM_TI_FOREIGN_LICENSE_PLATE      0x03040024  /* 外地车牌 */
#define ALARM_TI_ABNORMAL_LICENSE_PLATE     0x03040025  /* 异常车牌 */
#define ALARM_TI_RIGHT_NOT_YIELD_LEFT       0x03040026  /* 右转不让左转 */
#define ALARM_TI_UTURN_NOT_YIELD_STRAIGHT   0x03040027  /* 掉头不让直行 */
#define ALARM_TI_NO_LEFT_TURN               0x03040028  /* 禁止左转 */
#define ALARM_TI_NO_RIGHT_TURN              0x03040029  /* 禁止右转 */
#define ALARM_TI_LOW_SPEED                  0x0304002a  /* 低速 */
#define ALARM_TI_OVER_SPEED                 0x0304002b  /* 超速 */
#define ALARM_TI_SUNROOF_STANDING           0x0304002c  /* 天窗站人 */
#define ALARM_TI_NONMOTOR_WITHOUT_HELMET    0x0304002d  /* 非机动车不戴安全帽 */
#define ALARM_TI_NONMOTOR_MANNED            0x0304002e  /* 非机动车载人 */
#define ALARM_TI_OCCUPY_MOTORWAY            0x0304002f  /* 非机动车占用机动车道 */
#define ALARM_TI_NONMOTOR_RETROGRADE        0x03040031  /* 非机动车逆行 */
#define ALARM_TI_RIGHT_NOT_YIELD_PEDESTRIAN 0x03040032  /* 右转不让行人 */
#define ALARM_TI_CONTINUOUS_CHANGE_LANE     0x03040033  /* 连续变道 */

/* Universal Algo Config*/
#define ALARM_UC_LOAD_UPGRADE               0x05010001  /* 算法升级或加载版本结果 */ 
#define ALARM_UC_ALGO_SWITCH                0x05010002  /* 设备算法变更 */ 
#define ALARM_UC_TABLE_RULE                 0x05010003  /* 通用化算法结果字段建表规则 */ 
#define ALARM_UC_RULE_CABILITY              0x05010004  /* 算法配置页面展示的规则项能力集上报 */ 

/* Config Notify */
#define ALARM_CN_ADD_DEVICE                 0x05020001  /* 添加设备 */
#define ALARM_CN_MODIFY_DEVICE              0x05020002  /* 修改设备 */
#define ALARM_CN_DELETE_DEVICE              0x05020003  /* 删除设备 */
#define ALARM_CN_CHANGE_PORT                0x05020005  /* 端口变更 */

/* 为防止私有帧解析时溢出 设定单个TLV最大长度为*/
#define TLV_BUFFERR_MAX_LEN                         40*1024*1024

#define AIUNITE_ALGO_ID    "_2"     /* 人脸 */
#define PERIMETER_ALGO_ID  "_14"    /* 周界 */

/* IP地址 */
typedef struct tagIDM_DEV_IP_ADDRESS
{
    CHAR    szIPv4[IDM_IPV4_ADDRESS_LEN];           /* IPv4地址 */
    CHAR    szIPv6[IDM_IPV6_ADDRESS_LEN];           /* IPv6地址 */
}IDM_DEV_IP_ADDRESS_S;

/* 设备参数信息 */
typedef struct tagIDM_DEV_DEVICE_INFO
{
    CHAR    szDeviceID[IDM_DEVICE_ID_LEN];          /* 设备ID */
    CHAR    szDeviceName[IDM_DEVICE_NAME_LEN];      /* 设备名称 */
    CHAR    szSerialNum[IDM_SERIAL_NUMBER_LEN];     /* 设备序列号 */
    CHAR    szMacAddress[IDM_MAC_ADDRESS_LEN];      /* 设备Mac地址 */
    CHAR    szIP[IDM_DEVICE_IP_MAX_LEN];            /* 设备IP地址 */
    ULONG   ulChannel;                              /* 通道号 */
    USHORT  usPort;                                 /* 端口号 */
    UCHAR   ucRemainLoginTimes;                     /* 剩余可登录次数：用户名密码错误时有效 */
    UCHAR   ucPasswordLevel;                        /* 密码安全等级：0-无效 1-默认密码 2-弱密码 3-中密码 4-强密码 */
    CHAR    szLocalIP[IDM_DEVICE_IP_MAX_LEN];       /* 本地IP地址 */
    ULONG   ulRemainLockTime;                       /* 剩余锁定时间：单位：秒，用户锁定时有效 */

	CHAR    szAuthType[32];                          /* 认证类型 当前固定为摘要认证 取Digest*/
	CHAR    szRealm[32];                             /* 领域参数 根据设备唯一序号生成 */
	CHAR    szNonce[32];                             /* 现时参数 根据事件生成 有生命周期 */

	ULONG   ulUserLoginID;                          /* 用户登录ID */
	ULONG   ulLinkSessionID;                        /* 登录主链路Session ID*/
	ULONG   ulKeepaliveIntervel;                    /* 单次心跳时间 秒*/
	ULONG   ulKeepaliveFailedTimes;                 /* 连续心跳失败次数 达到次数认为离线需要重新登录 */
	CHAR    szUserAuth[1024];                       /* 用户权限 多元素英文逗号组合而成 每个元素最大8字节 最多128个元素*/
	CHAR    szPlayBackAuthChannels[512];                 /* 用户回放通道级权限 0-1组成 0无权限 1有权限*/
	CHAR    szPreviewAuthChannels[512];                  /* 用户实况通道级权限 0-1组成 0无权限 1有权限*/
	UCHAR   ucUserLockStatus;                       /* 用户锁定状态 失败时有效 0-未锁定 1-锁定*/
	UCHAR   aucRes[236];
}IDM_DEV_DEVICE_INFO_S;

/* 报警设备参数信息 */
typedef struct tagIDM_DEV_ALARM_DEVICE_INFO
{
    CHAR    szDeviceID[IDM_DEVICE_ID_LEN];          /* 设备ID */
    CHAR    szDeviceName[IDM_DEVICE_NAME_LEN];      /* 设备名称 */
    CHAR    szSerialNum[IDM_SERIAL_NUMBER_LEN];     /* 设备序列号 */
    CHAR    szMacAddress[IDM_MAC_ADDRESS_LEN];      /* 设备Mac地址 */
    CHAR    szIP[IDM_DEVICE_IP_MAX_LEN];            /* 设备IP地址 */
    ULONG   ulChannel;                              /* 通道号 */
    USHORT  usPort;                                 /* 端口号 */
	UCHAR   usUnuse[2];                             /* 预留2字节 */
	CHAR    szChannelName[128];                     /* 通道名称 */
	CHAR    szChannelID[64];                        /* 通道ID编码 */
    CHAR    szDevVersion[64];                       /* 设备版本 */
}IDM_DEV_ALARM_DEVICE_INFO_S;

typedef struct tagIDM_DEV_GB28181_INFO
{
    CHAR    szDeviceRegID[IDM_DEVICE_ID_LEN];
    UCHAR   aucRes[32];
}IDM_DEV_GB28181_INFO_S;

typedef struct tagIDM_DEV_STREAM_URL
{
    CHAR    szRtspUrl[IDM_RTSPURL_MAX_LEN];       /* 主码流 */
    CHAR    szSubRtspUrl[IDM_RTSPURL_MAX_LEN];    /* 子码流 */
    UCHAR   aucRes[32];
}IDM_DEV_STREAM_URL_S;

typedef struct tagIDM_DEV_IPPARACFG
{
    ULONG   ulEnable;                               /* 设备是否启用，不支持设置由设备返回 0:未启用，其他:启用*/
    CHAR    szDeviceID[IDM_DEVICE_ID_LEN];          /* 设备ID，不支持设置由设备返回 */
    CHAR    szDeviceName[IDM_DEVICE_NAME_LEN];      /* 设备名称 */
    CHAR    szDeviceIP[IDM_DEVICE_IP_MAX_LEN];      /* 设备IP地址 */
    CHAR    szDeviceModel[IDM_DEVICE_MODEL_LEN];    /* 设备型号，不支持设置由设备返回*/
    USHORT  usPort;                                 /* 设备端口号 */
    UCHAR   ucProtocol;                             /* 设备接入类型:0：ONVIF,1：GB/T28181,2：SDK,3：RTSP协议*/
    UCHAR   ucOnline;                               /* 设备是否在线:0:离线，1:在线，不支持设置由设备返回*/
    CHAR    szUsername[IDM_USERNAME_MAX_LEN];       /* 登录用户名 */
    CHAR    szPassword[IDM_PASSWORD_MAX_LEN];       /* 登录密码 */
    USHORT  usChannelSize;                          /* 设备通道总数，最大256*/
    USHORT  usChannelNum;                           /* 添加的设备通道数，最大256*/
    UCHAR   szChannelEnable[32];                    /* 设备接入通道使能，按位定义,0:不使能,1:使能*/
    UCHAR   szLocalChanNo[256];                     /* 对应本地通道号*/
    UCHAR   szLocalChanOnline[32];                  /* 对应本地通道在线状态，按位定义,0:不在线,1:在线*/
	UCHAR   ucIsAddAllChannels;                     /* 是否添加所有获取到的通道 false受用户指定限制 true后台添加所有获取到的通道 默认为false*/
	CHAR   *szMultiDeviceID;                        /* 内存用户自行管理 删除多设备时传入以,分割的设备ID构成的字符串 如"id1,id2"*/
	USHORT usHttpPort;								/* http访问端口*/
	USHORT usHttpsPort;								/* https访问端口*/
	USHORT usRtspPort;								/* rtsp端口 */
	UCHAR   aucRes[21];
    union
    {
        IDM_DEV_GB28181_INFO_S stGB28181Info;       /* 设备登录ID,GB/T28181使用 */
        IDM_DEV_STREAM_URL_S  stStreamUrl;          /* Rtsp URL */
    };
}IDM_DEV_IPPARACFG_S;

typedef struct tagIDM_DEV_QUEIPPARACFG
{
    ULONG ulDevNum;                                 /* 有效的设备数 */
    IDM_DEV_IPPARACFG_S* pstIPCfg;                  /* 设备列表信息数组指针，固定256个数组，内存由用户申请 */
}IDM_DEV_QUEIPPARACFG_S;

#if 0
/* 系统参数配置结构体 */
#endif
/* 时间参数 */
typedef struct tagIDM_DEV_TIME_PARAM
{
    USHORT  usYear;                                 /* 年 */
    USHORT  usMonth;                                /* 月 */
    USHORT  usDay;                                  /* 日 */
    USHORT  usHour;                                 /* 时 */
    USHORT  usMinute;                               /* 分 */
    USHORT  usSecond;                               /* 秒 */
}IDM_DEV_TIME_PARAM_S;

typedef struct tagIDM_DEV_TIMESPAN_PARAM
{
    USHORT  usHour;                                 /* 时 */
    USHORT  usMinute;                               /* 分 */
    USHORT  usSecond;                               /* 秒 */
    UCHAR   aucRes[2];
}IDM_DEV_TIMESPAN_PARAM_S;

/* 设备系统信息 */
typedef struct tagIDM_DEV_SYSTEM_INFO
{
    CHAR    szDeviceModel[64];                      /* 设备型号 */
    CHAR    szSerialNum[64];                        /* 设备序列号 */
    CHAR    szAuthCode[32];                         /* 设备验证码 */
    CHAR    szMacAddress[32];                       /* 设备Mac地址 */
    CHAR    szSoftwareVersion[64];                  /* 软件版本号 */
    IDM_DEV_TIME_PARAM_S    stSoftwareTime;         /* 软件生成时间 */
    USHORT  usDeviceClass;                          /* 设备类别：0：IPC高清网络摄像机 1:ITC智能交通摄像机 100:IVR智能网络硬盘录像机 101:NVR网络硬盘录像机 */
    USHORT  usDigitalChannelNum;                    /* 数字通道个数 */
    UCHAR   ucAnalogChannelNum;                     /* 模拟通道个数 */
    UCHAR   ucDiskNum;                              /* 硬盘个数 */
    USHORT  usHttpPort;                             /* HTTP端口号，默认80 */
    USHORT  usHttpsPort;                            /* HTTPS端口号，默认443 */
    USHORT  usRtspPort;                             /* RTSP端口号，默认554 */
    USHORT  usSdkPort;                              /* SDK端口号 */
    UCHAR   ucAlarmInNum;                           /* 报警输入个数 */
    UCHAR   ucAlarmOutNum;                          /* 报警输出个数 */
    UCHAR   aucRes[240];
}IDM_DEV_SYSTEM_INFO_S;
#if 0
/* 通道参数配置结构体 */
#endif
/* 视频编码参数 */
typedef struct tagIDM_DEV_VIDEO_ENCODE_PARAM
{
    UCHAR   ucStreamType;                           /* 码流类型：0-主码流 1-子码流 2-三码流 */
    UCHAR   ucVideoType;                            /* 视频类型：0-视频流 1-复合流 */
    UCHAR   ucEncodeType;                           /* 视频编码类型： 0-MPEG2 1--MJPEG 2-H264 3-H265 4-MPEG4 */
    UCHAR   ucEncodeLevel;                          /* 编码等级(复杂度)：0-低 1-中 2-高 */
    UCHAR   ucSmartEncode;                          /* 是否启用智能编码：0-否 1-是 */
    UCHAR   ucQuality;                              /* 图像质量：0-低 1-中 2-高 */
    UCHAR   ucBitrateType;                          /* 码率类型：0-定码率 1-变码率 */
    UCHAR   ucSmoothing;                            /* 码流平滑：[1,100] */
    USHORT  usIFrameInterval;                       /* I帧间隔：[1,400] */
    USHORT  usResolution;                           /* 视频分辨率：
                                                     * 0-D1(704*576)
                                                     * 1-CIF(352*288/352*240)
                                                     * 2-QCIF(176*144/176*120)
                                                     * 3-DCIF(528*384/528*320)
                                                     * 4-2CIF(704*288/704*240)
                                                     * 5-VGA(640*780)
                                                     * 6-SVGA(800*600)
                                                     * 7-XVGA(1280*960)
                                                     * 8-QVGA(320*240)
                                                     * 9-720P(1280*720)
                                                     * 10-1080P(1920*1080)
                                                     * 11-QQVGA(160*120)
                                                     * 12-XGA(1024*768)
                                                     * 13-SXGA(1280*1024)
                                                     * 14-QSXGA(2560*2048)
                                                     * 15-HSXGA(5120*4096)
                                                     * 16-UXGA(1600*1200)
                                                     * 17-QUXGA(3200*2400)
                                                     * 18-1.3M(1280*960)
                                                     * 19-HXGA(4096*3072)
                                                     * 20-HUXGA(6400*4800)
                                                     * 21-WXGA(1280*800)
                                                     * 22-WXGA+(1440*900)
                                                     * 23-WSXGA+(1680*1050)
                                                     * 24-WUXGA(1920*1200)
                                                     * 25-WQXGA(2560*1600)
                                                     * 26-2160P(3840*2160)
                                                     * 27-900P(1600*900)
                                                     * 28-1440P(2560*1440)
                                                     * 29-WQUXGA(3840*2400)
                                                     * 30-4320P(7680*4320) */
    USHORT  usFrameRate;                            /* 视频帧率(fps)*/
    USHORT  usBitrate;                              /* 视频码率*/
    UCHAR   aucRes[16];
}IDM_DEV_VIDEO_ENCODE_PARAM_S;

/* 音频编码参数 */
typedef struct tagIDM_DEV_AUDIO_ENCODE_PARAM
{
    UCHAR   ucStreamType;                           /* 码流类型：0-主码流 1-子码流 2-三码流 */
    UCHAR   ucEncodeType;                           /* 音频编码类型：1-ADPCM 2-G722 3-G.711U 4-G711.A 5-G.726 6-AAC 7-MP2L2 8-PCM 9-G722.1 */
    UCHAR   ucBitrate;                              /* 音频码率：1-5.3Kbps 2-6.3Kbps 3-8Kbps 4-24Kbps 5-40Kbps 6-48Kbps 7-56Kbps 8-64Kbps 9-80Kbps 10-96Kbps 11-112Kbps 12-144Kbps 13-160Kbps 14-192Kbps 15-224Kbps 16-256Kbps 17-320Kbps 18-384Kbps */
    UCHAR   ucSamplingRate;                         /* 音频采样率：1-4KHz 2-8KHz 3-11.025KHz 4-16KHz 5-20KHz 6-22.05KHz 7-32KHz 8-32KHz 9-48KHz 10-64KHz 11-96KHz 12-128KHz 13-192KHz */
    UCHAR   ucAudioInType;                          /* 音频输入类型：1-MicIn 2-LineIn */
    UCHAR   ucAudioInVolume;                        /* 音频输入音量：[0,100] */
    UCHAR   ucAudioOutVolume;                       /* 音频输出音量：[0,100] */
    UCHAR   ucNoiseReduce;                          /* 是否开启环境噪声过滤：0-关闭 1-开启 */
    UCHAR   aucRes[16];
}IDM_DEV_AUDIO_ENCODE_PARAM_S;

/* 码流参数 */
typedef struct tagIDM_DEV_STREAM_PARAM
{
    IDM_DEV_VIDEO_ENCODE_PARAM_S stVideoEncode;     /* 视频编码参数 */
    IDM_DEV_AUDIO_ENCODE_PARAM_S stAudioEncode;     /* 音频编码参数 */
}IDM_DEV_STREAM_PARAM_S;

/* RGB参数 */
typedef struct tagIDM_DEV_RGB_PARAM
{
    UCHAR ucRed;                                    /* R：[0,255] */
    UCHAR ucGreen;                                  /* G：[0,255] */
    UCHAR ucBlue;                                   /* B：[0,255] */
    UCHAR ucRes;
}IDM_DEV_RGB_PARAM_S;

/* OSD叠加项参数 V1*/
typedef struct tagIDM_DEV_OSD_ITEMS_PARAM
{
    USHORT usX;                                     /* 字符叠加项左上角坐标X：[0,10000] */
    USHORT usY;                                     /* 字符叠加项左上角坐标Y：[0,10000] */
    CHAR szContent[64];                             /* 字符叠加内容 */
    UCHAR ucShow;                                   /* 是否显示字符叠加项 */
    UCHAR aucRes[3];
}IDM_DEV_OSD_ITEMS_PARAM_S;

/* 视频OSD参数 V1*/
typedef struct tagIDM_DEV_VIDEO_OSD_PARAM
{
    UCHAR ucOsdAlign;                               /* OSD对齐方式：0-自适应 1-左对齐 2-右对齐 */
    UCHAR ucOsdAttribute;                           /* OSD属性：0-透明+闪烁 1-透明+不闪烁 2-不透明+闪烁 3-不透明+不闪烁 */
    UCHAR ucFontSize;                               /* OSD字体大小：0-16x16 1-32x32 2-48x48 3-64x64 */
    UCHAR ucColorType;                              /* OSD字体颜色类型：0-黑白 1-自定义 */
    IDM_DEV_RGB_PARAM_S stColor;                    /* OSD字体自定义颜色 */
    UCHAR ucShowDate;                               /* 是否显示日期：0-否 1-是 */
    UCHAR ucShowWeek;                               /* 是否显示星期：0-否 1-是 */
    UCHAR ucTimeFormat;                             /* 时间格式：0-12小时制 1-24小时制 */
    UCHAR ucDateFormat;                             /* 日期格式：0-XXXX-XX-XX年月日 1-XX-XX-XXXX月日年 2-XX-XX-XXXX日月年 */
    USHORT usTimeX;                                 /* 时间日期左上角坐标X：[0,10000] */
    USHORT usTimeY;                                 /* 时间日期左上角坐标Y：[0,10000] */
    UCHAR ucShowChannelName;                        /* 是否显示通道名称：0-否 1-是 */
    UCHAR ucRes;
    CHAR szChannelName[64];                         /* 通道名称 */
    USHORT usChannelNameX;                          /* 通道名称左上角坐标X：[0,10000] */
    USHORT usChannelNameY;                          /* 通道名称左上角坐标Y：[0,10000] */
    IDM_DEV_OSD_ITEMS_PARAM_S astOsdItems[8];       /* 字符叠加项 */
    UCHAR aucRes[128];
}IDM_DEV_VIDEO_OSD_PARAM_S;

/* OSD叠加项参数 V2*/
typedef struct tagIDM_DEV_OSD_ITEMS_PARAM_V2
{
	USHORT usX;                                     /* 字符叠加项左上角坐标X：[0,10000] */
	USHORT usY;                                     /* 字符叠加项左上角坐标Y：[0,10000] */
	UCHAR  ucShow;                                   /* 是否显示字符叠加项 */
	CHAR   szContent[128];                             /* 字符叠加内容 和V1主要差距*/
	UCHAR aucRes[32];
}IDM_DEV_OSD_ITEMS_PARAM_S_V2;

/* 视频OSD参数 V2*/
typedef struct tagIDM_DEV_VIDEO_OSD_PARAM_V2
{
	UCHAR ucOsdAlign;                               /* OSD对齐方式：0-自适应 1-左对齐 2-右对齐 */
	UCHAR ucOsdAttribute;                           /* OSD属性：0-透明+闪烁 1-透明+不闪烁 2-不透明+闪烁 3-不透明+不闪烁 */
	UCHAR ucFontSize;                               /* OSD字体大小：0-16x16 1-32x32 2-48x48 3-64x64 */
	UCHAR ucColorType;                              /* OSD字体颜色类型：0-黑白 1-自定义 */
	IDM_DEV_RGB_PARAM_S stColor;                    /* OSD字体自定义颜色 */
	UCHAR ucShowDate;                               /* 是否显示日期：0-否 1-是 */
	UCHAR ucShowWeek;                               /* 是否显示星期：0-否 1-是 */
	UCHAR ucTimeFormat;                             /* 时间格式：0-12小时制 1-24小时制 */
	UCHAR ucDateFormat;                             /* 日期格式：0-XXXX-XX-XX年月日 1-XX-XX-XXXX月日年 2-XX-XX-XXXX日月年 */
	USHORT usTimeX;                                 /* 时间日期左上角坐标X：[0,10000] */
	USHORT usTimeY;                                 /* 时间日期左上角坐标Y：[0,10000] */
	UCHAR ucShowChannelName;                        /* 是否显示通道名称：0-否 1-是 */
	UCHAR ucRes;
	USHORT usChannelNameX;                          /* 通道名称左上角坐标X：[0,10000] */
	USHORT usChannelNameY;                          /* 通道名称左上角坐标Y：[0,10000] */
	CHAR szChannelName[128];                        /* 通道名称 */
	UCHAR aucRes[128];
	IDM_DEV_OSD_ITEMS_PARAM_S_V2 astOsdItems[8];       /* 字符叠加项 */
}IDM_DEV_VIDEO_OSD_PARAM_S_V2;


#if 0
/* 网络参数配置结构体 */
#endif

/* 以太网卡参数 */
typedef struct tagIDM_DEV_ETHERNET_PARAM
{
    ULONG   ulEthernetNo;                           /* 网卡编号 */
    CHAR    szEthernetName[32];                     /* 网卡名称 */
    ULONG   ulType;                                 /* 网卡类型：0-自适应 1-10M半双工 2-10M全双工 3-100M半双工 4-100M全双工 5-1000M全双工 */
    LONG    lDhcpEnable;                            /* 是否启用DHCP：0-否 1-是 */
    ULONG   ulIPv6Mode;                             /* IPv6地址分配方式：0-自动获取 1-手动配置 2-路由公告*/
    ULONG   ulMtu;                                  /* MTU */
    CHAR    szMacAdderss[IDM_MAC_ADDRESS_LEN];      /* MAC地址 */
    IDM_DEV_IP_ADDRESS_S  stIP;                     /* IP地址 */
    IDM_DEV_IP_ADDRESS_S  stSubnetMask;             /* 子网掩码 */
    IDM_DEV_IP_ADDRESS_S  stGateway;                /* 网关 */
    IDM_DEV_IP_ADDRESS_S  stMulticast;              /* 组播地址 */
    ULONG   ulDnsMode;                              /* DNS分配方式：0-自动获取 1-手动配置 */
    IDM_DEV_IP_ADDRESS_S  stPreferredDns;           /* 首选DNS */
    IDM_DEV_IP_ADDRESS_S  stStandbyDns;             /* 备用DNS */
    UCHAR   aucRes[256];
}IDM_DEV_ETHERNET_PARAM_S;

/* Bonding网卡参数 */
typedef struct tagIDM_DEV_BONDING_PARAM
{
    ULONG   ulWorkMode;                             /* 工作模式：0-负载均衡 1-网络容错 */
    UCHAR   aucBonding[16];                         /* 虚拟网卡绑定的物理网卡，下标为网卡编号，值为0-不使用 1-使用 */
    IDM_DEV_ETHERNET_PARAM_S stEthernet;
    UCHAR   aucRes[64];
}IDM_DEV_BONDING_PARAM_S;

/* 网络参数 */
typedef struct tagIDM_DEV_NET_PARAM
{
    LONG    lBondingEnable;                         /* 是否启用Bonding：0-否 1-是 */
    ULONG   ulDefaultEthernetNo;                    /* 默认网卡编号 */
    ULONG   ulBondingNumber;                        /* Bonding网卡数 */
    ULONG   ulEthernetNumber;                       /* 以太网卡数 */
    IDM_DEV_BONDING_PARAM_S  astBonding[2];         /* Bonding网卡参数 */
    IDM_DEV_ETHERNET_PARAM_S astEthernet[4];        /* 以太网卡参数 */
    USHORT  ausRes[256];
}IDM_DEV_NET_PARAM_S;

/* UPnP端口映射参数 */
typedef struct tagIDM_DEV_UPNP_PORT
{
    LONG    lEnable;                                /* 是否启用：0-否 1-是 */
    USHORT  usPort;                                 /* 映射的外部端口号 */
    USHORT  usRes;
}IDM_DEV_UPNP_PORT_S;

/* UPnP参数 */
typedef struct tagIDM_DEV_UPNP_PARAM
{
    LONG    lUpnpEnable;                            /* 是否启用UPnP：0-否 1-是 */
    ULONG   ulUpnpMode;                             /* 端口映射方式：0-自动 1-手动 */
    IDM_DEV_UPNP_PORT_S astUpnpPort[32];            /* 端口映射：0-HTTP 1-HTTPS 2-RTSP 3-SDK */
}IDM_DEV_UPNP_PARAM_S;

/* NTP参数 */
typedef struct tagIDM_DEV_NTP_PARAM
{
    LONG    lEnable;                                /* 是否启用：0-否 1-是 */
    CHAR    szNtpServer[IDM_DOMAIN_NAME_LEN];       /* NTP服务器IP/域名 */
    USHORT  usNtpPort;                              /* NTP服务器端口 */
    USHORT  usInterval;                             /* 更新周期：[1,10080], 默认1440 */
}IDM_DEV_NTP_PARAM_S;

/* PPPOE参数 */
typedef struct tagIDM_DEV_PPPOE_PARAM
{
    LONG    lEnable;                                /* 是否启用：0-否 1-是 */
    CHAR    szUsername[IDM_USERNAME_MAX_LEN];       /* 用户名 */
    CHAR    szPassword[IDM_PASSWORD_MAX_LEN];       /* 密码 */
    IDM_DEV_IP_ADDRESS_S stIPAddress;               /* IP */
}IDM_DEV_PPPOE_PARAM_S;

/* DDNS参数 */
typedef struct tagIDM_DEV_DDNS_PARAM
{
    LONG    lEnable;                                /* 是否启用：0-否 1-是 */
    ULONG   ulType;                                 /* 类型：0-DynDNS(暂不支持) 1-NO-IP */
    CHAR    szServerName[IDM_DOMAIN_NAME_LEN];      /* DDNS服务器IP/域名 */
    CHAR    szDomainName[IDM_DOMAIN_NAME_LEN];      /* 域名 */
    USHORT  usPort;                                 /* DDNS端口号 */
    USHORT  usRes;
    CHAR    szUsername[IDM_USERNAME_MAX_LEN];       /* 用户名 */
    CHAR    szPassword[IDM_PASSWORD_MAX_LEN];       /* 密码 */
}IDM_DEV_DDNS_PARAM_S;

/* REST API 透传请求参数 */
typedef struct tagIDM_DEV_REQUEST_PARAM
{
    CHAR    *pcUrl;                                 /* 请求URL,例： GET /api/esp/network/ddns */
    ULONG   ulUrlLen;                               /* 请求URL长度 */
    CHAR    *pcBuffer;                              /* 输入缓冲区(JSON格式)，即HTTP Body */
    ULONG   ulBufferSize;                           /* 输入缓冲区大小 */
    ULONG   ulTimeout;                              /* 超时时间：单位：ms，默认5s */
}IDM_DEV_REQUEST_PARAM_S;

/* REST API 透传响应参数 */
typedef struct tagIDM_DEV_RESPONSE_PARAM
{
    CHAR    *pcBuffer;                              /* 输出缓冲区(JSON格式)，即HTTP Body */
    ULONG   ulBufferSize;                           /* 输出缓冲区大小 */
    ULONG   ulReturnSize;                           /* 实际输出的JSON长度 */
}IDM_DEV_RESPONSE_PARAM_S;

#if 0
/* 云台配置结构体 */
#endif
/* 预置位信息结构体 */
typedef struct tagIDM_DEV_PRESET_NAME
{
    USHORT  usPresetNum;                            /*  预置点编号 */
    USHORT  usStatus;                               /*  预置位状态(只读)：1-已定义，2-未定义，3-特殊预置位 */
    CHAR    szName[64];                             /*  预置位名称 */
    UCHAR   aucRes[64];
}IDM_DEV_PRESET_NAME_S;

/*巡航路径预置位列表结构体*/
typedef struct tagIDM_DEV_PRESET_LIST
{
    USHORT    usPresetNum;                          /* 预置点编号 */
    USHORT    usDelayTime;                          /* 延时时间：5~120 */
    USHORT    usSpeed;                              /* 速度：1~40 */
    UCHAR     aucRes[2];
}IDM_DEV_PRESET_LIST_S;

/*巡航路径信息结构体*/
typedef struct tagIDM_DEV_CRUISE_INFO
{
    USHORT  usCruiseNum;                            /* 巡航路径编号 */
    USHORT  usEnable;                               /* 是否启用：0-否，1-是 */
    ULONG   ulPresetCount;                          /* 设置预置位个数 */
    IDM_DEV_PRESET_LIST_S stPresetList[256];
}IDM_DEV_CRUISE_INFO_S;

typedef struct tagIDM_DEV_WATCH_INFO
{
    USHORT  usEnable;                               /* 是否启用：0-否，1-是 */
    USHORT  usActionType;                           /* 守望动作类型：0-巡航扫描 1-花样扫描 2-预置点 3-帧扫描 4-自动扫描 5-随机扫描 6-全景扫描 7-垂直扫描 */
    USHORT  usActionID;                             /* 守望动作对应的ID：巡航扫描、花样扫描、预置点ID */
    USHORT  usWaitTime;                             /* 守望等待时间：5~720秒 */
    UCHAR   aucRes[32];
}IDM_DEV_WATCH_INFO_S;

#if 0
/* 智能参数配置结构体 */
#endif
/* 名单库信息结构体 */
typedef struct tagIDM_DEV_REPOSITORY_INFO
{
    ULONG   ulRepoID;                               /*  名单库ID */
    CHAR    szCreaterName[64];                      /*  名单库创建者名 */
    CHAR    szRepoName[64];                         /*  名单库名称 */
    CHAR    szRepoDesc[256];                        /*  名单库描述 */
    FLOAT   fThreshold;                             /*  灵敏度阈值 */
    CHAR    szCreateTime[64];                       /*  创建时间(不可设置) */
    CHAR    szUpdateTime[64];                       /*  修改时间(不可设置) */
}IDM_DEV_REPOSITORY_INFO_S;

/* 名单库删除结构体 */
typedef struct tagIDM_DEV_REPOSITORY_DELETE
{
    ULONG   ulRepoID;                               /* 名单库ID */
}IDM_DEV_REPOSITORY_DELETE_S;

/* 打开名单库结构体 */
typedef struct tagIDM_DEV_REPOSITORY_OPEN
{
    LONG    lUserID;                                /* 设备登录句柄 */
    ULONG   ulRepoID;                               /* 名单库ID */
}IDM_DEV_REPOSITORY_OPEN_S;

/* 关闭名单库结构体 */
typedef struct tagIDM_DEV_REPOSITORY_CLOSE
{
    ULONG   ulRepoHandle;                           /* 打开的名单库句柄 */
}IDM_DEV_REPOSITORY_CLOSE_S;

/* 创建建模任务结构体 */
typedef struct tagIDM_DEV_REPOSITORY_CREATEMODEL
{
    ULONG   ulRepoID;                               /* 名单库ID */
    ULONG   ulRange;                                /* 建模范围 1-全部建模，2-全部未建模，3-指定ID建模 */
    ULONG   ulFaceID[1024];                         /* 人脸ID */
    ULONG   ulFaceNum;
}IDM_DEV_REPOSITORY_CREATEMODEL_S;

/* 查询建模任务结构体 */
typedef struct tagIDM_DEV_REPOSITORY_QUERYMODEL
{
    ULONG   ulModelingID;                           /* 建模任务ID */
}IDM_DEV_REPOSITORY_QUERYMODEL_S;

/* 查询建模任务结构体 */
typedef struct tagIDM_DEV_REPOSITORY_QUERYMODEL_RESULT
{
    ULONG   ulTotalNum;                             /* 总数 */
    ULONG   ulSuccedNum;                            /* 成功数 */
    ULONG   ulFailedNum;                            /* 失败数 */
}IDM_DEV_REPOSITORY_QUERYMODEL_RESULT_S;

/* 名单库查询条件结构体 */
typedef struct tagIDM_DEV_REPOSITORY_QUERYCOND
{
    ULONG   ulRepoID;                               /* 名单库ID，填0时不作为搜索条件 */
    CHAR    szCreaterName[64];                      /* 名单库创建者名 */
    CHAR    szRepoName[64];                         /* 名单库名称 */
    ULONG   ulPageNo;                               /* 搜索当前页 */
}IDM_DEV_REPOSITORY_QUERYCOND_S;

/* 名单库查询结果结构体 */
typedef struct tagIDM_DEV_REPOSITORY_QUERYRESULT
{
    ULONG   ulResultNum;                            /* 查询结果数 */
    ULONG   ulTotalNum;                             /* 总数 */
    ULONG   ulPageNo;                               /* 当前页码 */
    IDM_DEV_REPOSITORY_INFO_S stResult[10];         /* 查询结果，最大10个 */
}IDM_DEV_REPOSITORY_QUERYRESULT_S;

/* 名单库操作输入参数结构体 */
typedef struct tagIDM_DEV_REPOSITORY_OPT_PARAM
{
    ULONG   ulParamType;                            /* 操作类型：1-创建名单库 2-名单库设置 3-名单库删除 4-名单库查询 5-加载名单库 6-释放名单库 7-名单库建模任务 8-查询建模进度 */
    union
    {
        IDM_DEV_REPOSITORY_INFO_S stCreatRepo;      /* 创建名单库结构体 */
        IDM_DEV_REPOSITORY_INFO_S stModifyRepo;     /* 设置名单库结构体 */
        IDM_DEV_REPOSITORY_DELETE_S stDeleteRepo;   /* 删除名单库结构体 */
        IDM_DEV_REPOSITORY_QUERYCOND_S stQueryRepo; /* 查询名单库结构体 */
        IDM_DEV_REPOSITORY_OPEN_S stOpenRepo;       /* 打开名单库结构体 */
        IDM_DEV_REPOSITORY_CLOSE_S stCloseRepo;     /* 关闭名单库结构体 */
        IDM_DEV_REPOSITORY_CREATEMODEL_S stCreateModel; /* 创建建模任务结构体 */
        IDM_DEV_REPOSITORY_QUERYMODEL_S stQueryModel;   /* 查询建模进度结构体 */
    };
}IDM_DEV_REPOSITORY_OPT_PARAM_S;

/* 名单库操作输出参数结构体 */
typedef struct tagIDM_DEV_REPOSITORY_OPT_PARAMOUT
{
    ULONG   ulParamType;                            /* 操作类型：1-创建名单库 2-名单库设置 3-名单库删除 4-名单库查询 5-加载名单库 6-释放名单库 7-名单库建模任务 8-查询建模进度 */
    union
    {
        ULONG   ulCreatRepoID;                      /* 创建的名单库ID */
        ULONG   ulModifyRepoID;                     /* 修改的名单库ID */
        ULONG   ulDeleteRepoID;                     /* 删除的名单库ID */
        IDM_DEV_REPOSITORY_QUERYRESULT_S stQueryRepo; /* 名单库查询结果 */
        ULONG   ulOpenRepoHandle;                   /* 打开名单库句柄 */
        ULONG   ulReleaseRepoHandle;                /* 关闭名单库句柄 */
        ULONG   ulModelingID;                       /* 创建的建模任务ID */
        IDM_DEV_REPOSITORY_QUERYMODEL_RESULT_S stQueryModel; /* 建模任务查询结果 */
    };
}IDM_DEV_REPOSITORY_OPT_PARAMOUT_S;

/* 名单库人物信息结构体 */
typedef struct tagIDM_REPOSITORY_PERSON_INFO
{
    CHAR    szName[64];                             /* 姓名 */
    ULONG   ulgender;                               /* 性别 */
    ULONG   ulIDType;                               /* 证件类型 */
    CHAR    szIDNumber[64];                         /* 证件号 */
    CHAR    szBirthday[32];                         /* 生日 */
    ULONG   ulNation;                               /* 民族 */
    ULONG   ulProvince;                             /* 省份 */
    ULONG   ulCity;                                 /* 城市 */
    ULONG   ulCounty;                               /* 国家 */
    CHAR    szDesc[256];                            /* 描述 */
    CHAR    szPicName[256];                         /* 图片名 */
    CHAR    szPicFormat[8];                         /* 图片格式 */
    CHAR    *pImage;                                /* 图片数据指针 */
    ULONG   ulImageLenth;                           /* 图片长度 */
}IDM_REPOSITORY_PERSON_INFO_S;

/* 名单库人物导入结构体 */
typedef struct tagIDM_REPOSITORY_HUMAN_IMPORT
{
    USHORT  usImportType;                           /* 导入类型 */
    USHORT  usPersonCount;                          /* 导入数量 */
    IDM_REPOSITORY_PERSON_INFO_S stPersonList[10];  /* 导入属性 */
}IDM_REPOSITORY_HUMAN_IMPORT_S;

/* 名单库人物属性修改结构体 */
typedef struct tagIDM_REPOSITORY_HUMAN_MODIFY
{
    ULONG   ulRecordID;                             /* 修改目标的ID */
    IDM_REPOSITORY_PERSON_INFO_S stPersonInfo;      /* 修改属性 */
}IDM_REPOSITORY_HUMAN_MODIFY_S;

/* 名单库人物删除结构体 */
typedef struct tagIDM_REPOSITORY_HUMAN_DELETE
{
    ULONG   ulRecordID[20];                         /* 删除目标的ID数组 */
    ULONG   ulPersonCount;                          /* 删除数量 */
}IDM_REPOSITORY_HUMAN_DELETE_S;

/* 筛选条件结构体 */
typedef struct tagIDM_REPOSITORY_QUERY_CONDITION
{
    CHAR    szKey[128];                             /* 条件字段 */
    CHAR    szValue[256];                           /* 条件参数 */
    ULONG   ulOperator;                             /* 条件操作符 */
}IDM_REPOSITORY_HUMAN_CONDITION_S;

/* 排序条件结构体 */
typedef struct tagIDM_REPOSITORY_QUERY_ORDER
{
    ULONG   ulOrder;                                /* 排序方向 */
    CHAR    szKey[128];                             /* 排序字段 */
}IDM_REPOSITORY_HUMAN_ORDER_S;

/* 名单库人物查询结构体 */
typedef struct tagIDM_REPOSITORY_HUMAN_QUERY
{
    ULONG   ulPageNo;                               /* 查询结果页号 */
    ULONG   ulPageSize;                             /* 每页最大条目 */
    ULONG   ulCondLogic;                            /* 条件间的逻辑关系 */
    USHORT  usCondNum;                              /* 筛选条件数量 */
    USHORT  usOrderNum;                             /* 结果排序条件 */
    ULONG   ulRecordNum;                            /* 人脸ID列表数量，最大50 */
    ULONG   ulRecordID[50];                         /* 人脸ID列表 */
    IDM_REPOSITORY_HUMAN_CONDITION_S stConds[16];   /* 筛选条件，最大16个 */
    IDM_REPOSITORY_HUMAN_ORDER_S stOrder[3];        /* 结果排序方式，最大3个 */
}IDM_REPOSITORY_HUMAN_QUERY_S;

/* 名单库内容操作结构体 */
typedef struct tagIDM_REPOSITORY_CONTROL_PARAM
{
    ULONG   ulParamType;                            /* 操作类型：1-导入人脸记录 2-修改名单库中人脸记录 3-查询名单库中人脸记录 4-删除名单库中人脸记录 */
    union
    {
        IDM_REPOSITORY_HUMAN_IMPORT_S stImport;     /* 名单库人物导入结构体 */
        IDM_REPOSITORY_HUMAN_MODIFY_S stModify;     /* 名单库人物属性修改结构体 */
        IDM_REPOSITORY_HUMAN_DELETE_S stDelete;     /* 名单库人物删除结构体 */
        IDM_REPOSITORY_HUMAN_QUERY_S  stQuery;      /* 名单库人物查询结构体 */
    };
}IDM_REPOSITORY_CONTROL_PARAM_S;

/* 名单库内容操作结构体 */
typedef struct tagIDM_REPOSITORY_CONTROL_RESULT
{
    ULONG   ulParamType;                            /* 操作类型：1-导入人脸记录 2-修改名单库中人脸记录 3-查询名单库中人脸记录 4-删除名单库中人脸记录 */
    CHAR    *pszResult;                             /* 操作结果返回的JSON格式字符串 */
    ULONG   ulResultSize;                           /* 字符串长度 */
}IDM_REPOSITORY_CONTROL_RESULT_S;

#if 0
/* 异常消息 */
#endif
/* 异常消息回调函数 */
typedef VOID(CALLBACK *IDM_DEV_Exception_Callback_PF)(
    LONG    lUserID,
    LONG    lHandle,
    ULONG   ulType,
    VOID    *pUserData
    );

#if 0
/* 设备登录 */
#endif
/* 异步登录回调函数 */
typedef VOID(CALLBACK *IDM_DEV_Login_Callback_PF)(
    LONG    lUserID,
    LONG    lResult,
    IDM_DEV_DEVICE_INFO_S *pstDeviceInfo,
    VOID    *pUserData
    );

/* 登录结构体 */
typedef struct tagIDM_DEV_USER_LOGIN_INFO
{
    CHAR    szDeviceIP[IDM_DEVICE_IP_MAX_LEN];      /* 设备IP地址 */
    USHORT  usPort;                                 /* 设备端口号 */
    USHORT  usRes;
    CHAR    szUsername[IDM_USERNAME_MAX_LEN];       /* 登录用户名 */
    CHAR    szPassword[IDM_PASSWORD_MAX_LEN];       /* 登录密码 */
    CHAR    szDeviceID[IDM_DEVICE_ID_LEN];          /* 设备ID，主动注册模式下使用ID进行登录*/
    LONG    lLoginMode;                             /* 登录模式, 0-SDK私有协议登录 ,1-主动注册 */
    IDM_DEV_Login_Callback_PF pfLoginCallBack;      /* 异步登录回调函数，暂不启用 */
    VOID    *pUserData;                             /* 用户数据 */
	UCHAR   ucCertLoginMode;                        /* 证书登录模式 0为普通登录 1为证书登录 */
	CHAR    szTargetIP[43];							/* 目标IP(兼容IPv4,IPv6),优先使用szDeviceIP字段*/
	UCHAR   aucRes[20];
}IDM_DEV_USER_LOGIN_INFO_S;

/* 被动模式设备连接成功回调函数V1 */
typedef VOID(CALLBACK *IDM_DEV_Connect_Callback_PF)(
    const CHAR  *pszDeviceID,
    VOID        *pUserData
    );

/* 被动模式设备连接成功回调函数V2 */
/* 主动注册时 设备带的设备信息 */
typedef struct  tagIDM_DEV_PASSIVE_CONNECT_DEVINFO
{
	CHAR  szDeviceID[64];                 /* 设备ID */
	CHAR  szDeviceModel[32];              /* 设备型号*/
	CHAR  szDeviceAuthCode[32];           /* 验证码 */
	CHAR  szDeviceFirmWareName[128];      /* 固件名称 */ 
	CHAR  szSoftVersion[64];              /* 软件版本号 */
	CHAR  szDevIP[64];                    /* 设备IP */  
	CHAR  unUsed[128];                    /* 未使用字段 */
}IDM_DEV_PASSIVE_CONNECT_DEVINFO_S;
typedef INT(CALLBACK *IDM_DEV_Connect_Callback_PF_V2)(
	IDM_DEV_PASSIVE_CONNECT_DEVINFO_S *pInfo,
	VOID        *pUserData
	);

#if 0
/* 实时预览 */
#endif
/* 实时预览回调函数 */
typedef VOID(CALLBACK *IDM_DEV_RealPlay_Callback_PF) (
    LONG    lRealPlayHandle,
    ULONG   ulDataType,
    UCHAR   *pucBuffer,
    ULONG   ulBufferSize,
    VOID    *pUserData
    );

/* 预览参数结构体 */
typedef struct tagIDM_DEV_PREVIEW_INFO
{
    ULONG   ulChannel;                              /* 通道号 */
    ULONG   ulStreamType;                           /* 码流类型：0-主码流 1-子码流 2-三码流 */
    ULONG   ulLinkMode;                             /* 连接方式：0-TCP 1-UDP 2-多播 3-RTP/RTSP，暂时只支持TCP */
	UCHAR	ulStreamTimeout;						/*收流超时时间(秒)[5-120] 不在范围内,默认30秒*/
    UCHAR   aucRes[255];
}IDM_DEV_PREVIEW_INFO_S;

typedef struct tagIDM_DEV_PACKET_INFO
{
    ULONG   ulFrameNum;                             /* 帧序号 */
    ULONG   ulPacketType;                           /* 数据类型: 0-视频I帧 1-视频B帧 2-视频P帧 3-音频帧 4-私有数据 */
    ULONG   ulEncodeType;                           /* 编码类型 */
    ULONG   ulPacketMode;                           /* 打包方式 */
    ULONG   ulTimeStamp;                            /* 时间戳低位 */
    ULONG   ulTimeStampHight;                       /* 时间戳高位 */
    ULONG   ulFrameRate;                            /* 帧率 */
    USHORT  usWidth;                                /* 宽度 */
    USHORT  usHeight;                               /* 高度 */
    ULONG   ulBufferSize;                           /* 数据大小 */
    UCHAR   *pucBuffer;                             /* 数据缓冲指针 */
    UCHAR   aucRes[64];
}IDM_DEV_PACKET_INFO_S;

/* 实时预览回调函数 */
typedef VOID(CALLBACK *IDM_DEV_RealPlayES_Callback_PF) (
    LONG    lRealPlayHandle,
    IDM_DEV_PACKET_INFO_S *pstPacketInfo,
    VOID    *pUserData
    );

#if 0
/* 录像回放 */
#endif
/* 录像回放回调函数 */
typedef VOID(CALLBACK *IDM_DEV_PlayBack_Callback_PF) (
    LONG    lPlayBackHandle,
    ULONG   ulDataType,
    UCHAR   *pucBuffer,
    ULONG   ulBufferSize,
    VOID    *pUserData
    );
/* 录像文件下载回调函数 */
typedef VOID(CALLBACK *IDM_DEV_Download_Callback_PF) (
	LONG    lPlayBackHandle,
	ULONG   ulDataType,
	UCHAR   *pucBuffer,
	ULONG   ulBufferSize,
	VOID    *pUserData
	);
/* 文件下载进度回调函数 */
typedef VOID(CALLBACK *IDM_DEV_Download_Progress_Callback_PF) (
	LONG    lPlayBackHandle,
	FLOAT   fProgress,
	VOID    *pUserData
	);

/* 文件名条件结构体 */
typedef struct tagIDM_DEV_PLAYBACK_COND_NAME
{
    CHAR  szFileName[256];                          /* 回放文件名 */
}IDM_DEV_PLAYBACK_COND_NAME_S;

/* 时间条件结构体 */
typedef struct tagIDM_DEV_PLAYBACK_COND_TIME
{
    ULONG   ulChannel;                              /* 通道号 */
    ULONG   ulStreamType;                           /* 码流类型：0-主码流 1-子码流 2-三码流 */
    IDM_DEV_TIME_PARAM_S  stStartTime;
    IDM_DEV_TIME_PARAM_S  stEndTime;
    UCHAR   ucNotDelFile;                           /* 下载未完成是否删除文件：0-删除 1-不删除 */
    UCHAR   aucRes[127];
}IDM_DEV_PLAYBACK_COND_TIME_S;

/* 回放条件参数结构体 */
typedef struct tagIDM_DEV_PLAYBACK_COND
{
    USHORT usType;                                  /* 回放条件类型：0-按文件名 1-按时间 */
    UCHAR  ucRecordType;                            /* 回放录像类型：0-所有录像 1-常规录像 2-移动侦测 3-报警录像 */

	UCHAR  ucDownloadModel;                         /* 下载模式：0-流模式下载 1-帧模式下载 ，不带该字段默认为流模式下载 */
	UCHAR  ucRecordDomainLevel;                     /* 待检索日历的录像所属域级别， 默认值为0 0-本级域(本地)，1-1级域(远程)，当前最大支持1级 */
	ULONG  ulChannel;                               /* 通道号 (远程时需要用)*/
	LLONG  llFileSize;                              /* 文件大小返回给用户 */
    UCHAR  ucStreamTimeout;							/*收流超时时间(秒)[5-120] 不在范围内,默认30秒*/
    union {
        IDM_DEV_PLAYBACK_COND_NAME_S stNameCond;    /* 文件名条件 */
        IDM_DEV_PLAYBACK_COND_TIME_S stTimeCond;    /* 时间条件 */
    };
}IDM_DEV_PLAYBACK_COND_S;

/* 回放录像文件查找条件结构体 */
typedef struct tagIDM_DEV_FILE_COND
{
    ULONG   ulPageNum;                              /* 搜索结果页码号 */
    ULONG   ulChannel;                              /* 通道号 */
    ULONG   ulFileType;                             /* 录像类型 1-常规录像, 2-移动侦测录像, 3-报警录像, 252-断网录像, 253-手动录像, 254-所有类型 */
    ULONG   ulStreamType;                           /* 码流类型 0-主码流, 1-辅码流, 2-三码流, N-N码流（以此类推）, 253-辅码流优先（N->0）同时只查一种, 254-主码流优先（0->N）同时只查一种, 255-查询所有满足其他条件的码流 */
    ULONG   ulLockStatus;                           /* 录像锁定状态 0-未锁定, 1-锁定, 254-所有 */
    IDM_DEV_TIME_PARAM_S  stStartTime;              /* 起始时间 */
    IDM_DEV_TIME_PARAM_S  stEndTime;                /* 结束时间 */
    UCHAR   aucRes[64];
}IDM_DEV_FILE_COND_S;

/* 时间段 */
typedef struct tagIDM_DEV_TIME_SPAN
{
    IDM_DEV_TIME_PARAM_S  stStartTime;              /* 起始时间 */
    IDM_DEV_TIME_PARAM_S  stEndTime;                /* 结束时间 */
}IDM_DEV_TIME_SPAN_S;

/* 回放录像文件查找条件结构体 */
typedef struct tagIDM_DEV_FILE_COND_EX
{
    ULONG   ulPageNum;                              /* 搜索结果页码号1-N */
    ULONG   aulChannel[16];                         /* 通道号列表 */
    ULONG   aulFileType[32];                        /* 录像类型列表 */
    ULONG   aulStreamType[10];                      /* 码流类型列表 */
    ULONG   ulLockStatus;                           /* 录像锁定状态 0-未锁定, 1-锁定, 254-所有 */
    IDM_DEV_TIME_SPAN_S astTimeSpan[8];             /* 时间段列表 */
    UCHAR   ucChannelNum;                           /* 通道号数量 */
    UCHAR   ucFileTypeNum;                          /* 录像类型数量 */
    UCHAR   ucStreamTypeNum;                        /* 码流类型数量 */
    UCHAR   ucTimeSpanNum;                          /* 时间段数量 */
	UCHAR   ucRecordDomainLevel;                    /* 待检索日历的录像所属域级别， 0-本级域(本地)，1-1级域(远程)，当前最大支持1级 */
    UCHAR   aucRes[63];
}IDM_DEV_FILE_COND_EX_S;

typedef struct tagIDM_DEV_FILE_COND_V3
{
	ULONG   ulPageNum;                              /* 搜索结果页码号1-N */
	UINT    uiPageSize;								/* 每页数量*/
	ULONG   aulChannel[16];                         /* 通道号列表 */
	ULONG   aulFileType[32];                        /* 录像类型列表 */
	ULONG   aulStreamType[10];                      /* 码流类型列表 */
	ULONG   ulLockStatus;                           /* 录像锁定状态 0-未锁定, 1-锁定, 254-所有 */
	IDM_DEV_TIME_SPAN_S astTimeSpan[8];             /* 时间段列表 */
	UCHAR   ucChannelNum;                           /* 通道号数量 */
	UCHAR   ucFileTypeNum;                          /* 录像类型数量 */
	UCHAR   ucStreamTypeNum;                        /* 码流类型数量 */
	UCHAR   ucTimeSpanNum;                          /* 时间段数量 */
	UCHAR   ucRecordDomainLevel;                    /* 待检索日历的录像所属域级别， 0-本级域(本地)，1-1级域(远程)，当前最大支持1级 */
	UCHAR   aucRes[63];
}IDM_DEV_FILE_COND_S_V3;

/* 回放录像文件信息结构体 */
typedef struct tagIDM_DEV_FILE_RECORD
{
    CHAR    szFileName[256];                        /* 文件名 */
    ULONG   ulFileSize;                             /* 文件大小 */
    ULONG   ulChannelNo;                            /* 文件所属通道号 */
    ULONG   ulRecordType;                           /* 录像类型 1-常规录像, 2-移动侦测录像, 3-报警录像, 252-断网录像, 253-手动录像 */
    ULONG   ulStreamType;                           /* 码流类型 0-主码流, 1-辅码流, 2-三码流, N-N码流(以此类推) */
    ULONG   ulLockStatus;                           /* 录像锁定状态 0:未锁定，1:锁定 */
    IDM_DEV_TIME_PARAM_S  stStartTime;              /* 起始时间 */
    IDM_DEV_TIME_PARAM_S  stEndTime;                /* 结束时间 */
}IDM_DEV_FILE_RECORD_S;

/* 回放录像文件查询结果V1 建议废弃 */
typedef struct tagIDM_DEV_FILE_RESULT
{
    ULONG ulPageNum;                                /* 当前页码 */
    ULONG ulTotalNum;                               /* 总页码 */
    ULONG ulRecordNum;                              /* 返回的记录数量 */
    IDM_DEV_FILE_RECORD_S stRecord[20];             /* 返回的文件信息 */
}IDM_DEV_FILE_RESULT_S;

/* 回放录像文件查询结果V3 */
typedef struct tagIDM_DEV_FILE_RESULT_V3
{
	ULONG ulPageNo;                                 /* 当前页码 */
	ULONG ulTotalNum;                               /* 记录总数 */
	ULONG ulRecordNum;                              /* 当前页返回的记录数量 */
	IDM_DEV_FILE_RECORD_S *pFileArray;              /* 返回的文件信息 (内部分配,需要外部释放IDM_DEV_Free)*/
}IDM_DEV_FILE_RESULT_S_V3;

/* 月历录像分布查询条件结构体 */
typedef struct tagIDM_DEV_MRD_SEARCH_PARAM
{
    ULONG   ulChannel;                              /* 通道号 */
    USHORT  usYear;                                 /* 年 */
    USHORT  usMonth;                                /* 月 */
    ULONG   ulStreamType;                           /* 码流类型： 0-主码流, 1-辅码流, 2-三码流, N-N码流(以此类推) */
    ULONG   ulFileType;                             /* 录像文件类型：1-常规录像, 2-移动侦测录像, 3-报警录像, 252-断网录像, 253-手动录像 254-所有 */
    UCHAR   aucRes[28];
}IDM_DEV_MRD_SEARCH_PARAM_S;

/* 月历录像分布查询条件结构体 */
typedef struct tagIDM_DEV_MRD_SEARCH_PARAM_EX
{
    ULONG   aulChannel[16];                         /* 通道号 */
    USHORT  usYear;                                 /* 年 */
    USHORT  usMonth;                                /* 月 */
    ULONG   aulStreamType[32];                      /* 码流类型： 0-主码流, 1-辅码流, 2-三码流, N-N码流(以此类推) */
    ULONG   aulFileType[10];                        /* 录像文件类型：1-常规录像, 2-移动侦测录像, 3-报警录像, 252-断网录像, 253-手动录像 254-所有 */
    UCHAR   ucChannelNum;                           /* 通道号数量 */
    UCHAR   ucFileTypeNum;                          /* 录像类型数量 */
    UCHAR   ucStreamTypeNum;                        /* 码流类型数量 */
	UCHAR   ucRecordDomainLevel;                    /* 待检索日历的录像所属域级别， 0-本级域(本地)，1-1级域(远程)，当前最大支持1级 */
    UCHAR   aucRes[28];
}IDM_DEV_MRD_SEARCH_PARAM_EX_S;

/*月历录像分布查询结果结构体*/
typedef struct tagIDM_DEV_MRD_SEARCH_RESULT
{
    UCHAR    ucDay[32];
    UCHAR    aucRes[32];
}IDM_DEV_MRD_SEARCH_RESULT_S;

#if 0
/* 报警布防/监听 */
#endif
/* 报警参数结构体 */
typedef struct tagIDM_DEV_ALARM_PARAM
{
    ULONG   ulLevel;                                /* 布防优先级：0–高 1–中 2–低 */
    CHAR    *pcSubscribes;                          /* 订阅参数字符串(/事件类型/事件等级)(JSON格式)  例如 "{\"channel_no_list\":[65535],\"event_types\":[0],\"event_levels\":[2]}";*/
													/* 通道列表         channel_no_list 65535表示布防所有通道
													   告警类型列表     event_types     0表示所有类型 列表为[]表示不订阅任何类型
													   布防事件等级列表 event_levels
													   图片上报模式     img_trans_type   0-二进制+URL 1-二进制 2-URL
													   开始时间        [可选]start_time  ISO8601格式
													   结束时间        [可选]end_time    ISO8601格式
													*/
    ULONG   ulSubscribesLen;                        /* 订阅参数字符串的长度 */
    UCHAR   ucType;                                 /* 报警上传类型：0-JSON(支持) 1-结构体 */
    UCHAR   ucLinkMode;                             /* 是否事件链接复用: 0xFF-使用登录链接 其他:另起链接*/
	UCHAR   ucIgnoreAlgoGuardPlan;					/* 忽略算法本身的布防时间控制 1 忽略,0不忽略,默认0*/
	UCHAR   aucRes[125];
}IDM_DEV_ALARM_PARAM_S;

/* 报警消息回调函数 */
typedef VOID(CALLBACK *IDM_DEV_Message_Callback_PF) (
    LONG    lUserID,
    ULONG   ulCommand,
    VOID    *pBuffer,
    ULONG   ulBufferSize,
    IDM_DEV_ALARM_DEVICE_INFO_S *pstAlarmDeviceInfo,
    VOID    *pUserData
    );

typedef struct tagIDM_DEV_ALARM_BUFFER
{
    ULONG   ulIndex;                                /* 索引 */
    USHORT  usType;                                 /* 数据类型：1-JSON 2-二进制 */
    USHORT  usSubType;                              /* 数据子类型: (类型为二进制时有效) 1-车辆大图 2-车牌彩色小图 3-车牌二值图 4-驾驶员面部特征图 5-副驾驶面部特征图 6-车标 7-违章合成图 8-过车合成图 9-车辆特写图 10-人员图 11-人脸图 12-非机动车图 13-物品图 14-场景图 100-一般图片 101-热力图 102-车辆缩略图 200-二进制特征数据 */
    CHAR    *pBuffer;                               /* 数据缓冲区指针 */
    ULONG   ulBufferSize;                           /* 数据缓冲区长度 */
}IDM_DEV_ALARM_BUFFER_S;

/* 通用事件报警结构体 */
typedef struct tagIDM_DEV_ALARM_EVENT
{
    IDM_DEV_ALARM_BUFFER_S stEvent;                 /* 事件信息(JSON) */
    ULONG ulBufferNumber;                           /* 数据(图片/特征值)数量 */
    IDM_DEV_ALARM_BUFFER_S astBuffers[16];          /* 数据(图片/特征值)组 */
    ULONG ulEventType;                              /* 事件类型 */
    UCHAR aucRes[60];
}IDM_DEV_ALARM_EVENT_S;

typedef struct tagIDM_DEV_RECTANGLE
{
    USHORT  usX;                                    /* X坐标：[0,10000] */
    USHORT  usY;                                    /* Y坐标：[0,10000] */
    USHORT  usWidth;                                /* 宽：[0,10000] */
    USHORT  usHeight;                               /* 高：[0,10000] */
}IDM_DEV_RECTANGLE_S;

typedef struct tagIDM_DEV_POINT
{
    USHORT  usX;                                    /* X坐标：[0,10000] */
    USHORT  usY;                                    /* Y坐标：[0,10000] */
}IDM_DEV_POINT_S;

typedef struct tagIDM_DEV_POINTREGION
{
    ULONG ulValidNum;                               /* 有效点数量*/
    IDM_DEV_POINT_S stPointList[10];
}IDM_DEV_POINTREGION_S;

typedef struct tagIDM_DEV_ALARM_IMAGE_INFO
{
    CHAR    *pImage;                                /* 图片数据 */
    ULONG   ulImageSize;                            /* 图片长度 */
    USHORT  usWidth;                                /* 宽 */
    USHORT  usHeight;                               /* 高 */
    UCHAR   ucFormat;                               /* 图片编码格式：0-JPEG */
    UCHAR   ucTransMode;                            /* 图片传输方式：0-二进制 1-URL */
    UCHAR   aucRes[6];
}IDM_DEV_ALARM_IMAGE_INFO_S;

/* 报警输出配置 */
typedef struct tagIDM_DEV_ALARMOUT_CFG
{
    CHAR    szAlarmOutName[32];                     /* 报警输出名称 */
    LONG    lContinuedTime;                         /* 报警状态持续时间 */
    USHORT  usAlarmOutMode;                         /* 报警输出模式，0-关闭，1-自动 */
    USHORT  usAlarmOutStatus;                       /* 报警输出状态，只能获取无法配置，0-未报警；1-报警中 */
    UCHAR   aucRes[256];
}IDM_DEV_ALARMOUT_CFG_S;

/* 报警输出配置 */
typedef struct tagIDM_DEV_ALARMOUT_STATUS
{
    ULONG   ulAlarmOutNum;
    CHAR    acAlarmOutStatus[128];                  /* 报警输出状态 0-无输出 1-有输出 */
}IDM_DEV_ALARMOUT_STATUS_S;

/* 报警输出控制EX*/
typedef struct tagIDM_DEV_ALARMOUT_CONTROL
{
    ULONG ulAlarmID;                                /* 报警输出口ID*/
    ULONG ulAlarmOutStatus;                         /* 报警输出状态 0-无输出 1-有输出 2-一次脉冲输出*/
    ULONG ulTimeOut;                                /* 脉冲输出持续时间，单位:秒*/
    ULONG ulChannelNo;                              /* 报警输出远端通道，从0开始。本机报警通道号为0xFFFF*/
    UCHAR aucRes[128];
}IDM_DEV_ALARMOUT_CONTROL_S;

/* 报警联动录像通道配置 */
typedef struct tagIDM_DEV_ALARMOUT_LINKRECORD
{
    ULONG ulChannelNo;
    UCHAR aucRes[32];
}IDM_DEV_ALARMOUT_LINKRECORD_S;

/* 报警联动录像通道配置 */
typedef struct tagIDM_DEV_ALARMOUT_LINKSWITCH
{
    ULONG ulSwitchNo;
    UCHAR ucEnable;
    UCHAR aucRes[31];
}IDM_DEV_ALARMOUT_LINKSWITCH_S;

/* 远程通道报警输出配置 */
typedef struct tagIDM_DEV_ALARMOUT_REMOT
{
	ULONG ulAlarmOutID;                              /* 开关量输出ID 从0开始 */
	UCHAR ucEnable;                                  /* 是否启用联动开关量输出 */
	UCHAR aucRes[31];
}IDM_DEV_ALARMOUT_REMOT_S;

/* 远程通道配置 */
typedef struct tagIDM_DEV_REMOT_CHANNEL
{
	ULONG ulChannelNo;
	ULONG   ulRemotAlarmOutSize;
	ULONG   ulRemotAlarmOutNum;
	IDM_DEV_ALARMOUT_REMOT_S *pstAlamOutCfg;
	UCHAR aucRes[31];
}IDM_DEV_REMOT_CHANNEL_S;

/* 语音列表信息配置 */
typedef struct tagIDM_DEV_VOICE_INFO
{
	ULONG ulVoiceNo;                                      /* 需要联动播报的语音文件序号 */
	CHAR  szVoiceName[64];
	UCHAR aucRes[31];
}IDM_DEV_VOICE_INFO_S;

/* 报警联动配置 */
typedef struct tagIDM_DEV_ALARMOUT_LINKAGE_CFG
{
    ULONG   ulChannelNo;                                   /* 视频通道号 从0开始 1拖N的情况;0为主机 */
    ULONG   ulEventType;                                   /* 事件类型 */  
    ULONG   ulLibID;                                       /* 名单库ID 从0开始 0代表无库*/
    CHAR    szLibName[64];                                 /* 名单库名称 */
    UCHAR   ucLinkEmail;                                   /* 是否联动邮件 */
    UCHAR   ucLinkFTP;                                     /* 是否联动ftp */
    UCHAR   ucLinkUploadCenter;                            /* 是否联动上报中心 */
    UCHAR   ucLinkAudio;                                   /* 是否联动音频 */
    UCHAR   ucLinkRecod;                                   /* 是否联动录像 */
	UCHAR   ucIsLocalAlarmOutEnabled;                      /* 是否启用本地报警输出联动 0则不启用 仅使用于极云EC设备 IPC不支持；需要和pstAlamOutCfg配合使用*/
	UCHAR   ucIsTotalEnabled;                              /* 联动远端报警输出总开关 0则配置的报警输出联通都不启用  */
    UCHAR   aucRes[1];
    ULONG   ulRecordDelay;                                 /* 警后录像时间 */
    ULONG   ulLinkRecordSize;                              
    ULONG   ulLinkRecordNum;
    IDM_DEV_ALARMOUT_LINKRECORD_S *pstRecordCfg;           /* 需要联动的录像通道列表 */
    ULONG   ulLinkSwitchSize;
    ULONG   ulLinkSwitchNum;
    IDM_DEV_ALARMOUT_LINKSWITCH_S *pstSwitchCfg;
	ULONG   ulRemotChannelSize;
	ULONG   ulRemotChanelNum;
	IDM_DEV_REMOT_CHANNEL_S *pstRemotChannelCfg;
	ULONG   ulPlayVoiceNo;
	ULONG   ulVoiceListSize;
	ULONG   ulVoiceListNum;
	IDM_DEV_VOICE_INFO_S *pstVoiceInfoCfg;
    UCHAR   aucRes2[128];
}IDM_DEV_ALARMOUT_LINKAGE_CFG_S;

/* 报警布防时间配置*/
typedef struct tagIDM_DEV_GUARDPLAN_TIME
{
    ULONG ulSpanNum;                                   /* 时间段数量 0~8*/
    IDM_DEV_TIMESPAN_PARAM_S  stStartTime[8];              /* 起始时间 精确到分*/
    IDM_DEV_TIMESPAN_PARAM_S  stEndTime[8];                /* 结束时间 精确到分*/
    UCHAR   aucRes[32];
}IDM_DEV_ALARM_GUARDPLAN_TIME_S;

typedef struct tagIDM_DEV_ALARM_GUARDPLAN
{
    ULONG ulChannelNo;                                  /* 通道号*/
    ULONG ulGuardType;                                  /* 布防业务类型。0.移动侦测，1.遮挡报警，2.报警输入，3.报警输出，4.人脸抓拍图片上报*/
    ULONG ulGuardCtrlType;                              /* 布防控制类型。布防业务类型不为2和3时有效。1.控制事件产生，2.控制事件上报*/
    ULONG ulAlarmPutID;                                 /* 报警输入输出ID号，布防业务类型为2和3时有效*/
    IDM_DEV_ALARM_GUARDPLAN_TIME_S stTimeSpan[7];       /* 布防时间段 数组下标0~6:周一~周日*/
    UCHAR aucRes[32];
}IDM_DEV_ALARM_GUARDPLAN_S;

/*语音报警列表*/
typedef struct tagIDM_VOICELIST_INFO
{
    ULONG ulVoiceNo;                                   /*语音序号，从1开始*/
    CHAR szVoiceName[64];                              /*语音名称*/
    ULONG ulFileFormat;                                /*语音文件格式，1 ACC*/
    UCHAR ucIsInner;                                   /*是否预置语音，预置语音不支持用户重新导入覆盖*/
    ULONG ulTimeLen;                                   /*语音文件播放时长 单位：秒*/
    ULONG ulPlayCount;                                 /*报警语音播放次数，范围 1~10*/    
}IDM_VOICELIST_INFO_S;

typedef struct tagIDM_DEV_VOICELIST
{
    ULONG ulChannelNo;                                 /*通道号*/
    ULONG ulListNum;                                   /*语音列表数量 0~13*/
    IDM_VOICELIST_INFO_S stVoiceInfo[13];               /*语音列表信息*/
}IDM_DEV_VOICELIST_S;


/*全结构化合一算法配置*/
typedef struct tagIDM_DEV_INTELLIGENCE_AIUNITE_CFG
{
    ULONG ulChannelNo;                              /* 通道号*/
    UCHAR ucSensitivity;                            /* 检测灵敏度 1~100*/
    UCHAR ucVehicleStatistic;                       /* 是否开启车流量统计。0-关闭，1-开启*/
    UCHAR ucSnapShot;                               /* 快照开关。0-关闭，1-开启*/
    UCHAR ucFaceCompare;                            /* 人脸比对开关。0-关闭，1-开启*/
    UCHAR ucPlateExpos;                             /* 车牌曝光开关。0-关闭，1-开启*/
    UCHAR ucAILed;                                  /* AI补光开关。0-关闭，1-开启*/
    UCHAR ucAILedTime;                              /* AI补光持续时间 1~100 秒*/
    UCHAR ucFaceExpos;                              /* 人脸曝光开关。0-关闭，1-开启*/
    UCHAR ucFaceExposLumi;                          /* 人脸曝光亮度 0~100*/
    UCHAR ucMaskVerify;                             /* 口罩校验开关。0-关闭，1-开启*/
    USHORT usFaceExposTime;                         /* 人脸曝光时间。 1~3600 秒*/
    USHORT usFaceAnaInterval;                       /* 人脸分析时间间隔。 1~600 秒*/
    USHORT usFollowTime;                            /* 尾随时间*/
    UCHAR ucFollowSpeak;                            /* 尾随播报开关。0-关闭，1-开启*/
    UCHAR ucRegionAttr;                             /* 区域属性。1-选中区域，2-屏蔽区域*/
    UCHAR ucDetectMode;                             /* 检测模式。0-混行检测，1-机动车检测，2-非机动车检测，3-行人检测*/
    UCHAR ucImageQuality;                           /* 图片质量。0~100*/
    USHORT usDetectTime;                            /* 检测时间*/
    UCHAR ucMaxPointNum;                            /* 规则框坐标点最大值 3~10*/
    UCHAR ucMinPointNum;                            /* 规则框坐标点最小值 3~10*/
    UCHAR ucMaxRegionNum;                           /* 最大规则区域个数 1~4*/
    UCHAR ucMinRegionNum;                           /* 最小规则区域个数 1~4*/
    UCHAR ucPerson;                                /* 行人解析开关。0-关闭，1-开启*/
    UCHAR ucVehicle;                                /* 车辆解析开关。0-关闭，1-开启*/
    UCHAR ucNonVehicle;                             /* 非机动车解析开关。0-关闭，1-开启*/
    UCHAR ucFace;                                   /* 人脸解析开关。0-关闭，1-开启*/
    USHORT usNonTruckTime;                          /* 非卡车上报时间间隔*/
    UCHAR ucNonTruckFilter;                         /* 非卡车过滤开关。0-关闭，1-开启*/
    UCHAR ucRuleRegionNum;                          /* 合一算法规则区域个数*/
    UCHAR ucTruckRegionNum;                         /* 非卡车过滤区域个数*/
    UCHAR aucRes;                                
    IDM_DEV_POINTREGION_S stMinRegion;              /* 最小检测区域*/
    IDM_DEV_POINTREGION_S stMaxRegion;              /* 最大检测区域*/
    IDM_DEV_POINTREGION_S stRuleRegion[4];          /* 合一算法规则区域列表*/
    IDM_DEV_POINTREGION_S stTruckRegion[4];         /* 非卡车过滤区域*/
    UCHAR   aucRes2[128];
}IDM_DEV_INTELLIGENCE_AIUNITE_CFG_S;

/* 云台控制参数 */
typedef struct tagIDM_DEV_PTZ_CONTROL_INFO
{
    UCHAR   ucSpeed;                                /* 速度：[1,100], 0 表示默认速度50 */
    UCHAR   ucAction;                               /* 动作：0-开始 1-停止 */
    UCHAR   aucRes[2];
}IDM_DEV_PTZ_CONTROL_INFO_S;

/* 3D定位参数 */
typedef struct tagIDM_DEV_PTZ_3D_ZOOM_INFO
{
    USHORT  usTopX;                                 /* 起始X坐标：[0,10000] */
    USHORT  usTopY;                                 /* 起始Y坐标：[0,10000] */
    USHORT  usBottomX;                              /* 结束X坐标：[0,10000] */
    USHORT  usBottomY;                              /* 结束Y坐标：[0,10000] */
}IDM_DEV_PTZ_3D_ZOOM_INFO_S;

/* 限位参数 */
typedef struct tagIDM_DEV_PTZ_LIMIT_INFO
{
    UCHAR   ucMode;                                 /* 限位模式：0-键控限位 1-扫描限位 */
    UCHAR   ucAction;                               /* 动作：0-设置 1-清除 */
    UCHAR   aucRes[2];
}IDM_DEV_PTZ_LIMIT_INFO_S;

typedef struct tagIDM_DEV_IPDEVINFO
{
    USHORT  usEnable;                               /* 设备是否启用 */
    USHORT  usPort;                                 /* 端口号 */
    CHAR    szIPv4[IDM_IPV4_ADDRESS_LEN];           /* 设备IP */
    CHAR    szDeviceName[IDM_DEVICE_NAME_LEN];      /* 设备名称 */
    CHAR    szUsername[IDM_USERNAME_MAX_LEN];       /* 用户名 */
    CHAR    szPassword[IDM_PASSWORD_MAX_LEN];       /* 密码 */
    UCHAR   aucRes[256];
}IDM_DEV_IPDEVINFO_S;

#if 0
/* 手动触发抓拍 */
#endif
/* 手动抓拍参数 */
typedef struct tagIDM_DEV_MANUALSNAP
{
    ULONG ulChanID;
    ULONG ulStreamType;
    UCHAR aucRes[32];
}IDM_DEV_MANUALSNAP_S;

/* 手动抓拍结果 */
typedef struct tagIDM_DEV_MANUALSNAP_RESULT
{
    CHAR    *pBuffer;                               /* 数据缓冲区指针 */
    ULONG   ulBufferSize;                           /* 数据缓冲区长度 */
    ULONG   ulPictureSize;                          /* 图片大小 */
    IDM_DEV_TIME_PARAM_S stTime;
    UCHAR   aucRes[32];
}IDM_DEV_MANUALSNAP_RESULT_S;

typedef struct tagIDM_DEV_MANUALSNAP_EX
{
    ULONG ulChannel;                                /* 通道号 */
    UCHAR ucLaneNo;                                 /* 车道号 */
    UCHAR aucRes[31];
}IDM_DEV_MANUALSNAP_EX_S;

/* 手动抓拍结果 */
typedef struct tagIDM_DEV_MANUALSNAP_RESULT_EX
{
    CHAR    szVehicleType[8];                       /* 车辆类型 */
    CHAR    szVehicleBrand[32];                     /* 车辆主品牌 */
    CHAR    szVehicleModel[32];                     /* 车辆子品牌 */
    CHAR    szVehicleStyle[32];                     /* 车辆年款 */
    UCHAR   ucVehicleColor;                         /* 车身颜色：1-黑 2-白 3-灰 4-红 5-蓝 6-黄 7-橙 8-棕 9-绿 10-紫 11-青 12-粉 13-透明 80-黄绿 81-渐变绿82-金 83-银 99-其他 */
    UCHAR   ucPlateType;                            /* 车牌类型：1-大型汽车号牌 2-小型汽车号牌 3-使馆汽车号牌 4-领馆汽车号牌 5-境外汽车号牌
                                                    6-外籍汽车号牌 7-普通摩托号牌 8-轻便摩托号牌 9-使馆摩托号牌 10-领馆摩托号牌
                                                    11-境外摩托号牌 12-外籍摩托号牌 13-低速车号牌 14-拖拉机号牌 15-挂车号牌
                                                    16-教练车号牌 17-教练摩托车号牌 20-临时入境汽车号牌 21-临时入境摩托车号牌 22-临时行驶车号牌
                                                    23-警用汽车号牌 24-警用摩托车号牌 25-原农机号牌 26-香港出入境号牌 27-澳门出入境号牌
                                                    31-武警号牌 32-军队号牌 70-农用摩托车号牌 71-实验汽车号牌 72-时延摩托车号牌
                                                    73-小型新能源车号牌 74-大型新能源车号牌 99-其他 */
    UCHAR   ucPlateColor;                           /* 车牌颜色：1-黑 2-白 5-蓝 6-黄 9-绿 80-黄绿 81-渐变绿 99-其他 */
    UCHAR   ucPlateConfidence;                      /* 车牌置信度：[0,100] */
    CHAR    szPlateNo[16];                          /* 车牌号码 */
    IDM_DEV_RECTANGLE_S stPlateRect;                /* 车牌坐标 */
    IDM_DEV_TIME_PARAM_S stSnapTime;                /* 抓拍时间 */
    CHAR    *pVehicle;                              /* 车辆特写图指针 */
    ULONG   ulVehicleSize;                          /* 车辆特写图长度 */
    CHAR    *pPlate;                                /* 车牌图片指针 */
    ULONG   ulPlateSize;                            /* 车牌图片长度 */
    CHAR    *pScene;                                /* 场景图片指针 */
    ULONG   ulSceneSize;                            /* 场景图片长度 */
    CHAR    *pPlateBinary;                          /* 车牌二值图片指针 */
    ULONG   ulPlateBinarySize;                      /* 车牌二值图片长度 */
    UCHAR   aucRes[16];
}IDM_DEV_MANUALSNAP_RESULT_EX_S;

#if 0
/* 设备搜索 */
#endif
/* 设备搜索结果 */
typedef struct tagIDM_DEV_DEVICE_SEARCH_INFO
{
    ULONG   ulRes1;
    ULONG   ulActived;                                 /* 是否已经激活 */   
    ULONG   ulResetAbility;                            /* 是否支持设备重置  */    
    ULONG   ulPasswdReset;                             /* 是否支持密码重置 */
    ULONG   ulDHCP;                                    /* 是否开启dhcp */
    ULONG   ulAlarmInNum;                              /* 报警输入通道数量 */       
    ULONG   ulAlarmOutNum;                             /* 报警输出通道数量 */
    ULONG   ulDiskNum;                                 /* 硬盘个数 */                  
    ULONG   ulIPType;                                  /* IP类型 */
    CHAR    szIP[IDM_IPV6_ADDRESS_LEN];                /* IP地址 */
    CHAR    szMask[IDM_IPV6_ADDRESS_LEN];              /* 子网掩码 */
    CHAR    szGateway[IDM_IPV6_ADDRESS_LEN];           /* 网关 */
    USHORT  usDevPort;                                 /* 私有协议端口 */ 
    USHORT  usHttpPort;                                /* HTTP端口 */
    CHAR    szDevMac[IDM_MAC_ADDRESS_LEN];             /* 设备MAC地址 */
    CHAR    szAdapterMac[IDM_MAC_ADDRESS_LEN];         /* */
    CHAR    szSoftwareVer[64];                         /* 软件版本 */      
    CHAR    szBootTime[64];                            /* 设备开机时间 */
    CHAR    szDevModel[64];                            /* 设备型号 设备类型的字符串描述 */
    CHAR    szSerialNum[IDM_SERIAL_NUMBER_LEN];        /* 设备序列号 */ 
	CHAR    szOemInfo[64];                             /* OEM厂商信息 */
	CHAR    szDevCurTime[64];                            /* 设备当前时间 */
	ULONG   ulAnalogChannelNum;                          /* 模拟通道数*/    
	ULONG   ulDigitalChannelNum;                         /* 数字通道数 */
    UCHAR   aucRes[64];
}IDM_DEV_DEVICE_SEARCH_INFO_S;

/* 设备搜索回调函数 */
typedef VOID(CALLBACK *IDM_DEV_SearchDevice_Callback_PF) (
    IDM_DEV_DEVICE_SEARCH_INFO_S    *pstDeviceInfo,
    VOID    *pUserData
    );

/* 设备激活参数结构体 */
typedef struct tagIDM_DEV_ACTIVATE_INFO_S
{
    CHAR    szPassword[IDM_PASSWORD_MAX_LEN];       /* 密码 */
    CHAR    szDeviceSN[64];
    CHAR    szPhoneNum[32];
    CHAR    szEmailAddr[256];
    UCHAR   aucRes[128];
}IDM_DEV_ACTIVATE_INFO_S;


/* 语音转发回调函数 */
typedef VOID(CALLBACK *IDM_DEV_VoiceCom_Callback_PF) (
    LONG    lVoiceComHandle,
    ULONG   ulDataType,
    UCHAR   *pucBuffer,
    ULONG   ulBufferSize,
    VOID    *pUserData
    );

/* 语音对讲参数结构体 */
typedef struct tagIDM_DEV_VOICECOM_INFO
{
    ULONG   ulChannel;                              /* 通道号 */
    UCHAR   ucChannelType;                          /* 通道类型：0-远程通道 1-本地通道 */
    UCHAR   aucRes[127];
}IDM_DEV_VOICECOM_INFO_S;

/* 文件下载回调函数 */
typedef VOID(CALLBACK *IDM_DEV_TransFile_Callback_PF) (
	UCHAR   *pucBuffer,
	ULONG   ulBufferSize,
	FLOAT   fProgress,
	VOID    *pUserData
	);


/* 算法通用化 结构体定义 */
#define ALGO_ID_MAX_LEN 64
/* 1.1 设备上通用化算法包结果建表规则查询 - 使用透传结构体*/
/* 1.2 设备上通用算法规则配置查询         - 使用透传结构体*/
/* 1.3 设备上通用算法规则配置设置         - 使用透传结构体*/
/* 1.4 设备上通用化算法包页面配置规则查询 - 使用透传结构体*/
/* 通用算法透传请求参数 */
typedef struct tagIDM_UNI_TRANS_REQUEST_PARAM
{
	CHAR     szMethod[128];                         /* 方法 不需要用户填写*/
	ULONG    ulBufferSize;                          /* JSON数据长度 */
	CHAR    *pcBuffer;                              /* JSON数据 如果传空JSON 传入"{}" 不要将地址置空 空间需要用户自行申请和释放*/
}IDM_UNI_TRANS_REQUEST_PARAM_S;

/* 网卡信息结构体 */
typedef struct tagIDM_DEV_CARD_INFO
{
	ULONG   ulLanID;                                  /*网卡编号*/
	CHAR    szLanName[32];                            /*网卡名称*/
	UCHAR   ucPPPoeEnable;                            /*是否启用了PPPoE, 0 - 未启用， 1-启用*/
	UCHAR   ucPortLinkStatus;                         /*网口link状态，0-no link，1-link ok*/
	ULONG   ulCardSupportNum;                         /*支持网卡类型的数量*/
	ULONG   ulCardSupport[6];                         /*支持网卡的类型*/
	ULONG   ulConfigDuplex;                           /*网卡类型*/
	UCHAR   ucAutomatic;                              /*是否启用自动获取ip地址*/
	CHAR    szIPv4Addr[64];                           /*网卡IPv4地址*/
	CHAR    szIPv4Mask[64];                           /*IPv4子网掩码*/
	CHAR    szIPv4Gateway[64];                        /*IPv4默认网关*/
	ULONG   ulIPv6Mode;                               /*IPv6地址获取方式 0-自动获取，1-手工配置，2-路由公告*/
	CHAR    szIPv6Addr[64];                           /*IPv6地址*/
	ULONG   ulIPv6MaskLength;                         /*IPv6子网掩码长度*/
	CHAR    szIPv6Gateway[64];                        /*IPv6默认网关*/
	CHAR    szMacAddr[32];                            /*网卡MAC地址*/
	ULONG   ulMTU;                                    /*MTU*/
	CHAR    szMultiAddr[64];                          /*组播地址，暂不支持*/
	UCHAR   ucMultiEnableSearch;                      /*是否启用组播搜索，暂不支持*/
	CHAR    szPreDNS[64];                             /*首先DNS服务器*/
	CHAR    szStandbyDNS[64];                         /*备选DNS服务器*/
	UCHAR   ucBooding;                                /*是否绑定虚拟网卡，0-否，1-是*/
	CHAR    szMode[32];                               /*网卡绑定模式 BalanceALB:适配器适应性均衡负载，ActiveBackup:容错模式*/
	ULONG   ulMembersSize;                            /*虚拟网卡绑定物理网卡lan_id的个数*/
	ULONG   ulMembers[6];                             /*虚拟网卡绑定各物理网卡成员编号，lan_id数组*/                   
	UCHAR   aucRes[64];
}IDM_DEV_CARD_INFO_S;

/* 通用算法透传响应参数 */
typedef struct tagIDM_UNI_TRANS_RESPONSE_PARAM
{
	CHAR    *pcBuffer;                              /* 输出缓冲区(JSON格式) */
	ULONG    ulReturnSize;                          /* 实际输出的JSON长度  */
}IDM_UNI_TRANS_RESPONSE_PARAM_S;

/* 1.6 已安装算法查询结构体 */
typedef struct tagIDM_UNI_SUPPORT_EVENTS
{
	ULONG  ulEventType;       /* 私有协议事件类型 */
	CHAR   szEventName[128];  /* 事件名称 */
	UCHAR  ucEventLevel;      /* 事件级别 */
	UCHAR  ucUnRes[123]; 
}IDM_UNI_SUPPORT_EVENTS_S;
typedef struct tagIDM_INSTALLED_ALGO
{
	CHAR                      szAlgoIdentify[64];   /* 算法唯一标识 */
	UCHAR                     ucIsUniAlgo;          /* 是否通用化算法 */
	UCHAR                     ucIsRunning;          /* 是否正在运行 */
	UCHAR                     ucUnRes[2];        
	CHAR                      szAlgoName[64];       /* 算法名称 */
	ULONG                     ulManuFact;           /* 算法厂商 */
	CHAR                      szManuFactName[64];   /* 算法厂商展示名称*/
	CHAR                      szAlgoVersion[64];    /* 算法版本 */
	CHAR                      szInstallTime[64];    /* 安装时间 ISO8601 2020-11-19T14:23:44.123+0800 */
	IDM_UNI_SUPPORT_EVENTS_S *pstSupportEventsList; /* 算法支持的算法类型列表 通用化算法必填 */
	ULONG                     ulSupportEventListLen;/* 列表长度*/
}IDM_INSTALLED_ALGO_S;

typedef struct tagIDM_UNI_QUERY_INSTALLED_ALGO_RESPONSE
{
	IDM_INSTALLED_ALGO_S *       pstInstalledAlgoList;       /* 已安装的算法列表 */
	ULONG                        ulInstalledAlgoListLen;     /* 已安装的算法列表长度 */
	UCHAR                        ucIsSupportUniAlgo;         /* 是否支持通用化算法 不携带则意味着不支持 */
	UCHAR                        ucUnRes[53];        
}IDM_UNI_QUERY_INSTALLED_ALGO_RESPONSE_S;


/* 1.7 算法切换结构体 */
typedef struct tagIDM_UNI_SWITCH_ALGO
{
	ULONG ulChannelNo;        /* 通道编号从0开始 无效0xFFFF */
	CHAR  szAlgoIdentify[64]; /* 算法唯一标识 */
	ULONG ulManuFact;         /* 算法厂商 */
	CHAR  szAlgoVersion[32];  /* 算法版本号 */
	UCHAR ucFlag;             /* 内部使用 */
	UCHAR ucUnRes[141]; 
}IDM_UNI_SWITCH_ALGO_S;


/* 1.8 加载/升级算法版本结构体 */
typedef struct tagIDM_UNI_URL_INFO
{
	CHAR   szHTTPIPAddress[64];     /* HTTP下载地址       */
	CHAR   szUrl[256];              /* HTTP文件访问的路径 */
	CHAR   szToken[48];             /* 访问token          */
	USHORT usHTTPPort;              /* HTTP访问端口       */
	UCHAR  ucUnRes[142]; 
}IDM_UNI_URL_INFO_S;

typedef struct tagIDM_UNI_LOAD_ALGO_REQUEST
{
	CHAR    szTaskID[64];        /* 算法加载或升级任务的ID */
	CHAR    szAlgoIdentify[64];  /* 算法唯一标识 */
	CHAR    szAlgoName[64];      /* 算法名称 */
	ULONG   ulManuFact;          /* 算法厂商 */
	CHAR    szManuFactName[64];  /* 算法厂商展示名称*/
	CHAR    szAlgoVersion[32];   /* 算法版本号 */
	ULONG   ulAlgoSize;          /* 算法包大小 单位字节*/
	UCHAR   ucLoadSource;        /* 算法版本来源 1-设备web 2-算法仓web 3-工具 */
	UCHAR   ucLoadType;          /* 加载模式 1-安装 2-升级 3-工具 */
	UCHAR   ucUnRes[2]; 
	ULONG   ulChannelNoListLen;  /* 通道列表长度*/
	ULONG * pulChannelNoList;    /* 待加载算法的通道列表 本机不需要带; 如果VMS通过EC216给接入的IPC加载或升级算法则需要*/
	IDM_UNI_URL_INFO_S stUrlInfo;/* 工具包下载URL信息*/
}IDM_UNI_LOAD_ALGO_REQUEST_S;


/*文件传输参数结构体*/
typedef struct tagIDM_DEV_TRANS_FILE_INFO
{
	ULONG   ulSrvType;                               /*业务类型：0-通用文件上传 1-配置文件上传 2-算法包文件上传 3-音频播报文件上传 4-设备升级包上传 100-通用文件下载 101-配置文件下载 102-算法包文件下载 999-所有*/
	CHAR    sFileSrcPath[256];                       /*文件传输源路径*/                  
	CHAR    szFileDestPath[256];                     /*文件传输目的路径*/
	CHAR    szFileName[256];                         /*文件名称*/
}IDM_DEV_TRANS_FILE_INFO_S;

/* TCP/IP配置参数结构体 */
typedef struct tagIDM_DEV_TCPIP_CFG
{
	CHAR   szDevSN[64];                                /*设备序列号*/
	ULONG  ulDefaultLanID;                             /*默认使用的网卡ID，多网卡下必填*/
	ULONG  CardListNum;                                /*物理网卡列表的大小*/
	IDM_DEV_CARD_INFO_S stCardInfo[5];                 /*物理网卡信息*/
	UCHAR  ucExitBond;                                 /*是否存在虚拟网卡 0-不存在，1-存在*/
	IDM_DEV_CARD_INFO_S stBond;                        /*虚拟网卡信息*/
	UCHAR   aucRes[64];
}IDM_DEV_TCPIP_CFG_S;

/* 启动一键搜索添加设备参数结构体 */
typedef struct tagIDM_DEV_START_DEV_AUTO_SEARCH_ADD
{
	ULONG ulAuthType;                                    /*搜索设备登录鉴权类型：1-使用本设备admin用户及密码登录搜索设备鉴权，2-使用自定义用户和密码登录搜索设备鉴权*/
	CHAR  szUerName[64];                                 /*搜索到设备的登录用户名，使用自定义用户名密码鉴权时必填*/
	CHAR  szPassword[64];                                    /*搜索到设备的登录密码，使用自定义用户名密码鉴权时必填*/
	UCHAR aucRes[32];
}IDM_DEV_START_DEV_AUTO_SEARCH_ADD_S;

/* 查询一键搜索添加设备处理进度参数结构体 */
typedef struct tagIDM_DEV_QUERY_DEV_AUTO_ADD_PROGRESS
{
	ULONG ulAddSucceedNum;                               /*添加成功的设备数量*/
	ULONG ulAlreadyExistNum;                             /*添加时发先已存在的设备数量*/
	ULONG ulAddFailedNum;                                /*添加失败的设备数量*/
	ULONG ulTotalSearchNum;                              /*搜索得到的设备总数量*/
	ULONG ulProcessPercent;                              /*处理百分比进度，取值范围[0,100]*/
	UCHAR aucRes[32];
}IDM_DEV_QUERY_DEV_AUTO_ADD_PROGRESS_S;




/* 文件上传任务创建返回结果结构体 */
typedef struct tagIDM_DEV_CREAT_TRANSFILE_RESULT
{
	ULONG ulTaskID;                                  /*文件上传任务ID*/
	ULONG ulPerChunkSize;                            /*单个文件块大小*/
}IDM_DEV_CREAT_TRANSFILE_RESULT_S;

/*上传文件块参数结构体*/
typedef struct tagIDM_DEV_UPLOAD_FILE_CHUNK
{
	ULONG ulTaskID;                                  /*文件上传任务ID*/
	ULONG ulFileChunkNum;                            /*需要上传的文件块总数*/
	ULONG ulCurChunkIdx;                             /*当前上传文件块索引，从1开始，当为总数时为结束*/
	ULONG ulChunkOptonIdx;                           /*当前文件块在Option消息体中的索引，默认为1*/
	ULONG ulPerChunkSize;                            /*单个文件块大小*/
	ULONG ulFileSize;                                /*文件大小*/
}IDM_DEV_UPLOAD_FILE_CHUNK_S;

/*文件传输参数结构体*/
typedef struct tagIDM_DEV_TRANS_FILE_INFOS
{
	CHAR    szTaskName[128];                         /*任务名称*/
	ULONG   ulSrvType;                               /*业务类型：0-通用文件上传 1-配置文件上传 2-算法包文件上传 3-音频播报文件上传 4-设备升级包上传 100-通用文件下载 101-配置文件下载 102-算法包文件下载 999-所有*/
	ULONG   ulFileID;                                /*文件id*/
	CHAR    szFileMD5[64];                           /*文件MD5值*/
	ULONG   ulFileSize;                              /*文件大小*/
	CHAR    szFileDestPath[256];                     /*文件传输目的路径*/
	CHAR    szFileName[256];                         /*文件名称*/
}IDM_DEV_TRANS_FILE_INFOS_S;

/* 创建文件下载任务参数结构体 */
typedef struct tagIDM_DEV_DOWNLOAD_FILE_INFO
{
	CHAR    szTaskName[128];                         /*任务名称，非必填*/
	ULONG   ulSrvType;                               /*业务类型：0-通用文件上传 1-配置文件上传 2-算法包文件上传 3-音频播报文件上传 4-设备升级包上传 100-通用文件下载 101-配置文件下载 102-算法包文件下载 999-所有*/
	CHAR    szFileSrctPath[256];                     /*服务端下载文件路径，如果业务类型已经隐含了下载路径，则不需要填写*/
	CHAR    szFileName[256];                         /*文件名称，如果业务类型已经隐含了文件名，不需要填写，由服务端返回*/
	UCHAR   aucRes[64];
}IDM_DEV_DOWNLOAD_FILE_INFO_S;

/* 文件下载任务创建返回结果结构体 */
typedef struct tagIDM_DEV_CREAT_DOWNLOAD_RESULT
{
	ULONG ulTaskID;                                  /*文件下载任务ID*/
	CHAR  szFileName[256];                           /*文件名称*/
	ULONG ulFileSize;                                /*文件大小*/
	CHAR  szFileMD5[64];                             /*文件MD5值*/
	ULONG ulPerChunkSize;                            /*单个文件块大小*/
	ULONG ulFileChunksNum;                           /*文件传输块总量*/
}IDM_DEV_CREAT_DOWNLOAD_RESULT_S;

/*触发语音报警播放参数结构体*/
typedef struct tagIDM_DEV_TRIGGER_ALARM_VOICE
{
	ULONG   ulChannel;                                /*通道号，从0开始，可选*/
	ULONG   ulVoiceNo;                                /*语音序号，从1开始*/
	ULONG   ulTriggerAction;                          /*触发动作：0 - 关闭；1 - 触发*/
}IDM_DEV_TRIGGER_ALARM_VOICE_S;


/* STUN信息结构体 */
typedef struct tagIDM_DEV_STUN_INFO
{
	CHAR  szPublicIP[64];                               /*STUN服务公网地址*/
	ULONG ulPublicPort;                                 /*STUN服务公网端口*/
	UCHAR   aucRes[16];
}IDM_DEV_STUN_INFO_S;

/* P2P穿网信息协商参数结构体 */
typedef struct tagIDM_DEV_P2P_THROUGH_NET
{
	CHAR  szAPPPublicIP[64];                            /*APP公网IP地址（必填）*/
	ULONG ulAPPPlblicPort;                              /*APP公网端口（必填）*/
	ULONG ulAPPNatType;                                 /*APP端NAT类型：1-全锥型，2-IP限制型，3-端口限制型，4-对称型（必填）*/
	ULONG ulP2PTimeout;                                 /*P2P打洞超时时间，单位：秒（必填）*/
	CHAR  szP2PToken[64];                               /*P2P打洞链路唯一标识，由APP侧生成（必填）*/
	ULONG STUNServeNum;                                 /*STUN的数量（必填）*/
	IDM_DEV_STUN_INFO_S stSTUN[5];                      /*STUN信息（必填）*/
	UCHAR   aucRes[64];
}IDM_DEV_P2P_THROUGH_NET_S;

/* P2P穿网协议协商返回结果参数结构体 */
typedef struct tagIDM_DEV_P2P_THROUGH_RESULT
{
	CHAR  szDevPublicIP[64];                             /*设备公网IP地址*/
	ULONG ulDevPublicPort;                               /*设备公网端口*/
	ULONG ulDevNatType;                                  /*设备端NAT类型：1-全锥型，2-IP限制型，3-端口限制型，4-对称型*/
}IDM_DEV_P2P_THROUGH_RESULT_S;


/* 设备系统信息 V2*/
typedef struct tagIDM_DEV_SYSTEM_INFO_V2
{
	CHAR    szDeviceModel[64];                      /* 设备型号 */
	CHAR    szSerialNum[64];                        /* 设备序列号 */
	CHAR    szAuthCode[32];                         /* 设备验证码 */
	CHAR    szMacAddress[32];                       /* 设备Mac地址 */
	CHAR    szSoftwareVersion[64];                  /* 软件版本号 */
	CHAR    stSoftwareBuildTime[64];                /* 软件生成时间 */
	USHORT  usDeviceClass;                          /* 设备类别：0：IPC高清网络摄像机 1:ITC智能交通摄像机 100:IVR智能网络硬盘录像机 101:NVR网络硬盘录像机 */
	USHORT  usDigitalChannelNum;                    /* 数字通道个数 */
	UCHAR   ucAnalogChannelNum;                     /* 模拟通道个数 */
	UCHAR   ucDiskNum;                              /* 硬盘个数 */
	USHORT  usHttpPort;                             /* HTTP端口号，默认80 */
	USHORT  usHttpsPort;                            /* HTTPS端口号，默认443 */
	USHORT  usRtspPort;                             /* RTSP端口号，默认554 */
	USHORT  usSdkPort;                              /* SDK端口号 */
	UCHAR   ucAlarmInNum;                           /* 报警输入个数 */
	UCHAR   ucAlarmOutNum;                          /* 报警输出个数 */

	CHAR    szDevIP[64];                            /* 设备IP地址 */
	CHAR    szPubNetIP[64];                         /* 设备主动注册时 连接到netsdk的 IP地址 不一定是公网IP */
	CHAR    szNetMask[64];                          /* 子网掩码 */
	CHAR    szGetWayIP[64];                         /* 网关IP地址 */
	CHAR    szGetWayMac[32];                        /* 网关MAC地址 */
	CHAR    szFirmwareName[128];                    /* 固件名称 */
	CHAR    szBootTime[64];                         /* 设备开机时间 */
	CHAR    szOEMInfo[64];                          /* OEM厂商信息 */
	UCHAR   ucIsResetAbility;                       /* 是否支持设备重置 */
	UCHAR   ucIsResetPasswrdResetAbility;           /* 是否支持密码重置 */
	UCHAR   ucIsActivated;                          /* 是否已激活 */
	UCHAR   ucIPType;                               /* IP地址类型 */
	UCHAR   ucIpcClass;                             /* 前端IPC类型大类 */
	UCHAR   ucIsDHCP;                               /* DHCP是否开启 */
	UCHAR   aucRes[138];
}IDM_DEV_SYSTEM_INFO_V2_S;

/* 设备二维码 */
typedef struct tagIDM_DEV_QR_RESPONSE
{
	CHAR szQrCode[64];
	CHAR unUsed[192];
}IDM_DEV_QR_RESPONSE_S;

/* 14. 查询设备信息 */
typedef struct tagIDM_DEV_ADDED_CHANNEL
{
	ULONG    ulLocalChannelNo;    /* 本地通道号 */
	ULONG    ulRemoteChannelNo;   /* 远程通道号 */
	CHAR     szChannelName[128];  /* 通道名称 */
	UCHAR    isOnline;            /* 通道是否在线 */
	UCHAR    unUsed[119];         
}IDM_DEV_ADDED_CHANNEL_S;

typedef struct tagIDM_DEV_QUERY_DEV_INFO
{
	CHAR    szDeviceID[64];      /* 设备ID */
	CHAR    szName[128];         /* 设备名称 */
	CHAR    szIPAddress[64];     /* 设备IP */
	ULONG   ulTotalChannelNum;   /* 远程通道总数 */

	ULONG  ulAddedChannelNum;    /* 已添加的设备通道数量*/
	IDM_DEV_ADDED_CHANNEL_S *    pstAddedChannelList; /*已添加的设备通道列表*/

	USHORT  usPort;                 /* 设备端口 */
	UCHAR   ucIsOnline;             /* 设备是否在线 0-离线 1-在线*/
	UCHAR   ucProtocol;             /* 接入协议 */

	CHAR    szUserName[64];          /* 用户名*/
	CHAR    szPassword[64];          /* 密码*/
	CHAR    szDeviceType[32];        /* 设备型号*/
	CHAR    szDevRegID[32];          /* 设备注册ID 国标接入必选*/
	CHAR    szMainURL[256];          /* RTSP接入时主码流URL */
	CHAR    szSubURL[256];           /* RTSP接入时子码流URL */

	USHORT   usHTTPPort;             /* HTTP服务端口 */
	USHORT   usHTTPSPort;            /* HTTPS服务端口 */
	USHORT   usRTSPPort;             /* RTSP服务端口 */
	UCHAR    ucTransProtocol;        /* 网络传输协议 */
	UCHAR    ucSecurity;               /* 密码等级 0-弱密码 1-中密码 2-强密码*/
	UCHAR    unUsed[40];
}IDM_DEV_QUERY_DEV_INFO_S;

/* netsdk事件通知类型 */
typedef enum emIDM_EVENT_TYPE
{
	EVENT_ALL         = 0x0006,  /* 所有事件 暂时不支持 */
	EVENT_NET_CLOSE   = 0x0007,  /* 实况网络关闭 */
	EVENT_NET_FAIL    = 0x0008,  /* 实况网络失败 */
	EVENT_NET_TIMEOUT = 0x0009,  /* 实况网络超时 */
	EVENT_NET_DONE    = 0x000A,  /* 实况完成 */

	EVENT_LIVE_CLOSE  = 0x0010,  /* 实况网络关闭 */
	EVENT_LIVE_FAIL   = 0x0011,  /* 实况网络失败 */
	EVENT_LIVE_TIMEOUT= 0x0012,  /* 实况网络超时 */
	EVENT_LIVE_DONE   = 0x0013,  /* 实况完成 */

	EVENT_VOD_CLOSE   = 0x0017, /* 回放网络关闭 */
	EVENT_VOD_FAIL    = 0x0018, /* 回放网络失败 */
	EVENT_VOD_TIMEOUT = 0x0019, /* 回放网络超时 */
	EVENT_VOD_DONE    = 0x001A, /* 回放完成 */

	/* 以下暂未支持 */
	EVENT_FILE_CLOSE  = 0x0020, /* 文件传输时 网络关闭 */
	EVENT_FILE_FAIL   = 0x0021, /* 文件传输时 网络失败 */
	EVENT_FILE_TIMEOUT= 0x0022, /* 文件传输时 网络超时 */
	EVENT_FILE_DONE   = 0x0023, /* 文件传输完成 */

	EVENT_VOICE_CLOSE = 0x0027, /* 语音对讲时 网络关闭 */
	EVENT_VOICE_FAIL  = 0x0028, /* 语音对讲时 网络失败 */
	EVENT_VOICE_TIMEOUT=0x0029, /* 语音对讲时 网络超时 */
	EVENT_VOICE_DONE  = 0x002A, /* 语音对讲完成 */
}IDM_EVENT_TYPE_EM_S;

typedef VOID(CALLBACK *IDM_DEV_EventNotify_Callback_PF)(
	LONG    lUserID,
	LONG    lHandle,
	VOID    *pUserData,
	int     emType,
	VOID    *param1,
	VOID    *param2
	);

/* 抓图计划时间段信息 */
typedef struct tagIDM_DEV_SNAP_TIME_SPAN
{
	ULONG   ulStructSize;                                  /* 当前结构体大小 */
	CHAR    szBeginTime[32];                               /* 开始时间，“HH:mm”格式，24小时制 */
	CHAR    szEndTime[32];                                 /* 结束时间，“HH:mm”格式，24小时制 */
	UCHAR   aucRes[32];
}IDM_DEV_SNAP_TIME_SPAN_S;

/* 抓图计划信息 */
typedef struct tagIDM_DEV_SCHEDULE
{
	ULONG   ulStructSize;                                  /* 当前结构体大小 */
	ULONG   ulDayNum;                                      /* 抓图计划天数 */
	ULONG   aulDayNo[31];                                  /* 天序号列表，如果是天计划，固定为1，如果是周计划代表星期几，
														   从1-7代表星期一到星期天；如果是月计划代表是当月的几号，取值从1-31，
														   不到31天的月份最后不存在的那几天的时间段计划忽略；
														   注意：天序号不能重复
														   */
	ULONG   ulTimeSpanNum;                                 /* 时间段的个数 */
	IDM_DEV_SNAP_TIME_SPAN_S* pstTimeSpan;                 /* 抓图计划时间段信息 */
	UCHAR   aucRes[32];
}IDM_DEV_SCHEDULE_S;

/* 抓图计划通道配置信息 */
typedef struct tagIDM_DEV_CHANNEL_SNAP_PLAN
{
	ULONG   ulStructSize;                                  /* 当前结构体大小 */
	ULONG   ulChannelNo;                                   /* 通道号，从0开始 */
	UCHAR   ucStreamType;                                  /* 流类型 */
	UCHAR   aucRes[63];
}IDM_DEV_CHANNEL_SNAP_PLAN_S;


/*  公有云解析任务抓图计划任务信息 */
typedef struct tagIDM_DEV_SNAP_TASK_INFO
{
	ULONG   ulStructSize;                                  /* 当前结构体大小 */
	CHAR    szTaskID[64];                                  /* 抓图计划任务id */
	ULONG   ulChannelInfoNum;                              /* 抓图计划通道配置信息个数 */
	IDM_DEV_CHANNEL_SNAP_PLAN_S* pstChannelSnapPlan;       /* 抓图计划通道配置信息 */
	ULONG   ulCaptureInterval;                             /* 抓拍时间间隔，单位：ms */
	ULONG    ulScheduleNum;                                 /* 总共有多少计划 */
	IDM_DEV_SCHEDULE_S* pstSchedule;                       /* 每一计划的抓图计划信息 */
	UCHAR   ucSecheduleType;                               /* 计划类型1：天计划；2：周计划；3：月计划*/
	UCHAR   ucPlanEnable;                                  /* 计划是否使能，0-不使能，1-使能 */
	UCHAR   aucRes[62];
}IDM_DEV_SNAP_TASK_INFO_S;

/* 公有云解析任务抓图计划结构体 */
typedef struct tagIDM_DEV_ANALISYS_TASK_SNAP_PLAN
{
	ULONG   ulStructSize;                                  /* 当前结构体大小 */
	ULONG   ulTaskInfoNum;                                 /* 任务个数 */
	IDM_DEV_SNAP_TASK_INFO_S* pstSnapTaskInfo;             /* 抓图计划通道配置信息 */
	UCHAR   aucRes[64];
}IDM_DEV_ANALISYS_TASK_SNAP_PLAN_S;

/* 公有云解析任务抓图计划任务ID信息 */
typedef struct tagIDM_DEV_TASK_ID_INFO
{
	CHAR    szTaskID[64];                                  /* 抓图计划任务id */
	UCHAR   ucEnable;                                      /* 是否使能，0-否，1-是（该字段用于设置抓图任务使能状态接口）*/
	UCHAR   ucRes[3];                                      /* 预留*/
}IDM_DEV_TASK_ID_INFO_S;

/* 公有云解析任务抓图计划任务ID列表结构体 */
typedef struct tagIDM_DEV_TASK_ID
{
	ULONG   ulTaskIDNum;                                   /* 抓图计划任务id的个数（用于公有云解析任务抓图计划时，当个数为0时，代表查询所有任务） */
	IDM_DEV_TASK_ID_INFO_S*    pstTaskID;                  /* 抓图计划任务id信息 */
}IDM_DEV_TASK_ID_S;

/* 启动抓拍图片批量流式下载参数结构体 */
typedef struct tagIDM_DEV_SAP_PIC_BATCH_DOWONLOAD
{
	ULONG   ulStructSize;               /* 当前结构体大小 */
	ULONG   ulChannelNo;                /* 通道号，从0开始 */
	ULONG   ulAlgoType;                 /* 算法类型：2-人脸识别；6-视频结构化；15-卡口智能；16-电警智能；39-全目标识别（全结构化） */
	ULONG   ulDataType;                 /* 数据类型。当ulAlgoType=2时：0-所有，1-无库人脸，2-有库人脸
										当ulAlgoType=6时：0-所有，3-行人，4-机动车，5-非机动车
										当ulAlgoType=15或16时：取值为交通行业/违法事件类型
										当ulAlgoType=39时：0-所有，1-无库人脸，2-有库人脸，3-行人，4-机动车，5-非机动车
										*/
	ULONG   ulFaceLibNo;                /* 人脸库编号，当（ulAlgoType为2或39）且（ulDataType为0或2）时，本字段必填 */
	CHAR    szStartTime[64];            /* 开始时间，ISO8601格式 */
	CHAR    szEndTime[64];              /* 结束时间，ISO8601格式 */
	UCHAR   aucRes[64];
}IDM_DEV_SAP_PIC_BATCH_DOWONLOAD_S;

/* 启动抓拍图片批量流式下载返回结果结构体 */
typedef struct tagIDM_START_PIC_DOWNLOAD_RESULT
{
	ULONG   ulStructSize;               /* 当前结构体大小 */
	CHAR    szPicDownloadSessionID[64]; /* 抓图批量下载会话ID */
	ULONG   ulTotalPicNum;              /* 满足条件的图片总张数 */
	UCHAR   aucRes[32];
}IDM_START_PIC_DOWNLOAD_RESULT_S;

/* 单个/批量文件下载文件信息 */
typedef struct tagIDM_FILES_INFO
{
	ULONG   ulStructSize;               /* 当前结构体大小 */
	ULONG   ulFileID;                   /* 文件id标识，根据业务需要填写，没有明确要求不填写 */
	CHAR    szFileName[256];            /* 文件名 */
	UCHAR   aucRes[128];
}IDM_FILES_INFO_S;

/* 单个/批量文件下载结构体 */
typedef struct tagIDM_DOWNLOAD_FILES
{
	ULONG   ulStructSize;               /* 当前结构体大小 */
	ULONG   ulSrvType;                  /* 业务类型：0-通用文件上传 1-配置文件上传 2-算法包文件上传 3-音频播报文件上传 4-设备升级包上传 100-通用文件下载 101-配置文件下载 102-算法包文件下载 999-所有 */
	CHAR    szSrcPath[256];             /* 服务下载文件所在路径，如果业务类型隐含下载路径，则不需要填写 */
	ULONG   ulFilesInfoNum;             /* 文件信息的个数 */
	IDM_FILES_INFO_S *pstFilesInfo;     /* 文件信息 */
	UCHAR   aucRes[256];
}IDM_DOWNLOAD_FILES_S;

/* 图片流批量下载进度结构体 */
typedef struct tagIDM_SNAP_PIC_DOWNLOAD_PROGRESS
{
	ULONG    ulStructSize;                                      /* 当前结构体大小 */
	INT      iProgress;                                         /* 图片流批量下载进度[0-100] */
	INT      iCurrentNum;                                       /* 图片已下载数量 */
	INT      iCountFail;                                        /* 下载失败图片数量 */
	UINT     uiNameLength;                                      /* 文件名称长度 */
	CHAR     *pNamesFail;                                       /* 下载失败图片名称 以,隔开 */
	UCHAR    aucRes[8];
}IDM_SNAP_PIC_DOWNLOAD_PROGRESS_S;

typedef struct tagIDM_DEV_UPGRADE_REQUEST
{
	CHAR szImageName[128];         /*升级镜像包名称*/
	CHAR szImageUrl[256];          /*升级镜像下载URL地址*/
	LLONG ulImageSize;            /*镜像包大小 单位字节*/
	UCHAR unUsed[120];
}IDM_DEV_UPGRADE_REQUEST_S;

typedef struct tagIDM_DEV_UPGRADE_SESSION
{
	CHAR  szUpgradeSessionID[64];    /*升级回话ID*/
	UCHAR unused[64];
}IDM_DEV_UPGRADE_SESSION_S;

typedef struct tagIDM_DEV_UPGRADE_STATUS
{
	USHORT usRate;                  /*升级进度 0-100*/
	UCHAR  ucUpgradeStatus;         /*升级状态 0-空闲 1-升级初始化中 2-文件上传中 3-下载中 4-成功 5-失败*/
	UCHAR  unused[13];
}IDM_DEV_UPGRADE_STATUS_S;

typedef struct tagIDM_DEV_SAVE_DATA_INFO
{
	UINT  uFileTime;                /*录制文件时长 大于0有效 单位秒*/
	UINT  uFileSize;                /*录制文件大小 大于0有效 单位字节*/
	CHAR  szFileName[256];          /*录制文件名称 包含路径 */
}IDM_DEV_SAVE_DATA_INFO_S;


typedef VOID(CALLBACK *IDM_DEV_LogCallback) (UCHAR level, const CHAR*logMsg);

typedef struct tagIDM_DEV_WGET_IMAGE
{
	UINT uiChannelNo;                       /* 通道号 */
	CHAR szImgUrl[256];                     /* 图片URL */
    UCHAR ucImgDomainLevel;                 /* 待检索的图片所属域级别， 0-本级域(本地)，1-1级域(远程)，当前最大支持1级 */
	UCHAR szUnused[251];
}IDM_DEV_WGET_IMAGE_S;

typedef struct tagIDM_DEV_IMAGE_RESPONSE
{
	UINT uiImgWidth;                          /* 图片宽度 */
	UINT uiImgHeight;                         /* 图片高度 单位像素 */
	CHAR szImgFormat[16];                     /* 图片格式*/
	UINT uiImgSize;                           /* 图片数据大小 */
	UCHAR *pucImgBuffer;                        /* 图片数据  消息头中二进制数据 子类型为100标识一般图片 */
	UCHAR unUsed[224];
}IDM_DEV_IMAGE_RESPONSE_S;

/* 证书初始化结构体  在启动主动注册服务时提供 */
typedef struct tagIDM_DEV_CERTIFICATE_INFO
{
	UINT    uiRootCertLength;                       /* 根证书数据长度 */
	UCHAR   *pucRootCertData;                       /* 根证书数据 */
	UINT    uiPlatformCertLength;                   /* 平台证书数据长度 */
	UCHAR   *pucPlatformCertData;                   /* 平台证书数据 */
	UINT    uiPrivateKeyLength;                     /* 平台私钥数据长度 */
	UCHAR   *pucPrivateKeyData;                     /* 平台私钥数据 */
	UCHAR   aucRes[90];
}IDM_DEV_CERTIFICATE_INFO_S;

#ifndef CONST
#define CONST const
#endif
/* 周界配置参数 */
typedef struct tagIDM_DEV_PERIMETER_PARAM
{
	UINT        uiChipNo;                           /* [可选]请求参数 芯片ID  EC用 0开始 暂未使用*/
	UCHAR       ucMode;                             /*       请求参数 周界检测模式 0-入侵 1-进入 2-离开 */

	UCHAR       ucEnabled;                          /* 是否启用检测并上报 0-静默不上报 1-正常工作 */
	USHORT      usMinTime;                          /* 最短停留时间 1-100s 区域入侵时 该参数必填 */
	USHORT      usMaxRegionNum;                     /* 规则框最大个数 */
	USHORT      usMinRegionNum;                     /* 规则框最小个数 */
	USHORT      usMaxPointNum;                      /* 规则框最大点数 默认10 */
	USHORT      usMinPointNum;                      /* 规则框最小点数 默认3 */
	IDM_DEV_POINT_S astMinSizeRegion[4];            /* 最小尺寸规则框 顺时针 4坐标点 */
	IDM_DEV_POINT_S astMaxSizeRegion[4];            /* 最大尺寸规则框 顺时针 4坐标点 */
	IDM_DEV_POINTREGION_S astRegionList[4];              /* 区域规则列表 最多支持4个 */
	UINT        uiRegionNum;                       /* 区域规则列表长度 */
	UCHAR       ucIsDetectPerson;                   /* 是否检测行人 */
	UCHAR       ucIsDetectNonVehicle;               /* 是否检测行非机动车 */
	UCHAR       ucIsDetectVehicle;                  /* 是否检测行机动车 */
	USHORT      ausRes[253];
}IDM_DEV_PERIMETER_PARAM_S;

typedef struct tagIDM_UNI_ALGO_OP
{
	UINT  uiChannelNo;            /* 请求参数- 通道号 默认填0 */
	UCHAR ucOpType;               /* 请求参数- 操作类型  0-关闭  1-启动  2-获取状态 */
	UCHAR ucIsRunning;            /* ucOpType为2时 本字段填充查询到的算法状态 其余操作无效 */
	UCHAR ucUnUsed[250];
}IDM_UNI_ALGO_OP;

/** 重置用户密码 **/
typedef struct tagIDM_DEV_RESET_PASSWORD
{
    CHAR   szUserName[64];                               // 用户名 
    CHAR   szNewPassword[64];                            // 新密码
    CHAR   szOldPassword[64];                            // 旧密码
}IDM_DEV_RESET_PASSWORD_S;

/* 函数接口 */
#ifdef __cplusplus
extern "C"{
#endif

/*
*@brief: 获取SDK版本号
*@return: 版本号
*/
IDM_API LONG IDM_DEV_GetSDKVersion();

/*
*@brief: SDK初始化
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_Init();

/*
*@brief: SDK反初始化
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_Cleanup();

/*
*@brief: 设置保存日志到文件, 会自动添加输出到文件模式.
*@param: IN ucLogLevel 日志等级  0-关闭日志 1-error级别 2-info级别 3-debug级别
*@param: IN ucLogMode 日志存储模式 未实现 填0
*@param: IN szLogDirectory 日志文件路径  比如 C:\\logs  或者 . 
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_SaveLogToFile(UCHAR ucLogLevel, UCHAR ucLogMode,CHAR *szLogDirectory);


/*
*@brief: 设置日志输出模式
*@param: IN mode 日志输出模式 0关闭,1输出到命令行,2输出到文件(需要先配置文件信息),4输出到调试窗口(windows有效),8使用回调(需要设置回调)
*@return: 无
*/
IDM_API VOID IDM_DEV_SetLogOutputMode(UCHAR mode);


/*
*@brief: 设置日志回调(会自动添加输出到日志文件模式)
*@param: IN mode 0关闭,1输出到命令行,2输出到文件(需要先配置文件信息),4输出到调试窗口(windows有效),8使用回调(需要设置回调)
*@return: 无
*/
IDM_API VOID IDM_DEV_SetLogCallback(IDM_DEV_LogCallback callback);

/*
*@brief: 设置日志输出模式
*@param: IN level 日志等级  0-关闭日志 1-error级别 2-info级别 3-debug级别
*@return: 无
*/
IDM_API VOID IDM_DEV_SetLogLevel(UCHAR level);


/*
*@brief: 设置异常消息接收回调函数
*@param: IN pfExceptionCallback 异常消息回调函数
*@param: IN pUserData 用户数据
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_SetExceptionCallback(IDM_DEV_Exception_Callback_PF pfExceptionCallback, VOID *pUserData);

/*
*@brief: 设备登录
*@param: IN stLoginInfo 登录结构体
*@param: OUT pstDeviceInfo 设备信息
*@param: OUT plUserID 登录成功分配的设备句柄
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_Login(IDM_DEV_USER_LOGIN_INFO_S stLoginInfo, IDM_DEV_DEVICE_INFO_S *pstDeviceInfo, LONG *plUserID);

/*
*@brief: 设备登出
*@param: IN lUserID 设备句柄
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_Logout(LONG lUserID);

/*
*@brief: 设备实时预览
*@param: IN lUserID 设备句柄
*@param: IN stPreviewInfo 预览参数结构体
*@param: IN pfRealPlayCallBack 预览数据回调函数
*@param: IN pUserData 用户数据
*@param: OUT plRealPlayHandle 预览句柄
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_RealPlay(LONG lUserID, IDM_DEV_PREVIEW_INFO_S stPreviewInfo, IDM_DEV_RealPlay_Callback_PF pfRealPlayCallBack, VOID *pUserData, LONG *plRealPlayHandle);

/*
*@brief: 设备实时预览
*@param: IN lUserID 设备句柄
*@param: IN sPreviewInfo 预览参数结构体
*@param: IN pfRealPlayCallBack 预览数据回调函数
*@param: IN pUserData 用户数据
*@param: OUT plRealPlayHandle 预览句柄
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_RealPlayES(LONG lUserID, IDM_DEV_PREVIEW_INFO_S sPreviewInfo, IDM_DEV_RealPlayES_Callback_PF pfRealPlayCallBack, VOID *pUserData, LONG *plRealPlayHandle);

/*
*@brief: 停止实时预览
*@param: IN lRealPlayHandle 预览句柄
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_StopRealPlay(LONG lRealPlayHandle);

/*
*@brief: 设置实时预览回调函数
*@param: IN lRealPlayHandle 预览句柄
*@param: IN pfRealPlayCallback 预览数据回调函数
*@param: IN pUserData 用户数据
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_SetRealPlayCallback(LONG lRealPlayHandle, IDM_DEV_RealPlay_Callback_PF pfRealPlayCallback, VOID *pUserData);

/*
*@brief: 设置实时预览回调函数(ES流)
*@param: IN lRealPlayHandle 预览句柄
*@param: IN pfRealPlayCallback 预览数据回调函数
*@param: IN pUserData 用户数据
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_SetRealPlayESCallback(LONG lRealPlayHandle, IDM_DEV_RealPlayES_Callback_PF pfRealPlayCallback, VOID *pUserData);

/*
*@brief: 保存实时流到文件
*@param: IN lRealPlayHandle 预览句柄
*@param: IN pcFileName 保存的文件路径
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_SaveRealPlayData(LONG lRealPlayHandle, CHAR* pcFileName);

/*
*@brief: 停止保存实时流到文件
*@param: IN lRealPlayHandle 预览句柄
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_StopSaveRealPlayData(LONG lRealPlayHandle);

/*
*@brief: 录像回放
*@param: IN lUserID 设备句柄
*@param: IN stPlayBackCond 录像查询条件
*@param: IN pfPlayBackCallback 回放数据回调函数
*@param: IN pUserData 用户数据
*@param: OUT lPlayBackHandle 回放句柄
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_PlayBack(LONG lUserID, IDM_DEV_PLAYBACK_COND_S stPlayBackCond, IDM_DEV_PlayBack_Callback_PF pfPlayBackCallback, VOID* pUserData, LONG* plPlayBackHandle);

/*
*@brief: 停止录像回放
*@param: IN lPlayBackHandle 回放句柄
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_StopPlayBack(LONG lPlayBackHandle);

/*
*@brief: 设置录像回放回调函数
*@param: IN lPlayBackHandle 回放句柄
*@param: IN pfPlayBackCallback 回放数据回调函数
*@param: IN pUserData 用户数据
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_SetPlayBackCallback(LONG lPlayBackHandle, IDM_DEV_PlayBack_Callback_PF pfPlayBackCallback, VOID* pUserData);

/*
*@brief: 回放控制
*@param: IN lPlayBackHandle 回放句柄
*@param: IN ulCommand 命令号
*@param: IN pBuffer 参数指针，根据命令号对应不同结构体
*@param: IN ulBufferSize 参数长度
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_PlayBackControl(LONG lPlayBackHandle, ULONG ulCommand, VOID* pBuffer, ULONG ulBufferSize);

/*
*@brief: 保存回放流到文件
*@param: IN lPlayBackHandle 回放句柄
*@param: IN pcFileName 保存的文件路径
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_SavePlayBackData(LONG lPlayBackHandle, CHAR* pcFileName);
/*
*@brief: 停止保存回放流到文件
*@param: IN lPlayBackHandle 回放句柄
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_StopSavePlayBackData(LONG lPlayBackHandle);

/*
*@brief: 按条件查询录像文件
*@param: IN lUserID 设备句柄
*@param: IN stFileCond 查找条件
*@param: OUT pstFileResult 查找结果
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_FindFile(LONG lUserID, IDM_DEV_FILE_COND_S stFileCond, IDM_DEV_FILE_RESULT_S* pstFileResult);

/*
*@brief: 按条件查询录像文件
*@param: IN lUserID 设备句柄
*@param: IN stFileCond 查找条件
*@param: OUT pstFileResult 查找结果
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_FindFile_Ex(LONG lUserID, IDM_DEV_FILE_COND_EX_S stFileCond, IDM_DEV_FILE_RESULT_S* pstFileResult);

/*
*@brief: 按文件名设置录像锁定状态
*@param: IN lUserID 设备句柄
*@param: IN sFileName 需要设置的录像文件名
*@param: IN ulLockStatus 锁定状态 0：未锁定，1：锁定
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_SetFileLockStatus(LONG lUserID, CHAR* sFileName, ULONG ulLockStatus);

/*
*@brief: 按文件名获取录像锁定状态
*@param: IN lUserID 设备句柄
*@param: IN sFileName 需要获取的录像文件名
*@param: OUT pulLockStatus 锁定状态 0：未锁定，1：锁定
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_GetFileLockStatus(LONG lUserID, CHAR* sFileName, ULONG* pulLockStatus);

/*
*@brief: 录像月历查询
*@param: IN lUserID 设备句柄
*@param: IN stSearchParam 查询条件结构体
*@param: OUT psetResult 查询结果结构体
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_GetMonthlyRecord(LONG lUserID, IDM_DEV_MRD_SEARCH_PARAM_S stSearchParam, IDM_DEV_MRD_SEARCH_RESULT_S* psetResult);

/*
*@brief: 录像月历查询
*@param: IN lUserID 设备句柄
*@param: IN stSearchParam 查询条件结构体
*@param: OUT psetResult 查询结果结构体
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_GetMonthlyRecord_Ex(LONG lUserID, IDM_DEV_MRD_SEARCH_PARAM_EX_S stSearchParam, IDM_DEV_MRD_SEARCH_RESULT_S* psetResult);

/*
*@brief: 录像文件下载
*@param: IN lUserID 设备句柄
*@param: IN pstDownloadCond 录像下载条件
*@param: IN pcSavedFileName 下载后保存的文件名(包含路径)
*@param: OUT plFileHandle 文件句柄
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_DownloadFile(LONG lUserID, IDM_DEV_PLAYBACK_COND_S *pstDownloadCond, const CHAR *pcSavedFileName, LONG* plFileHandle);

/*
*@brief: 录像文件下载
*@param: IN lUserID 设备句柄
*@param: IN pstDownloadCond 录像下载条件
*@param: IN pfDownloadCallback 录像下载以帧模式的回调函数
*@param: IN pcSavedFileName 下载后保存的文件名(包含路径),普通下载模式
*@param: OUT plFileHandle 文件句柄
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_DownloadFile_Ex(LONG lUserID, IDM_DEV_PLAYBACK_COND_S *pstDownloadCond, IDM_DEV_Download_Callback_PF pfDownloadCallback, const CHAR *pcSavedFileName, VOID* pUserData, LONG* plFileHandle);

/*
*@brief: 设置录像文件下载回调函数
*@param: IN lPlayBackHandle 录像文件下载句柄
*@param: IN pfVodDownloadFileCallback 录像文件下载数据回调函数
*@param: IN pUserData 用户数据
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_DownloadFileData(LONG lUserID, IDM_DEV_PLAYBACK_COND_S *pstDownloadCond, IDM_DEV_Download_Callback_PF pfDownloadCallback, VOID* pUserData, LONG* plFileHandle);

/*
*@brief: 停止录像文件下载
*@param: IN lFileHandle 文件句柄
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_StopDownloadFile(LONG lFileHandle);

/*
*@brief: 查询录像文件下载进度
*@param: IN lFileHandle 文件句柄
*@param: OUT total_len  文件的总大小(若该值为0，则标识正在请求中)
*@param: OUT down_len   已下载大小
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_GetDownloadProgress(LONG lFileHandle, LLONG *total_len, LLONG *down_len);

/*
*@brief: 云台控制
*@param: IN lUserID 设备句柄
*@param: IN ulChannel 通道号
*@param: IN ulCommand 命令号
*@param: IN pBuffer 参数指针，根据命令号对应不同结构体
*@param: IN ulBufferSize 参数长度
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_PTZControl(LONG lUserID, ULONG ulChannel, ULONG ulCommand, VOID* pBuffer, ULONG ulBufferSize);

/*
*@brief: 系统控制
*@param: IN lUserID 设备句柄
*@param: IN ulChannel 通道号
*@param: IN ulCommand 命令号
*@param: IN pBuffer 参数指针，根据命令号对应不同结构体
*@param: IN ulBufferSize 参数长度
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
//IDM_API LONG IDM_DEV_SystemControl(LONG lUserID, ULONG ulChannel, ULONG ulCommand, VOID* pBuffer, ULONG ulBufferSize);

/*
*@brief: 设置报警布防回调函数
*@param: IN ulIndex 布防回调函数索引 暂不支持多个回调 默认0
*@param: IN pfAlarmCallback 报警消息回调函数
*@param: IN pUserData 用户数据
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_SetAlarmCallback(ULONG ulIndex, IDM_DEV_Message_Callback_PF pfAlarmCallback, VOID *pUserData);

/*
*@brief: 建立报警布防上传通道
*@param: IN lUserID 设备句柄
*@param: IN stAlarmParam 报警布防参数
*@param: OUT plAlarmHandle 布防句柄
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_StartAlarmUp(LONG lUserID, IDM_DEV_ALARM_PARAM_S stAlarmParam, LONG *plAlarmHandle);

/*
*@brief: 撤销已建立的布防通道
*@param: IN lAlarmHandle 布防句柄
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_StopAlarmUp(LONG lAlarmHandle);

/*
*@brief: 开启报警监听
*@param: IN pcIP 设备句柄
*@param: IN usPort 报警布防参数
*@param: IN pfListenCallback 报警消息回调函数
*@param: IN pUserData 用户数据
*@param: OUT plListenHandle 监听句柄
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
//IDM_API LONG IDM_DEV_StartListen(CHAR* pcIP, USHORT usPort, IDM_DEV_Message_Callback_PF pfListenCallback, VOID* pUserData, LONG* plListenHandle);

/*
*@brief: 停止报警监听
*@param: IN lListenHandle 监听句柄
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
//IDM_API LONG IDM_DEV_StopListen(LONG lListenHandle);

/*
*@brief: 获取设备参数
*@param: IN lUserID 设备句柄
*@param: IN ulCommand 设备配置命令
*@param: IN ulChannel 通道号
*@param: OUT pBuffer 接收数据的缓冲指针
*@param: IN ulBufferSize 接收数据的缓冲长度
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_GetConfig(LONG lUserID, ULONG ulCommand, ULONG lChannel, VOID* pBuffer, ULONG ulBufferSize);

/*
*@brief: 设置设备参数
*@param: IN lUserID 设备句柄
*@param: IN ulCommand 设备配置命令
*@param: IN ulChannel 通道号
*@param: IN pBuffer 输入数据的缓冲指针
*@param: IN ulBufferSize 输入数据的缓冲长度
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_SetConfig(LONG lUserID, ULONG ulCommand, ULONG ulChannel, VOID* pBuffer, ULONG ulBufferSize);

/*
*@brief: 批量获取设备配置
*@param: IN lUserID 设备句柄
*@param: IN ulCommand 命令号
*@param: IN ulCount 命令号
*@param: IN pInBuffer 输入参数指针，根据命令号对应不同结构体
*@param: IN ulInBufferSize 输入参数长度
*@param: OUT pOutBuffer 输出参数指针，根据命令号对应不同结构体
*@param: OUT ulOutBufferSize 输出参数长度
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_GetMultipleConfig(LONG lUserID, ULONG ulCommand, ULONG ulCount, VOID* pInBuffer, ULONG ulInBufferSize,VOID* pOutBuffer, ULONG ulOutBufferSize);

/*
*@brief: 批量设置设备配置
*@param: IN lUserID 设备句柄
*@param: IN ulCommand 命令号
*@param: IN pInBuffer 输入参数指针，根据命令号对应不同结构体
*@param: IN ulInBufferSize 输入参数长度
*@param: OUT pOutBuffer 输出参数指针，根据命令号对应不同结构体
*@param: OUT ulOutBufferSize 输出参数长度
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_SetMultipleConfig(LONG lUserID, ULONG ulCommand, ULONG ulCount, VOID* pInBuffer, ULONG ulInBufferSize,VOID* pOutBuffer, ULONG ulOutBufferSize);

/*
*@brief: 获取设备能力集
*@param: IN lUserID 设备句柄
*@param: IN ulAbilityType 能力集类型
*@param: IN pcInBuffer 输入数据指针
*@param: IN ulInLength 输入数据长度
*@param: OUT pcOutBuffer 输出数据指针
*@param: OUT ulOutLength 输出数据长度
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_GetAbility(LONG lUserID, ULONG ulAbilityType, CHAR* pcInBuffer, ULONG ulInLength, CHAR* pcOutBuffer, ULONG ulOutLength);

/*
*@brief: 获取设备状态
*@param: IN lUserID 设备句柄
*@param: IN ulCommand 命令号
*@param: IN pcInBuffer 输入数据指针
*@param: IN ulInLength 输入数据长度
*@param: OUT pcOutBuffer 输出数据指针
*@param: OUT ulOutLength 输出数据长度
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
//IDM_API LONG IDM_DEV_GetStatus(LONG lUserID, ULONG ulCommand, CHAR* pcInBuffer, ULONG ulInLength, CHAR* pcOutBuffer, ULONG ulOutLength);

/*
*@brief: 设备远程升级
*@param: IN lUserID 设备句柄
*@param: IN stUpgradeParam 升级参数
*@param: OUT plUpgradeHandle 升级句柄
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
//IDM_API LONG IDM_DEV_StartUpgrade(LONG lUserID, IDM_DEV_UPGRADE_PARAM_S stUpgradeParam, LONG* plUpgradeHandle);

/*
*@brief: 停止设备远程升级，并释放资源
*@param: IN lUpgradeHandle 升级句柄
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
//IDM_API LONG IDM_DEV_StopUpgrade(LONG lUpgradeHandle);

/*
*@brief: 获取升级信息
*@param: IN lUpgradeHandle 升级句柄
*@param: OUT pstUpgradeInfo 升级信息
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
//IDM_API LONG IDM_DEV_GetUpgradeInfo(LONG lUpgradeHandle, IDM_DEV_UPGRADE_INFO_S* pstUpgradeInfo);

/*
*@brief: 日志查询
*@param: IN lUserID 设备句柄
*@param: IN stLogCond 日志查询条件
*@param: OUT lLogHandle 日志查询句柄
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
//IDM_API LONG IDM_DEV_StartSearchLog(LONG lUserID, IDM_DEV_LOG_COND_S stLogCond, LONG* plLogHandle);

/*
*@brief: 停止日志查询，并释放资源
*@param: IN lLogHandle 日志查询句柄
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
//IDM_API LONG IDM_DEV_StopSearchLog(LONG lLogHandle);

/*
*@brief: 查询下条日志信息
*@param: IN lLogHandle 日志查询句柄
*@param: OUT pstLogData 日志信息
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
//IDM_API LONG IDM_DEV_SearchNextLog(LONG lLogHandle, IDM_DEV_LOG_DATA_S* pstLogData);

/*
*@brief: REST API透传
*@param: IN lUserID 设备句柄
*@param: IN pstRequest 请求参数
*@param: OUT pstResponse 响应参数
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_TransRestApi(LONG lUserID, IDM_DEV_REQUEST_PARAM_S *pstRequest, IDM_DEV_RESPONSE_PARAM_S *pstResponse);

/*
*@brief: 名单库库配置
*@param: IN lUserID 设备句柄
*@param: IN stParamIn 输入名单库操作信息
*@param: OUT pstParamOut 输出名单库操作结果信息
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_RepositoryOpt(LONG lUserID, IDM_DEV_REPOSITORY_OPT_PARAM_S stParamIn, IDM_DEV_REPOSITORY_OPT_PARAMOUT_S *pstParamOut);
/*
*@brief: 名单库库内容配置
*@param: IN plRepoHandle 通过IDM_DEV_RepositoryOpt加载名单库返回的句柄
*@param: IN stParam 输入命令和对应参数的结构体
*@param: OUT pszResult 输出操作结果JSON字符串数据的缓冲指针
*@param: OUT pulResultSize 输出数据的缓冲长度
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_RepositoryControl(LONG lRepoHandle, IDM_REPOSITORY_CONTROL_PARAM_S stParam, IDM_REPOSITORY_CONTROL_RESULT_S *pstResult);

/*
*@brief: 手动抓拍透传
*@param: IN lUserID 设备句柄
*@param: IN pInter 抓拍参数
*@param: OUT pOuter 响应参数
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_ManualSnap(LONG lUserID, IDM_DEV_MANUALSNAP_S *pInter, IDM_DEV_MANUALSNAP_RESULT_S *pOuter);

/*
*@brief: 手动抓拍牌识
*@param: IN lUserID 设备句柄
*@param: IN pInter 抓拍参数
*@param: OUT pOuter 响应参数
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_ManualSnap_Ex(LONG lUserID, IDM_DEV_MANUALSNAP_EX_S *pInter, IDM_DEV_MANUALSNAP_RESULT_EX_S *pOuter);

/*
*@brief: 启动搜索服务
*@param: IN pfSearchCallback 搜索结果回调函数
*@param: IN pUserData 用户数据
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_StartSearchDevices(IDM_DEV_SearchDevice_Callback_PF pfSearchCallback, VOID* pUserData);

/*
*@brief: 停止搜索服务
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_StopSearchDevices();

/*
*@brief: 通过IP搜索设备
*@param: IN pfSearchCallback 搜索结果回调函数
*@param: IN pUserData 用户数据
*@param: IN sDevIP 设备IP地址
*@param: IN usDevPort 设备端口号
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_SearchDevice(IDM_DEV_SearchDevice_Callback_PF pfSearchCallback, VOID* pUserData, CHAR* szIP, USHORT usPort);

/*
*@brief: 设备激活
*@param: IN sDevIP 设备IP地址
*@param: IN usDevPort 设备端口号
*@param: IN pActivateInfo 激活信息
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_ActivateDevice(CHAR* sDevIP, USHORT usDevPort, IDM_DEV_ACTIVATE_INFO_S *pActivateInfo);


/*
*@brief: 开启被动模式监听服务
*@param: IN usSerPort 监听端口
*@param: IN pUserData 回调函数返回的用户数据
*@param: IN pfConnectCallback 设备连接后从回调函数中返回
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_StartServer(USHORT usServerPort, VOID* pUserData, IDM_DEV_Connect_Callback_PF pfConnectCallback);

/*
*@brief: 关闭被动模式监听服务
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_StopServer();

/*
*@brief: 设置设备报警输出
*@param: IN lUserID 设备句柄
*@param: IN ulAlarmID 报警输出号
*@param: IN ulAlarmOutStatus 0-停止输出，1-输出
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_SetAlarmOut(LONG lUserID, ULONG ulAlarmID, ULONG ulAlarmOutStatus);

/*
*@brief: 设置设备报警输出
*@param: IN lUserID 设备句柄
*@param: IN pstAlarmControl 报警输出详细控制参数
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_SetAlarmOut_EX(LONG lUserID, IDM_DEV_ALARMOUT_CONTROL_S *pstAlarmControl);

/*
*@brief: 获取设备报警输出
*@param: IN lUserID 设备句柄
*@param: OUT pstAlarmOutStatus 报警输出状态
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_GetAlarmOut(LONG lUserID, IDM_DEV_ALARMOUT_STATUS_S *pstAlarmOutStatus);

/*
*@brief: 启动语音转发
*@param: IN lUserID 设备句柄
*@param: IN pstVoiceComInfo 语音转发参数
*@param: IN pfVoiceComCallback 音频数据回调函数
*@param: IN pUserData 用户数据指针
*@param: OUT plVoiceComHandle 语音转发句柄
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_StartVoiceCom(LONG lUserID, IDM_DEV_VOICECOM_INFO_S* pstVoiceComInfo, IDM_DEV_VoiceCom_Callback_PF pfVoiceComCallback, VOID* pUserData ,LONG* plVoiceComHandle);

/*
*@brief: 停止语音转发
*@param: IN plVoiceComHandle 语音转发句柄
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_StopVoiceCom(LONG lVoiceComHandle);

/*
*@brief: 转发语音数据
*@param: IN plVoiceComHandle 语音转发句柄
*@param: IN pSendBuf 存放语音数据的缓冲区
*@param: IN ulBufSize 语音数据大小
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_VoiceComSendData(LONG lVoiceComHandle, UCHAR* pSendBuf, ULONG ulBufSize);

/*
*@brief: 组播获取tcp/ip配置
*@param: IN DevSN 设备序列号
*@param: OUT psTCPIPConfig 组播获取ip配置结构体
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_GetTCPIPConfig(CHAR* DevSN, IDM_DEV_TCPIP_CFG_S* psTCPIPConfig);

/*
*@brief: 组播设置tcp/ip配置
*@param: IN psTriggerAlarmVoice 组播设置ip配置结构体
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_SetTCPIPConfig(IDM_DEV_TCPIP_CFG_S* psTCPIPConfig);

/*
*@brief: P2P穿网信息协商
*@param: IN lUsrID 设备句柄
*@param: IN psP2PThroughNet p2p穿网信息协商结构体
*@param: IN psP2PThroughResult p2p穿网信息协商返回结果结构体
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_P2PThroughNet(LONG lUserID, IDM_DEV_P2P_THROUGH_NET_S* psP2PThroughNet, IDM_DEV_P2P_THROUGH_RESULT_S* psP2PThroughResult);

/*   ----------------------------------------NOTE---------------------------------------------
*    1. 凡是响应结构体变量中 netsdk会动态开辟内存的都需要用户调用IDM_FREE   
*    2. IDM_FREE并不释放响应结构体变量本身的空间  需要用户自行管理
*    3. 响应结构体变量不要进行浅拷贝
*    4. 响应结构体变量
*    ____________________________
*/
/**
*@brief:  0. 释放结构体中的动态内存   
	IDM_FREE(&响应结构体变量);或者 IDM_DEV_Free(&响应结构体变量,sizeof(响应结构体变量));
释放内存时 传入结构体地址 将结构体中所有空间置0或者释放 防止野指针
凡是响应结构体中有动态内存的 都需要调用IDM_FREE释放内存
*@param:   pstResponse为需要释放动态内存的结构体首地址
*@param:   sizeOfstResponse结构体空间大小
*@return: 无返回值
**/
IDM_API VOID IDM_DEV_Free(VOID *pstResponse, ULONG sizeOfstResponse);
#define IDM_FREE(pstResponse) \
	IDM_DEV_Free((pstResponse),sizeof((*pstResponse))) 
/* 通用算法相关透传接口 */
/*
*@brief: 2.1 设备上通用化算法包结果建表规则查询 需要调用IDM_FREE(响应结构体地址)释放内存
*@param: IN  lUserID 设备句柄
*@param: IN  pstRequest 请求信息构成的结构体
*@param: OUT pstResponse 响应信息构成的结构体
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_UNI_QueryAlgoResultTableRules(LONG lUserID, IDM_UNI_TRANS_REQUEST_PARAM_S *pstRequest, IDM_UNI_TRANS_RESPONSE_PARAM_S *pstResponse);

/*  
*@brief: 2.2 设备上通用化算法包页面配置规则查询 需要调用IDM_FREE(结构体地址)释放内存
*@param: IN  lUserID 设备句柄
*@param: IN  pstRequest 请求信息构成的结构体
*@param: OUT pstResponse 响应信息构成的结构体
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_UNI_QueryAlgoConfigWebPage(LONG lUserID, IDM_UNI_TRANS_REQUEST_PARAM_S *pstRequest, IDM_UNI_TRANS_RESPONSE_PARAM_S *pstResponse);

/*
*@brief: 2.3 设置设备上通用算法配置规则参数 
*@param: IN  lUserID 设备句柄
*@param: IN  pstRequest 请求信息构成的结构体
*@param: OUT pstResponse 响应信息构成的结构体
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_UNI_SetAlgoRuleParam(LONG lUserID, IDM_UNI_TRANS_REQUEST_PARAM_S *pstRequest, IDM_UNI_TRANS_RESPONSE_PARAM_S *pstResponse);

/*
*@brief: 2.4 获取设备上通用算法配置规则参数 需要调用IDM_FREE(响应结构体地址)释放内存
*@param: IN  lUserID 设备句柄
*@param: IN  pstRequest 请求信息构成的结构体
*@param: OUT pstResponse 响应信息构成的结构体
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_UNI_GetAlgoRuleParam(LONG lUserID, IDM_UNI_TRANS_REQUEST_PARAM_S *pstRequest, IDM_UNI_TRANS_RESPONSE_PARAM_S *pstResponse);

/*
*@brief: 2.5 已安装算法的查询接口
*@note : 调用完成后需要调用IDM_FREE(响应结构体地址)释放内存
*@param: IN  lUserID   设备句柄
*@param: IN  ulChannel 编号 从0开始  无效值0xFFFF
*@param: OUT pstResponse 响应结构体
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_UNI_QueryInstalledAlgo(LONG lUserID, ULONG ulChannel, IDM_UNI_QUERY_INSTALLED_ALGO_RESPONSE_S *pstResponse);


/*
*@brief: 2.6 算法切换接口
*@param: IN  lUserID   设备句柄
*@param: OUT pstResponse 响应结构体
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_UNI_SwitchAlgo(LONG lUserID, IDM_UNI_SWITCH_ALGO_S *pstRequest);


/*
*@brief:  2.7 加载/升级/卸载算法版本接口
*@param: IN  lUserID 设备句柄
*@param: IN  pstRequest 请求信息构成的结构体
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_UNI_LoadAlgo(LONG lUserID, IDM_UNI_LOAD_ALGO_REQUEST_S * pstRequest);


/*
*@brief: 启动一键搜索添加设备
*@param: IN lUsrID 设备句柄
*@param: IN psStartDevAutoSearchAdd 启动一键搜索添加设备参数结构体
*@param: OUT lTaskID 启动一键搜索添加设备返回的任务ID,预留，当前只支持一个任务，任务id可以不带
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_StartDevAutoSearchAdd(LONG lUserID, IDM_DEV_START_DEV_AUTO_SEARCH_ADD_S* psStartDevAutoSearchAdd, LONG* lTaskID);

/*
*@brief: 查询一键搜索添加设备处理进度
*@param: IN lUsrID 设备句柄
*@param: OUT psQueryDevAutoAddProgress 查询一键搜索添加设备处理进度结构体
*@param: IN lTaskID 启动一键搜索添加设备返回的任务ID,预留，当前只支持一个任务，任务id可以不带
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_QueryDevAutoAddProgress(LONG lUserID, IDM_DEV_QUERY_DEV_AUTO_ADD_PROGRESS_S* psQueryDevAutoAddProgress, LONG lTaskID);


IDM_API LONG IDM_DEV_GetThransFileProgress(LONG lFileHandle, FLOAT *pfProgress);

/*
*@brief: 获取文件上传任务进度
*@param: IN taskId 任务id
*@param: OUT curSize 当成已经传输字节数
*@param: OUT totalSize 总文件字节数
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_GetTransFileProgress(LONG taskId, LONG *curSize, LONG *totalSize);

/*
*@brief: 创建文件上传输任务
*@param: IN lUsrID 设备句柄
*@param: IN TaskID 文件传输任务ID
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_DestroyFileTransTask(LONG lUserID, LONG TaskID);

/*
*@brief: 创建文件上传任务
*@param: IN lUsrID 设备句柄
*@param: IN psTransFileInfo 创建文件上传任务参数结构体
*@param: OUT plTaskID 创建文件上传任务返回任务ID
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_CreatUploadFileTask(LONG lUserID, IDM_DEV_TRANS_FILE_INFOS_S* psTransFileInfo, LONG* plTaskID);

/*
*@brief: 创建文件下载任务
*@param: IN lUsrID 设备句柄
*@param: IN psDownloadFileInfo 创建文件下载任务参数结构体
*@param: OUT plTaskID 创建文件下载任务返回任务ID
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_CreatDownloadFileTask(LONG lUserID, IDM_DEV_DOWNLOAD_FILE_INFO_S* psDownloadFileInfo, LONG* plTaskID);

/*
*@brief: 上传文件
*@param: IN lUsrID 设备句柄
*@param: IN pSendBuf 文件流数据缓冲区
*@param: IN ulBufSize 文件流数据大小
*@param: IN lTaskID  文件上传任务ID
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_UploadFile(LONG lUserID, UCHAR* pSendBuf, ULONG ulBufSize, LONG lTaskID);

/*
*@brief: 下载文件
*@param: IN lUsrID 设备句柄
*@param: IN pfDownloadFileCallback 文件下载回调函数
*@param: IN lTaskID  文件下载任务ID
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_DownloadFileS(LONG lUserID, IDM_DEV_TransFile_Callback_PF pfDownloadFileCallback, LONG lTaskID);

/*
*@brief: 手动触发语音播放
*@param: IN lUsrID 设备句柄
*@param: IN psTriggerAlarmVoice 触发语音播放结构体
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_TrrigerAlarmVoice(LONG lUserID, IDM_DEV_TRIGGER_ALARM_VOICE_S* psTriggerAlarmVoice);

/*
*@brief: 设置全局超时时间
*@param: IN lWaitTimems 超时时间单位ms(建议3000-5000)
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_SetGlobalWaitTime(INT lWaitTimems);


/*
*@brief: REST API透传V2
*@note : 请求结构体空间由用户自行管理   需要调用IDM_FREE(响应结构体地址)释放内存
*@param: IN lUserID 设备句柄
*@param: IN pstRequest 请求参数
*@param: OUT pstResponse 响应参数
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_TransRestApi_V2(LONG lUserID, IDM_DEV_REQUEST_PARAM_S *pstRequest, IDM_DEV_RESPONSE_PARAM_S *pstResponse);

/*
*@brief: 获取设备二维码
*@param: IN lUserID 设备句柄
*@param: OUT pstResponse 响应参数
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_GetQRCode(LONG lUserID, IDM_DEV_QR_RESPONSE_S *pstResponse);

/**
*@brief:  15. 查询设备信息    需要调用IDM_FREE(响应结构体地址)释放动态内存
*@param: IN    lUserID    设备句柄
*@param: IN    szDeviceID 设备ID
*@param: OUT   pstResponse 响应结构体
*@return: 成功返回IDM_SUCCESS，失败返回错误码
**/
IDM_API LONG IDM_DEV_QueryDeviceInfo(LONG lUserID, CHAR * szDeviceID, IDM_DEV_QUERY_DEV_INFO_S * pstResponse);

/**
*@brief: 关闭主动注册模式下的套接字
*@param: IN    szDeviceID 设备ID
*@return: 成功返回IDM_SUCCESS，失败返回错误码
**/
IDM_API LONG IDM_DEV_CloseTcpSocket(CHAR * szDeviceID);

/* 获取SDK版本 字符串信息*/
IDM_API CHAR * IDM_DEV_GetSDKStringVersion();
/*
*@brief: 设置录像下载进度回调函数
*@param: IN lDownloadHandle 下载句柄
*@param: IN pfDownloadProgressCallback 录像下载进度回调函数
*@param: IN pUserData 用户数据
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_SetDownloadProgressCallback(LONG lDownloadHandle, IDM_DEV_Download_Progress_Callback_PF pfDownloadProgressCallback, VOID* pUserData);

/*
*@brief: 启动抓拍图片批量下载
*@param: IN lUserID 设备句柄
*@param: IN pstRequest 启动抓拍图片批量下载参数结构体
*@param: IN szFilePath 文件单个/批量下载保存路径
*@param: OUT pstResponse 响应参数
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_StartSapPicDownload(LONG lUserID, IDM_DEV_SAP_PIC_BATCH_DOWONLOAD_S* pstRequest, IDM_START_PIC_DOWNLOAD_RESULT_S* pstResponse, CHAR* szFilePath);

/*
*@brief: 停止抓拍图片批量下载
*@param: IN szPicDownloadSessionID 启动抓拍图片批量下载接口返回结果结构体中的，下载会话ID
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_StopSapPicDownload(CHAR * szPicDownloadSessionID);

/*
*@brief: 停止抓拍图片批量下载
*@param: IN szPicDownloadSessionID 启动抓拍图片批量下载接口返回结果结构体中的，下载会话ID
*@param: IN pstProgress 下载进度结构体
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_GetSapPicDownloadProgess(CHAR * szPicDownloadSessionID, IDM_SNAP_PIC_DOWNLOAD_PROGRESS_S * pstProgress);

/*
*@brief: 文件单个/批量下载，10M以内的文件
*@param: IN lUserID 设备句柄
*@param: IN pstDownlodFiles 文件单个/批量下载参数结构体
*@param: IN szFilePath 文件单个/批量下载保存路径
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_DownloadSmallFiles(LONG lUserID, IDM_DOWNLOAD_FILES_S * pstDownlodFiles, CHAR* szFilePath);

/*
*@brief: 查询公有云解析任务抓图计划
*@param: IN lUserID 设备句柄
*@param: IN pstTaskID 任务id列表结构体
*@param: IN/OUT pstAnalysisTaskSnapPlan 获取抓图计划返回结构体
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_GetAnalysisPicSnapPlan(LONG lUserID, IDM_DEV_TASK_ID_S *pstTaskID, IDM_DEV_ANALISYS_TASK_SNAP_PLAN_S* pstAnalysisTaskSnapPlan);

/*
*@brief: 设置公有云解析任务抓图计划
*@param: IN lUserID 设备句柄
*@param: IN pstPicSnapPlan 设置抓图计划结构体
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_SetAnalysisPicSnapPlan(LONG lUserID, IDM_DEV_ANALISYS_TASK_SNAP_PLAN_S* pstAnalysisTaskSnapPlan);

/*
*@brief: 删除公有云解析任务抓图计划
*@param: IN lUserID 设备句柄
*@param: IN pstTaskID 任务id列表结构体
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_DelAnalysisPicSnapPlan(LONG lUserID, IDM_DEV_TASK_ID_S *pstTaskID);

/*
*@brief: 设置公有云解析任务抓图计划使能状态
*@param: IN lUserID 设备句柄
*@param: IN pstTaskID 任务id列表结构体
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_SetAnalysisPicSnapPlanEnale(LONG lUserID, IDM_DEV_TASK_ID_S *pstTaskID);

/*
*@brief: 手动抓拍透传V2
*@param: IN lUserID 设备句柄
*@param: IN pInter 抓拍参数  内存由用户自行管理
*@param: OUT pOuter 响应参数 调用IDM_FREE进行内存释放
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_ManualSnap_V2(LONG lUserID, IDM_DEV_MANUALSNAP_S *pInter, IDM_DEV_MANUALSNAP_RESULT_S *pOuter);

/*
*@param: IN lUserID 设备句柄
*@param: IN stFileCond 查找条件
*@param: OUT pstFileResult 查找结果
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_FindFile_V3(LONG lUserID, IDM_DEV_FILE_COND_S_V3 stFileCond, IDM_DEV_FILE_RESULT_S_V3 *pstFileResult);

/*
*@brief: 启动升级
*@param: IN lUserID 设备句柄
*@param: IN pstRequest 请求结构体
*@param: OUT pstResponse 响应结构体
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_StartUpgrade(LONG lUserID, IDM_DEV_UPGRADE_REQUEST_S *pstRequest, IDM_DEV_UPGRADE_SESSION_S *pstResponse);

/*
*@brief: 终止升级
*@param: IN lUserID 设备句柄
*@param: IN pstRequest 请求结构体
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_StopUpgrade(LONG lUserID, IDM_DEV_UPGRADE_SESSION_S*pstRequest);

/*
*@brief: 获取升级状态
*@param: IN lUserID 设备句柄
*@param: IN pstRequest 请求结构体
*@param: OUT pstResponse 响应结构体
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_GetUpgradeStatus(LONG lUserID, IDM_DEV_UPGRADE_SESSION_S*pstRequest, IDM_DEV_UPGRADE_STATUS_S *pstResponse);

/*
*@brief: 保存实时流到文件 V2
*@param: IN lRealPlayHandle 预览句柄
*@param: IN pcFileName 保存的文件路径
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_SaveRealPlayData_V2(LONG lRealPlayHandle, IDM_DEV_SAVE_DATA_INFO_S *pFileInfo);

/*
*@brief: 保存回放流到文件 V2
*@param: IN lRealPlayHandle 回放句柄
*@param: IN pFileInfo       文件信息
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_SavePlayBackData_V2(LONG lPlayBackHandle, IDM_DEV_SAVE_DATA_INFO_S *pFileInfo);

/*
*@brief: 开启被动模式监听服务 V2
*@param: IN usSerPort 监听端口
*@param: IN pUserData 回调函数返回的用户数据
*@param: IN pfConnectCallback 设备连接后从回调函数中返回
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_StartServer_V2(USHORT usSerPort, VOID *pUserData, IDM_DEV_Connect_Callback_PF_V2 pfConnectCallback);


/*
*@brief: 下载URL对应图片
*@note : 响应结构体中内存由用户调用IDM_DEV_Free(响应结构体首地址, 响应结构体长度)进行释放
*@param: IN lUserID 设备句柄
*@param: IN pRequst 请求参数
*@param: OUT pResp 响应参数
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_GetImageByURL(LONG lUserID, IDM_DEV_WGET_IMAGE_S *pRequest, IDM_DEV_IMAGE_RESPONSE_S *pResponse);

/*
*@brief: 公有云平台注册证书
*@param: IN pstRequest 请求参数
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_DEV_RegisterCert(IDM_DEV_CERTIFICATE_INFO_S *pCertInfo);

/*
*@brief: 算法操作接口
*@param: IN  lUserID    设备句柄
*@param: IN  szAlgoID   算法ID   PERIMETER_ALGO_ID 周界 或者 AIUNITE_ALGO_ID 人脸比对
*@param: IN  pstParam   参数结构体
*@return: 成功返回IDM_SUCCESS，失败返回错误码
*/
IDM_API LONG IDM_UNI_AlgoOp(LONG lUserID, CONST CHAR *szAlgoID, IDM_UNI_ALGO_OP *pstParam);

/**
*@brief: 5 修改用户密码
*@param: IN  lUserID 设备句柄
*@param: IN  pstRequest 请求参数
*@return: 成功返回IDM_SUCCESS，失败返回错误码
**/
IDM_API LONG IDM_DEV_ResetUserPassword(LONG lUserID, IDM_DEV_RESET_PASSWORD_S *pstRequest);

#ifdef __cplusplus
}
#endif

#endif
