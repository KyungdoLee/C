#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

static f32 cost_minimize(f32 w, f32 x, f32 y, f32 alpha)
{
    f32 c;
    const f32 target = 0.00001;

    while((c=cost(w,x,y)) > target){
        w=w-alpha*c;
        if (w<0.0){
            w=0.0;
            break;
        }
        ///print("cost=%f\n",c);
    }
    return w;
}

f32 liner_learning(f32 *xd, f32 *yd, f32 w, f32 alpha, u32 cnt, u32 m)
{
    f32 x, y, c, d;
    u32 i, j;

    printf("\n---------------------------\n");
    printf("Learning...\n");
    for (i=0; i < cnt ; i++)
    {
        d=0.0;
        c=0.0;
        for (j=0; j<m; j++){
            x = *(xd + j);
            y = *(yd +j);
            c += cost(w,x,y);
            d += cost_minimize(w,x,y,alpha);
        }
        c = c/m;
        w = w - alpha*(d/m);
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
    cnt = 60;

    w=linear_test(w,alpha, cnt);
    linear_answer(w,x);

    return 0;
}
