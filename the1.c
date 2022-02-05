#include <stdio.h>
#define SIZE 25
#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)

int i, j, cur_color, paint;
int img[SIZE][SIZE];
int vis[SIZE][SIZE]; /* visited for recursion */
void fill(int row, int col, int paint, int cur_color);
void print_img();
int copy_paste(int diff_r, int diff_c, int copy_r, int copy_c, int paste_r, int paste_c);
int main()
{

    int color_row, color_col, px_r, px_c;
    char opr;
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            scanf("%d ", &img[i][j]);
        }
    }
    scanf("\n%c\n", &opr); /* operation code */
    if (opr == 'F')
    {
        scanf("%d %d", &color_row, &color_col); /* choosing color */
        scanf("%d %d", &px_r, &px_c);           /* choosing px to paint */
        cur_color = img[px_r][px_c];
        if (color_row < SIZE && color_row >= 0 && color_col < SIZE && color_col >= 0) /* Finding color If the coordinates are in image */
        {
            paint = img[color_row][color_col];
        }
        else /* Finding color If the coordinates are not in image */
        {
            if (color_col >= SIZE && color_row < 0)
            {
                paint = 2;
            }
            else if (color_col >= SIZE && color_row >= SIZE)
            {
                paint = 4;
            }
            else if (color_col >= SIZE)
            {
                paint = 3;
            }
            else if (color_col < 0 && color_row < 0)
            {
                paint = 0;
            }
            else if (color_col < 0 && color_row >= SIZE)
            {
                paint = 6;
            }
            else if (color_col < 0)
            {
                paint = 7;
            }
            else if (color_row < 0)
            {
                paint = 1;
            }
            else if (color_row >= SIZE)
            {
                paint = 5;
            }
        }
        fill(px_r, px_c, paint, cur_color); /* Filling with recursion */
        print_img();
    }
    else if (opr == 'P')
    {
        int mx, mn, diff_r, diff_c, cnt;
        int copy_r[2], copy_c[2];
        int paste_r[2], paste_c[2];
        scanf("%d %d %d %d", &copy_r[0], &copy_c[0], &copy_r[1], &copy_c[1]);
        scanf("%d %d %d %d", &paste_r[0], &paste_c[0], &paste_r[1], &paste_c[1]);
        /* Finding min points of rows and columns */
        mx = max(copy_c[0], copy_c[1]);
        mn = min(copy_c[0], copy_c[1]);
        diff_c = mx - mn;
        copy_c[0] = mn;
        mx = max(copy_r[0], copy_r[1]);
        mn = min(copy_r[0], copy_r[1]);
        diff_r = mx - mn;
        copy_r[0] = mn;

        mn = min(paste_c[0], paste_c[1]);
        paste_c[0] = mn;
        mn = min(paste_r[0], paste_r[1]);
        paste_r[0] = mn;
        cnt = copy_paste(diff_r, diff_c, copy_r[0], copy_c[0], paste_r[0], paste_c[0]);
        print_img();
        printf("%d\n", cnt);
    }
    else if (opr == 'R')
    {
        char dir;
        int deg, diff_r, diff_c, dec, cnt;
        int copy_r[2], copy_c[2];
        int paste_r[2], paste_c[2];
        dec = 0, cnt = 0;

        scanf("%c %d", &dir, &deg);
        if (dir == 'L') /* If L, changes the degree to as it is R */
        {
            deg = (360 - deg) % 360;
        }
        scanf("%d %d %d %d", &copy_r[0], &copy_c[0], &copy_r[1], &copy_c[1]);
        scanf("%d %d %d %d", &paste_r[0], &paste_c[0], &paste_r[1], &paste_c[1]);
        diff_r = copy_r[1] - copy_r[0];
        diff_c = copy_c[1] - copy_c[0];
        if (deg == 90 || deg == 270)
        {
            if (deg == 90)
                dec = 1;
            for (i = 0; i < diff_c + 1; i++)
            {
                for (j = 0; j < diff_r + 1; j++)
                {
                    if (img[copy_r[0] + dec * (diff_r - j) + (dec - 1) * (-j)][copy_c[0] + dec * (i) + (dec - 1) * (-diff_c + i)] != img[paste_r[0] + i][paste_c[0] + j])
                    {
                        img[paste_r[0] + i][paste_c[0] + j] = img[copy_r[0] + dec * (diff_r - j) + (dec - 1) * (-j)][copy_c[0] + dec * (i) + (dec - 1) * (-diff_c + i)];
                        cnt++;
                    }
                }
            }
        }
        else if (deg == 0 || deg == 180)
        {
            if (deg == 0)
            {
                cnt = copy_paste(diff_r, diff_c, copy_r[0], copy_c[0], paste_r[0], paste_c[0]);
            }
            else
            {
                for (i = 0; i < diff_c + 1; i++)
                {
                    for (j = 0; j < diff_r + 1; j++)
                    {
                        if (img[copy_r[0] + diff_r - i][copy_c[0] + diff_c - j] != img[paste_r[0] + i][paste_c[0] + j])
                        {
                            cnt++;
                            img[paste_r[0] + i][paste_c[0] + j] = img[copy_r[0] + diff_r - i][copy_c[0] + diff_c - j];
                        }
                    }
                }
            }
        }
        print_img();
        printf("%d\n", cnt);
    }

    return 0;
}

void fill(int row, int col, int paint, int cur_color)
{
    if (col < 0 || col >= SIZE || row < 0 || row >= SIZE) /* if it is out of the ranges, return*/
    {
        return;
    }
    if (vis[row][col] == 1 || img[row][col] != cur_color) /* If already visited or it is color is different */
    {
        vis[row][col] = 1;
        return;
    }
    vis[row][col] = 1;
    img[row][col] = paint;
    fill(row - 1, col - 1, paint, cur_color);
    fill(row - 1, col, paint, cur_color);
    fill(row - 1, col + 1, paint, cur_color);
    fill(row, col + 1, paint, cur_color);
    fill(row + 1, col + 1, paint, cur_color);
    fill(row + 1, col, paint, cur_color);
    fill(row + 1, col - 1, paint, cur_color);
    fill(row, col - 1, paint, cur_color);
    return;
}
int copy_paste(int diff_r, int diff_c, int copy_r, int copy_c, int paste_r, int paste_c)
{
    int cnt;
    cnt = 0;
    for (i = 0; i < diff_r + 1; i++)
    {
        for (j = 0; j < diff_c + 1; j++)
        {
            if (img[paste_r + i][paste_c + j] != img[copy_r + i][copy_c + j])
            {
                cnt++;
                img[paste_r + i][paste_c + j] = img[copy_r + i][copy_c + j];
            }
        }
    }
    return cnt;
}
void print_img()
{
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            printf("%d ", img[i][j]);
        }
        printf("\n");
    }
}