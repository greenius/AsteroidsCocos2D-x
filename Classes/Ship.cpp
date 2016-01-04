//
//  Ship.cpp
//  Asteroids
//
//  Created by Clawoo on 9/16/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Ship.h"

USING_NS_CC;

Ship* Ship::spriteWithFile(const char *pszFileName)
{
    Ship *pobSprite = new Ship();
    if (pobSprite && pobSprite->initWithFile(pszFileName))
    {
        pobSprite->scheduleUpdate();
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
	return NULL;
}

void Ship::update(float dt)
{
    this->setPosition(Vec2(this->getPosition().x + velocity_.x, this->getPosition().y + velocity_.y));
    
    Size windowSize = Director::getInstance()->getWinSize();
    
    if (this->getPosition().x < 0)
    {
        this->setPosition(Vec2(windowSize.width, this->getPosition().y));
    }
    else if (this->getPosition().x > windowSize.width)
    {
        this->setPosition(Vec2(0, this->getPosition().y));
    }
    
    if (this->getPosition().y < 0)
    {
        this->setPosition(Vec2(this->getPosition().x, windowSize.height));
    }
    else if (this->getPosition().y > windowSize.height)
    {
        this->setPosition(Vec2(this->getPosition().x, 0));
    }
}