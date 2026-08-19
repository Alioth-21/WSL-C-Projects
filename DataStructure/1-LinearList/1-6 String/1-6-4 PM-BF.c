// 1-6-4 PM-BF.c
// Phis is the BF pattern matching algorithm

#include <stdio.h>
#include <string.h>

int BF(const char* S, const char* P){
    // find the first occurrence of P in S, return the position
    // Not found return -1
    int slen = strlen(S);
    int plen = strlen(P);
    if(slen == 0 || plen == 0) return -1;

    int i=0, j=0;
    while(i<slen && j<plen){
        if(S[i] == P[j]){
            i++;
            j++;
        }
        else{
            i = i-j+1;
            j = 0;
        }
    }
    return (j == plen) ? (i - j) : -1;
}

int main(){
    char S[] = "ababcabcacbab";
    char P[] = "abcac";

    int pos = BF(S, P);
    if(pos != -1) printf("Pattern at pos: %d\n", pos);
    else printf("Pattern not found\n");

    return 0;
}