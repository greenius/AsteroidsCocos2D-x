//
//  Asteroid.cpp
//  Asteroids
//
//  Created by Clawoo on 9/18/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Asteroid.h"

USING_NS_CC;

Asteroid* Asteroid::spriteWithFile(const char *pszFileName)
{
    Asteroid *pobSprite = new Asteroid();
    if (pobSprite && pobSprite->initWithFile(pszFileName))
    {
        pobSprite->scheduleUpdate();
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
	return NULL;
}

void Asteroid::update(float dt)
{
    // Rotate (based on time interval between each frame)
    this->setRotation(this->getRotation() + dt * 15);
    
    // Move
    this->setPosition(Vec2(this->getPosition().x + velocity_.x, this->getPosition().y + velocity_.y));
    
    Size windowSize = Director::getInstance()->getWinSize();
    
    // If object moves off the bounds of the screen, make it appear on the other side
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

// Super-basic AABB collision detection
bool Asteroid::collidesWith(Sprite *obj)
{
    // Create two rectangles with CGRectMake, using each sprite's x/y position and width/height
    Rect ownRect = Rect(this->getPosition().x - this->getContentSize().width / 2,
                                this->getPosition().y - this->getContentSize().height / 2, 
                                this->getContentSize().width, 
                                this->getContentSize().height);
    
    Rect otherRect = Rect(obj->getPosition().x - obj->getContentSize().width / 2,
                                obj->getPosition().y - obj->getContentSize().height / 2, 
                                obj->getContentSize().width, 
                                obj->getContentSize().height);
    
    // Feed the results into CGRectIntersectsRect() which tells if the rectangles intersect (obviously)
    return ownRect.intersectsRect(otherRect);
}
