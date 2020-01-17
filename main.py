import machine, ssd1306, time
from hx711 import HX711
from scales import Scales
from machine import Pin


# Kalibrierungswert
cal_140 = 60000

# Pin 25 und 26 für i2c einrichten
i2c = machine.I2C(scl=machine.Pin(25), sda=machine.Pin(26))

# init Oled mit i2c
oled = ssd1306.SSD1306_I2C(128, 32, i2c, 0x3c)
oled.fill(0)

# Pin für Tara Taste einrichten
tara_pin = Pin(12, Pin.IN, Pin.PULL_UP)


# Bootscreen anzeigen
oled.text("Kaffee Waage", 10, 5)
oled.show()
time.sleep(1)

# Wägezelle initialisieren
scl = Scales(d_out=4, pd_sck=5)

# 
scl.tare()
while True:
    val = scl.stable_value(5,0)
    weight = round(140 * val / cal_140, 1)
    if weight < 0.5:
        if weight < -0.5:
            oled.fill(0)
            oled.text('negative value!', 0, 20)
            oled.show()
        else:
            weight = 0.0
    
    if weight >= 0:
        oled.fill(0)
        oled.text(str(weight)+'g', 0, 10)
        oled.show()

    # Tara Taste ablesen und gegebenfalls scl über die tara() Funktion zurücksetzen.
    if tara_pin.value() == 0: # Tara Taste wurde ausgelöst
        oled.fill(0)
        oled.text('Tara...', 0, 20)
        oled.show()
        scl.tare()



