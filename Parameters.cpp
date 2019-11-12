#include "Parameters.h"
#include "math.h"

void Parameters::setup(float min_in, float max_in, float min_out, float max_out,
                       bool scale, float InitialVal)
{
    mMinIn = min_in;
    mMaxIn = max_in;
    mMinOut = min_out;
    mMaxOut = max_out;
    mScale = scale;
    
    mEncVal = InitialVal;
    
    if (mScale == 0)
    {
        mParamVal = ( (mEncVal - mMinIn) / (mMaxIn - mMinIn) ) * (mMaxOut - mMinOut) + mMinOut;
    }
    else
    {
        a = mMinOut / (pow(10,mMinIn));
        b = log10f(mMaxOut / mMinOut) / (mMaxIn - mMinIn);
        mParamVal = a * pow(10,b*mEncVal);
    }
}

void Parameters::update(float Increment)
{
    if (mEncVal + Increment > mMaxIn)
    {
        mEncVal = mMaxIn;
    }
    else if (mEncVal + Increment < mMinIn)
    {
        mEncVal = mMinIn;
    }
    else mEncVal += Increment;
    
    
    if (mScale == 0)
    {
        mParamVal = ( (mEncVal - mMinIn) / (mMaxIn - mMinIn) ) * (mMaxOut - mMinOut) + mMinOut;
    }
    else
    {
        mParamVal = a * pow(10,b*mEncVal);
    }
}

float Parameters::getParam()
{
    return mParamVal;
}
