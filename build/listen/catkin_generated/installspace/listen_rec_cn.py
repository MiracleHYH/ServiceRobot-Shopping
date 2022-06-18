#! /home/zzy/anaconda3/envs/ros/bin/python
# -*- coding: utf-8 -*-
from __future__ import print_function
from pickle import FALSE
from ssl import ALERT_DESCRIPTION_DECOMPRESSION_FAILURE
import rospy
import sys
import json
import time
import record
import os
from listen.srv import listen,listenResponse
from colorama import Fore
from listen.msg import listen_results
from std_msgs import msg
import std_msgs


IS_PY3 = sys.version_info.major == 3
if IS_PY3:
    from urllib.request import urlopen
    from urllib.request import Request
    from urllib.error import URLError
    from urllib.parse import urlencode

    timer = time.perf_counter
else:
    import urllib3
    from urllib3 import urlopen
    from urllib3 import Request
    from urllib3 import URLError
    from urllib import urlencode

    if sys.platform == "win32":
        timer = time.clock
    else:
        # On most other platforms the best timer is time.time()
        timer = time.time

API_KEY = 'm1gRTsALZa9GMZvQVrQLReri'
SECRET_KEY = 'hOasA5hHYAA3cgQAY9SGKOnSGvjC2VUq'

# 需要识别的文件
AUDIO_FILE = './audio/result.wav'  # 只支持 pcm/wav/amr 格式，极速版额外支持m4a 格式
# 文件格式
FORMAT = AUDIO_FILE[-3:];  # 文件后缀只支持 pcm/wav/amr 格式，极速版额外支持m4a 格式

CUID = '123456PYTHON';
# 采样率
RATE = 16000;  # 固定值

# 普通版

DEV_PID = 1737;#1537;  # 1537 表示识别普通话，使用输入法模型。根据文档填写PID，选择语言及识别模型，1737为英语
ASR_URL = 'http://vop.baidu.com/server_api'
SCOPE = 'audio_voice_assistant_get'  # 有此scope表示有asr能力，没有请在网页里勾选，非常旧的应用可能没有

class DemoError(Exception):
    pass


"""  TOKEN start """

TOKEN_URL = 'http://openapi.baidu.com/oauth/2.0/token'


def fetch_token():
    params = {'grant_type': 'client_credentials',
              'client_id': API_KEY,
              'client_secret': SECRET_KEY}
    post_data = urlencode(params)
    if (IS_PY3):
        post_data = post_data.encode('utf-8')
    req = Request(TOKEN_URL, post_data)
    try:
        f = urlopen(req)
        result_str = f.read()
    except URLError as err:
        #print('token http response http code : ' + str(err.code))
        result_str = err.read()
    if (IS_PY3):
        result_str = result_str.decode()
    #print(result_str)
    result = json.loads(result_str)
    #print(result)
    if ('access_token' in result.keys() and 'scope' in result.keys()):
        if SCOPE and (not SCOPE in result['scope'].split(' ')):  # SCOPE = False 忽略检查
            raise DemoError('scope is not correct')
        #print('SUCCESS WITH TOKEN: %s ; EXPIRES IN SECONDS: %s' % (result['access_token'], result['expires_in']))
        return result['access_token']
    else:
        raise DemoError('MAYBE API_KEY or SECRET_KEY not correct: access_token or scope not found in token response')


"""  TOKEN end """
def kmp(string1)->int:
    if string1.find('一')!=-1:
        return 1
    elif string1.find('二')!=-1:
        return 2
    elif string1.find('三')!=-1:
        return 3
    elif string1.find('四')!=-1:
        return 4
    else:
        return 0

results=rospy.Publisher('listen_results',listen_results)
def chattback(req):
    os.chdir('/home/slam-dunk/catkin_ws/src/listen/scripts/audio')
    record.audio_record('result.wav',5)
    os.chdir(os.path.split(os.getcwd())[0])#record
    token=fetch_token()
    speech_data = []
    with open(AUDIO_FILE, 'rb') as speech_file:
        speech_data = speech_file.read()
    length = len(speech_data)
    if length == 0:
        raise DemoError('file %s length read 0 bytes' % AUDIO_FILE)

    params = {'cuid': CUID, 'token': token, 'dev_pid': DEV_PID}
    #测试自训练平台需要打开以下信息
    #params = {'cuid': CUID, 'token': token, 'dev_pid': DEV_PID, 'lm_id' : LM_ID}
    params_query = urlencode(params);

    headers = {
        'Content-Type': 'audio/' + FORMAT + '; rate=' + str(RATE),
        'Content-Length': length
    }

    url = ASR_URL + "?" + params_query
    #print("url is", url);
    #print("header is", headers)
    # print post_data
    req = Request(ASR_URL + "?" + params_query, speech_data, headers)
    try:
        begin = timer()
        f = urlopen(req)
        result_str = f.read()
        result_str=result_str.decode()
        result=json.loads(result_str)
        print(result['result'])
        print("Request time cost %f" % (timer() - begin))
        index=0
        res=listen_results()
        for i in result['result']:
            index=kmp(i)
            print(index) 
            res.index=index
            res.results=str(i).encode
            results.publish(res)
            if index!=0:
                return listenResponse(True)
    except  URLError as err:
        print('asr http response http code : ' + str(err.code))
        result_str = err.read()
    return listenResponse(False)
    



def listen_server():
    rospy.init_node('listen-cn',anonymous=False)
    rospy.loginfo(msg=f'''{Fore.GREEN}调用服务/listen_dst来开启一次语音识别，当识别到关键字的时候，返回True，否则返回False
    结果存储在一个消息类型为listen_results中：
    1-results建存储着识别结果
    2-index存储匹配结果''')
    s=rospy.Service('listen_dst',listen,chattback)
    print("ready to listen")
    rospy.spin()

if __name__ == '__main__':
    try:
        listen_server()
    except rospy.ROSInterruptException:
        pass
