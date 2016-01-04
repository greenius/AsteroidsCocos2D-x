//
//  ControlsLayer.cpp
//  Asteroids
//
//  Created by Clawoo on 9/18/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "ControlsLayer.h"
#include "TitleLayer.h"

USING_NS_CC;

Scene* ControlsLayer::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	
	// 'layer' is an autorelease object
	auto layer = ControlsLayer::create();
    
	// add layer as a child to scene
	scene->addChild(layer);
    
	// return the scene
	return scene;
}

bool ControlsLayer::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
    
    // Get window size
    Size windowSize = Director::getInstance()->getWinSize();
    
    Label *title = Label::createWithSystemFont("how to play", "Courier", 32.0);
    
    title->setPosition(Vec2(windowSize.width / 2, windowSize.height - title->getContentSize().height));
    
    // Add to layer
    this->addChild(title, 1);
    
    Label *controlsLabel = Label::createWithSystemFont("tap = shoot\npinch = rotate\nswipe = move",
                                                       "Courier",
                                                       16.0,
                                                       Size(windowSize.width, windowSize.height / 3),
                                                       TextHAlignment::CENTER
);

    controlsLabel->setPosition(Point(windowSize.width/2, windowSize.height/2));
    this->addChild(controlsLabel);
    
  MenuItemFont *backButton = MenuItemFont::create("back", std::bind(&ControlsLayer::backButtonAction, this, std::placeholders::_1));
    
    Menu *menu = Menu::createWithItem(backButton);
    menu->setPosition(Vec2(windowSize.width/2, controlsLabel->getPosition().y - controlsLabel->getContentSize().height));
    
    this->addChild(menu, 2);
    
    return true;
}

void ControlsLayer::backButtonAction(Ref* pSender)
{
    Director::getInstance()->replaceScene(TitleLayer::createScene());
}
