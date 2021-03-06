#include <stdio.h>
#include <stdlib.h>

typedef unsigned int u32;
typedef int i32;
typedef unsigned long ul32;
typedef float f32;
typedef double d4;

#define ARRAY_CNT(a) sizeof(a)/sizeof(a[0])

#define H(w,x) w*x

//average cost
static inline f32 cost(f32 w, f32 x, f32 y)
{
    return (H(w,x)-y)*(H(w,x)-y);
}


f32 liner_learning(f32 *xd, f32 *yd, f32 w, f32 alpha, u32 cnt, u32 m)
{
    f32 x, y;
    f32 c, descent;
    u32 i, j;

    printf("\n---------------------------\n");
    printf("Learning...\n");
    for (i=0; i < cnt ; i++)
    {
        descent = 0.0;
        c = 0.0;
        for (j=0; j<m; j++){
            x = *(xd + j);
            y = *(yd +j);
            c += cost(w,x,y);
            descent += ((H(w,x) - y) *x);
        }
        c = c/m;
        w = w - alpha*(descent/m);
        printf("%4d: cost=%f, w=%f\n",i,c,w);
    }
    return w;
}

f32 linear_test(f32 w, f32 alpha, u32 cnt)
{
    f32 x_data[] = {1,2,3,4};
    f32 y_data[] = {2,4,6,8};
    u32 m;

    m = ARRAY_CNT(y_data);
    w = liner_learning(x_data, y_data, w, alpha, cnt, m);
    return w;
}

void linear_answer(f32 w, f32 x)
{
    f32 y;
    y = H(w,x);

    printf("-------------------\n");
    printf("Answer for %f:%f\n", x, y);
}

int main(void)
{
    f32 w, x, alpha;
    u32 cnt;
    w = 5.0;
    x = 8.0;
    alpha = 0.1;
    cnt = 30;

    w=linear_test(w,alpha, cnt);
    linear_answer(w,x);

    return 0;
}
