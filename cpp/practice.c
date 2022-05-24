#include<stdio.h>

int main(){
    //input
    char str[101];
    int n;
    scanf("%d %s", &n, &str);
    
    //processing
    for(int i = 1; i <= n; i++){
        int flag = 0; // 0 mane repeat kore

        //repeat 
        if(n % i != 0) continue;
        for(int j = i; j < n; j+=i){
            for(int k = 0; k  < i; k++){
                if(str[j+k] != str[k])
                    flag = 1;
            }
        }

        if(flag == 0){
            //print kore dibo
            
            for(int j = 0; j < i; j++){
                printf("%c", str[j]);
            }
            break;
        }
            
    }
}