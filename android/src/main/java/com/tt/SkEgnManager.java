package com.tt;

import android.content.Context;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;

/**
 * Created by cj on 2016/12/27.
 */

public class SkEgnManager {

    private static final String TAG = "SkEgnManager";

    public static final String SERVER_TYPE_CLOUD = "cloud";

    public static final int CODE_CREATE_ENGINE_FAIL = 0;

    public static final int CODE_RESULT_OK = 1;

    public static final int STATUS_START_CREATE_ENGINE = 0;
    public static final int STATUS_CREATE_ENGINE_SUCCESS = 1;
    public static final int STATUS_CREATE_ENGINE_FAIL = 2;
    public static final int STATUS_ENGINE_ALREADY_EXISTS = 3;

    public enum engine_status{
        IDLE,
        RECORDING,
        STOP
    };
    engine_status status1 = engine_status.IDLE;

    private AIRecorder recorder = null;
    private long engine = 0;
    private String currentEngine;//当前引擎
    private JSONObject cfg = null;
    JSONObject params = null;

    private static SkEgnManager mSkEgnManager;

    private Context mContext;

    private SkEgnManager(Context context) {
        mContext = context;
    }

    public static SkEgnManager getInstance(Context context) {
        return mSkEgnManager == null ? mSkEgnManager = new SkEgnManager(context) : mSkEgnManager;
    }

    private Handler mHandler;

    private SkEgn.skegn_callback callback = new SkEgn.skegn_callback() {
        public int run(byte[] id, int type, byte[] data, int size) {
            if (type == SkEgn.SKEGN_MESSAGE_TYPE_JSON) {
                String result = new String(data, 0, size).trim();
                Message message = new Message();
                message.what = CODE_RESULT_OK;
                message.obj = result;
                mHandler.sendMessage(message);
            }
            return 0;
        }
    };

    //初始化引擎
    public void initEngine(String serverType, Handler handler){
        mHandler = handler;
        if(currentEngine==null){
            //开始初始化引擎
            mHandler.sendEmptyMessage(STATUS_START_CREATE_ENGINE);
            /* 初始化cfg */
            cfg = new JSONObject();
            try {
                cfg.put("appKey", AppConfig.appkey);
                cfg.put("secretKey", AppConfig.secretkey);

                // InputStream is = null;
                /* 云端引擎
                 * appKey：*，客户唯一标识
                 * secretKey：*，客户唯一密钥
                 * provision：*，授权证书文件绝对/相对路径(包含文件名)
                 * enable：*，启用云服务，设为1：开启；设为0：关闭；默认为1
                 * server：指定SDK使用的评测服务地址，缺省地址：ws://api.17kouyu.com:8080,灰度地址：ws://gray.17kouyu.com:8090
                 * serverlist：一般不需要手动配置，serverList的地址:https://sdk.17kouyu.com/serverlistssl.txt(SSL)、http://sdk.17kouyu.com/serverlist.txt，server使用指定的服务地址时必须将此参数配置为空字符串“”
                 * connectTimeout：单位：秒(s)，建立连接的超时时间，默认是 10s
                 * serverTimeout：单位：秒(s)，响应的超时时间，默认60s
                 * VAD相关设置请查看开发文档*/
                // cfg.put("cloud", new JSONObject("{\"server\": \"" + AppConfig.cloudServer_release
                //         + "\", serverList:\"\"}"));
                cfg.put("cloud", new JSONObject("{\"enable\": 1}")); //新增
                JSONObject sdkLogObj = new JSONObject();
                sdkLogObj.put("enable", 1);
                sdkLogObj.put("output", AiUtil.externalFilesDir(mContext) + "/sdklog.txt");
                cfg.put("sdkLog", sdkLogObj);

                // is = mContext.getAssets().open(AppConfig.provision);

                // File provisionFile = new File(
                //         AiUtil.externalFilesDir(mContext),
                //         "skegn.provision");
                // AiUtil.writeToFile(provisionFile, is);
                // is.close();
                // cfg.put("provision", null);
                System.out.println(cfg.toString());
            } catch (JSONException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            } /*catch (IOException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }*/
            catch (Exception e) {//新增
                // TODO Auto-generated catch block
                e.printStackTrace();
            }

            engine = SkEgn.skegn_new(cfg.toString(), mContext);

            if(engine != CODE_CREATE_ENGINE_FAIL){
                //初始化引擎成功
                currentEngine = serverType;
                mHandler.sendEmptyMessage(STATUS_CREATE_ENGINE_SUCCESS);
            } else {
                //初始化引擎失败
                mHandler.sendEmptyMessage(STATUS_CREATE_ENGINE_FAIL);
            }

//            recorder = AIRecorder.getInstance();
        }else{
            //引擎已存在
            mHandler.sendEmptyMessage(STATUS_ENGINE_ALREADY_EXISTS);
        }
    }

    /**
     * 初始化参数
     * @param coreType
     * @param refText
     * @param qType
     */
    public void initParams(String coreType, String refText, String qType) {
        params = new JSONObject();
        /*初始化请求参数
        * soundIntensityEnable：默认 0，即不返回音强 (SoundIntensity)值， 可选 1，该值通过 callback 回调返回，返回次数与feed次数一致，维度："sound_intensity"
        * coreProvideType：*，云服务需配置为："cloud"
        * app：*，使用云服务为必须，app: 应用相关信息
        * audio：*，audioType：*，云端支持:wav, mp3, flv, ogg, amr 格式, 本地支持: wav 格式。目前只支持单声道音频
        *           sampleRate：*，采样率, 必须与音频本身采样率一致，不同音频格式有不同的要求, wav格式要求必须是16k，amr支持8k, 16k，其他音频采样率必须大于等于16 kHz
        *           channel：*，目前只支持单声道 1
        * request：*，getParam：在返回结果时同时返回请求参数，默认0关闭，可选1开启
        *             coreType：*，请求的内核类型 目前支持 word.eval(1 单词)/sent.eval(200 单词内)/para.eval(1000 单词内)/open.eval/choice.rec(无限制)/align.eval(音频对比内核)/grammar.rec(语法题)/asr.rec(英文自由识别)。更多详情参考开发文档
        *             refText：使用非音频比对内核时必需，参考文本，多个参考答案用竖线(|)隔开, refText 格式要求请参阅 “参考文本传入格式要求.pdf”
        *             paragraph_need_word_score：仅适用于para.eval，作用：段落评测返回每个单词的具体得分
        *             refAudio：使用音频比对内核时必需，标准音频文件的绝对/相对路径，使用音频比对内核时可选
        *             attachAudioUrl：使用云服务时可选，指定服务器使返回结果附带音频下载地址
        *             dict_type：音素字典选项，默认 KK，可选 CMU/KK/IPA88
        *             phoneme_output：音素纬度开关，默认 0 关闭，1 为开
        *             scale：评分制，取值范围(0,100]
        *             precision：评分精度，建议取值的范围(0,1]
        *             slack：人工干预单词的得分，取值范围[-1,1]，干预后每个单词得分取值范 围[0,100]，正数加分负数减分，一般0.2为轻度调整，1为最强度调整
        *             keywords：关键词，open.eval 题型有效，多个关键词之间用丨隔开
        *             qType：题型，open.eval 题型必须，更多详情参考开发文档*/
        try {
            JSONObject audio = new JSONObject(
                    "{\"audioType\": \"wav\",\"sampleBytes\": 2,\"sampleRate\": 16000,\"channel\": 1,\"compress\": \"speex\"}");
            params.put("app", new JSONObject(
                    "{\"userId\":\"userId0\"}"));
            params.put("coreProvideType", currentEngine);
            JSONObject request = new JSONObject();
            if (coreType.equals(CoreType.EN_WORD_EVAL)){
                request.put("dict_type", "KK");
            }
            request.put("coreType", coreType);
            request.put("attachAudioUrl", 1);
            request.put("getParam", 0);
            if(refText != null){
                if (coreType.contains("open")) {
                    request.put("qClass", 2);
                    request.put("qType", Integer.parseInt(qType));
                }
                request.put("refText", refText);
                request.put("paragraph_need_word_score", 1);
            }
            params.put("audio", audio);
            params.put("request", request);
            System.out.println(params.toString());
        } catch (JSONException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        Log.e("sss", "上传参数params===>" + params.toString());
    }

    //开始录制
    public void startRecord(String coreType, String refText, String qType, Handler handler){
        //取消之前引擎所有操作, 相当于reset操作
        SkEgn.skegn_cancel(engine);
        if(recorder == null){
            recorder = AIRecorder.getInstance();
        }
        //初始化参数
        initParams(coreType, refText, qType);

        mHandler = handler;
        byte[] id = new byte[64];
        int rv = SkEgn.skegn_start(engine, params.toString(), id,
                callback, mContext);
        if(rv!=0){
            setResult("skegn_start failed", coreType);
            return;
        }

        status1 = engine_status.RECORDING;

        String wavPath = AiUtil.getFilesDir(mContext).getPath()
                + "/record/" + new String(id).trim() + ".wav";
        recorder.start(wavPath, new AIRecorder.Callback() {
            public void run(byte[] data, int size) {
                SkEgn.skegn_feed(engine, data, size);
            }
        });
    }

    //停止录制
    public void stopRecord(){
        SkEgn.skegn_stop(engine);
        if(recorder != null){
            recorder.stop();
        }
        status1 = engine_status.STOP;
    }

    //回放
    public void playback(){
        if(recorder != null){
            recorder.playback();
        }
    }

    //引擎回收(停止)
    public void recycle(){
        currentEngine = null;
        if (engine != CODE_CREATE_ENGINE_FAIL) {
            SkEgn.skegn_delete(engine);
            status1 = engine_status.STOP;
        }
        if (recorder != null) {
            recorder.stop();
            recorder = null;
        }
    }

    public String setResult(String r, String coreType)
    {
        StringBuilder keyValue = new StringBuilder();
        JSONObject json;
        JSONObject resultjson;
        try {
            json = new JSONObject(r);
            if(json != null && json.has("result")){
                resultjson = json.getJSONObject("result");
                if(resultjson.has("overall")){
                    keyValue.append("总    分: " + resultjson.getString("overall") + "\n");
                }
                if(resultjson.has("integrity")){
                    keyValue.append("完整度: " + resultjson.getString("integrity") + "\n");
                }
                if(resultjson.has("recognition")){
                    keyValue.append("识别结果: " + resultjson.getString("recognition") + "\n");
                }
                if(resultjson.has("confidence")){
                    keyValue.append("匹配度: " + resultjson.getString("confidence") + "\n");
                }
                if(resultjson.has("fluency")){
                    keyValue.append("流利度: " + resultjson.getString("fluency") + "\n");
                }
                if(resultjson.has("pronunciation")){
                    keyValue.append("发音得分：" + resultjson.getString("pronunciation") + "\n");
                }
                if(resultjson.has("speed")){
                    keyValue.append("语速：" + resultjson.getString("speed") + " 词/分\n");
                }
                if(resultjson.has("rear_tone") && coreType.equals(CoreType.EN_SENT_EVAL) && resultjson.getInt("overall") > 0){
                    keyValue.append("句末语调：" + resultjson.getString("rear_tone") + "\n");
                }
                if(coreType.equals(CoreType.EN_WORD_EVAL)){
                    keyValue.append("音素得分：/");
                    JSONArray wjsono = resultjson.getJSONArray("words");
                    JSONArray wjson = wjsono.getJSONObject(0).getJSONArray("phonemes");
                    for(int i=0; i<wjson.length(); i++)
                    {
                        keyValue.append(wjson.getJSONObject(i).getString("phoneme") + ":" + wjson.getJSONObject(i).getString("pronunciation") + " /");
                    }
                    keyValue.append("\n");
                }else if(coreType.equals(CoreType.EN_SENT_EVAL)){
                    keyValue.append("单词得分：\n");
                    JSONArray wjsono = resultjson.getJSONArray("words");
                    for(int i=0; i<wjsono.length(); i++){
                        String word = wjsono.getJSONObject(i).getString("word").replaceAll("\\.|\\,|\\!|\\;|\\?|\"", "");
                        if(word.startsWith("\'") || word.endsWith("\'")){
                            word = word.replace("\'", "");
                        }
                        keyValue.append(word + ": ");
                        keyValue.append(wjsono.getJSONObject(i).getJSONObject("scores").getString("overall") + "  ");
                    }
                    keyValue.append("\n");
                }
//                keyValue.append("\n结果详情:\n" + resultjson.toString(4));
                keyValue.append("\n结果详情:\n" + json.toString(4));
                r = "";
            }
        } catch (JSONException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        return keyValue.append(r).toString();
    }

}
