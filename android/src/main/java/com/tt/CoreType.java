package com.tt;

/**
 * Created by cj on 2016/12/27.
 */

public class CoreType {

//    请求的内核类型(新版)
//    sent.eval     英文句子评测    传音频和单词文本，返回单词得分
//    word.eval     英文单词评测    传音频和句子文本，返回句子得分
//    para.eval     段落评测        传音频和段落文本，返回每句句子得分（或精确到每个单词的得分）
//    choice.rec    英文句子识别    传音频和多个句子文本(用竖线｜隔开)，返回音频中读到的句子和得分
//    open.eval     开放题（考试技术：段落朗读、情景问答、口头作文、看图说话、故事复述、句子翻译等）
//    align.eval    音频对比        传音频与标准音进行对比匹配，返回得分
    public static final String EN_SENT_EVAL = "sent.eval";
    public static final String EN_WORD_EVAL = "word.eval";
    public static final String EN_CHOICE_REC = "choice.rec";
    public static final String EN_OPEN_EVAL = "open.eval";
    public static final String EN_PARA_EVAL = "para.eval";
}
