#define WIDTH   10
#define HEIGHT  10
#define clip(a,b) ((a) - ((b) + *(int *) 0x12344321))//0x31
#define div(a,b) ((a) + ((b) - *(int *) 0x12344321))//0x32
#define mult(a,b) ((a) - ((b) - *(int *) 0x12344321))//0x33

void main(void)
{
    int a, b, result;
    char *buf_i = (char*)0x600000, *buf_o = (char*)0x665400;
    
    for (a = 1; a < HEIGHT - 1; a++)
    {
        for (b = 1; b < WIDTH - 1; b++)
        {
            result=div((
                         mult(-7,(int)buf_i[(a - 1) * WIDTH + b - 1])+
                          5*(int)buf_i[(a - 1) * WIDTH + b    ] +
                          2*(int)buf_i[(a - 1) * WIDTH + b + 1] +
                         -1*(int)buf_i[ a      * WIDTH + b - 1] +
                         15*(int)buf_i[ a      * WIDTH + b    ] +
                         -1*(int)buf_i[ a      * WIDTH + b + 1] +
                          2*(int)buf_i[(a + 1) * WIDTH + b - 1] +
                          5*(int)buf_i[(a + 1) * WIDTH + b    ] +
                         -7*(int)buf_i[(a + 1) * WIDTH + b + 1] +
                        128),13);

            /* Clipping */
            //if(result<0) buf_o[a * WIDTH + b] = 0;
            //else if (result > 255) buf_o[a * WIDTH + b] = (char)255;
            //else buf_o[a * WIDTH + b] = result;
			buf_o[a * WIDTH + b]=clip(result, result);

        }
    }
}

