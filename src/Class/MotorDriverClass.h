#ifndef MotorDriverClass_h
#define MotorDriverClass_h

#include "Arduino.h"

class MotorDriver
{ 
    public:
        MotorDriver(uint8_t stepPin, uint8_t dirPin, uint8_t enablePin);
        void rotateDegrees(float deg);
        void rotateRadians(float rad);
        void smoothStep(uint16_t nSteps);
        void oneRevolution(void);   
        void initialize(void);
        
        uint16_t t_on = 5; //us
        uint16_t stepsPerRev = 200; 
        uint16_t minFrequency = 250;
        uint16_t maxFrequency = 1300;
        uint8_t accelerationPercent = 30; 
    private:
    
    unsigned long _previousMicros = 0; 
    unsigned long _currentMicros;
    
    uint8_t _stepPin;
    uint8_t _dirPin;
    uint8_t _enablePin;

    uint16_t t_off; 
    uint16_t _x = 0;

    bool _state = 0; 
    bool _dir;

    void _moveNumberOfSteps(uint16_t steps);
    float _stepsToAccelerate(uint16_t nSteps);
    uint16_t _degToSteps(float deg);
    uint16_t _radToSteps(float rad);
    void _step(uint16_t frequency);  
    uint16_t _stepCounter = 0; 
    uint16_t _aSteps = 0;

    float _fStepFactor = 0; 
    void _enableMotor(bool state); 
     
    void _direction(bool dir);

};


#endif