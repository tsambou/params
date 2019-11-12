#include <Bela.h>
#include "digital_gpio_mapping.h"
#include "global.h"
#include "Encoders.h"
#include "Parameters.h"
#include <math.h>

// This object holds the value of the Current Encoder Mode
Parameters EncMode;

// Doesn't let me create instances with variable [NofCh] etc, even though they are const (in global.h/cpp)
// Parameters Param[NofCh][NofModes][NofEncoders];
Parameters Param[1][3][3];

// Input / Output pins for Microprocessor in order to read the 4 encoders 
char PL_Pin = {P8_09}; //yellow
char Clock_Pin = {P8_10}; //orange
char Input_Pin = {P8_11};


bool setup(BelaContext *context, void *userData)
{
    pinMode(context,0,PL_Pin,OUTPUT);
    pinMode(context,0,Clock_Pin,OUTPUT);
    pinMode(context,0,Input_Pin,INPUT);
    
    
    //  SETUP Parameters' objects:
    // (float min_in, float max_in, float min_out, float max_out, bool scale, float InitialVal)
    
    EncMode.setup(0,20 , 0,2 , 0 , 0);
    
    for (unsigned int i=0 ; i<NofCh ; i++)
    {
        Param[i][0][0].setup(0,100, 0,2, 0,50); //volume
        Param[i][0][1].setup(0,100, -1,1, 0,50); //panning
        Param[i][0][2].setup(0,100, -100,100, 0,50); //something
        Param[i][1][0].setup(0,100, 20,160, 1,0); //lowshelf freq
        Param[i][1][1].setup(0,100, 0,1, 0,50); //lowshelf gain
        Param[i][1][2].setup(0,100, 1,40, 1,0); //lowshelf Q
        Param[i][2][0].setup(0,100, 1500,12000, 1,0); //highshelf freq
        Param[i][2][1].setup(0,100, 0,1, 0,50); //highshelf gain
        Param[i][2][2].setup(0,100, 1,40, 1,0); //highshelf Q
    }
    
    
    
    return true;
}


//-------------------------------------------------------------------------------


void render(BelaContext *context, void *userData)
{
    static Encoders Enc(context,Input_Pin); //initialize Encoders object to READ the pins
    static int SelectedCh = 0, SelectedEncMode = 0;

    for (unsigned int n = 0 ; n < context->digitalFrames ; n++) 
    {
        if (n % 2 == 0) digitalWriteOnce(context,n,Clock_Pin,GPIO_LOW);
        else digitalWriteOnce(context,n,Clock_Pin,GPIO_HIGH);
    }
    digitalWrite(context,0,PL_Pin,GPIO_HIGH);
    digitalWriteOnce(context,15,PL_Pin,GPIO_LOW);

    Enc.read(); // Reads pins of encoders and determines whether they were turned (Increment)

    if (gCount%200 == 0)
    {
        EncMode.update(Enc.getIncr(0));
        SelectedEncMode = (int)(EncMode.getParam() + 0.5);
        
        // Update parameters for Current/Selected Channel and Current Encoder Mode, for our 3 Encoders
        for (unsigned int i=0 ; i<NofEncoders ; i++)
        {
            Param[SelectedCh][SelectedEncMode][i].update(Enc.getIncr(i+1));
        }     
    }
    
    if (gCount % 2000 == 0)
    {
        rt_printf("Enc Mode ------ Val1   ------  Val2   ------  Val3\n");
        rt_printf("   %d    ----  %f  ---  %f  ---  %f \n",SelectedEncMode,Param[SelectedCh][SelectedEncMode]    [0].getParam(),Param[SelectedCh][SelectedEncMode][1].getParam(),Param[SelectedCh][SelectedEncMode][2].getParam());
    }
    
    gCount++;
}

void cleanup(BelaContext *context, void *userData)
{
    
}
