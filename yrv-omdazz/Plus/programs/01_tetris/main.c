#include "memory_mapped_registers.h"
#include <stdint.h>
#include <coremark.h>
#include "tetris.h"

#define LED_0   0xe
#define LED_1   0xd
#define LED_2   0xb
#define LED_3   0x7

#define HEX_H   0b11001000
#define HEX_E   0b10110000
#define HEX_L   0b11110001
#define HEX_O   0b10000001

/*
0x00010000 port0 = {8'bxxxxxxxx, RDP, RA, RB, RC, RD, RE, RF, RG}
0x00010002 port1 = {4'bxxxx, C46, C45, C43, C42, 4'bxxxx, AN4, AN3, AN2, AN1}
0x00010004 port2 = L[16:1]
0x00010006 port3 = {CLR_EI, 1'bx, INIT, ECALL, NMI, LINT, INT, EXCEPT, L[24:17]}
0x00010008 port4 = DIP[16:1]
0x0001000a port5 = {C9, C8, C6, S5, S4, S3, S2, S1, DIP[24:17]}
0x0001000c port6 = {DIV_RATE, S_RESET, 3'bxxx}
0x0001000e port7 = {4'bxxxx, EMPTY, DONE, FULL, OVR, SER_DATA}
*/




uint32_t clock;

void sleep();

void long_sleep();

void very_long_sleep();

int tetris_hittest(struct tetris *t);
void clean();

void H();

void E();

void L();

void O();

void HELO(int state);

int next(int prev, int step);

void itoa(int, char *);

void beep();
char getchar();

void __attribute__((optimize("O0"))) say_serial_a();

void __attribute__((optimize("O0"))) say_lpt_a();

short time();
void setpos(int x,int y);

extern  void cls();
extern  void putc(int x, int y, char c);
int clofk=0;

struct tetris_level {
    int score;
    int nsec;
};

struct tetris {
    char game [12][15];
    int w;
    int h;
    int level;
    int gameover;
    int score;
    struct tetris_block {
        char data[5][5];
        int w;
        int h;
    } current;
    int x;
    int y;
};

struct tetris_block blocks[] =
{
    {{"##", 
         "##"},
    2, 2
    },
    {{" X ",
         "XXX"},
    3, 2
    },
    {{"OOOO"},
        4, 1},
    {{"OO",
         "O ",
         "O "},
    2, 3},
    {{"OO",
         " O",
         " O"},
    2, 3},
    {{"ZZ ",
         " ZZ"},
    3, 2}
};

struct tetris_level levels[]=
{
    {0,
        1200000},
    {1500,
        900000},
    {8000,
        700000},
    {20000,
        500000},
    {40000,
        400000},
    {75000,
        300000},
    {100000,
        200000}
};

#define TETRIS_PIECES (sizeof(blocks)/sizeof(struct tetris_block))
#define TETRIS_LEVELS (sizeof(levels)/sizeof(struct tetris_level))




void main() {
    int w=12, h=15;
    struct tetris t;
    int count=0;
    clean();
    int state = 0;
    int step = 3;
    int num = 65536;
    char cmd;

    cls();


    tetris_init(&t, w, h);
    tetris_new_block(&t);
    
    while (1) {
        count++;

        tetris_print(&t);
        
        if (count%10 == 0) {
            cmd=getchar();
            switch (cmd) {
                case 'A':
                    t.x--;
                    if (tetris_hittest(&t))
                        t.x++;
                    break;
                case 'D':
                    t.x++;
                    if (tetris_hittest(&t))
                        t.x--;
                    break;
                case 'S':
                    tetris_gravity(&t);
                    break;
                case 0x20:
                    tetris_rotate(&t);
                    break;
            }
        }
        if (state == step) {
            beep();
            // say_lpt_a();
            
            tetris_gravity(&t);
            tetris_check_lines(&t);

        }

        HELO(state);
        state = next(state, step);
        if(t.gameover) {
             tetris_init(&t,w,h);
        }
    }
}


void sleep() {
    for (int i = 0; i < 100; i++) {
        clock++;
    }
}

void long_sleep() {
    for (int i = 0; i < 1000; i++) {
        clock++;
    }
}

void very_long_sleep() {
    for (int i = 0; i < 30000; i++) {
        asm("nop");
    }
}


void clean() {
    port0 = 0xff;
    port1 = 0xf;
    port3 = 0x01;
}

char getchar() {
    return (char) port4;
}

void H() {
    port1 = LED_3;
    port0 = HEX_H;
    sleep();
    clean();
}

void E() {
    port1 = LED_2;
    port0 = HEX_E;
    sleep();
    clean();
}

void L() {
    port1 = LED_1;
    port0 = HEX_L;
    sleep();
    clean();
}

void O() {
    port1 = LED_0;
    port0 = HEX_O;
    sleep();
    clean();
}

void HELO(int state) {
    if (state > 500) H();
    if (state > 400) E();
    if (state > 300) L();
    if (state > 200) O();
}

int next(int prev, int step) {
    if (prev > 600) prev = 0;
    return prev + step;
}

void beep() {
    for (short i = 0; i < 100; i++) {
        port2 = 0xff00;
        long_sleep();
        port2 = 0x0000;
        long_sleep();
    }
}

void __attribute__((optimize("O0"))) say_serial_a() {
    port5 = 0x1468;
    port5 = 0x1460;
    port6 = 0x0041;
    port5 = 0x1462;
    port5 = 0x1460;

}

void __attribute__((optimize("O0"))) say_lpt_a() {
    port2 = 0x41;
    port3 = 0x01;
    very_long_sleep();
    port3 = 0x00;
    very_long_sleep();
    port3 = 0x01;
}


short time() {
    return port5;
}


void
tetris_init(struct tetris *t,int w,int h) {
    int x, y;
    t->level = 1;
    t->score = 0;
    t->gameover = 0;
    t->w = w;
    t->h = h;
    for (x=0; x<w; x++) {
        for (y=0; y<h; y++)
            t->game[x][y] = ' ';
    }
}

void
tetris_print(struct tetris *t) {
    int x,y;
    int dx=30,dy=20;

setpos(0,1);
  ee_printf("[LEVEL: %d | SCORE: %d]\n", t->level, t->score);


setpos(0,55);  
ee_printf("Press 'A' to left \n");
ee_printf("Press 'D' to right \n");
ee_printf("Press 'S' to down \n");
ee_printf("Press 'Space' to rotate \n");

for (y=0; y<t->h; y++) {
    setpos(0+dx,y+dy);
    ee_printf ("!");
    setpos((t->w+1)+dx,y+dy);
    ee_printf ("!");
}

for (x=0; x<t->w+2; x++) {   
    setpos(x+dx,y+dy);
     ee_printf("~");
}



setpos(0,30);
    for (y=0; y<t->h; y++) {
        for (x=0; x<t->w; x++) {
            setpos(dx+x+1,dy+y);
            if (x>=t->x && y>=t->y 
                    && x<(t->x+t->current.w) && y<(t->y+t->current.h) 
                    && t->current.data[y-t->y][x-t->x]!=' ')
                ee_printf("%c", t->current.data[y-t->y][x-t->x]);
            else
                ee_printf("%c", t->game[x][y]);
        }
    }
}

int
tetris_hittest(struct tetris *t) {
    int x,y,X,Y;
    struct tetris_block b=t->current;
    for (x=0; x<b.w; x++)
        for (y=0; y<b.h; y++) {
            X=t->x+x;
            Y=t->y+y;
            if (X<0 || X>=t->w)
                return 1;
            if (b.data[y][x]!=' ') {
                if ((Y>=t->h) || 
                        (X>=0 && X<t->w && Y>=0 && t->game[X][Y]!=' ')) {
                    return 1;
                }
            }
        }
    return 0;
}


int random() {
    return (int)port5;
}


void
tetris_new_block(struct tetris *t) {
    t->current=blocks[random()%TETRIS_PIECES];
    t->x=(t->w/2) - (t->current.w/2);
    t->y=0;
    if (tetris_hittest(t)) {
        t->gameover=1;
    }
}

void
tetris_print_block(struct tetris *t) {
    int x,y,X,Y;
    struct tetris_block b=t->current;
    for (x=0; x<b.w; x++)
        for (y=0; y<b.h; y++) {
            if (b.data[y][x]!=' ')
                t->game[t->x+x][t->y+y]=b.data[y][x];
        }
}

void
tetris_rotate(struct tetris *t) {
    struct tetris_block b=t->current;
    struct tetris_block s=b;
    int x,y;
    b.w=s.h;
    b.h=s.w;
    for (x=0; x<s.w; x++)
        for (y=0; y<s.h; y++) {
            b.data[x][y]=s.data[s.h-y-1][x];
        }
    x=t->x;
    y=t->y;
    t->x-=(b.w-s.w)/2;
    t->y-=(b.h-s.h)/2;
    t->current=b;
    if (tetris_hittest(t)) {
        t->current=s;
        t->x=x;
        t->y=y;
    }
}

void
tetris_gravity(struct tetris *t) {
    int x,y;
    t->y++;
    if (tetris_hittest(t)) {
        t->y--;
        tetris_print_block(t);
        tetris_new_block(t);
    }
}

void
tetris_fall(struct tetris *t, int l) {
    int x,y;
    for (y=l; y>0; y--) {
        for (x=0; x<t->w; x++)
            t->game[x][y]=t->game[x][y-1];
    }
    for (x=0; x<t->w; x++)
        t->game[x][0]=' ';
}

void
tetris_check_lines(struct tetris *t) {
    int x,y,l;
    int p=100;
    for (y=t->h-1; y>=0; y--) {
        l=1;
        for (x=0; x<t->w && l; x++) {
            if (t->game[x][y]==' ') {
                l=0;
            }
        }
        if (l) {
            t->score += p;
            p*=2;
            tetris_fall(t, y);
            y++;
        }
    }
}

int
tetris_level(struct tetris *t) {
    int i;
    for (i=0; i<TETRIS_LEVELS; i++) {
        if (t->score>=levels[i].score) {
            t->level = i+1;
        } else break;
    }
    return levels[t->level-1].nsec;
}