from machine import Pin, PWM
import time

# Pins setup
ultrasonic_trigger = Pin(26, Pin.OUT)  # Trigger pin for ultrasonic sensor
ultrasonic_echo = Pin(27, Pin.IN)     # Echo pin for ultrasonic sensor
servo_pin = PWM(Pin(15))               # Servo on GPIO15
pir_sensor = Pin(0, Pin.IN)            # PIR sensor on GPIO0
garage_light = Pin(16, Pin.OUT)        # Garage light on GPIO16
buzzer = Pin(5, Pin.OUT)               # Buzzer on GPIO5

# Servo settings
servo_pin.freq(50)  # Frequency for servo motor (50Hz)

# Function to measure distance using ultrasonic sensor
def measure_distance():
    ultrasonic_trigger.low()
    time.sleep_us(2)
    ultrasonic_trigger.high()
    time.sleep_us(10)
    ultrasonic_trigger.low()

    # Initialize variables
    pulse_start = 0
    pulse_end = 0

    while ultrasonic_echo.value() == 0:
        pulse_start = time.ticks_us()
    while ultrasonic_echo.value() == 1:
        pulse_end = time.ticks_us()

    pulse_duration = time.ticks_diff(pulse_end, pulse_start)
    distance = (pulse_duration * 0.0343) / 2  # Convert to cm
    return distance

# Function to set servo angle
def set_servo_angle(angle):
    min_duty = 1000  # Adjust as per your servo’s requirement
    max_duty = 9000  # Adjust as per your servo’s requirement
    duty = min_duty + (angle / 180) * (max_duty - min_duty)
    servo_pin.duty_u16(int(duty))

# Main loop
while True:
    # Check for car presence using ultrasonic sensor
    distance = measure_distance()
    if distance < 10:
        buzzer.on() 
    if distance < 50:  # Car detected within 50 cm
        set_servo_angle(90)  # Open gate
        garage_light.on()
         # Turn on buzzer to alert car to stop
    else:
        set_servo_angle(0)  # Close gate
        buzzer.off()  # Turn off buzzer
    
    # PIR sensor to turn on garage light if motion detected
    if pir_sensor.value() == 1:  # Motion detected
        garage_light.on()
    else:
        garage_light.off()
    
    
