#define SDL_MAIN_HANDLED

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_gpu.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>




typedef struct{
  float x;
  float y;
  float acelX;
  float acelY;
  unsigned int ratio;
  float rads;
  unsigned int life;
  SDL_bool active;
}AlienStruct;

typedef struct{
  float x;
  float y;
  float acelX;
  float acelY;
  unsigned int ratio;
  float rads;
}PlayerStruct;

typedef struct {
  float x;
  float y;
  float acelX;
  float acelY;
  unsigned int ratio;
  float rads;
  unsigned int life;
  unsigned char type;
  SDL_bool active;
  SDL_bool clockwise;
} AsteroidStruct;

typedef struct {
  float x;
  float y;
  float acelX;
  float acelY;
  SDL_bool active;
  SDL_bool player;
} BulletStruct;

typedef struct {
  float x;
  float y;
  float ratio;
  float ratioMax;
  unsigned char rAngle;
  SDL_bool active;
} ExplosionStruct;

typedef struct {
  unsigned int Asteroid;
  unsigned int Bullet;
  SDL_bool isBomb;
  SDL_bool active;
} queueHitStruct;

typedef struct {
  unsigned char idType;
  unsigned int indexType;
} VsStruct;

typedef struct {
  unsigned int x;
  unsigned int y;
  float ratio;
  SDL_bool augment;
  SDL_bool active;

} BombStruct;

typedef struct {
  unsigned int x;
  unsigned int y;
  float ratio;
  SDL_bool augment;
  SDL_bool active;
} PowerStruct;

#define SDL_GPU_USE_BUFFER_MAPPING 1
#define AsteroidLimit 1500
#define limitBullet 100000
#define limitAsteroids 100000
#define limitExplosions 100000
#define limitQueueHit 1000000
#define idAlien 248
#define idPlayerB 249
#define idPower 250
#define idBomb 251
#define idExplosion 252
#define idAsteroid 253
#define idPlayer 254
#define idBullet 255

GPU_Target* renderer;

GPU_Rect rectangulo;
GPU_Rect rectGO;
GPU_Rect rectGOb;

SDL_Color White = {255, 255, 255, 255};
SDL_Color Black = {0, 0, 0, 255};

const float pi = 3.14159;
const float twoPi = 6.28318;
const float halfPi = 1.570795;
const float quarterPi = 0.7853975;
const float threePidivtwo = 4.712385;
const unsigned int limitX = 1280;
const unsigned int limitY = 720;
const int SCREEN_FPS = 60;
int SCREEN_TICKS_PER_FRAME;
Uint32 aTick;
Uint32 bTick;
Uint32 cTick;
Uint32 dTick;


unsigned char retardo = 10;
unsigned char maxFreqBullet = 1;
unsigned char maxFreqBBullet = 1;
unsigned char heat = 0;
unsigned char heatB = 0;

AlienStruct Alien;
PlayerStruct Player;
PlayerStruct PlayerB;
BombStruct Bomb;
PowerStruct Power;
unsigned char playerRatio = 10;
unsigned char playerBombs = 5;
unsigned char playerLives = 3;
unsigned int playerScore = 0;
unsigned char playerPower = 1;
unsigned char playerBRatio = 10;
unsigned char playerBBombs = 0;
unsigned char playerBLives = 0;
unsigned int playerBScore = 0;
unsigned char playerBPower = 1;

 


unsigned int indexBullet = 0;
unsigned int indexAsteroids = 0;
unsigned int indexExplosions = 0;
unsigned int indexQueueHit = 0;
unsigned int contador = 0;
unsigned int z = 0;
unsigned int v = 0;
unsigned int floodWatch = 0;
float t = 0;
float j;
float propM = -0.1;
float propMB = -0.1;
unsigned char respawnTime = 0;
unsigned char pressedLeft = 0;
unsigned char pressedRight = 0;
unsigned char pressedFire = 0;
unsigned char pressedAccel = 0;
unsigned char pressedBomb = 0;
unsigned int pc = 0;
unsigned int bombCooldown = 0;
unsigned char respawnBTime = 0;
unsigned char pressedBLeft = 0;
unsigned char pressedBRight = 0;
unsigned char pressedBFire = 0;
unsigned char pressedBAccel = 0;
unsigned char pressedBBomb = 0;


char string[80];



SDL_bool quit = SDL_FALSE;
SDL_bool flagsSoundActive = SDL_TRUE;
SDL_bool flagsBombActive = SDL_FALSE;
SDL_bool flagsDead = SDL_FALSE;
SDL_bool flagsBDead = SDL_TRUE;
SDL_bool flagsgetBomb = SDL_FALSE;
SDL_bool flagsgetPower = SDL_FALSE;
SDL_bool flagsgetBBomb = SDL_FALSE;
SDL_bool flagsgetBPower = SDL_FALSE;
SDL_bool flagsGameOver = SDL_TRUE;
SDL_bool flagsFrameSkip = SDL_FALSE;

SDL_Event evento;



Mix_Chunk *die = NULL;
Mix_Chunk *explosion = NULL;
Mix_Chunk *shoot = NULL;
Mix_Chunk *nuke = NULL;
Mix_Chunk *gotBomb = NULL;
Mix_Chunk *propLoop = NULL;
Mix_Chunk *propStart = NULL;
Mix_Chunk *propStop = NULL;
Mix_Chunk *alien = NULL;

TTF_Font *font = NULL;

SDL_Surface* superficie;
SDL_Surface* surfaceGO;
SDL_Surface* surfaceGOb;

GPU_Image* textureGO;
GPU_Image* textureGOb;
GPU_Image* texturaMensaje;


ExplosionStruct *Explosion;
AsteroidStruct *Asteroid;
BulletStruct *Bullet;
queueHitStruct *queueHit;
VsStruct **virtualScreen;


unsigned char getPixel(int x, int y);
void putPixel(int x, int y, unsigned char c, unsigned int index);
void drawLine(int x0, int y0, int x1, int y1, unsigned char color, unsigned int index);
void drawExplosions(char color);
void animateExplosions(void);
void drawAsteroid(int x,int y, float angle, unsigned int ratio, unsigned char color, unsigned int index, unsigned char type);
void generateAsteroid(unsigned int x, unsigned int y, unsigned char quantity, unsigned char ratio);
void Die(void);
void Hit(int bala, int asteroide);
void checkHits(void);
void addHit(int bullet, int asteroid, SDL_bool isBomb);
int collisionDetected(int x, int y, unsigned char c, unsigned int index);
void drawShip(unsigned int x, unsigned int y, float angulo, unsigned int radio,unsigned char color);
void drawBullets(void);
void eraseBullets(void);
void addBullet(SDL_bool player);
void addExplosion(unsigned int x, unsigned int y, unsigned char ratio);
void limitCheck(void);
void movePlayer(void);
void drawAsteroids(unsigned char color);
void generateAsteroids(unsigned char quantity);
void moveAsteroids(void);
int initVideo(void);
void readInputs(void);
void launchBomb(int jugador);
void applyInputs(void);
void endSDL(void);
void initVS(void);
int memoryError(void);
int intro(void);
void playerInit(void);
void gameOver(void);
void drawScores(void);
void otherChecks(void);
void flood(int x,int y, unsigned char fill_col, unsigned char old_col, unsigned int index);
void putPixelb(int x, int y, unsigned char c, unsigned int index);
void drawBomb(unsigned int x, unsigned int y, float angulo, unsigned int radio,unsigned char color);
void addBomb(void);
void getBomb(void);
void drawPower(unsigned int x, unsigned int y, float angulo, unsigned int radio,unsigned char color);
void getPower(void);
void drawProps(unsigned int x, unsigned int y, float angulo, unsigned int radio,unsigned char color);
void initGameOver(void);
int checkSomething(void);
int checkSomethingB(void);
void playerInitB(void);
void drawShipB(unsigned int x, unsigned int y, float angulo, unsigned int radio,unsigned char color);
void drawPropsB(unsigned int x, unsigned int y, float angulo, unsigned int radio,unsigned char color);
void getBBomb(void);
void getBPower(void);
void cleanHitQueue(void);
void hitAlien(int x, int y);















unsigned char getPixel(int x, int y){
	if ( ((x>0) && (y>0)) && ((x<limitX) && (y<limitY)) )		// Some nasty pixels cause array overflow
		return(virtualScreen[x][y].idType);
}


void putPixelb(int x, int y, unsigned char c, unsigned int index){
	if ( ((x>0) && (y>0)) && ((x<limitX) && (y<limitY)) ){		// Some nasty pixels cause array overflow
		virtualScreen[x][y].idType = c;
		virtualScreen[x][y].indexType = index;
		//SDL_SetRenderDrawColor(renderer, c, c, c, SDL_ALPHA_OPAQUE);
	  	//SDL_RenderDrawPoint(renderer, x, y);
	}	
}

void putPixel(int x, int y, unsigned char c, unsigned int index){
	if ( ((x>0) && (y>0)) && ((x<limitX) && (y<limitY)) ){		// Some nasty pixels cause array overflow

		if (c!=idExplosion)
			//if (c!=0) 
				if (getPixel(x,y) != 0)
					if (getPixel(x,y) != c)
						collisionDetected(x,y,c,index);

		if (c!=idExplosion){
			virtualScreen[x][y].idType = c;
			virtualScreen[x][y].indexType = index;
		}	
	}	
}


void flood(int x,int y, unsigned char fill_col, unsigned char old_col, unsigned int index){
	if (x>0)
		if(x<limitX-1)
			if (y>0)
				if (y<limitY-1)
					if (floodWatch < 30000)
						if(getPixel(x,y)==old_col){
							floodWatch++;
							putPixelb(x,y,fill_col,index);
							flood(x+1,y,fill_col,old_col,index);
							flood(x-1,y,fill_col,old_col,index);
							flood(x,y+1,fill_col,old_col,index);
							flood(x,y-1,fill_col,old_col,index);
						}
}




void drawLine(int x0, int y0, int x1, int y1, unsigned char color, unsigned int index){

	if (color == 0)
		GPU_Line(renderer, x0, y0, x1, y1, Black);
	else
		GPU_Line(renderer, x0, y0, x1, y1, White);

	int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
	int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
	int err,e2;

	if (dx>dy)
		err = dx >> 1;
	else
		err = -(dy >> 1);
	
	       
	for(;;){
		putPixel(x0,y0,color,index);
	        if (x0==x1 && y0==y1) break;
		e2 = err;
	        if (e2 >-dx) { err -= dy; x0 += sx; }
		if (e2 < dy) { err += dx; y0 += sy; }
      }





}



void drawExplosions(char color){

	for (contador=0; contador<indexExplosions; contador++){
		if (Explosion[contador].active){


			drawLine(Explosion[contador].x+(Explosion[contador].ratio*cos(twoPi+Explosion[contador].rAngle)), Explosion[contador].y+(Explosion[contador].ratio*sin(twoPi+Explosion[contador].rAngle)), Explosion[contador].x+(Explosion[contador].ratioMax*cos(twoPi+Explosion[contador].rAngle)), Explosion[contador].y+(Explosion[contador].ratioMax*sin(twoPi+Explosion[contador].rAngle)),color,0); // |

			drawLine(Explosion[contador].x+(Explosion[contador].ratio*cos(quarterPi+Explosion[contador].rAngle)), Explosion[contador].y+(Explosion[contador].ratio*sin(quarterPi+Explosion[contador].rAngle)), Explosion[contador].x+(Explosion[contador].ratioMax*cos(quarterPi+Explosion[contador].rAngle)), Explosion[contador].y+(Explosion[contador].ratioMax*sin(quarterPi+Explosion[contador].rAngle)),color,0); // /

			drawLine(Explosion[contador].x+(Explosion[contador].ratio*cos(halfPi+Explosion[contador].rAngle)), Explosion[contador].y+(Explosion[contador].ratio*sin(halfPi+Explosion[contador].rAngle)), Explosion[contador].x+(Explosion[contador].ratioMax*cos(halfPi+Explosion[contador].rAngle)), Explosion[contador].y+(Explosion[contador].ratioMax*sin(halfPi+Explosion[contador].rAngle)),color,0); // -

			drawLine(Explosion[contador].x+(Explosion[contador].ratio*cos(quarterPi+halfPi+Explosion[contador].rAngle)), Explosion[contador].y+(Explosion[contador].ratio*sin(quarterPi+halfPi+Explosion[contador].rAngle)), Explosion[contador].x+(Explosion[contador].ratioMax*cos(quarterPi+halfPi+Explosion[contador].rAngle)), Explosion[contador].y+(Explosion[contador].ratioMax*sin(quarterPi+halfPi+Explosion[contador].rAngle)),color,0); // \

			drawLine(Explosion[contador].x+(Explosion[contador].ratio*cos(pi+Explosion[contador].rAngle)), Explosion[contador].y+(Explosion[contador].ratio*sin(pi+Explosion[contador].rAngle)), Explosion[contador].x+(Explosion[contador].ratioMax*cos(pi+Explosion[contador].rAngle)), Explosion[contador].y+(Explosion[contador].ratioMax*sin(pi+Explosion[contador].rAngle)),color,0); // |

			drawLine(Explosion[contador].x+(Explosion[contador].ratio*cos(pi+quarterPi+Explosion[contador].rAngle)), Explosion[contador].y+(Explosion[contador].ratio*sin(pi+quarterPi+Explosion[contador].rAngle)), Explosion[contador].x+(Explosion[contador].ratioMax*cos(pi+quarterPi+Explosion[contador].rAngle)), Explosion[contador].y+(Explosion[contador].ratioMax*sin(pi+quarterPi+Explosion[contador].rAngle)),color,0); // /


			drawLine(Explosion[contador].x+(Explosion[contador].ratio*cos(threePidivtwo+Explosion[contador].rAngle)), Explosion[contador].y+(Explosion[contador].ratio*sin(threePidivtwo+Explosion[contador].rAngle)), Explosion[contador].x+(Explosion[contador].ratioMax*cos(threePidivtwo+Explosion[contador].rAngle)), Explosion[contador].y+(Explosion[contador].ratioMax*sin(threePidivtwo+Explosion[contador].rAngle)),color,0); // |

			drawLine(Explosion[contador].x+(Explosion[contador].ratio*cos(threePidivtwo+quarterPi+Explosion[contador].rAngle)), Explosion[contador].y+(Explosion[contador].ratio*sin(threePidivtwo+quarterPi+Explosion[contador].rAngle)), Explosion[contador].x+(Explosion[contador].ratioMax*cos(threePidivtwo+quarterPi+Explosion[contador].rAngle)), Explosion[contador].y+(Explosion[contador].ratioMax*sin(threePidivtwo+quarterPi+Explosion[contador].rAngle)),color,0); // |



		}
	}
}

void animateExplosions(void){
	z = 0;	
	for (contador=0; contador<indexExplosions; contador++)
		if (Explosion[contador].active){
			if (Explosion[contador].ratio < Explosion[contador].ratioMax)
				Explosion[contador].ratio += 1;
			else
				Explosion[contador].active = SDL_FALSE;
			z++;
		}	

	if (z == 0)
		indexExplosions = 0;
	

}

void drawAsteroid(int x, int y, float angle, unsigned int ratio, unsigned char color, unsigned int index, unsigned char type){

	switch (type){
		case 0:{
		  drawLine(x+ratio*cos(angle),y+ratio*sin(angle),x+ratio/2*cos(angle),y+ratio/2*sin(angle),color,index);
		  drawLine(x+ratio/2*cos(angle),y+ratio/2*sin(angle),x+ratio*cos(angle+pi+1),y+ratio*sin(angle+pi+1),color,index);
		  drawLine(x+ratio*cos(angle+pi+1),y+ratio*sin(angle+pi+1),x+ratio*cos(angle+pi+0.1),y+ratio*sin(angle+pi+0.1),color,index);
		  drawLine(x+ratio*cos(angle+pi+0.1),y+ratio*sin(angle+pi+0.1),x+ratio/2*cos(angle+pi-0.1),y+ratio/2*sin(angle+pi-0.1),color,index);
		  drawLine(x+ratio/2*cos(angle+pi-0.1),y+ratio/2*sin(angle+pi-0.1),x+ratio*cos(angle+pi-halfPi),y+ratio*sin(angle+pi-halfPi),color,index);
		  drawLine(x+ratio*cos(angle+pi-halfPi),y+ratio*sin(angle+pi-halfPi),x+ratio*cos(angle+halfPi-0.3),y+ratio*sin(angle+halfPi-0.3),color,index);
		  drawLine(x+ratio*cos(angle+halfPi-0.3),y+ratio*sin(angle+halfPi-0.3),x+ratio*cos(angle+halfPi/2),y+ratio*sin(angle+halfPi/2),color,index);
		  drawLine(x+ratio*cos(angle+halfPi/2),y+ratio*sin(angle+halfPi/2),x+ratio*cos(angle),y+ratio*sin(angle),color,index);
		  break;
		}
		case 1:{       
		  drawLine(x+ratio*cos(angle),y+ratio*sin(angle),x+ratio*cos(angle+0.4),y+ratio*sin(angle+0.4),color,index);
		  drawLine(x+ratio*cos(angle+0.4),y+ratio*sin(angle+0.4),x+ratio*cos(angle+0.8),y+ratio*sin(angle+0.8),color,index);
		  drawLine(x+ratio*cos(angle+0.8),y+ratio*sin(angle+0.8),x+ratio*cos(angle+1.2),y+ratio*sin(angle+1.2),color,index);
		  drawLine(x+ratio*cos(angle+1.2),y+ratio*sin(angle+1.2),x+ratio*cos(angle+2),y+ratio*sin(angle+2),color,index);
		  drawLine(x+ratio*cos(angle+2),y+ratio*sin(angle+2),x+ratio*cos(angle+3),y+ratio*sin(angle+3),color,index);
		  drawLine(x+ratio*cos(angle+3),y+ratio*sin(angle+3),x+ratio*cos(angle+4),y+ratio*sin(angle+4),color,index);
		  drawLine(x+ratio*cos(angle+4),y+ratio*sin(angle+4),x+ratio*cos(angle+5),y+ratio*sin(angle+5),color,index);
		  drawLine(x+ratio*cos(angle+5),y+ratio*sin(angle+5),x+ratio*cos(angle+6),y+ratio*sin(angle+6),color,index);
		  drawLine(x+ratio*cos(angle+6),y+ratio*sin(angle+6),x+(ratio-ratio/2)*cos(angle),y+(ratio-ratio/2)*sin(angle),color,index);
		  drawLine(x+(ratio-ratio/2)*cos(angle),y+(ratio-ratio/2)*sin(angle),x+ratio*cos(angle),y+ratio*sin(angle),color,index);
		  break;
	       }  

		case 2:{       
		  drawLine(x+ratio*cos(angle),y+ratio*sin(angle),x+ratio*cos(angle+0.4),y+ratio*sin(angle+0.4),color,index);
		  drawLine(x+ratio*cos(angle+0.4),y+ratio*sin(angle+0.4),x+(ratio-ratio/3)*cos(angle+0.8),y+(ratio-ratio/3)*sin(angle+0.8),color,index);
		  drawLine(x+(ratio-ratio/3)*cos(angle+0.8),y+(ratio-ratio/3)*sin(angle+0.8),x+(ratio-ratio/3)*cos(angle+1.2),y+(ratio-ratio/3)*sin(angle+1.2),color,index);
		  drawLine(x+(ratio-ratio/3)*cos(angle+1.2),y+(ratio-ratio/3)*sin(angle+1.2),x+(ratio-ratio/3)*cos(angle+2),y+(ratio-ratio/3)*sin(angle+2),color,index);
		  drawLine(x+(ratio-ratio/3)*cos(angle+2),y+(ratio-ratio/3)*sin(angle+2),x+(ratio-ratio/1.5)*cos(angle+3),y+(ratio-ratio/1.5)*sin(angle+3),color,index);
		  drawLine(x+(ratio-ratio/1.5)*cos(angle+3),y+(ratio-ratio/1.5)*sin(angle+3),x+(ratio-ratio/1.5)*cos(angle+4),y+(ratio-ratio/1.5)*sin(angle+4),color,index);
		  drawLine(x+(ratio-ratio/1.5)*cos(angle+4),y+(ratio-ratio/1.5)*sin(angle+4),x+(ratio-ratio/1.5)*cos(angle+5),y+(ratio-ratio/1.5)*sin(angle+5),color,index);
		  drawLine(x+(ratio-ratio/1.5)*cos(angle+5),y+(ratio-ratio/1.5)*sin(angle+5),x+(ratio-ratio/1.5)*cos(angle+6),y+(ratio-ratio/1.5)*sin(angle+6),color,index);
		  drawLine(x+(ratio-ratio/1.5)*cos(angle+6),y+(ratio-ratio/1.5)*sin(angle+6),x+(ratio-ratio/2)*cos(angle),y+(ratio-ratio/2)*sin(angle),color,index);
		  drawLine(x+(ratio-ratio/2)*cos(angle),y+(ratio-ratio/2)*sin(angle),x+ratio*cos(angle),y+ratio*sin(angle),color,index);
		  break;
	       }  

		case 3:{       
		  drawLine(x+ratio*cos(angle),y+ratio*sin(angle),x+(ratio-ratio/2)*cos(angle+0.4),y+(ratio-ratio/2)*sin(angle+0.4),color,index);
		  drawLine(x+(ratio-ratio/2)*cos(angle+0.4),y+(ratio-ratio/2)*sin(angle+0.4),x+(ratio-ratio/3)*cos(angle+0.8),y+(ratio-ratio/3)*sin(angle+0.8),color,index);
		  drawLine(x+(ratio-ratio/3)*cos(angle+0.8),y+(ratio-ratio/3)*sin(angle+0.8),x+(ratio-ratio/4)*cos(angle+1.2),y+(ratio-ratio/4)*sin(angle+1.2),color,index);
		  drawLine(x+(ratio-ratio/4)*cos(angle+1.2),y+(ratio-ratio/4)*sin(angle+1.2),x+(ratio-ratio/2)*cos(angle+2),y+(ratio-ratio/2)*sin(angle+2),color,index);
		  drawLine(x+(ratio-ratio/2)*cos(angle+2),y+(ratio-ratio/2)*sin(angle+2),x+(ratio-ratio/6)*cos(angle+3),y+(ratio-ratio/6)*sin(angle+3),color,index);
		  drawLine(x+(ratio-ratio/6)*cos(angle+3),y+(ratio-ratio/6)*sin(angle+3),x+(ratio-ratio/2)*cos(angle+4),y+(ratio-ratio/2)*sin(angle+4),color,index);
		  drawLine(x+(ratio-ratio/2)*cos(angle+4),y+(ratio-ratio/2)*sin(angle+4),x+(ratio-ratio/8)*cos(angle+5),y+(ratio-ratio/8)*sin(angle+5),color,index);
		  drawLine(x+(ratio-ratio/8)*cos(angle+5),y+(ratio-ratio/8)*sin(angle+5),x+(ratio-ratio/9)*cos(angle+6),y+(ratio-ratio/9)*sin(angle+6),color,index);
		  drawLine(x+(ratio-ratio/9)*cos(angle+6),y+(ratio-ratio/9)*sin(angle+6),x+(ratio-ratio/2)*cos(angle),y+(ratio-ratio/2)*sin(angle),color,index);
		  drawLine(x+(ratio-ratio/2)*cos(angle),y+(ratio-ratio/2)*sin(angle),x+ratio*cos(angle),y+ratio*sin(angle),color,index);
		  break;
	       }  


	}		       

	if (color != 0){
		floodWatch = 0;
		flood (x,y,color,0,index);
	}		
	else{
		floodWatch = 0;
		flood (x,y,0,idAsteroid,index);
	}
}


void generateAsteroid(unsigned int x, unsigned int y, unsigned char quantity, unsigned char ratio){
	if (indexAsteroids < AsteroidLimit){		
		for (contador = indexAsteroids; contador < (indexAsteroids+quantity); contador++){
			Asteroid[contador].x = x;
			Asteroid[contador].y = y;
	
			switch (rand () % 8){
				case 0:	Asteroid[contador].acelX = ((rand () % 1)+1/rand () % 4)+0.1; break;
				case 1:	Asteroid[contador].acelX = ((rand () % 1)+1/rand () % 4)-0.1; break;
				case 2:	Asteroid[contador].acelX = ((rand () % 1)+1/rand () % 4)+0.25; break;
				case 3:	Asteroid[contador].acelX = ((rand () % 1)+1/rand () % 4)-0.25; break;
				case 4:	Asteroid[contador].acelX = ((rand () % 1)+1/rand () % 4)+0.5; break;
				case 5:	Asteroid[contador].acelX = ((rand () % 1)+1/rand () % 4)-0.5; break;
				case 6:	Asteroid[contador].acelX = ((rand () % 1)+1/rand () % 4)+0.75; break;
				case 7:	Asteroid[contador].acelX = ((rand () % 1)+1/rand () % 4)-0.75; break;
			}
	
			switch (rand () % 8){
				case 0:	Asteroid[contador].acelY = ((rand () % 1)+1/rand () % 4)+0.1; break;
				case 1:	Asteroid[contador].acelY = ((rand () % 1)+1/rand () % 4)-0.1; break;
				case 2:	Asteroid[contador].acelY = ((rand () % 1)+1/rand () % 4)+0.25; break;
				case 3:	Asteroid[contador].acelY = ((rand () % 1)+1/rand () % 4)-0.25; break;
				case 4:	Asteroid[contador].acelY = ((rand () % 1)+1/rand () % 4)+0.5; break;
				case 5:	Asteroid[contador].acelY = ((rand () % 1)+1/rand () % 4)-0.5; break;
				case 6:	Asteroid[contador].acelY = ((rand () % 1)+1/rand () % 4)+0.75; break;
				case 7:	Asteroid[contador].acelY = ((rand () % 1)+1/rand () % 4)-0.75; break;
			}
	
	
	
	
			Asteroid[contador].ratio = ratio;
			Asteroid[contador].rads = rand () % 15;
			Asteroid[contador].active = SDL_TRUE;
			if (rand() % 2 == 1)
				Asteroid[contador].clockwise = SDL_TRUE;
			else
				Asteroid[contador].clockwise = SDL_FALSE; 
			Asteroid[contador].life = (int)ratio/2;		
	
			Asteroid[contador].type = rand () % 4;
	
	
		}
		indexAsteroids = contador;
	}
}


void Die(void){
	if (!flagsDead){
		drawProps(Player.x, Player.y, Player.rads, playerRatio, 0);
	
		drawShip(Player.x, Player.y, Player.rads, playerRatio,0);
		
		
		addExplosion((int)Player.x, (int)Player.y, (char)Player.ratio);
		playerLives--;
		drawScores();
		flagsDead = SDL_TRUE;
		respawnTime = 200;
		if (flagsSoundActive)
			Mix_PlayChannel( -1, die, 0 );
	}	
}

void DieB(void){
	if (!flagsBDead){
		drawPropsB(PlayerB.x, PlayerB.y, PlayerB.rads, playerBRatio, 0);
	
		drawShipB(PlayerB.x, PlayerB.y, PlayerB.rads, playerBRatio,0);
		
		
		addExplosion((int)PlayerB.x, (int)PlayerB.y, (char)PlayerB.ratio);
		playerBLives--;
		drawScores();
		flagsBDead = SDL_TRUE;
		respawnBTime = 200;
		if (flagsSoundActive)
			Mix_PlayChannel( -1, die, 0 );
	}	
}


void Hit(int bala, int asteroide){

	if (Asteroid[asteroide].active){

		Asteroid[asteroide].life--;
		Bullet[bala].active = SDL_FALSE;
		
		if (Asteroid[asteroide].life <= 0){
	
			addExplosion((int)Asteroid[asteroide].x, (int)Asteroid[asteroide].y, (char)Asteroid[asteroide].ratio);
	
	      		drawAsteroid(Asteroid[asteroide].x, Asteroid[asteroide].y, Asteroid[asteroide].rads, Asteroid[asteroide].ratio,0,asteroide, Asteroid[asteroide].type);         
	
			Asteroid[asteroide].active = SDL_FALSE;
	
		
		
			if (Asteroid[asteroide].ratio>=Player.ratio/2){
				t=(rand() % 2) +2;
		
				v = (rand() % 10) +1;
		
				switch (rand() % 12){
					case 0:generateAsteroid(Asteroid[asteroide].x-Asteroid[asteroide].ratio, Asteroid[asteroide].y, v, Asteroid[asteroide].ratio/t);
					       generateAsteroid(Asteroid[asteroide].x+Asteroid[asteroide].ratio, Asteroid[asteroide].y, v, Asteroid[asteroide].ratio/t); 
					       generateAsteroid(Asteroid[asteroide].x+Asteroid[asteroide].ratio, Asteroid[asteroide].y+Asteroid[asteroide].ratio, v, Asteroid[asteroide].ratio/t); 
					       generateAsteroid(Asteroid[asteroide].x+Asteroid[asteroide].ratio, Asteroid[asteroide].y-Asteroid[asteroide].ratio, v, Asteroid[asteroide].ratio/t); 
					       break;
		
		
					case 1:generateAsteroid(Asteroid[asteroide].x-Asteroid[asteroide].ratio, Asteroid[asteroide].y-Asteroid[asteroide].ratio, v, Asteroid[asteroide].ratio/t);
					       generateAsteroid(Asteroid[asteroide].x-Asteroid[asteroide].ratio, Asteroid[asteroide].y+Asteroid[asteroide].ratio, v, Asteroid[asteroide].ratio/t);
					       generateAsteroid(Asteroid[asteroide].x+Asteroid[asteroide].ratio, Asteroid[asteroide].y, v, Asteroid[asteroide].ratio/t); 
					       generateAsteroid(Asteroid[asteroide].x+Asteroid[asteroide].ratio, Asteroid[asteroide].y, v, Asteroid[asteroide].ratio/t); 
					       break;
		
					case 2:generateAsteroid(Asteroid[asteroide].x-Asteroid[asteroide].ratio, Asteroid[asteroide].y-Asteroid[asteroide].ratio, v, Asteroid[asteroide].ratio/t);
					       generateAsteroid(Asteroid[asteroide].x+Asteroid[asteroide].ratio, Asteroid[asteroide].y+Asteroid[asteroide].ratio, v, Asteroid[asteroide].ratio/t); 
					       break;
		
					case 3:generateAsteroid(Asteroid[asteroide].x, Asteroid[asteroide].y-Asteroid[asteroide].ratio, v, Asteroid[asteroide].ratio/t);
					       generateAsteroid(Asteroid[asteroide].x+Asteroid[asteroide].ratio, Asteroid[asteroide].y+Asteroid[asteroide].ratio, v, Asteroid[asteroide].ratio/t); 
					       break;
		
					case 4:generateAsteroid(Asteroid[asteroide].x, Asteroid[asteroide].y-Asteroid[asteroide].ratio, v, Asteroid[asteroide].ratio/t);
					       generateAsteroid(Asteroid[asteroide].x, Asteroid[asteroide].y+Asteroid[asteroide].ratio, v, Asteroid[asteroide].ratio/t); 
					       break;
		
					case 5:generateAsteroid(Asteroid[asteroide].x, Asteroid[asteroide].y, v, Asteroid[asteroide].ratio/t);
					       generateAsteroid(Asteroid[asteroide].x, Asteroid[asteroide].y+Asteroid[asteroide].ratio, v, Asteroid[asteroide].ratio/t); 
					       break;
		
					case 6:generateAsteroid(Asteroid[asteroide].x-Asteroid[asteroide].ratio, Asteroid[asteroide].y, v, Asteroid[asteroide].ratio/t);
					       break;
		
					case 7:generateAsteroid(Asteroid[asteroide].x-Asteroid[asteroide].ratio, Asteroid[asteroide].y-Asteroid[asteroide].ratio, v, Asteroid[asteroide].ratio/t);
					       break;
		
					case 8:generateAsteroid(Asteroid[asteroide].x-Asteroid[asteroide].ratio, Asteroid[asteroide].y-Asteroid[asteroide].ratio, v, Asteroid[asteroide].ratio/t);
					       break;
		
					case 9:generateAsteroid(Asteroid[asteroide].x, Asteroid[asteroide].y-Asteroid[asteroide].ratio, v, Asteroid[asteroide].ratio/t);
					       break;
		
					case 10:generateAsteroid(Asteroid[asteroide].x, Asteroid[asteroide].y-Asteroid[asteroide].ratio, v, Asteroid[asteroide].ratio/t);
					       break;
		
					case 11:generateAsteroid(Asteroid[asteroide].x, Asteroid[asteroide].y, v, Asteroid[asteroide].ratio/t);
					       break;
					       
		
				}
			}
				if (Bullet[bala].player == 0)	
					playerScore += Asteroid[asteroide].ratio*10;
				else
					playerBScore += Asteroid[asteroide].ratio*10;
			
			if (!flagsBombActive)
				drawScores();
			
		}
		if (!flagsBombActive)
			if (flagsSoundActive)
				Mix_PlayChannel( 1, explosion, 0 );
	}

}


void checkHits(void){
	for (contador=0; contador<indexQueueHit; contador++)
		if (queueHit[contador].active){
			queueHit[contador].active = SDL_FALSE;
			if (queueHit[contador].isBomb)
				flagsBombActive = SDL_TRUE;
			Hit(queueHit[contador].Bullet, queueHit[contador].Asteroid);
			flagsBombActive = SDL_FALSE;

		}	

	if (indexQueueHit > 0)
		if (!queueHit[indexQueueHit-1].active)
			indexQueueHit--;

}



void addHit(int bullet, int asteroid, SDL_bool isBomb){
	queueHit[indexQueueHit].active = SDL_TRUE;
	queueHit[indexQueueHit].Asteroid = asteroid;
	queueHit[indexQueueHit].Bullet = bullet;
	queueHit[indexQueueHit].isBomb = isBomb;

	indexQueueHit++;
}



int collisionDetected(int x, int y, unsigned char c, unsigned int index){
	    if (c == idBullet)
		    if (virtualScreen[x][y].idType == idAsteroid){
			    addHit(index,virtualScreen[x][y].indexType,SDL_FALSE);
			    addExplosion(x, y, 10);	// Explosion peque


		    }		    

	    if (c == idAlien){
		    if (virtualScreen[x][y].idType == idPlayer)
			    Die();
		    if (virtualScreen[x][y].idType == idPlayerB)
			    DieB();
	    }


	    if (c == idBullet){
		    if (virtualScreen[x][y].idType == idPlayer)
			    Die();
		    if (virtualScreen[x][y].idType == idPlayerB)
			    DieB();

		    if (virtualScreen[x][y].idType == idAlien){
			    addHit(virtualScreen[x][y].indexType,index,SDL_FALSE);
			    hitAlien(x,y);
			    addExplosion(x,y,10);
		    }

	    }		    

	    if (c == idPlayer){
		    //if ((virtualScreen[x][y].idType == idAsteroid) || (virtualScreen[x][y].idType == idBullet))
		//	    Die();

		    if (virtualScreen[x][y].idType == idPower)
			    flagsgetPower = SDL_TRUE;

	    	    if (virtualScreen[x][y].idType == idBomb)
			    flagsgetBomb = SDL_TRUE;
	    }	    

	    if (c == idPlayerB){
		    //if ((virtualScreen[x][y].idType == idAsteroid) || (virtualScreen[x][y].idType == idBullet))
			//    DieB();

		    if (virtualScreen[x][y].idType == idPower)
			    flagsgetBPower = SDL_TRUE;

	    	    if (virtualScreen[x][y].idType == idBomb)
			    flagsgetBBomb = SDL_TRUE;

	    }		    


	    if (c == idAsteroid){
		    if (virtualScreen[x][y].idType == idBullet){
			    addHit(virtualScreen[x][y].indexType,index,SDL_FALSE);
			    addExplosion(x, y, 10);
		    }	    

		    if (virtualScreen[x][y].idType == idPlayer)
			    Die();

		    if (virtualScreen[x][y].idType == idPlayerB)
			    DieB();

		    if (virtualScreen[x][y].idType == idAlien){
			    addHit(virtualScreen[x][y].indexType,index,SDL_FALSE);
			    hitAlien(x,y);
			    addExplosion(x,y,10);
		    }


	    }				    

	    if (c == idBomb){
		    if (virtualScreen[x][y].idType == idPlayer)
			    flagsgetBomb = SDL_TRUE;

		    if (virtualScreen[x][y].idType == idPlayerB)
			    flagsgetBBomb = SDL_TRUE;

	    }

	    if (c == idPower){
		    if (virtualScreen[x][y].idType == idPlayer)
			    flagsgetPower = SDL_TRUE;

		    if (virtualScreen[x][y].idType == idPlayerB)
			    flagsgetBPower = SDL_TRUE;
	    }

}
	    
void drawAlien(unsigned int x, unsigned int y, float angulo, unsigned int radio,unsigned char color){

  drawLine((x+(radio-radio/4)*cos(angulo-0.5)),(y+(radio-radio/4)*sin(angulo+pi-0.5)),(x+(radio-radio/4)*cos(angulo+0.5+pi)),(y+(radio-radio/4)*sin(angulo+pi+0.5+pi))   ,color,0);
  drawLine((x+(radio-radio/4)*cos(angulo+0.5)),(y+(radio-radio/4)*sin(angulo+pi+0.5)),(x+(radio-radio/4)*cos(angulo-0.5+pi)),(y+(radio-radio/4)*sin(angulo+pi-0.5+pi))   ,color,0);

  drawLine((x+(radio-radio/4)*cos(angulo-0.5)),(y+(radio-radio/4)*sin(angulo+pi-0.5)),  (x+(radio-radio/8)*cos(angulo-0.05)),(y+(radio-radio/8)*sin(angulo+pi-0.05)), color,0);
  drawLine((x+(radio-radio/8)*cos(angulo-0.05)),(y+(radio-radio/8)*sin(angulo+pi-0.05)),    (x+(radio-radio/4)*cos(angulo+0.5)),(y+(radio-radio/4)*sin(angulo+pi+0.5))  , color,0);

  drawLine((x+(radio-radio/4)*cos(angulo+0.5+pi)),(y+(radio-radio/4)*sin(angulo+pi+0.5+pi)),    (x+(radio-radio/8)*cos(angulo+pi)),(y+(radio-radio/8)*sin(angulo+pi+pi)), color,0);
  drawLine((x+(radio-radio/8)*cos(angulo+pi)),(y+(radio-radio/8)*sin(angulo+pi+pi)),   (x+(radio-radio/4)*cos(angulo-0.5+pi)),(y+(radio-radio/4)*sin(angulo+pi-0.5+pi))   , color,0);       


angulo=-angulo;

  for (j=angulo+0.58 ; j<=angulo+2.56; j+=0.01)
	  drawLine(x+(radio/1.5)*cos(j),y+(radio/1.5)*sin(j), x+(radio/1.5)*cos(j+0.01), y+(radio/1.5)*sin(j+0.01), color, 0); 


if (color != 0){
	floodWatch = 0;
	flood (x,y,color,0,0);
}
else{
	floodWatch = 0;
	flood (x,y,0,idAlien,0);
}	

}

void drawShip(unsigned int x, unsigned int y, float angulo, unsigned int radio,unsigned char color){

  drawLine((x+radio*cos(angulo)),(y+radio*sin(angulo)),(x+radio*cos(angulo+pi-0.5236)),(y+radio*sin(angulo+pi-0.5236)),color,0);
  drawLine((x+radio*cos(angulo)),(y+radio*sin(angulo)),(x+radio*cos(angulo+pi+0.5236)),(y+radio*sin(angulo+pi+0.5236)),color,0);
  drawLine((x+radio*cos(angulo+pi-0.5236)),(y+radio*sin(angulo+pi-0.5236)),(x+(radio-(radio/3))*cos(angulo+pi)),(y+(radio-(radio/3))*sin(angulo+pi)),color,0);
  drawLine((x+radio*cos(angulo+pi+0.5236)),(y+radio*sin(angulo+pi+0.5236)),(x+(radio-(radio/3))*cos(angulo+pi)),(y+(radio-(radio/3))*sin(angulo+pi)),color,0);

if (color != 0){
	floodWatch = 0;
	flood (x,y,color,0,0);
}
else{
	floodWatch = 0;
	flood (x,y,0,idPlayer,0);
}	
}

void drawShipB(unsigned int x, unsigned int y, float angulo, unsigned int radio,unsigned char color){

  drawLine((x+radio*cos(angulo)),(y+radio*sin(angulo)),(x+radio*cos(angulo+pi+1)),(y+radio*sin(angulo+pi+1)),color,0);
  drawLine((x+radio*cos(angulo)),(y+radio*sin(angulo)),(x+radio*cos(angulo+pi-1)),(y+radio*sin(angulo+pi-1)),color,0);
  drawLine((x+radio*cos(angulo+pi+1)),(y+radio*sin(angulo+pi+1)),(x+radio*cos(angulo+pi-1)),(y+radio*sin(angulo+pi-1)),color,0);

  drawLine((x+radio*cos(angulo+pi-0.5236)),(y+radio*sin(angulo+pi-0.5236)),(x+(radio-(radio/3))*cos(angulo+pi)),(y+(radio-(radio/3))*sin(angulo+pi)),color,0);
  drawLine((x+radio*cos(angulo+pi+0.5236)),(y+radio*sin(angulo+pi+0.5236)),(x+(radio-(radio/3))*cos(angulo+pi)),(y+(radio-(radio/3))*sin(angulo+pi)),color,0);

if (color != 0){
	floodWatch = 0;
	flood (x,y,color,0,0);
}
else{
	floodWatch = 0;
	flood (x,y,0,idPlayerB,0);
}	

}


void drawProps(unsigned int x, unsigned int y, float angulo, unsigned int radio,unsigned char color){
  drawLine((x+radio*1.2*cos(angulo+pi+propM)),(y+radio*1.2*sin(angulo+pi+propM)),(x+(radio-(radio/4))*cos(angulo+pi)),(y+(radio-(radio/4))*sin(angulo+pi)),color,0);
  drawLine((x+radio*1.2*cos(angulo+pi-0.2+propM)),(y+radio*1.2*sin(angulo+pi-0.2+propM)),(x+(radio-(radio/4))*cos(angulo+pi)),(y+(radio-(radio/4))*sin(angulo+pi)),color,0);
  drawLine((x+radio*1.2*cos(angulo+pi+0.2+propM)),(y+radio*1.2*sin(angulo+pi+0.2+propM)),(x+(radio-(radio/4))*cos(angulo+pi)),(y+(radio-(radio/4))*sin(angulo+pi)),color,0);
}

void drawPropsB(unsigned int x, unsigned int y, float angulo, unsigned int radio,unsigned char color){
  drawLine((x+radio*1.2*cos(angulo+pi+propMB)),(y+radio*1.2*sin(angulo+pi+propMB)),(x+(radio-(radio/4))*cos(angulo+pi)),(y+(radio-(radio/4))*sin(angulo+pi)),color,0);
  drawLine((x+radio*1.2*cos(angulo+pi-0.2+propMB)),(y+radio*1.2*sin(angulo+pi-0.2+propMB)),(x+(radio-(radio/4))*cos(angulo+pi)),(y+(radio-(radio/4))*sin(angulo+pi)),color,0);
  drawLine((x+radio*1.2*cos(angulo+pi+0.2+propMB)),(y+radio*1.2*sin(angulo+pi+0.2+propMB)),(x+(radio-(radio/4))*cos(angulo+pi)),(y+(radio-(radio/4))*sin(angulo+pi)),color,0);
}


void drawBullets(void){
    if (indexBullet > 0)
      for (contador = 0; contador < indexBullet ; contador++)
        if (Bullet[contador].active){
          Bullet[contador].x+=Bullet[contador].acelX;
          Bullet[contador].y+=Bullet[contador].acelY;

	  putPixel((int)Bullet[contador].x, (int)Bullet[contador].y, idBullet, contador);

	  GPU_Pixel(renderer, Bullet[contador].x, Bullet[contador].y, White);
	  
      }  
}

void eraseBullets(void){
    z = 0;
    if (indexBullet > 0){
      for (contador = 0; contador < indexBullet ; contador++)
        if (Bullet[contador].active){
	  z++;
	  putPixel((int)Bullet[contador].x, (int)Bullet[contador].y, 0, contador);

	  GPU_Pixel(renderer, Bullet[contador].x, Bullet[contador].y, Black);



          if ((Bullet[contador].x < 0) || (Bullet[contador].x > limitX) || (Bullet[contador].y < 0) || (Bullet[contador].y > limitY))	
            Bullet[contador].active = SDL_FALSE;
        }                   
      if (z == 0)
	indexBullet = 0;
    }
}  

void addBullet(SDL_bool player){
	if (pc > maxFreqBullet)
		if (indexBullet < limitBullet){  
			for (contador = 0; contador < playerPower; contador ++){

				Bullet[indexBullet].x = Player.x+(cos(Player.rads)*(playerRatio+4))+(cos(contador)*contador);
				Bullet[indexBullet].y = Player.y+(sin(Player.rads)*(playerRatio+4))+(sin(contador)*contador);
				Bullet[indexBullet].acelX = cos(Player.rads)*4;
				Bullet[indexBullet].acelY = sin(Player.rads)*4;
				Bullet[indexBullet].active = SDL_TRUE;
				Bullet[indexBullet].player = player;
				indexBullet++;
				heat++;
			}
				
			if (heat>50)
				maxFreqBullet++;

			pc = 0;
			if (flagsSoundActive)
				Mix_PlayChannel( -1, shoot, 0 );

			// Retroceso!
			
	  		Player.acelX-=cos(Player.rads)/20; 
			Player.acelY-=sin(Player.rads)/20;

		}        

}

void addBulletB(SDL_bool player){
	if (pc > maxFreqBBullet)
		if (indexBullet < limitBullet){  
			for (contador = 0; contador < playerBPower; contador ++){
				Bullet[indexBullet].x = PlayerB.x+(cos(PlayerB.rads)*(playerBRatio+4))+(cos(contador)*contador);
				Bullet[indexBullet].y = PlayerB.y+(sin(PlayerB.rads)*(playerBRatio+4))+(sin(contador)*contador);
				Bullet[indexBullet].acelX = cos(PlayerB.rads)*4;
				Bullet[indexBullet].acelY = sin(PlayerB.rads)*4;
				Bullet[indexBullet].active = SDL_TRUE;
				Bullet[indexBullet].player = player;
				indexBullet++;
				heatB++;
			}
				
			if (heatB>50)
				maxFreqBBullet++;

			pc = 0;
			if (flagsSoundActive)
				Mix_PlayChannel( -1, shoot, 0 );

			// Retroceso!
			
	  		PlayerB.acelX-=cos(PlayerB.rads)/20; 
			PlayerB.acelY-=sin(PlayerB.rads)/20;

		}        

}


void addExplosion(unsigned int x, unsigned int y, unsigned char ratio){
	if (indexExplosions < limitExplosions){
		Explosion[indexExplosions].x = x;
		Explosion[indexExplosions].y = y;
		Explosion[indexExplosions].ratio = 0;
		Explosion[indexExplosions].ratioMax = ratio;
		Explosion[indexExplosions].active = SDL_TRUE;
		Explosion[indexExplosions].rAngle = rand() % 4;
		Explosion[indexExplosions].rAngle -= 2;

		indexExplosions++;
	}
	
}


void limitCheck(void){
    if (Player.rads >= twoPi)
      Player.rads=0;

    if (Player.rads < 0)
      Player.rads=twoPi;  
    
    /*if (Player.x < (Player.ratio*1.2))
      Player.x=limitX - (Player.ratio*1.5);

    if (Player.x > (limitX - (Player.ratio*1.2)))
      Player.x=Player.ratio*1.5;

    if (Player.y > (limitY - (Player.ratio*1.2)))
      Player.y=60;		// Espacio para marcadores, deberia de ser 0


    if (Player.y < 60)		// Espacio para marcadores, deberia de ser 0
      Player.y=limitY - (Player.ratio*2);*/

    if (Player.x < (Player.ratio))
      Player.x=limitX - Player.ratio - 1;

    if (Player.x > (limitX - Player.ratio - 1))
      Player.x=Player.ratio;

    if (Player.y > (limitY - Player.ratio - 1))
      Player.y=50 + Player.ratio;		// Espacio para marcadores, deberia de ser 0


    if (Player.y < (50 + Player.ratio))		// Espacio para marcadores, deberia de ser 0
      Player.y=limitY - Player.ratio - 1;






    if (PlayerB.rads >= twoPi)
      PlayerB.rads=0;

    if (PlayerB.rads < 0)
      PlayerB.rads=twoPi;  
    

    /*if (PlayerB.y > (limitY - (PlayerB.ratio*1.2)))
      PlayerB.y=60;		// Espacio para marcadores, deberia de ser 0

    if (PlayerB.x < (PlayerB.ratio*1.2))
      PlayerB.x=limitX - (PlayerB.ratio*2);

    if (PlayerB.x > (limitX - (PlayerB.ratio*1.2)))
      PlayerB.x=PlayerB.ratio*1.5;

    if (PlayerB.y < 60)		// Espacio para marcadores, deberia de ser 0
      PlayerB.y=limitY - (PlayerB.ratio*2);*/


    if (PlayerB.y > (limitY - PlayerB.ratio - 1))
      PlayerB.y=50 + PlayerB.ratio;		// Espacio para marcadores, deberia de ser 0

    if (PlayerB.x < (PlayerB.ratio))
      PlayerB.x=limitX - PlayerB.ratio - 1;

    if (PlayerB.x > (limitX - PlayerB.ratio - 1))
      PlayerB.x=PlayerB.ratio;

    if (PlayerB.y < (50 + PlayerB.ratio))		// Espacio para marcadores, deberia de ser 0
      PlayerB.y=limitY - PlayerB.ratio - 1;



  for (contador = 0; contador < indexAsteroids; contador++)
    if (Asteroid[contador].active){
      if (Asteroid[contador].rads >= twoPi)
        Asteroid[contador].rads=0;

      if (Asteroid[contador].rads < 0)
        Asteroid[contador].rads=twoPi;  
  }
/*
      //if (Asteroid[contador].x > (limitX - (Asteroid[contador].ratio + 10)))
	//      Asteroid[contador].x=(Asteroid[contador].ratio) + 10;
      if (Asteroid[contador].x >= limitX)
	      Asteroid[contador].x=0;

      if (Asteroid[contador].y >= limitY)
	      Asteroid[contador].y=0;


      //if (Asteroid[contador].y > (limitY - (Asteroid[contador].ratio +10)))
      //  Asteroid[contador].y=50 + (Asteroid[contador].ratio) + 10;

      //if (Asteroid[contador].x < (Asteroid[contador].ratio + 10))
        //Asteroid[contador].x=(limitX - (Asteroid[contador].ratio +10));
      if (Asteroid[contador].x < 0)
        Asteroid[contador].x=limitX - 1;

      if (Asteroid[contador].y < 0)
        Asteroid[contador].y=limitY - 1;



      //if (Asteroid[contador].y < (50 + Asteroid[contador].ratio + 10))	// Espacio para marcadores, deberia de ser 0
      //  Asteroid[contador].y=(limitY - (Asteroid[contador].ratio + 10));
  }	*/

}

void movePlayer(void){
    Player.x+=Player.acelX;
    Player.y+=Player.acelY;  
}

void movePlayerB(void){
    PlayerB.x+=PlayerB.acelX;
    PlayerB.y+=PlayerB.acelY;  
}


void drawAsteroids(unsigned char color){

	z = 0;

	for (contador=0; contador < indexAsteroids; contador++)
		if (Asteroid[contador].active){
      			/*if (Asteroid[contador].rads >= twoPi)
			        Asteroid[contador].rads=0;

			if (Asteroid[contador].rads < 0)
			        Asteroid[contador].rads=twoPi;  */


      			if (Asteroid[contador].x >= limitX)
			      Asteroid[contador].x=0;

		        if (Asteroid[contador].y >= limitY)
			      Asteroid[contador].y=0;


      			if (Asteroid[contador].x < 0)
			        Asteroid[contador].x=limitX - 1;

		        if (Asteroid[contador].y < 0)
			        Asteroid[contador].y=limitY - 1;


   			if (Asteroid[contador].x >= (limitX - Asteroid[contador].ratio)){
				drawAsteroid(Asteroid[contador].x - limitX, Asteroid[contador].y, Asteroid[contador].rads, Asteroid[contador].ratio,color,contador, Asteroid[contador].type);         
			}

   			if (Asteroid[contador].y >= (limitY - Asteroid[contador].ratio)){
				drawAsteroid(Asteroid[contador].x, Asteroid[contador].y - limitY , Asteroid[contador].rads, Asteroid[contador].ratio,color,contador, Asteroid[contador].type);         
			}


			if (Asteroid[contador].x < Asteroid[contador].ratio)
				drawAsteroid(Asteroid[contador].x + limitX , Asteroid[contador].y, Asteroid[contador].rads, Asteroid[contador].ratio,color,contador, Asteroid[contador].type);         

			if (Asteroid[contador].y < (Asteroid[contador].ratio))
				drawAsteroid(Asteroid[contador].x, Asteroid[contador].y + limitY, Asteroid[contador].rads, Asteroid[contador].ratio,color,contador, Asteroid[contador].type);         


			drawAsteroid(Asteroid[contador].x, Asteroid[contador].y, Asteroid[contador].rads, Asteroid[contador].ratio,color,contador, Asteroid[contador].type);         
			z++;
		}  





  if (z == 0)
	  indexAsteroids = 0;
}


void generateAsteroids(unsigned char quantity){
	int counter;
	for (counter = 0; counter < quantity; counter++)
		generateAsteroid( rand ()%limitX, rand()%limitY ,1, playerRatio*10);
}


void moveAsteroids(void){
  for (contador = 0; contador < indexAsteroids; contador++){
    Asteroid[contador].x += Asteroid[contador].acelX;
    Asteroid[contador].y += Asteroid[contador].acelY;
    if (Asteroid[contador].clockwise)
      Asteroid[contador].rads += 0.025;
    else
      Asteroid[contador].rads -= 0.025;  
  }
}


int initVideo(void){
	
	GPU_SetPreInitFlags(GPU_INIT_DISABLE_VSYNC);

	renderer = GPU_Init(limitX, limitY, GPU_DEFAULT_INIT_FLAGS);

	if(renderer == NULL)
	        return 1;

	//GPU_SetFullscreen(1,0);

        GPU_Clear(renderer);
}

void readInputs(void){
    while( SDL_PollEvent( &evento ) ){
      switch( evento.type ){
        case SDL_KEYDOWN:  switch( evento.key.keysym.sym ){
          case SDLK_LEFT: pressedLeft = 1; break;
	  case SDLK_RIGHT: pressedRight = 1; break;
  	  case SDLK_i: pressedFire = 1; break;
	  case SDLK_o: if (!pressedAccel && !flagsDead) { pressedAccel = 1; Mix_HaltChannel(15); Mix_PlayChannel( 15, propStart, 0 ); } break;
	  case SDLK_p: pressedBomb = 1; break;


          case SDLK_a: pressedBLeft = 1; break;
	  case SDLK_d: pressedBRight = 1; break;
  	  case SDLK_1: pressedBFire = 1; break;
	  case SDLK_2: if (!pressedBAccel && !flagsBDead) { pressedBAccel = 1; Mix_HaltChannel(14); Mix_PlayChannel( 14, propStart, 0 ); } break;
	  case SDLK_3: pressedBBomb = 1; break;


        } break;
        case SDL_KEYUP:  switch( evento.key.keysym.sym ){
          case SDLK_LEFT: pressedLeft = 0; break;
	  case SDLK_RIGHT: pressedRight = 0; break;
  	  case SDLK_i: pressedFire = 0; break;
	  case SDLK_o: pressedAccel = 0; Mix_HaltChannel(15); Mix_PlayChannel( 15, propStop, 0 ); break;
	  case SDLK_p: pressedBomb = 0; break;

          case SDLK_a: pressedBLeft = 0; break;
	  case SDLK_d: pressedBRight = 0; break;
  	  case SDLK_1: pressedBFire = 0; break;
	  case SDLK_2: pressedBAccel = 0; Mix_HaltChannel(14); Mix_PlayChannel( 14, propStop, 0 ); break;
	  case SDLK_3: pressedBBomb = 0; break;


        } break;
      case SDL_QUIT: quit = SDL_TRUE; break;			   
      }
    }    
}


void launchBomb(int jugador){
	if (bombCooldown == 0)
		if (!flagsBombActive){
			flagsBombActive = SDL_TRUE;
			if (jugador == 1)
				playerBombs--;
			else
				playerBBombs--;
			if (flagsSoundActive)
				Mix_PlayChannel( -1, nuke, 0 );

			for (contador=0; contador<indexAsteroids; contador++)
				if (Asteroid[contador].active)	
					for (v=0; v<50; v++)
						addHit(0, contador, SDL_TRUE);


			drawScores();
			flagsBombActive = SDL_FALSE;
			bombCooldown = 100;
		}	
}


 
void applyInputs(void){
	if (!flagsGameOver){
	    if (pressedLeft)
		    Player.rads-=0.1;
	    if (pressedRight)
		    Player.rads+=0.1;
	    if (pressedFire)  {
		if (!flagsDead)
		    addBullet(0);
	    }	
	    else
		    if (heat>0)
			    heat--;
	
	    if (pressedAccel)
	    	if (!flagsDead){
		  Player.acelX+=cos(Player.rads)/10; 
		  Player.acelY+=sin(Player.rads)/10;
		  if (Mix_Playing(15) == 0)
			  Mix_PlayChannel( 15, propLoop, 0 );
		  
	    }  
	
	    if (pressedBomb)
		    if (!flagsBombActive)
			if (!flagsDead)
			    if (playerBombs>0)
				    launchBomb(1);


	    if (pressedBLeft)
		    PlayerB.rads-=0.1;
	    if (pressedBRight)
		    PlayerB.rads+=0.1;
	    if (pressedBFire)  {
		if (!flagsBDead)
		    addBulletB(1);
	    }	
	    else
		    if (heatB>0)
			    heatB--;
	
	    if (pressedBAccel)
	    	if (!flagsBDead){
		  PlayerB.acelX+=cos(PlayerB.rads)/10; 
		  PlayerB.acelY+=sin(PlayerB.rads)/10;
		  if (Mix_Playing(14) == 0)
			  Mix_PlayChannel( 14, propLoop, 0 );
		  
	    }  
	
	    if (pressedBBomb)
		    if (!flagsBombActive)
			if (!flagsBDead)
			    if (playerBBombs>0)
				    launchBomb(2);

	}
	else{
		if ((pressedFire) || (pressedBFire)) {
			//launchBomb();
			//generateAsteroids(2);
			flagsGameOver = SDL_FALSE;

			GPU_RectangleFilled(renderer, 200,200,1050,500, Black);

			GPU_RectangleFilled(renderer, 0,0,1200,50, Black);


			drawScores();

			playerBombs = 50;
			playerLives = 3;
			playerScore = 0;
			playerPower = 1;
			

			playerInit();

			if (pressedBFire){
				playerBBombs = 5;
				playerBLives = 3;
				playerBScore = 0;
				playerBPower = 1;
				playerInitB();
			}	




		}	
	}	
}	

void endSDL(void){
  GPU_Quit();
     
  SDL_Quit();
}	

void initVS(void){
	int x,y;
	for (x=0; x<limitX; x++)
		for(y=0; y<limitY; y++)
			virtualScreen[x][y].idType=0;
}

int memoryError(void){
	printf("Not enough memory!");
	return(1);
}

/*int intro(void){



    if (SDL_Init(SDL_INIT_VIDEO) != 0)  {
	    return 1;
    }    
    if (SDL_CreateWindowAndRenderer(320, 200, SDL_WINDOW_OPENGL, &window, &renderer) != 0) {
	    return 1;
    }    

    if (SDL_SetWindowFullscreen(window,SDL_WINDOW_FULLSCREEN) != 0)
	    return 1;


    SDL_RenderClear(renderer);

    SDL_Delay(5000);

SDL_Surface *salon = NULL;
salon = SDL_LoadBMP("salon.bmp");
SDL_Surface *pantalla = SDL_CreateRGBSurface(0, 320, 200, 32, 0, 0, 0, 0);
SDL_Texture *texture;


SDL_Rect scroll;
scroll.y=0;
scroll.h=128;
scroll.w=320;

for (scroll.x=0; scroll.x<200; scroll.x++){
	SDL_BlitSurface(salon, &scroll, pantalla, NULL);
	texture = SDL_CreateTextureFromSurface(renderer, pantalla);



	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
	SDL_Delay(20);
}

scroll.x=50;
scroll.w=200;
for (scroll.h=200; scroll.h>50; scroll.h--){
	scroll.w--;
	scroll.x++;


	SDL_RenderCopy(renderer, texture, &scroll, NULL);
	SDL_RenderPresent(renderer);
	SDL_Delay(20);

}


    SDL_Delay(1000);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);






}*/

int checkSomething(void){
	int c = 0;

	if (indexAsteroids>0)
		drawAsteroids(idAsteroid); 


	for (v = (Player.x-Player.ratio); v < (Player.x+Player.ratio) ; v++)
		for (z = (Player.y-Player.ratio); z < (Player.y+Player.ratio); z++)
			if (getPixel(v,z) != 0)
				c = 1;

	
	if (indexAsteroids>0)
		drawAsteroids(0); 

	return(c);
}

int checkSomethingB(void){
	int c = 0;

	if (indexAsteroids>0)
		drawAsteroids(idAsteroid); 


	for (v = (PlayerB.x-PlayerB.ratio); v < (PlayerB.x+PlayerB.ratio) ; v++)
		for (z = (PlayerB.y-PlayerB.ratio); z < (PlayerB.y+PlayerB.ratio); z++)
			if (getPixel(v,z) != 0)
				c = 1;

	
	if (indexAsteroids>0)
		drawAsteroids(0); 

	return(c);
}



void playerInit(void){


	Player.x = limitX/2 - 200;
	Player.y = limitY/2;
	Player.ratio = 25;
	Player.rads = 0;
	Player.acelX = 0;
	Player.acelY = 0;
	playerPower = 1;

	if (checkSomething() == 1){
		respawnTime=100;
		flagsDead = SDL_TRUE;
	}
	else{
		//Bomb.active = SDL_FALSE;
		//Power.active = SDL_FALSE;
		flagsDead = SDL_FALSE;
	}	
}

void playerInitB(void){


	PlayerB.x = limitX/2 + 200;
	PlayerB.y = limitY/2;
	PlayerB.ratio = 25;
	PlayerB.rads = pi;
	PlayerB.acelX = 0;
	PlayerB.acelY = 0;
	playerBPower = 1;
	

	if (checkSomethingB() == 1){
		respawnBTime=100;
		flagsBDead = SDL_TRUE;
	}
	else{
		//Bomb.active = SDL_FALSE;
		//Power.active = SDL_FALSE;
		flagsBDead = SDL_FALSE;
	}	
}


void gameOver(void){
	//quit = SDL_TRUE;
	flagsGameOver = SDL_TRUE;
}

void drawScores(void){
	sprintf(string, "P1 LIVES: %d BOMBS: %d SCORE: %d  P2 LIVES: %d BOMBS: %d SCORE: %d", playerLives, playerBombs, playerScore,playerBLives,playerBBombs,playerBScore);

	superficie = TTF_RenderText_Solid(font, string, White);

	texturaMensaje = GPU_CopyImageFromSurface(superficie);


	GPU_RectangleFilled(renderer, 0,0,superficie->w,superficie->h, Black);

	rectangulo.x = 0;
	rectangulo.y = 0;
	rectangulo.w = superficie->w;
	rectangulo.h = superficie->h;
	GPU_Blit(texturaMensaje, &rectangulo, renderer, superficie->w/2, superficie->h/2);
}

void addBomb(void){
  Bomb.ratio = playerRatio*2;	
  Bomb.x = (rand() % (limitX - (int)Bomb.ratio * 2)) + (int)Bomb.ratio * 2;
  Bomb.y = (rand() % (limitY - (int)Bomb.ratio * 2)) + (int)Bomb.ratio * 2;
  Bomb.active = SDL_TRUE;
  Bomb.augment = SDL_TRUE;
}


void cleanHitQueue(void){
	for (contador=0; contador<indexQueueHit; contador++)
		queueHit[contador].active = SDL_FALSE;

	indexQueueHit = 0;
}

void addPower(void){
  Power.ratio = playerRatio*2;	
  Power.x = (rand() % (limitX - (int)Power.ratio * 2)) + (int)Power.ratio;
  Power.y = (rand() % (limitY - (int)Power.ratio * 2)) + (int)Power.ratio;
  if (Power.y < 70)
	  Power.y=70;
  Power.active = SDL_TRUE;
  Power.augment = SDL_TRUE;
}

void initAlien(void){

	if (rand() % 2){
	  	Alien.x=50;
		Alien.acelX=0.5;
	}
	else{
		Alien.x=limitX-50;
	  	Alien.acelX=-0.5;
	}	
	Alien.y=(rand() % 600) + 100;
 
	Alien.acelY=0;
	Alien.ratio=playerRatio*6;
	Alien.rads=pi;
	Alien.life=Alien.ratio*20;
	Alien.active = SDL_TRUE;

}

void moveAlien(void){
	Alien.x+=Alien.acelX;
	Alien.y+=Alien.acelY;
	

	switch (rand() % 6){
		case 0:	Alien.acelX+=cos(Alien.rads); Alien.acelY+=sin(Alien.rads); break;
		case 1:	Alien.acelX-=cos(Alien.rads); Alien.acelY-=sin(Alien.rads); break;
		case 2:	Alien.acelX+=cos(Alien.rads); Alien.acelY-=sin(Alien.rads); break;
		case 3:	Alien.acelX-=cos(Alien.rads); Alien.acelY+=sin(Alien.rads); break;
	}
		
	if (rand() % 2)
		Alien.rads+=0.05;
	else
		Alien.rads-=0.05;

	if (Alien.rads >= twoPi)
		Alien.rads = 0;
	if (Alien.rads < 0 )
		Alien.rads = twoPi;


	if ((Alien.x > limitX) || (Alien.x < 0) || (Alien.y > limitY) || (Alien.y < 80))
		Alien.active = SDL_FALSE;

}

void hitAlien(int x, int y){
	Alien.life--;

	if (Alien.life == 0){
		drawAlien(Alien.x,Alien.y,Alien.rads,Alien.ratio,0);
		addExplosion(x,y,Alien.ratio);
		Alien.active = SDL_FALSE;
	}



}








void otherChecks(void){
	if ((rand() % 3000) == 0)
		if (!Alien.active)
			initAlien();

	if ((rand() % 5000) == 0)
		if (!Bomb.active)
			addBomb();

	if ((rand() % 1000) == 0)
		if (!Power.active)
			addPower();


	if (Power.active){
		if (Power.ratio >= (playerRatio))
			Power.augment = SDL_FALSE;

		if (Power.ratio <= playerRatio/3)
			Power.augment = SDL_TRUE;

		if (Power.augment)
			Power.ratio+=0.5;
		else
			Power.ratio-=0.5;
	}	


	if (Bomb.active){
		if (Bomb.ratio >= (playerRatio*3))
			Bomb.augment = SDL_FALSE;

		if (Bomb.ratio <= playerRatio)
			Bomb.augment = SDL_TRUE;

		if (Bomb.augment)
			Bomb.ratio+=0.5;
		else
			Bomb.ratio-=0.5;
	}	

	if (flagsgetBomb){
		flagsgetBomb = SDL_FALSE;
		getBomb();
	}

	if (flagsgetBBomb){
		flagsgetBBomb = SDL_FALSE;
		getBBomb();
	}


	if (flagsgetPower){
		flagsgetPower = SDL_FALSE;
		getPower();
	}

	if (flagsgetBPower){
		flagsgetBPower = SDL_FALSE;
		getBPower();
	}




	if (heat<50)
		if (maxFreqBullet > 1)
			maxFreqBullet--;

	if (heatB<50)
		if (maxFreqBBullet > 1)
			maxFreqBBullet--;

	if (pc>100){
		if (indexAsteroids == 0){
			cleanHitQueue();
			generateAsteroids(2);
		}
		/*if (flagsDead){
			respawnTime--;
			if (respawnTime == 0)
				if (playerLives>0)
					playerInit();
				else
					gameOver();	
		}	*/
		if ((playerBLives == 0) && (playerLives == 0)){
			flagsDead = SDL_FALSE;
			flagsBDead = SDL_TRUE;
			gameOver();	
		}			

		if (flagsDead){
			respawnTime--;
			if (respawnTime == 0)
				if (playerLives>0)
					playerInit();
		}	

		if (flagsBDead){
			respawnBTime--;
			if (respawnBTime == 0)
				if (playerBLives>0)
					playerInitB();


		}
	}

	if (bombCooldown > 0)
		bombCooldown--;
}






void drawBomb(unsigned int x, unsigned int y, float angulo, unsigned int radio,unsigned char color){



  drawLine((x+radio*cos(angulo+pi+0.1)), (y+radio*sin(angulo+pi+0.1)), (x+radio*cos(angulo+pi-0.1)), (y+radio*sin(angulo+pi-0.1)), color, 0);

  drawLine((x+radio*cos(angulo+pi+0.1)), (y+radio*sin(angulo+pi+0.1)), (x+(radio-radio/8)*cos(angulo+pi+0.2)), (y+(radio-radio/8)*sin(angulo+pi+0.2)), color, 0);
  drawLine((x+radio*cos(angulo+pi-0.1)),(y+radio*sin(angulo+pi-0.1)),(x+(radio-radio/8)*cos(angulo+pi-0.2)),(y+(radio-radio/8)*sin(angulo+pi-0.2)),color,0);


  drawLine((x+(radio-radio/2)*cos(angulo+pi+0.25)), (y+(radio-radio/2)*sin(angulo+pi+0.25)), (x+(radio-radio/8)*cos(angulo+pi+0.2)), (y+(radio-radio/8)*sin(angulo+pi+0.2)), color, 0);
  drawLine((x+(radio-radio/2)*cos(angulo+pi-0.25)),(y+(radio-radio/2)*sin(angulo+pi-0.25)),(x+(radio-radio/8)*cos(angulo+pi-0.2)),(y+(radio-radio/8)*sin(angulo+pi-0.2)),color,0);


  drawLine((x+(radio-radio/2)*cos(angulo+pi+0.25)), (y+(radio-radio/2)*sin(angulo+pi+0.25)), (x+(radio-radio/2)*cos(angulo+pi-0.25)), (y+(radio-radio/2)*sin(angulo+pi-0.25)), color, 0);



  drawLine((x+(radio-radio/2)*cos(angulo+pi+0.25)), (y+(radio-radio/2)*sin(angulo+pi+0.25)), (x+(radio-radio/2)*cos(angulo+pi+0.5)), (y+(radio-radio/2)*sin(angulo+pi+0.25)), color, 0);
  drawLine((x+(radio-radio/2)*cos(angulo+pi-0.25)), (y+(radio-radio/2)*sin(angulo+pi-0.25)), (x+(radio-radio/2)*cos(angulo+pi-0.5)), (y+(radio-radio/2)*sin(angulo+pi-0.25)), color, 0);

  drawLine((x+(radio-radio/2)*cos(angulo+pi-0.5)), (y+(radio-radio/1.5)*sin(angulo+pi-0.25)), (x+(radio-radio/2)*cos(angulo+pi-0.5)), (y+(radio-radio/2)*sin(angulo+pi-0.25)), color, 0);
  drawLine((x+(radio-radio/2)*cos(angulo+pi+0.5)), (y+(radio-radio/1.5)*sin(angulo+pi+0.25)), (x+(radio-radio/2)*cos(angulo+pi+0.5)), (y+(radio-radio/2)*sin(angulo+pi+0.25)), color, 0);

  drawLine((x+(radio-radio/2)*cos(angulo+pi+0.5)), (y+(radio-radio/1.5)*sin(angulo+pi+0.25)), (x+(radio-radio/2)*cos(angulo+pi-0.5)), (y+(radio-radio/1.5)*sin(angulo+pi-0.25)), color, 0);
}

void getBomb(void){
	Mix_PlayChannel( -1, gotBomb, 0 );
	//drawScores();
	Bomb.active = SDL_FALSE;
	playerBombs++;
}

void getBBomb(void){
	Mix_PlayChannel( -1, gotBomb, 0 );
	//drawScores();
	Bomb.active = SDL_FALSE;
	playerBBombs++;
}


void getPower(void){
	Mix_PlayChannel( -1, gotBomb, 0 );
	Power.active = SDL_FALSE;
	playerPower++;
}

void getBPower(void){
	Mix_PlayChannel( -1, gotBomb, 0 );
	Power.active = SDL_FALSE;
	playerBPower++;
}




void drawPower(unsigned int x, unsigned int y, float angulo, unsigned int radio,unsigned char color){
  drawLine((x+radio*cos(angulo-0.7)),(y+radio*sin(angulo-0.7)),(x+radio*cos(angulo+pi+0.7)),(y+radio*sin(angulo+pi+0.7)),color,0);
  drawLine((x+radio*cos(angulo-0.7)),(y+radio*sin(angulo-0.7)),(x+(radio-radio/5)*cos(angulo)),(y+(radio-radio/5)*sin(angulo)),color,0);
  drawLine((x+(radio-radio/1.2)*cos(angulo)),(y+(radio-radio/1.2)*sin(angulo)),(x+(radio-radio/5)*cos(angulo)),(y+(radio-radio/5)*sin(angulo)),color,0);
  drawLine((x+(radio-radio/1.2)*cos(angulo)), (y+(radio-radio/1.2)*sin(angulo)), (x+(radio+radio/20)*cos(angulo-0.7)), (y+(radio-radio/1.3)*sin(angulo-0.7)),color,0);
  
  drawLine((x+radio*cos(angulo-0.7))+radio,(y+radio*sin(angulo-0.7)),(x+radio*cos(angulo+pi+0.7))+radio,(y+radio*sin(angulo+pi+0.7)),color,0);
  drawLine((x+radio*cos(angulo-0.7))+(radio*1.75),(y+radio*sin(angulo-0.7)),(x+radio*cos(angulo+pi+0.7))+(radio*1.75),(y+radio*sin(angulo+pi+0.7)),color,0);
  drawLine((x+radio*cos(angulo-0.7))+radio,(y+radio*sin(angulo-0.7)),(x+radio*cos(angulo-0.7))+(radio*1.75),(y+radio*sin(angulo-0.7)),color,0);
  drawLine((x+radio*cos(angulo+pi+0.7))+radio,(y+radio*sin(angulo+pi+0.7)),(x+radio*cos(angulo+pi+0.7))+(radio*1.75),(y+radio*sin(angulo+pi+0.7)),color,0);


  drawLine((x+radio*cos(angulo-0.7))+radio*2,(y+radio*sin(angulo-0.7)),(x+radio*cos(angulo+pi+0.7))+radio*2.2,(y+radio*sin(angulo+pi+0.7)),color,0);
  drawLine((x+radio*cos(angulo-0.7))+radio*3,(y+radio*sin(angulo-0.7)),(x+radio*cos(angulo+pi+0.7))+radio*2.8,(y+radio*sin(angulo+pi+0.7)),color,0);
  drawLine((x+radio*cos(angulo+pi+0.7))+radio*2.2,(y+radio*sin(angulo+pi+0.7)),(x+radio*cos(angulo+pi+0.7))+(radio*2.5),(y+(radio-radio/2)*sin(angulo+pi+0.7)),color,0);
  drawLine((x+radio*cos(angulo+pi+0.7))+radio*2.8,(y+radio*sin(angulo+pi+0.7)),(x+radio*cos(angulo+pi+0.7))+(radio*2.5),(y+(radio-radio/2)*sin(angulo+pi+0.7)),color,0);

}
void initGameOver(void){

	sprintf(string, "GAME OVER");

	surfaceGO = TTF_RenderText_Solid(font, string, White);

	textureGO = GPU_CopyImageFromSurface(surfaceGO);

	sprintf(string, "Press i for one player, 1 for two players");

	surfaceGOb = TTF_RenderText_Solid(font, string, White);

	textureGOb = GPU_CopyImageFromSurface(surfaceGOb);

	
	rectGO.x=0;
	rectGO.y=0;
	rectGO.w=surfaceGO->w;
	rectGO.h=surfaceGO->h;

	rectGOb.x=0;
	rectGOb.y=0;
	rectGOb.w=surfaceGOb->w;
	rectGOb.h=surfaceGOb->h;
}

int main(void)
{   

	if ((Bullet = malloc(sizeof(BulletStruct) * limitBullet)) == NULL)
		return(memoryError());

	if ((Asteroid = malloc(sizeof(AsteroidStruct) * limitAsteroids)) == NULL)
		return(memoryError());

	if ((virtualScreen = malloc(sizeof (*virtualScreen) * limitX)) == NULL)
		return(memoryError());

	if ((Explosion = malloc(sizeof (*Explosion) * limitExplosions)) == NULL)
		return(memoryError());


	if ((queueHit = malloc(sizeof (*queueHit) * limitQueueHit)) == NULL)
		return(memoryError());

	for (contador = 0; contador < limitX; contador++)
	        if ((virtualScreen[contador] = malloc(sizeof(*virtualScreen[contador]) * limitY)) == NULL)
			return(memoryError());

	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
	        return (1);    

	shoot = Mix_LoadWAV( "shoot.wav" );
	die = Mix_LoadWAV( "die.wav" );
	explosion = Mix_LoadWAV( "explosion.wav" );
	nuke = Mix_LoadWAV( "nuke.wav" );
	gotBomb = Mix_LoadWAV( "getbomb.wav" );
	propLoop = Mix_LoadWAV( "fx_loop.wav" );
	propStart = Mix_LoadWAV( "fx_start.wav" );
	propStop = Mix_LoadWAV( "fx_stop.wav" );
	alien = Mix_LoadWAV( "alien.wav" );

	if( TTF_Init() == -1 )
		return (1);

	font = TTF_OpenFont( "hyperspace.otf", 30 );

	
  	srand(time(NULL));
	generateAsteroids(2);



	//intro();
	Mix_AllocateChannels(16);


	initVideo();
	initVS();
	initGameOver();

	drawScores();
	
	SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

	while (!quit) {
		//printf("%d\n", indexAsteroids);
                aTick = SDL_GetTicks();

		checkHits();
		readInputs();
		applyInputs();
		if (!flagsDead)
			movePlayer();
		if (!flagsBDead)
			movePlayerB();
		if (Alien.active)
			moveAlien();

		limitCheck();


// DIBUJADO

		if (!flagsGameOver){
			drawScores();		// A lo mejor dibujarlos en cada ciclo es un poco overkill...

			if (Bomb.active)
				drawBomb(Bomb.x, Bomb.y, threePidivtwo, Bomb.ratio, idBomb);
		
			if (Power.active)
				drawPower(Power.x, Power.y, threePidivtwo, Power.ratio, idPower);


			if (pressedAccel)
				if (!flagsDead)
					if (!flagsFrameSkip)
						drawProps(Player.x, Player.y, Player.rads, playerRatio, idExplosion);

			if (pressedBAccel)
				if (!flagsBDead)
					if (!flagsFrameSkip)
						drawPropsB(PlayerB.x, PlayerB.y, PlayerB.rads, playerBRatio, idExplosion);
	
		   	if (!flagsDead)	
				if (!flagsFrameSkip)
					drawShip(Player.x, Player.y, Player.rads, playerRatio,idPlayer);

		   	if (!flagsBDead)	
				if (!flagsFrameSkip)
					drawShipB(PlayerB.x, PlayerB.y, PlayerB.rads, playerBRatio,idPlayerB);

			if (Alien.active)
				drawAlien(Alien.x,Alien.y,Alien.rads,Alien.ratio,idAlien);


			if (!flagsFrameSkip)
				drawExplosions(idExplosion);


		}
		else{
			GPU_Blit(textureGO, &rectGO, renderer, 650, 300);
			GPU_Blit(textureGOb, &rectGOb, renderer, 620, 350);
		}
		if (!flagsFrameSkip){
			if (indexAsteroids>0)
				drawAsteroids(idAsteroid); 

	
			drawBullets();
		
		}
			


		if (!flagsFrameSkip)
		        GPU_Flip(renderer);
// DIBUJADO


                bTick = SDL_GetTicks();

// DELAY
	if (!flagsFrameSkip)
		SDL_Delay(retardo); 

// DELAY		
                cTick = SDL_GetTicks();

// BORRADO

		if (!flagsGameOver){

			if (Bomb.active)
				drawBomb(Bomb.x, Bomb.y, threePidivtwo, Bomb.ratio, 0);
		
			if (Power.active)
				drawPower(Power.x, Power.y, threePidivtwo, Power.ratio, 0);


			if (pressedAccel)
				if (!flagsDead){
					if (!flagsFrameSkip)
						drawProps(Player.x, Player.y, Player.rads, playerRatio, 0);
					propM += 0.05;
					if (propM > 0.1)
						propM = -0.1;
			}

    			if (!flagsDead)
				if (!flagsFrameSkip)
					drawShip(Player.x, Player.y, Player.rads, playerRatio,0);


			if (pressedBAccel)
				if (!flagsBDead){
					if (!flagsFrameSkip)
						drawPropsB(PlayerB.x, PlayerB.y, PlayerB.rads, playerBRatio, 0);
					propMB += 0.05;
					if (propMB > 0.1)
						propMB = -0.1;
			}

    			if (!flagsBDead)
				if (!flagsFrameSkip)
					drawShipB(PlayerB.x, PlayerB.y, PlayerB.rads, playerBRatio,0);


			if (Alien.active){
				drawAlien(Alien.x,Alien.y,Alien.rads,Alien.ratio,0);
				Mix_PlayChannel( -1, alien, 0 );

			}


		}

		if (!flagsFrameSkip){
			if (indexAsteroids>0)
				drawAsteroids(0);

			eraseBullets();

			drawExplosions(0);

		}	




		GPU_Clear(renderer);		// En windows por algun motivo hay que limpiar, si no flickerea

// BORRADO

		animateExplosions();
		if (indexAsteroids>0)
			moveAsteroids();

		pc++;

		otherChecks();

                dTick = SDL_GetTicks();

		dTick -= cTick - bTick;

		dTick -= aTick;
                if(dTick < SCREEN_TICKS_PER_FRAME ){
			retardo = SCREEN_TICKS_PER_FRAME - dTick;
			flagsFrameSkip = SDL_FALSE;
		}
		else
			flagsFrameSkip = SDL_TRUE;



		//printf("%d %d %d %d %d %d\n",indexAsteroids, indexBullet, indexExplosions, dTick,retardo,flagsFrameSkip);

	}
	endSDL();
	free(virtualScreen);
	free(Bullet);
	free(Asteroid);
	free(Explosion);
	free(queueHit);
	Mix_FreeChunk(die);
	Mix_FreeChunk(explosion);
	Mix_FreeChunk(shoot);
	Mix_FreeChunk(gotBomb);
	Mix_FreeChunk(propStart);
	Mix_FreeChunk(propStop);
	Mix_FreeChunk(propLoop);
	Mix_FreeChunk(alien);



	return 0;
}















