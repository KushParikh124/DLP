#include<stdio.h>
#include <stdbool.h>
#include<stdlib.h>

bool is_valid(char *p)
{
    int i = 0;
    if(p[i] == '\0'){
        return false;
    }
    while (p[i] != '\0'){
        i++;
    }
    if((p[i-1] != 'b') || (p[i-2] != 'b')){
        return false;   
    }
    for(int j = i - 3; j >= 0 ; j--){
        if(p[j] != 'a'){
            return false;
        }
    }
    return true;
}

int main(){
    char *p = (char *)malloc(7 * sizeof(char));
    printf("Enter a String : ");
    scanf("%s", p);
    printf("You Entered : %s\n", p);
    bool valid = is_valid(p);
    printf("This String is %s\n" , valid ? "Valid" : "Not Valid");
    return 0;
}
