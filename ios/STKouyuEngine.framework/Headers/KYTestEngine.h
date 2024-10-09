//
//  KYTestEngine.h
//  KouyuDemo
//
//  引擎类（用于构建引擎、开启评测等功能）
//
//  Created by Attu on 2017/8/15.
//  Copyright © 2017年 Attu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "KYStartEngineConfig.h"
#import "KYTestConfig.h"

typedef enum : NSUInteger {
    KY_CloudEngine,       //云端引擎
    KY_NativeEngine,      //离线引擎
    KY_MultiEngine,       //云端，离线双引擎
} KYEngineType;

typedef void(^KYTestResultBlock)(NSString *testResult);

//typedef void(^KYVadResultBlock)(int vad_status, int sound_intensity);

//typedef void(^KYTickBlock)(CGFloat millisUntilFinished, CGFloat percentUntilFinished);

typedef void(^KYPlayFinishBlock)(void);

@protocol KYTestEngineDelegate <NSObject>
@optional

- (void)kyTestEngineDidRecordStart;
- (void)kyTestEngineDidRecordStartFail:(NSString *)str;
- (void)kyTestEngineDidRecordTick:(CGFloat)millisUntilFinished percentUntilFinished:(CGFloat)percentUntilFinished;
- (void)kyTestEngineDidRecordEnd;
- (void)kyTestEngineDidVadScore:(int)vad_status sound_intensity:(int)sound_intensity;
- (void)kyTestEngineDidScore:(NSString *)str;
- (void)kyTestEngineDidRecordFeedFail:(NSString *)str;
- (void)kyTestEngineDidRecordWriteAudioResult:(BOOL)result;
- (void)kyTestEngineDidPlayStart;
- (void)kyTestEngineDidPlayStartFail:(NSString *)str;
- (void)kyTestEngineDidPlayEnd;
@end

@interface KYTestEngine : NSObject
@property (nonatomic, weak) id<KYTestEngineDelegate> delegate;

+ (instancetype)sharedInstance;

/**
 初始化引擎

 @param engineType 引擎类型
 @param startEngineConfig 初始化引擎配置参数
 @param finishBlock 初始化是否成功回调
 */
- (void)initEngine:(KYEngineType)engineType startEngineConfig:(KYStartEngineConfig *)startEngineConfig finishBlock:(void(^)(BOOL isSuccess, NSString *str))finishBlock;


/**
 启动引擎开始评测 
 
 @param testConfig  评测配置参数
 @param testResultBlock 评测成功回调
 @param finishBlock 开始评测是否成功回调
 */
- (NSString *)startEngineWithTestConfig:(KYTestConfig *)testConfig result:(KYTestResultBlock)testResultBlock finishBlock:(void(^)(BOOL isSuccess, NSString *str))finishBlock;

/**
 启动引擎开始评测
 
 @param testConfig  评测配置参数
 @param onStartBlock 开始录制回调
 @param onStartFailBlock 开始录制失败回调
 @param onPauseBlock 录制暂停回调
 @param onTickBlock 指定录制时长后倒计时回调
 @param onRecordingBlock 开启vad后中间回调
 @param onRecordEndBlock 录制结束回调
 @param onScoreBlock 评测成功回调
 @param finishBlock 开始评测是否成功回调
 */

- (NSString *)startEngineWithTestConfig:(KYTestConfig *)testConfig
                           onStartBlock:(void(^)(void))onStartBlock
                       onStartFailBlock:(void(^)(NSString *failReason))onStartFailBlock onPauseBlock:(void(^)(void))onPauseBlock
                            onTickBlock:(void(^)(CGFloat millisUntilFinished, CGFloat percentUntilFinished))onTickBlock
                       onRecordingBlock:(void(^)(int vad_status, int sound_intensity))onRecordingBlock
                       onRecordEndBlock:(void(^)(void))onRecordEndBlock
                           onScoreBlock:(void(^)(NSString *result))onScoreBlock
                            finishBlock:(void(^)(BOOL isSuccess, NSString *str))finishBlock;

/**
 关闭引擎（有回调）
 */
- (void)stopEngine;

/**
 取消评测（无回调）
 */
- (void)cancelEngine;

/**
 销毁引擎
 */
- (void)deleteEngine;

/**
 回放
 */
- (void)playback;

/**
 播放指定路径音频
 **/
- (void)playWithPath:(NSString *)wavPath;

/**
 回放
 
 @param playFinishBlock 播放完成回调
 */
- (void)playback:(KYPlayFinishBlock)playFinishBlock;

/**
 播放指定路径音频
 
 @param playFinishBlock 播放完成回调
 **/
- (void)playWithPath:(NSString *)wavPath void:(KYPlayFinishBlock)playFinishBlock;

/**
 停止播放
 */
- (void)stopPlay;

/**
 激活音频设备
 */
- (void)activeAudioSession;

/**
 查看引擎状态
 YES or NO
 */
- (BOOL)getEngineStatus;

/**
 获取最后一次录音路径
 */
- (NSString *)getLastRecordPath;

/**
 手动feed音频
 */
- (void)feedAudioData:(void *)audioData audioLength:(int)length;

/**
 手动更新证书
 @param provison 评测证书路径
 @param appkey 评测appkey
 @param secretkey 评测secretkey
 */
- (BOOL)updateProvision:(NSString *)provison appkey:(NSString *)appkey secretkey:(NSString *)secretkey;

- (BOOL)updateProvision:(NSString *)appkey secretkey:(NSString *)secretkey;

- (BOOL)updateProvision;

/**
 手动获取证书内容
 @param provision 获取证书内容路径
 @param inquireProvisionBlock 证书内容获取回调
 */
- (BOOL)inquireProvision:(NSString *)provision
   inquireProvisionBlock:(void(^)(NSString * message))inquireProvisionBlock;

- (BOOL)inquireProvision:(void(^)(NSString * message))inquireProvisionBlock;

@end
