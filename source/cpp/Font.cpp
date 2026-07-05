int GetFont(float &x, float &y, char letter, float &s_width, int set, int modeset, bool password, int game_mode)
{
    
    // Default for most letters
    s_width = 1.8f;
    
    if(password==true)     
    switch (letter) 
    {
           
        // UPPER CASE   
        
        case 'A':		// left mouse button
             x = 0;
             y = 1;
	    break;

        case 'B':		// left mouse button
             x = 1;
             y = 1;
	    break;
        
        case 'C':		// left mouse button
             x = 2;
             y = 1;
	    break;
        
        case 'D':		// left mouse button
             x = 3;
             y = 1;
	    break;
        
        case 'E':		// left mouse button
             x = 4;
             y = 1;
	    break;
        
        case 'F':		// left mouse button
             x = 5;
             y = 1;
	    break;
        
        case 'G':		// left mouse button
             x = 6;
             y = 1;
	    break;
         
        case 'H':		// left mouse button
             x = 7;
             y = 1;
	    break;
                
        case 'I':		// left mouse button
             x = 8;
             y = 1;
	    break;
                
        case 'J':		// left mouse button
             x = 9;
             y = 1;
	    break;
                
        case 'K':		// left mouse button
             x = 10;
             y = 1;
	    break;
                
        case 'L':		// left mouse button
             x = 11;
             y = 1;
	    break;
                
        case 'M':		// left mouse button
             x = 12;
             y = 1;
	    break;
                
        case 'N':		// left mouse button
             x = 13;
             y = 1;
	    break;
                
        case 'O':		// left mouse button
             x = 14;
             y = 1;
	    break;
                
        case 'P':		// left mouse button
             x = 15;
             y = 1;
	    break;
                 
        case 'Q':		// left mouse button
             x = 0;
             y = 0;
	    break;
                        
        case 'R':		// left mouse button
             x = 1;
             y = 0;
	    break;
                        
        case 'S':		// left mouse button
             x = 2;
             y = 0;
	    break;
                        
        case 'T':		// left mouse button
             x = 3;
             y = 0;
	    break;
                        
        case 'U':		// left mouse button
             x = 4;
             y = 0;
	    break;
                        
        case 'V':		// left mouse button
             x = 5;
             y = 0;
	    break;
                        
        case 'W':		// left mouse button
             x = 6;
             y = 0;
	    break;
                        
        case 'X':		// left mouse button
             x = 7;
             y = 0;
	    break;
                        
        case 'Y':		// left mouse button
             x = 8;
             y = 0;
	    break;
                        
        case 'Z':		// left mouse button
             x = 9;
             y = 0;
	    break; 
                                                                                                                	    
        default:
    
            x = 0;
            y = 0;
            
        break;          
        
     }           
      
    if(password==false)    
    switch (letter)
    {
           
        // UPPER CASE   
        
        case 'A':		// left mouse button
             x = 0;
             y = 7;
	    break;

        case 'B':		// left mouse button
             x = 1;
             y = 7;
	    break;
        
        case 'C':		// left mouse button
             x = 2;
             y = 7;
	    break;
        
        case 'D':		// left mouse button
             x = 3;
             y = 7;
	    break;
        
        case 'E':		// left mouse button
             x = 4;
             y = 7;
	    break;
        
        case 'F':		// left mouse button
             x = 5;
             y = 7;
	    break;
        
        case 'G':		// left mouse button
             x = 6;
             y = 7;
	    break;
         
        case 'H':		// left mouse button
             x = 7;
             y = 7;
	    break;
                
        case 'I':		// left mouse button
             x = 8;
             y = 7;
        //     s_width = 1.0;                
	    break;
                
        case 'J':		// left mouse button
             x = 9;
             y = 7;
	    break;
                
        case 'K':		// left mouse button
             x = 10;
             y = 7;
	    break;
                
        case 'L':		// left mouse button
             x = 11;
             y = 7;
        //     s_width = 0.8;               
	    break;
                
        case 'M':		// left mouse button
             x = 12;
             y = 7;
	    break;
                
        case 'N':		// left mouse button
             x = 13;
             y = 7;
	    break;
                
        case 'O':		// left mouse button
             x = 14;
             y = 7;
	    break;
                
        case 'P':		// left mouse button
             x = 15;
             y = 7;
	    break;
                 
        case 'Q':		// left mouse button
             x = 0;
             y = 6;
	    break;
                        
        case 'R':		// left mouse button
             x = 1;
             y = 6;
	    break;
                        
        case 'S':		// left mouse button
             x = 2;
             y = 6;
	    break;
                        
        case 'T':		// left mouse button
             x = 3;
             y = 6;
	    break;
                        
        case 'U':		// left mouse button
             x = 4;
             y = 6;
	    break;
                        
        case 'V':		// left mouse button
             x = 5;
             y = 6;
	    break;
                        
        case 'W':		// left mouse button
             x = 6;
             y = 6;
	    break;
                        
        case 'X':		// left mouse button
             x = 7;
             y = 6;
	    break;
                        
        case 'Y':		// left mouse button
             x = 8;
             y = 6;
	    break;
                        
        case 'Z':		// left mouse button
             x = 9;
             y = 6;
	    break;   
           
        // LOWER CASE   

        case 'a':		// left mouse button
             x = 10;
             y = 6;
	    break;

        case 'b':		// left mouse button
             x = 11;
             y = 6;
	    break;
        
        case 'c':		// left mouse button
             x = 12;
             y = 6;
	    break;
        
        case 'd':		// left mouse button
             x = 13;
             y = 6;
	    break;
        
        case 'e':		// left mouse button
             x = 14;
             y = 6;
	    break;
        
        case 'f':		// left mouse button
             x = 15;
             y = 6;
	    break;
        
        case 'g':		// left mouse button
             x = 0;
             y = 5;
	    break;
         
        case 'h':		// left mouse button
             x = 1;
             y = 5;
	    break;
                
        case 'i':		// left mouse button
             x = 2;
             y = 5;
             s_width = 0.8f;             
	    break;
                
        case 'j':		// left mouse button
             x = 3;
             y = 5;
	    break;
                
        case 'k':		// left mouse button
             x = 4;
             y = 5;
	    break;
                
        case 'l':		// left mouse button
             x = 5;
             y = 5;
             s_width = 1.0f;               
	    break;
                
        case 'm':		// left mouse button
             x = 6;
             y = 5;
	    break;
                
        case 'n':		// left mouse button
             x = 7;
             y = 5;
	    break;
                
        case 'o':		// left mouse button
             x = 8;
             y = 5;
	    break;
                
        case 'p':		// left mouse button
             x = 9;
             y = 5;
	    break;
                 
        case 'q':		// left mouse button
             x = 10;
             y = 5;
	    break;
                        
        case 'r':		// left mouse button
             x = 11;
             y = 5;
             s_width = 1.5;              
	    break;
                        
        case 's':		// left mouse button
             x = 12;
             y = 5;
	    break;
                        
        case 't':		// left mouse button
             x = 13;
             y = 5;
             s_width = 1.5f;               
	    break;
                        
        case 'u':		// left mouse button
             x = 14;
             y = 5;
	    break;
                        
        case 'v':		// left mouse button
             x = 15;
             y = 5;
	    break;
                        
        case 'w':		// left mouse button
             x = 0;
             y = 4;
	    break;
                        
        case 'x':		// left mouse button
             x = 1;
             y = 4;
	    break;
                        
        case 'y':		// left mouse button
             x = 2;
             y = 4;
	    break;
                        
        case 'z':		// left mouse button
             x = 3;
             y = 4;
	    break;
              
        case '0':		// left mouse button
             x = 0;
             if( ( modeset != 0 || set == 6) && game_mode != 4)
                 y = 2; 
             else
                 y = 3;
             
             if( set == 0 && game_mode == 3)
                y = 9;
             
	    break;
                          
        case '1':		// left mouse button
             x = 1;
             if( ( modeset != 0 || set == 6) && game_mode != 4)
                 y = 2;
             else
                 y = 3;
             
             if( set == 0 && game_mode == 3)
                y = 9;
                 
	    break;
                                 
        case '2':		// left mouse button
             x = 2;
             if( ( modeset != 0 || set == 6) && game_mode != 4)
                 y = 2;
             else
                 y = 3;
             
             if( set == 0 && game_mode == 3)
                y = 9;
                 
	    break;
                                 
        case '3':		// left mouse button
             x = 3;
             if( ( modeset != 0 || set == 6) && game_mode != 4)
                 y = 2;
             else
                 y = 3;
             
             if( set == 0 && game_mode == 3)
                y = 9;
                 
	    break;
                                 
        case '4':		// left mouse button
             x = 4;
             if( ( modeset != 0 || set == 6) && game_mode != 4)
                 y = 2;
             else
                 y = 3;
             
             if( set == 0 && game_mode == 3)
                y = 9;
                 
	    break;
                                 
        case '5':		// left mouse button
             x = 5;
             if( ( modeset != 0 || set == 6) && game_mode != 4)
                 y = 2;
             else
                 y = 3;
             
             if( set == 0 && game_mode == 3)
                y = 9;
                 
	    break;
                                 
        case '6':		// left mouse button
             x = 6;
             if( ( modeset != 0 || set == 6) && game_mode != 4)
                 y = 2;
             else
                 y = 3;
             
             if( set == 0 && game_mode == 3)
                y = 9;
                 
	    break;
                                 
        case '7':		// left mouse button
             x = 7;
             if( ( modeset != 0 || set == 6) && game_mode != 4)
                 y = 2;
             else
                 y = 3;
             
             if( set == 0 && game_mode == 3)
                y = 9;
                 
	    break; 
                                 
        case '8':		// left mouse button
             x = 8;
             if( ( modeset != 0 || set == 6) && game_mode != 4) // set == 1 ||
                 y = 2;
             else 
                 y = 3;
             
             if( set == 0 && game_mode == 3)
                y = 9;
                 
	    break; 
                                 
        case '9':		// left mouse button
             x = 9;
             if( ( modeset != 0 || set == 6) && game_mode != 4)
                 y = 2;
             else
                 y = 3;
             
             if( set == 0 && game_mode == 3)
                y = 9;
                 
	    break;
	    
	    case '>':
             x=10;
             y=3;
        break;
        	    
	    case 'é':
             x=11;
             y=3;
        break;
	    
	    case 'û':
             x=12;
             y=3;
        break;
	    
	    case 'è':
             x=13;
             y=3;
        break;
	    
	    case 'à':
             x=14;
             y=3;
        break;
	    
	    case '+':
             x=15;
             y=3;
        break;
	    
	    case 'î':
             x=10;
             y=2;
        break;
	    
	    case 'ç':
             x=11;
             y=2;
        break; 
	    
	    case 'ô':
             x=12;
             y=2;
        break;
	    
	    case 'â':
             x=13;
             y=2;
        break;
 	    
	    case '/':
             x=14;
             y=2;
        break;
  	    
	    case 'Ç':
             x=15;
             y=2;
        break;
  	    
	    case 'ù':
             x=0;
             y=1;
        break;
        
	    case '¡': 
             x=1;
             y=1;
        break;
        
	    case '¿':
             x=2; 
             y=1;
        break;
        
	    case 'ú':
             x=3;
             y=1;
        break;            

	    case 'í':
             x=4;
             y=1;
        break;            
            
	    case 'ñ':
             x=5;
             y=1;
        break;    
            
	    case 'Á':
             x=6;
             y=1;
        break;          
            
	    case 'Í':
             x=7;
             y=1;
        break;         
            
	    case 'ó':
             x=8;
             y=1;
        break;           
            
	    case 'á':
             x=9;
             y=1;
        break;          
            
	    case 'É':
             x=10;
             y=1;
        break;            
            
	    case 'Ú':
             x=11;
             y=1;
        break;          
            
	    case 'Ó':
             x=12;
             y=1;
        break;          
            
	    case 'º':
             x=13;
             y=1;
        break;
            
	    case 'Ñ':
             x=14;
             y=1;
        break;                  
            
	    case 'À':
             x=15;
             y=1;
        break;   
            
	    case 'È':
             x=0;
             y=0;
        break;  
            
	    case 'Ö':
             x=1;
             y=0;
        break;          
                                                                                                                   	    
        case '[':		// left mouse button
             x = 7;
             y = 4;
	    break;
                                         
        case ']':		// left mouse button
             x = 8;
             y = 4;
	    break;
 	    
        case '(':		// left mouse button
             x = 13;
             y = 4;
	    break;
                                         
        case ')':		// left mouse button
             x = 14;
             y = 4;
	    break;
                                         
        case ',':		// left mouse button
             x = 15;
             y = 4;
	    break;
                                                        
        case ':':		// left mouse button
             x = 9;
             y = 4;
	    break;
                                         
        case '-':		// left mouse button
             x = 10;
             y = 4;
	    break;
                                         
        case '!':		// left mouse button
             x = 4;
             y = 4;
	    break;
                                         
        case '&':		// left mouse button
             x = 5;
             y = 4; 
	    break;
                                                         
        case '.':		// left mouse button
             x = 6;
             y = 4;
	    break;
                                                          
        case '?':		// left mouse button
             x = 11;
             y = 4;
	    break;
                                                          
        case '@':		// left mouse button
             x = 12;
             y = 4;
	    break;
                                                           
        case '$':		// left mouse button
             x = 2;
             y = 0;
	    break;  
                                                           
        case 'Ž':		// left mouse button
             x = 3;
             y = 0; 
	    break;           
                                                           
        case 'Ý':		// left mouse button
             x = 4;
             y = 0;
	    break;  
                                                           
        case 'Þ':		// left mouse button
             x = 5;
             y = 0; 
	    break;    
	    
        case '¶':		// HQ Symbol
             x = 0;
             y = 8;
	    break;   
                                                           
        case '¤':		// HQ Symbol
             x = 1;
             y = 8; 
	    break; 
                                                            
        case '×':		// Multi face 1
             x = 6;
             y = 0;   
	    break;     
                                                           
        case '~':		// Multi face 2  
             x = 7;
             y = 0; 
	    break;    	
                                                            
        case '¢':		// Multi face 1
             x = 8;
             y = 0;   
	    break;     
                                                           
        case 'ª':		// Multi face 2 
             x = 9;
             y = 0;  
	    break;  					     
        
        case '¥':		// HQ Symbol
             x = 13;
             y = 0; 
	    break;      
	    
        // Censored synbols!
        case '§':		// HQ Symbol
             x = 10;
             y = 0; 
	    break;  
        case '¼':		// HQ Symbol
             x = 11;
             y = 0; 
	    break;  
        case '½':		// HQ Symbol
             x = 12;
             y = 0; 
	    break;  
        case '¾':		// HQ Symbol
             x = 14; 
             y = 0; 
	    break;   

        case '¸':		// FireRate 
             x = 10;
             y = 9; 
	    break;  
        case '³':		// FireRate
             x = 11; 
             y = 9;  
	    break;  							    

        case 'Õ':		// Reload
             x = 12;
             y = 9; 
	    break;  
        case '¬':		// Reload
             x = 13;  
             y = 9;  
	    break;          

        case '«':		// Reload
             x = 14;
             y = 9; 
	    break;  
        case 'Ï':		// Reload
             x = 15; 
             y = 9;   
	    break;    
        case '±':		// '/' 
             x = 0; 
             y = 10;   
	    break;    
                                                                                                                         	    
        default:
    
            x = 15;
            y = 0;
            
        break;
                              
    }

	return true;															// All went well, continue on
}
int GetNewFont(float &x, float &y, char letter, float &s_width, int set, int modeset, bool password, int game_mode)
{
	x = 4;
	y = 3;

    switch (letter)
    {
           
        // UPPER CASE   
        
        case 'A':		// left mouse button
             x = 0;
             y = 0;
	    break;

        case 'B':		// left mouse button
             x = 1;
             y = 0;
	    break;
        
        case 'C':		// left mouse button
             x = 2;
             y = 0;
	    break;
        
        case 'D':		// left mouse button
             x = 3;
             y = 0;
	    break;
        
        case 'E':		// left mouse button
             x = 4;
             y = 0;
	    break;
        
        case 'F':		// left mouse button
             x = 5;
             y = 0;
	    break;
        
        case 'G':		// left mouse button
             x = 6;
             y = 0;
	    break;
         
        case 'H':		// left mouse button
             x = 7;
             y = 0;
	    break;
                
        case 'I':		// left mouse button
             x = 8;
             y = 0;
        //     s_width = 1.0;                
	    break;
                
        case 'J':		// left mouse button
             x = 9;
             y = 0;
	    break;
                
        case 'K':		// left mouse button
             x = 10;
             y = 0;
	    break;
                
        case 'L':		// left mouse button
             x = 11;
             y = 0;
        //     s_width = 0.8;               
	    break;
                
        case 'M':		// left mouse button
             x = 12;
             y = 0;
	    break;
                
        case 'N':		// left mouse button
             x = 13;
             y = 0;
	    break;
                
        case 'O':		// left mouse button
             x = 14;
             y = 0;
	    break;
                
        case 'P':		// left mouse button
             x = 15;
             y = 0;
	    break;
                 
        case 'Q':		// left mouse button
             x = 0;
             y = 1;
	    break;
                        
        case 'R':		// left mouse button
             x = 1;
             y = 1;
	    break;
                        
        case 'S':		// left mouse button
             x = 2;
             y = 1;
	    break;
                        
        case 'T':		// left mouse button
             x = 3;
             y = 1;
	    break;
                        
        case 'U':		// left mouse button
             x = 4;
             y = 1;
	    break;
                        
        case 'V':		// left mouse button
             x = 5;
             y = 1;
	    break;
                        
        case 'W':		// left mouse button
             x = 6;
             y = 1;
	    break;
                        
        case 'X':		// left mouse button
             x = 7;
             y = 1;
	    break;
                        
        case 'Y':		// left mouse button
             x = 8;
             y = 1;
	    break;
                        
        case 'Z':		// left mouse button
             x = 9;
             y = 1;
	    break;   
           
        // LOWER CASE   

        case 'a':		// left mouse button
             x = 10;
             y = 1;
	    break;

        case 'b':		// left mouse button
             x = 11;
             y = 1;
	    break;
        
        case 'c':		// left mouse button
             x = 12;
             y = 1;
	    break;
        
        case 'd':		// left mouse button
             x = 13;
             y = 1;
	    break;
        
        case 'e':		// left mouse button
             x = 14;
             y = 1;
	    break;
        
        case 'f':		// left mouse button
             x = 15;
             y = 1;
	    break;
        
        case 'g':		// left mouse button
             x = 0;
             y = 2;
	    break;
         
        case 'h':		// left mouse button
             x = 1;
             y = 2;
	    break;
                
        case 'i':		// left mouse button
             x = 2;
             y = 2;
       //      s_width = 0.8f;             
	    break;
                
        case 'j':		// left mouse button
             x = 3;
             y = 2;
	    break;
                
        case 'k':		// left mouse button
             x = 4;
             y = 2;
	    break;
                
        case 'l':		// left mouse button
             x = 5;
             y = 2;
        //     s_width = 1.0f;               
	    break;
                
        case 'm':		// left mouse button
             x = 6;
             y = 2;
	    break;
                
        case 'n':		// left mouse button
             x = 7;
             y = 2;
	    break;
                
        case 'o':		// left mouse button
             x = 8;
             y = 2;
	    break;
                
        case 'p':		// left mouse button
             x = 9;
             y = 2;
	    break;
                 
        case 'q':		// left mouse button
             x = 10;
             y = 2;
	    break;
                        
        case 'r':		// left mouse button
             x = 11;
             y = 2;
       //      s_width = 1.5;              
	    break;
                        
        case 's':		// left mouse button
             x = 12;
             y = 2;
	    break;
                        
        case 't':		// left mouse button
             x = 13; 
             y = 2;
       //      s_width = 1.5f;               
	    break;
                        
        case 'u':		// left mouse button
             x = 14;
             y = 2;      
	    break;
                        
        case 'v':		// left mouse button
             x = 15;
             y = 2;
	    break;
                        
        case 'w':		// left mouse button
             x = 0;
             y = 3;
	    break;
                        
        case 'x':		// left mouse button
             x = 1;
             y = 3;
	    break;
                        
        case 'y':		// left mouse button
             x = 2;
             y = 3;
	    break;
                        
        case 'z':		// left mouse button
             x = 3;
             y = 3;
	    break;

		// 0 - 9 Numbers...
                        
        case '0':		// left mouse button
             x = 5;
             y = 3;
	    break;

		// 0 - 9 Numbers...
                        
        case '1':		// left mouse button
             x = 6;
             y = 3;
	    break;
		
		// 0 - 9 Numbers...
                        
        case '2':		// left mouse button
             x = 7;
             y = 3;
	    break;
		
		// 0 - 9 Numbers...
                        
        case '3':		// left mouse button
             x = 8;
             y = 3;
	    break;
		
		// 0 - 9 Numbers...
                        
        case '4':		// left mouse button
             x = 9;
             y = 3;
	    break;
		
		// 0 - 9 Numbers...
                        
        case '5':		// left mouse button
             x = 10;
             y = 3;
	    break;
		
		// 0 - 9 Numbers...
                        
        case '6':		// left mouse button
             x = 11;
             y = 3;
	    break;
		
		// 0 - 9 Numbers...   
                        
        case '7':		// left mouse button
             x = 12;
             y = 3;
	    break;
		
		// 0 - 9 Numbers...
                        
        case '8':		// left mouse button
             x = 13;
             y = 3;
	    break;
		
		// 0 - 9 Numbers...
                        
        case '9':		// left mouse button
             x = 14;
             y = 3;
	    break;
                        
        case '&':		// left mouse button
             x = 15;
             y = 3;
	    break;
                        
        case '@':		// left mouse button
             x = 0;
             y = 4;
	    break;		
                        
		case ':':		// left mouse button
             x = 1;
             y = 4;
	    break;		
                        
        case '/':		// left mouse button
             x = 2;
             y = 4;
	    break;	
                        
        case '.':		// left mouse button
             x = 3;
             y = 4; 
	    break;	
                        
		case ',':		// left mouse button
             x = 4;
             y = 4;
	    break;		
                        
        case '!':		// left mouse button
             x = 5;
             y = 4;
	    break;	
                        
        case '?':		// left mouse button
             x = 6;
             y = 4;
	    break;	
                         
        case '$':		// left mouse button
             x = 7;
             y = 4;
	    break;	             
                         
        case '-':		// left mouse button
             x = 8;
             y = 4;
	    break;	    
                         
        case '+':		// left mouse button
             x = 9;
             y = 4;
	    break;	  
 	    
        case '(':		// left mouse button
             x = 10;
             y = 4;
	    break;
                                         
        case ')':		// left mouse button
             x = 11;
             y = 4;
	    break;
 	    
        case '£':		// VG_PUNCH_FONT...
             x = 12;
             y = 4;
	    break;
                                         
        case '¥':		// VG_KICK_FONT...
             x = 13;
             y = 4;
	    break;
                                         
        case '¢':		// VG_LEFT_FONT...
             x = 14;
             y = 4;
	    break;
                                         
        case '¤':		// VG_RIGHT_FONT...
             x = 15;
             y = 4;
	    break;
                                         
        case '¦':		// VG_UP_FONT...
             x = 0;
             y = 5;
	    break;
                                         
        case '§':		// VG_DOWN_FONT...
             x = 1;
             y = 5;
	    break;
                                         
        case '¨':		// VG_LEFT_FONT_H...
             x = 2;
             y = 5;
	    break;
                                         
        case '©':		// VG_RIGHT_FONT_H...
             x = 3;
             y = 5;
	    break;
                                         
        case 'ª':		// VG_UP_FONT_H...
             x = 4;
             y = 5;
	    break;
                                         
        case '«':		// VG_DOWN_FONT_H...
             x = 5; 
             y = 5;
	    break;
                                         
        case '¬':		// VG_PUNCH_FONT_H...
             x = 6; 
             y = 5;
	    break; 
                                         
        case '®':		// VG_KICK_FONT_H...
             x = 7;
             y = 5;
	    break; 
                                         
        case '¯':		// VG_DOWNLEFT_FONT...
             x = 8;
             y = 5;  
	    break;
                                         
        case '²':		// VG_DOWNRIGHT_FONT...
             x = 9;
             y = 5;
	    break;
                                         
        case '³':		// VG_UPLEFT_FONT...
             x = 10;
             y = 5;
	    break;
                                         
        case '¹':		// VG_UPRIGHT_FONT...
             x = 11;
             y = 5;
	    break;
                                         
        case 'À':		// VG_PUNCH2_FONT...
             x = 12;
             y = 5;
	    break;
                                         
        case 'Á':		// VG_KICK2_FONT...
             x = 13;
             y = 5;
	    break;
                                         
        case 'Â':		// VG_PUNCH2_FONT_H...
             x = 14;
             y = 5;
	    break;
                                         
        case 'Ã':		// VG_KICK2_FONT_H...
             x = 15;
             y = 5;
	    break;
                                   
        case 'Æ':		// VG_SPECIAL1_FONT...
             x = 0;
             y = 6;
	    break;
                                   
        case 'Ç':		// VG_SPECIAL2_FONT...
             x = 1;
             y = 6;
	    break;
                                   
        case 'È':		// VG_SPECIAL3_FONT...
             x = 2;
             y = 6; 
	    break;
                                   
        case 'É':		// VG_SPECIAL4_FONT...
             x = 3;
             y = 6;
	    break;
                                   
        case 'Ê':		// VG_SPECIAL5_FONT...
             x = 4;
             y = 6; 
	    break;
                                   
        case 'Ë':		// VG_SPECIAL6_FONT...
             x = 5;
             y = 6;
	    break;
                                   
        case 'ö':		// WIN SYMBOL FONT...
             x = 6;
             y = 6;
	    break;
                                   
        case '÷':		// A button...
             x = 7;
             y = 6;
	    break;
                                   
        case 'ø':		// B button...
             x = 8;
             y = 6;
	    break;
                                   
        case 'ù':		// X button...
             x = 9;
             y = 6;
	    break;
                                   
        case 'ú':		// Y button...
             x = 10;
             y = 6;
	    break;
                                   
        case 'Ý':		// Back button...
             x = 11;
             y = 6;
	    break;
                                   
        case 'Ž':		// Start button...
             x = 12;
             y = 6;
	    break;
                                   
        case '¿':		// Perfect symbol...
             x = 13;
             y = 6;
	    break;

         case '{':		// Gyeong face...
             x = 14;
             y = 6; 
	    break;
                                                    
        case '}':		// Siu face...
             x = 15;
             y = 6;
	    break;
                              
        case '~':		// Minso face...
             x = 0;
             y = 7;
	    break;
                              
        case '¡':		// Reese face...
             x = 1;
             y = 7;
	    break;
                              
        case 'Ì':		// Yohan face...
             x = 2;
             y = 7;
	    break;
                              
        case 'Í':		// Jae face...
             x = 3;
             y = 7;
	    break;
                              
        case 'Î':		// Gun face...
             x = 4;
             y = 7;
	    break;
                              
        case 'Ï':		// Hyuk face...
             x = 5;
             y = 7;
	    break;
                              
        case 'Ð':		// Blank face...
             x = 6;
             y = 7;
	    break;
                                   
        case 'ã':		// Arrest symbol...
             x = 7;
             y = 7;
	    break;
                                   
        case '#':		// Spacebar symbol...
             x = 8;
             y = 7;
	    break;
                                   
        case 'Ø':		// Foward slash symbol...
             x = 9;
             y = 7;
	    break;
                                   
        case '±':		// Hash symbol...
             x = 10;
             y = 7;
	    break;
                                   
		case '¼':		// Block symbol...
             x = 11;
             y = 7;
	    break;
                                    
        case '½':		// Throw symbol...
             x = 12;
             y = 7;
	    break;
                                   
		case '¾':		// Left trigger symbol...
             x = 13;
             y = 7;
	    break;
                                   
        case '»':		// Right trigger symbol...
             x = 14;
             y = 7;
	    break;

	}
	
	return true;															// All went well, continue on

}