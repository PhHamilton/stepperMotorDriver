#include <Arduino.h>
#include "MotorDriverClass.h"

#define CLOCKWISE 1 
#define COUNTERCLOCKWISE 0 

MotorDriver::MotorDriver(uint8_t stepPin, uint8_t dirPin, uint8_t enablePin)
{
    _stepPin = stepPin; 
    _dirPin = dirPin;
    _enablePin = enablePin;
}

void MotorDriver::initialize(void)
{
    pinMode(_stepPin, OUTPUT);
    pinMode(_dirPin, OUTPUT);
    pinMode(_enablePin, OUTPUT);
    _direction(CLOCKWISE);
    _enableMotor(false);
}

void MotorDriver::oneRevolution(void)
{
    smoothStep(stepsPerRev);
}

void MotorDriver::rotateDegrees(float deg)
{
    smoothStep(_degToSteps(deg));
}

void MotorDriver::rotateRadians(float rad)
{
    smoothStep(_radToSteps(rad));
}


void MotorDriver::smoothStep(uint16_t smoothStep)
{

    _fStepFactor = ((maxFrequency-minFrequency)/_stepsToAccelerate(smoothStep));

    if(_stepCounter != smoothStep)
    {
        _enableMotor(true);
        if(_stepCounter < _stepsToAccelerate(smoothStep)) //Acceleration
        {
            _step(minFrequency + _fStepFactor*(_stepCounter+1));
        }
        
        else if(_stepCounter >= smoothStep - _stepsToAccelerate(smoothStep)) //Deacceleration
        {
            _step(maxFrequency - _fStepFactor*(_stepCounter - (smoothStep - _stepsToAccelerate(smoothStep))));
        }
        
        else // Constant speed phase
            _step(maxFrequency);
        _stepCounter++; 
    }
    else
    {
        _enableMotor(false);
    }
}

float MotorDriver::_stepsToAccelerate(uint16_t nSteps)
{
    if(accelerationPercent > 50) accelerationPercent = 50; 
    if(accelerationPercent < 0) accelerationPercent = 0;

    return (nSteps*accelerationPercent/100);
}

uint16_t MotorDriver::_degToSteps(float deg)
{
    deg < 0 ? _direction(COUNTERCLOCKWISE) : _direction(CLOCKWISE);
    return (uint16_t)(stepsPerRev*((float)abs(deg)/360));
}

uint16_t MotorDriver::_radToSteps(float rad)
{
    rad < 0 ? _direction(COUNTERCLOCKWISE) : _direction(CLOCKWISE);
    return (uint16_t)(stepsPerRev*((float)abs(rad)/(2*PI)));
}

void MotorDriver::_step(uint16_t frequency)
{
    t_off = (uint16_t)(1000000/frequency) - t_on;
    


    digitalWrite(_stepPin, HIGH);
    delayMicroseconds(t_on);
    digitalWrite(_stepPin, LOW);
    delayMicroseconds(t_off);

    
    
    
    /*

_currentMicros = micros();

    switch(_x)
    {
    case 0:
        if(_currentMicros - _previousMicros <= t_on)
        { 
            digitalWrite(_stepPin, HIGH);
        }
        else
        {
            _previousMicros = _currentMicros;
            _x = 1;
        }
            
        break;
    case 1:
        if(_currentMicros - _previousMicros <= t_off)
        {
            digitalWrite(_stepPin, LOW);
            
        }
        else
        {   
            _previousMicros = _currentMicros;
            _x = 0; 
        }
        break;
    default:
        break;
    }
    */
    
    
}

void MotorDriver::_enableMotor(bool state)
{
    state == true ? digitalWrite(_enablePin, LOW) : digitalWrite(_enablePin, HIGH);
}

void MotorDriver::_direction(bool dir)
{
    if(dir == CLOCKWISE)
    {
        digitalWrite(_dirPin, HIGH); 
         
    }
    else
    {
        digitalWrite(_dirPin, LOW);  
        
    }
    
}
