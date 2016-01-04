//
//  TitleLayer.cpp
//  Asteroids
//
//  Created by Clawoo on 9/18/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "TitleLayer.h"
#include "GameLayer.h"
#include "ScoresLayer.h"
#include "ControlsLayer.h"

USING_NS_CC;

Scene* TitleLayer::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	
	// 'layer' is an autorelease object
	auto layer = TitleLayer::create();
    
	// add layer as a child to scene
	scene->addChild(layer);
    
	// return the scene
	return scene;
}

bool TitleLayer::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
    
    // Get window size
    Size windowSize = Director::getInstance()->getWinSize();
    
    // Create text label for title of game - "@stroids" - don't sue me Atari!
    Label *title = Label::createWithSystemFont("@stroids", "Courier", 64.0);
    
    // Position title at center of screen
    title->setPosition(Vec2(windowSize.width / 2, windowSize.height/2));
    
    // Add to layer
    this->addChild(title, 1);
    
    // Set the default CCMenuItemFont font
    MenuItemFont::setFontName("Courier");
    
    // Create "play," "scores," and "controls" buttons - when tapped, they call methods we define: playButtonAction and scoresButtonAction
  MenuItemFont *playButton = MenuItemFont::create("play", std::bind(&TitleLayer::playButtonAction, this, std::placeholders::_1));
  MenuItemFont *scoresButton = MenuItemFont::create("scores", std::bind(&TitleLayer::scoresButtonAction, this, std::placeholders::_1));
  MenuItemFont *controlsButton = MenuItemFont::create("controls", std::bind(&TitleLayer::controlsButtonAction, this, std::placeholders::_1));
    
    // Create menu that contains our buttons
  Menu *menu = Menu::create(playButton, scoresButton, controlsButton, NULL);

    // Align buttons horizontally
    menu->alignItemsHorizontallyWithPadding(20);
    
    // Set position of menu to be below the title text
    menu->setPosition(Vec2(windowSize.width / 2, title->getPosition().y - title->getContentSize().height / 1.5));

    // Add menu to layer
    this->addChild(menu, 2);
        
	return true;
}

void TitleLayer::playButtonAction(Ref* pSender)
{
    Director::getInstance()->replaceScene(GameLayer::createScene());
}

void TitleLayer::scoresButtonAction(Ref* pSender)
{
    Director::getInstance()->replaceScene(ScoresLayer::createScene());
}

void TitleLayer::controlsButtonAction(Ref* pSender)
{
    Director::getInstance()->replaceScene(ControlsLayer::createScene());
}
