#include <stdio.h>


//move zero to end
//  int array[]={2,1,2,0,1,2,0};
void move_zero_to_end(int *array, int n)
{
    int left=0;
    int right=0;
    int tmp;

    while(right < n)
    {
        if(array[right] !=0 )
        {

            tmp= array[right] ;
            array[right] = array[left] ;
            array[left] =tmp;
            left++;

        }
        right++;

    }


}
int main()
{

    int array[]={2,1,2,0,1,2,0};
    int n= sizeof(array)/sizeof(array[0]);
    void (*fnptr)(int *, int);
    fnptr = move_zero_to_end;
    (*fnptr)++;
    for( int i=0 ; i< n ;i++)
    {
        printf("%d",array[i]);
    }


    return 0;

}