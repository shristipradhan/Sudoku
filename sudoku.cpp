/* 
 This program generates a 9x9 solved Sudoku grid.
 Each column, each row, and each of 3x3 sub-grids contain all of the digits from 1 to 9.
 
 Created by Shristi Pradhan on 2012-04-11.
 Credits: Presha Joshi, Priyanka Shrestha
 Copyright (c) 2012 Shristi Pradhan. All rights reserved.
 */

#include<iostream>
#include<stdlib.h>
using namespace std;

class answer
{
public:
    answer(){}
    ~answer(){}
    int a, b, c, d, p, pos;
    int x[3][3][3][3][10];
    int i, j;
    int ans1[9][9];
    void move();
    void generate();
    void backtrack();
    void regenerate();
    void destroy();
    void antidestroy();
    void final();
    void opt();
    void display();
    void copy();
    void prob();
};

// To fill probability in each square
void answer::prob()
{
	for(a = 0; a < 3; a++)
	{
		for(c = 0; c < 3; c++)
            
		{
			for(b = 0; b < 3; b++)
			{
				for(d = 0; d < 3; d++)
				{
                    for(p = 0;p < 10; p++)
                    
                        x[a][b][c][d][p] = p;
                    
				}
			}
            
		}
	}
    
	random();
}

void answer::final()
{
	prob();
	int count = 0;
	a = b = c = d = 0;
	random();
	while(a < 3)
	{
		count++;
		p = (rand() % 9) + 1;
		opt();
		destroy();
		move();
	}
}

// Check for options
void answer::opt()
{
    int flag = 0;
    int no;
	if (x[a][b][c][d][p] > 0)
    {
        x[a][b][c][d][0] = p;
    }
	else
	{
		for(no = 1; no < 10; no++)
		{
			if(x[a][b][c][d][no] > 0)
            {
                flag=1;
                break;
            }
            
		}
		if(flag == 1)
		{
			p = (rand() % 9) + 1;
            while(x[a][b][c][d][p]!=p)
            {
                p = (rand() % 9) + 1;
            }
			opt();
		}
		if(flag == 0)
		{
			backtrack();
		}
        
	}
}

void answer::destroy()
{
    int m,n,r,s,u,v;
    int t = p;
    u = c;
    v = d+1;
    for(; u < 3; u++)
	{
		for(; v < 3; v++)
            
        {
            if(x[a][b][u][v][t] > 0)
                x[a][b][u][v][t] = 0;
            else
                
                x[a][b][u][v][p]--;
            
        }
        
        if(v > 2)
            v=0;
        
	}
    
    for(m = b+1; m < 3; m++)                  // Eliminates prob in whole row
    {
		for(n = 0; n < 3; n++)
		{
            if(x[a][m][c][n][p] > 0)
				x[a][m][c][n][p] = 0;
            else
				x[a][m][c][n][p]--;
            
		}
    }
    
    for(r = a+1; r < 3; r++)			 // Eliminates prob in whole column
    {
        for(s = 0; s < 3; s++)
        {
            if(x[r][b][s][d][p] > 0)
                x[r][b][s][d][p] = 0;
            else
                x[r][b][s][d][p]--;
            
        }
    }
}

void answer::move()
{
	d++;
    
    if(d > 2)
    {
        b++;
        d = 0;
    }
    
    if(b > 2)
    {
        c++;
        b = 0;
        d = 0;
    }
    
    if(c > 2)
    {
        a++;
        b = 0;
        d = 0;
        c = 0;
    }
}

void answer::backtrack()
{
    int flag1 = 0;
	d--;
    
    if(d < 0)
    {
        b--;
        d = 2;
    }
    
    if(b < 0)
    {
        c--;
        b = 2;
        d = 2;
    }
    
    if(c < 0)
    {
        a--;
        b = 2;
        d = 2;
        c = 2;
    }
    
    pos = x[a][b][c][d][0];
    antidestroy();
    x[a][b][c][d][pos] = -10;
up:
	pos = (rand() % 9) + 1;
	if(x[a][b][c][d][pos] > 0)
	{
		p = pos;
		opt();
	}
	else
	{
		for(p = 1; p < 10; p++)
		{
            
			if(x[a][b][c][d][p] > 0)
			{
				flag1 = 1;
				break;
			}
        }
        if(flag1 == 1)
        {
			goto up;
        }
        
        if(flag1 == 0)
        {
			regenerate();
			backtrack();
        }
    }
}

//reassign the corresponding probability
void answer::regenerate()
{
	for(p = 1; p < 10; p++)
	{
		if(x[a][b][c][d][p] == -10)
		{
			x[a][b][c][d][p] = p;
		}
	}
}

void answer::antidestroy()
{
    int m,n,r,s,u,v;
    int row = a;
    int col = b;
    u = c;
    v = d+1;
    for(; u < 3; u++)
	{
		for(; v < 3; v++)
            
        {
            if(x[row][col][u][v][pos] == 0)
                x[row][col][u][v][pos] = pos;
            else
                
                x[a][b][u][v][pos]++;
        }
        
        if(v > 2)
            v = 0;
        
	}
    
    for(m = b+1; m < 3; m++)                  // Eliminates prob in whole row
    {
		for(n = 0; n < 3; n++)
		{
            if(x[a][m][c][n][pos] == 0)
				x[a][m][c][n][pos] = pos;
            else
				x[a][m][c][n][pos]++;
            
		}
    }
    
    
    for(r = a+1; r < 3; r++)			 // Eliminates prob in whole column
    {
        for(s = 0; s < 3; s++)
        {
            if(x[r][b][s][d][pos] == 0)
                x[r][b][s][d][pos] = pos;
            else
                x[r][b][s][d][pos]++;
            
            
        }
    }
    
}

void answer::copy()
{
	i = 0;
	j = 0; a = 0; b = 0 ; c = 0; d = 0;
	{
		for(i = 0; i < 9; i++)
		{
			for(j = 0; j < 9; j++)
			{
				ans1[i][j] = x[a][b][c][d][0];
				move();
			}
		}
	}
}

// Print the 9x9 grid
void answer::display()
{
    for(i = 0; i < 9; i++)
    {
        for(j = 0; j < 9; j++)
        {
            cout << ans1[i][j];
        }
        cout << endl;
    }
    
}

int main()
{
	answer a1;
	a1.final();
	a1.copy();
	a1.display();
    return 0;
}
