# Elevate_Gcode
Gcode Firmware for the NTUEE Elevate CNC Writing Project

分工

main.ino
  loop還沒寫
  就Serial.readStringUntil('\n');
  然後丟進去parser
  parse成vector了以後丟到translator裡面
  translator會自動完成Gcode翻譯和馬達作動

configuration.h
  就一堆跟硬體和pin腳位有關的define
  羊
  
motor_driver.h
  Servo
    上下而已，寫一個吃bool，0上筆1下筆
    void Move_Pen(bool b);
    感覺可以讓小隊員實作
  Stepper
    給(pos x, pos y), 馬達工作，暫時寫死F
    void Move_Stepper_Linear(float x, float y); // x, y for milimeter, 準備直線移動到(x, y)
    void Move_Stepper_Cicular_R(bool b, float x, float y, float r); // b=0逆時針，b=1順時針，準備移動到(x, y)，圓半徑r
    void Move_Stepper_Cicular_IJ(bool b, float x, float y, float i, float j); // b順逆，準備移動到(x, y)，圓心(i, j)
  Enable
    void Enable_Stepper_X(bool b); // 0 for disable, 1 for enable
    void Enable_Stepper_Y(bool b); // 0 for disable, 1 for enable
    bool Get_Enable_X(); // return X_enable
    bool Get_Enable_Y();
  晚點大家一起吸
  其實還有一些G28(Homing)和G92(Coordinate)之類的功能沒做
  感覺Homing可以讓小隊員實作
  Caution: M112 / M410 interupt功能
    
gcode_parser.h
  https://github.com/maniacbug/StandardCplusplus/blob/master/README.md
  上面的可以讓你arduino用stl
  String in -> std::vector<String> out
  std::vector<String> Function(String in)
  記得把G0 X30 Y30 F50的F暫時吃掉
  
gcode_headers.h
  std::vector in -> Move_Stepper/Move_Pen
  void seperator(std::vector<String> v); // 純粹靠v[0]分成g和m
  output g/m後面那串數字和v[1:]
  gcode_gheader.h
    void g_code_translator(int num, std::vector<String> v);
  gcode_mheader.h
    void m_code_translator(int num, std::vector<String> v)
