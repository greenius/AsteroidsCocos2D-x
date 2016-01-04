//
//  ControlsLayer.h
//  Asteroids
//
//  Created by Clawoo on 9/18/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#ifndef __CONTROLSLAYER_H__
#define __CONTROLSLAYER_H__

#include "cocos2d.h"


class ControlsLayer : public cocos2d::Layer
{
public:

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  
    
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::Scene* createScene();
    
	// implement the "static node()" method manually
	CREATE_FUNC(ControlsLayer);
    
    void backButtonAction(Ref* pSender);
    
private:
    
};

#endif // __CONTROLSLAYER_H__
