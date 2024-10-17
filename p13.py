import time
from pyfirmata import Arduino, util

# 建立與 Arduino 的連接
board = Arduino('COM6')

# 定義 LED pin = digital 13 output
#led_pin = board.get_pin('d:13:o') 
it = util.Iterator(board) #避免序列溢位
it.start()

while True:
    # 開啟 LED
#    led_pin.write(1)
    board.digital[13].write(1)
    time.sleep(0.5)  # 暫停

    # 關閉 LED
#    led_pin.write(0)
    board.digital[13].write(0)
    time.sleep(0.5)  # 暫停
    
    board.analog[0].enable_reporting()
    print (board.analog[0].read())
    time.sleep(1)    
