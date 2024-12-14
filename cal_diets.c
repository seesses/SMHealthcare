//
//  cal_diets.c
//  Diets for Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define MAX_DIETS 100      			// Maximum number of diets
#define MAX_FOOD_NAME_LEN 50		// Maximum length of the name of food


// list of diets 
static Diet diet_list[MAX_DIETS];
static int diet_list_size = 0;


/*
    description : read the information in "diets.txt"
*/

void loadDiets(const char* DIETFILEPATH) {  //const: 변수값 변경 불가 
    FILE *file = fopen(DIETFILEPATH, "r");
    if (file == NULL) {
        printf("There is no file for diets! \n");
        return;
    }

     // ToCode: to read a list of the diets from the given file
    while (fscanf(file, "%s %d", diet_list[diet_list_size].food_name, &diet_list[diet_list_size].calories_intake)==2) {
    	diet_list_size++;
        if (diet_list_size >= MAX_DIETS){
        	break;
		}
    }
    fclose(file);
}

/*
    description : to enter the selected diet and the total calories intake in the health data
    input parameters : health_data - data object to which the selected diet and its calories are added 
    return value : No
    
    operation : 1. provide the options for the diets to be selected
    			2. enter the selected diet and the total calories intake in the health data
*/

void inputDiet(HealthData* health_data) {
    int choice, i;
    
    do{
    	 // ToCode: to provide the options for the diets to be selected
    	printf("The list of diets:\n");
    	for (i=0; i<diet_list_size; i++) {
        	printf("%d. %s - %d kcal\n", i+1, diet_list[i].food_name, diet_list[i].calories_intake);
   		}
    	printf("7. Exit\n");

		// ToCode: to enter the diet to be chosen with exit option
		printf("Select a diet: ");
		scanf("%d", &choice);
		printf("\n"); //a line change to stand out
	
		if(choice==7){
		break;
		}

    	// ToCode: to enter the selected diet in the health data
    	if(choice<1 || choice>7){
    		printf("Please select between 1 and 7 numbers.\n");
		}
		else{
			Diet selected_diet=diet_list[choice-1]; //'selected_diet' is temporarily save the user's selected diet_list
        	
        	int total_calories_intake;
        	
			health_data->diet[health_data->diet_count]=selected_diet;
        	health_data->diet_count++;
        	// ToCode: to enter the total calories intake in the health data
        	health_data->total_calories_intake+=selected_diet.calories_intake;
        	
        	printf("You selected: %s (%d kcal)\n", selected_diet.food_name, selected_diet.calories_intake);
		}
    	
	}while(1); //loop until the user selects 7
   

}

