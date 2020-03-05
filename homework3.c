#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "homework3.h"
#include "myGPIO.h"
#include "myTimer.h"

int main(void)
{
    // Count variables to control the LEDs.
    unsigned int count0 = 0;
    unsigned int count1 = 0;

    // TODO: Declare the variables that main uses to interact with your state machine.
    unsigned char BoosterPack_Button_History = UNPRESSED_BUTTON;
    // Stops the Watchdog timer.
    initBoard();
    // Initialize the GPIO.
    // YOU MUST WRITE THIS FUNCTION IN myGPIO.c
    initGPIO();
    // Initialize Timer0 to provide a one second count interval for updating LED2.
    // YOU MUST WRITE THIS FUNCTION IN myTimer.c
    initTimer(TIMER32_0_BASE, TIMER0_PRESCALER, TIMER0_COUNT);
    // Initialize Timer1 to provide a one millisecond count interval for updating the button history.
    // YOU MUST WRITE THIS FUNCTION IN myTimer.c
    initTimer(TIMER32_1_BASE, TIMER1_PRESCALER, TIMER1_COUNT);

    while(1)
    {
        bool pressed_flag = false;
        // Update the color of LED2 using count0 as the index.
        // YOU MUST WRITE THIS FUNCTION BELOW.
        changeLaunchpadLED2(count0);
        // Update the color of the Boosterpack LED using count1 as the index.
        // YOU MUST WRITE THIS FUNCTION BELOW.
        changeBoosterpackLED(count1);

        // TODO: If Timer0 has expired, increment count0.
        // YOU MUST WRITE timer0expired IN myTimer.c
        if(timer0Expired())
            count0++;

        // TODO: If Timer1 has expired, update the button history from the pushbutton value.
        // YOU MUST WRITE timer1expired IN myTimer.c
        if(timer1Expired())
        {
            BoosterPack_Button_History = ((BoosterPack_Button_History << 1) | checkStatus_BoosterpackS1());
        }


        // TODO: Call the button state machine function to check for a completed, debounced button press.
        // YOU MUST WRITE THIS FUNCTION BELOW.
        if(fsmBoosterpackButtonS1(BoosterPack_Button_History))
            pressed_flag = true;


        // TODO: If a completed, debounced button press has occurred, increment count1.
        if(pressed_flag)
            count1++;
    }
}

void initBoard()
{
    WDT_A_hold(WDT_A_BASE);
}

// TODO: Map the value of a count variable to a color for LED2.
// Since count is an unsigned integer, you can mask the value in some way.
void changeLaunchpadLED2(unsigned int count)
{
    enum{
                OFF = 0b000,
                RED = 0b001,
                BLUE = 0b010,
                GREEN = 0b011,
                MAGENTA = 0b100,
                YELLOW = 0b101,
                CYAN = 0b110,
                WHITE = 0b111

            };
    if((count & MASK) == RED)
        turnOn_LaunchpadLED2Red();
    else if((count & MASK) == BLUE)
    {
        turnOff_LaunchpadLED2Red();
        turnOn_LaunchpadLED2Blue();
    }
    else if((count & MASK) == GREEN)
    {
        turnOff_LaunchpadLED2Blue();
        turnOn_LaunchpadLED2Green();
    }
    else if((count & MASK) == MAGENTA)
    {
        turnOff_LaunchpadLED2Green();
        turnOn_LaunchpadLED2Red();
        turnOn_LaunchpadLED2Blue();
    }
    else if((count & MASK) == YELLOW)
    {
        turnOff_LaunchpadLED2Blue();
        turnOn_LaunchpadLED2Green();
    }
    else if((count & MASK) == CYAN)
    {
        turnOff_LaunchpadLED2Red();
        turnOn_LaunchpadLED2Blue();
    }
    else if((count & MASK) == WHITE)
    {
        turnOn_LaunchpadLED2Green();
        turnOn_LaunchpadLED2Red();
    }
    else
    {
        turnOff_LaunchpadLED2Red();
        turnOff_LaunchpadLED2Blue();
        turnOff_LaunchpadLED2Green();
    }
}

// TODO: Maybe the value of a count variable to a color for the Boosterpack LED
// This is essentially a copy of the previous function, using a different LED
void changeBoosterpackLED(unsigned int count)
{
    enum{
                OFF = 0b000,
                RED = 0b001,
                BLUE = 0b010,
                GREEN = 0b011,
                MAGENTA = 0b100,
                YELLOW = 0b101,
                CYAN = 0b110,
                WHITE = 0b111

            };
    if((count & MASK) == RED)
        turnOn_BoosterpackLEDRed();
        else if((count & MASK) == BLUE)
        {
            turnOff_BoosterpackLEDRed();
            turnOn_BoosterpackLEDBlue();
        }
        else if((count & MASK) == GREEN)
        {
            turnOff_BoosterpackLEDBlue();
            turnOn_BoosterpackLEDGreen();
        }
        else if((count & MASK) == MAGENTA)
        {
            turnOff_BoosterpackLEDGreen();
            turnOn_BoosterpackLEDRed();
            turnOn_BoosterpackLEDBlue();
        }
        else if((count & MASK) == YELLOW)
        {
            turnOff_BoosterpackLEDBlue();
            turnOn_BoosterpackLEDGreen();
        }
        else if((count & MASK) == CYAN)
        {
            turnOff_BoosterpackLEDRed();
            turnOn_BoosterpackLEDBlue();
        }
        else if((count & MASK) == WHITE)
        {
            turnOn_BoosterpackLEDGreen();
            turnOn_BoosterpackLEDRed();
        }
        else
        {
            turnOff_BoosterpackLEDRed();
            turnOff_BoosterpackLEDBlue();
            turnOff_BoosterpackLEDGreen();
        }
}

// TODO: Create a button state machine.
// The button state machine should return true or false to indicate a completed, debounced button press.
bool fsmBoosterpackButtonS1(unsigned char buttonhistory)
{
    bool pressed = false;
    static unsigned char B1_History = UNPRESSED_BUTTON;
    static enum{
        Unpressed,
        Pressed
    }state;
    switch(state)
    {
    case Unpressed:
        if(B1_History != PRESSED_BUTTON && buttonhistory == PRESSED_BUTTON)
            state = Pressed;
        break;
    case Pressed:
        if(B1_History != UNPRESSED_BUTTON && buttonhistory == UNPRESSED_BUTTON)
        {
            state = Unpressed;
            pressed = true;
        }
    }
    B1_History = buttonhistory;
    return pressed;
}
