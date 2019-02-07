#ifndef JOY_DEF
#define JOY_DEF

class Joystick {
    public:
        unsigned int MAX_VAL, MIN_VAL, PIN_ANALOG, PIN_BUTTON;
        Joystick(unsigned int, unsigned int);
        Joystick(unsigned int, unsigned int, unsigned int, unsigned int);
        int getValue();
};

#endif
