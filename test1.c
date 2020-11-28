#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_ttf.h>
#include<math.h>
#define GRAVITY 0.35
typedef struct
{
    float x,y;
    float dy,dx;
    int onBlock,facingRight,frame,time;

}Mario;
typedef struct
{
    int x,y,w,h,status;
}block;
typedef struct
{
    Mario mario;
    block ground1[200];
    block ground2[200];
    block middleBrick[14];
    block upperBrick[16];
    block upperTreasure[5];
    block middleTreasure[7];
    block stackBlock1[26];
    block stackBlock2[21];
    block stackBlock3[16];
    block stackBlock4[11];
    block stackBlock5[5];
    block stackBlock6[4];
    block stackBlock7[3];
    block stackBlock8[2];
    block tunnelBlock[3];
    block tunnelBlock2;
    block tunnelBlock3[2];
    block cloudBlock[50];
    block hillBlock[15];
    block upperCoin[5];
    block middleCoin[7];
    block castleBlock;

    //ForImages
    SDL_Texture *marioImage[3];
    SDL_Texture *block;
    SDL_Texture *brick;
    SDL_Texture *stackBlock;
    SDL_Texture *treasure[2];
    SDL_Texture *tunnel[3];
    SDL_Texture *cloud[4];
    SDL_Texture *hill;
    SDL_Texture *coin;
    SDL_Texture *castle;

    SDL_Renderer *renderer;
    //For Text
    SDL_Texture *font;
    SDL_Surface *message;

    int scroll;
    int score;
    int currentScreen;
    char points[50];
    int statusScreen;
}initiateM;

void loadImages(initiateM *game)
{
    SDL_Surface *surface=NULL;
      surface=IMG_Load("images/castle.png");
    if(surface==NULL)
    {
        printf("Couldn't load castle.png");
    }
    game->castle=SDL_CreateTextureFromSurface(game->renderer,surface);

    SDL_FreeSurface(surface);
     surface=IMG_Load("images/coin.png");
    if(surface==NULL)
    {
        printf("Couldn't load coin.png");
    }
    game->coin=SDL_CreateTextureFromSurface(game->renderer,surface);

    SDL_FreeSurface(surface);
     surface=IMG_Load("images/hill_block.png");
    if(surface==NULL)
    {
        printf("Couldn't load upper_block.png");
    }
    game->hill=SDL_CreateTextureFromSurface(game->renderer,surface);
    SDL_FreeSurface(surface);

    surface=IMG_Load("images/upper_block.png");
    if(surface==NULL)
    {
        printf("Couldn't load upper_block.png");
    }
    game->brick=SDL_CreateTextureFromSurface(game->renderer,surface);
    SDL_FreeSurface(surface);
    surface=IMG_Load("images/cloud_1.png");
    if(surface==NULL)
    {
        printf("Couldn't load cloud_1.png");
    }
    game->cloud[0]=SDL_CreateTextureFromSurface(game->renderer,surface);
    SDL_FreeSurface(surface);
    surface=IMG_Load("images/cloud_2.png");
    if(surface==NULL)
    {
        printf("Couldn't load cloud_2.png");
    }
    game->cloud[1]=SDL_CreateTextureFromSurface(game->renderer,surface);
    SDL_FreeSurface(surface);
    surface=IMG_Load("images/cloud_1.png");
    if(surface==NULL)
    {
        printf("Couldn't load cloud_1.png");
    }
    game->cloud[2]=SDL_CreateTextureFromSurface(game->renderer,surface);
    SDL_FreeSurface(surface);
    surface=IMG_Load("images/cloud_2.png");
    if(surface==NULL)
    {
        printf("Couldn't load cloud_2.png");
    }
    game->cloud[3]=SDL_CreateTextureFromSurface(game->renderer,surface);
    SDL_FreeSurface(surface);
    surface=IMG_Load("images/stack_block.png");
    if(surface==NULL)
    {
        printf("Couldn't load stack_block.png");
    }
    game->stackBlock=SDL_CreateTextureFromSurface(game->renderer,surface);
    SDL_FreeSurface(surface);

    surface=IMG_Load("images/ground_block.png");
    if(surface==NULL)
    {
        printf("Couldn't load ground_block.png");
    }
    game->block=SDL_CreateTextureFromSurface(game->renderer,surface);
    SDL_FreeSurface(surface);
    surface=IMG_Load("images/treasure_brick.png");
    if(surface==NULL)
    {
        printf("Couldn't load treasure_brick.png");
    }
    game->treasure[0]=SDL_CreateTextureFromSurface(game->renderer,surface);
    SDL_FreeSurface(surface);
    surface=IMG_Load("images/treasure_brick2.png");
    if(surface==NULL)
    {
        printf("Couldn't load treasure_brick2.png");
    }
    game->treasure[1]=SDL_CreateTextureFromSurface(game->renderer,surface);
    SDL_FreeSurface(surface);
      surface=IMG_Load("images/tunnel_01.png");
    if(surface==NULL)
    {
        printf("Couldn't load tunnel_01.png");
    }
    game->tunnel[0]=SDL_CreateTextureFromSurface(game->renderer,surface);
    SDL_FreeSurface(surface);
    surface=IMG_Load("images/tunnel_02.png");
    if(surface==NULL)
    {
        printf("Couldn't load tunnel_02.png");
    }
    game->tunnel[1]=SDL_CreateTextureFromSurface(game->renderer,surface);
    SDL_FreeSurface(surface);
     surface=IMG_Load("images/tunnel_03.png");
    if(surface==NULL)
    {
        printf("Couldn't load tunnel_03.png");
    }
    game->tunnel[2]=SDL_CreateTextureFromSurface(game->renderer,surface);
    SDL_FreeSurface(surface);
    surface=IMG_Load("images/man1.png");
    if(surface==NULL)
    {
        printf("Couldn't load man1.png");
    }
    game->marioImage[0]=SDL_CreateTextureFromSurface(game->renderer,surface);
    SDL_FreeSurface(surface);
    surface=IMG_Load("images/man3.png");
    if(surface==NULL)
    {
        printf("Couldn't load man3.png");
    }
    game->marioImage[1]=SDL_CreateTextureFromSurface(game->renderer,surface);
    SDL_FreeSurface(surface);
     surface=IMG_Load("images/man2.png");
    if(surface==NULL)
    {
        printf("Couldn't load man2.png");
    }
    game->marioImage[2]=SDL_CreateTextureFromSurface(game->renderer,surface);
    SDL_FreeSurface(surface);
}
void loadCastle(initiateM *game)
{
    game->castleBlock.w=384;
    game->castleBlock.h=384;
    game->castleBlock.x=9120;
    game->castleBlock.y=116;
}
void loadCoin(initiateM *game)
{
    for(int j=0,i=0;j<200;j++)
    {
     if(j==7||j==9||j==64||j==92||j==95||j==98||j==156)
        {
        game->middleCoin[i].w=48;
        game->middleCoin[i].h=48;
        game->middleCoin[i].x=j*48;
        game->middleCoin[i].y=252;
        game->middleCoin[i].status=0;
        i++;
        }

    }
    for(int j=0,i=0;j<200;j++)
    {
        if(j==8||j==95||j==115||j==116||j==80)
        {
        game->upperCoin[i].w=48;
        game->upperCoin[i].h=48;
        game->upperCoin[i].x=j*48;
        game->upperCoin[i].y=52;
        game->upperCoin[i].status=0;
        i++;
        }
    }
}
void loadClouds(initiateM *game)
{
    for(int j=0,n=0;j<50;j++)
    {
        n=rand()%4;
        game->cloudBlock[j].w=96;
        game->cloudBlock[j].h=96;
        game->cloudBlock[j].x=1.2*(j*n)*96;
        game->cloudBlock[j].y=n*20;
    }
}
void loadHill(initiateM *game)
{
    for(int j=0;j<15;j++)
    {
        game->hillBlock[j].w=320;
        game->hillBlock[j].h=350;
        game->hillBlock[j].x=320+j*640;
        game->hillBlock[j].y=380;
    }
}
void loadTunnel(initiateM *game)
{
    for(int j=0,i1=0,i3=0;j<100;j++)
    {
        if(j==7||j==74||j==83)
        {
            game->tunnelBlock[i1].w=96;
            game->tunnelBlock[i1].h=96;
            game->tunnelBlock[i1].x=j*96;
            game->tunnelBlock[i1].y=404;
        i1++;
        }
        if(j==12)
        {
            game->tunnelBlock2.w=96;
            game->tunnelBlock2.h=144;
            game->tunnelBlock2.x=j*96;
            game->tunnelBlock2.y=356;
        }
        if(j==22||j==16)
        {
            game->tunnelBlock3[i3].w=96;
            game->tunnelBlock3[i3].h=192;
            game->tunnelBlock3[i3].x=j*96;
            game->tunnelBlock3[i3].y=308;
        i3++;
        }
    }
}
void loadstackBlocks(initiateM *game)
{
   for(int j=0,i1=0,i2=0,i3=0,i4=0,i5=0,i6=0,i7=0,i8=0;j<200;j++)
    {
        if((j>=120&&j<=123)||(j>=126&&j<=129)||(j>=134&&j<=138)||(j>=141&&j<=144)||(j>=167&&j<=175))
        {
         game->stackBlock1[i1].w=48;
        game->stackBlock1[i1].h=48;
        game->stackBlock1[i1].x=j*48;
        game->stackBlock1[i1].y=452;
        i1++;
        }
        if((j>=121&&j<=123)||(j>=126&&j<=128)||(j>=135&&j<=138)||(j>=141&&j<=143)||(j>=168&&j<=175))
        {
        game->stackBlock2[i2].w=48;
        game->stackBlock2[i2].h=48;
        game->stackBlock2[i2].x=j*48;
        game->stackBlock2[i2].y=404;
        i2++;
        }
         if((j>=122&&j<=123)||j==126||j==127||(j>=136&&j<=138)||(j>=141&&j<=142)||(j>=169&&j<=175))
        {
        game->stackBlock3[i3].w=48;
        game->stackBlock3[i3].h=48;
        game->stackBlock3[i3].x=j*48;
        game->stackBlock3[i3].y=356;
        i3++;
        }
        if((j==123)||(j==126)||(j>=137&&j<=138)||(j==141)||(j>=170&&j<=175))
        {
        game->stackBlock4[i4].w=48;
        game->stackBlock4[i4].h=48;
        game->stackBlock4[i4].x=j*48;
        game->stackBlock4[i4].y=308;
        i4++;
        }
         if((j>=171&&j<=175))
        {
        game->stackBlock5[i5].w=48;
        game->stackBlock5[i5].h=48;
        game->stackBlock5[i5].x=j*48;
        game->stackBlock5[i5].y=260;
        i5++;
        }
        if((j>=172&&j<=175))
        {
        game->stackBlock6[i6].w=48;
        game->stackBlock6[i6].h=48;
        game->stackBlock6[i6].x=j*48;
        game->stackBlock6[i6].y=212;
        i6++;
        }
        if((j>=173&&j<=175))
        {
        game->stackBlock7[i7].w=48;
        game->stackBlock7[i7].h=48;
        game->stackBlock7[i7].x=j*48;
        game->stackBlock7[i7].y=164;
        i7++;
        }
        if(j==174||j==175)
        {
        game->stackBlock8[i8].w=48;
        game->stackBlock8[i8].h=48;
        game->stackBlock8[i8].x=j*48;
        game->stackBlock8[i8].y=116;
        i8++;
        }

    }

}
void loadTreasure(initiateM *game)
{
   for(int j=0,i=0;j<200;j++)
    {
        if(j==7||j==9||j==64||j==92||j==95||j==98||j==156)
        {
        game->middleTreasure[i].w=48;
        game->middleTreasure[i].h=48;
        game->middleTreasure[i].x=j*48;
        game->middleTreasure[i].y=300;
        game->middleTreasure[i].status=0;
        i++;
        }

    }
    for(int j=0,i=0;j<200;j++)
    {
        if(j==8||j==95||j==115||j==116||j==80)
        {
        game->upperTreasure[i].w=48;
        game->upperTreasure[i].h=48;
        game->upperTreasure[i].x=j*48;
        game->upperTreasure[i].y=100;
        game->upperTreasure[i].status=0;
        i++;
        }
    }

}
void loadBrick(initiateM *game)
{
    for(int j=0,i=0;j<200;j++)
    {
        if(j==6||j==8||j==10||j==63||j==65||j==80||j==86||j==87||j==104||j==115||j==116||j==154||j==155||j==157)
        {
        game->middleBrick[i].w=48;
        game->middleBrick[i].h=48;
        game->middleBrick[i].x=j*48;
        game->middleBrick[i].y=300;
        i++;
        }

    }
    for(int j=0,i=0;j<200;j++)
    {
        if(j==66||j==67||j==68||j==69||j==70||j==71||j==72||j==73||j==77||j==78||j==79||j==107||j==108||j==109||j==114||j==117)
        {
        game->upperBrick[i].w=48;
        game->upperBrick[i].h=48;
        game->upperBrick[i].x=j*48;
        game->upperBrick[i].y=100;
        i++;
        }

    }
}
void loadGround(initiateM *game)
{

    //initialize bricks
     for(int i=0,j=0;i<200;i++,j++)
    {
  if(j==55||j==139)
    {
        j=j+2;
    }
  if(j==72)
  {
      j=j+3;
  }

    game->ground1[i].w = 48;
    game->ground1[i].h = 48;
    game->ground1[i].x = j*48;
    game->ground1[i].y = 500;
    game->ground2[i].w = 48;
    game->ground2[i].h = 48;
    game->ground2[i].x = j*48;
    game->ground2[i].y = 548;
  }

}
void loadProperties(initiateM *game)
{   game->scroll=0;
    game->score=0;
    game->mario.x=320;
    game->mario.y=240;
    game->mario.dy=0;
    game->mario.dx=0;
    game->mario.onBlock=0;
    game->mario.facingRight=0;
    game->mario.frame=0;
    game->mario.time=0;
    game->currentScreen=1;
    game->statusScreen=1;

}


int eventLoop(SDL_Window *window,initiateM *game)
{
    int programRun=1;
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
         case SDL_QUIT:
               programRun=0;
               break;

          break;
        case SDL_KEYDOWN:
            {
                switch(event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    programRun=0;
                break;
                case SDLK_SPACE:
                    game->statusScreen=2;
                    break;
                case SDLK_UP:
                    if(game->mario.onBlock)
                    {
                    game->mario.dy=-12;
                    game->mario.onBlock=0;
                    }

                }
            }
        break;
        }
    }
    const Uint8 *state=SDL_GetKeyboardState(NULL);
    if(state[SDL_SCANCODE_RIGHT])
    {
     game->mario.dx+=0.5;
     if(game->mario.dx>6)
     {
         game->mario.dx=6;
     }
     game->mario.facingRight=1;
    }
    else if(state[SDL_SCANCODE_LEFT])
    {
     game->mario.dx-=0.5;
     if(game->mario.dx<-6)
     {
         game->mario.dx=-6;
     }
     game->mario.facingRight=0;
    }
    else
    {

        game->mario.dx=0;

        game->mario.frame=0;
    }

    return programRun;
}
void doRender(SDL_Renderer *renderer,initiateM *game)
{   //draw background sky blue
    SDL_SetRenderDrawColor(renderer,128, 128, 255, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer,0,0,255,255);
//screen1
if(game->statusScreen==1)

{
    for(int j=0,n=0;j<10;j++)
{   n=  j%4;
        SDL_Rect cloudRect1 = {game->cloudBlock[j].x, game->cloudBlock[j].y, game->cloudBlock[j].w, game->cloudBlock[j].h };
        SDL_RenderCopy(renderer, game->cloud[n], NULL, &cloudRect1);
}
    SDL_SetRenderDrawColor(renderer,140,60,0,255);
    SDL_Rect rectangle={180,140,400,200};
    SDL_RenderFillRect(renderer,&rectangle);
for(int i = 0; i < 50; i++)
  {
    SDL_Rect ledgeRect1 = {game->ground1[i].x, game->ground1[i].y, game->ground1[i].w, game->ground1[i].h };
    SDL_RenderCopy(renderer, game->block, NULL, &ledgeRect1);
     SDL_Rect ledgeRect2 = {game->ground2[i].x, game->ground2[i].y, game->ground2[i].w, game->ground2[i].h };
    SDL_RenderCopy(renderer, game->block, NULL, &ledgeRect2);

  }


    TTF_Font *fontLoad1 =NULL;
    fontLoad1 = TTF_OpenFont("fonts/Crazy_Pixel.ttf",100);
    if(fontLoad1==NULL)
    {
        printf("Couldnt Load Font");
    }
    SDL_Color color={255,255,255};
    game->message= TTF_RenderText_Solid(fontLoad1,"EASY",color);
    game->font= SDL_CreateTextureFromSurface(renderer,game->message);
    SDL_Rect textRect0={300,100,200,200};
    SDL_RenderCopy(renderer,game->font,NULL, &textRect0);
    game->message= TTF_RenderText_Solid(fontLoad1,"MARIO",color);
    game->font= SDL_CreateTextureFromSurface(renderer,game->message);
    SDL_Rect textRect={300,150,200,200};
    SDL_RenderCopy(renderer,game->font,NULL, &textRect);
    game->message= TTF_RenderText_Solid(fontLoad1,"Press [ SPACE ] to continue",color);
    game->font= SDL_CreateTextureFromSurface(renderer,game->message);
    SDL_Rect textRect2={290,430,200,80};
    SDL_RenderCopy(renderer,game->font,NULL, &textRect2);
}
//screen2
if(game->statusScreen==2)
{

for(int j=0;j<15;j++)
{
        SDL_Rect hillRect1 = {game->hillBlock[j].x+game->scroll, game->hillBlock[j].y, game->hillBlock[j].w, game->hillBlock[j].h };
        SDL_RenderCopy(renderer, game->hill, NULL, &hillRect1);
}

      //draw clouds
for(int j=0,n=0;j<50;j++)
{   n=  j%4;
        SDL_Rect cloudRect1 = {game->cloudBlock[j].x+game->scroll, game->cloudBlock[j].y, game->cloudBlock[j].w, game->cloudBlock[j].h };
        SDL_RenderCopy(renderer, game->cloud[n], NULL, &cloudRect1);
}


     //draw ground blocks;
     for(int i = 0; i < 200; i++)
  {
    SDL_Rect ledgeRect1 = {game->ground1[i].x+game->scroll, game->ground1[i].y, game->ground1[i].w, game->ground1[i].h };
    SDL_RenderCopy(renderer, game->block, NULL, &ledgeRect1);
     SDL_Rect ledgeRect2 = {game->ground2[i].x+game->scroll, game->ground2[i].y, game->ground2[i].w, game->ground2[i].h };
    SDL_RenderCopy(renderer, game->block, NULL, &ledgeRect2);

  }

  //draw bricks
  for(int j=0;j<15;j++)
  {
    SDL_Rect middlebrickRect = {game->middleBrick[j].x+game->scroll, game->middleBrick[j].y, game->middleBrick[j].w, game->middleBrick[j].h };
    SDL_RenderCopy(renderer, game->brick, NULL, &middlebrickRect);
  }
  for(int j=0;j<16;j++)
  {
    SDL_Rect upperbrickRect = {game->upperBrick[j].x+game->scroll, game->upperBrick[j].y, game->upperBrick[j].w, game->upperBrick[j].h };
    SDL_RenderCopy(renderer, game->brick, NULL, &upperbrickRect);
  }
  //draw stack blocks
 for(int j=0;j<26;j++)
  {

    SDL_Rect stack1 = {game->stackBlock1[j].x+game->scroll, game->stackBlock1[j].y, game->stackBlock1[j].w, game->stackBlock1[j].h };
    SDL_RenderCopy(renderer, game->stackBlock, NULL, &stack1);
  }
for(int j=0;j<21;j++)
  {

    SDL_Rect stack2 = {game->stackBlock2[j].x+game->scroll, game->stackBlock2[j].y, game->stackBlock2[j].w, game->stackBlock2[j].h };
    SDL_RenderCopy(renderer, game->stackBlock, NULL, &stack2);
  }
for(int j=0;j<16;j++)
  {

    SDL_Rect stack3 = {game->stackBlock3[j].x+game->scroll, game->stackBlock3[j].y, game->stackBlock3[j].w, game->stackBlock3[j].h };
    SDL_RenderCopy(renderer, game->stackBlock, NULL, &stack3);
  }
  for(int j=0;j<11;j++)
  {

    SDL_Rect stack4 = {game->stackBlock4[j].x+game->scroll, game->stackBlock4[j].y, game->stackBlock4[j].w, game->stackBlock4[j].h };
    SDL_RenderCopy(renderer, game->stackBlock, NULL, &stack4);
  }
  for(int j=0;j<5;j++)
  {

    SDL_Rect stack5 = {game->stackBlock5[j].x+game->scroll, game->stackBlock5[j].y, game->stackBlock5[j].w, game->stackBlock5[j].h };
    SDL_RenderCopy(renderer, game->stackBlock, NULL, &stack5);
  }
  for(int j=0;j<4;j++)
  {

    SDL_Rect stack6 = {game->stackBlock6[j].x+game->scroll, game->stackBlock6[j].y, game->stackBlock6[j].w, game->stackBlock6[j].h };
    SDL_RenderCopy(renderer, game->stackBlock, NULL, &stack6);
  }
  for(int j=0;j<3;j++)
  {

    SDL_Rect stack7 = {game->stackBlock7[j].x+game->scroll, game->stackBlock7[j].y, game->stackBlock7[j].w, game->stackBlock7[j].h };
    SDL_RenderCopy(renderer, game->stackBlock, NULL, &stack7);
  }
  for(int j=0;j<2;j++)
  {

    SDL_Rect stack8 = {game->stackBlock8[j].x+game->scroll, game->stackBlock8[j].y, game->stackBlock8[j].w, game->stackBlock8[j].h };
    SDL_RenderCopy(renderer, game->stackBlock, NULL, &stack8);
  }


  //draw treasure
  for(int j=0;j<7;j++)
  {
    SDL_Rect middletreasureRect = {game->middleTreasure[j].x+game->scroll, game->middleTreasure[j].y, game->middleTreasure[j].w, game->middleTreasure[j].h };
    SDL_RenderCopy(renderer, game->treasure[game->middleTreasure[j].status], NULL, &middletreasureRect);
  }

  for(int j=0;j<5;j++)
  {

    SDL_Rect uppertreasureRect = {game->upperTreasure[j].x+game->scroll, game->upperTreasure[j].y, game->upperTreasure[j].w, game->upperTreasure[j].h };
    SDL_RenderCopy(renderer, game->treasure[game->upperTreasure[j].status], NULL, &uppertreasureRect);
  }

    //draw tunnel
for(int j=0;j<3;j++)
{
        SDL_Rect tunnelRect1 = {game->tunnelBlock[j].x+game->scroll, game->tunnelBlock[j].y, game->tunnelBlock[j].w, game->tunnelBlock[j].h };
        SDL_RenderCopy(renderer, game->tunnel[0], NULL, &tunnelRect1);
}
        SDL_Rect tunnelRect2 = {game->tunnelBlock2.x+game->scroll, game->tunnelBlock2.y, game->tunnelBlock2.w, game->tunnelBlock2.h };
        SDL_RenderCopy(renderer, game->tunnel[1], NULL, &tunnelRect2);

        for(int j=0;j<2;j++)
{
        SDL_Rect tunnelRect3 = {game->tunnelBlock3[j].x+game->scroll, game->tunnelBlock3[j].y, game->tunnelBlock3[j].w, game->tunnelBlock3[j].h };
        SDL_RenderCopy(renderer, game->tunnel[2], NULL, &tunnelRect3);
}



//draw coin
    for(int j=0;j<7;j++)
  {
    if(((game->mario.y==348)&&((game->mario.x>(game->middleCoin[j].x-25))&&(game->mario.x<(game->middleCoin[j].x+48+6))))&&game->middleTreasure[j].status==0)
    {
        game->middleCoin[j].status=1;
        game->middleTreasure[j].status=1;
    }
    if((game->middleCoin[j].status==1))
    {
    SDL_Rect middlecoinRect = {game->middleCoin[j].x+game->scroll, game->middleCoin[j].y, game->middleCoin[j].w, game->middleCoin[j].h };
    SDL_RenderCopy(renderer, game->coin, NULL, &middlecoinRect);

    }
  }

  for(int j=0;j<5;j++)
  {if(((game->mario.y==148)&&((game->mario.x>(game->upperCoin[j].x-25))&&(game->mario.x<(game->upperCoin[j].x+48+6))))&&game->upperTreasure[j].status==0)
    {
        game->upperCoin[j].status=1;
        game->upperTreasure[j].status=1;
    }
if((game->upperCoin[j].status==1))
    {
    SDL_Rect uppercoinRect = {game->upperCoin[j].x+game->scroll, game->upperCoin[j].y, game->upperCoin[j].w, game->upperCoin[j].h };
    SDL_RenderCopy(renderer, game->coin, NULL, &uppercoinRect);
    }
  }
//draw castle
    SDL_Rect castleRect = {game->castleBlock.x+game->scroll, game->castleBlock.y, game->castleBlock.w, game->castleBlock.h };
    SDL_RenderCopy(renderer, game->castle, NULL, &castleRect);

  //draw mario
  SDL_Rect marioPlayer ={game->mario.x+game->scroll,game->mario.y,48,48};
  SDL_RenderCopyEx(game->renderer,game->marioImage[game->mario.frame],NULL,&marioPlayer,0,NULL,(game->mario.facingRight==0));

  //text
    TTF_Font *fontLoad2 =NULL;
    fontLoad2 = TTF_OpenFont("fonts/Crazy_Pixel.ttf",48);
    if(fontLoad2==NULL)
    {
        printf("Couldnt Load Font");
    }
    SDL_Color color={255,255,255};
    game->message= TTF_RenderText_Solid(fontLoad2,game->points,color);
    game->font= SDL_CreateTextureFromSurface(renderer,game->message);
    SDL_Rect textRect={330,10,100,100};
    SDL_RenderCopy(renderer,game->font,NULL, &textRect);
}
if(game->statusScreen==3)
{
     SDL_SetRenderDrawColor(renderer,0, 0, 0, 255);
    SDL_RenderClear(renderer);
    TTF_Font *fontLoad3 =NULL;
    fontLoad3 = TTF_OpenFont("fonts/Crazy_Pixel.ttf",200);
    if(fontLoad3==NULL)
    {
        printf("Couldnt Load Font");
    }
    SDL_Color color={255,255,255};
    game->message= TTF_RenderText_Solid(fontLoad3,"Game Over",color);
    game->font= SDL_CreateTextureFromSurface(renderer,game->message);
    SDL_Rect textRect={200,50,400,400};
    SDL_RenderCopy(renderer,game->font,NULL, &textRect);

     TTF_Font *fontLoad4 =NULL;
    fontLoad4 = TTF_OpenFont("fonts/Crazy_Pixel.ttf",200);
    if(fontLoad4==NULL)
    {
        printf("Couldnt Load Font");
    }

    game->message= TTF_RenderText_Solid(fontLoad4,game->points,color);
    game->font= SDL_CreateTextureFromSurface(renderer,game->message);
    SDL_Rect textRect2={300,20,100,100};
    SDL_RenderCopy(renderer,game->font,NULL, &textRect2);

}
if(game->statusScreen==4)
{
     SDL_SetRenderDrawColor(renderer,0, 0, 0, 255);
    SDL_RenderClear(renderer);
    TTF_Font *fontLoad3 =NULL;
    fontLoad3 = TTF_OpenFont("fonts/Crazy_Pixel.ttf",200);
    if(fontLoad3==NULL)
    {
        printf("Couldnt Load Font");
    }
    SDL_Color color={255,255,255};
    game->message= TTF_RenderText_Solid(fontLoad3,"Level Complete",color);
    game->font= SDL_CreateTextureFromSurface(renderer,game->message);
    SDL_Rect textRect={200,50,400,400};
    SDL_RenderCopy(renderer,game->font,NULL, &textRect);

     TTF_Font *fontLoad4 =NULL;
    fontLoad4 = TTF_OpenFont("fonts/Crazy_Pixel.ttf",200);
    if(fontLoad4==NULL)
    {
        printf("Couldnt Load Font");
    }

    game->message= TTF_RenderText_Solid(fontLoad4,game->points,color);
    game->font= SDL_CreateTextureFromSurface(renderer,game->message);
    SDL_Rect textRect2={300,20,100,100};
    SDL_RenderCopy(renderer,game->font,NULL, &textRect2);

}
    SDL_RenderPresent(renderer);


    //temporary_only
    game->scroll= -game->mario.x+320;
}

void collisionDetectGround(initiateM *game)
{
//collision check with bricks
for(int i = 0; i < 200; i++)
  {
    float mw = 48, mh = 48;
    float mx = game->mario.x, my = game->mario.y;
    float bx = game->ground1[i].x, by = game->ground1[i].y, bw = game->ground1[i].w, bh = game->ground1[i].h;

 if((mx < bx && mx+mw>bx)||(mx==bx)||(mx+mw>bx+bw&&mx<bx+bw))
    {
      //land collide
      if(my+mh > by && my < by &&game->mario.dy>0)
      {
        //correct y
        game->mario.y = by-mh;
        my = by-mh;

        game->mario.dy=0;
         game->mario.onBlock=1;
      }
    }

  }


}
void collisionDetectmiddleBrick(initiateM *game)
{
//collision check with bricks
for(int i = 0; i < 14; i++)
  {
    float mw = 48, mh = 48;
    float mx = game->mario.x, my = game->mario.y;
    float bx = game->middleBrick[i].x, by = game->middleBrick[i].y, bw = game->middleBrick[i].w, bh = game->middleBrick[i].h;

 if((mx < bx && mx+mw>bx)||(mx==bx)||(mx+mw>bx+bw&&mx<bx+bw))
    {
      //top collide
      if(my < by+bh && my+mh > by+bh )
      {
        //correct y
        game->mario.y = by+bh;
        my = by+bh;

        game->mario.dy=0;

      }
    }
    if(((mx<bx)&&(mx+mw>bx))||(mx<(bx+bw)&&(mx+mw)>(bx+bw))||mx==bx)
    {
      //land collide
      if(my+mh > by && my < by &&game->mario.dy>0)
      {
        //correct y
        game->mario.y = by-mh;
        my = by-mh;

        game->mario.dy=0;
         game->mario.onBlock=1;
      }
    }


    if((my+mh > (by+bh)&&(my<(by+bh))) || (my<by&&(my+mh)>by))
    {
      //right side collide
      if(mx < bx+bw && mx+mw > bx+bw)
      {
        //correct x
        game->mario.x = bx+bw;
        mx = bx+bw;
        game->mario.dx=0;

      }
      //left side collide
      else if(mx+mw > bx && mx < bx )
      {
        //correct x
        game->mario.x = bx-mw;
        mx = bx-mw;
        game->mario.dx=0;
      }
    }
  }
}
void collisionDetectupperBrick(initiateM *game)
{
//collision check with upper bricks
for(int i = 0; i < 16; i++)
  {
    float mw = 48, mh = 48;
    float mx = game->mario.x, my = game->mario.y;
    float bx = game->upperBrick[i].x, by = game->upperBrick[i].y, bw = game->upperBrick[i].w, bh = game->upperBrick[i].h;

 if((mx < bx && mx+mw>bx)||(mx==bx)||(mx+mh>bx+bh&&mx<bx+bh))
    {
      //top collide
      if(my < by+bh && my+mh > by+bh )
      {
        //correct y
        game->mario.y = by+bh;
        my = by+bh;

        game->mario.dy=0;

      }
    }
if(((mx<bx)&&(mx+mw>bx))||(mx<(bx+bw)&&(mx+mw)>(bx+bw))||mx==bx)
    {
      //land collide
      if(my+mh > by && my < by)
      {
        //correct y
        game->mario.y = by-mh;
        my = by-mh;

        game->mario.dy=0;
         game->mario.onBlock=1;
      }
    }

    if((my==by)||((my<by)&&(my+mh)>by)||(my<by+bh&&my+mh>by+bh))
    {
      //right side collide
      if(mx < bx+bw && mx+mw > bx+bw)
      {
        //correct x
        game->mario.x = bx+bw;
        mx = bx+bw;
        game->mario.dx=0;

      }
      //left side collide
      else if(mx+mw > bx && mx < bx )
      {
        //correct x
        game->mario.x = bx-mw;
        mx = bx-mw;
        game->mario.dx=0;
      }
    }
  }
}
void collisionDetectCastle(initiateM *game)
{

    float mw = 48, mh = 48;
    float mx = game->mario.x, my = game->mario.y;
    float bx = game->castleBlock.x, by = game->castleBlock.y, bw = game->castleBlock.w, bh = game->castleBlock.h;


   if(((mx<bx)&&(mx+mw>bx))||(mx<(bx+bw)&&(mx+mw)>(bx+bw))||mx==bx||(mx>bx&&mx+mw<bx+bw)||(mx+mw==by+bw))
    {
      //land collide
      if(my+mh > by && my < by)
      {
        //correct y
        game->mario.y = by-mh;
        my = by-mh;

        game->mario.dy=0;
       game->mario.onBlock=1;
       game->statusScreen=4;
       SDL_Delay(300);
      }
    }

 if((my==by)||((my<by)&&(my+mh)>by)||(my<by+bh&&my+mh>by+bh)||(my>by&&my+mh<by+bh)||((my+mh)==(by+bh)))
    {


      //left side collide
       if(mx+mw > bx && mx < bx )
      {
        //correct x
        game->mario.x = bx-mw;
        mx = bx-mw;
        game->statusScreen=4;
        SDL_Delay(300);

      }
    }
}
void collisionDetectTunnel(initiateM *game)
{
//collision first tunnel
for(int i = 0; i < 3; i++)
  {
    float mw = 48, mh = 48;
    float mx = game->mario.x, my = game->mario.y;
    float bx = game->tunnelBlock[i].x, by = game->tunnelBlock[i].y, bw = game->tunnelBlock[i].w, bh = game->tunnelBlock[i].h;


   if(((mx<bx)&&(mx+mw>bx))||(mx<(bx+bw)&&(mx+mw)>(bx+bw))||mx==bx||(mx>bx&&mx+mw<bx+bw)||(mx+mw==by+bw))
    {
      //land collide
      if(my+mh > by && my < by)
      {
        //correct y
        game->mario.y = by-mh;
        my = by-mh;

        game->mario.dy=0;
       game->mario.onBlock=1;
      }
    }

 if((my==by)||((my<by)&&(my+mh)>by)||(my<by+bh&&my+mh>by+bh)||(my>by&&my+mh<by+bh)||((my+mh)==(by+bh)))
    {
      //right side collide
      if(mx < bx+bw && mx+mw > bx+bw)
      {
        //correct x
        game->mario.x = bx+bw;
        mx = bx+bw;


      }
      //left side collide
      else if(mx+mw > bx && mx < bx )
      {
        //correct x
        game->mario.x = bx-mw;
        mx = bx-mw;

      }
    }
  }
  //second tunnel
   float mw = 48, mh = 48;
    float mx = game->mario.x, my = game->mario.y;
    float bx = game->tunnelBlock2.x, by = game->tunnelBlock2.y, bw = game->tunnelBlock2.w, bh = game->tunnelBlock2.h;


  if(((mx<bx)&&(mx+mw>bx))||(mx<(bx+bw)&&(mx+mw)>(bx+bw))||mx==bx||(mx>bx&&mx+mw<bx+bw)||(mx+mw==by+bw))
    {
      //land collide
      if(my+mh > by && my < by)
      {
        //correct y
        game->mario.y = by-mh;
        my = by-mh;

        game->mario.dy=0;
         game->mario.onBlock=1;
      }
    }
 if((my==by)||((my<by)&&(my+mh)>by)||(my<by+bh&&my+mh>by+bh)||(my>by&&my+mh<by+bh)||((my+mh)==(by+bh)))
    {
      //right side collide
      if(mx < bx+bw && mx+mw > bx+bw)
      {
        //correct x
        game->mario.x = bx+bw;
        mx = bx+bw;

        game->mario.dx=0;
      }
      //left side collide
      else if(mx+mw > bx && mx < bx )
      {
        //correct x
        game->mario.x = bx-mw;
        mx = bx-mw;
        game->mario.dx=0;
      }
    }

    //third tunnel
    for(int i = 0; i < 2; i++)
  {
    float mw = 48, mh = 48;
    float mx = game->mario.x, my = game->mario.y;
    float bx = game->tunnelBlock3[i].x, by = game->tunnelBlock3[i].y, bw = game->tunnelBlock3[i].w, bh = game->tunnelBlock3[i].h;


  if(((mx<bx)&&(mx+mw>bx))||(mx<(bx+bw)&&(mx+mw)>(bx+bw))||mx==bx||(mx>bx&&mx+mw<bx+bw)||(mx+mw==by+bw))
    {
      //land collide
      if(my+mh > by && my < by)
      {
        //correct y
        game->mario.y = by-mh;
        my = by-mh;

        game->mario.dy=0;
         game->mario.onBlock=1;
      }
    }

   if((my==by)||((my<by)&&(my+mh)>by)||(my<by+bh&&my+mh>by+bh)||(my>by&&my+mh<by+bh)||((my+mh)==(by+bh)))
    {
      //right side collide
      if(mx < bx+bw && mx+mw > bx+bw)
      {
        //correct x
        game->mario.x = bx+bw;
        mx = bx+bw;

        game->mario.dx=0;
      }
      //left side collide
      else if(mx+mw > bx && mx < bx )
      {
        //correct x
        game->mario.x = bx-mw;
        mx = bx-mw;
        game->mario.dx=0;
      }
    }
  }
}
void collisionstackBlocks(initiateM *game)
{   //stack 1
int n;
n=26;
    for(int i=0;i<26;i++)
    {
         float mw = 48, mh = 48;
    float mx = game->mario.x, my = game->mario.y;
    float bx = game->stackBlock1[i].x, by = game->stackBlock1[i].y, bw = game->stackBlock1[i].w, bh = game->stackBlock1[i].h;
if(i!=(n-1))
{
       if(((mx<bx)&&(mx+mw>bx))||(mx<(bx+bw)&&(mx+mw)>(bx+bw))||mx==bx)
    {
      //land collide
      if(my+mh > by && my < by &&game->mario.dy>0)
      {
        //correct y
        game->mario.y = by-mh;
        my = by-mh;

        game->mario.dy=0;
         game->mario.onBlock=1;
      }
    }
}
    if((my+mh > (by+bh)&&(my<(by+bh))) || (my<by&&(my+mh)>by)||my==by)
    {
      //right side collide
      if(mx < bx+bw && mx+mw > bx+bw)
      {
        //correct x
        game->mario.x = bx+bw;
        mx = bx+bw;
        game->mario.dx=0;

      }
      //left side collide
      else if(mx+mw > bx && mx < bx )
      {
        //correct x
        game->mario.x = bx-mw;
        mx = bx-mw;
        game->mario.dx=0;
      }
    }
    }

 //stack 2
 n=21;
    for(int i=0;i<21;i++)
    {
         float mw = 48, mh = 48;
    float mx = game->mario.x, my = game->mario.y;
    float bx = game->stackBlock2[i].x, by = game->stackBlock2[i].y, bw = game->stackBlock2[i].w, bh = game->stackBlock2[i].h;

if(i!=(n-1))
{
     if(((mx<bx)&&(mx+mw>bx))||(mx<(bx+bw)&&(mx+mw)>(bx+bw))||mx==bx)
    {
      //land collide
      if(my+mh > by && my < by &&game->mario.dy>0)
      {
        //correct y
        game->mario.y = by-mh;
        my = by-mh;

        game->mario.dy=0;
         game->mario.onBlock=1;
      }
    }
}
   if((my+mh > (by+bh)&&(my<(by+bh))) || (my<by&&(my+mh)>by)||my==by)
    {
      //right side collide
      if(mx < bx+bw && mx+mw > bx+bw)
      {
        //correct x
        game->mario.x = bx+bw;
        mx = bx+bw;
        game->mario.dx=0;

      }
      //left side collide
      else if(mx+mw > bx && mx < bx )
      {
        //correct x
        game->mario.x = bx-mw;
        mx = bx-mw;
        game->mario.dx=0;
      }
    }
    }

     //stack 3
     n=16;
    for(int i=0;i<16;i++)
    {
         float mw = 48, mh = 48;
    float mx = game->mario.x, my = game->mario.y;
    float bx = game->stackBlock3[i].x, by = game->stackBlock3[i].y, bw = game->stackBlock3[i].w, bh = game->stackBlock3[i].h;
if(i!=(n-1))
{
     if(((mx<bx)&&(mx+mw>bx))||(mx<(bx+bw)&&(mx+mw)>(bx+bw))||mx==bx)
    {
      //land collide
      if(my+mh > by && my < by &&game->mario.dy>0)
      {
        //correct y
        game->mario.y = by-mh;
        my = by-mh;

        game->mario.dy=0;
         game->mario.onBlock=1;
      }
    }
}
   if((my+mh > (by+bh)&&(my<(by+bh))) || (my<by&&(my+mh)>by)||my==by)
    {
      //right side collide
      if(mx < bx+bw && mx+mw > bx+bw)
      {
        //correct x
        game->mario.x = bx+bw;
        mx = bx+bw;
        game->mario.dx=0;

      }
      //left side collide
      else if(mx+mw > bx && mx < bx )
      {
        //correct x
        game->mario.x = bx-mw;
        mx = bx-mw;
        game->mario.dx=0;
      }
    }
    }

     //stack 4
     n=11;
    for(int i=0;i<11;i++)
    {
         float mw = 48, mh = 48;
    float mx = game->mario.x, my = game->mario.y;
    float bx = game->stackBlock4[i].x, by = game->stackBlock4[i].y, bw = game->stackBlock4[i].w, bh = game->stackBlock4[i].h;

if(i!=(n-1))
{
     if(((mx<bx)&&(mx+mw>bx))||(mx<(bx+bw)&&(mx+mw)>(bx+bw))||mx==bx)
    {
      //land side collide
      if(my+mh > by && my < by &&game->mario.dy>0)
      {
        //correct y
        game->mario.y = by-mh;
        my = by-mh;

        game->mario.dy=0;
         game->mario.onBlock=1;
      }
    }
}
  if((my+mh > (by+bh)&&(my<(by+bh))) || (my<by&&(my+mh)>by)||my==by)
    {
      //right side collide
      if(mx < bx+bw && mx+mw > bx+bw)
      {
        //correct x
        game->mario.x = bx+bw;
        mx = bx+bw;
        game->mario.dx=0;

      }
      //left side collide
      else if(mx+mw > bx && mx < bx )
      {
        //correct x
        game->mario.x = bx-mw;
        mx = bx-mw;
        game->mario.dx=0;
      }
    }
    }

     //stack 5
     n=5;
    for(int i=0;i<5;i++)
    {
         float mw = 48, mh = 48;
    float mx = game->mario.x, my = game->mario.y;
    float bx = game->stackBlock5[i].x, by = game->stackBlock5[i].y, bw = game->stackBlock5[i].w, bh = game->stackBlock5[i].h;

if(i!=(n-1))
{

    if(((mx<bx)&&(mx+mw>bx))||(mx<(bx+bw)&&(mx+mw)>(bx+bw))||mx==bx)
    {
      //land collide
      if(my+mh > by && my < by &&game->mario.dy>0)
      {
        //correct y
        game->mario.y = by-mh;
        my = by-mh;

        game->mario.dy=0;
         game->mario.onBlock=1;
      }
    }
}
    if((my+mh > (by+bh)&&(my<(by+bh))) || (my<by&&(my+mh)>by)||my==by)
    {
      //right side collide
      if(mx < bx+bw && mx+mw > bx+bw)
      {
        //correct x
        game->mario.x = bx+bw;
        mx = bx+bw;
        game->mario.dx=0;

      }
      //left side collide
      else if(mx+mw > bx && mx < bx )
      {
        //correct x
        game->mario.x = bx-mw;
        mx = bx-mw;
        game->mario.dx=0;
      }
    }
    }

     //stack 6
     n=4;
    for(int i=0;i<4;i++)
    {
         float mw = 48, mh = 48;
    float mx = game->mario.x, my = game->mario.y;
    float bx = game->stackBlock6[i].x, by = game->stackBlock6[i].y, bw = game->stackBlock6[i].w, bh = game->stackBlock6[i].h;

if(i!=(n-1))
{
    if(((mx<bx)&&(mx+mw>bx))||(mx<(bx+bw)&&(mx+mw)>(bx+bw))||mx==bx)
    {
      //land collide
      if(my+mh > by && my < by &&game->mario.dy>0)
      {
        //correct y
        game->mario.y = by-mh;
        my = by-mh;

        game->mario.dy=0;
         game->mario.onBlock=1;
      }
    }
}
   if((my+mh > (by+bh)&&(my<(by+bh))) || (my<by&&(my+mh)>by)||my==by)
    {
      //right side collide
      if(mx < bx+bw && mx+mw > bx+bw)
      {
        //correct x
        game->mario.x = bx+bw;
        mx = bx+bw;
        game->mario.dx=0;

      }
      //left side collide
      else if(mx+mw > bx && mx < bx )
      {
        //correct x
        game->mario.x = bx-mw;
        mx = bx-mw;
        game->mario.dx=0;
      }
    }
    }

     //stack 7
    n=3;
    for(int i=0;i<3;i++)
    {
         float mw = 48, mh = 48;
    float mx = game->mario.x, my = game->mario.y;
    float bx = game->stackBlock7[i].x, by = game->stackBlock7[i].y, bw = game->stackBlock7[i].w, bh = game->stackBlock7[i].h;

if(i!=(n-1))
{

    if(((mx<bx)&&(mx+mw>bx))||(mx<(bx+bw)&&(mx+mw)>(bx+bw))||mx==bx)
    {
      //land collide
      if(my+mh > by && my < by &&game->mario.dy>0)
      {
        //correct y
        game->mario.y = by-mh;
        my = by-mh;

        game->mario.dy=0;
         game->mario.onBlock=1;
      }
    }
}
   if((my+mh > (by+bh)&&(my<(by+bh))) || (my<by&&(my+mh)>by)||my==by)
    {
      //right side collide
      if(mx < bx+bw && mx+mw > bx+bw)
      {
        //correct x
        game->mario.x = bx+bw;
        mx = bx+bw;
        game->mario.dx=0;

      }
      //left side collide
      else if(mx+mw > bx && mx < bx )
      {
        //correct x
        game->mario.x = bx-mw;
        mx = bx-mw;
        game->mario.dx=0;
      }
    }
    }

     //stack 8
     n=2;
    for(int i=0;i<2;i++)
    {
         float mw = 48, mh = 48;
    float mx = game->mario.x, my = game->mario.y;
    float bx = game->stackBlock8[i].x, by = game->stackBlock8[i].y, bw = game->stackBlock8[i].w, bh = game->stackBlock8[i].h;

        if(((mx<bx)&&(mx+mw>bx))||(mx<(bx+bw)&&(mx+mw)>(bx+bw))||mx==bx)
    {
      //land collide
      if(my+mh > by && my < by &&game->mario.dy>0)
      {
        //correct y
        game->mario.y = by-mh;
        my = by-mh;

        game->mario.dy=0;
         game->mario.onBlock=1;
      }
    }
    if((my+mh > (by+bh)&&(my<(by+bh))) || (my<by&&(my+mh)>by)||my==by)
    {
      //right side collide
      if(mx < bx+bw && mx+mw > bx+bw)
      {
        //correct x
        game->mario.x = bx+bw;
        mx = bx+bw;
        game->mario.dx=0;

      }
      //left side collide
      else if(mx+mw > bx && mx < bx )
      {
        //correct x
        game->mario.x = bx-mw;
        mx = bx-mw;
        game->mario.dx=0;
      }
    }
    }
}
void collisionDetectTreasure(initiateM *game)
{
//collision check with upper treasure
for(int i = 0; i < 5; i++)
  {
    float mw = 48, mh = 48;
    float mx = game->mario.x, my = game->mario.y;
    float bx = game->upperTreasure[i].x, by = game->upperTreasure[i].y, bw = game->upperTreasure[i].w, bh = game->upperTreasure[i].h;

    if((mx < bx && mx+mw>bx)||(mx==bx)||(mx+mh>bx+bh&&mx<bx+bh))
    {
      //top collide
      if(my < by+bh && my+mh > by+bh )
      {
        //correct y
        game->mario.y = by+bh;
        my = by+bh;

        game->mario.dy=0;

      }
    }
  if(((mx<bx)&&(mx+mw>bx))||(mx<(bx+bw)&&(mx+mw)>(bx+bw))||mx==bx||(mx>bx&&mx+mw<bx+bw))
    {
      //land collide
      if(my+mh > by && my < by)
      {
        //correct y
        game->mario.y = by-mh;
        my = by-mh;

        game->mario.dy=0;
         game->mario.onBlock=1;
      }
    }


   if((my+mh > (by+bh)&&(my<(by+bh))) || (my<by&&(my+mh)>by)||my==by)
    {
      //right side collide
      if((mx < bx+bw && mx+mw > bx+bw))
      {
        //correct x
        game->mario.x = bx+bw;
        mx = bx+bw;
        game->mario.dx=0;

      }
      //left side collide
      else if(mx+mw > bx && mx < bx )
      {
        //correct x
        game->mario.x = bx-mw;
        mx = bx-mw;
        game->mario.dx=0;
      }
    }


  }


  //collision check with middle treasure
for(int i = 0; i < 7; i++)
  {
    float mw = 48, mh = 48;
    float mx = game->mario.x, my = game->mario.y;
    float bx = game->middleTreasure[i].x, by = game->middleTreasure[i].y, bw = game->middleTreasure[i].w, bh = game->middleTreasure[i].h;

    if((mx < bx && mx+mw>bx)||(mx==bx)||(mx+mh>bx+bh&&mx<bx+bh))
    {
     //top collide
      if(my < by+bh && my+mh > by+bh )
      {
        //correct y
        game->mario.y = by+bh;
        my = by+bh;

        game->mario.dy=0;

      }
    }

     if(((mx<bx)&&(mx+mw>bx))||(mx<(bx+bw)&&(mx+mw)>(bx+bw))||mx==bx||(mx>bx&&mx+mw<bx+bw))
    {
      //land collide
      if(my+mh > by && my < by)
      {
        //correct y
        game->mario.y = by-mh;
        my = by-mh;

        game->mario.dy=0;
         game->mario.onBlock=1;
      }
    }


  if((my+mh > (by+bh)&&(my<(by+bh))) || (my<by&&(my+mh)>by)||my==by)
    {
      //right side collide
      if(mx < bx+bw && mx+mw > bx+bw)
      {
        //correct x
        game->mario.x = bx+bw;
        mx = bx+bw;
        game->mario.dx=0;

      }
      //left side collide
      else if(mx+mw > bx && mx < bx )
      {
        //correct x
        game->mario.x = bx-mw;
        mx = bx-mw;
        game->mario.dx=0;
      }
    }
  }
}
void statusAlive(initiateM *game)
{
    if(game->mario.y>=580)
    {
        SDL_Delay(300);
        game->statusScreen=3;
    }

}
void processGravity(initiateM *game)
{   game->mario.time++;
    game->mario.y+=game->mario.dy;
    game->mario.x+=game->mario.dx;
    game->mario.dy+=GRAVITY;
    if(game->mario.dx!=0 && game->mario.onBlock==1)
    {
        if(game->mario.time%5==0)
        {
            if(game->mario.frame==1)
            {
                game->mario.frame=0;
            }
            else
                game->mario.frame=1;
        }
    }
    if(game->mario.onBlock!=1)
    {
        game->mario.frame=2;
    }
}
void coinCheck(initiateM *game)
{   //middle coin
 for(int i = 0; i < 7; i++)
 {
    float mw = 48, mh = 48;
    float mx = game->mario.x, my = game->mario.y;
    float bx = game->middleCoin[i].x, by = game->middleCoin[i].y, bw = game->middleCoin[i].w, bh = game->middleCoin[i].h;
    if(game->middleCoin[i].status==1)
    {

    if(my+mh > by && my<by+bh)
    {
      //right side collide
      if(mx < bx+bw && mx+mw > bx+bw)
      {
        game->middleCoin[i].status=0;
        game->score=game->score+100;
        sprintf(game->points,"SCORE : %d",game->score);
        printf("You Scored");


      }
      //left side collide
      else if(mx+mw > bx && mx < bx )
      {
        //correct x
        game->middleCoin[i].status=0;

        game->score=game->score+100;
     sprintf(game->points,"SCORE : %d",game->score);
        printf("You Scored");

      }
    }
    }
}

 for(int i = 0; i < 5; i++)
 {
    float mw = 48, mh = 48;
    float mx = game->mario.x, my = game->mario.y;
    float bx = game->upperCoin[i].x, by = game->upperCoin[i].y, bw = game->upperCoin[i].w, bh = game->upperCoin[i].h;
    if(game->upperCoin[i].status==1)
    {

    if(my+mh > by && my<by+bh)
    {
      //right side collide
      if(mx < bx+bw && mx+mw > bx+bw)
      {
        game->upperCoin[i].status=0;
        game->score=game->score+100;
        sprintf(game->points,"SCORE : %d",game->score);




      }
      //left side collide
      else if(mx+mw > bx && mx < bx )
      {
        //correct x
        game->upperCoin[i].status=0;
        game->score=game->score+100;
        sprintf(game->points,"SCORE : %d",game->score);


      }
    }
    }
}
}

int main(int argc,char *argv[])
{   initiateM game;
    int programRun=1;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    window=SDL_CreateWindow("Mario",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,720,580,0);
    renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    game.renderer=renderer;
  //text
    game.score=0;





    loadProperties(&game);
    loadImages(&game);
    loadCastle(&game);
    loadTunnel(&game);
    loadGround(&game);
    loadClouds(&game);
    loadHill(&game);
    loadBrick(&game);
    loadTreasure(&game);
    loadCoin(&game);
    loadstackBlocks(&game);
    sprintf(game.points,"SCORE : %d",game.score);
    while(programRun)
    {
    programRun=eventLoop(window,&game);
    statusAlive(&game);
    collisionDetectCastle(&game);
    collisionDetectupperBrick(&game);
    collisionDetectmiddleBrick(&game);
    collisionDetectGround(&game);
    collisionDetectTunnel(&game);
    collisionDetectTreasure(&game);
    collisionstackBlocks(&game);
    processGravity(&game);
    collisionDetectTreasure(&game);
    doRender(renderer,&game);

    coinCheck(&game);

    SDL_Delay(10);
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    TTF_Quit();
    SDL_Quit();
    return 0;
}
