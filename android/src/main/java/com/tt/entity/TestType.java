package com.tt.entity;

/**
 * Created by cj on 2016/12/26.
 */

public class TestType {

    private String coreType;//必须，请求的内核类型
    private String refText;//必须，参考文本

    private String qType;//可选，题型，en.open题型必须，0短文朗读;1短文跟读;2句子翻译;3段落翻译;4故事复述;5看图说话;6情景问答;7口头作文，开放题型建议5个以上参考答案，越多越准,用竖线|隔开

    private String answer;//句子翻译时作为refText传入

    public TestType(String coreType, String refText) {
        this.coreType = coreType;
        this.refText = refText;
    }

    //en.open题型必须
    public TestType(String coreType, String refText, String qType) {
        this.coreType = coreType;
        this.refText = refText;
        this.qType = qType;
    }

    public TestType(String coreType, String refText, String qType, String answer) {
        this.coreType = coreType;
        this.refText = refText;
        this.qType = qType;
        this.answer = answer;
    }

    public String getAnswer() {
        return answer;
    }

    public void setAnswer(String answer) {
        this.answer = answer;
    }

    public String getqType() {
        return qType;
    }

    public void setqType(String qType) {
        this.qType = qType;
    }

    public String getCoreType() {
        return coreType;
    }

    public void setCoreType(String coreType) {
        this.coreType = coreType;
    }

    public String getRefText() {
        return refText;
    }

    public void setRefText(String refText) {
        this.refText = refText;
    }
}
