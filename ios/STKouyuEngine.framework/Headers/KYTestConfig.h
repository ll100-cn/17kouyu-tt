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
    KYTestType_AsrEval,            //带识别评测
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


@interface KYTestConfig : NSObject

// 可选，默认 0，即不返回音强(SoundIntensity)值，可选 1，该值通过 callback 回调返回，参数为“sound_intensity”
@property (nonatomic, assign) BOOL soundIntensityEnable;

// 必选，配置为:"cloud",离线版为:"native"
@property (nonatomic, copy) NSString *coreProvideType;

// 可选，序列号
@property (nonatomic, copy) NSString *serialNumber;

// 可选, 用户在应用中的唯一标识
@property (nonatomic, copy) NSString *userId;



/****************  audio参数  *****************/

// 必须, 云端支持:wav, mp3, flv, ogg, amr 格式, 本地支持: wav 格式
@property (nonatomic, copy) NSString *audioType;

// 必须, 目前只支持单声道, 所以这里只能填 1
@property (nonatomic, assign) NSInteger channel;

// 必须, 每采样字节数, 支持单字节(8 位):1 和双字节(16 位):2
@property (nonatomic, assign) NSInteger sampleBytes;

// 必须, 采样率, 必须与音频本身采样率一致，不同语音服务有不同的要求, wav 格式要求必须是 16k
@property (nonatomic, assign) NSInteger sampleRate;

// 可选, 默认 8，取值范围 1~10. 若不在取值范围之内，则默认配置 8.
@property (nonatomic, assign) NSInteger quality;

// 可选，默认 2
@property (nonatomic, assign) NSInteger complexity;

// 可选, 音频压缩配置, speex:speex 压缩(默认配置), raw:不压缩
@property (nonatomic, assign) KYCompressType compress;

// 可选, vbr 配置，默认值 NO,若设置为 YES，则 quality 值作为 vbr quality 配置
@property (nonatomic, assign) BOOL vbr;

//可选, 发包缓存, 默认48000
@property (nonatomic, assign) NSInteger max_ogg_delay;

// 可选, 录音音频保存路径。默认路径 ~/Document/record/。自定义路径需设置完整路径
@property (nonatomic, copy) NSString *recordPath;

// 可选, 录音音频名称。加上.wav后缀
@property (nonatomic, copy) NSString *recordName;

// 本地音频路径。需要支持本地音频评测时，传音频路径。支持pcm、mp3、ogg、flv、opus、amr、silk格式
@property (nonatomic, copy) NSString *audioPath;

/******************************************/



/****************  proto参数  *****************/

// 可选，指定评分协议，可选值:http
@property (nonatomic, copy) NSString *protocol;

/******************************************/

/****************  request参数  *****************/

// 可选，在返回结果时同时返回请求参数，默认 NO 关闭，可选 YES 开启
@property (nonatomic, assign) BOOL getParam;

// 必须，请求的内核类型 目前支持 word.eval(1 个单词)/sent.eval(200 单词内)/para.eval(1000 单词内)/open.eval/choice.rec(无限制)
@property (nonatomic, assign) KYTestType coreType;

// 必须，参考文本，多个参考答案用竖线(|)隔开, refText 格式要求请参阅 “参考文本传入格式要求.pdf”
@property (nonatomic, copy) NSString *refText;

// 公网可访问URL地址，使用音频比对内核时必填
@property (nonatomic, copy) NSString *refAudio;

// 可选，使用云服务时可选，指定服务器使返回结果附带音频下载地址
@property (nonatomic, assign) BOOL attachAudioUrl;

// 可选，音素字典选项，默认 KK，可选 CMU/KK/IPA88
@property (nonatomic, assign) KYPhonemeOption phonemeOption;

// 可选，音素纬度开关，默认 1 开，0 为关闭
@property (nonatomic, assign) BOOL phoneme_output;

// 可选，单词句子段落内核可选，年龄段支持，可选值 1:3~6years-old， 2:6~12years-old，3:>12years-old，默认为 3
@property (nonatomic, assign) KYAgeGroupSupportOption ageGroup;

// 可选，模型，只对open.eval有效，支持school/home两种参数，不传时默认为school，kernel_2.7.0以及之后版本有效
@property (nonatomic, assign) KYModeType mode;

// para.eval时有效，YES时返回每个单词得分
@property (nonatomic, assign) BOOL isParagraphNeedWordScore;

// 可选，分制，取值范围(0,100]
@property (nonatomic, assign) CGFloat scale;

// 可选，精度，建议取值的范围(0,1]
@property (nonatomic, assign) CGFloat precision;

// 可选，人工干预单词的得分，取值范围[-1,1]，干预后每个单词得分取值范 围[0,100]
@property (nonatomic, assign) CGFloat slack;

// 可选，关键字，open.eval 题型有效
@property (nonatomic, copy) NSString *keywords;

// 可选，题型，open.eval 题型必须，0 短文朗读;1 短文跟读;2 句子翻译;3 段落翻译;4 故事复述;5 看图说话;6 情景问答;7 口头作文
@property (nonatomic, assign) KYQType qType;

// 可选，自定义音标
@property (nonatomic, strong) NSDictionary *customized_lexicon;

// 可选， 自定义参数 (字典中key为要自定义增加的参数名，value为参数值)
@property (nonatomic, strong) NSDictionary *customParams;

// 可选，音标纠错，通过substitution显示实际发音音标，默认 NO 关闭，可选 YES 开启
@property (nonatomic, assign) BOOL phoneme_diagnosis;

// seek可选，发音结束判断间隔，单位 10ms,默认 60，即 600ms
@property (nonatomic, assign) CGFloat seek;

// ref_length可选，从开始录音计时，未超出该时间无论是否停止说话vad状态一直为1，超出时间以实际说话状态为准，建议根据实际业务设置，单位 10ms,默认 0
@property (nonatomic, assign) CGFloat ref_length;

// 可选，开启后边录边评，调用stopEngine才会返回结果，默认NO
@property (nonatomic, assign) BOOL forceRecord;

// 可选，重评，默认NO
@property (nonatomic, assign) BOOL autoRetry;

// 可选，启后遇到指定错误码重评，默认20009
@property (nonatomic, strong) NSArray *errIds;

// 可选, 是否开启中间结果,仅支持自由识别和句子评测
@property (nonatomic, assign) BOOL realtime_feedback;

// 可选,错误答案列表
@property (nonatomic, copy) NSString *negativeReftext;

// 可选,dict_type为ipa88时,指定OW返回音标,en_br返回əʊ,en_us返回oʊ,默认en_br
@property (nonatomic, copy) NSString *dict_dialect;

//可选,是否开启非英文检测,默认关闭,仅对句子评测有效
@property (nonatomic, assign) BOOL detect_nonscorable;

//可选，指定音标评分,支持KK、IPA88音标,默认KK,{"type":"IPA88", "pron":{"but":["bət","bʌt"]}}
@property (nonatomic, strong) NSDictionary *customized_pron;

//可选，英文评测时保留非英文字符
@property (nonatomic, assign) BOOL output_rawtext;

//可选，静音检测，提升评分速度
@property (nonatomic, assign) BOOL vad_detection;

//可选,仅对KYQType_SituationalReply有效，正答关键词，具体设置详见参数文档
@property (nonatomic, strong) NSArray *keypoints;

//可选,仅对KYQType_SituationalReply有效，正答关键词权重,范围(0,1]，具体设置详见参数文档
@property (nonatomic, assign) CGFloat keypoints_weight;

//可选,仅对KYQType_SituationalReply有效，错答关键词，具体设置详见参数文档
@property (nonatomic, strong) NSArray *negative_keypoints;

// 可选, 响应的超时时间，优先级高于KYStartEngineConfig中的serverTimeout,不设置则使用KYStartEngineConfig中的serverTimeout
@property (nonatomic, assign) CGFloat serverTimeout;

@end
