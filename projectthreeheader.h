#ifndef PROJECTTHREEHEADER_H_INCLUDED
#define PROJECTTHREEHEADER_H_INCLUDED

#define LO_MIN_WIND 2
#define HI_MIN_WIND 5
#define LO_MAX_WIND 12
#define HI_MAX_WIND 18
#define LO_MIN_TEMP 15
#define HI_MIN_TEMP 19
#define LO_MAX_TEMP 23
#define HI_MAX_TEMP 29
#define LO_TOLERANCE_WIND 0.85
#define HI_TOLERANCE_WIND 0.95
#define LO_TOLERANCE_TEMP 0.92
#define HI_TOLERANCE_TEMP 0.98
#define SITE_ID1 1234
#define SITE_ID2 1111
#define SITE_ID3 9876
#define SITE_ARRAY_SIZE 93
#define GENERATESITE i % 3

//for use with maxMinTolerance array
#define WINDTOLERANCE 0
#define TEMPTOLERANCE 1
#define MINWIND 2
#define MAXWIND 3
#define MINTEMP 4
#define MAXTEMP 5

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <limits.h>


struct SiteInfo{
    int siteId;
    int day;
    float windSpeed;
    float temperature;

};


typedef enum {SIMULATE=1, ANALYZE, NATURALEXIT } choice;


choice get_choice(void);
float get_random_float(double minRand, double maxRand);
void set_site_information(float *siteParamater,float lowValue, float HighValue);
void generate_random_data(struct SiteInfo *siteData, int arraySize, float tolerances[6][3]);

float get_site_maximum_wind(struct SiteInfo *siteData, int arraySize, int siteId);
float get_site_average_wind(struct SiteInfo *siteData, int arraySize, int siteId);
float get_site_maximum_temp(struct SiteInfo *siteData, int arraySize, int siteId);
float get_site_average_temp(struct SiteInfo *siteData, int arraySize, int siteId);
float get_overall_maximum_wind(struct SiteInfo *siteData, int arraySize, int *siteId, int *day);

/***********************************************************************************************/

float get_random_float(double minRand, double maxRand){
    //returns a float between the numbers given
    //srand(time(NULL)); <- for some reason this ruins everything.    
    float range = maxRand - minRand;
    float random = ((float) rand()) / (float) RAND_MAX;
    float r = random * range;
    return minRand + r;
}//get_random_float

/***********************************************************************************************/

void set_site_information(float *siteParamater,float lowValue, float HighValue){
    //takes in a weather site parameter float and assigns it a random value between the limites
    *siteParamater = get_random_float(lowValue,HighValue);
    return;
}//set_site?information

/***********************************************************************************************/

choice get_choice(void){
    //simply returns a choice
    int numericalChoice;
    do{
        printf("Select a choice \n");
        printf("--------------- \n");
        printf("1. Simulate Data \n"
            "2. Analyze Data \n"
            "3. Exit\n");

        scanf("%d",&numericalChoice);
        if(numericalChoice < 1 || numericalChoice > 3)
        {
            printf("\n%d is not a valid entry.\n",numericalChoice);
        }

        return numericalChoice;

    }while(numericalChoice < 1 || numericalChoice > 3);

}//get_choice

/***********************************************************************************************/

void generate_random_data(struct SiteInfo *siteData, int arraySize, float tolerances[6][3]){
    
    float randNum;
    int siteIds[3] = {SITE_ID1, SITE_ID2, SITE_ID3};
    for(int i = 0; i < arraySize; i++)
        {

                // i % 3 is used to generate the numbers between 0 and 2.
                //GENERATESITE is defined as i % 3
                
                siteData->siteId = siteIds[GENERATESITE];
                
                //set wind speed
                randNum = get_random_float(0,1);
                if((randNum <= tolerances[WINDTOLERANCE][GENERATESITE]))
                {
                    siteData->windSpeed = get_random_float(tolerances[MINWIND][GENERATESITE],tolerances[MAXWIND][GENERATESITE]);
                }
                else if(randNum > 1.0 - tolerances[WINDTOLERANCE][GENERATESITE] && randNum < 1.0-tolerances[WINDTOLERANCE][GENERATESITE]/2)
                {
                    siteData->windSpeed = get_random_float(0,1) * tolerances[MINWIND][GENERATESITE];
                }
                else
                {
                    siteData->windSpeed = get_random_float(1,1.25) * tolerances[MAXWIND][GENERATESITE];
                }

                //set temperature;
                randNum = get_random_float(0,1);
                if(randNum <= tolerances[TEMPTOLERANCE][GENERATESITE])
                {
                    siteData->temperature = get_random_float(tolerances[MINTEMP][GENERATESITE],tolerances[MAXTEMP][GENERATESITE]);
                }
                else if(randNum > 1.0 - tolerances[TEMPTOLERANCE][GENERATESITE] && randNum < 1.0-tolerances[TEMPTOLERANCE][GENERATESITE]/2)
                {
                        siteData->temperature = get_random_float(0,1) * tolerances[MINTEMP][GENERATESITE];
                }
                else
                {
                        siteData->temperature = get_random_float(1,1.25) * tolerances[MAXTEMP][GENERATESITE];
                }
                siteData->day = i/3 + 1; //generates days between 1 and 31

                //printf("\nSite: %d Day: %d Wind Speed: %f Temp: %f\n", siteData->siteId, siteData->day, siteData->windSpeed, siteData->temperature);
        siteData++;
        }

    return;
}//generate_random_data

/***********************************************************************************************/

float get_site_maximum_wind(struct SiteInfo *siteData, int arraySize, int siteId){
    float maximumWind = -1000;
    for(int i = 0; i < arraySize; i++)
    {
        if(siteData->siteId == siteId && siteData->windSpeed >= maximumWind)
        {
            maximumWind = siteData->windSpeed;
        }

        siteData++;
    }
    return maximumWind;
}//get_site_maximum_wind

float get_site_average_wind(struct SiteInfo *siteData, int arraySize, int siteId){
    float rollingSum = 0;
    for(int i = 0; i < arraySize; i++)
    {
        if(siteData->siteId == siteId)
        {
            rollingSum += siteData->windSpeed;
        }
        siteData++;
    }
    return rollingSum / (float) (arraySize/3);

}//get_site_average_wind

/***********************************************************************************************/

float get_site_maximum_temp(struct SiteInfo *siteData, int arraySize, int siteId){

    float maximumTemp = -1000;
    for(int i = 0; i < arraySize; i++)
    {
        if(siteData->siteId == siteId && siteData->temperature >= maximumTemp)
        {
            maximumTemp = siteData->temperature;
        }

        siteData++;
    }
    return maximumTemp;
}//get_site_maximum_temp

/***********************************************************************************************/

float get_site_average_temp(struct SiteInfo *siteData, int arraySize, int siteId){
    float rollingSum = 0;
    for(int i = 0; i < arraySize; i++)
    {
        if(siteData->siteId == siteId)
        {
            rollingSum += siteData->temperature;
        }
        siteData++;
    }
    return rollingSum / (float) (arraySize/3);
}//get_site_average_temp

/***********************************************************************************************/

float get_overall_maximum_wind(struct SiteInfo *siteData, int arraySize, int *siteId, int *day){
    float maximumWind  = -1000;
    for(int i = 0; i < arraySize; i++)
    {
        if(siteData->windSpeed >= maximumWind)
        {
            maximumWind = siteData->windSpeed;
            *day = siteData->day;
            *siteId = siteData->siteId;
        }
        siteData++;
    }
    return maximumWind;
}//get_overall_maximum_wind

/***********************************************************************************************/

float get_overall_maximum_temp(struct SiteInfo *siteData, int arraySize, int *siteId, int *day){
    float maximumTemp  = -1000;
    for(int i = 0; i < arraySize; i++)
    {
        if(siteData->temperature > maximumTemp)
        {
            maximumTemp = siteData->temperature;
            *day = siteData->day;
            *siteId = siteData->siteId;
        }
        siteData++;
    }
    return maximumTemp;
}//get_overall_maximum_temp
#endif // PROJECTTHREEHEADER_H_INCLUDED
/***********************************************************************************************/
