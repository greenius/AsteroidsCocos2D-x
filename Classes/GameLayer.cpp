//
//  GameLayer.cpp
//  Asteroids
//
//  Created by Clawoo on 9/16/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "GameLayer.h"
#include "GameConfig.h"
#include "Asteroid.h"
#include "Bullet.h"
#include "TitleLayer.h"

USING_NS_CC;

GameLayer::~GameLayer()
{
  this->getEventDispatcher()->removeEventListener(listener);
  listener->release();
  listener = nullptr;
}

Scene* GameLayer::createScene()
{
	// 'scene' is an autorelease object
	Scene *scene = Scene::create();
	
	// 'layer' is an autorelease object
	GameLayer *layer = GameLayer::create();
    
	// add layer as a child to scene
	scene->addChild(layer);
    
	// return the scene
	return scene;
}

bool GameLayer::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

  listener = EventListenerTouchAllAtOnce::create();
//  listener->setSwallowTouches(true);
  listener->onTouchesBegan = CC_CALLBACK_2(GameLayer::onTouchesBegan, this);
  listener->onTouchesMoved = CC_CALLBACK_2(GameLayer::onTouchesMoved, this);
  listener->onTouchesEnded = CC_CALLBACK_2(GameLayer::onTouchesEnded, this);
  listener->retain();

  this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
  listener->setEnabled(true); // This method is used to enable/disable the touch whenever required

//    setIsTouchEnabled(true);

    // Get window size
    Size windowSize = Director::getInstance()->getWinSize();
    
    // Create ship object, position it, then add to layer
    ship_ = (Ship *)Ship::spriteWithFile("ship.png");
    ship_->setPosition(Vec2(windowSize.width / 2, windowSize.height / 2));
    this->addChild(ship_);
    
//    asteroids_ = new Vector<Sprite *>();
//    bullets_ = new Vector<Sprite *>();

    currentLevel_ = 0;
    
    this->startLevel();
    
    this->scheduleUpdate();
    
	return true;
}

void GameLayer::update(float dt)
{
    if (asteroids_.size() == 0)
    {
        currentLevel_++;
        this->startLevel();
    }
    
    // Array that keeps asteroids that need to be removed
  Vector<Sprite *> asteroidsToDelete;

    // Array that keeps asteroids that need to be split in half
  Vector<Sprite *> asteroidsToSplit;
    
    // Array that keeps expired or otherwise exploded bullets that need to be removed
    Vector<Sprite *> bulletsToDelete;

    Vector<Sprite *>::iterator it, jt;
    int i=0;
    // Check for collisions vs. asteroids
    for (it = asteroids_.begin(); it != asteroids_.end(); it++)
    {
        Asteroid *a = (Asteroid*)*it;
        CCLOG("asteroid #%d", i++);
        
        // Check if asteroid hits ship
        if (a->collidesWith(ship_))
        {
            // Game over, man!
            this->gameOver();
            return;
        }
        
        // Check if asteroid hits bullet, or if bullet is expired
        for (jt = bullets_.begin(); jt != bullets_.end(); jt++)
        {
            Bullet *b = (Bullet *)*jt;
            
            if (b->getExpired())
            {
                // Remove the bullet from organizational array
              bulletsToDelete.pushBack(b);
                // Remove bullet sprite from layer
                this->removeChild(b, false);
            }
            else if (a->collidesWith(b))
            {
                // Remove the asteroid the bullet collided with
                asteroidsToDelete.pushBack(a);
                
                // Remove asteroid sprite from layer
                this->removeChild(a, false);
                
                // Remove the bullet the asteroid collided with
                bulletsToDelete.pushBack(b);
                
                // Remove bullet sprite from layer
                this->removeChild(b, false);

                if (a->getSize() < kAsteroidSmall)
                {
                    asteroidsToSplit.pushBack(a);
                }
            }
        }
    }
    
    // split the larger asteroids that were hit by bullets
    for (it = asteroidsToSplit.begin(); it != asteroidsToSplit.end(); it++)
    {
        Asteroid *a = (Asteroid *)*it;
        for (int i = 0; i < 2; i++)
        {
            this->createAsteroidAt(a->getPosition(), a->getSize()+1);
        }
    }

  for(it = asteroidsToDelete.begin(); it != asteroidsToDelete.end(); ++it)
  {
    asteroids_.eraseObject(*it);
  }
  for(it = bulletsToDelete.begin(); it != bulletsToDelete.end(); ++it)
  {
    bullets_.eraseObject(*it);
  }
}

//MutableArray<CCTouch *>* GameLayer::allTouchesFromSet(CCSet *touches)
//{
//    MutableArray<CCTouch *> *arr = new MutableArray<CCTouch *>();
//    
//    CCSetIterator it;
//    
//	for( it = touches->begin(); it != touches->end(); it++) 
//    {
//        arr->addObject((CCTouch *)*it);
//    }
//    return arr;
//}

void GameLayer::onTouchesBegan(const std::vector<Touch*>& touches, cocos2d::Event* event)
{

    CCLOG("onTouchesBegan: %lu", (unsigned long)touches.size());

    // This method is passed an NSSet of touches called (of course) "touches"
    // We need to convert it to an array first
//    MutableArray<CCTouch *> *allTouches = this->allTouchesFromSet(touches);
//    CCTouch* fingerOne = (CCTouch *)allTouches->getObjectAtIndex(0);
  Touch* fingerOne = touches[0];

    // Convert each UITouch object to a CGPoint, which has x/y coordinates we can actually use
    Point pointOne = fingerOne->getLocationInView();
    
    // The touch points are always in "portrait" coordinates - convert to landscape
    pointOne = Director::getInstance()->convertToGL(pointOne);
    
    // We store the starting point of the touch so we can determine whether the touch is a swipe or tap.
    // A tap shouldn't move, so we compare the distance of the starting/ending touches, and if the distance is
    // small enough (we account for a bit of movement, just in case), the input is considered a tap
    startTouchPoint_ = pointOne;
    if (touches.size() > 1)
    {
        Touch *fingerTwo = touches[1];
        
        // Convert each UITouch object to a CGPoint, which has x/y coordinates we can actually use
        Point pointTwo = fingerTwo->getLocationInView();
        
        // The touch points are always in "portrait" coordinates - convert to landscape
        pointTwo = Director::getInstance()->convertToGL(pointTwo);
        
        // Initialize the variables used to store the angle of rotation derived from the user's fingers
        currentTouchAngle_ = previousTouchAngle_ = CC_RADIANS_TO_DEGREES(atan2(pointOne.x - pointTwo.x, pointOne.y - pointTwo.y));
    }
}

void GameLayer::onTouchesMoved(const std::vector<Touch*>& touches, Event* event)
{
    CCLOG("onTouchesMoved: %lu", (unsigned long)touches.size());
    // This method is passed an NSSet of touches called (of course) "touches"
    // We need to convert it to an array first
//    MutableArray<CCTouch *> *allTouches = this->allTouchesFromSet(touches);

    // Only run the following code if there is more than one touch
    if (touches.size() > 1)
    {
        // We're going to track the first two touches (i.e. first two fingers)
        // Create "UITouch" objects representing each touch
      Touch *fingerOne = touches[0];
      Touch *fingerTwo = touches[1];
        
        // Convert each UITouch object to a CGPoint, which has x/y coordinates we can actually use
        Point pointOne = fingerOne->getLocationInView();
        Point pointTwo = fingerTwo->getLocationInView();
        
        // The touch points are always in "portrait" coordinates - you will need to convert them if in landscape (which we are)
        pointOne = Director::getInstance()->convertToGL(pointOne);
        pointTwo = Director::getInstance()->convertToGL(pointTwo);
        
        // Get the angle that's created by the user's two fingers
        currentTouchAngle_ = CC_RADIANS_TO_DEGREES(atan2(pointOne.x - pointTwo.x, pointOne.y - pointTwo.y));
        
        // Compare with the previous angle, to decide whether the change is positive or negative.
        float difference = currentTouchAngle_ - previousTouchAngle_;
        
        // The ship is then rotated by that difference
        ship_->setRotation(ship_->getRotation() + difference);
        
        // Store the current angle variable to be used again on the next loop iteration
        previousTouchAngle_ = currentTouchAngle_;
    }
}

void GameLayer::onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
{
    CCLOG("onTouchesEnded: %lu", (unsigned long)touches.size());
    // This method is passed an NSSet of touches called (of course) "touches"
    // We need to convert it to an array first
//    MutableArray<CCTouch *> *allTouches = this->allTouchesFromSet(touches);

    if (touches.size() == 1)
    {
        Touch* fingerOne = touches[0];
        
        // Convert each UITouch object to a CGPoint, which has x/y coordinates we can actually use
        Point pointOne = fingerOne->getLocationInView();
        
        // The touch points are always in "portrait" coordinates - convert to landscape
        pointOne = Director::getInstance()->convertToGL(pointOne);
        
        // Set the variable that stores the ending touch point
        endTouchPoint_ = pointOne;

        // Get the distance that the user's finger moved during this touch
        float distance = sqrt(pow(endTouchPoint_.x - startTouchPoint_.x, 2) + pow(endTouchPoint_.y - startTouchPoint_.y, 2));
        
        // If the distance moved (in pixels) is small enough, consider the gesture a tap
        if (distance < 5)
        {
            this->createBullet();
        }
        // Otherwise, it's a swipe
        else
        {
            // Use distance of swipe as a multiplier for the ship velocity (longer swipe, go faster)
            ship_->setVelocity(Vec2(cos(CC_DEGREES_TO_RADIANS(ship_->getRotation())) * distance / 100, 
                                   -sin(CC_DEGREES_TO_RADIANS(ship_->getRotation())) * distance / 100));
        }
    }
}

void GameLayer::createAsteroidAt(cocos2d::Point position , int size)
{
    const char *imageFile;
    
    switch (size) {
        case kAsteroidLarge:
            imageFile = "asteroid-large.png";
            break;
        case kAsteroidMedium:
            imageFile = "asteroid-medium.png";
            break;
        case kAsteroidSmall:
            imageFile = "asteroid-small.png";
            break;
            
        default:
            break;
    }
    
    Asteroid *a = Asteroid::spriteWithFile(imageFile);
    a->setSize(size);
    a->setPosition(position);
    
    // Random numbers 
    a->setVelocity(Vec2((float)(arc4random() % 100) / 100 - 1, (float)(arc4random() % 100) / 100 - 1));
    
    // Add asteroid to organization array
    asteroids_.pushBack(a);
    
    // Add asteroid to layer
    this->addChild(a);
}

void GameLayer::createBullet()
{
    Bullet *b = Bullet::spriteWithFile("bullet.png");
    
    // Set the bullet's position by starting w/ the ship's position, then adding the rotation vector, so the bullet appears to come from the ship's nose
    
    b->setPosition(Vec2(ship_->getPosition().x + cos(CC_DEGREES_TO_RADIANS(ship_->getRotation())) * ship_->getContentSize().width, 
                       ship_->getPosition().y - sin(CC_DEGREES_TO_RADIANS(ship_->getRotation())) * ship_->getContentSize().height));
    
    // Set the bullet's velocity to be in the same direction as the ship is pointing, plus whatever the ship's velocity is
    b->setVelocity(Vec2(cos(CC_DEGREES_TO_RADIANS(ship_->getRotation())) * 2 + ship_->getVelocity().x, 
                       -sin(CC_DEGREES_TO_RADIANS(ship_->getRotation())) * 2 + ship_->getVelocity().y));
    
    // Add bullet to organizational array
    bullets_.pushBack(b);
     
    // Add bullet to layer
    this->addChild(b);
}

void GameLayer::startLevel()
{
    // Reset the ship's position, which also removes all bullets
    this->resetShip();
    
    // Get window size
    Size windowSize = Director::getInstance()->getWinSize();
    
    // Create asteroids based on level number
	for (int i = 0; i < (currentLevel_ + 2); i++)
	{
		// Random numbers
		Point randomPointOnScreen = Vec2((float)(arc4random() % 100) / 100 * windowSize.width, (float)(arc4random() % 100) / 100 * windowSize.height);
        
        this->createAsteroidAt(randomPointOnScreen, kAsteroidLarge);
	}
}

void GameLayer::resetShip()
{
  Vector<Sprite *>::iterator it;
    
    for (it = bullets_.begin(); it != bullets_.end(); it++)
    {
        Bullet *b = (Bullet *)*it;
        this->removeChild(b, true);
    }
    
    bullets_.clear();
}

void GameLayer::gameOver()
{
    this->resetShip();
    this->unscheduleUpdate();
    
    ship_->setVisible(false);
    
    Size windowSize = Director::getInstance()->getWinSize();
    
    Label *title = Label::createWithSystemFont("game over", "Courier", 64.0);
    title->setPosition(Vec2(windowSize.width / 2, windowSize.height/2));
    this->addChild(title, 1);
    
  MenuItemFont *backButton = MenuItemFont::create("back to title", std::bind(&GameLayer::backButtonAction, this, std::placeholders::_1));
    
    Menu *menu = Menu::createWithItem(backButton);
    menu->setPosition(Vec2(windowSize.width/2, title->getPosition().y - title->getContentSize().height));
    
    this->addChild(menu, 2);
}

void GameLayer::backButtonAction(Ref* pSender)
{
    Director::getInstance()->replaceScene(TitleLayer::createScene());
}
