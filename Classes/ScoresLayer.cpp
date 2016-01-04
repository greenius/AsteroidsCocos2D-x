//
//  ScoresLayer.cpp
//  Asteroids
//
//  Created by Clawoo on 9/18/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "ScoresLayer.h"
#include "TitleLayer.h"

USING_NS_CC;

Scene* ScoresLayer::createScene()
{
	// 'scene' is an autorelease object
	Scene *scene = Scene::create();
	
	// 'layer' is an autorelease object
	ScoresLayer *layer = ScoresLayer::create();
    
	// add layer as a child to scene
	scene->addChild(layer);
    
	// return the scene
	return scene;
}

bool ScoresLayer::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
    
    // Get window size
    Size windowSize = Director::getInstance()->getWinSize();
    
    Label *title = Label::createWithSystemFont("high scores", "Courier", 32.0);
    
    title->setPosition(Vec2(windowSize.width / 2, windowSize.height - title->getContentSize().height));
    
    // Add to layer
    this->addChild(title, 1);
    
  Label *scoresLabel = Label::createWithSystemFont("None", "Courier", 16.0, Size(windowSize.width, windowSize.height/3), TextHAlignment::CENTER);
    scoresLabel->setPosition(Point(windowSize.width/2, windowSize.height/2));

  MenuItemFont *backButton = MenuItemFont::create("back", std::bind(&ScoresLayer::backButtonAction, this, std::placeholders::_1));
    
    Menu *menu = Menu::createWithItem(backButton);
    menu->setPosition(Vec2(windowSize.width/2, scoresLabel->getPosition().y - scoresLabel->getContentSize().height));
    
    this->addChild(menu, 2);
    
    return true;
}

void ScoresLayer::backButtonAction(Ref* pSender)
{
    Director::getInstance()->replaceScene(TitleLayer::createScene());
}
