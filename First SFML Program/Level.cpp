#include "stdafx.h" 
#include "Level.h"


void Level::LoadResources()
{
	mSelectRect.setSize(sf::Vector2f(mTileSize+4, mTileSize+4));
	mSelectRect.setFillColor(sf::Color(0,0,0,0));
	mSelectRect.setOutlineColor(sf::Color(0,255,0));
	mSelectRect.setOutlineThickness(-2);
	mRotateCircle.setRadius(55);
	mRotateCircle.setFillColor(sf::Color(0,0,0,0));
	mRotateCircle.setOutlineColor(sf::Color(60,60,60,160));
	mRotateCircle.setOutlineThickness(-15);
	mRotateCircle.setOrigin(32,32);
	mTileSelected = false;

	
	mFloorTexture.loadFromFile("../Sprites/FloorTile.png");
	mFloorSprite.setTexture(mFloorTexture);
	mLaserTexture.loadFromFile("../Sprites/Laser.png");
	mLaserSprite.setTexture(mLaserTexture);
	mMirrorTexture.loadFromFile("../Sprites/Mirror.png");
	mMirrorSprite.setTexture(mMirrorTexture);
	mEmitterTexture.loadFromFile("../Sprites/Emitter.png");
	mEmitterSprite.setTexture(mEmitterTexture);
	mWallTexture.loadFromFile("../Sprites/Wall.png");
	mWallSprite.setTexture(mWallTexture);
	mDiamondTexture.loadFromFile("../Sprites/Diamond.png");
	mDiamondSprite.setTexture(mDiamondTexture);
	mPortalBlueTexture.loadFromFile("../Sprites/Portal1.png");
	mPortalBlueSprite.setTexture(mPortalBlueTexture);
	mPortalRedTexture.loadFromFile("../Sprites/Portal2.png");
	mPortalRedSprite.setTexture(mPortalRedTexture);
	mBatteryTexture.loadFromFile("../Sprites/battery spritesheet.png");
	mBatterySprite.setTexture(mBatteryTexture);
	mBatterySprite.setTextureRect(sf::IntRect(0,0,32,32));
	mLeafTexture.loadFromFile("../Sprites/Leaf2.png");
	mLeafSprite.setTexture(mLeafTexture);
	mLeafSprite.setTextureRect(sf::IntRect(0,0,32,32));
}

void Level::NextLevel()
{
	mCurrentLevel++;
	LoadLevel(mCurrentLevel);
}

void Level::PrevLevel()
{
	mCurrentLevel = max(mCurrentLevel-1,0);
	LoadLevel(mCurrentLevel);
}

void Level::LoadLevel(int i)
{
	ifstream myReadFile;
	string line;
	myReadFile.open("../Levels/Level" + std::to_string(i) + ".txt");
	getline(myReadFile,line);
	mWidth = atoi(line.substr(0, line.find(',')).c_str());
	mHeight = atoi(line.substr( line.find(',')+1, line.size()-line.find(',')-1).c_str());
	mMapOffset = sf::Vector2<int>((mScreenWidth-mWidth*mTileSize)/2, (mScreenHeight-mHeight*mTileSize)/2);
	mTiles.clear();
	mEmitters.clear();
	mBatteries.clear();
	mLeafs.clear();
	bool portal1 = true;
	Portal* lastPortal = new Portal();
	for(int col = 0; col < mWidth; col++)
	{
		mTiles.push_back(std::vector<Tile*>());
		for(int row = 0; row < mHeight; row++)
		{
			mTiles.at(col).push_back(new Tile(sf::Vector2<int>(mTileSize/2 + col * mTileSize,mTileSize/2 + row * mTileSize), 0, mTileSize));
		}
	}
	if (myReadFile.is_open()) 
	{
		for(int row = 0; row < mHeight; row++)
		{
			getline(myReadFile,line);
			for(int col = 0; col < mWidth; col++)
			{
				string s = "";
				int i = atoi((s+line.at(col)).c_str());
				if(i == 0)
					mTiles.at(col).at(row)=(new Tile(sf::Vector2<int>(mTileSize/2 + col * mTileSize,mTileSize/2 + row * mTileSize), 0, mTileSize));
				else if(i == 1)
				{
					LaserEmitter* le = new LaserEmitter(sf::Vector2<int>(mTileSize/2 + col * mTileSize,mTileSize/2 +  row * mTileSize), 0, mEmitterSprite, mTileSize, mLaserSprite, sf::Vector2<int>(mWidth,mHeight));
					mTiles.at(col).at(row)=(le);
					mEmitters.push_back(le);
				}
				else if(i == 2)
				{
					mTiles.at(col).at(row)=(new Mirror(sf::Vector2<int>(mTileSize/2 + col * mTileSize,mTileSize/2 +  row * mTileSize), 20, mMirrorSprite, mTileSize));
				}
				else if(i == 3)
				{
					Battery* bat =(new Battery(sf::Vector2<int>(mTileSize/2 + col * mTileSize,mTileSize/2 +  row * mTileSize), mBatterySprite, mTileSize));
					mTiles.at(col).at(row) = bat;
					mBatteries.push_back(bat);
				}
				else if(i == 4)
				{
					mTiles.at(col).at(row)=(new Wall(sf::Vector2<int>(mTileSize/2 + col * mTileSize,mTileSize/2 +  row * mTileSize), mWallSprite, mTileSize));
				}
				else if(i == 5)
				{
					Leaf* lea =(new Leaf(sf::Vector2<int>(mTileSize/2 + col * mTileSize,mTileSize/2 +  row * mTileSize), mLeafSprite, mTileSize));
					mTiles.at(col).at(row) = lea;
					mLeafs.push_back(lea);
				}
				else if(i == 6)
				{
					if(portal1)
					{
						lastPortal = new Portal(sf::Vector2<int>(mTileSize/2 + col * mTileSize,mTileSize/2 +  row * mTileSize), 20, mPortalBlueSprite, mTileSize);
						mTiles.at(col).at(row)=(lastPortal);
					}
					else
					{
						Portal* p = new Portal(sf::Vector2<int>(mTileSize/2 + col * mTileSize,mTileSize/2 +  row * mTileSize), 20, mPortalRedSprite, mTileSize);
						mTiles.at(col).at(row)=(p);
						p->SetOutPortal(lastPortal);
						lastPortal->SetOutPortal(p);
					}
					portal1 = !portal1;
				}
				else if(i == 7)
				{
					mTiles.at(col).at(row)=(new Diamond(sf::Vector2<int>(mTileSize/2 + col * mTileSize,mTileSize/2 +  row * mTileSize), mDiamondSprite, mTileSize));
				}
			}
		}
	}
	myReadFile.close();
	mTileSelected = false;
}

Level::Level(int tileSize, int screenWidth, int screenHeight)
	:mTileSize(tileSize), mScreenWidth(screenWidth), mScreenHeight(screenHeight)
{
	LoadResources();
	mCurrentLevel = 1;
	LoadLevel(mCurrentLevel);
}

void Level::Update(sf::Time t)
{
	for(int i = 0;i < mBatteries.size(); i++)
	{
		mBatteries.at(i)->Update(t);
	}
	for(int i = 0;i < mLeafs.size(); i++)
	{
		mLeafs.at(i)->Update(t);
	}
}

void Level::Draw(sf::RenderWindow* window)
{
	sf::Transform t;
	t.translate(sf::Vector2f(mMapOffset));
	sf::RenderStates rs(t);
	for(int x = 0; x < mTiles.size(); x++)
		for(int y = 0; y < mTiles.at(0).size(); y++)
		{
			mFloorSprite.setOrigin(mTileSize / 2,mTileSize / 2);
			mFloorSprite.setPosition(mTileSize / 2 + mTileSize * x, mTileSize / 2 + mTileSize * y);
			window->draw(mFloorSprite, rs);
			if(!mTiles.at(x).at(y)->IsFloor())
				mTiles.at(x).at(y)->Draw(window, mMapOffset);
		}
	if(mTileSelected)
	{
		window->draw(mSelectRect, rs);
		window->draw(mRotateCircle, rs);
	}
	for(int i = 0;i < mBatteries.size(); i++)
	{
		mBatteries[i]->SetCollision(false);
	}
	for(int i = 0;i < mLeafs.size(); i++)
	{
		mLeafs[i]->SetCollision(false);
	}
	for(int i = 0;i < mEmitters.size(); i++)
	{
		mEmitters[i]->CalculateLaserPath(mTiles);
		mEmitters[i]->Draw(window, mMapOffset);
	}
}

void Level::Select(int x, int y)
{
	int xIndex = (x/mTileSize), yIndex = (y/mTileSize);
	if(!mTiles.at(xIndex).at(yIndex)->CanSelect())
	{
		mSelectedTile = sf::Vector2<int>(xIndex, yIndex);
		mTileSelected = false;
	}
	else
	{
		mTileSelected = true;
		mSelectedTile = sf::Vector2<int>(xIndex, yIndex);
		mSelectRect.setPosition(sf::Vector2f(mSelectedTile*mTileSize-sf::Vector2<int>(2,2)));
		mRotateCircle.setPosition(sf::Vector2f(mSelectedTile*mTileSize-sf::Vector2<int>(7,7)));
	}
}

void Level::UpdateRotateCircle(int x, int y)
{
	sf::Vector2<int> diff = (mSelectedTile)*mTileSize-sf::Vector2<int>(x,y)+sf::Vector2<int>(mTileSize/2,mTileSize/2);
	float dist = min(max(sqrt(diff.x*diff.x+diff.y*diff.y)+7.5f, 55.0), 160.0);
	mRotateCircle.setRadius(dist);
	mRotateCircle.setPosition(sf::Vector2f(mTileSize*1.5,mTileSize*1.5)+sf::Vector2f(mSelectedTile*mTileSize-sf::Vector2<int>(dist,dist)));
}

void Level::SwapSelected(int x, int y)
{
	Tile* selected = mTiles.at(mSelectedTile.x).at(mSelectedTile.y);
	if(selected->CanSelect() && mTiles.at(x).at(y)->IsFloor())
		if(selected != mTiles.at(x).at(y))
		{
			mTiles.at(x).at(y)->SetLocation(sf::Vector2<int>(mSelectedTile.x * mTileSize, mSelectedTile.y * mTileSize));
			selected->SetLocation(sf::Vector2<int>(x * mTileSize, y * mTileSize));
			mTiles.at(mSelectedTile.x).at(mSelectedTile.y) = mTiles.at(x).at(y);
			mTiles.at(x).at(y) = selected;
			Select(x * mTileSize, y * mTileSize);
		}
}

bool Level::TileSelected() const
{
	return mTileSelected;
}


bool Level::LevelCompleted() const
{
	bool complete = true;
	for(int i = 0; i < mBatteries.size(); i++)
	{
		if(!mBatteries[i]->Charged())
		{
			complete = false;
			break;
		}
	}
	return complete;
}

std::vector<std::vector<Tile*>> Level::GetTiles() const
{
	return mTiles;
}

bool Level::IsTile(int x, int y) const
{
	int xIndex = (x/mTileSize), yIndex = (y/mTileSize);
	return mTiles.at(xIndex).at(yIndex)->IsFloor();
}

sf::Vector2<int>  Level::SelectedTile() const
{
	return mSelectedTile;
}