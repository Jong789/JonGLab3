#include "mbed.h"
#include "LSM6DSLSensor.h"

#define PI 3.141592654

/* This program reads data from the 3-axis accelerometer, 
displays data for the x,y,z accelerometer values, 
and computes the pitch angle of the mbed board with respect to horizontal along the x-axis,
using these x,y,z accelerometer values */

static DevI2C devI2c(PB_11,PB_10);
static LSM6DSLSensor acc_gyro(&devI2c,0xD4,D4,D5); // high address

const float pi = 3.141592654; // declare value of pi as a constant 

float computeAngle(int x, int y, int z){
    float res = 0;

    float pitch_radians = 0;    // declare variable for radians result from equation 6
    int y_squared = y * y;  // to calculate y squared for equation 6 
    int z_squared = z * z;  // to calculate z squared for equation 6

        pitch_radians = atan ((x / (sqrt(y_squared + z_squared)))); // Equation 6 from datasheet 
    
        res = pitch_radians * (180 / pi); // to convert radians to degrees

    return res;
}

/* Simple main function */
int main() {
    uint8_t id;
    int32_t axes[3];
    float res=0;
    acc_gyro.init(NULL);

    acc_gyro.enable_x();
    acc_gyro.enable_g();

    printf("This is an accelerometer example running on Mbed OS %d.%d.%d.\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
    acc_gyro.read_id(&id);
    printf("LSM6DSL accelerometer & gyroscope = 0x%X\r\n", id);

    while(1) {

        acc_gyro.get_x_axes(axes);
        res = computeAngle(axes[0], axes[1], axes[2]);
        printf("LSM6DSL: %6d, %6d, %6d, %3.2f\r\n", axes[0], axes[1], axes[2], res);


        thread_sleep_for(2000);

    }
}