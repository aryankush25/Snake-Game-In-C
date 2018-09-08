//
//  main.cpp
//  Snake Game
//
//  Created by Aryan Agarwal on 24/08/18.
//  Copyright © 2018 Aryan. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include <time.h>

#define max_row 15
#define max_col 30

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
    
    temp->r=(rand() % (max_row - 0 + 1)) + 0;
    temp->c=(rand() % (max_col - 0 + 1)) + 0;
    temp->value = 'F';
    
    *head = temp;
}

void addPoision(struct poision **head) {
    struct poision *temp=(struct poision *)malloc(sizeof(struct poision *));
    srand(time(0));
    temp->r=(rand() % (max_row - 0 + 1)) + 0;
    temp->c=(rand() % (max_col - 0 + 1)) + 0;
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


char checkNode(struct snake *head,int i,int j) {
    while(head!=NULL) {
        if(head->r==i && head->c==j)
            return head->value;
        head=head->next;
    }
    return 0;
}

int main(int argc, const char * argv[]) {
    
    struct snake *head=NULL;
    struct food *f = NULL;
    struct poision *p = NULL;
    
    addFood(&f);
    addPoision(&p);
    
    addSnake(&head,10,7,'o');
    for(int i=1; i<5;i++)
    {
        addSnake(&head,10-i,7,'*');
    }
    
    int i,j;
    char mat[max_row][max_col];
    
    for(i=0;i<max_row;i++)
    {
        for(j=0;j<max_col;j++)
        {
            char x = checkNode(head,i,j);
            if(i==0||i==(max_row-1)||j==0||j==(max_col-1))
            {
                mat[i][j]='#';
            }
            else if(x == '*' || x == 'o')
            {
                mat[i][j]=x;
            }
            else
                mat[i][j]=' ';
        }
    }
    for(i=0;i<max_row;i++)
    {
        for(j=0;j<max_col;j++)
        {
            printf("%c",mat[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}

