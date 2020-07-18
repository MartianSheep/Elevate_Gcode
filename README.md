<!-------------------------------------------------------------------------
	FileName		[ README.md ]
	PackageName		[ Elevate_Gcode ]
	Function		[ README file of the NTUEE CNC Drawing Machine ]
	Author			[ Teaching Group, Elevate, NTUEE ]
	Time			[ 2020 Jul.-present, NTUEE, NTU, Taipei, Taiwan ]
	Copyright		[ Copyleft(c) 2020-present NTUEE, NTU, Taiwan ]
-------------------------------------------------------------------------->

# Elevate_Gcode
Gcode Firmware for the NTUEE Elevate CNC Mini Drawing Machine Project

## 分工

### main.ino
	* 應該是寫完了
	* U和D因為不是Gcode先寫在這裡

### configuration.h
	* 就一堆跟硬體和pin腳位有關的define
	
### motor_driver.h
	* Servo
		* 上下而已，寫一個吃bool，0上筆1下筆
		* 還有一個可以吃角度的函式
		* 感覺可以讓小隊員實作
	* Stepper
		* 給(pos x, pos y), 馬達工作，暫時寫死F
		* void Move_Stepper_Linear(float x, float y); // x, y for milimeter, 準備直線移動到(x, y)
		* issue: 為什麼他程式那麼快就跑完了，啊我馬達有可能還沒動完
		* 有可能delay改用millis()或micros()
	* Enable
		* 其實是可以兩個馬達分別enable的
		* 現在純粹是把ena_pin設成一樣，然後G28就一起enable
	* 感覺Homing可以讓小隊員實作
	* Caution: M112 / M410 interupt功能：拔插頭或是關電源吧
		
### gcode file
	* 極度土炮vector
	* 目前看來好像沒問題，不知道

米納桑甘巴爹
![](backend_devs.jpg)