//
//  GameLayer.h
//  Asteroids
//
//  Created by Clawoo on 9/16/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef __GAMELAYER_H__
#define __GAMELAYER_H__

#include "cocos2d.h"
#include "Ship.h"

class GameLayer : public cocos2d::Layer
{
public:
    ~GameLayer();
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  
    void update(float dt);
    
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::Scene* createScene();
    
	// implement the "static node()" method manually
	CREATE_FUNC(GameLayer);


    void createAsteroidAt(cocos2d::Point position , int size);
    void createBullet();
    void startLevel();
    void resetShip();
    void gameOver();
    void backButtonAction(Ref* pSender);

private:
  void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
  void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
  void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);

    Ship *ship_;
	// To determine rotation
	float previousTouchAngle_, currentTouchAngle_;
    
	// To determine movement/shooting
    cocos2d::Point startTouchPoint_, endTouchPoint_;
    
    // Arrays used to keep track of all visible asteroids/bullets
    cocos2d::Vector<cocos2d::Sprite *> asteroids_;
    cocos2d::Vector<cocos2d::Sprite *> bullets_;
    
    // Used to determine the number of asteroids that appear
    int currentLevel_;

  cocos2d::EventListenerTouchAllAtOnce* listener;
};

#endif // __GAMELAYER_H__
