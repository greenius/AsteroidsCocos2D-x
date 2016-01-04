//
//  TitleLayer.h
//  Asteroids
//
//  Created by Clawoo on 9/18/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef __TITLELAYER_H__
#define __TITLELAYER_H__

#include "cocos2d.h"


class TitleLayer : public cocos2d::Layer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  
    
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::Scene* createScene();
    
	// implement the "static node()" method manually
	CREATE_FUNC(TitleLayer);
    
    void playButtonAction(Ref* pSender);
    void scoresButtonAction(Ref* pSender);
    void controlsButtonAction(Ref* pSender);
private:

};

#endif // __TITLELAYER_H__
