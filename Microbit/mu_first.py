# Write your code here :-)
from microbit import *

class Car():
    def __init__(self,a,b):
        self.name=a
        self.year=b
    def detail(self):
        display.show(self.name)
        display.show(self.year)

class Bus(Car):
    def __init__(self,a,b,c):
        self.capticity=a
        super().__init__(b,c)
        
    def detail(self):
        display.show(self.capticity)
        super().detail()

    
mycar = Car("Ford",2012)
yourcar = Bus(10,"Toyata",2013)

while True:
    if button_a.is_pressed():
        mycar.detail()
    elif button_b.is_pressed():
        yourcar.detail()
    else:
        display.show(Image.HAPPY)