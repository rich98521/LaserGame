#ifndef LEVEL_H
#define LEVEL_H
using namespace std;
#include<iostream>
#include<fstream>
#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include "Tile.h"
#include "LaserEmitter.h"
#include "Mirror.h"
#include "Battery.h"
#include "Wall.h"
#include "Diamond.h"
#include "Leaf.h"

class Level
{
private:
	std::vector<std::vector<Tile*>> mTiles;
	int mTileSize;
	int mWidth, mHeight;
	sf::Sprite mFloorSprite, mMirrorSprite, mEmitterSprite, mBatterySprite, mWallSprite, mLaserSprite, mPortalBlueSprite, mPortalRedSprite, mDiamondSprite, mLeafSprite;
	sf::Texture mFloorTexture, mMirrorTexture, mEmitterTexture, mBatteryTexture, mWallTexture, mLaserTexture, mPortalBlueTexture, mPortalRedTexture, mDiamondTexture, mLeafTexture;
	sf::Vector2<int> mSelectedTile;
	sf::RectangleShape mSelectRect;
	sf::CircleShape mRotateCircle;
	bool mTileSelected;
	std::vector<LaserEmitter*> mEmitters;
	std::vector<Battery*> mBatteries;
	std::vector<Leaf*> mLeafs;
	void LoadResources();
	sf::Vector2<int> mMapOffset;
	int mScreenWidth, mScreenHeight;
	int mCurrentLevel;
public:
	Level(int,int,int);
	int Width() const { return mWidth; }
	int Height() const { return mHeight; }
	sf::Vector2<int> Offset() const { return mMapOffset; }
	void Draw(sf::RenderWindow*);
	void Select(int, int);
	void SwapSelected(int, int);
	bool TileSelected() const;
	bool LevelCompleted() const;
	bool IsTile(int, int) const;
	std::vector<std::vector<Tile*>> GetTiles() const;
	sf::Vector2<int> SelectedTile() const;
	void Update(sf::Time);
	void LoadLevel(int);
	void UpdateRotateCircle(int, int);
	void NextLevel();
	void PrevLevel();
};


#endif