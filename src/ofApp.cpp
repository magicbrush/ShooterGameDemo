#include "ofApp.h"
#include "MovingSprite.h"
#include "HuntingSprite.h"

using namespace  CPPClass;

//--------------------------------------------------------------
void ofApp::setup(){
	// 限制帧率为30
	ofSetFrameRate(30);
		
	// 读取资源文件
	ImgLevel.loadImage("Level.jpg");
	ImgPlayer.loadImage("Player.png");
	ImgBullet.loadImage("Bullet.png");
	ImgEnemy1.loadImage("Enemy1.png");
	ImgEnemy2.loadImage("Enemy2.png");	
	Font.loadFont("vag.ttf",25);
	SoundBGMusic.loadSound("background.mp3");
	SoundBGMusic.setLoop(true);
	SoundBGMusic.setVolume(0.5f);
	SoundBGMusic.play();
	SoundBullet.loadSound("bullet.mp3");
	SoundBullet.setVolume(0.5f);
	SoundBullet.setLoop(false);
	SoundBullet.setMultiPlay(true);
	SoundLaugh.loadSound("laughSordid.mp3");
	SoundLaugh.setVolume(1.0f);
	SoundLaugh.setLoop(false);
	SoundLaugh.setMultiPlay(false);
	SoundDie.loadSound("die.mp3");
	SoundDie.setVolume(1.0f);
	SoundDie.setLoop(false);
	SoundDie.setMultiPlay(true);	
	SoundMonsterDie.loadSound("monsterDie.mp3");
	SoundMonsterDie.setVolume(0.7f);
	SoundMonsterDie.setLoop(false);
	SoundMonsterDie.setMultiPlay(true);

	// 复位游戏
	Player = NULL;
	resetGame();
}

//--------------------------------------------------------------
void ofApp::update(){
	
	
	// 如果处于运行状态，则更新所有内容
	if(Running)
	{			
		// 随机添加敌人
		randGenerateEnemy();

		// 玩家行动
		updatePlayer();		

		// 子弹行动
		updateBullets();

		// 敌人行动
		updateEnemies();

		// 死亡判断
		updateLifeStates();

		// 计时
		time += ofGetLastFrameTime();
	}	

	// 删除子弹序列和敌人序列中的空指针
	eraseNullSprite(Bullets);
	eraseNullSprite(Enemys);
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	// 删除子弹序列和敌人序列中的空指针
	eraseNullSprite(Bullets);
	eraseNullSprite(Enemys);

	// 显示场景
	drawLevel();

	// 显示所有MovingSprite
	if(Running)
	{
		Player->draw();
		
		int numB = Bullets.size();
		for(int i=0;i<numB;i++)
		{
			Bullets[i]->draw();
		}
		int numE = Enemys.size();
		for(int i=0;i<numE;i++)
		{
			Enemys[i]->draw();
		}
	}	

	// 显示分数和时间
	string Score = "score:" + ofToString(score);
	string Time = "Time:" + ofToString(int(time*100)/100.0f);
	Font.drawString(Score,20,35);
	Font.drawString(Time,ofGetWidth()-200,35);

	
	if(!Running)
	{
		// ofPushMatrix()/ofPopMatrix():
		//将图形变化限制在二者之间
		ofPushMatrix();
		ofTranslate(ofGetWidth()/2,ofGetHeight()/2);
		float scl = 2.0f + 0.4f*sin(5.0f*ofGetElapsedTimef());
		ofScale(scl,scl,1.0f);
		// ofPushStyle()/ofPopStyle():
		//将绘制风格（比如颜色）限制到二者之间
		ofPushStyle();
		ofSetColor(ofColor::red);
		Font.drawString("YOU'RE DEAD!", 
			-100,0);
		ofPopStyle();
		ofPopMatrix();

		Font.drawString("F1: restart", 20,ofGetHeight()-35);
	}
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	// wasd 控制玩家的加速度
	float A = 1.0f;	
	if('w'==key)
	{
		Acc = ofVec2f(0,-A);
	}
	else if(key=='s')
	{
		Acc = ofVec2f(0,A);
	}
	else if('a'==key)
	{
		Acc = ofVec2f(-A,0);
	}
	else if('d' ==key)
	{
		Acc = ofVec2f(A,0);
	}
	// 用f1复位
	else if(OF_KEY_F1==key)
	{
		resetGame();
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	// wasd任意按键释放后，加速度为0
	if('w'==key||'s'==key||'a'==key||'d'==key)
	{
		Acc = ofVec2f(0,0);
	}
	
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	PlayerFireBulletTo(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

// 注意参数是引用，想想原因？
void ofApp::eraseNullSprite( vector<CPPClass::MovingSprite*>& S )
{
	if(S.size()==0)
	{
		return;
	}
	int num = S.size();
	for(int i=num-1;i>=0;i--)
	{
		if(S[i]==NULL)
		{
			S.erase(S.begin()+i);
		}
	}
}

// 注意参数是引用，想想原因？
void ofApp::clearSprites( vector<CPPClass::MovingSprite*>& S )
{
	int num = S.size();
	for(int i=0;i<num;i++)
	{
		delete S[i];
		S[i]=NULL;
	}
	for(int i=0;i<num;i++)
	{
		S.erase(S.begin());
	}
}

void ofApp::resetGame()
{
	Running = true;
	time = 0;
	score = 0;

	if(Player!=NULL)
	{
		delete Player;
	}
	// 6.3 动态内存分配
	Player = new MovingSprite(
		ofPoint(ofGetWidth()/2,ofGetHeight()-20),
		ofVec2f(0),
		ofVec2f(30,30),		
		&ImgPlayer);

	Acc = ofVec2f(0,0);
	clearSprites(Bullets);
	clearSprites(Enemys);
}

void ofApp::randGenerateEnemy(  )
{
	// 生成随机数
	float rn = ofRandom(0,100);
	// 利用指数函数，达到目的：时间越久，
	// 生成敌人的概率Probability值越大
	float Probability = 1.0f - exp(-0.01f*time);
	Probability *= 20.0f;
	if(rn<Probability) // 随机数小于 Probability, 生成敌人
	{
		// 以0.8概率生成笨蛋敌人，以0.2概率生成跟踪敌人
		int rn2 = ofRandom(0,100);
		MovingSprite* enemy;
		if(rn2<80)
		{
			// 6.3 动态内存分配
			enemy = new MovingSprite(
				ofPoint(ofRandom(1,ofGetWidth()-1),1),
				ofVec2f(ofRandom(-1,1),ofRandom(3,5)),
				ofVec2f(ofRandom(25,35),ofRandom(25,35)),					
				&ImgEnemy1);
		}
		else
		{
			// 6.3 动态内存分配
			enemy = new HuntingSprite(Player,
				ofPoint(ofRandom(1,ofGetWidth()-1),1),
				ofVec2f(ofRandom(-1,1),ofRandom(3,5)),
				ofVec2f(ofRandom(15,25),ofRandom(15,25)),					
				1.0f,
				&ImgEnemy2);
			// 奸笑
			SoundLaugh.play();
		}

		Enemys.push_back(enemy);
	}
}

void ofApp::updateEnemies()
{
	// RLevel 窗口
	ofRectangle RLevel(0,0,ofGetWidth(),ofGetHeight());
	// RectPlayer 玩家所在的矩形
	ofRectangle RectPlayer = Player->getRect();

	// 遍历所有敌人，执行自己的行动
	int numE = Enemys.size();
	for(int i=0;i<numE;i++)
	{
		// 更新
		Enemys[i]->update();			
	}
}

void ofApp::updateBullets()
{
	// 遍历每个子弹，移动
	int numB = Bullets.size();
	for(int i=0;i<numB;i++)
	{
		if(Bullets[i]==NULL)
		{
			continue;
		}
		// 子弹活动
		Bullets[i]->update();
		// 子弹减速
		Bullets[i]->resist(0.98);
	}
}

void ofApp::updatePlayer()
{	
	// 玩家改变速度
	Player->accelerate(Acc);
	// 玩家活动
	Player->update();
	// 玩家减速
	Player->resist(0.9);	
}

void ofApp::drawLevel()
{
	float w,h;
	w = ofGetWidth();
	h = ofGetHeight();
	ImgLevel.draw(0,0,w,h);
}

void ofApp::PlayerFireBulletTo( int x, int y )
{
	//子弹初始位置为玩家位置
	ofPoint PosPlayer = Player->getPosition();

	// 子弹射击目标为鼠标位置
	ofPoint MousePos(x,y);

	// 子弹方向为目标位置减去子弹初始位置
	ofVec2f Dir = MousePos-PosPlayer;
	Dir.normalize();
	
	// 子弹发射度为其方向矢量的15倍
	ofVec2f VelBullet = Dir*15.0f;

	// 子弹发射速度=发射速度+玩家速度
	ofVec2f FireVel = VelBullet + Player->getVelocity();

	// 生成子弹
	MovingSprite* bullet = 
		new MovingSprite(
		ofPoint(PosPlayer),
		FireVel,
		ofVec2f(10,10),
		&ImgBullet);
	Bullets.push_back(bullet);

	// 发声
	SoundBullet.play();
}

void ofApp::updateLifeStates()
{
	//　玩家死亡判断1：若超出边界，游戏结束
	ofRectangle RectPlayer = Player->getRect();
	ofRectangle RLevel(0,0,ofGetWidth(),ofGetHeight());
	if(!RectPlayer.intersects(RLevel))
	{			
		Running = false;
		// 惨叫
		SoundDie.play();		
	}
	//　玩家死亡判断2：被敌人逮着
	int numE = Enemys.size();
	for(int i=0;i<numE;i++)
	{
		ofRectangle RectEnemy = Enemys[i]->getRect();
		// 是否抓住玩家
		if(RectPlayer.intersects(RectEnemy))
		{
				// 游戏结束
				Running = false;
				// 惨叫
				SoundDie.play();
		}					
	}

	// 敌人和子弹的死亡判断
	numE = Enemys.size();
	// 是否出界
	for(int i=0;i<numE;i++)
	{
		ofPoint P = Enemys[i]->getPosition();
		if(!RLevel.inside(P))
		{
			delete Enemys[i];// 6.3 动态内存分配
			Enemys[i] =NULL;
			continue;
		}	
	}
	eraseNullSprite(Enemys);

	//　是否挨子弹
	numE = Enemys.size();
	for(int i=0;i<Enemys.size();i++)
	{			
			ofRectangle RectEnemy = Enemys[i]->getRect();	
			int numB = Bullets.size();
			for(int j=0;j<numB;j++)
			{
				if(Bullets[j]==NULL)
				{
					continue;
				}
				ofPoint PBullet = Bullets[j]->getPosition();
				if(RectEnemy.inside(PBullet)&&Enemys[i]!=NULL)// 中弹
				{
					// 删除敌人和子弹
					score += Enemys[i]->getScore();
					delete Enemys[i]; // 6.3 动态内存分配
					Enemys[i] =NULL;
					Bullets[j]->setVelocity(ofVec2f(0));					

					// 死亡音效
					// 以不同的大小、速度播放，实现每个怪物不同喊声
					SoundMonsterDie.setVolume(ofRandom(0.4f,0.8f));
					SoundMonsterDie.setSpeed(ofRandom(0.5f,1.5f));
					SoundMonsterDie.play();
				}
			}			
	}		
	eraseNullSprite(Enemys);	

	// 子弹死亡判断
	int numB = Bullets.size();
	for(int i=0;i<numB;i++)
	{
		if(Bullets[i]==NULL)
		{
			continue;
		}
		
		if(Bullets[i]->getVelocity().length()<0.33f)
		{
			// 子弹速度过小，则消失
			delete Bullets[i];
			Bullets[i]=NULL;
		}
	}
	eraseNullSprite(Bullets);

	

}
