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
	* U與D已改成 M280 P0 S(deg)
	* <b style={color:green}>complete</b>

### configuration.h
	* 就一堆跟硬體和pin腳位有關的define
	* <b style={color:green}>complete</b>
	
### motor_driver.h
	* Servo
		* 上下而已，寫一個吃bool，0上筆1下筆
		* 還有一個可以吃角度的函式
		* <b style="color:green;">complete</b>
		* <b style="color:red;">挖code給小隊員實作</b>
	* Stepper
		* 給(pos x, pos y), 馬達工作，暫時寫死F
		* void Move_Stepper_Linear(float x, float y); // x, y for milimeter, 準備直線移動到(x, y)
		* 用麵+詹的神奇手刻方波解決問題
		* <b style="color:green;">complete</b>
	* Enable
		* 其實是可以兩個馬達分別enable的
		* ena_pin 已分開，用限動開關操控
		* <b style="color:green;">complete</b>
		
	* Homing
		* <b style="color:green;">complete</b>
		* <b style="color:red;">挖code給小隊員實作</b>
		
	* Caution: M112 / M410 interupt功能：拔插頭或是關電源吧
		
### gcode file
	* 極度土炮vector
	* <b style={color:green}>complete</b>
	* <b style="color:red;">挖code給小隊員實作</b>

米納桑甘巴爹
![](backend_devs.jpg)
