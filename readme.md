
# 我的智能家居解决方案 #

### 射频控制电灯等简单电路 ###

##### 射频开关使用 #####
![射频单火线开关RF433](images/rf433_05.jpg)
学习型开关,可学习toggle,总开,总关等信号,220V,130W 频率433.92MHz


##### 射频发射模块(带编码) #####
![射频遥控模块](images/rf433_04.jpg)
射频遥控模块,带编码,通信方式串口

	0xDF 0x03 0x01 0x01 0x01 0xA0 0xFD 固定 长度 地址 地址 键码 震荡 固定

发射详见rf433.c


##### homebridge #####
##### homebridge-cmd #####	
~/.homebridge/config.json
```Json
{
    "bridge": {
        "name": "Homebridge",
        "username": "E5:22:1D:E3:C2:39",
        "port": 51826,
        "pin": "032-78-211"
    },
    "description": "The Onion!",
    "platforms": [],
    "accessories": [
        {
            "accessory": "CMD",
            "name": "空调",
            "on_cmd": "python /home/pi/python/ir.py 03 send",
            "off_cmd": "python /home/pi/python/ir.py 04 send"
        },
        {
            "accessory":"CMD",
            "name":"灯",
            "on_cmd":"sudo /home/pi/home/rf433 01 01 01",
        }
    ]
}
```




rf433射频

红外
