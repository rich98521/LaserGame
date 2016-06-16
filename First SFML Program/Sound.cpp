#include "stdafx.h" 
#include "fmod.hpp"
#include "fmod_errors.h" // Only if you want error checking
using namespace std;
#include "Sound.h"

Sound::Sound() 
{
	playSound = true;
	playBurn = true;      
	resultBurn = FMOD::System_Create(&FMODsys);        // Create the main system object.
	resultBurn = FMODsys->init(100, FMOD_INIT_NORMAL, 0);   // Initialize FMOD.
	resultBurn = FMODsys->createSound("../Sounds/burning.mp3" ,FMOD_DEFAULT, 0, &Burnsound);
	resultBack = FMOD::System_Create(&FMODsys);        // Create the main system object.
	resultBack = FMODsys->init(100, FMOD_INIT_NORMAL, 0);   // Initialize FMOD.
	resultBack = FMODsys->createSound("../Sounds/BackGroundSound.mp3" ,FMOD_DEFAULT, 0, &Backgroundsound);
	//resultBack = FMODsys->createSound("../Sounds/BackGroundSound.mp3", FMOD_LOOP_NORMAL|FMOD_3D, 0, &Backgroundsound);
	resultBattery = FMOD::System_Create(&FMODsys);        // Create the main system object.
	resultBattery = FMODsys->init(100, FMOD_INIT_NORMAL, 0);   // Initialize FMOD.
	resultBattery = FMODsys->createSound("../Sounds/burning.mp3" ,FMOD_DEFAULT, 0, &Batterysound);

}
//
//Sound* Sound::Instance()
//{
//	if(!mSound)
//		mSound = new Sound();
//	else
//		return mSound;
//}

void Sound::PlayBurning(){    
	if(playBurn ==true)
	{
		FMODsys->playSound(FMOD_CHANNEL_FREE,Burnsound, false, &channel1); 
		channel1->setVolume(0.5f);// Set the volume while it is paused.
		channel1->setPaused(false); 
		playBurn = false;
	}
}

void Sound::PlayBatteryCharged(){
	FMODsys->playSound(FMOD_CHANNEL_FREE, Batterysound, false, &channel2); 
	channel2->setVolume(0.5f);// Set the volume while it is paused.
	channel2->setPaused(false);  
}

void Sound::RePlayBackgroundSound(){
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
	if(playSound ==true)
	{
		FMOD::Reverb *reverb;
		resultBack = FMODsys->createReverb(&reverb);
		FMOD_REVERB_PROPERTIES prop = FMOD_PRESET_UNDERWATER;
		reverb->setProperties(&prop);
		FMOD_VECTOR pos = {0, 0,0};
		float mindist = 1.0f;
		float maxdist = 10.0f;
		reverb->set3DAttributes(&pos, mindist, maxdist);
		reverb->setActive(true);


		FMODsys->playSound(FMOD_CHANNEL_FREE, Backgroundsound, false, &channel3); 
		channel3->setVolume(0.2f);// Set the volume while it is paused.
		channel3->set3DMinMaxDistance(1,15);
		channel3->setMode(FMOD_LOOP_NORMAL);
		channel3->setLoopCount(-1);
		channel3->setPaused(false);
		

		FMOD_VECTOR  listenervel  = { 1000, 1000, 0 };
		//update position & velocity of listener
		//position of listener needed for spatial & reverb effects
		//velocity of listener needed for dopper effects
		FMOD_VECTOR  listenerpos  = { 1051, 1050.0f, 1 };
		//final pair of parameters are forward direction and up direction of listener (not needed in 2D)
		FMODsys->set3DListenerAttributes(0, &listenerpos, &listenervel, 0, 0);
		//update position of sound
		if(channel3){
			FMOD_VECTOR  sourcePos  = { 1, 0.0f, 0 };
			//source is fixed so velocity is zero
			channel3->set3DAttributes(&sourcePos,0);
		}
		playSound = false;
	}
}

void Sound::PlayBackgroundSound(){
	////if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
	//if(playSound ==true)
	//{
	//	FMODsys->playSound(FMOD_CHANNEL_FREE, Backgroundsound, false, &channel3); 
	//	channel3->setVolume(0.3f);// Set the volume while it is paused.
	//	channel3->setMode(FMOD_LOOP_NORMAL);
	//	channel3->setLoopCount(-1);
	//	channel3->setPaused(false);
	//	FMOD::Reverb *reverb;
	//	resultBack = FMODsys->createReverb(&reverb);
	//	FMOD_REVERB_PROPERTIES prop = FMOD_PRESET_UNDERWATER;
	//	reverb->setProperties(&prop);
	//	FMOD_VECTOR pos = {50, 50.0f,0};
	//	float mindist = 100.0f;
	//	float maxdist = 150.0f;
	//	reverb->set3DAttributes(&pos, mindist, maxdist);
	//	reverb->setActive(true);
	//	playSound = false;
	//}
}

void Sound::PlayLaserSound(){
	////setup FMOD
	//FMOD::System *FMODsys; //will point to the FMOD system
	//FMOD_RESULT result;
	//result = FMOD::System_Create(&FMODsys);        // Create the main system object.

	//result = FMODsys->init(100, FMOD_INIT_NORMAL, 0);   // Initialize FMOD.

	//FMOD::Sound *sound;
	//result = FMODsys->createSound("../Sounds/burning.mp3" ,FMOD_DEFAULT, 0, &sound);

	//if (result != FMOD_OK)
	//{
	//	//std::cout << "FMOD error! (%d) %s\n" << result;
	//	//exit(-1);
	//}

	//FMOD::Channel *channel;

	//FMODsys->playSound(FMOD_CHANNEL_FREE, sound, true, &channel); 

	//channel->setVolume(0.5f);// Set the volume while it is paused.
	//channel->setPaused(false);  

	//FMODsys->update();
}

void Sound::Reverb()
{
	//FMOD::Reverb *reverb;
	//result = FMODsys->createReverb(&reverb);
	//FMOD_REVERB_PROPERTIES prop = FMOD_PRESET_UNDERWATER;
	//reverb->setProperties(&prop);
	//FMOD_VECTOR pos = {seaSprite.getPosition().x, 0.0f,seaSprite.getPosition().y };
	//float mindist = 100.0f;
	//float maxdist = 150.0f;
	//reverb->set3DAttributes(&pos, mindist, maxdist);
	//reverb->setActive(true);
}

void Sound::Listener()
{
	//FMOD_VECTOR  listenervel  = { velocity.x, 0.0f, velocity.y };
	////update position & velocity of listener
	////position of listener needed for spatial & reverb effects
	////velocity of listener needed for dopper effects
	//FMOD_VECTOR  listenerpos  = { listenerSprite.getPosition().x, 0.0f, listenerSprite.getPosition().y };
	////final pair of parameters are forward direction and up direction of listener (not needed in 2D)
	//FMODsys->set3DListenerAttributes(0, &listenerpos, &listenervel, 0, 0);
	//        
	////update position of sound
	//if(channel){
	//	FMOD_VECTOR  sourcePos  = { sourceSprite.getPosition().x, 0.0f, sourceSprite.getPosition().y };
	//	//source is fixed so velocity is zero
	//	channel->set3DAttributes(&sourcePos,0);
	//}
}
