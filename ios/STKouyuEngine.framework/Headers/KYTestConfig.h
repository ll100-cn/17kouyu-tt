//
//  KYTestConfig.h
//  KouyuDemo
//
//  评测时需要配置的参数
//
//  Created by Attu on 2017/8/28.
//  Copyright © 2017年 Attu. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

//音频压缩配置
typedef enum : NSUInteger {
    KYCompress_Speex = 1,     //压缩
    KYCompress_Raw,       //不压缩
} KYCompressType;


//请求的内核类型
typedef enum : NSUInteger {
    KYTestType_Word,              //单词评测(1 个单词)
    KYTestType_Sentence,          //句子评测(200 单词内)
    KYTestType_Paragraph,         //段落评测(1000 单词内)
    KYTestType_Open,              //开放题型
    KYTestType_Choice,            //有限分支识别
    KYTestType_Asr,               //英文自由识别
    KYTestType_Align,              //音频比对
    KYTestType_Word_Pro,           //单词评测(1 个单词，自适应年龄段)
    KYTestType_Sentence_Pro,       //句子评测(200 单词内，自适应年龄段)
    KYTestType_Word_Cn,            //中文字评测
    KYTestType_Sentence_Cn,        //中文句子评测
    KYTestType_Paragraph_Cn,        //中文段落评测
    KYTestType_AsrEval,            //带识别评测
    KYTestType_Word_fr,           //法语词评测
    KYTestType_Sentence_fr,       //法语句子评测
    KYTestType_Paragraph_fr,       //法语段落评测
    KYTestType_Word_kr,           //韩语词评测
    KYTestType_Sentence_kr,       //韩语句子评测
    KYTestType_Paragraph_kr,       //韩语段落评测
    KYTestType_Word_jp,           //日语词评测
    KYTestType_Sentence_jp,       //日语句子评测
    KYTestType_Paragraph_jp,       //日语段落评测
    KYTestType_Wordspell,          
} KYTestType;

//音素字典选项
typedef enum : NSUInteger {
    KYPhonemeOption_CMU = 1,
    KYPhonemeOption_KK,
    KYPhonemeOption_IPA88,
} KYPhonemeOption;

//年龄段支持
typedef enum : NSUInteger {
    KYAgeGroupSupportOption_Junior = 1,     //3~6years-old
    KYAgeGroupSupportOption_Middle,         //6~12years-old
    KYAgeGroupSupportOption_Senior,         //>12years-old
} KYAgeGroupSupportOption;

//开放题型选项
typedef enum : NSUInteger {
    KYQType_PassageReading,         //短文朗读
    KYQType_FollowReadPassage,      //短文跟读
    KYQType_SentenceTranslation,    //句子翻译
    KYQType_ParagraphTranslation,   //段落翻译
    KYQType_RepeatStory,            //故事复述
    KYQType_LookAndSay,             //看图说话
    KYQType_SituationalReply,       //情景问答
    KYQType_OralComposition,        //口头作文
    KYQType_SentenceReading,        //句子朗读
} KYQType;

//区分使用场景
typedef enum : NSUInteger {
    KYModeType_School,
    KYModeType_Home,
} KYModeType;

extern NSString *const KYEngineCloud;      //在线引擎

extern NSString *const KYEngineNative;   //离线引擎

@interface KYTestConfigTemp : NSObject

@property (nonatomic, assign) KYTestType coreType;

@property (nonatomic, copy) NSString *coreTypeNS;

@property (nonatomic, copy) NSString *coreProvideType;

@end


@interface KYTestConfig : NSObject

// 可选，是否返回音强，可选值YES（开启，带vad功能的sdk KYStartEngineConfig需要设置vadEnable为YES）、NO（关闭），默认 NO。该值通过 callback 回调返回，参数为“sound_intensity”
@property (nonatomic, assign) BOOL soundIntensityEnable;

// 可选，指定评测引擎类型，engineType为KY_MultiEngine时必填，可选值：cloud、native
@property (nonatomic, copy) NSString *coreProvideType;

// 可选，序列号
@property (nonatomic, copy) NSString *serialNumber;

// 可选, 用户在应用中的唯一标识
@property (nonatomic, copy) NSString *userId;



/****************  audio参数  *****************/

// 必须, 在线支持:wav, mp3, flv, ogg, amr 格式, 本地支持: wav 格式，传mp3，使用framework录音时,可录成mp3格式音频
@property (nonatomic, copy) NSString *audioType;

// 必填，声道数，填1
@property (nonatomic, assign) NSInteger channel;

// 必填，每采样字节数, 支持单字节(8 位):1 和双字节(16 位):2
@property (nonatomic, assign) NSInteger sampleBytes;

// 必填, 采样率, 单位Hz，必须与音频本身采样率一致，不同语音服务有不同的要求, wav 格式要求必须是 16000
@property (nonatomic, assign) NSInteger sampleRate;

// 废弃，可选, 默认 8，取值范围 1~10. 若不在取值范围之内，则默认配置 8.
@property (nonatomic, assign) NSInteger quality;

// 废弃，可选，默认 2
@property (nonatomic, assign) NSInteger complexity;

// 可选，在线评测音频压缩设置，可选值： KYCompress_Speex 为压缩(默认)，KYCompress_Raw 为不压缩
@property (nonatomic, assign) KYCompressType compress;

// 废弃，可选, vbr 配置，默认值 NO,若设置为 YES，则 quality 值作为 vbr quality 配置
@property (nonatomic, assign) BOOL vbr;

//可选, 发包缓存, 可选9600，48000，默认48000，需要与realtime_feedback 一起设置，仅KYTestType_Sentence、KYTestType_Sentence_Pro、KYTestType_Asr有效
@property (nonatomic, assign) NSInteger max_ogg_delay;

// 可选, 录音音频保存路径。默认路径 ~/Document/record/。自定义路径需设置完整路径
@property (nonatomic, copy) NSString *recordPath;

// 可选，指定录音文件名，支持wav、mp3（含后缀，如：xxx.wav、xxx.mp3），后缀格式须与audioType保持一致
@property (nonatomic, copy) NSString *recordName;

// 可选，本地音频文件评分，传音频绝对路径，格式与audioType保持一致。在线支持mp3、wav、ogg、spx、flv、slk、silk、opus、speex、aac、other、amr格式，离线仅支持wav 格式
@property (nonatomic, copy) NSString *audioPath;

// 可选，手动feed音频流。可选值YES、NO，默认NO，若设置为YES，则优先级高于audioPath（本地音频文件评测）、framework自带录音，音频格式须与audioType保持一致
@property (nonatomic, assign) BOOL isStream;




/******************************************/



/****************  proto参数  *****************/

// 可选，指定评分协议，可选值:http
@property (nonatomic, copy) NSString *protocol;

/******************************************/

/****************  request参数  *****************/

// 可选，在返回结果时同时返回请求参数，默认 NO 关闭，可选 YES 开启
@property (nonatomic, assign) BOOL getParam;

// 必填，评测内核，设置coreTypeNS时可不传
@property (nonatomic, assign) KYTestType coreType;

// 可选，字符串类型评测内核，使用此参数时coreType可不传，优先级高于coreType。可选值参考“评测参数及结果说明“
@property (nonatomic, copy) NSString *coreTypeNS;

// 必填，评测文本，多个参考答案用竖线(|)隔开，refText 格式要求参考 “评测文本格式”，中文评测设置refPinyin、coreType为KYTestType_Align、coreTypeNS为align.eval时为可选
@property (nonatomic, copy) NSString *refText;

// 可选，参考音频，公网可访问URL地址，coreType为KYTestType_Align、coreTypeNS为align.eval时必填
@property (nonatomic, copy) NSString *refAudio;

// 可选，评测结果返回音频下载地址（仅云服务时有效），可选值YES、NO，默认NO
@property (nonatomic, assign) BOOL attachAudioUrl;

// 可选，音素字典选项，默认 KK，可选 CMU/KK/IPA88
@property (nonatomic, assign) KYPhonemeOption phonemeOption;

// 可选，评测结果是否返回phonemes音素纬度，可选值YES、NO，默认YES，仅单词、句子内核有效
@property (nonatomic, assign) BOOL phoneme_output;

// 可选，英文单词、句子、段落内核指定年龄段评测，可选值：KYAgeGroupSupportOption_Junior（3~6years-old）、KYAgeGroupSupportOption_Middle（6~12years-old）、KYAgeGroupSupportOption_Senior（>12years-old），默认为KYAgeGroupSupportOption_Senior
@property (nonatomic, assign) KYAgeGroupSupportOption ageGroup;

// 可选，评测环境模式，仅对coreType为KYTestType_Open、coreTypeNS为open.eval有效，可选值：KYModeType_School、KYModeType_Home，默认为KYModeType_School
@property (nonatomic, assign) KYModeType mode;

// 可选，段落内核评测时返回每个单词得分，可选值：YES、NO，默认为NO
@property (nonatomic, assign) BOOL isParagraphNeedWordScore;

// 可选，分制，取值范围(0,100]
@property (nonatomic, assign) CGFloat scale;

// 可选，精度，建议取值的范围(0,1]
@property (nonatomic, assign) CGFloat precision;

// 可选，打分松紧度， 取值范围[-1,1]，默认0，正数加分负数减分 ，0.1 加分幅度较小，1 加分幅度较大，干预后影响各维度分数
@property (nonatomic, assign) CGFloat slack;

// 可选，关键字，open.eval 题型有效
@property (nonatomic, copy) NSString *keywords;

// 可选，开放题题型，coreType为KYTestType_Open、coreTypeNS为open.eval时必填，可选值：参考KYQType
@property (nonatomic, assign) KYQType qType;

// 可选，自定义音标，英文为CMU音标、中文为拼音。仅对KYTestType_Word、KYTestType_Word_Pro、KYTestType_Sentence、KYTestType_Sentence_Pro、KYTestType_Paragraph、KYTestType_Word_Cn、KYTestType_Sentence_Cn、KYTestType_Paragraph_Cn有效
@property (nonatomic, strong) NSDictionary *customized_lexicon;

// 可选， 自定义参数 (字典中key为要自定义增加的参数名，value为参数值)
@property (nonatomic, strong) NSDictionary *customParams;

// 可选，音标纠错，通过substitution显示实际发音音标，默认 NO 关闭，可选 YES 开启
@property (nonatomic, assign) BOOL phoneme_diagnosis;

// 可选，本次vad 发音结束判断间隔，单位：10ms，默认60（即600ms），优先级高于KYStartEngineConfig seek
@property (nonatomic, assign) CGFloat seek;

// 可选，本次评测vad最短说话时间，开始说话后该时间内vad状态始终为1，单位 10ms，默认 0（关闭）
@property (nonatomic, assign) CGFloat ref_length;

// 可选，开启后调用stopEngine才会返回结果，可选值：YES、NO，默认NO
@property (nonatomic, assign) BOOL forceRecord;

// 可选，遇到指定errIds错误码重评，可选值：YES、NO，默认NO
@property (nonatomic, assign) BOOL autoRetry;

// 可选，指定重评错误码，默认20009
@property (nonatomic, strong) NSArray *errIds;

// 可选, 是否开启中间结果,仅支持自由识别和句子评测
@property (nonatomic, assign) BOOL realtime_feedback;

// 可选,错误答案列表
@property (nonatomic, copy) NSString *negativeReftext;

// 可选，限定英式、美式发音，可选值：en_br（英式）、en_us（美式），不设置表示不限定
@property (nonatomic, copy) NSString *dict_dialect;

// 可选,是否开启非英文检测,默认关闭,仅对句子评测有效
@property (nonatomic, assign) BOOL detect_nonscorable;

// 可选，指定音标评分，支持KK、IPA88音标，仅在线评测KYTestType_Word、KYTestType_Sentence、KYTestType_Paragraph、KYTestType_Word_Pro、KYTestType_Sentence_Pro、KYTestType_AsrEval有效
@property (nonatomic, strong) NSDictionary *customized_pron;

// 可选，保留标点符号，可选值：YES、NO，默认NO，仅在线评测KYTestType_Sentence、KYTestType_Sentence_Pro、KYTestType_Paragraph、KYTestType_Sentence_Cn、KYTestType_Paragraph_Cn有效
@property (nonatomic, assign) BOOL output_rawtext;

//可选，静音检测，提升评分速度
@property (nonatomic, assign) BOOL vad_detection;

// 可选，正答关键词，仅在线评测KYTestType_Open qType=KYQType_SituationalReply有效
@property (nonatomic, strong) NSArray *keypoints;

// 可选，正答关键词，仅在线评测KYTestType_Open qType=KYQType_SituationalReply有效
@property (nonatomic, assign) CGFloat keypoints_weight;

// 可选，错答关键词，仅在线评测KYTestType_Open qType=KYQType_SituationalReply有效
@property (nonatomic, strong) NSArray *negative_keypoints;

// 可选, 本次在线评测时等待评测结果的超时时间，优先级高于KYStartEngineConfig  serverTimeout，单位：秒，默认是 60（即60秒）
@property (nonatomic, assign) CGFloat serverTimeout;

// 可选，最大录音时长，单位毫秒，到时间后自动停止录音
@property (nonatomic, assign) CGFloat duration;

// 可选，kyTestEngineDidRecordTick回调间隔，单位：毫秒，默认100（100毫秒）
@property (nonatomic, assign) CGFloat durationInterval;

// 可选，中文拼音评测参考文本，仅在线评测KYTestType_Word_Cn、KYTestType_Sentence_Cn、KYTestType_Paragraph_Cn有效
@property (nonatomic, copy) NSString *refPinyin;

//可选，识别结果增加标点，可选值YES、NO，默认NO，支持的coreType详见”评测参数及结果“
@property (nonatomic, assign) BOOL punctuate;

//可选，sig方式评测
@property (nonatomic, strong) NSDictionary *customized_sig;

// 可选，sig鉴权方式评测, 使用此方式评测，KYStartEngineConfig secretkey可以传空值
@property (nonatomic, copy) NSString *customized_sig_url;

// 可选，录音回调间隔，单位:ms
@property (nonatomic, assign) CGFloat recordCallbackInterval;

// 可选，重复读、漏读检测，可选值：0、1 ，0：关闭 1：开启，默认：0
@property (nonatomic, assign) CGFloat readtype_diagnosis;

// 可选，自由识别，遇到数字是否转成阿拉伯数字
@property (nonatomic, assign) CGFloat itn;

// 可选，内核参数
@property (nonatomic, strong) NSDictionary *request;

// 可选，是否开启音标划分
@property (nonatomic, assign) BOOL blend_phoneme_enable;

@end
