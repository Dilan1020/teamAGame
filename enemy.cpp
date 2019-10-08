
#include "bullet.h"
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Enemy.h"


SDL_Texture* Enemy::loadImage(std::string fname, SDL_Renderer *gRenderer) {
	SDL_Texture* newText = nullptr;

	SDL_Surface* startSurf = IMG_Load(fname.c_str());
	if (startSurf == nullptr) {
		std::cout << "Unable to load image " << fname << "! SDL Error: " << SDL_GetError() << std::endl;
		return nullptr;
	}

	newText = SDL_CreateTextureFromSurface(gRenderer, startSurf);
	if (newText == nullptr) {
		std::cout << "Unable to create texture from " << fname << "! SDL Error: " << SDL_GetError() << std::endl;
	}

	SDL_FreeSurface(startSurf);

	return newText;
}

    Enemy::Enemy(int x, int y, SDL_Renderer *gRenderer) :xPos{(double) x}, yPos{(double) y},width{100},height{75},xVelo{0},yVelo{0}{
      enemy_sprite = {(int) xPos, (int) yPos, width, height};
      enemy_hitbox = enemy_sprite;
      time_since_move = SDL_GetTicks();
      sprite1 = loadImage("sprites/EnemyPlane1.png", gRenderer);
      sprite2 = loadImage("sprites/EnemyPlane3.png", gRenderer);
    }

    void Enemy::renderEnemy(SDL_Renderer* gRenderer){
      if ((SDL_GetTicks() / ANIMATION_FREQ) % 2 == 1) {
      SDL_RenderCopyEx(gRenderer, sprite1, nullptr, &enemy_sprite, 0.0, nullptr, SDL_FLIP_NONE);
      }
      else {
        SDL_RenderCopyEx(gRenderer, sprite2, nullptr, &enemy_sprite, 0.0, nullptr, SDL_FLIP_NONE);
      }
      enemy_hitbox=enemy_sprite;
    }

    void Enemy::move(int player_x, int player_y)
    {
        time_since_move = SDL_GetTicks() - last_move;
       // move the enemy to the right if the player is moving right
       // want to "collide" when the enemy hits us
       if(xPos < (player_x - width))
         xPos += (double) (xVelo * time_since_move) / 1000;
       
       // move the enemy to the right if the player is moving right
       // want to "collide" when the enemy hits us
       if(xPos > (player_x + width))
         xPos -= (double) (xVelo * time_since_move) / 1000;
       
      // move the enemy down while the player is moving down
      if(yPos < (player_y - height))
        yPos -= (double) (yVelo * time_since_move) / 1000;

      // move the enemy up while the player is moving up 
      if(yPos > (player_y + height))
        yPos += (double) (yVelo * time_since_move) / 1000;

       enemy_sprite = {(int)xPos,(int)yPos,width,height};
       last_move = SDL_GetTicks();
    }


    int Enemy::getX(){
      return (int) xPos;
    }

    int Enemy::getY(){
      return (int) yPos;
    }

    void Enemy::setyVelo(int y){
      yVelo = y;
    }

    void Enemy::setxVelo(int x) {
      xVelo = x;
    }

    SDL_Rect* Enemy::getHitbox(){
      return &enemy_hitbox;
    }


    Bullet* Enemy::shoot()
    {
        Bullet* b = new Bullet(xPos+width+5,yPos+height/2,-300);

        return b;
    }