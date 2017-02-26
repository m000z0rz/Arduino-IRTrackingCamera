
#ifndef IRTrackingCamera_h
#define IRTrackingCamera_h

struct Vector2 {
    int x;
    int y;
};

class IRTrackingCamera {

private:
    static int _i2cAddress;
    unsigned char _buffer[16]; // for storing raw data from I2C

    static void sendTwoBytesAndDelay(unsigned char b1, unsigned char b2, unsigned long delay_ms);

public:
    Vector2 Points[4];
    //unsigned char PointCount;

    IRTrackingCamera();
    //~IRTrackingCamera();

    void initialize();
    void update(); // returns # of points currently detected
};

#endif
