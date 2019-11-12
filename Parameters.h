#include "global.h"

class Parameters
{
    
private:
    float mMinIn , mMaxIn; // 0 - 96 for one encoder cycle
    float mMinOut , mMaxOut; // In will be scaled to these boundaries (real parameter values)
    bool mScale; // 0 for linear, 1 for logarithmic
    float mEncVal; // encoder value to be bounded by MinIn and MaxIn
    float mParamVal; // real parameter value to be bounded by MinOut and MaxOut
    
    float a,b; // needed to calculate the logarithmic change
    
public:
    
    // Instead of a constructor, so I can create the instances in the form of array and initialize them afterwards
    void setup(float min_in, float max_in, float min_out, float max_out, bool scale, float InitialVal);

    // update method takes the increment of the corresponding encoder, refreshed mEncVal (within its boundaries)
    // and scales it linearly or logarithmicaly (depending on mScale) to the real parameter value. 
    void update(float Increment);

    // returns value of parameter
    float getParam();
    
};
