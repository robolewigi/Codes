     bool running = true;
     SDL_Renderer* renderer;
     SDL_Event event;
     std::vector< SDL_Vertex > verticies;
     std::vector< SDL_Vertex > triangles;
     float deltaTime = 0;
     int key=-1;
     int getArgc; char** getArgv;

struct windowsOld {
     bool running = true;
     SDL_Renderer* renderer;
     SDL_Event event;
     std::vector< SDL_Vertex > verticies;
     std::vector< SDL_Vertex > triangles;
     float deltaTime = 0;
     int key=-1;
     int getArgc; char** getArgv;
     std::string filePath;
     int width=1,height=1;
     int mouseX=-1,mouseY=-1;
     SDL_Window* window={};
     Uint64 last=0;
     Uint64 now=SDL_GetPerformanceCounter();
     bool keys[83]{};
     bool mouse[4]{};
     int cenWid =0,cenHei =0;
     float aspect=1.0f;
     int monitorX =0 , monitorY =0;
     bool click = false; 
         int button=-1;
   
      std::fstream save1;
 
     void begin( ) { 
         SDL_Init( SDL_INIT_EVERYTHING );
  window = SDL_CreateWindow("SDL",55, 55, 888, 555, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
     renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
      
      filePath=getArgv[0];
 
     {filePath.erase(filePath.find_last_of("\\"));
      std::filesystem::create_directories("saves");
     
       save1.open("saves\\save1.txt");
 if (!save1){
    save1.open("saves\\save1.txt",std::ios::app);
 
       SDL_MaximizeWindow(window);
            SDL_GetWindowSize(window,&monitorX,&monitorY);
            cenWid  = monitorX / 2, cenHei = monitorY / 2;
  aspect = float(monitorY) / float(monitorX);
             SDL_RenderSetLogicalSize(SDL_GetRenderer(window), monitorX, monitorY);
  SDL_RestoreWindow(window); 
      
  save1 << monitorX << "\n" << monitorY << "\n";
 
  }else{
       save1 >> monitorX >> monitorY;
  aspect = float(monitorY) / float(monitorX);
 
  SDL_RenderSetLogicalSize(SDL_GetRenderer(window),monitorX, monitorY);
  resize();
 
  }
 save1.close();}
 
   findMouse();   
     }
 
      void resize(){
           SDL_GetWindowSize(window,&width,&height);
           SDL_SetWindowSize(window, width, int(width * aspect));
        SDL_GetWindowSize(window,&width,&height);
        cenWid=width/2 ,cenHei=height/2;
      }
 
     void findMouse(){
       SDL_GetMouseState(&mouseX,&mouseY);
                       mouseX = int(mouseX / float( float(width )/monitorX ));
                       mouseY = int(mouseY / float( float(height)/monitorY ));
     }
 
     void mouseClick(){
 
     }
 
     void events()
     {
         button = event.button.button;
         key = event.key.keysym.scancode;
         if (key >= 0 && key <= 82 )
         {
             switch(event.type){
                 case SDL_KEYDOWN:
                   keys[key] = true; 
         break;
 
                 case SDL_KEYUP:
                     keys[key] = false; 
                     break;
             }
         }
         if( button >= 0 && button <= 3)
         {
          switch(event.type){
                 case SDL_MOUSEBUTTONDOWN:
         mouse[button] = true; 
                     findMouse();
                       break;
     
                 case SDL_MOUSEMOTION:
                     findMouse();
                           break;
 
                 case SDL_MOUSEBUTTONUP:
                     mouse[button] = false; 
                     break;}
         }
 
         if(keys[SDL_SCANCODE_ESCAPE] || event.window.event == 14){
             running = false;
         }
               
         if(event.window.event == SDL_WINDOWEVENT_RESIZED){
   resize();
         }
     }
 
     void update()  {
         SDL_SetRenderDrawColor(renderer, 99, 99, 99, 255);
      SDL_RenderClear( renderer );
   last = now;
    now = SDL_GetPerformanceCounter();
 
    deltaTime = (now - last)*1000.0f / SDL_GetPerformanceFrequency() ;
 
 
     }
 
     void quit() {
         SDL_DestroyRenderer( renderer );
     SDL_DestroyWindow( window );
     SDL_Quit();
     }
 
};

struct shapesOld : virtual windowsOld{
      int poiX[6] = { 0,1,0,1,0,1 };
 int poiY[6] =      { 0,0,1,0,1,1 };
 
 
 SDL_Color colorMult(SDL_Color col, float x=1.0 ){
     col.r = Uint8(col.r * x); col.g = Uint8(col.g * x); col.b = Uint8(col.b * x);
     return col;
 }
 
 void rectangle(float x, float y, float w, float h,SDL_Color color=colors[0])
 {
     verticies.insert(verticies.end(), { { SDL_FPoint{ poiX[0] * w + x, poiY[0] * h+ y }, color, SDL_FPoint{ 0 } },
                                 { SDL_FPoint{ poiX[1] * w + x, poiY[1] * h+ y }, color, SDL_FPoint{ 0 }},
                                 { SDL_FPoint{ poiX[2] * w + x, poiY[2] * h+ y }, color, SDL_FPoint{ 0 }},
                                 { SDL_FPoint{ poiX[3] * w + x, poiY[3] * h+ y }, color, SDL_FPoint{ 0 } },
                                 { SDL_FPoint{ poiX[4] * w + x, poiY[4] * h+ y }, color, SDL_FPoint{ 0 }},
                                 { SDL_FPoint{ poiX[5] * w + x, poiY[5] * h+ y }, color, SDL_FPoint{ 0 }} });
 }
 
       void triangle(float x, float y,float z=1.0f)
      {
       triangles.insert(triangles.end(),{{   SDL_FPoint{  0.0f*z+x, 0.0f*z+y }, SDL_Color{  155, 0, 0, 255 }, SDL_FPoint{ 0 } },
                                   { SDL_FPoint{ -1.0f*z+x, 1.0f*z+y }, SDL_Color{ 155, 0, 0, 255 }, SDL_FPoint{ 0 }},
                                   { SDL_FPoint{  1.0f*z+x, 1.0f*z+y }, SDL_Color{  155, 0, 0, 255 }, SDL_FPoint{ 0 }},
                                  });
 
      }
 
       void color(int x, int y,SDL_Color color=colors[0]){
           if(x==0){
           for(int i=0;i<6;i++){
               verticies[i+y].color = color;
           }
           }
       }
 
       float degrees(float degrees)
 {
     return(degrees * (3.141592f/180));
 }
 
 
     void rotate(float cx,float cy,float x, float y,float rot,int index)
  	{
  	  float s = sin(degrees(rot));
  	  float c = cos(degrees(rot));
  	
  	      translate point back to origin:
  	  x -= cx;
  	  y -= cy;
  	
  	      rotate point
  	  float xnew = x * c - y * s;
  	  float ynew = x * s + y * c;
  	
  	      translate point back:
  	   triangles[index].position.x = xnew + cx;
  	  triangles[index].position.y = ynew + cy;
     }
 
      struct object{
          float locX=0,locY = 0;
             float size=0.0f;
   float angle=90,dx=0,dy=0;
   int shapeIndex=0; int type;
   object(float x,float y, float s,float a, float xd,float yd,int ind,int t)
   {
 
   }
  };
 
 std::vector <object> objects;
 
 void createRectangle(float x,float y, float s,float a, float xd,float yd,int ind,int t,int arrayInd){
  object thisObj=objects[arrayInd];
     thisObj.locX=x;thisObj.locY=y;thisObj.size=s;thisObj.angle=a;thisObj.dx=xd;thisObj.dy=yd;thisObj.shapeIndex=ind;thisObj.type=t;
        if(thisObj.type==0){
   rectangle(thisObj.locX-thisObj.size/2,thisObj.locY-thisObj.size/2,thisObj.size,thisObj.size);
   }
 
 }
 
   	void translate(float x=0,int set=0,int dir =0, int in=0){
  		x *= deltaTime/4.0f; 
  			if(set==0){
  	
  			 float dx = dir==0 ? cos(degrees(- objects[in].angle)) * deltaTime/15 : sin (degrees( objects[in].angle)) * deltaTime/15;
  			 float dy = dir==0 ? sin(degrees(- objects[in].angle)) * deltaTime/15 : cos (degrees( objects[in].angle)) * deltaTime/15;
  			 dx*=x;  dy*=x;
             
  			triangles[objects[in].shapeIndex].position.x+= dx;
             triangles[objects[in].shapeIndex+1].position.x+= dx;	
             triangles[objects[in].shapeIndex+2].position.x+= dx;
  			triangles[objects[in].shapeIndex].position.y+= dy;
             triangles[objects[in].shapeIndex+1].position.y+= dy;	
             triangles[objects[in].shapeIndex+2].position.y+= dy;
  			objects[in].locX=triangles[objects[in].shapeIndex].position.x;  
             objects[in].locY=triangles[objects[in].shapeIndex].position.y;
  			}
 
  			if(set==1){
  			 objects[in].angle=fmod(x+ objects[in].angle,360.0f);
  		 objects[in].angle=	 objects[in].angle < 0 ? 360+ objects[in].angle : objects[in].angle;
  	
  		    	for(int i=1;i<3;i++){
  			rotate( objects[in].locX, objects[in].locY,triangles
                 [ objects[in].shapeIndex+i].position.x,
                 triangles[ objects[in].shapeIndex+i].position.y,-x,i);
  			}
  			}
             if(set==2)
             {
             
             }
  			
  		}
 
 
       void update()  {
 
           windows::update();
                           SDL_SetRenderDrawColor( renderer, 0, 0, 0, SDL_ALPHA_OPAQUE );
                           SDL_RenderGeometry(renderer, nullptr, verticies.data(), int(verticies.size()), nullptr, 0);
                           SDL_RenderGeometry(renderer, nullptr, triangles.data(), int(triangles.size()), nullptr, 0);
       }
 
};

struct uiOld : virtual shapesOld{
 
     struct widget{
     int index=0,shape=0;
     float locX=0,locY=0;
     float sizeX=0.0f,sizeY=0.0f;
     SDL_Color color = colors[0]; 
     };
 
     std::vector <widget> widgets;
 
      void createWidget(float x, float y, float w, float h,SDL_Color col=colors[1], int index=-1,int shape=0){
         if(shape==0){
          rectangle(x,y,w,h,col);
         }
              if(index==-1){
                  index = int(widgets.size() + 1);
             widgets.resize(index);
             widgets[index - 1].index = int(verticies.size() - 6);
              }
 
         widgets[index-1].locX=x,widgets[index-1].locY=y,
             widgets[index-1].sizeX=w,widgets[index-1].sizeY=h;
         widgets[index-1].color=col;
     }
      int widgetSelect=-1;
 
     void begin( ){
         windows::begin( );
       
 
         createWidget(222,222,77,77,colors[1]);
         createWidget(1,1,77,77,colors[4]);
     }
 
    void events(){
        windows::events();
 
 
           if(widgetSelect>=0){
       color(0,widgets[widgetSelect].index,widgets[widgetSelect].color);
     widgetSelect=-1;
           }
 
   for(int i=0;i<widgets.size()+1;i++){
      if(i==widgets.size()){
         break;
  }
 
       if( mouseX   >=widgets[i].locX   &&   mouseX   <=widgets[i].locX+widgets[i].sizeX &&
             mouseY  >=widgets[i].locY   &&   mouseY  <=widgets[i].locY+widgets[i].sizeY){
      widgetSelect=i;
    color(0,widgets[widgetSelect].index,colorMult(widgets[widgetSelect].color,0.8f));
    break;
       }
     }
 
    }
};
   
struct gridOld : virtual shapesOld{
 
     int mapSize = 50, mapX = 8, mapY = 8;
     int gridStart=-1,gridEnd=-1;
     
 void begin( ) {
     gridStart = int(verticies.size());
         for (int x = 0; x < mapX*mapY; x++) {
              rectangle(float(x % mapX * mapSize), float(x / mapX * mapSize), float(mapSize - 1), float(mapSize - 1));
         }
     gridEnd = int(verticies.size());
     windows::begin( );
 }
 
 };  
 
 struct player : virtual shapes
 {
     int playerObj;
     
 void begin() {
     windows::begin();
      playerObj = int(objects.size());
      objects.resize(playerObj+1);
      triangle(objects[playerObj].locX,objects[playerObj].locY,objects[playerObj].size);
      objects[playerObj].shapeIndex = int(triangles.size() - 3);
 
 } 
 
 void update()
 {
     shapes::update();
 
             if(keys[SDL_SCANCODE_W]){
                                        translate(1,0,0,playerObj );
        }
            if(keys[SDL_SCANCODE_S]){
                                        translate(-1,0,0,playerObj);
         }
            if(keys[SDL_SCANCODE_A]){
                                        translate(-1,0,1,playerObj);
         }
            if(keys[SDL_SCANCODE_D])
   {
                                        translate(1,0,1,playerObj);
      }
              if(keys[SDL_SCANCODE_Q]){
                                        translate(-0.3f,1,0,playerObj);
  }
  if(keys[SDL_SCANCODE_E]){
                                        translate( 0.3f,1,0,playerObj);
        }
 
 }
 
 };
 
 struct topDown : virtual grid, player{
     void begin(){
     grid::begin();
     player::begin();
 
     }
 
     void update(){
         player::update();
 
         float vRayStartX=objects[playerObj].locX, vRayStartY=objects[playerObj].locY;
 				
         float vRayDirX = sqrt(1 + (objects[playerObj].dy / objects[playerObj].dx) * (objects[playerObj].dy /objects[playerObj].dx));                                               
  	    float vRayDirY = sqrt(1 + (objects[playerObj].dx / objects[playerObj].dy) * (objects[playerObj].dx /objects[playerObj].dy));
 
 		
 		 
 
 		float vRayUnitStepSizeX = sqrt(1 + (vRayDirY / vRayDirX) * (vRayDirY / vRayDirX)); 
         float vRayUnitStepSizeY = sqrt(1 + (vRayDirX / vRayDirY) * (vRayDirX / vRayDirY)) ;
 
 		int vMapCheckX = int(vRayStartX),vMapCheckY = int(vRayStartY);
 
 		float vRayLength1DX,vRayLength1DY;
 		int vStepX, vStepY;
 
 		if (vRayDirX < 0)
 		{
 			vStepX = -1;
 			vRayLength1DX = (vRayStartX - float(vMapCheckX)) * vRayUnitStepSizeX;
 		}
 		else
 		{
 			vStepX = 1;
 			vRayLength1DX = (float(vMapCheckX + 1) - vRayStartX) * vRayUnitStepSizeX;
 		}
         
 		if (vRayDirY < 0)
 		{
 			vStepY = -1;
 			vRayLength1DY = (vRayStartY - float(vMapCheckY)) * vRayUnitStepSizeY;
 		}
 		else
 		{
 			vStepY = 1;
 			vRayLength1DY = (float(vMapCheckY + 1) - vRayStartY) * vRayUnitStepSizeY;
 		}
 
 		bool bTileFound = false;
 		float fMaxDistance = 100.0f;
 		float fDistance = 0.0f;
 		while (!bTileFound && fDistance < fMaxDistance)
 		{
 			if (vRayLength1DX < vRayLength1DY)
 			{
 				vMapCheckX += vStepX;
 				fDistance = vRayLength1DX;
 				vRayLength1DX += vRayUnitStepSizeX;
 			}
 			else
 			{
 				vMapCheckY += vStepY;
 				fDistance = vRayLength1DY;
 				vRayLength1DY += vRayUnitStepSizeY;
 			}
 
 			if (vMapCheckX >= 0 && vMapCheckX < mapX && vMapCheckY >= 0 && vMapCheckY < mapY)
 			{
 				 if (vecMap[vMapCheckY * mapX + vMapCheckX] == 1)
 				 {
 				 	bTileFound = true;
 				 }
 			}
 		}
 
 		float vIntersectionX,vIntersectionY;
 		if (bTileFound)
 		{
 		vIntersectionX = vRayStartX + vRayDirX * fDistance;
          vIntersectionY = vRayStartY + vRayDirY * fDistance;
 		}
 
     }
  
 
};

struct paintOld : virtual gridOld, virtual uiOld {
  
 struct tile{
 int x,y,type;
 };
 
 float panX=0,panY=0;
 
 std::vector <tile> tiles;
     int colorSelect = 3;
     int shadeSelect =0;
      std::fstream map;
 
      int loadBox=-1;
 
 void begin( ){
 grid::begin( );
 
 tiles.resize(mapY*mapX+mapX);
 
 for (int i=0;i<tiles.size();i++){
      tiles[i].x=i%mapX;
      tiles[i].y=i/mapX;
 }
 
 for(int i=gridStart;i<gridEnd;i++){
     verticies[i].color = colors[0];
 }
 
  rectangle(0, 0, float(monitorX), 120, colors[2]);
 createWidget(22, 15, float(mapSize/1.25), float(mapSize/1.25), colors[colorSelect]);
 
 for(int i = 0;i<8;i++)
 {
     createWidget((i + 2) * mapSize / 1.5f, 15.0f, mapSize / 1.5f, mapSize / 1.5f,colors[int(i * 3)] );
 }
 
 createWidget( monitorX * .75f, 19.0f, float(mapSize), float(mapSize / 1.25),colors[3]);
 
 createWidget( monitorX * .88f, 19.0f, float(mapSize), float(mapSize / 1.25),colors[4]);
 
 }
 
 
 void update(){
     shapes::update();
 
    if(keys[SDL_SCANCODE_W]){
    for(int i=gridStart;i<gridEnd;i++){
    verticies[i].position.y+=deltaTime;
        panY=verticies[gridStart].position.y;
 
    }
    }
    if(keys[SDL_SCANCODE_S]){
       for(int i=gridStart;i<gridEnd;i++){
    verticies[i].position.y-=deltaTime;
           panY=verticies[gridStart].position.y;
 
    }
    }
    if(keys[SDL_SCANCODE_A]){
       for(int i=gridStart;i<gridEnd;i++){
    verticies[i].position.x+=deltaTime;
          panX=verticies[gridStart].position.x;
 
    }
    }
    if(keys[SDL_SCANCODE_D]){
       for(int i=gridStart;i<gridEnd;i++){
    verticies[i].position.x-=deltaTime;
           panX=verticies[gridStart].position.x;
 
    }
    }
    if(keys[SDL_SCANCODE_Z]){
    
    }
    if(keys[SDL_SCANCODE_C]){
    
    }
    if(keys[SDL_SCANCODE_Q]){
    
    }
    if(keys[SDL_SCANCODE_E]){
    
    }
 
 }
 
 void colorSelecting(){
   verticies[widgets[0].index].color=colors[colorSelect+shadeSelect];
                for(int i =0;i<6;i++){
              verticies[widgets[0].index+i].color=colors[colorSelect+shadeSelect];
          }
                widgets[0].color=colors[colorSelect+shadeSelect];
      }
 
 void mouseClick(){
     if(widgetSelect==0 ){
         shadeSelect = (1 + shadeSelect)%3;
             colorSelecting();
 
     }
 
      if(widgetSelect>=1 && widgetSelect<=8){
            colorSelect = (widgetSelect - 1) * 3;
           colorSelecting();
      }
 
 if(widgetSelect==9){
          map.open("saves\\map.map",std::ofstream::out |std::ofstream::trunc);
 
          for(int i =0;i<tiles.size();i++){
          map << tiles[i].type ;
          if(i!=tiles.size()-1){
           map<< ",";
          }
          if(i%mapX==mapX-1){
          map << "\n";
          }}
  map.close();
 }
 
 if(widgetSelect==10){
     for(int i=0;i<6;i++){
     if(verticies[loadBox+i].color. a==0){
         verticies[loadBox+i].color.a=255;
     }else {                    
     verticies[loadBox+i].color    .a=0;
     }
     }
 }
 }
 
 void events(){
 ui::events();
 
 if(mouse[SDL_BUTTON_LEFT]&&widgetSelect==-1){
    
        int x = int(mouseX-panX) / mapSize, y = int(mouseY - panY) / mapSize;
 
     for(int i =0;i<6;i++){
         int j = ((y * mapX + x) * 6 + i);
         if(j>=gridStart && j<gridEnd && x>=0 && x<mapX){
             tiles[j/6].type = colorSelect+shadeSelect;
             verticies[j].color = colors[colorSelect+shadeSelect];
         } }
 
     }
 }
 

};

int mainOld( int argc, char** argv )
{
 shapesOld engine;

     getArgc=argc; getArgv=argv;
  
     engine.begin( ); 

         while( running ) {

              while( SDL_PollEvent( &event ) )
              {  engine.events(); 
              if(event.type==SDL_MOUSEBUTTONDOWN && engine.button==SDL_BUTTON_LEFT){
                  engine.mouseClick();
                  }               
                    }
        engine.update();
         SDL_RenderPresent( renderer );
     }
        
    engine.quit();

    return 0;
}
