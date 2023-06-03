#include<stdio.h>
#include<graphics.h>
#include<string.h>
#include<time.h>
#include<ctype.h>
#include<conio.h>
// maximum width & height of the drawing window
#define x getmaxx()
#define y getmaxy()

// file pointer to store & retrieve match details
FILE *fp;

void loading(void); // loading screen
void introduction(void); // about the game screen
void main_menu(void);   // main menu screen
void controls(void); // controls screen
void credits(void); // acknowledgement screen
void enternames(void); // enter names of player1 & player2 screen
void names_align(void); // to align names of player1 & player 2 on the board
void win_screen(void); // winner screen
void recentgames(void); // recently played matches screen
void game(void); // board
void board_design(void); // board design
void edge_check(int *a, int *b, int *c, int *d); // edge mapping
void box_check(void); // to check box was formed or not
void box(void); // to assign who created the box
void box_print(void); // to print P1/P2 in the box accordingly

// Global Variables
int main_window; // Primary Drawing Window
int start=0;
int cx=100, cy=100; // Cursor Coordinates
int call_to_box=0; // Flag for whether to call box function or not
int print_box[40];
int player_turn=0;
int player_turn_done=0;
int edge_flag[100];
int box_created[40];
int all_coords[80][5]; // To store lines drawn by player1/player2
int coords_count=0; // counter for number of lines drawn
int line_already_drawn_flag=0;
int a,b;
int lines=60;
double time_spent=0.0; // to store time played in seconds
double time_spent_min=0.0; // to store time played in minutes
char details[150];
char winner[50]={0}; // store name of winner

// to store names, score & alignment of names of both players
struct player
{
    char name[50];
    int score;
    int name_align_x;
    int name_align_y;
}p1,p2;

void box_print(void) // to keep printing the initial till the game ends
{
    settextstyle(3,0,3);
    // 1st box
    if(print_box[0]==1)
    {
        setcolor(10);
        outtextxy(140,140,"P1");
    }
    else if(print_box[0]==2)
    {
        setcolor(13);
        outtextxy(140,140,"P2");
    }
    // 2nd box
    if(print_box[1]==1)
    {
        setcolor(10);
        outtextxy(240,140,"P1");
    }  
    else if(print_box[1]==2)
    {
        setcolor(13);
        outtextxy(240,140,"P2");
    }
    // 3rd box
    if(print_box[2]==1)
    {
        setcolor(10);
        outtextxy(340,140,"P1");
    }    
    else if(print_box[2]==2)
    {
        setcolor(13);
        outtextxy(340,140,"P2");
    }    
    // 4th box
    if(print_box[3]==1)
    {
        setcolor(10);
        outtextxy(440,140,"P1");
    }    
    else if(print_box[3]==2)
    {
        setcolor(13);
        outtextxy(440,140,"P2");
    }    
    // 5th box
    if(print_box[4]==1)
    {
        setcolor(10);
        outtextxy(540,140,"P1");
    }    
    else if(print_box[4]==2)
    {
        setcolor(13);
        outtextxy(540,140,"P2");
    }    
    // 6th box
    if(print_box[5]==1)
    {
        setcolor(10);
        outtextxy(140,240,"P1");
    }    
    else if(print_box[5]==2)
    {
        setcolor(13);
        outtextxy(140,240,"P2");
    }    
    // 7th box
    if(print_box[6]==1)
    {
        setcolor(10);
        outtextxy(240,240,"P1");
    }    
    else if(print_box[6]==2)
    {
        setcolor(13);
        outtextxy(240,240,"P2");
    }    
    // 8th box
    if(print_box[7]==1)
    {
        setcolor(10);
        outtextxy(340,240,"P1");
    }    
    else if(print_box[7]==2)
    {
        setcolor(13);
        outtextxy(340,240,"P2");
    }    
    // 9th box
    if(print_box[8]==1)
    {
        setcolor(10);
        outtextxy(440,240,"P1");
    }    
    else if(print_box[8]==2)
    {
        setcolor(13);
        outtextxy(440,240,"P2");
    }     
    // 10th box
    if(print_box[9]==1)
    {
        setcolor(10);
        outtextxy(540,240,"P1");
    }    
    else if(print_box[9]==2)
    {
        setcolor(13);
        outtextxy(540,240,"P2");
    }    
    // 11th box
    if(print_box[10]==1)
    {
        setcolor(10);
        outtextxy(140,340,"P1");
    }    
    else if(print_box[10]==2)
    {
        setcolor(13);
        outtextxy(140,340,"P2");
    }    
    // 12th box
    if(print_box[11]==1)
    {
        setcolor(10);
        outtextxy(240,340,"P1");
    }    
    else if(print_box[11]==2)
    {
        setcolor(13);
        outtextxy(240,340,"P2");
    }    
    // 13th box
    if(print_box[12]==1)
    {
        setcolor(10);
        outtextxy(340,340,"P1");
    }    
    else if(print_box[12]==2)
    {
        setcolor(13);
        outtextxy(340,340,"P2");
    }    
    // 14th box
    if(print_box[13]==1)
    {
        setcolor(10);
        outtextxy(440,340,"P1");
    }    
    else if(print_box[13]==2)
    {
        setcolor(13);
        outtextxy(440,340,"P2");
    }    
    // 15th box
    if(print_box[14]==1)
    {
        setcolor(10);
        outtextxy(540,340,"P1");
    }    
    else if(print_box[14]==2)
    {
        setcolor(13);
        outtextxy(540,340,"P2");
    }    
    // 16th box
    if(print_box[15]==1)
    {
        setcolor(10);
        outtextxy(140,440,"P1");
    }    
    else if(print_box[15]==2)
    {
        setcolor(13);
        outtextxy(140,440,"P2");
    }    
    // 17th box
    if(print_box[16]==1)
    {
        setcolor(10);
        outtextxy(240,440,"P1");
    }    
    else if(print_box[16]==2)
    {
        setcolor(13);
        outtextxy(240,440,"P2");
    }    
    // 18th box
    if(print_box[17]==1)
    {
        setcolor(10);
        outtextxy(340,440,"P1");
    }
    else if(print_box[17]==2)
    {
        setcolor(13);
        outtextxy(340,440,"P2");
    }
    // 19th box
    if(print_box[18]==1)
    {
        setcolor(10);
        outtextxy(440,440,"P1");
    }
    else if(print_box[18]==2)
    {
        setcolor(13);
        outtextxy(440,440,"P2");
    }
    // 20th box
    if(print_box[19]==1)
    {
        setcolor(10);
        outtextxy(540,440,"P1");
    }    
    else if(print_box[19]==2)
    {
        setcolor(13);
        outtextxy(540,440,"P2");
    }    
    // 21st box
    if(print_box[20]==1)
    {
        setcolor(10);
        outtextxy(140,540,"P1");
    }    
    else if(print_box[20]==2)
    {
        setcolor(13);
        outtextxy(140,540,"P2");
    }    
    // 22nd box
    if(print_box[21]==1)
    {
        setcolor(10);
        outtextxy(240,540,"P1");
    }    
    else if(print_box[21]==2)
    {
        setcolor(13);
        outtextxy(240,540,"P2");
    }    
    // 23rd box
    if(print_box[22]==1)
    {
        setcolor(10);
        outtextxy(340,540,"P1");
    }    
    else if(print_box[22]==2)
    {
        setcolor(13);
        outtextxy(340,540,"P2");
    }    
    // 24th box
    if(print_box[23]==1)
    {
        setcolor(10);
        outtextxy(440,540,"P1");
    }    
    else if(print_box[23]==2)
    {
        setcolor(13);
        outtextxy(440,540,"P2");
    }    
    // 25th box
    if(print_box[24]==1)
    {
        setcolor(10);
        outtextxy(540,540,"P1");
    }    
    else if(print_box[24]==2)
    {
        setcolor(13);
        outtextxy(540,540,"P2");
    }    
}
// To check which player made the box
void box(void)
{
    // 1st box
    if(box_created[0]==1 && player_turn==0 && print_box[0]!=1 && print_box[0]!=2)
    {
        print_box[0]=1;
        p1.score++;
    }
    else if(box_created[0]==1 && player_turn==1 && print_box[0]!=1 && print_box[0]!=2)
    {
        print_box[0]=2;
        p2.score++;
    }
    // 2nd box
    if(box_created[1]==1 && player_turn==0 && print_box[1]!=1 && print_box[1]!=2)
    {
        print_box[1]=1;
        p1.score++;
    }
    else if(box_created[1]==1 && player_turn==1 && print_box[1]!=1 && print_box[1]!=2)
    {
        print_box[1]=2;
        p2.score++;
    }
    // 3rd box
    if(box_created[2]==1 && player_turn==0 && print_box[2]!=1 && print_box[2]!=2)
    {
        print_box[2]=1;
        p1.score++;
    }
    else if(box_created[2]==1 && player_turn==1 && print_box[2]!=1 && print_box[2]!=2)
    {
        print_box[2]=2;
        p2.score++;
    }
    // 4th box
    if(box_created[3]==1 && player_turn==0 && print_box[3]!=1 && print_box[3]!=2)
    {
        print_box[3]=1;
        p1.score++;
    }
    else if(box_created[3]==1 && player_turn==1 && print_box[3]!=1 && print_box[3]!=2)
    {    
        print_box[3]=2;
        p2.score++;
    }
    // 5th box
    if(box_created[4]==1 && player_turn==0 && print_box[4]!=1 && print_box[4]!=2)
    {    
        print_box[4]=1;
        p1.score++;
    }
    else if(box_created[4]==1 && player_turn==1 && print_box[4]!=1 && print_box[4]!=2)
    {    
        print_box[4]=2;
        p2.score++;
    }
    // 6th box
    if(box_created[5]==1 && player_turn==0 && print_box[5]!=1 && print_box[5]!=2)
    {    
        print_box[5]=1;
        p1.score++;
    }
    else if(box_created[5]==1 && player_turn==1 && print_box[5]!=1 && print_box[5]!=2)
    {    
        print_box[5]=2;
        p2.score++;
    }
    // 7th box
    if(box_created[6]==1 && player_turn==0 && print_box[6]!=1 && print_box[6]!=2)
    {    
        print_box[6]=1;
        p1.score++;
    }
    else if(box_created[6]==1 && player_turn==1 && print_box[6]!=1 && print_box[6]!=2)
    {    
        print_box[6]=2;
        p2.score++;
    }
    // 8th box
    if(box_created[7]==1 && player_turn==0 && print_box[7]!=1 && print_box[7]!=2)
    {    
        print_box[7]=1;
        p1.score++;
    }
    else if(box_created[7]==1 && player_turn==1 && print_box[7]!=1 && print_box[7]!=2)
    {    
        print_box[7]=2;
        p2.score++;
    }
    // 9th box
    if(box_created[8]==1 && player_turn==0 && print_box[8]!=1 && print_box[8]!=2)
    {    
        print_box[8]=1;
        p1.score++;
    }
    else if(box_created[8]==1 && player_turn==1 && print_box[8]!=1 && print_box[8]!=2)
    {    
        print_box[8]=2;
        p2.score++;
    }
    // 10th box
    if(box_created[9]==1 && player_turn==0 && print_box[9]!=1 && print_box[9]!=2)
    {    
        print_box[9]=1;
        p1.score++;
    }
    else if(box_created[9]==1 && player_turn==1 && print_box[9]!=1 && print_box[9]!=2)
    {    
        print_box[9]=2;
        p2.score++;
    }
    // 11th box
    if(box_created[10]==1 && player_turn==0 && print_box[10]!=1 && print_box[10]!=2)
    {    
        print_box[10]=1;
        p1.score++;
    }
    else if(box_created[10]==1 && player_turn==1 && print_box[10]!=1 && print_box[10]!=2)
    {    
        print_box[10]=2;
        p2.score++;
    }
    // 12th box
    if(box_created[11]==1 && player_turn==0 && print_box[11]!=1 && print_box[11]!=2)
    {    
        print_box[11]=1;
        p1.score++;
    }
    else if(box_created[11]==1 && player_turn==1 && print_box[11]!=1 && print_box[11]!=2)
    {    
        print_box[11]=2;
        p2.score++;
    }
    // 13th box
    if(box_created[12]==1 && player_turn==0 && print_box[12]!=1 && print_box[12]!=2)
    {    
        print_box[12]=1;
        p1.score++;
    }
    else if(box_created[12]==1 && player_turn==1 && print_box[12]!=1 && print_box[12]!=2)
    {    
        print_box[12]=2;
        p2.score++;
    }
    // 14th box
    if(box_created[13]==1 && player_turn==0 && print_box[13]!=1 && print_box[13]!=2)
    {    
        print_box[13]=1;
        p1.score++;
    }
    else if(box_created[13]==1 && player_turn==1 && print_box[13]!=1 && print_box[13]!=2)
    {    
        print_box[13]=2;
        p2.score++;
    }
    // 15th box
    if(box_created[14]==1 && player_turn==0 && print_box[14]!=1 && print_box[14]!=2)
    {    
        print_box[14]=1;
        p1.score++;
    }
    else if(box_created[14]==1 && player_turn==1 && print_box[14]!=1 && print_box[14]!=2)
    {    
        print_box[14]=2;
        p2.score++;
    }
    // 16th box
    if(box_created[15]==1 && player_turn==0 && print_box[15]!=1 && print_box[15]!=2)
    {    
        print_box[15]=1;
        p1.score++;
    }
    else if(box_created[15]==1 && player_turn==1 && print_box[15]!=1 && print_box[15]!=2)
    {    
        print_box[15]=2;
        p2.score++;
    }
    // 17th box
    if(box_created[16]==1 && player_turn==0 && print_box[16]!=1 && print_box[16]!=2)
    {    
        print_box[16]=1;
        p1.score++;
    }
    else if(box_created[16]==1 && player_turn==1 && print_box[16]!=1 && print_box[16]!=2)
    {    
        print_box[16]=2;
        p2.score++;
    }
    // 18th box
    if(box_created[17]==1 && player_turn==0 && print_box[17]!=1 && print_box[17]!=2)
    {    
        print_box[17]=1;
        p1.score++;
    }
    else if(box_created[17]==1 && player_turn==1 && print_box[17]!=1 && print_box[17]!=2)
    {    
        print_box[17]=2;
        p2.score++;
    }
    // 19th box
    if(box_created[18]==1 && player_turn==0 && print_box[18]!=1 && print_box[18]!=2)
    {    
        print_box[18]=1;
        p1.score++;
    }
    else if(box_created[18]==1 && player_turn==1 && print_box[18]!=1 && print_box[18]!=2)
    {    
        print_box[18]=2;
        p2.score++;
    }
    // 20th box
    if(box_created[19]==1 && player_turn==0 && print_box[19]!=1 && print_box[19]!=2)
    {    
        print_box[19]=1;
        p1.score++;
    }
    else if(box_created[19]==1 && player_turn==1 && print_box[19]!=1 && print_box[19]!=2)
    {    
        print_box[19]=2;
        p2.score++;
    }
    // 21st box
    if(box_created[20]==1 && player_turn==0 && print_box[20]!=1 && print_box[20]!=2)
    {    
        print_box[20]=1;
        p1.score++;
    }
    else if(box_created[20]==1 && player_turn==1 && print_box[20]!=1 && print_box[20]!=2)
    {    
        print_box[20]=2;
        p2.score++;
    }
    // 22nd box
    if(box_created[21]==1 && player_turn==0 && print_box[21]!=1 && print_box[21]!=2)
    {    
        print_box[21]=1;
        p1.score++;
    }
    else if(box_created[21]==1 && player_turn==1 && print_box[21]!=1 && print_box[21]!=2)
    {    
        print_box[21]=2;
        p2.score++;
    }
    // 23rd box
    if(box_created[22]==1 && player_turn==0 && print_box[22]!=1 && print_box[22]!=2)
    {    
        print_box[22]=1;
        p1.score++;
    }
    else if(box_created[22]==1 && player_turn==1 && print_box[22]!=1 && print_box[22]!=2)
    {    
        print_box[22]=2;
        p2.score++;
    }
    // 24th box
    if(box_created[23]==1 && player_turn==0 && print_box[23]!=1 && print_box[23]!=2)
    {    
        print_box[23]=1;
        p1.score++;
    }
    else if(box_created[23]==1 && player_turn==1 && print_box[23]!=1 && print_box[23]!=2)
    {    
        print_box[23]=2;
        p2.score++;
    }
    // 25th box
    if(box_created[24]==1 && player_turn==0 && print_box[24]!=1 && print_box[24]!=2)
    {    
        print_box[24]=1;
        p1.score++;
    }
    else if(box_created[24]==1 && player_turn==1 && print_box[24]!=1 && print_box[24]!=2)
    {    
        print_box[24]=2;
        p2.score++;
    }
    // To keep the turn of same player
    player_turn_done=0;
}
void box_check(void)
{
    // used if statement because more than 1 box could've been made using 1 line
    settextstyle(3,0,2);
    // 1st box
    if(edge_flag[0]==1 && edge_flag[5]==1 && edge_flag[6]==1 && edge_flag[11]==1 && box_created[0]!=1)
    {
        box_created[0]=1;
        call_to_box=1;
    }
    // 2nd box
    if(edge_flag[1]==1 && edge_flag[6]==1 && edge_flag[7]==1 && edge_flag[12]==1 && box_created[1]!=1)
    {
        box_created[1]=1;
        call_to_box=1;
    }
    // 3rd box
    if(edge_flag[2]==1 && edge_flag[7]==1 && edge_flag[8]==1 && edge_flag[13]==1 && box_created[2]!=1)
    {
        box_created[2]=1;
        call_to_box=1;
    }
    // 4th box
    if(edge_flag[3]==1 && edge_flag[8]==1 && edge_flag[9]==1 && edge_flag[14]==1 && box_created[3]!=1)
    {
        box_created[3]=1;
        call_to_box=1;
    }
    // 5th box
    if(edge_flag[4]==1 && edge_flag[9]==1 && edge_flag[10]==1 && edge_flag[15]==1 && box_created[4]!=1)
    {
        box_created[4]=1;
        call_to_box=1;
    }
    // 6th box
    if(edge_flag[11]==1 && edge_flag[16]==1 && edge_flag[17]==1 && edge_flag[22]==1 && box_created[5]!=1)
    {
        box_created[5]=1;
        call_to_box=1;
    }
    // 7th box
    if(edge_flag[12]==1 && edge_flag[17]==1 && edge_flag[18]==1 && edge_flag[23]==1 && box_created[6]!=1)
    {
        box_created[6]=1;
        call_to_box=1;
    }
    // 8th box
    if(edge_flag[13]==1 && edge_flag[18]==1 && edge_flag[19]==1 && edge_flag[24]==1 && box_created[7]!=1)
    {
        box_created[7]=1;
        call_to_box=1;
    }
    //9th box
    if(edge_flag[14]==1 && edge_flag[19]==1 && edge_flag[20]==1 && edge_flag[25]==1 && box_created[8]!=1)
    {
        box_created[8]=1;
        call_to_box=1;
    }
    // 10th box
    if(edge_flag[15]==1 && edge_flag[20]==1 && edge_flag[21]==1 && edge_flag[26]==1 && box_created[9]!=1)
    {
        box_created[9]=1;
        call_to_box=1;
    }
    // 11th box
    if(edge_flag[22]==1 && edge_flag[27]==1 && edge_flag[28]==1 && edge_flag[33]==1 && box_created[10]!=1)
    {
        box_created[10]=1;
        call_to_box=1;
    }
    // 12th box
    if(edge_flag[23]==1 && edge_flag[28]==1 && edge_flag[29]==1 && edge_flag[34]==1 && box_created[11]!=1)
    {
        box_created[11]=1;
        call_to_box=1;
    }
    // 13th box
    if(edge_flag[24]==1 && edge_flag[29]==1 && edge_flag[30]==1 && edge_flag[35]==1 && box_created[12]!=1)
    {
        box_created[12]=1;
        call_to_box=1;
    }
    // 14th box
    if(edge_flag[25]==1 && edge_flag[30]==1 && edge_flag[31]==1 && edge_flag[36]==1 && box_created[13]!=1)
    {
        box_created[13]=1;
        call_to_box=1;
    }
    // 15th box
    if(edge_flag[26]==1 && edge_flag[31]==1 && edge_flag[32]==1 && edge_flag[37]==1 && box_created[14]!=1)
    {
        box_created[14]=1;
        call_to_box=1;
    }
    // 16th box
    if(edge_flag[33]==1 && edge_flag[38]==1 && edge_flag[39]==1 && edge_flag[44]==1 && box_created[15]!=1)
    {
        box_created[15]=1;
        call_to_box=1;
    }
    // 17th box
    if(edge_flag[34]==1 && edge_flag[39]==1 && edge_flag[40]==1 && edge_flag[45]==1 && box_created[16]!=1)
    {
        box_created[16]=1;
        call_to_box=1;
    }
    // 18th box
    if(edge_flag[35]==1 && edge_flag[40]==1 && edge_flag[41]==1 && edge_flag[46]==1 && box_created[17]!=1)
    {
        box_created[17]=1;
        call_to_box=1;
    }
    // 19th box
    if(edge_flag[36]==1 && edge_flag[41]==1 && edge_flag[42]==1 && edge_flag[47]==1 && box_created[18]!=1)
    {
        box_created[18]=1;
        call_to_box=1;
    }
    // 20th box
    if(edge_flag[37]==1 && edge_flag[42]==1 && edge_flag[43]==1 && edge_flag[48]==1 && box_created[19]!=1)
    {
        box_created[19]=1;
        call_to_box=1;
    }
    // 21st box
    if(edge_flag[44]==1 && edge_flag[49]==1 && edge_flag[50]==1 && edge_flag[55]==1 && box_created[20]!=1)
    {
        box_created[20]=1;
        call_to_box=1;
    }
    // 22nd box
    if(edge_flag[45]==1 && edge_flag[50]==1 && edge_flag[51]==1 && edge_flag[56]==1 && box_created[21]!=1)
    {
        box_created[21]=1;
        call_to_box=1;
    }
    // 23rd box
    if(edge_flag[46]==1 && edge_flag[51]==1 && edge_flag[52]==1 && edge_flag[57]==1 && box_created[22]!=1)
    {
        box_created[22]=1;
        call_to_box=1;
    }
    // 24th box
    if(edge_flag[47]==1 && edge_flag[52]==1 && edge_flag[53]==1 && edge_flag[58]==1 && box_created[23]!=1)
    {
        box_created[23]=1;
        call_to_box=1;
    }
    // 25th box
    if(edge_flag[48]==1 && edge_flag[53]==1 && edge_flag[54]==1 && edge_flag[59]==1 && box_created[24]!=1)
    {
        box_created[24]=1;
        call_to_box=1;
    }
}
void edge_check(int *a,int *b,int *c,int *d) // edge mapping
{
    // 1st Box
    if(edge_flag[0]!=1 || edge_flag[5]!=1 || edge_flag[6]!=1 || edge_flag[11]!=1)
    {
        if((*a==100 && *b==100 && *c==200 && *d==100) || (*a==200 && *b==100 && *c==100 && *d==100))
            edge_flag[0]=1;
        else if((*a==100 && *b==100 && *c==100 && *d==200) || (*a==100 && *b==200 && *c==100 && *d==100))
            edge_flag[5]=1;
        else if((*a==200 && *b==100 && *c==200 && *d==200) || (*a==200 && *b==200 && *c==200 && *d==100))
            edge_flag[6]=1;
        else if((*a==100 && *b==200 && *c==200 && *d==200) || (*a==200 && *b==200 && *c==100 && *d==200))
            edge_flag[11]=1;
    }
    // 2nd Box
    if(edge_flag[1]!=1 || edge_flag[6]!=1 || edge_flag[7]!=1 || edge_flag[12]!=1)
    {
        if((*a==200 && *b==100 && *c==300 && *d==100) || (*a==300 && *b==100 && *c==200 && *d==100))
            edge_flag[1]=1;
        else if((*a==200 && *b==100 && *c==200 && *d==200) || (*a==200 && *b==200 && *c==200 && *d==100))
            edge_flag[6]=1;
        else if((*a==300 && *b==100 && *c==300 && *d==200) || (*a==300 && *b==200 && *c==300 && *d==100))
            edge_flag[7]=1;
        else if((*a==200 && *b==200 && *c==300 && *d==200) || (*a==300 && *b==200 && *c==200 && *d==200))
            edge_flag[12]=1;
    }
    // 3rd Box
    if(edge_flag[2]!=1 || edge_flag[7]!=1 || edge_flag[8]!=1 || edge_flag[13]!=1)
    {
        if((*a==300 && *b==100 && *c==400 && *d==100) || (*a==400 && *b==100 && *c==300 && *d==100))
            edge_flag[2]=1;
        else if((*a==300 && *b==100 && *c==300 && *d==200) || (*a==300 && *b==200 && *c==300 && *d==100))
            edge_flag[7]=1;
        else if((*a==400 && *b==100 && *c==400 && *d==200) || (*a==400 && *b==200 && *c==400 && *d==100))
            edge_flag[8]=1;
        else if((*a==300 && *b==200 && *c==400 && *d==200) || (*a==400 && *b==200 && *c==300 && *d==200))
            edge_flag[13]=1;
    }
    // 4th Box
    if(edge_flag[3]!=1 || edge_flag[8]!=1 || edge_flag[9]!=1 || edge_flag[14]!=1)
    {
        if((*a==400 && *b==100 && *c==500 && *d==100) || (*a==500 && *b==100 && *c==400 && *d==100))
            edge_flag[3]=1;
        else if((*a==400 && *b==100 && *c==400 && *d==200) || (*a==400 && *b==200 && *c==400 && *d==100))
            edge_flag[8]=1;
        else if((*a==500 && *b==100 && *c==500 && *d==200) || (*a==500 && *b==200 && *c==500 && *d==100))
            edge_flag[9]=1;
        else if((*a==400 && *b==200 && *c==500 && *d==200) || (*a==500 && *b==200 && *c==400 && *d==200))
            edge_flag[14]=1;
    }
    // 5th Box
    if(edge_flag[4]!=1 || edge_flag[9]!=1 || edge_flag[10]!=1 || edge_flag[15]!=1)
    {
        if((*a==500 && *b==100 && *c==600 && *d==100) || (*a==600 && *b==100 && *c==500 && *d==100))
            edge_flag[4]=1;
        else if((*a==500 && *b==100 && *c==500 && *d==200) || (*a==500 && *b==200 && *c==500 && *d==100))
            edge_flag[9]=1;
        else if((*a==600 && *b==100 && *c==600 && *d==200) || (*a==600 && *b==200 && *c==600 && *d==100))
            edge_flag[10]=1;
        else if((*a==500 && *b==200 && *c==600 && *d==200) || (*a==600 && *b==200 && *c==500 && *d==200))
            edge_flag[15]=1;
    }
    // 6th Box
    if(edge_flag[11]!=1 || edge_flag[16]!=1 || edge_flag[17]!=1 || edge_flag[22]!=1)
    {
        if((*a==100 && *b==200 && *c==200 && *d==200) || (*a==200 && *b==200 && *c==100 && *d==200))
            edge_flag[11]=1;
        else if((*a==100 && *b==200 && *c==100 && *d==300) || (*a==100 && *b==300 && *c==100 && *d==200))
            edge_flag[16]=1;
        else if((*a==200 && *b==200 && *c==200 && *d==300) || (*a==200 && *b==300 && *c==200 && *d==200))
            edge_flag[17]=1;
        else if((*a==100 && *b==300 && *c==200 && *d==300) || (*a==200 && *b==300 && *c==100 && *d==300))
            edge_flag[22]=1;
    }
    // 7th Box
    if(edge_flag[12]!=1 || edge_flag[17]!=1 || edge_flag[18]!=1 || edge_flag[23]!=1)
    {
        if((*a==200 && *b==200 && *c==300 && *d==200) || (*a==300 && *b==200 && *c==200 && *d==200))
            edge_flag[12]=1;
        else if((*a==200 && *b==200 && *c==200 && *d==300) || (*a==200 && *b==300 && *c==200 && *d==200))
            edge_flag[17]=1;
        else if((*a==300 && *b==200 && *c==300 && *d==300) || (*a==300 && *b==300 && *c==300 && *d==200))
            edge_flag[18]=1;
        else if((*a==200 && *b==300 && *c==300 && *d==300) || (*a==300 && *b==300 && *c==200 && *d==300))
            edge_flag[23]=1;
    }
    // 8th Box
    if(edge_flag[13]!=1 || edge_flag[18]!=1 || edge_flag[19]!=1 || edge_flag[24]!=1)
    {
        if((*a==300 && *b==200 && *c==400 && *d==200) || (*a==400 && *b==200 && *c==300 && *d==200))
            edge_flag[13]=1;
        else if((*a==300 && *b==200 && *c==300 && *d==300) || (*a==300 && *b==300 && *c==300 && *d==200))
            edge_flag[18]=1;
        else if((*a==400 && *b==200 && *c==400 && *d==300) || (*a==400 && *b==300 && *c==400 && *d==200))
            edge_flag[19]=1;
        else if((*a==300 && *b==300 && *c==400 && *d==300) || (*a==400 && *b==300 && *c==300 && *d==300))
            edge_flag[24]=1;
    }
    // 9th Box
    if(edge_flag[14]!=1 || edge_flag[19]!=1 || edge_flag[20]!=1 || edge_flag[25]!=1)
    {
        if((*a==400 && *b==200 && *c==500 && *d==200) || (*a==500 && *b==200 && *c==400 && *d==200))
            edge_flag[14]=1;
        else if((*a==400 && *b==200 && *c==400 && *d==300) || (*a==400 && *b==300 && *c==400 && *d==200))
            edge_flag[19]=1;
        else if((*a==500 && *b==200 && *c==500 && *d==300) || (*a==500 && *b==300 && *c==500 && *d==200))
            edge_flag[20]=1;
        else if((*a==400 && *b==300 && *c==500 && *d==300) || (*a==500 && *b==300 && *c==400 && *d==300))
            edge_flag[25]=1;
    }
    // 10th Box
    if(edge_flag[15]!=1 || edge_flag[20]!=1 || edge_flag[21]!=1 || edge_flag[26]!=1)
    {
        if((*a==500 && *b==200 && *c==600 && *d==200) || (*a==600 && *b==200 && *c==500 && *d==200))
            edge_flag[15]=1;
        else if((*a==500 && *b==200 && *c==500 && *d==300) || (*a==500 && *b==300 && *c==500 && *d==200))
            edge_flag[20]=1;
        else if((*a==600 && *b==200 && *c==600 && *d==300) || (*a==600 && *b==300 && *c==600 && *d==200))
            edge_flag[21]=1;
        else if((*a==500 && *b==300 && *c==600 && *d==300) || (*a==600 && *b==300 && *c==500 && *d==300))
            edge_flag[26]=1;
    }
    // 11th Box
    if(edge_flag[22]!=1 || edge_flag[27]!=1 || edge_flag[28]!=1 || edge_flag[33]!=1)
    {
        if((*a==100 && *b==300 && *c==200 && *d==300) || (*a==200 && *b==300 && *c==100 && *d==300))
            edge_flag[22]=1;
        else if((*a==100 && *b==300 && *c==100 && *d==400) || (*a==100 && *b==400 && *c==100 && *d==300))
            edge_flag[27]=1;
        else if((*a==200 && *b==300 && *c==200 && *d==400) || (*a==200 && *b==400 && *c==200 && *d==300))
            edge_flag[28]=1;
        else if((*a==100 && *b==400 && *c==200 && *d==400) || (*a==200 && *b==400 && *c==100 && *d==400))
            edge_flag[33]=1;
    }
    // 12th Box
    if(edge_flag[23]!=1 || edge_flag[28]!=1 || edge_flag[29]!=1 || edge_flag[34]!=1)
    {
        if((*a==200 && *b==300 && *c==300 && *d==300) || (*a==300 && *b==300 && *c==200 && *d==300))
            edge_flag[23]=1;
        else if((*a==200 && *b==300 && *c==200 && *d==400) || (*a==200 && *b==400 && *c==200 && *d==300))
            edge_flag[28]=1;
        else if((*a==300 && *b==300 && *c==300 && *d==400) || (*a==300 && *b==400 && *c==300 && *d==300))
            edge_flag[29]=1;
        else if((*a==200 && *b==400 && *c==300 && *d==400) || (*a==300 && *b==400 && *c==200 && *d==400))
            edge_flag[34]=1;
    }
    // 13th Box
    if(edge_flag[24]!=1 || edge_flag[29]!=1 || edge_flag[30]!=1 || edge_flag[35]!=1)
    {
        if((*a==300 && *b==300 && *c==400 && *d==300) || (*a==400 && *b==300 && *c==300 && *d==300))
            edge_flag[24]=1;
        else if((*a==300 && *b==300 && *c==300 && *d==400) || (*a==300 && *b==400 && *c==300 && *d==300))
            edge_flag[29]=1;
        else if((*a==400 && *b==300 && *c==400 && *d==400) || (*a==400 && *b==400 && *c==400 && *d==300))
            edge_flag[30]=1;
        else if((*a==300 && *b==400 && *c==400 && *d==400) || (*a==400 && *b==400 && *c==300 && *d==400))
            edge_flag[35]=1;
    }
    // 14th Box
    if(edge_flag[25]!=1 || edge_flag[30]!=1 || edge_flag[31]!=1 || edge_flag[36]!=1)
    {
        if((*a==400 && *b==300 && *c==500 && *d==300) || (*a==500 && *b==300 && *c==400 && *d==300))
            edge_flag[25]=1;
        else if((*a==400 && *b==300 && *c==400 && *d==400) || (*a==400 && *b==400 && *c==400 && *d==300))
            edge_flag[30]=1;
        else if((*a==500 && *b==300 && *c==500 && *d==400) || (*a==500 && *b==400 && *c==500 && *d==300))
            edge_flag[31]=1;
        else if((*a==400 && *b==400 && *c==500 && *d==400) || (*a==500 && *b==400 && *c==400 && *d==400))
            edge_flag[36]=1;
    }
    // 15th Box
    if(edge_flag[26]!=1 || edge_flag[31]!=1 || edge_flag[32]!=1 || edge_flag[37]!=1)
    {
        if((*a==500 && *b==300 && *c==600 && *d==300) || (*a==600 && *b==300 && *c==500 && *d==300))
            edge_flag[26]=1;
        else if((*a==500 && *b==300 && *c==500 && *d==400) || (*a==500 && *b==400 && *c==500 && *d==300))
            edge_flag[31]=1;
        else if((*a==600 && *b==300 && *c==600 && *d==400) || (*a==600 && *b==400 && *c==600 && *d==300))
            edge_flag[32]=1;
        else if((*a==500 && *b==400 && *c==600 && *d==400) || (*a==600 && *b==400 && *c==500 && *d==400))
            edge_flag[37]=1;
    }
    // 16th Box
    if(edge_flag[33]!=1 || edge_flag[38]!=1 || edge_flag[39]!=1 || edge_flag[44]!=1)
    {
        if((*a==100 && *b==400 && *c==200 && *d==400) || (*a==200 && *b==400 && *c==100 && *d==400))
            edge_flag[33]=1;
        else if((*a==100 && *b==400 && *c==100 && *d==500) || (*a==100 && *b==500 && *c==100 && *d==400))
            edge_flag[38]=1;
        else if((*a==200 && *b==400 && *c==200 && *d==500) || (*a==200 && *b==500 && *c==200 && *d==400))
            edge_flag[39]=1;
        else if((*a==100 && *b==500 && *c==200 && *d==500) || (*a==200 && *b==500 && *c==100 && *d==500))
            edge_flag[44]=1;
    }
    // 17th Box
    if(edge_flag[34]!=1 || edge_flag[39]!=1 || edge_flag[40]!=1 || edge_flag[45]!=1)
    {
        if((*a==200 && *b==400 && *c==300 && *d==400) || (*a==300 && *b==400 && *c==200 && *d==400))
            edge_flag[34]=1;
        else if((*a==200 && *b==400 && *c==200 && *d==500) || (*a==200 && *b==500 && *c==200 && *d==400))
            edge_flag[39]=1;
        else if((*a==300 && *b==400 && *c==300 && *d==500) || (*a==300 && *b==500 && *c==300 && *d==400))
            edge_flag[40]=1;
        else if((*a==200 && *b==500 && *c==300 && *d==500) || (*a==300 && *b==500 && *c==200 && *d==500))
            edge_flag[45]=1;
    }
    // 18th Box
    if(edge_flag[35]!=1 || edge_flag[40]!=1 || edge_flag[41]!=1 || edge_flag[46]!=1)
    {
        if((*a==300 && *b==400 && *c==400 && *d==400) || (*a==400 && *b==400 && *c==300 && *d==400))
            edge_flag[35]=1;
        else if((*a==300 && *b==400 && *c==300 && *d==500) || (*a==300 && *b==500 && *c==300 && *d==400))
            edge_flag[40]=1;
        else if((*a==400 && *b==400 && *c==400 && *d==500) || (*a==400 && *b==500 && *c==400 && *d==400))
            edge_flag[41]=1;
        else if((*a==300 && *b==500 && *c==400 && *d==500) || (*a==400 && *b==500 && *c==300 && *d==500))
            edge_flag[46]=1;
    }
    // 19th Box
    if(edge_flag[36]!=1 || edge_flag[41]!=1 || edge_flag[42]!=1 || edge_flag[47]!=1)
    {
        if((*a==400 && *b==400 && *c==500 && *d==400) || (*a==500 && *b==400 && *c==400 && *d==400))
            edge_flag[36]=1;
        else if((*a==400 && *b==400 && *c==400 && *d==50*0) || (*a==400 && *b==500 && *c==400 && *d==400))
            edge_flag[41]=1;
        else if((*a==500 && *b==400 && *c==500 && *d==500) || (*a==500 && *b==500 && *c==500 && *d==400))
            edge_flag[42]=1;
        else if((*a==400 && *b==500 && *c==500 && *d==500) || (*a==500 && *b==500 && *c==400 && *d==500))
            edge_flag[47]=1;
    }
    // 20th Box
    if(edge_flag[37]!=1 || edge_flag[42]!=1 || edge_flag[43]!=1 || edge_flag[48]!=1)
    {
        if((*a==500 && *b==400 && *c==600 && *d==400) || (*a==600 && *b==400 && *c==500 && *d==400))
            edge_flag[37]=1;
        else if((*a==500 && *b==400 && *c==500 && *d==500) || (*a==500 && *b==500 && *c==500 && *d==400))
            edge_flag[42]=1;
        else if((*a==600 && *b==400 && *c==600 && *d==500) || (*a==600 && *b==500 && *c==600 && *d==400))
            edge_flag[43]=1;
        else if((*a==500 && *b==500 && *c==600 && *d==500) || (*a==600 && *b==500 && *c==500 && *d==500))
            edge_flag[48]=1;
    }
    // 21st Box
    if(edge_flag[44]!=1 || edge_flag[49]!=1 || edge_flag[50]!=1 || edge_flag[55]!=1)
    {
        if((*a==100 && *b==500 && *c==200 && *d==500) || (*a==200 && *b==500 && *c==100 && *d==500))
            edge_flag[44]=1;
        else if((*a==100 && *b==500 && *c==100 && *d==600) || (*a==100 && *b==600 && *c==100 && *d==500))
            edge_flag[49]=1;
        else if((*a==200 && *b==500 && *c==200 && *d==600) || (*a==200 && *b==600 && *c==200 && *d==500))
            edge_flag[50]=1;
        else if((*a==100 && *b==600 && *c==200 && *d==600) || (*a==200 && *b==600 && *c==100 && *d==600))
            edge_flag[55]=1;
    }
    // 22nd Box
    if(edge_flag[45]!=1 || edge_flag[50]!=1 || edge_flag[51]!=1 || edge_flag[56]!=1)
    {
        if((*a==200 && *b==500 && *c==300 && *d==500) || (*a==300 && *b==500 && *c==200 && *d==500))
            edge_flag[45]=1;
        else if((*a==200 && *b==500 && *c==200 && *d==600) || (*a==200 && *b==600 && *c==200 && *d==500))
            edge_flag[50]=1;
        else if((*a==300 && *b==500 && *c==300 && *d==600) || (*a==300 && *b==600 && *c==300 && *d==500))
            edge_flag[51]=1;
        else if((*a==200 && *b==600 && *c==300 && *d==600) || (*a==300 && *b==600 && *c==200 && *d==600))
            edge_flag[56]=1;
    }
    // 23rd Box
    if(edge_flag[46]!=1 || edge_flag[51]!=1 || edge_flag[52]!=1 || edge_flag[57]!=1)
    {
        if((*a==300 && *b==500 && *c==400 && *d==500) || (*a==400 && *b==500 && *c==300 && *d==500))
            edge_flag[46]=1;
        else if((*a==300 && *b==500 && *c==300 && *d==600) || (*a==300 && *b==600 && *c==300 && *d==500))
            edge_flag[51]=1;
        else if((*a==400 && *b==500 && *c==400 && *d==600) || (*a==400 && *b==600 && *c==400 && *d==500))
            edge_flag[52]=1;
        else if((*a==300 && *b==600 && *c==400 && *d==600) || (*a==400 && *b==600 && *c==300 && *d==600))
            edge_flag[57]=1;
    }
    // 24th Box
    if(edge_flag[47]!=1 || edge_flag[52]!=1 || edge_flag[53]!=1 || edge_flag[58]!=1)
    {
        if((*a==400 && *b==500 && *c==500 && *d==500) || (*a==500 && *b==500 && *c==400 && *d==500))
            edge_flag[47]=1;
        else if((*a==400 && *b==500 && *c==400 && *d==600) || (*a==400 && *b==600 && *c==400 && *d==500))
            edge_flag[52]=1;
        else if((*a==500 && *b==500 && *c==500 && *d==600) || (*a==500 && *b==600 && *c==500 && *d==500))
            edge_flag[53]=1;
        else if((*a==400 && *b==600 && *c==500 && *d==600) || (*a==500 && *b==600 && *c==400 && *d==600))
            edge_flag[58]=1;
    }
    // 25th Box
    if(edge_flag[48]!=1 || edge_flag[53]!=1 || edge_flag[54]!=1 || edge_flag[59]!=1)
    {
        if((*a==500 && *b==500 && *c==600 && *d==500) || (*a==600 && *b==500 && *c==500 && *d==500))
            edge_flag[48]=1;
        else if((*a==500 && *b==500 && *c==500 && *d==600) || (*a==500 && *b==600 && *c==500 && *d==500))
            edge_flag[53]=1;
        else if((*a==600 && *b==500 && *c==600 && *d==600) || (*a==600 && *b==600 && *c==600 && *d==500))
            edge_flag[54]=1;
        else if((*a==500 && *b==600 && *c==600 && *d==600) || (*a==600 && *b==600 && *c==500 && *d==600))
            edge_flag[59]=1;
    }
}
void board_design(void)
{
    int i, j, a = 100, b = 100, n=6;
    char name1[50], name2[50], score1[50], score2[50], lines_left[100];
    //BORDER
    setlinestyle(0,0,1);
    setcolor(15);
    rectangle(20,20,x-20,y-20);
    rectangle(10,10,x-10,y-10);
    rectangle(40,40,x-40,y-40);
    line(665,40,665,y-110);
    line(40,y-110,x-40,y-110);

    // Matrix
    setcolor(15);
    for(i=0;i<n;i++)
    { 
        for(j=0; j<n; j++)
        {
            circle(a,b,13);
            a=a+100;
        }
        b=b+100;
        a=100;
    }

    // Print Player1's Turn or Player2's Turn
    settextstyle(10,0,4);
    if(start==0)
    {
        setcolor(11);
        outtextxy(691,60,"Press ENTER to");
        outtextxy(686,100,"start the game!");
    }
    else if(player_turn==0 && start==1)
    {
        setcolor(10);
        outtextxy(691,80,"Player1's Turn");
    }
    else if(player_turn==1 && start==1)
    {
        setcolor(13);
        outtextxy(691,80,"Player2's Turn");
    }
    setcolor(15);
    line(665,150,x-40,150);

    // SCORE
    settextstyle(10,0,5);
    setcolor(12);
    outtextxy(760,175,"SCORE");
    // Player Names & Score    
    settextstyle(10,0,4);
    setcolor(10);
    sprintf(name1, "%s = %d", p1.name, p1.score);
    outtextxy(p1.name_align_x, p1.name_align_y, name1);
    setcolor(13);
    sprintf(name2, "%s = %d", p2.name, p2.score);
    outtextxy(p2.name_align_x, p2.name_align_y, name2);
    setcolor(15);
    line(665,330,x-40,330);

    // Border Color which is changing according to the player's turn
    if(player_turn==0)
    {
        setfillstyle(SOLID_FILL,10);
        floodfill(15,15,15);
    }
    else if(player_turn==1)
    {
        setfillstyle(SOLID_FILL,13);
        floodfill(15,15,15);
    }

    // CONTROLS
    settextstyle(10,0,5);
    setcolor(14);
    outtextxy(725,350,"CONTROLS");
    // UP
    setcolor(15);
    setfillstyle(SOLID_FILL,15);
    line(745,410,735,430); // /
    line(745,410,755,430); // \ //
    line(735,430,755,430); // _
    floodfill(743,420,15);
    // DOWN
    line(735,440,755,440); // _
    line(735,440,745,460); // \ //
    line(755,440,745,460); // /
    floodfill(743,450,15);
    // LEFT
    line(725,440,725,460); // |
    line(725,440,705,450); // /
    line(725,460,705,450); // \ //
    floodfill(715,450,15);
    // RIGHT
    line(765,440,765,460); // |
    line(765,440,785,450); // \ //
    line(765,460,785,450); // /
    floodfill(775,450,15);

    // Controls
    settextstyle(3,0,3);
    outtextxy(810,425,"NAVIGATION");

    // A & S key
    rectangle(725,500,765,540);
    outtextxy(738,508,"A");
    outtextxy(788,508,"To Lock 1st Point");

    rectangle(725,580,765,620);
    outtextxy(738,588,"S");
    outtextxy(788,588,"To Lock 2nd Point");

    // To print number of lines left
    settextstyle(10,0,4);
    line(620,y-110,620,y-40);
    sprintf(lines_left, "Lines Left : %d", lines);
    outtextxy(660,y-90,lines_left);
}
void game(void)
{
    setfillstyle(SOLID_FILL,15);
    //NAVIGATION
    int l1,l2,l3,l4;
    int i,a_pressed_flag=0;
    int input=0;
    while(1)
    {   
        // board will be redrawn only if any one of the valid key is pressed
        if(input==13 || input==80 || input==72 || input==75 || input==77 || input==97 || input==65|| input==115 || input==83)
        {    
            board_design();
            input=0;
        }
        if(kbhit())
        {
            input = getch();
            cleardevice();
            setcolor(14);
            setfillstyle(SOLID_FILL,14); // Cursor Color
            if(input==13 && start==0) // enter key to start the game
            {
                circle(cx,cy,5);
                outtextxy(160,y-90,"Enter Key Pressed");
                floodfill(cx,cy,14);
                start=1;
            }
            else if(start==1)
            {
                settextstyle(10,0,4);
                if(input==80) // down
                {   
                    if(cy<600)
                        cy+=100;
                    circle(cx,cy,5);
                    outtextxy(115,y-90,"DOWN Arrow Key Pressed");
                    floodfill(cx-3,cy-3,14);
                    moveto(cx,cy);
                    a=getx(); b=gety();
                }
                else if(input==72) // up 
                {   
                    if(cy>100)
                        cy-=100;
                    circle(cx,cy,5);
                    outtextxy(130,y-90,"UP Arrow Key Pressed");
                    floodfill(cx,cy,14);
                    moveto(cx,cy);
                    a=getx(); b=gety();
                }
                else if(input==75) // left
                {   
                    if(cx>100)
                        cx-=100;
                    circle(cx,cy,5);
                    outtextxy(115,y-90,"LEFT Arrow Key Pressed");
                    floodfill(cx,cy,14);
                    moveto(cx,cy);
                    a=getx(); b=gety();
                }
                else if(input==77) // right
                {   
                    if(cx<600)
                        cx+=100;
                    circle(cx,cy,5);
                    outtextxy(105,y-90,"RIGHT Arrow Key Pressed");
                    floodfill(cx,cy,14);
                    moveto(cx,cy);
                    a=getx(); b=gety();
                }
                else if(input==97 || input==65) // a or A
                {
                    l1=a; l2=b; a_pressed_flag=1;
                    // To show cursor after line completion
                    circle(cx,cy,5);
                    outtextxy(190,y-90,"A Key Pressed");
                    floodfill(cx,cy,14);
                }
                else if((input==115 || input==83) && a_pressed_flag==1) // s or S
                {
                    l3=a; l4=b;
                    if(((l1-l3==0 && l2-l4==100) || (l1-l3==0 && l2-l4==-100)) || ((l1-l3==100 && l2-l4==0) || (l1-l3==-100 && l2-l4==0)))
                    {
                        // checking if line is already drawn or not
                        for(int i=0;i<coords_count;i++)
                        {
                            if((l1==all_coords[i][0] && l2==all_coords[i][1] && l3==all_coords[i][2] && l4==all_coords[i][3]) || (l3==all_coords[i][0] && l4==all_coords[i][1] && l1==all_coords[i][2] && l2==all_coords[i][3]))
                            {
                                line_already_drawn_flag=1;
                                setcolor(12);
                                outtextxy(100,y-90,"Line already drawn there!");
                                setcolor(14);
                                break;
                            }
                        }
                        if(line_already_drawn_flag==0)
                        {
                            outtextxy(190,y-90,"S Key Pressed");
                            all_coords[coords_count][0]=l1;
                            all_coords[coords_count][1]=l2;
                            all_coords[coords_count][2]=l3;
                            all_coords[coords_count][3]=l4;
                            all_coords[coords_count][4]=player_turn;
                            edge_check(&l1,&l2,&l3,&l4);
                            box_check();
                            coords_count+=1;
                            player_turn_done=1;
                            lines--;
                        }
                        a_pressed_flag=0;
                        line_already_drawn_flag=0; // Resetting flag to 0
                        // To show cursor after line completition
                        circle(cx,cy,5);
                        floodfill(cx,cy,14);
                    }
                    else // if selected points are not ajacent
                    {
                        settextstyle(10,0,3);
                        setcolor(12);
                        outtextxy(160,y-100,"Selected Points must be");
                        outtextxy(85,y-75,"Horizontally or Vertically Adjacent");
                        settextstyle(10,0,4);
                        setcolor(14);
                        // To show cursor after error msg
                        circle(cx,cy,5);
                        floodfill(cx,cy,14);
                    }
                }
                else if((input==115 || input==83) && a_pressed_flag==0) // if S key was pressed without pressing A key first
                {
                    setcolor(12);
                    outtextxy(120,y-90,"Press the A Key First");
                    setcolor(14);
                    // To show cursor after pressing S alone without pressing A first
                    circle(cx,cy,5);
                    floodfill(cx,cy,14);
                }
                else // if invalid key was pressed
                {
                    // To show cursor after pressing invalid key
                    circle(cx,cy,5);
                    floodfill(cx,cy,14);
                    board_design();
                    setcolor(12);
                    outtextxy(120,y-90,"Invalid Key Pressed");
                }   

                // Lines
                for(i=0; i<coords_count; i++)
                {
                    if(all_coords[i][4]==0) // if line was created by player1
                    {
                        setcolor(10);
                        setlinestyle(0,0,3);
                        line(all_coords[i][0], all_coords[i][1], all_coords[i][2], all_coords[i][3]);
                    }
                    else if(all_coords[i][4]==1) // if line was created by player2
                    {
                        setcolor(13);
                        setlinestyle(0,0,3);
                        line(all_coords[i][0], all_coords[i][1], all_coords[i][2], all_coords[i][3]);            
                    }
                }
                if(call_to_box==1) // box was formed
                    box(); // to check who created the box i.e. player1 or player2
                box_print();
                call_to_box=0;
                if(player_turn_done==1 || lines==0) // break if player turn has to change or game ends
                {
                    board_design();
                    break;
                }
            }
            else
            {
                board_design();
                setcolor(12);
                outtextxy(110,y-105,"Please Press Enter Key");
                outtextxy(150,y-75,"to Start the game");
            }
        }       
    }
}
void recentgames(void)
{
    cleardevice();
    settextjustify(1,1);
    settextstyle(3,0,3);
    int i=0, j=0, color=9, flag=0, a=x/2, b=600, count=9; // count = 9 so that only last 9 non empty records are displayed
    int input=0;
    char c=0;
    char display[15][300]={{0}};
    fp = fopen("matches.dat", "rb");
    if(fp==NULL) 
    {
        printf("\n The file 'matches.dat' could not be opened");
        exit(1);
    }
    else
    {
        while((c = fgetc(fp)) != EOF)
        {
            if(c == ' ') // whenever whitespace is found flag gets incremented
                flag++;
            if(flag==17) // on 17th whitespace row of 2d array display gets changed
            {
                display[i][j]='\0';
                flag=0;
                i++;
                j=0;
            }
            else
            {
                display[i][j]=c;
                j++;
            }
        }
    }
    fclose(fp);
    setcolor(15);
    // to print last 9 records
    for(i=sizeof(display)/sizeof(display[0])-1; i>=0; i--)
    {
        if((display[i][0] != '\0') && count>0) // if string is not empty and count > 0
        {
            outtextxy(a,b,display[i]);
            b-=50;
            count--;   
        }
        else
            continue;
    }
    setcolor(15); 
    settextstyle(3,0,6);
    settextjustify(1,1);
    rectangle(40,40,x-40,y-40);
    rectangle(20,20,x-20,y-20);
    setcolor(13);
    //HEADING
    outtextxy(x/2,120,"Recent Matches");
    setlinestyle(2,0,2);
    line(x/2-200,135,x/2+200,135);
    settextstyle(8,0,5);
    setcolor(14);
    outtextxy(x/2,y-90,"Backspace - Main Menu");  
    setcolor(10);
    while(1) // Border Animation
    {
        if(color>14)
            color = 9;
        setfillstyle(SOLID_FILL,color);
        floodfill(25,25,15);
        color++;
        delay(500);
        if(kbhit())
        {
            input = getch();
            if(input==8)
            {
                cleardevice();
                main_menu();
            }
        }
    }
}
void win_screen(void)
{
    setlinestyle(0,0,2);
    int a,b,c,d,e,f,g,h,i,j,color=10;
    char player_won[50], input;
    if(p1.score>p2.score)
    {
        sprintf(player_won, "%s WON!", p1.name);
        strcpy(winner, p1.name);
    }
    else if(p1.score<p2.score)
    {
        sprintf(player_won, "%s WON!", p2.name);
        strcpy(winner, p2.name);
    }
    else if(p1.score==p2.score)
    {
        sprintf(player_won, "DRAW!");
        strcpy(winner, "DRAW");
    }
    
    // Storing details in file
    sprintf(details,"P1 : %s | P2 : %s | TIME PLAYED : %.2f mins | WINNER : %s", p1.name, p2.name, time_spent_min, winner);
    strcat(details," ");
    fp = fopen("matches.dat","ab");
    if(fp==NULL) 
    {
        printf("\n The file 'matches.dat' could not be opened");
        exit(1);
    }
    else
        fputs(details,fp);
    fclose(fp);
    
    while(1)
    {
        cleardevice();
        rectangle(30,30,x-30,y-30);
        if(color>14)
            color = 10;
        setfillstyle(SOLID_FILL,color);
        floodfill(55,55,15);
        settextstyle(10,0,9);
        setbkcolor(color);
        setcolor(9);
        settextjustify(1,1); // to centre align the text
        outtextxy(x/2, y/2, player_won);
        setcolor(15);
        settextstyle(10,0,5);
        outtextxy(x/2,y-80,"SPACEBAR - Main Menu | ESC - Exit"); 
        color++;
        delay(500);
        if(kbhit())
        {
            input = getch();
            if(input==32) // space
            {
                setbkcolor(0);
                main_menu();
                break;
            }
            if(input==27) // escape
            {
                exit(0);
                break;
            }
        }
    }
}
void player_system(void)
{
    setcurrentwindow(main_window);
    cleardevice();
    settextjustify(0,2);
    board_design();
    while(1)
    {
        if(kbhit())
            break;
    }
    // timer starts
    clock_t begin = clock();
    while(lines!=0) // to change player turn accordingly
    {
        if(player_turn==0)
        {
            game();
            player_turn_done=0;
            player_turn=1;
        }
        else
        {
            game();
            player_turn_done=0;
            player_turn=0;
        }
    }
    // timer ends
    clock_t end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    // converting time played into minutes from seconds
    time_spent_min = (double)time_spent / (double)60;
    win_screen();
}
void names_align(void)
{
    // Aligning the name of Player1
    if(strlen(p1.name)==10 || strlen(p1.name)>=10)
    {
        p1.name_align_x=695;
        p1.name_align_y=230;
    }
    else if(strlen(p1.name)==9)
    {
        p1.name_align_x=703;
        p1.name_align_y=230;
    }
    else if(strlen(p1.name)==8)
    {
        p1.name_align_x=710;
        p1.name_align_y=230;
    }
    else if(strlen(p1.name)==7)
    {
        p1.name_align_x=720;
        p1.name_align_y=230;
    }
    else if(strlen(p1.name)==6)
    {
        p1.name_align_x=725;
        p1.name_align_y=230;
    }
    else if(strlen(p1.name)==5)
    {
        p1.name_align_x=735;
        p1.name_align_y=230;
    }
    else if(strlen(p1.name)==4)
    {
        p1.name_align_x=743;
        p1.name_align_y=230;
    }
    else if(strlen(p1.name)==3)
    {
        p1.name_align_x=755;
        p1.name_align_y=230;
    }
    else if(strlen(p1.name)==2)
    {
        p1.name_align_x=765;
        p1.name_align_y=230;
    }
    else if(strlen(p1.name)==1)
    {
        p1.name_align_x=775;
        p1.name_align_y=230;
    }

    // Aligning the name of Player2
    if(strlen(p2.name)==10 || strlen(p2.name)>=10)
    {
        p2.name_align_x=695;
        p2.name_align_y=270;
    }
    else if(strlen(p2.name)==9)
    {
        p2.name_align_x=703;
        p2.name_align_y=270;
    }
    else if(strlen(p2.name)==8)
    {
        p2.name_align_x=710;
        p2.name_align_y=270;
    }
    else if(strlen(p2.name)==7)
    {
        p2.name_align_x=720;
        p2.name_align_y=270;
    }
    else if(strlen(p2.name)==6)
    {
        p2.name_align_x=725;
        p2.name_align_y=270;
    }
    else if(strlen(p2.name)==5)
    {
        p2.name_align_x=735;
        p2.name_align_y=270;
    }
    else if(strlen(p2.name)==4)
    {
        p2.name_align_x=743;
        p2.name_align_y=270;
    }
    else if(strlen(p2.name)==3)
    {
        p2.name_align_x=755;
        p2.name_align_y=270;
    }
    else if(strlen(p2.name)==2)
    {
        p2.name_align_x=765;
        p2.name_align_y=270;
    }
    else if(strlen(p2.name)==1)
    {
        p2.name_align_x=775;
        p2.name_align_y=270;
    }    
}
void enternames(void)
{
    int i=0;
    char name1[50], name2[50], dots[]="...", flag=1;
    initwindow(415,100,"ALERT",530,350);
    setcolor(12);
    rectangle(5,5,410,95);
    setcolor(15);
    settextstyle(3,0,3);
    outtextxy(25,25,"Please enter names of Player1 & Player2");
    outtextxy(25,50,"in the terminal window.");
    printf("***(No Numbers & Special Characters Allowed)***");
    // Player 1
    printf("\n\nEnter Name of Player1 : ");
    scanf("%s", name1);
    // checking if there is any special character/number in the name1
    while(flag==1)
    {
        for (i=0; i<strlen(name1); ++i)
        {
            // checking each character of the name1 for special character
            if(isalpha(name1[i])==0)
            {
                printf("Special Characters & Numbers are not allowed, Please re-enter name1 : ");
                flag=1;
                break;
            }
            else
                flag=0;
        }
        fflush(stdin);
        if(flag==1)
            scanf("%[^\n]s", name1);
        else if(flag==0)
        {
            strcpy(p1.name, name1);
            break;
        }     
    }
    flag=1;
    fflush(stdin);
    
    // Player 2
    printf("\nEnter Name of Player2 : ");
    scanf("%s", name2);
    fflush(stdin);
    // checking if there is any special character/number in the name1
    while(flag==1)
    {
        for (i=0; i<strlen(name2); ++i)
        {
            // checking each character of the name2 for special character
            if(isalpha(name2[i])==0)
            {
                printf("Special Characters & Numbers are not allowed, Please re-enter name2 : ");
                flag=1;
                break;
            }
            else
                flag=0;
        }
        fflush(stdin);
        if(flag==1)
            scanf("%[^\n]s", name2);
        else if(flag==0)
        {
            strcpy(p2.name, name2);
            break;
        }     
    }
    
    // if entered names are not equal & greater than 10 in length
    if(strcmp(p1.name, p2.name)!=0 && strlen(p1.name)>10)
    {
        p1.name[strlen(p1.name) - (strlen(p1.name) - 7)]  = '\0';
        strncat(p1.name, dots, 3);
    }
    if(strcmp(p1.name, p2.name)!=0 && strlen(p2.name)>10) 
    {
        p2.name[strlen(p2.name) - (strlen(p2.name) - 7)]  = '\0';
        strncat(p2.name, dots, 3);
    }
    // if entered names are same & both are greater than 10 in length
    if(strcmp(p1.name, p2.name)==0 && strlen(p1.name)>10 && strlen(p2.name)>10)
    {
        p1.name[strlen(p1.name) - (strlen(p1.name) - 6)]  = '\0';
        strncat(p1.name, dots, 2);
        strncat(p1.name, "1", 1);

        p2.name[strlen(p2.name) - (strlen(p2.name) - 6)]  = '\0';
        strncat(p2.name, dots, 2);
        strncat(p2.name, "2", 1);
    }
    // if entered names are same & both are less than 10 in length
    else if(strcmp(p1.name, p2.name)==0 && strlen(p1.name)<10 && strlen(p2.name)<10)
    {
        strncat(p1.name, "1", 1);
        strncat(p2.name, "2", 1);
    }
    // if entered names are same & both are equal to 10 in length
    else if(strcmp(p1.name, p2.name)==0 && strlen(p1.name)==10 && strlen(p2.name)==10)
    {
        p1.name[strlen(p1.name) - 1]  = '\0';
        strncat(p1.name, "1", 1);

        p2.name[strlen(p2.name) - 1]  = '\0';
        strncat(p2.name, "2", 1);
    }
    // to align the names on the screen
    names_align();
    printf("\nYou can proceed to the Main Window...");
    closegraph(CURRENT_WINDOW);
    player_system();
}
void credits(void)
{
    int i,j,l,n, input;
    setlinestyle(0,0,1);
	cleardevice();
    // design
	for(i=768,j=0,l=1024,n=0;i>=0;i-=8,j+=10,l-=10,n+=8)
    {
        setcolor(13);
        line(0,i,j,0);
        delay(12);
        setcolor(11);
        line(1024,n,l,768);
        delay(12);
    }
    settextstyle(10,0,4);
    setcolor(14);
    settextjustify(1,1);
    outtextxy(x/2+50,300,"My Sincere thanks to Project Guide"); delay(300);
    outtextxy(x/2,340,"Ms.M.Syamala Devi"); delay(300);
    outtextxy(x/2,380,"for this opportunity."); delay(300);
    outtextxy(x/2,420,"Special thanks to My"); delay(300);
    outtextxy(x/2,460,"Parents"); delay(300);
    outtextxy(x/2,500,"&"); delay(300);
    outtextxy(x/2,540,"Friends"); delay(300);
    outtextxy(x/2,580,"Presented by"); delay(300);
    outtextxy(x/2,620,"Akshit"); delay(300);
    while(1)
    {
        if(kbhit())
        {
            input = getch();
            if(input==8) // backspace 
            {
                cleardevice();
                main_menu();
                break;
            }
        }
    }
}
void controls(void)
{
    cleardevice();
    settextjustify(1,1);
    setlinestyle(0,0,1);
    int i,j,color=9;
    int input=0;
    //BORDER
    setcolor(15);
    settextstyle(8,0,6);
    rectangle(40,40,x-40,y-40);
    rectangle(20,20,x-20,y-20);
    //HEADING
    setcolor(13);
    setlinestyle(2,0,2);
    outtextxy(x/2,160,"Controls");
    rectangle(x/2-150,110,x/2+150,180);
    //CONTROLS
    setcolor(11);
    settextstyle(10,0,4);
    outtextxy(x/2-18,300,"- Press ENTER key to START the game.");
    outtextxy(x/2,350,"- Use UP, DOWN, LEFT & RIGHT arrow key");
    outtextxy(x/2-230,400,"  to Navigate.");
    outtextxy(x/2-38,450,"- Use A key to lock the 1st Point.");
    outtextxy(x/2-38,500,"- Use S key to lock the 2nd Point.");
    setcolor(14);
    settextstyle(8,0,5);
    outtextxy(x/2,y-120,"BACKSPACE - Main Menu");
    setcolor(10);
    while(1) // Border Animation
    {
        if(color>14)
            color = 9;
        setfillstyle(SOLID_FILL,color);
        floodfill(25,25,15);
        color++;
        delay(500);
        if(kbhit())
        {
            input = getch();
            if(input==8)
            {
                cleardevice();
                main_menu();
                break;
            }
        }
    }
}
void main_menu(void)
{
    cleardevice();
    setbkcolor(0);
    setlinestyle(0,0,2);
    int i,j,color=9,a,b;
    int input=0;
    int pressed=0;
    int cx=x/2-150,cy=270;
    while(1) // Border Animation
    {
        setbkcolor(0);
        setcolor(15);
        settextstyle(3,0,6);
        rectangle(40,40,x-40,y-40);
        rectangle(20,20,x-20,y-20);
        setcolor(13);
        //HEADING
        settextjustify(1,1);
        outtextxy(x/2,153,"MAIN MENU");
        setlinestyle(2,0,2);
        rectangle(x/2-170,100,x/2+170,170);
        // Options
        setlinestyle(0,0,2);
        setcolor(11);
        settextstyle(10,0,5);
        outtextxy(x/2,270,"New Game");
        outtextxy(x/2,340,"Controls");
        outtextxy(x/2,410,"Recently Played Matches");
        outtextxy(x/2,480,"Acknowledgement");
        outtextxy(x/2,550,"EXIT");
        setcolor(10);
        if(color>14)
            color = 9;
        setfillstyle(SOLID_FILL,color);
        floodfill(25,25,15);
        color++;
        delay(100);
        if(pressed==0)
        {
            outtextxy(cx,cy,">"); // 361 270
            moveto(cx,cy);
            a=getx();   b=gety();
        }
        if(kbhit())
        {
            pressed=1;
            input = getch();
            if(input == 80 && cy<550) //down
            {
                cleardevice();
                if(cx==361 && cy==270) 
                {
                    cx+=10;
                    cy+=70;
                    outtextxy(cx,cy, ">"); // 371 340 //controls
                    moveto(cx,cy);
                    a=getx();   b=gety();
                }
                else if(cx==371 && cy==340) 
                {
                    cx-=190;
                    cy+=70;
                    outtextxy(cx,cy,">"); // 181 410 //recently
                    moveto(cx,cy);
                    a=getx();   b=gety();
                }
                else if(cx==181 && cy==410) 
                {
                    cx+=100; //240
                    cy+=70;
                    outtextxy(cx,cy,">"); // 281 480 //acknowledgement
                    moveto(cx,cy);
                    a=getx();   b=gety();
                }
                else if(cx==281 && cy==480) 
                {
                    cx+=140; 
                    cy+=70;
                    outtextxy(cx,cy,">"); // 421 550 //exit
                    moveto(cx,cy);
                    a=getx();   b=gety();
                }
            }
            else if(input == 80 && cy==550)
                outtextxy(x/2,y-100,"You cannot go DOWN any further!");
            else if(input==72 && cy>270) // up
            {
                cleardevice();
                if(cx==371 && cy==340)  // controls
                {
                    cx-=10;
                    cy-=70;
                    outtextxy(cx,cy,">"); // 201 410
                    moveto(cx,cy);
                    a=getx();   b=gety();
                }
                else if(cx==181 && cy==410) // recently
                {
                    cx+=190;
                    cy-=70;
                    outtextxy(cx,cy,">"); // 421 480
                    moveto(cx,cy);
                    a=getx();   b=gety();
                }
                else if(cx==281 && cy==480) // acknowledgement
                {
                    cx-=100;
                    cy-=70;
                    outtextxy(cx,cy,">"); // 391 480
                    moveto(cx,cy);
                    a=getx();   b=gety();
                }
                else if(cx==421 && cy==550) // exit
                {
                    cx-=140; 
                    cy-=70;
                    outtextxy(cx,cy,">"); // 421 550
                    moveto(cx,cy);
                    a=getx();   b=gety();
                }
            }
            else if(input == 72 && cy==270)
                outtextxy(x/2,y-100,"You cannot go UP any further!");
            else if(input==13) // enter
            {
                if(a==361 && b==270)
                {
                    enternames();
                    break;
                }
                else if(a==371 && b==340)
                {
                    controls();
                    break;
                }
                else if(a==181 && b==410)
                {
                    recentgames();
                    break;
                }
                else if(a==281 && b==480)
                {
                    credits();
                    break;
                }
                else if(a==421 && b==550)
                {
                    exit(0);
                }
            }
            /*else if(input!=80 || input!=72 || input!=13)
            {
                outtextxy(cx,cy,">");
                outtextxy(x/2,y-100,"Invalid Key Pressed");
            }*/    
            
        }
    }
}
void introduction(void) // about the game
{
    cleardevice();
    int i,j,color=9;
    int input=0;
    setcolor(15);
    settextstyle(3,0,6);
    rectangle(40,40,x-40,y-40);
    rectangle(20,20,x-20,y-20);
    setcolor(13);
    //HEADING
    settextjustify(1,1);
    outtextxy(x/2,140,"About the Game");
    setlinestyle(2,0,2);
    line(x/2-210,160,x/2+210,160);
    //RULES
    setcolor(11);
    settextstyle(10,0,4);
    outtextxy(x/2,270,"> Each player takes turn drawing one line.");
    outtextxy(x/2-40,310,"> If that line completes a square, the");
    outtextxy(x/2-20,350,"  player writes their initial in the box");
    outtextxy(x/2-165,390,"  and draws another line.");
    outtextxy(x/2-5,430,"> Game continues until all dots have been");
    outtextxy(x/2-290,470,"  connected.");
    outtextxy(x/2-80,510,"> The player with most boxes WINS!");
    //NEXT SCREEN
    setcolor(14);
    settextstyle(10,0,5);
    outtextxy(x/2,640,"Press SPACEBAR to continue");    
    setcolor(10);
    while(1) // Border Animation
    {
        if(color>14)
            color = 9;
        setfillstyle(SOLID_FILL,color);
        floodfill(25,25,15);
        color++;
        delay(500);
        if(kbhit())
        {
            input = getch();
            if(input==32)
            {
                main_menu();
                break;
            }
        }
    }
}
void loading(void)
{
    int n;
    int bar = x/2-300;
    settextstyle(3,0,6);
    rectangle(5,5,x-5,y-5); // Loading Screen Border
    outtextxy(x/2-110,y/2-100,"Loading...");
    rectangle(x/2-300,y/2-20,x/2+300,y/2+30); // Loading Bar
    delay(1000);
    while(bar!=x/2+301)
    {   
        rectangle(x/2-300,y/2-20,bar,y/2+30);
        if(bar==x/2-180 || bar==x/2+70 || bar==x/2+260)
            delay(1000);
        bar++;
    }
    delay(500);
    introduction();
}
int main()
{
    main_window = initwindow(1024,768,"Dots & Boxes Game",230,30);
    // initializing score 
    p1.score=0; p2.score=0;
    loading();
    getch();
    closegraph();
    return 0;
}