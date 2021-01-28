#include <iostream>
#include <string>
#include <time.h>
#include <conio.h>
#include<fstream>
#include<vector>
#include <iomanip>
#include"stack.h"
#include"stack.cpp"
#include "randgen.h"
//NAZLI IREM CAMURLU 27064 17.07.2020
//ALL RIGHTS RESERVED
using namespace std;
int rows,columns;//put columns and rows as global variable to ease out access for functions
bool generated = false;//boolean to make sure the stack won't delete the data when it's work is done
bool generated_ = false;//second boolean for the second stack to make sure the stack won't delete the data when it's work is done as topandpop() function is used


int entrx,entry,endx,endy;//global variable to ease out access for functions entry points and end points
struct Node {
	Node(int x_co, int y_co) : x_coordinate(x_co) ,y_coordinate(y_co)//struct node to store the cell data for every cell.
	{
		cell_visited =false;
		right_wall  = 1;//all the walls are set to 1 as the walls will be broken down later.
		left_wall = 1;
		up_wall = 1;
		down_wall = 1;
		player_visited = false;//booleans are set to false in the starting point and changed later to positive if visited different for maze generation and solving of the maze
		

	}
	int x_coordinate;
	int y_coordinate;
	bool cell_visited ;//for cells that are visited when generating the maze to not go back again.
	bool player_visited;//for cells that are visited when solving the to not go back again.
	int right_wall ;
	int left_wall ;
	int up_wall;
	int down_wall;
};
void new_mat(vector<vector<Node>> &mat)//generating the matrix as pushing the default node information to all the cells of the matrix.
{       
		vector<Node> temp_node;
		for(int i = 0; i<columns ; i++)
		 {
        for (int j =0; j<rows; j++) {
            Node temp(i,j);
			temp_node.push_back(temp);
        }
        mat.push_back(temp_node);
    
			}

}
void assign_coordinate(vector<vector<Node>> mat)//assigning the coordinates as it is not put in the default construction and it has to be set.
{
	for (int x=0;x<columns;x++)
	{
    for(int y=0;y<rows;y++)
    {

        mat[x][y].x_coordinate=x;
        mat[x][y].y_coordinate=y;

    }
	}
}
bool not_all_visited(vector<vector<Node>> mat)//checking if all the cells are visited when generating the maze.
{
	for (int x=0;x<columns;x++)
	{
    for(int y=0;y<rows;y++)
    {
		if(mat[x][y].cell_visited==false)
		return true;

    }

	
	}
	return false;
}

void put_wall(Stack<Node>&info,vector<vector<Node>>&mat,Node&current_cell)
{
	    int count = 0;
        RandGen rand_num_generator;//random number generator to make sure every maze generated is unique.

		
        int randnum = rand_num_generator.RandInt(0,3);
        int x = current_cell.x_coordinate;//first setting x and y to current coordinate which will always be updated.
        int y=current_cell.y_coordinate;
		bool left_dir=false;
		bool right_dir=false;
		bool up_dir=false;
		bool down_dir = false;
		if(x!=0)//if conditions to update and check whether we can move to certain directions while generating the function 
		left_dir=mat[x-1][y].cell_visited;
		if(x!=(columns-1))
		right_dir=mat[x+1][y].cell_visited;
		if(y!=(rows-1))
		up_dir=mat[x][y+1].cell_visited;
		if(y!=0)
		down_dir=mat[x][y-1].cell_visited;
		if(((left_dir == false)&&(x!=0))||((up_dir == false)&&(y!=(rows-1)))||((right_dir==false)&&(x!=(columns-1)))||((down_dir == false)&&(y!=0)))//again putting in condition as sometimes there can be situations where we can be on the edges of the matrix and this condition makes sure we are still not stuck.
		{
		if((generated&&randnum==0)||(generated&&randnum==1)||(generated&&randnum==2)||(generated&&randnum==3))//this condition only appylys when we are done with generating the maze and we want to make sure we pushed the last data that we popped from the top of the stack.
		{
			info.push(current_cell);
			generated = false;
		}

		if((randnum==1)&&(left_dir==false)&&(generated==false))//left
		{
			if(x!=0)
			{
				
				
				current_cell=mat[x-1][y];//updating the current cell's and matrix cells' info to make sure evrything is updated.
				current_cell.x_coordinate=x-1;
				current_cell.y_coordinate=y;
				current_cell.cell_visited=true;
				mat[x-1][y]=current_cell;
				mat[x-1][y].cell_visited=true;
				mat[x-1][y].x_coordinate=x;
				mat[x-1][y].y_coordinate=y;
				mat[x-1][y].right_wall=0;
				mat[x][y].left_wall=0;
				info.push(current_cell);
				
				
				

			}
			


		}
		if ((randnum==2)&&(up_dir == false)&&(generated==false))//up
		{
			if(y!=(rows-1))
			{
				
					
					current_cell=mat[x][y+1];//updating the current cell's and matrix cells' info to make sure evrything is updated.
					current_cell.x_coordinate=x;
					current_cell.y_coordinate=y+1;
					current_cell.cell_visited=true;
					mat[x][y+1].cell_visited=true;
					mat[x][y+1].x_coordinate=x;
					mat[x][y+1].y_coordinate=y;
					mat[x][y+1].down_wall=0;
					mat[x][y].up_wall=0;
					info.push(current_cell);
					
				
				


			}
			


		}
		if ((randnum==0)&&(right_dir==false)&&(generated==false))//right
		{
			if(x!=(columns-1))
			{
				
					
					current_cell=mat[x+1][y];//updating the current cell's and matrix cells' info to make sure evrything is updated.
					current_cell.x_coordinate=x+1;
					current_cell.y_coordinate=y;
					current_cell.cell_visited=true;
					mat[x+1][y]=current_cell;
					mat[x+1][y].cell_visited=true;
					mat[x+1][y].x_coordinate=x;
					mat[x+1][y].y_coordinate=y;
					mat[x+1][y].left_wall=0;
					mat[x][y].right_wall=0;
					info.push(current_cell);
					
				
			


			}
			
		}
		if ((randnum == 3)&&(down_dir==false)&&(generated==false))//down
		{
			if(y!=0)
			{
				
					
					current_cell=mat[x][y-1];//updating the current cell's and matrix cells' info to make sure evrything is updated.
					current_cell.x_coordinate=x;
					current_cell.y_coordinate=y-1;
					current_cell.cell_visited=true;
					mat[x][y-1]=current_cell;
					mat[x][y-1].cell_visited=true;
					mat[x][y-1].x_coordinate=x;
					mat[x][y-1].y_coordinate=y;
					mat[x][y-1].up_wall=0;
					mat[x][y].down_wall=0;
					
					info.push(current_cell);
					
				
				

			}
			

		}


		}
		else
		{	
			
			current_cell = info.topAndPop();
			generated=true;
			bool down_dir=false;
			bool right_dir=false;
			bool left_dir=false;
			bool up_dir=false;
		}
}
void solve_maze(vector<vector<Node>> selected_maze,int entry_x,int entry_y,int end_x,int end_y,Node&curr_cell,Stack<Node>&info2)
{
		

		while((curr_cell.x_coordinate == end_x && curr_cell.y_coordinate == end_y)==false)
		{

		int count = 0;
        RandGen rand_num_generator;//again random number generator to find a unique path in the maz every time.

		
        int randnum = rand_num_generator.RandInt(0,3);
		int x = curr_cell.x_coordinate;
        int y =curr_cell.y_coordinate;
		bool left_dire=false;
		bool right_dire=false;
		bool up_dire=false;
		bool down_dire = false;
		if(x!=0)//if conditions to update and check whether we can move to certain directions while generating the function 
		left_dire=selected_maze[x-1][y].player_visited;
		if(x!=(columns-1))
		right_dire=selected_maze[x+1][y].player_visited;
		if(y!=(rows-1))
		up_dire=selected_maze[x][y+1].player_visited;
		if(y!=0)
		down_dire=selected_maze[x][y-1].player_visited;
		if((curr_cell.x_coordinate>end_x)&&(left_dire==false)&&(selected_maze[x][y].left_wall==0))//condition to increase performance and see if the current x coordinate is bigger than end coordinate than ve can reassign randnum accordingly.
		{
			randnum=2;
		}
		if((curr_cell.x_coordinate<end_x)&&(right_dire==false)&&(selected_maze[x][y].right_wall==0))//condition to increase performance and see if the current x coordinate is smaller than end coordinate than ve can reassign randnum accordingly.
		{
			randnum=0;
		}
		if((curr_cell.y_coordinate>end_y)&&(down_dire==false)&&(selected_maze[x][y].down_wall==0))//condition to increase performance and see if the current y coordinate is bigger than end coordinate than ve can reassign randnum accordingly.
		{
			randnum=3;
		}
		if((curr_cell.y_coordinate<end_y)&&(up_dire==false)&&(selected_maze[x][y].up_wall==0))//condition to increase performance and see if the current y coordinate is smaller than end coordinate than ve can reassign randnum accordingly.
		{
			randnum=1;
		}

		if(((left_dire == false)&&(x!=0)&&(selected_maze[x][y].left_wall==0))||((up_dire == false)&&(y!=(rows-1))&&(selected_maze[x][y].up_wall==0))||((right_dire==false)&&(x!=(columns-1))&&(selected_maze[x][y].right_wall==0))||((down_dire == false)&&(y!=0)&&(selected_maze[x][y].down_wall==0)))//again putting in condition as sometimes there can be situations where we can be on the edges of the matrix and this condition makes sure we are still not stuck.
		{
		if((generated_&&randnum==0)||(generated_&&randnum==1)||(generated_&&randnum==2)||(generated_&&randnum==3))////this condition only appylys when we are done with generating the maze and we want to make sure we pushed all the data and none of them is lost.
		{
			info2.push(curr_cell);
			generated_ = false;
		}

		else if((randnum==2)&&(left_dire==false)&&(generated_==false))//left
		{
			if(x!=0)
			{
				//bool lefter = selected_maze[x-1][y].player_visited;//when x is 0 or y is 0 or x is columns-1 or y is rows-1 the other booleans dont check anything so another boolean was implemented.
				if(selected_maze[x][y].left_wall==0)//looking if it is possible to move left and there is no walls
				{
				
				curr_cell=selected_maze[x-1][y];//updating every single information about curr_cell
				curr_cell.x_coordinate=x-1;
				curr_cell.y_coordinate=y;
				curr_cell.player_visited=true;
				selected_maze[x-1][y]=curr_cell;
				selected_maze[x-1][y].player_visited=true;
				selected_maze[x-1][y].x_coordinate=x;
				selected_maze[x-1][y].y_coordinate=y;
				
				info2.push(curr_cell);
				
				}
				

			}
			


		}
		else if ((randnum==1)&&(up_dire == false)&&(generated_==false))//up
		{
			if(y!=(rows-1))
			{
				//bool upper = selected_maze[x][y+1].player_visited;//when x is 0 or y is 0 or x is columns-1 or y is rows-1 the other booleans dont check anything so another boolean was implemented.
				if(selected_maze[x][y].up_wall==0)//looking if it is possible to move up and there is no walls
				{
					
					curr_cell=selected_maze[x][y+1];//updating every single information about curr_cell
					curr_cell.x_coordinate=x;
					curr_cell.y_coordinate=y+1;
					curr_cell.player_visited=true;
					selected_maze[x][y+1].player_visited=true;
					selected_maze[x][y+1].x_coordinate=x;
					selected_maze[x][y+1].y_coordinate=y;
					info2.push(curr_cell);
					
				}
			


			}
			


		}
		else if ((randnum==0)&&(right_dire==false)&&(generated_==false))//right
		{
			if(x!=(columns-1))
			{
				//bool righter = selected_maze[x+1][y].player_visited;//when x is 0 or y is 0 or x is columns-1 or y is rows-1 the other booleans dont check anything so another boolean was implemented.
				if(selected_maze[x][y].right_wall==0)//looking if it is possible to move right and there is no walls
				{
					
					curr_cell=selected_maze[x+1][y];//updating every single information about curr_cell
					curr_cell.x_coordinate=x+1;
					curr_cell.y_coordinate=y;
					curr_cell.player_visited=true;
					selected_maze[x+1][y]=curr_cell;
					selected_maze[x+1][y].player_visited=true;
					selected_maze[x+1][y].x_coordinate=x;
					selected_maze[x+1][y].y_coordinate=y;
					
					info2.push(curr_cell);
					
				}
			


			}
		

		}
		else if ((randnum ==3 )&&(down_dire==false)&&(generated_==false))//down
		{
			if(y!=0)
			{
				//bool downer = selected_maze[x][y-1].player_visited;//when x is 0 or y is 0 or x is columns-1 or y is rows-1 the other booleans dont check anything so another boolean was implemented.
				if(selected_maze[x][y].down_wall==0)//looking if it is possible to move down
				{
					
					curr_cell=selected_maze[x][y-1];//updating every single information about curr_cell
					curr_cell.x_coordinate=x;
					curr_cell.y_coordinate=y-1;
					curr_cell.player_visited=true;
					selected_maze[x][y-1]=curr_cell;
					selected_maze[x][y-1].player_visited=true;
					selected_maze[x][y-1].x_coordinate=x;
					selected_maze[x][y-1].y_coordinate=y;
					
					info2.push(curr_cell);
					
				}
				

			}
			

		}


		}
		else
		{	
			
			curr_cell = info2.topAndPop();//popping the top information when everything is done.
			generated_=true;
			bool down_dire=false;
			bool right_dire=false;
			bool left_dire=false;
			bool up_dire=false;
		}
	}
}

 void filestreamer(vector<vector<Node>> mat,int count) //ofstream function to write the info of the maze generated
 {
	ofstream offstream;
	string maze_number = to_string(count);

	offstream.open("maze_" +maze_number+".txt");
	offstream<<rows<<"  "<<columns<<endl;
	 for (int i =0;i<columns;i++)
	 {
		 for(int j=0;j<rows;j++)
		 {
			  offstream<< "x="<<i<<" y="<<j<<" l="<<mat[i][j].left_wall<<" r="<<mat[i][j].right_wall<<" u="<<mat[i][j].up_wall<<" d="<<mat[i][j].down_wall<<endl;
		 }

	 }
	 offstream.close();
 }
 void offstreamer (Stack<Node>&info2,int selected)//ofstream fucntion to write the path followd when solving the maze.
 {
	 
	 ofstream offstreamer;
	 int selected_ = selected+1;
	 string maze_number = to_string(selected_);
	 string x = to_string(entrx);
	 string y = to_string(entry);
	 string x_ = to_string(endx);
	 string y_ = to_string(endy);
	 offstreamer.open("maze_" +maze_number+"_path_"+x+"_"+y+"_"+x_+"_"+y_+".txt");
	 Stack<Node> temp_STACK;
	 while(!(info2.isEmpty()))
	 {
		Node courant_cell = info2.topAndPop();
		temp_STACK.push(courant_cell);
		
	 }
	 offstreamer<<entrx<<" "<<entry<<endl;
	 while(!(temp_STACK.isEmpty()))
	 {
		 Node courant_cell_2 = temp_STACK.topAndPop();
		 offstreamer<<courant_cell_2.x_coordinate<<" "<<courant_cell_2.y_coordinate<<endl;
	 }
	 offstreamer.close();
 }

int main()
{
	int number_maze,row,column,maze_num,entry_x,entry_y,end_x,end_y;
	vector<vector<vector<Node>>> Maze_diff;//a vector to store the matrixes to be able to use them later.

	cout<<"Enter number of mazes: ";
	cin>>number_maze;
	cout<<"Enter the number of rows and columns (M and N): ";
	cin>>row>>column;
	::rows=row;
	::columns=column;
	
	for(int i =0;i<number_maze;i++)
	{
	Stack<Node> info;//stack to be able to reach the info of our maze generated.
	vector<vector<Node>> mat;//our matrix to be generated.
	new_mat(mat);//assigning the default parameters to every cell of the matrix
	assign_coordinate(mat);//assigning the default coordinates to every cell of the matrix
	mat[0][0].cell_visited=true;//pushing 0,0 in the first place and assigning it as visited.
	info.push(mat[0][0]);
	Node current_cell = mat[0][0];
	while(not_all_visited(mat))//while we didnt visit all cells continue to crash the walls in our matrix.
	{
		put_wall(info,mat,current_cell);
		
	}
	Maze_diff.push_back(mat);
	
	filestreamer(mat,i+1);

	}
	cout<<"All mazes are generated."<<endl;

	Stack<Node>info2;//stack node to be able to store the info of path followed
	vector<vector<Node>> selected_maze;//our matrix of the maze selected
	cout<<"Enter a maze ID between 1 to "<<to_string(number_maze)<<" inclusive to find a path:";
	cin>>maze_num;
	int selected = maze_num-1;
	selected_maze = Maze_diff[selected];
	cout<<"Enter x and y coordinates of the entry points (x,y) or (column,row): ";
	cin>>entry_x>>entry_y;
	::entrx = entry_x;
	::entry = entry_y;
	cout<<"Enter x and y coordinates of the exit points (x,y) or (column,row): ";
	cin>>end_x>>end_y;
	::endx = end_x;
	::endy = end_y;
	Node curr_cell = selected_maze[entry_x][entry_y];//assigning curr cell as selected maze and assigning as player visited
	curr_cell.player_visited=true;
	info2.push(curr_cell);
	solve_maze(selected_maze,entry_x,entry_y,end_x,end_y,curr_cell,info2);//creating a path in the maze.
	offstreamer(info2,selected);//ofstream the path followed.
	return 0;
}