
//  main.cpp
//  Snake Game
//  Created by Aryan Agarwal on 24/08/18.
//  Copyright © 2018 Aryan. All rights reserved.

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<conio.h>

#define max_row 15
#define max_col 30

void delay(float number_of_seconds) {
    int milli_seconds = 1000 * number_of_seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds);
}

struct food {
    int r;
    int c;
    char value;
};
struct poision {
    int r;
    int c;
    char value;
};
struct snake {
    int r;
    int c;
    char value;
    struct snake *next;
};

void addFood(struct food **head) {
    struct food *temp=(struct food *)malloc(sizeof(struct food *));

    temp->r=(rand() % (max_row - 2 )) + 1;
    temp->c=(rand() % (max_col - 2 )) + 1;
    temp->value = 'F';
    
    *head = temp;
}

void addPoision(struct poision **head) {
    struct poision *temp=(struct poision *)malloc(sizeof(struct poision *));

    temp->r=(rand() % (max_row - 2 )) + 1;
    temp->c=(rand() % (max_col - 2 )) + 1;
    temp->value = 'P';
    
    *head = temp;
}

void addSnake(struct snake **head,int rr,int cc,char value) {
    struct snake *temp=(struct snake *)malloc(sizeof(struct snake));
    struct snake *tem=*head;
    srand(time(0));
    temp->r=rr;
    temp->c=cc;
    temp->next=NULL;
    temp->value = value;
    
    if(*head==NULL) {
        *head=temp;
    }
    else {
        while(tem->next!=NULL)
        {
            tem=tem->next;
        }
        tem->next = temp;
    }
}


char checkSnake(struct snake *head, int i, int j) {
    while(head!=NULL) {
        if(head->r==i && head->c==j)
            return head->value;
        head = head->next;
    }
    return 0;
}

char checkFood(struct food *head,int i,int j) {
    if(head->r == i && head->c == j)
        return head->value;
    return 0;
}

char checkPoision(struct poision *head, int i, int j) {
    if(head->r==i && head->c==j)
        return head->value;
    return 0;
}

void move(struct snake **head, char c) {
    
    struct snake* temp = *head;
    
    int r1, c1, r2, c2;
    
    r1 = temp->r;
    c1 = temp->c;
    
    switch (c) {
            
    case 't' :
        printf("Top\n");
        temp->r = r1 - 1;
        break;
            
    case 'b' :
        printf("Bottom\n");
        temp->r = r1 + 1;
        break;
            
    case 'r' :
        printf("Right\n");
        temp->c = c1+ 1;
        break;
            
    case 'l' :
        printf("Left\n");
        temp->c = c1 - 1;
        break;
            
    }
    
    temp = temp->next;
    while(temp != NULL)
    {
        r2 = temp->r;
        c2 = temp->c;
        
        temp->r = r1;
        temp->c = c1;
        
        r1 = r2;
        c1 = c2;
        
        temp = temp->next;
    }
    
}

void updateAndShow(char mat[max_row][max_col],struct snake *head,struct food *f,struct poision *p) {
    for(int i=0;i<max_row;i++)
    {
        for(int j=0;j<max_col;j++)
        {
            char x = checkSnake(head,i,j);
            char fo = checkFood(f,i,j);
            char po = checkPoision(p,i,j);
            if(i==0||i==(max_row-1)||j==0||j==(max_col-1))
            {
                mat[i][j]='#';
            }
            else if(x == 'O' || x == '0')
            {
                mat[i][j]=x;
            }
            else if( fo == 'F' )
            {
                mat[i][j]=fo;
            }
            else if( po == 'P' )
            {
                mat[i][j]=po;
            }
            else
                mat[i][j]=' ';
        }
    }
    for(int i=0;i<max_row;i++)
    {
        for(int j=0;j<max_col;j++)
        {
            printf("%c",mat[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, const char * argv[]) {
    
    struct snake *head=NULL;
    struct food *f = NULL;
    struct poision *p = NULL;
    srand(time(0));
    addFood(&f);
    addPoision(&p);
    
    addSnake(&head,10,7,'0');
    for(int i=1; i<4;i++) {
        addSnake(&head,10-i,7,'O');
    }
    
    char mat[max_row][max_col];
    
    updateAndShow(mat,head,f,p);
    
    int direction = 0; // 0 for vertical & 1 for horizontal
    
    char input;
    
    while ((input = getch()) != 'q') {
        
        switch (input) {
            case 'w':
            case 'W':
                if(direction==1) {
                    move(&head, 't');
                    delay(3);
                    direction=0;
                    updateAndShow(mat,head,f,p);
                }
                break;
                
            case 'd':
            case 'D':
                if(direction==0) {
                    move(&head, 'r');
                    delay(3);
                    direction=1;
                    updateAndShow(mat,head,f,p);
                }
                break;
                
            case 's':
            case 'S':
                if(direction==1) {
                    move(&head, 'b');
                    delay(3);
                    direction=0;
                    updateAndShow(mat,head,f,p);
                }
                break;
                
            case 'a':
            case 'A':
                if(direction==0) {
                    move(&head, 'l');
                    delay(3);
                    direction=1;
                    updateAndShow(mat,head,f,p);
                }
                break;
        }
    }

    return 0;
}

