/*
Code by Harry Adkins
Assignment 19
*/
//Question 1
/*
The program will have to loop through the pages multiple times in order to purposefully
increase the time it takes so that a timer can be more accurate, or so it can at least provide distinguishable results.
*/
//Question 2
/*

*/

int main(){
    int jump = PAGESIZE / sizeof(int);
    for(i = 0; i < NUMPAGES * jump; i += jump){
        a[i] += 1;
    }
}