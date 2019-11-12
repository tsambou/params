#include <Bela.h>
#include "global.h"

class Encoders
{
    
private:
    char mInput_pin;
    BelaContext *mContext;
    int mPin[8],mPin_prev[8];
    float mIncr[4],mIncr_prev[4];
    
    
public:
    explicit inline Encoders(BelaContext *context, char Input_pin) :
    mInput_pin(Input_pin) , mContext(context) {} // : Member Initializer
    
    void read();

    float getIncr(int index);

};
