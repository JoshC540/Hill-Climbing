//Joshua Cronin R00200811

#include "gradient.h"

float view[VIEW_SIZE][VIEW_SIZE];
int peakNotFound = 1;
int startingX = 65;
int startingY = 65;
float largestValue, largestOuterValue, largestInnerValue;
float previouslargestValue = 0.00;
int changeInX, changeInY;
int  isPlateu;
int largestValueX, largestValueY, largestInnerValueY, largestInnerValueX, largestOuterValueY, largestOuterValueX;
int viewX, viewY;
int i, j;
path_point path;
int attempts = 0;



int checkForCompletePlateau(){
    int countOfSingleValue = 0;
    for (i=0;i<VIEW_SIZE;i++){
        for (j=0;j<VIEW_SIZE;j++){
            if(view[i][j] == previouslargestValue){
                countOfSingleValue++;
            }
        }
    }
    if(countOfSingleValue == 11 * 11){
        return 1;
    }
    return 0;
}

void findLargestOuterValue(){
    largestOuterValue = 0.00;
    for (i=0;i<VIEW_SIZE;i++){
        if(view[i][0] > largestOuterValue){
            largestOuterValue = view[i][0];
            largestOuterValueY = i;
            largestOuterValueX = 0;
        }
        if(view[0][i] > largestOuterValue){
            largestOuterValue = view[0][i];
            largestOuterValueY = 0;
            largestOuterValueX = i;
        }
        if(view[i][10] > largestOuterValue){
            largestOuterValue = view[i][10];
            largestOuterValueY = i;
            largestOuterValueX = 10;
        }
        if(view[10][i] > largestOuterValue){
            largestOuterValue = view[10][i];
            largestOuterValueY = 10;
            largestOuterValueX = i;
        }
    }
}

void findLargestInnerValue(){
    largestInnerValue = 0.00;
    for (i=1;i<VIEW_SIZE -1;i++){
        for (j=1;j<VIEW_SIZE -1;j++){
            if(view[i][j] > largestInnerValue){
                largestInnerValue = view[i][j];
                largestInnerValueY = i;
                largestInnerValueX = j;
            }
        }
    }
}

void findLargestValue(){
    findLargestOuterValue();
    findLargestInnerValue();
    if(largestInnerValue > largestOuterValue){
        largestValue = largestInnerValue;
        largestValueX = largestInnerValueX;
        largestValueY = largestInnerValueY;
    }else{
        largestValue = largestOuterValue;
        largestValueX = largestOuterValueX;
        largestValueY = largestOuterValueY;
    }
}

void getDistance(){
    changeInX = largestValueX - 5;
    changeInY = largestValueY - 5;
   //printf("X: %d, Y: %d\n", viewX, viewY);
    //printf("Change X: %d, change Y: %d\n", changeInX, changeInY);
}

void assignNewCenter(){
    viewX = viewX + (changeInX);
    viewY = viewY + (changeInY);
}

void print_viewmatrix(){
    for (i=0;i<VIEW_SIZE;i++){
        for (j=0;j<VIEW_SIZE;j++){
            printf("%0.2f ", view[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int getCountOfLargestNumber(){
    int largeNumberCount = 0;
    for (i=0;i<VIEW_SIZE;i++){
        for (j=0;j<VIEW_SIZE;j++){
             if(view[i][j] == largestValue){
                 largeNumberCount++;
                 largestValueY = i;
                 largestValueX = j;
                }
            }
        }
        if(largeNumberCount > 1){
            viewX = viewX + (changeInX * 2);
            viewY = viewY + (changeInY * 2);
        }
        
    return largeNumberCount;
}

int checkIfAtPeak(){
    if(previouslargestValue == largestValue){
        int check = 0;
        check = declare_peak(viewX, viewY);
        if(check == 1){
            path.x = viewX;
            path.y = viewY;
            peakNotFound = 0;
            return 1;
        }
        viewX = ( rand() % 100 );
        viewY = ( rand() % 100 );
        return 0;
    }
    else{
        previouslargestValue = largestValue;
        peakNotFound = 1;
    }
}

path_point find_highest_point(){
    int attempts = 0;
    peakNotFound = 1;
    attempts = 0;
    generate_view(view, startingY, startingX);
    viewX = startingX;
    viewY = startingY;
    while(peakNotFound){
        //print_viewmatrix();
        attempts++;
        //ends if stuck in a loop
        if (attempts >= 500){
            path.x = viewX;
            path.y = viewY;
            return path;
        }
        isPlateu = checkForCompletePlateau();
        if(isPlateu == 1){
            assignNewCenter();
            generate_view(view, viewY, viewX);
        }
        else{
            findLargestValue();
            int countOfLargestNumber = getCountOfLargestNumber();
            getDistance();
            if(countOfLargestNumber == 1){
                int checkForPeak = checkIfAtPeak();
                if(checkForPeak == 1){
                    return path;
                }
                assignNewCenter();
                generate_view(view, viewY, viewX);
            } else{
                assignNewCenter();
                generate_view(view, viewY, viewX);
            }
        }
    }
    printf("Error\n");
}

