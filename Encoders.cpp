#include "Encoders.h"

void Encoders::read()
{
    
    for (unsigned int i=0 ; i<8 ; i++)
    {
        mPin_prev[i] = mPin[i];
        mPin[i] = digitalRead(mContext,2*i,mInput_pin);
    }
    
    // First time program runs (gCount == 0) initialize previous state of pins with current state
    if (gCount == 0)
    {
        for (unsigned int i=0 ; i<8 ; i++){
            mPin_prev[i] = mPin[i];
        }
    }
    
    // determine whether one encoder is turned, and increment the corresponding member variable mIncr[i]
    for (unsigned int i=0; i<4; i++)
    {
        
        if (mPin[i*2] != mPin_prev[i*2] || mPin[i*2+1] != mPin_prev[i*2+1] )
        {
            if (mPin[i*2+1] == 1)
            {
                if (mPin[i*2] > mPin_prev[i*2]) mIncr[i]++;
                if (mPin[i*2] < mPin_prev[i*2]) mIncr[i]--;
            }
            if (mPin[i*2+1] == 0)
            {
                if (mPin[i*2] > mPin_prev[i*2]) mIncr[i]--;
                if (mPin[i*2] < mPin_prev[i*2]) mIncr[i]++;
            }
            if (mPin[i*2] == 0)
            {
                if (mPin[i*2+1] > mPin_prev[i*2+1]) mIncr[i]++;
                if (mPin[i*2+1] < mPin_prev[i*2+1]) mIncr[i]--;
            }
            if (mPin[i*2] == 1)
            {
                if (mPin[i*2+1] > mPin_prev[i*2+1]) mIncr[i]--;
                if (mPin[i*2+1] < mPin_prev[i*2+1]) mIncr[i]++;
            }
        }
    }
}

float Encoders::getIncr(int index)
{
    mIncr_prev[index] = mIncr[index];
    mIncr[index] = 0;
    return mIncr_prev[index];
}
