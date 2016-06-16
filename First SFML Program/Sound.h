// FMOD.cpp : Defines the entry point for the console application.
//
//FMOD includes
//#pragma comment(lib,"fmodex_vc.lib")
#ifndef SOUND_H
#define SOUND_H
#include "Tile.h"
#include <iostream> 
#include <math.h>

class Sound{
public:
		Sound();
		void PlayBurning();
		void Update();
		void PlayBatteryCharged();
		void PlayBackgroundSound();
		void RePlayBackgroundSound();
		void PlayLaserSound();
		void Listener();
		void Reverb();
		int soundNum;
		bool playSound;
		bool playBurn;
		FMOD::Sound *Burnsound;
		FMOD::Sound *Backgroundsound;
		FMOD::Sound *Batterysound;
		FMOD::System *FMODsys; //will point to the FMOD system
		FMOD_RESULT resultBurn;
		FMOD_RESULT resultBack;
		FMOD_RESULT resultBattery;
		FMOD::Channel *channel1;
		FMOD::Channel *channel2;
		FMOD::Channel *channel3;

private:
	

		
	
};
#endif
