#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROWS 30
#define COLS 60

char canvas[ROWS][COLS];

// Initialize canvas
void initCanvas() {
    for(int i = 0; i < ROWS; i++)
        for(int j = 0; j < COLS; j++)
            canvas[i][j] = '_';
}

// Display canvas
void displayCanvas() {
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++)
            printf("%c", canvas[i][j]);
        printf("\n");
    }
}

// Plot point
void plot(int x, int y) {
    if(x >= 0 && x < ROWS && y >= 0 && y < COLS)
        canvas[x][y] = '*';
}

// Draw line (Bresenham)
void drawLine(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    int err = dx - dy;

    while(1) {
        plot(x1, y1);

        if(x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;

        if(e2 > -dy) {
            err -= dy;
            x1 += sx;
        }

        if(e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

// Draw rectangle
void drawRectangle(int x, int y, int width, int height) {
    drawLine(x, y, x, y + width);
    drawLine(x + height, y, x + height, y + width);
    drawLine(x, y, x + height, y);
    drawLine(x, y + width, x + height, y + width);
}

// Draw circle
void drawCircle(int xc, int yc, int r) {
    for(int angle = 0; angle < 360; angle++) {
        double rad = angle * 3.14159 / 180;
        int x = xc + r * cos(rad);
        int y = yc + r * sin(rad);
        plot(x, y);
    }
}

// Draw triangle
void drawTriangle(int x1, int y1,
                  int x2, int y2,
                  int x3, int y3) {
    drawLine(x1, y1, x2, y2);
    drawLine(x2, y2, x3, y3);
    drawLine(x3, y3, x1, y1);
}

// Delete area
void deleteArea(int x1, int y1, int x2, int y2) {
    for(int i = x1; i <= x2; i++) {
        for(int j = y1; j <= y2; j++) {
            if(i >= 0 && i < ROWS && j >= 0 && j < COLS)
                canvas[i][j] = '_';
        }
    }
}

int main() {
    int choice;

    initCanvas();

    while(1) {
        printf("\n===== 2D GRAPHICS EDITOR =====\n");
        printf("1. Draw Line\n");
        printf("2. Draw Rectangle\n");
        printf("3. Draw Circle\n");
        printf("4. Draw Triangle\n");
        printf("5. Delete Area\n");
        printf("6. Display Canvas\n");
        printf("7. Clear Canvas\n");
        printf("8. Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);

        if(choice == 1) {
            int x1,y1,x2,y2;
            printf("Enter x1 y1 x2 y2: ");
            scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
            drawLine(x1,y1,x2,y2);
        }
        else if(choice == 2) {
            int x,y,w,h;
            printf("Enter x y width height: ");
            scanf("%d%d%d%d",&x,&y,&w,&h);
            drawRectangle(x,y,w,h);
        }
        else if(choice == 3) {
            int x,y,r;
            printf("Enter center_x center_y radius: ");
            scanf("%d%d%d",&x,&y,&r);
            drawCircle(x,y,r);
        }
        else if(choice == 4) {
            int x1,y1,x2,y2,x3,y3;
            printf("Enter x1 y1 x2 y2 x3 y3: ");
            scanf("%d%d%d%d%d%d",
                  &x1,&y1,&x2,&y2,&x3,&y3);
            drawTriangle(x1,y1,x2,y2,x3,y3);
        }
        else if(choice == 5) {
            int x1,y1,x2,y2;
            printf("Enter delete area x1 y1 x2 y2: ");
            scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
            deleteArea(x1,y1,x2,y2);
        }
        else if(choice == 6) {
            displayCanvas();
        }
        else if(choice == 7) {
            initCanvas();
            printf("Canvas Cleared!\n");
        }
        else if(choice == 8) {
            break;
        }
        else {
            printf("Invalid Choice!\n");
        }
    }

    return 0;
}
