//
//  KYStartEngineConfig.h
//  KouyuDemo
//
//  初始化引擎时配置的参数
//
//  Created by Attu on 2017/8/28.
//  Copyright © 2017年 Attu. All rights reserved.
//

#ifndef KYStartEngineConfig_H_
#define KYStartEngineConfig_H_

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

extern NSString *const KY_CloudServer_Gray;      //灰度地址

extern NSString *const KY_CloudServer_Release;   //正式地址

FOUNDATION_EXPORT int const KYLOG_ERROR;
FOUNDATION_EXPORT int const KYLOG_WARN;
FOUNDATION_EXPORT int const KYLOG_INFO;
FOUNDATION_EXPORT int const KYLOG_DEBUG;

FOUNDATION_EXPORT void KYLog(int flag, NSString *format, ...) NS_FORMAT_FUNCTION(2,3) NS_NO_TAIL_CALL;


@interface KYStartEngineConfig : NSObject

/****************  公用参数  *****************/
// 必填，声通提供的 appKey
@property (nonatomic, copy) NSString *appKey;

// 必填，声通提供的 secretKey, KYTestConfig使用customized_sig或者customized_sig_url时，可以传空值
@property (nonatomic, copy) NSString *secretKey;

// 已废弃，是否需要在线下载证书，默认为 NO，(即使用本地证书)
@property (nonatomic, assign) BOOL isUseOnlineProvison;

// 已废弃，是否需要在线更新证书，默认为 NO。若为YES，isUseOnlineProvison参数也需设为YES。
@property (nonatomic, assign) BOOL isUpdateProvison;

// 可选，证书文件路径（包含文件名）
@property (nonatomic, copy) NSString *provison;

// 可选，是否启用 vad（仅带vad功能的sdk 支持），默认为NO（关闭），设置为YES后返回 VAD 状态：0表示没开始说话 1表示说话中 2表示结束说话
@property (nonatomic, assign) BOOL vadEnable;

// 可选，全局vad 发音结束判断间隔，单位：10ms，默认60（即600ms）
@property (nonatomic, assign) CGFloat seek;

// 可选，日志级别（sdkLogEnable为YES时有效），默认1。可选值：0为error，1为warn，2为info，3为debug
@property (nonatomic, assign) BOOL sdkLogEnable;

// 可选，日志级别（sdkLogEnable为YES时有效），默认1。可选值：0为error，1为warn，2为info，3为debug
@property (nonatomic, assign) CGFloat logLevel;

// 可选，指定日志保存路径（含文件名），默认路径为 Document目录下，sdkLog.txt文件
@property (nonatomic, copy) NSString *sdkLogPath;

// 可选，是否在控制台打印日志，默认YES，可选值：YES、NO
@property (nonatomic, assign) BOOL isOutputLog;

// 可选，是否由业务层自行设置AVAudioSession，默认NO，可选值：YES、NO
@property (nonatomic, assign) BOOL customized_avaudiosession;

/******************************************/




/****************  云端引擎参数  *****************/

// 可选，engineType为KY_CloudEngine、KY_MultiEngine时必填，是否开启在线评测，默认YES，可选值：YES、NO
@property (nonatomic, assign) BOOL enable;

// 可选，指定在线评测地址（若不填写 sdk 会使用默认地址 ws://api.stkouyu.com:8080）， 灰度地址:ws://gray.stkouyu.com:8090
@property (nonatomic, copy) NSString *server;

// 可选，获取 serverList 的地址
@property (nonatomic, copy) NSString *serverList;

// 可选，获取 sdkCfgAddr 的地址
@property (nonatomic, copy) NSString *sdkCfgAddr;

// 可选, 在线评测时建立连接的超时时间，单位：秒，默认20（即20秒）
@property (nonatomic, assign) CGFloat connectTimeout;

// 可选, 在线评测时等待评测结果的超时时间，单位：秒，默认是 60（即60秒）
@property (nonatomic, assign) CGFloat serverTimeout;

/******************************************/




/****************  离线引擎参数  *****************/

// 可选，创建英文本地引擎（指定英文本地资源绝对路径），engineType为KY_NativeEngine时必填
@property (nonatomic, copy) NSString *native;

// 废弃，创建本地引擎，参数为本地资源db路径
@property (nonatomic, copy) NSString *native_db_path;

// 可选，创建中文本地引擎
@property (nonatomic, copy) NSString *native_cn;

// 可选，使用 AiLocal 服务时，必须传入 AiLocal 服务的地址
@property (nonatomic, copy) NSString *ailocalAddress;

/******************************************/

// 可选，engineType为KY_MultiEngine时断网自动切换到本地引擎网络，默认NO，可选值YES、NO
@property (nonatomic, assign) BOOL autoDetectNetwork;

@end

#endif
