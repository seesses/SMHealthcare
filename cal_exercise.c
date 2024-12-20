//
//  cal_exercise.c
//  Excercise for Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define MAX_EXERCISES 100  			// Maximum number of exercises
#define MAX_EXERCISE_NAME_LEN 50	// Maximum length of the name of exercise


// To declare the structure of the exercises
static Exercise exercise_list[MAX_EXERCISES];
int exercise_list_size = 0; // Tracks the current number of exercises loaded


/*
    description : read the information in "excercises.txt"
*/

void loadExercises(const char* EXERCISEFILEPATH) {
    FILE *file = fopen(EXERCISEFILEPATH, "r");
    if (file == NULL) {
        printf("There is no file for exercises! \n");
        return;
    }

    // ToCode: to read a list of the exercises from the given file
    while (fscanf(file, "%s %d", exercise_list[exercise_list_size].exercise_name, &exercise_list[exercise_list_size].calories_burned_per_minute)==2) { //if it returns 2, it means both the exercise name and calories_burned were read correctly
    	exercise_list_size++; //increase the count of exercise lodded
        if (exercise_list_size >= MAX_EXERCISES){
        	break;
		}
    }

    fclose(file); // Close the file
}


/*
    description : to enter the selected exercise and the total calories burned in the health data
    input parameters : health_data - data object to which the selected exercise and its calories are added 
    return value : No
    
    operation : 1. provide the options for the exercises to be selected
    			2. enter the duration of the exercise
    			3. enter the selected exercise and the total calories burned in the health data
*/

void inputExercise(HealthData* health_data) {
    int choice, duration, i;
    
    if (exercise_list_size == 0) { //for debugging: check if the exercise list is empty  
        printf("No exercises loaded. Please check the exercises.txt file.\n");
        return;
    }
    
    
    do{
    	
    	// ToCode: to provide the options for the exercises to be selected
    	printf("The list of exercises: \n");
		for(i=0;i<exercise_list_size;i++){
			printf("%d. %s - %d kcal\n", i+1, exercise_list[i].exercise_name, exercise_list[i].calories_burned_per_minute);	
		}printf("7. Exit\n");
	
		// ToCode: to enter the exercise to be chosen with exit option
		printf("Select exercise: ");
		scanf("%d", &choice);
 
 
		// ToCode: to enter the selected exercise and total calcories burned in the health data
	
		if(choice==7){
			printf("OKAY. EXIT.\n");
			break;
		}
		else if(choice<1||choice>7){
			printf("Please select betwwen 1 and 7 numbers.\n \n");
			continue;
		}
					
		// To enter the duration of the exercise
    	printf("Enter the duration of the exercise (in min.): ");
    	scanf("%d", &duration);
    
    	if (duration <= 0) {
    		printf("[Error] Duration must be a positive number.\n \n");
    		continue;
		}
	
		
    	// Add the selected exercise to health_data 
		health_data->exercises[health_data->exercise_count] = exercise_list[choice - 1];
        health_data->exercise_durations[health_data->exercise_count] = duration;
    	
    	//Update total calories burned in health_data
    	
        int calories_burned = exercise_list[choice - 1].calories_burned_per_minute * duration;  // calculate the calories burned for the selected exercise
        health_data->total_calories_burned += calories_burned; // increase the cumulative total calories burned stored in 'health_data' by the calculated 'calories_burned'

        health_data->exercise_count++;
        printf("Total calories burned: %d kcal\n \n", calories_burned);
    	
	}while(1); //loop until the user selects 7		
		
}
    
