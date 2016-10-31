// Vibration.h


/*
 * Initialize the vibration sensors and flex sensor. Calls ADC
 * initialization from inside the function call.
 * Input: None
 * Output: None
 */
void Init_Vibration_Sensors(void);


// ***************************************************
// Following are test functions that may or may not end up
// being implemented
// ***************************************************
void TestFlexSensor(void);

void TestEasyTriggerVibrationSensor(void);

void TestMedTriggerVibrationSensor(void);
