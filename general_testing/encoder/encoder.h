#ifndef ENCODER_H
#define ENCODER_H
class Encoder
{
    public:
    unsigned char pinA;
    unsigned char pinB;
    int position;
    unsigned char state;

    Encoder(unsigned char pinALoc, unsigned char pinBLoc);

    int read();

    void registerCallback();
};
#endif