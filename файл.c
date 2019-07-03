#include "game.h"
#include "studio.h"                
#define MAP_WIDTH 8
#define MAP_HEIGHT 10
#define PLAYER_POSITION pos_y * MAP_WIDTH + pos_x

char map[] = {

    "#####   "
    "#xb ### "
    "###   # "
    "#x@b  # "
    "### bx# "
    "#x##b # "
    "# # x ##"
    "#b Obbx#"
    "#   x  #"
    "########"

};

int dest_squares[10];                                                  

int GetDestSquares()                                                    
{
    int count = 0, cell;                                               

    for(int row = 0; row < MAP_HEIGHT; row++)                           
    {
        for(int col = 0; col < MAP_WIDTH; col++)                        
        {
            cell = row * MAP_WIDTH + col;                               
        
            if(map[cell] == 'x' || map[cell] == 'O')                    
                dest_squares[count++] = cell;                           
        }
    }

    return count;                                                      
}

void GetPosition(int *pos_x, int *pos_y)
{
    int cell;                                                           

    for(int row = 0; row < MAP_HEIGHT; row++)                           
    {
        for(int col = 0; col < MAP_WIDTH; col++)                        
        {
            cell = row * MAP_WIDTH + col;                               
        
            if(map[cell] == '@')                                        
            {
                *pos_x = col;                                           
                *pos_y = row;                                          
            }
        }
    }
}

void MoveCharacter(int pos_x, int pos_y, int offset)
{
    if(map[PLAYER_POSITION + offset] != '#')                            
    {
        if(((map[PLAYER_POSITION + offset] == 'b') ||                   
            (map[PLAYER_POSITION + offset] == 'O')) &&                  
            (map[PLAYER_POSITION + offset * 2] != '#' ||               
             map[PLAYER_POSITION + offset * 2] != 'b' ||                
             map[PLAYER_POSITION + offset * 2] != 'O'))                 
        {
            map[PLAYER_POSITION] = ' ';                                 
            pos_x += offset;                                            

            if(map[PLAYER_POSITION + offset] == ' ')                  
                map[PLAYER_POSITION + offset] = 'b';                    

            else if(map[PLAYER_POSITION + offset] == 'x')             
                map[PLAYER_POSITION + offset] = 'O';                    

            else
            {
                map[PLAYER_POSITION - offset] = '@';                   
                return;                                               
            }

            map[PLAYER_POSITION] = '@';                                
        }

        else                                                                                                               
        {
            map[PLAYER_POSITION] = ' ';                                
            pos_x += offset;                                           
            map[PLAYER_POSITION] = '@';                                
        }
    }   
} 

int main()
{
    InitScreen();

    int key;                                                            
    int pos_x, pos_y;                                                   
    int dest_count;                                                     

    int dest_num = GetDestSquares();

    int center_x = SCREEN_WIDTH / 2 - MAP_WIDTH / 2;
    int center_y = SCREEN_HEIGHT / 2 - MAP_HEIGHT / 2;

    PrintMap(center_x, center_y, MAP_WIDTH, MAP_HEIGHT, map);
    
    while(1)
    {
        if(key == 27) break;
        
        key = getch();
        GetPosition(&pos_x, &pos_y);

        switch(key)
        {
            case 'W': MoveCharacter(pos_x, pos_y, - MAP_WIDTH); break;
            case 'S': MoveCharacter(pos_x, pos_y, MAP_WIDTH); break;
            case 'A': MoveCharacter(pos_x, pos_y, - 1); break;
            case 'D': MoveCharacter(pos_x, pos_y, 1); break;
        }

        dest_count = 0;                                                 

        for(int i = 0; i < 10; i++)                                    
        {            
            if(map[dest_squares[i]] == 'O') dest_count++;               
        
            if(map[dest_squares[i]] == ' ')                            
                map[dest_squares[i]] = 'x';                           
        }
        
        PrintMap(center_x, center_y, MAP_WIDTH, MAP_HEIGHT, map);

       
        if(dest_num == dest_count)
        {
            sprintf(screen + (SCREEN_WIDTH * SCREEN_HEIGHT / 2) - MAP_WIDTH / 2, "YOU WIN!");
            RefreshScreen();
            break;
        }       
    }

    Leave();
    
    return 0;
}
