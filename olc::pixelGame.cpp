//using the PixelGameEngine.h from: https://github.com/OneLoneCoder/olcPixelGameEngine
//shapes doesnt work


//  shape-30Jan2024, topDown 3Feb024, start-28Jan024, mode7-28Jan2024, race-29Jan2024, picture-10feb2024, ppuzzle-14feb2024
#define OLC_PGE_APPLICATION
#include "assets.h"

int width=222,height=155, pixS=3;
float speed;

int mapX=16,mapY=16,mapSize=16;

float degrees(float degrees)
{
    return(degrees * (3.141592/180));
}

  std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> ran(0.0f, 155.0f);

 //Shape

 struct shape : public olc::PixelGameEngine
 {
 
 
 	shape()
 	{
 		sAppName = "test";
 		
 	}
 	
 	virtual bool OnUserCreate()
 	{
 	for (int i=0;i<shapes.size();i++){
 	shapes[i].loc.x=ran(gen);
 		shapes[i].loc.y=ran(gen);
 			shapes[i].rot=ran(gen);
 	shapes[i].begin();}
 	
 		return true;}
 
 	virtual bool OnUserUpdate(float fElapsedTime)
 	{
 		speed=1000*fElapsedTime;
 		Clear(olc::BLACK);
 
 	for(int i=0;i<shapes.size();i++){
 		for(int j=0;j<shapes[i].tris.size();j++){
 	DrawTriangle(shapes[i].tris[j].p[0].x, shapes[i].tris[j].p[0].y,
 				shapes[i].tris[j].p[1].x,  shapes[i].tris[j].p[1].y,
 			   	shapes[i].tris[j].p[2].x,  shapes[i].tris[j].p[2].y);
 	} }
 
 	if(GetKey(olc::W).bHeld){
 		transform({0,-speed/2,0},0,1);
 	
 	}
 
 	if(GetKey(olc::S).bHeld){
 	transform({0,speed/2,0});
 	}
 
 		if(GetKey(olc::A).bHeld){
 	transform({-speed/2,0,0});
 	}
 
 	if(GetKey(olc::D).bHeld){
 	transform({speed/2,0,0});
 	}
 	
 		if(GetKey(olc::Q).bHeld){
 	transform({0,0,0},-speed/10);
 	}
 		
 		if(GetKey(olc::E).bHeld){
 	transform({0,0,0},speed/10);
 	}
 
 
 		if(GetKey(olc::Z).bHeld){
 	transform({0,0,0},0,1-speed/1000);
 	}
 
 	if(GetKey(olc::C).bHeld){ 
 	transform({0,0,0},0,1+speed/1000);
 
 	}
 	
 
 
 	return true;
 }
 
 };

 // topDown

 struct topDown : public olc::PixelGameEngine
 {
 	
 	struct vec3{
 	float x,y,z;
 	};
 	
 	int tiles[1];
 	
 	struct object{
 		float x=33,y=33,size=15;
 		float angle=90,dx,dy;
 		float xPoints[3]={x,x+size,x-size}; float yPoints[3]={y,y+size,y+size};
 	
 		void translate(float val1=0,int set=0,int val2 =0){
 		val1 *= speed; 
 			if(set==0){
 	
 			dx = val2==0 ? cos(degrees(-angle)) * speed/15 : sin (degrees(angle)) * speed/15;
 			dy = val2==0 ? sin(degrees(-angle)) * speed/15 : cos (degrees(angle)) * speed/15;
 			dx*=val1; dy*=val1;
 	
 			xPoints[0]+=dx;	xPoints[1]+=dx;	xPoints[2]+=dx;
 			yPoints[0]+=dy;	yPoints[1]+=dy;	yPoints[2]+=dy;
 			x=xPoints[0]; y=yPoints[0];
 			}
 			if(set==1){
 			angle=fmod(val1+angle,360);
 		angle=	angle < 0 ? 360+angle : angle;
 	
 		    	for(int i=1;i<3;i++){
 			rotate(x,y,xPoints[i],yPoints[i],-val1,i);
 			}
 			}
 			
 		}
 		void rotate(float cx,float cy,float val1, float val2,float rot,int index)
 	{
 	  float s = sin(degrees(rot));
 	  float c = cos(degrees(rot));
 	
 	//     translate point back to origin:
 	  val1 -= cx;
 	  val2 -= cy;
 	
 	  //   rotate point
 	  float xnew = val1 * c - val2 * s;
 	  float ynew = val1 * s + val2 * c;
 	
 	 //    translate point back:
 	  xPoints[index] = xnew + cx;
 	  yPoints[index] = ynew + cy;
 	}
 	
 	};
 	object player;
 	
 	
 	void rayUpda()
 	{
 		float rayStartX = player.x, rayStartY = player.y;
 
 	float rayUnitX = sqrt(1 + (player.dy / player.dx) * (player.dy / player.dx));
 	float rayUnitY = sqrt(1 + (player.dx / player.dy) * (player.dx / player.dy));
 
 	int mapCheckX = rayStartX, mapCheckY = rayStartY;
 	float rayLengthX, rayLengthY;  
 
 	int stepX, stepY;
 
 	if (player.dx < 0)
 		{
 			stepX = -1;
 			rayLengthX = (rayStartX - float(mapCheckX)) * rayUnitX;
 		}
 		else
 		{
 			stepX = 1;
 			rayLengthX = (float(mapCheckX + 1) - rayStartX) * rayUnitX;
 		}
 
 		if (player.dy < 0)
 		{
 			stepY = -1;
 			rayLengthY = (rayStartY - float(mapCheckY)) * rayUnitY;
 		}
 		else
 		{
 			stepY = 1;
 			rayLengthY = (float(mapCheckY + 1) - rayStartY) * rayUnitY;
 		}
 			bool tileFound = false;
 		float maxDistance = 100.0f;
 		float distance = 0.0f;
 		while (!tileFound && distance < maxDistance)
 		{
// Walk along shortest path
 			if (rayLengthX < rayLengthY)
 			{
 				mapCheckX += stepX;
 				distance = rayLengthX;
 				rayLengthX += rayUnitX;
 			}
 			else
 			{
 				mapCheckY += stepY;
 				distance = rayLengthY;
 				rayLengthY += rayUnitY;
 			}
 			//   Test tile at new test point
 			if (mapCheckX >= 0 && mapCheckX < mapX && mapCheckY >= 0 && mapCheckY < mapY)
 			{
 				if (tiles[mapCheckY * mapX + mapCheckX] == 1)
 				{
 					tileFound = true;
 				}
 			}
 		
 		}
 		//	  Calculate intersection location
 		float interX, interY;
 		if (tileFound)
 		{
 			interX = rayStartX + player.dx * distance;
 			interY = rayStartY + player.dy * distance;
 		}
 
 	}
 
 	void triangle(float val1[3],float val2[2])
 	{
 	FillTriangle(val1[0],val2[0],
 		         val1[1],val2[1],
 		         val1[2],val2[2],
 		olc::RED);
 	}
 
 	topDown()
 	{
 		sAppName = "test";
 	}
 
 	virtual bool OnUserCreate()
 	{
 
 		return true;}
 
 	virtual bool OnUserUpdate(float fElapsedTime)
 	{
 
 		speed=1000*fElapsedTime;
 		Clear(olc::BLACK);
 		for(int x=0;x<mapX;x++){
 			for(int y=0;y<mapY;y++)
 			{		FillRect(x*mapSize+1,y*mapSize
 				+1,mapSize-2,mapSize-2
 				,olc::WHITE);
 			}}
 
 		triangle(player.xPoints,player.yPoints);
 		rayUpda();
 
 	if(GetKey(olc::W).bHeld){ player.translate(1,0); 	}
 	if(GetKey(olc::S).bHeld){ player.translate(-1,0); 	}
 	if(GetKey(olc::A).bHeld){ player.translate(-1,0,1); 	}
 	if(GetKey(olc::D).bHeld){ player.translate(1,0,1);  }
 	if(GetKey(olc::E).bHeld){ player.translate(-.3,1);}
 	if(GetKey(olc::Q).bHeld){ player.translate( .3,1);}
 	
 		
 
 	return true;}
 
 };

// start

 struct start : public olc::PixelGameEngine
 {
 	start()
 	{
 		sAppName = "test";
 	}
 
 	virtual bool OnUserCreate()
 	{
 		
 		return true;}
 	virtual bool OnUserUpdate(float fElapsedTime)
 	{
 	Clear(olc::BLACK);
  speed=1000*fElapsedTime;
  
 	return true;}
 
 };

// mode7

 class mode7 : public olc::PixelGameEngine
 {
  	 
 public:
 	mode7()
 	{
 		sAppName = "Pseudo 3D Planes";
 	}
 
 
 private:
 	float fWorldX = 1000.0f;
 	float fWorldY = 1000.0f;
 	float fWorldA = 0.1f;
 	float fNear = 0.005f;
 	float fFar = 0.03f;
 	float fFoVHalf = 3.14159f / 4.0f;
 
 	olc::Sprite *sprGround;
 	olc::Sprite *sprSky;
 
 	int nMapSize = 1024;
 
 protected:
 	virtual bool OnUserCreate()
 	{
 	//	  Create a large sprite and fill it with horizontal and vertical lines
 		sprGround = new olc::Sprite(nMapSize, nMapSize);
 			sprSky = new olc::Sprite(nMapSize, nMapSize);
 		for (int x = 0; x <= nMapSize; x += 32)
 		{
 			for (int y = 0; y < nMapSize; y++)
 			{
 				sprGround->SetPixel(x, y, olc::MAGENTA);
 			
 
 				sprGround->SetPixel(x+1, y, olc::MAGENTA);
 
 				sprGround->SetPixel(x-1, y, olc::MAGENTA);
 
 				sprGround->SetPixel(y, x, olc::BLUE);
 
 				sprGround->SetPixel(y, x+1, olc::BLUE);
 
 				sprGround->SetPixel(y, x-1, olc::BLUE);
 			}
 		}
 
 
 		return true;
 	}
 
 	virtual bool OnUserUpdate(float fElapsedTime)
 	{
 		
 		//  Control rendering parameters dynamically
 		if (GetKey(olc::Key::Q).bHeld) fNear += 0.1f * fElapsedTime;
 		if (GetKey(olc::Key::A).bHeld) fNear -= 0.1f * fElapsedTime;
 
 		if (GetKey(olc::Key::W).bHeld) fFar += 0.1f * fElapsedTime;
 		if (GetKey(olc::Key::S).bHeld) fFar -= 0.1f * fElapsedTime;
 
 		if (GetKey(olc::Key::Z).bHeld) fFoVHalf += 0.1f * fElapsedTime;
 		if (GetKey(olc::Key::X).bHeld) fFoVHalf -= 0.1f * fElapsedTime;
 
 
 		//  Create Frustum corner points
 		float fFarX1 = fWorldX + cosf(fWorldA - fFoVHalf) * fFar;
 		float fFarY1 = fWorldY + sinf(fWorldA - fFoVHalf) * fFar;
 
 		float fNearX1 = fWorldX + cosf(fWorldA - fFoVHalf) * fNear;
 		float fNearY1 = fWorldY + sinf(fWorldA - fFoVHalf) * fNear;
 
 		float fFarX2 = fWorldX + cosf(fWorldA + fFoVHalf) * fFar;
 		float fFarY2 = fWorldY + sinf(fWorldA + fFoVHalf) * fFar;
 
 		float fNearX2 = fWorldX + cosf(fWorldA + fFoVHalf) * fNear;
 		float fNearY2 = fWorldY + sinf(fWorldA + fFoVHalf) * fNear;
 
 		 // Starting with furthest away line and work towards the camera point
 		for (int y = 0; y < ScreenHeight() / 2; y++)
 		{
 			//  Take a sample point for depth linearly related to rows down screen
 			float fSampleDepth = (float)y / ((float)ScreenHeight() / 2.0f);		
 
 			//  Use sample point in non-linear (1/x) way to enable perspective
 			//  and grab start and end points for lines across the screen
 			float fStartX = (fFarX1 - fNearX1) / (fSampleDepth) + fNearX1;
 			float fStartY = (fFarY1 - fNearY1) / (fSampleDepth) + fNearY1;
 			float fEndX = (fFarX2 - fNearX2) / (fSampleDepth) + fNearX2;
 			float fEndY = (fFarY2 - fNearY2) / (fSampleDepth) + fNearY2;
 
 			//  Linearly interpolate lines across the screen
 			for (int x = 0; x < ScreenWidth(); x++)
 			{
 				float fSampleWidth = (float)x / (float)ScreenWidth();
 				float fSampleX = (fEndX - fStartX) * fSampleWidth + fStartX;
 				float fSampleY = (fEndY - fStartY) * fSampleWidth + fStartY;
 
 				  Wrap sample coordinates to give "infinite" periodicity on maps
 				fSampleX = fmod(fSampleX, 1.0f);
 				fSampleY = fmod(fSampleY, 1.0f);
 
 				  Sample symbol and colour from map sprite, and draw the
 				  pixel to the screen
 				olc::Pixel col = sprGround->Sample(fSampleX, fSampleY);
 				Draw(x, y + (ScreenHeight() / 2), col);		
 
 				  Sample symbol and colour from sky sprite, we can use same
 				  coordinates, but we need to draw the "inverted" y-location
 				col = sprSky->Sample(fSampleX, fSampleY);
 				Draw(x, (ScreenHeight() / 2) - y, col);
 			}
 		}
 
 		 // Draw a blanking line to fill the gap between sky and ground
 		DrawLine(0, ScreenHeight() / 2, ScreenWidth(), ScreenHeight() / 2,  olc::CYAN);
 
 		//  Handle user navigation with arrow keys
 		if (GetKey(olc::Key::LEFT).bHeld)
 			fWorldA -= 1.0f * fElapsedTime;
 
 		if (GetKey(olc::Key::RIGHT).bHeld)
 			fWorldA += 1.0f * fElapsedTime;
 
 		if (GetKey(olc::Key::UP).bHeld)
 		{
 			fWorldX += cosf(fWorldA) * 0.2f * fElapsedTime;
 			fWorldY += sinf(fWorldA) * 0.2f * fElapsedTime;
 		}
 
 		if (GetKey(olc::Key::DOWN).bHeld)
 		{
 			fWorldX -= cosf(fWorldA) * 0.2f * fElapsedTime;
 			fWorldY -= sinf(fWorldA) * 0.2f * fElapsedTime;
 		}
 
 		return true;
 	}
 
 
 
 }; 

// race

 struct race : public olc::PixelGameEngine
 {
 	int segL = 200;  segment length
 	
 
 struct Line
 {
 	  int roadW = 2000;
   float x,y,z;  3d center of line
   float X,Y,W;  screen coord
   float curve,spriteX,clip,scale;
  
   	int width1 = 333;
 	int height1 = 222;
 	 float camD = 0.84;  camera depth
   Line()
   {spriteX=curve=x=y=z=0;}
 
   void project(int camX,int camY,int camZ)
   {
 	 
 
     scale = camD/(z-camZ);
     X = (1 + scale*(x - camX)) * width1/2;
     Y = (1 - scale*(y - camY)) * height1/2;
     W = scale * roadW  * width/2;
   }
 
 };
 
 	void drawQuad( int x1,int y1,int w1,int x2,int y2,int w2, olc::Pixel col)
 {
 	FillTriangle(x1-w1,y1,x2-w2,y2,x2+w2,y2,col);
 			FillTriangle(x1-w1,y1,x2+w2,y2,x1+w1,y1,col);
 }
 	 std::vector<Line> lines;
 
 
 	 int N;	 
    float playerX = 0;
    float curve =0.5f;
    int pos = 0;
    int H = 2000;
    int hill=-2000;
 
 	race()
 	{
 		sAppName = "test";
 	}
 
 
 	
 	Line p;
 
 	virtual bool OnUserCreate()
 	{
 		  for(int i=0;i<1600;i++)
      {
        Line line;
        line.z = i*segL;
 
        if (i>300 && i<700) line.curve=curve;
        if (i>1100) line.curve=curve;
 	
        if (i>750) line.y = sin(i/30.0)*hill;
 
        lines.push_back(line);
      }
 
 
 	   N = lines.size();
 		return true;}
 
 	virtual bool OnUserUpdate(float fElapsedTime)
 	{
 	Clear(olc::BLACK);
 	 int startPos = pos/segL;
 	   int camH = lines[startPos].y + H;
 
 	     int maxy = height;
   float x=0,dx=0;
 
   
 	  int speed=0;
 
 	if (GetKey(olc::RIGHT).bHeld) playerX += 0.1;
   if (GetKey(olc::LEFT).bHeld)    playerX-=0.1;
   if (GetKey(olc::UP).bHeld)    speed=200;
   if (GetKey(olc::DOWN).bHeld)    speed=-200;
   if (GetKey(olc::TAB).bHeld)    speed*=3;
   if (GetKey(olc::W).bHeld)    H+=100;
   if (GetKey(olc::S).bHeld)    H-=100;
 
 
 
     pos+=speed;
   while (pos >= N*segL) pos-=N*segL;
   while (pos < 0) pos += N*segL;
 
 
 
 
 	for(int n = startPos; n<startPos+300; n++)  
    {
     Line &l = lines[n%N];
     l.project(playerX*l.roadW-x, camH, startPos*segL - (n>=N?N*segL:0));
 	   x+=dx;
     dx+=l.curve;
 	
 	  l.clip=maxy;
     if (l.Y>=maxy) continue;
     maxy = l.Y;
 
 	
 		 olc::Pixel grass  = (n/3)%2?olc::Pixel{16,200,16}:olc::Pixel{0,154,0};
 		  olc::Pixel rumble = (n/3)%2?olc::Pixel{255,255,255}:olc::Pixel{0,0,0};
 	   olc::Pixel road = (n / 3) % 2 ? olc::Pixel{107, 107, 107} : olc::Pixel{ 105,105,105};
 	
 	   Line p = lines[(std::max(n-1,0))%N]; 
 
 
   drawQuad( 0, p.Y, width, 0, l.Y, width,grass);
 drawQuad(p.X, p.Y, p.W*1.2, l.X, l.Y, l.W*1.2,rumble);
 drawQuad( p.X, p.Y, p.W, l.X, l.Y, l.W,road);
 	 }
 
 	return true;}
 
 };

// picture

 struct picture : public olc::PixelGameEngine
 {
 	float panX=width/10, panY=height/5, scale=.5, rotate=0.0f;
 		int currTileX,currTileY;
 		olc::Pixel colors[12]={olc::BLACK,olc::WHITE};
 		int colorSelect = 1;
 		int centerX, centerY;
 
 	struct tile{
 	int color=0; 
 	int x,y;
 	};
 	std::vector<tile> tiles;
 
 	picture()
 	{
 		sAppName = "test";
 	}
 	
 	virtual bool OnUserCreate()
 	{
 		tiles.resize(mapY*mapX);
 		
 		for(int i=0;i<tiles.size();i++)
 		{
 		tiles[i].y=i/mapX;
 		tiles[i].x=i%mapX;
 		}
 		
 		centerX = mapX*mapSize/-2;
 		centerY = mapY*mapSize/-2;
 		return true;}
 
 	virtual bool OnUserUpdate(float fElapsedTime)
 	{
 		Clear(olc::BLACK);
 	speed=1000*fElapsedTime;
 	int findX = int((GetMouseX() - panX) /scale 	);
 	int findY = int((GetMouseY() - panY)	/ scale);
 		
 
 		if(findX >=0 && findX < mapX*mapSize && findY >= 0 && findY < mapY*mapSize){
 
 		findX = findX / mapSize;
 		findY = findY  / mapSize * mapX;
 		int find = findY + findX;
 	tile currTile = tiles[find];
 		FillRect(find%mapX*mapSize *scale +panX,find/mapY*mapSize*scale+panY,mapSize*scale,mapSize*scale,olc::GREY);
 	
 		if (GetMouse(0).bHeld){
 			tiles[find].color=colorSelect;}
 		}
 	
 
 		for(int i=tiles.size()-1;i>=0;i--){
 						FillRect(i%mapX*mapSize *scale +panX, i/mapX*mapSize * scale + panY, mapSize * scale+1, mapSize * scale+1,colors[tiles[i].color]);
 	}
 
 		DrawRect(panX+centerX,panY+centerY,mapX*mapSize*scale,mapY*mapSize*scale,olc::GREY);
 		FillRect(10,10,10,10,colors[colorSelect]);
 		DrawRect(10,10,10,10,olc::GREY);
 		
 
 		if(GetKey(olc::A).bHeld){panX+=0.1*speed;}
 		if(GetKey(olc::D).bHeld){panX+=-0.1*speed;}
 		if(GetKey(olc::W).bHeld){panY+=0.1*speed;}
 		if(GetKey(olc::S).bHeld){panY+=-0.1*speed;}
 		if(GetKey(olc::Z).bHeld){scale*=1-0.001*speed;}
 		if(GetKey(olc::C).bHeld){scale*=1+0.001*speed;}
 
 
 	return true;}
 
 };

// cards

struct cards : public olc::PixelGameEngine
{
	olc::Pixel background = (11,66,33);

	olc::Pixel pixMult(float x=0.0f,float y=0.0f,float z=0.0f){
	
		return ;
	}

	void slot(int x,int y){
	DrawRect(x,y,mapSize,mapSize,background);
	}

	cards()
	{
		sAppName = "puzzle";
	}

	virtual bool OnUserCreate()
	{
		
		return true;}
	virtual bool OnUserUpdate(float fElapsedTime)
	{
	Clear(background);
 speed=1000*fElapsedTime;
 

	return true;}

};

int main()
{
	start game;
	game.Construct(width, height, pixS, pixS);
	game.Start();
	return 0;
}
