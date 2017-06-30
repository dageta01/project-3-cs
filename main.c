#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "projectthreeheader.h"

/*
Name:       Tim Dager
Project:    Project 3
Course:     CS 229
Instructor: Parker
*/

/*
A program to simulate weather information from multiple sites.
*/

int main()
{
    int idArray[3] = {SITE_ID1,SITE_ID2,SITE_ID3};
    int dataGenerated = 0;
    int doExit = 0;
    float maxMinTolerance[6][3];
    struct SiteInfo data[SITE_ARRAY_SIZE];

    do{
        switch(get_choice()){
        case SIMULATE: //create the settings and create site information
            printf("\nSimulation Settings: \n");
            for(int i = 0; i < 3; i++){
                set_site_information(&maxMinTolerance[WINDTOLERANCE][i],LO_TOLERANCE_WIND,HI_TOLERANCE_WIND);
                set_site_information(&maxMinTolerance[TEMPTOLERANCE][i],LO_TOLERANCE_TEMP,HI_TOLERANCE_TEMP);
                set_site_information(&maxMinTolerance[MINWIND][i],LO_MIN_WIND,HI_MIN_WIND);
                set_site_information(&maxMinTolerance[MAXWIND][i],LO_MAX_WIND,HI_MAX_WIND);
                set_site_information(&maxMinTolerance[MINTEMP][i],LO_MIN_TEMP,HI_MIN_TEMP);
                set_site_information(&maxMinTolerance[MAXTEMP][i],LO_MAX_TEMP,HI_MAX_TEMP);

                printf("Site %d \n",i+1);
                printf("******* \n");
                printf("    -Wind Tolerance: %5.2f\n",maxMinTolerance[WINDTOLERANCE][i]);
                printf("    -Temperature Tolerance: %5.2f\n",maxMinTolerance[TEMPTOLERANCE][i]);
                printf("    -Minimum Wind: %5.2f\n",maxMinTolerance[MINWIND][i]);
                printf("    -Maximum Wind: %5.2f\n",maxMinTolerance[MAXWIND][i]);
                printf("    -Minimum Temperature: %5.2f\n",maxMinTolerance[MINTEMP][i]);
                printf("    -Maximum Temperature: %5.2f\n\n",maxMinTolerance[MAXTEMP][i]);
            }//for
            generate_random_data(data,SITE_ARRAY_SIZE,maxMinTolerance);
            dataGenerated = 1;
        break;

        case ANALYZE: // analyze the data created in SIMULATE case
            if(dataGenerated == 0)
            {
                printf("\nERROR: No data to analyze.\n\n");
            }//if(dataGenerated == 0)
            else
            {
                int maxWindDay, maxWindId, maxTempDay, maxTempId;
                float overAllMaxWind, overAllMaxTemp;
                printf("\nAnalysis Results: \n");
                for(int i = 0; i < 3; i++)
                {
                    printf("Site: %d ID: %d \n",i+1,idArray[i]);
                    printf("*************** \n");
                    printf("    -Maximum Wind: %5.2f \n",get_site_maximum_wind(data,SITE_ARRAY_SIZE,idArray[i]));
                    printf("    -Average Wind: %5.2f \n",get_site_average_wind(data,SITE_ARRAY_SIZE,idArray[i]));
                    printf("    -Maximum Temperature: %5.2f \n",get_site_maximum_temp(data,SITE_ARRAY_SIZE,idArray[i]));
                    printf("    -Average Temperature: %5.2f \n\n",get_site_average_temp(data,SITE_ARRAY_SIZE,idArray[i]));
                }//for

                overAllMaxTemp = get_overall_maximum_temp(data,SITE_ARRAY_SIZE,&maxTempId,&maxTempDay);
                overAllMaxWind = get_overall_maximum_wind(data,SITE_ARRAY_SIZE,&maxWindId,&maxWindDay);

                printf("Overall Analysis:\n");
                printf("*****************\n");
                printf("    -Max Wind of %5.2f occurs at Site %d on Day %d\n",overAllMaxWind,maxWindId,maxWindDay);
                printf("    -Max Temp of %5.2f occurs at Site %d on Day %d\n\n",overAllMaxTemp,maxTempId,maxTempDay);
            }//else
            break;
        case NATURALEXIT:
            doExit = 1;
            break;
        }//switch(getchoice())
    }while(doExit != 1);

    return 0;
}//main



