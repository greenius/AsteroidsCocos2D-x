//
//  Ship.h
//  Asteroids
//
//  Created by Clawoo on 9/16/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef __SHIP_H__
#define __SHIP_H__

#include "cocos2d.h"

class Ship : public cocos2d::Sprite
{
public:
    virtual void update(float dt);
	static Ship* spriteWithFile(const char *pszFileName);
    CC_SYNTHESIZE(cocos2d::Point, velocity_, Velocity);
	// implement the "static node()" method manually
	CREATE_FUNC(Ship);
};

#endif // __SHIP_H__